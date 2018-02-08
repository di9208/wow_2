#include "stdafx.h"
#include "cParticle.h"


cParticle::cParticle()
{
}


cParticle::~cParticle()
{
	SAFE_RELEASE(_vb);
	SAFE_RELEASE(_tex);
}

bool cParticle::init(char * FileName)
{
	g_pD3DDevice->CreateVertexBuffer(
		_vbSize * sizeof(Particle),
		D3DUSAGE_DYNAMIC | D3DUSAGE_POINTS | D3DUSAGE_WRITEONLY,
		ST_PC_VERTEX::FVF,
		D3DPOOL_DEFAULT, // D3DPOOL_MANAGED can't be used with D3DUSAGE_DYNAMIC 
		&_vb,
		0);
	std::string file = std::string(FileName);
	_tex = g_pTextureManager->GetTexture(file);
	return true;
}

void cParticle::reset()
{
	std::list<Attribute>::iterator i;
	for (i = _particles.begin(); i != _particles.end(); i++)
	{
		resetParticle(&(*i));
	}
}

void cParticle::addParticle()
{
	Attribute attribute;

	resetParticle(&attribute);

	_particles.push_back(attribute);
}

void cParticle::preRender()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);

	g_pD3DDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, true);
	g_pD3DDevice->SetRenderState(D3DRS_POINTSCALEENABLE, true);

	g_pD3DDevice->SetRenderState(D3DRS_POINTSCALE_A, FtoDw(0.0f));
	g_pD3DDevice->SetRenderState(D3DRS_POINTSCALE_B, FtoDw(0.0f));
	g_pD3DDevice->SetRenderState(D3DRS_POINTSCALE_C, FtoDw(1.0f));

	g_pD3DDevice->SetRenderState(D3DRS_POINTSIZE, FtoDw(_size));
	g_pD3DDevice->SetRenderState(D3DRS_POINTSIZE_MIN, FtoDw(0.2f));
	g_pD3DDevice->SetRenderState(D3DRS_POINTSIZE_MAX, FtoDw(20.0f));

	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	g_pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 0x00000088);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

}

void cParticle::postRender()
{


	g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, 0);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, false);
	g_pD3DDevice->SetRenderState(D3DRS_POINTSCALEENABLE, false);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	//g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
}

void cParticle::removeDeadParticles()
{
	std::list<Attribute>::iterator i;

	i = _particles.begin();

	while (i != _particles.end())
	{
		if (i->isAlive == false)
		{
			// erase returns the next iterator, so no need to
			// incrememnt to the next one ourselves.
			i = _particles.erase(i);
		}
		else
		{
			i++; // next in list
		}
	}
}

void cParticle::render()
{
	if (!_particles.empty())
	{
		//
		// set render states
		//

		preRender();

		g_pD3DDevice->SetTexture(0, _tex);
		g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
		g_pD3DDevice->SetStreamSource(0, _vb, 0, sizeof(Particle));

		//
		// render batches one by one
		//

		// start at beginning if we're at the end of the vb
		if (_vbOffset >= _vbSize)
			_vbOffset = 0;

		Particle* v = 0;

		_vb->Lock(
			_vbOffset * sizeof(Particle),
			_vbBatchSize * sizeof(Particle),
			(void**)&v,
			_vbOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD);

		DWORD numParticlesInBatch = 0;

		//
		// Until all particles have been rendered.
		//
		std::list<Attribute>::iterator i;
		for (i = _particles.begin(); i != _particles.end(); i++)
		{
			if (i->isAlive)
			{
				//
				// Copy a batch of the living particles to the
				// next vertex buffer segment
				//
			

				v->position = i->position;
				v->color = (D3DCOLOR)i->color;
				v++; // next element;

				numParticlesInBatch++; //increase batch counter

									   // if this batch full?
				if (numParticlesInBatch == _vbBatchSize)
				{
					//
					// Draw the last batch of particles that was
					// copied to the vertex buffer. 
					//
					_vb->Unlock();

					g_pD3DDevice->DrawPrimitive(
						D3DPT_POINTLIST,
						_vbOffset,
						_vbBatchSize);

					//
					// While that batch is drawing, start filling the
					// next batch with particles.
					//

					// move the offset to the start of the next batch
					_vbOffset += _vbBatchSize;

					// don't offset into memory thats outside the vb's range.
					// If we're at the end, start at the beginning.
					if (_vbOffset >= _vbSize)
						_vbOffset = 0;

					_vb->Lock(
						_vbOffset * sizeof(Particle),
						_vbBatchSize * sizeof(Particle),
						(void**)&v,
						_vbOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD);

					numParticlesInBatch = 0; // reset for new batch
				}
			}
		}

		_vb->Unlock();

		// its possible that the LAST batch being filled never 
		// got rendered because the condition 
		// (numParticlesInBatch == _vbBatchSize) would not have
		// been satisfied.  We draw the last partially filled batch now.

		if (numParticlesInBatch)
		{
			g_pD3DDevice->DrawPrimitive(
				D3DPT_POINTLIST,
				_vbOffset,
				numParticlesInBatch);
		}

		// next block
		_vbOffset += _vbBatchSize;

		//
		// reset render states
		//

		postRender();
	}
}

bool cParticle::isEmpty()
{
	return _particles.empty();
}

bool cParticle::isDead()
{
	std::list<Attribute>::iterator i;
	for (i = _particles.begin(); i != _particles.end(); i++)
	{
		// is there at least one living particle?  If yes,
		// the system is not dead.
		if (i->isAlive)
			return false;
	}
	// no living particles found, the system must be dead.
	return true;
}

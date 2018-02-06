#pragma once

class cParticle
{
public:

	struct Particle
	{
		D3DXVECTOR3 position;
		D3DCOLOR    color;
	};

	struct Attribute
	{
		D3DXVECTOR3 position;
		D3DXVECTOR3 velocity;
		D3DXVECTOR3 acceleration;
		float       lifeTime;     // how long the particle lives for before dying  
		float       age;          // current age of the particle  
		D3DXCOLOR   color;        // current color of the particle   
		D3DXCOLOR   colorFade;    // how the color fades with respect to time
		bool        isAlive;

		Attribute()
			:lifeTime(0.0f)
			,age(0.0f)
			,isAlive(true)
		{
		}
	};

protected:

	D3DXVECTOR3             _pos;
	float                   _size;       // size of particles
	IDirect3DVertexBuffer9* _vb;
	std::list<Attribute>    _particles;
	LPDIRECT3DTEXTURE9		_tex;
	int    _maxParticles; // max allowed particles system can have

//
// Following three data elements used for rendering the p-system efficiently


	DWORD _vbSize;      // size of vb
	DWORD _vbOffset;    // offset in vb to lock   
	DWORD _vbBatchSize;

public:
	cParticle();
	~cParticle();

	static DWORD FtoDw(float f)
	{
		return *((DWORD*)&f);
	}
	virtual bool init(char* FileName);
	virtual void reset();

	// sometimes we don't want to free the memory of a dead particle,
	// but rather respawn it instead.
	virtual void resetParticle(Attribute* attribute) = 0;
	virtual void addParticle();

	virtual void update(float timeDelta) = 0;

	virtual void preRender();
	virtual void render();
	virtual void postRender();

	void removeDeadParticles();

	bool isEmpty();
	bool isDead();
};


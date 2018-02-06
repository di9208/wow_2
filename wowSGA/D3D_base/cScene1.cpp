#include "stdafx.h"
#include "cScene1.h"
#include "cStage1.h"
#include "cFrustum.h"

cScene1::cScene1()
{
}


cScene1::~cScene1()
{
}

void cScene1::Setup()
{
	m_Map = new cStage1;
	m_Map->Setup();
	m_frustum = new cFrustum;
}

void cScene1::Update()
{
	m_frustum->SetupVertex();
}

void cScene1::Render()
{
	
	m_Map->Draw(m_frustum);

}

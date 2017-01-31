#include "stdafx.h"
#include "Emanation.h"


CEmanation::CEmanation(LPDIRECT3DDEVICE9 pDevice)
: CSingleGameObject(pDevice)
, m_pVertex(NULL)
, m_pConvertVertex(NULL)
, m_bCulling(true)
, m_bContents(true)
{

}

CEmanation::~CEmanation(void)
{
	Release();
}

HRESULT CEmanation::Initialize(void)
{
	return S_OK;
}

void CEmanation::Update(void)
{

}

void CEmanation::Render(void)
{

}

void CEmanation::Release(void)
{

}


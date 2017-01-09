#include "StdAfx.h"
#include "Background.h"


CBackground::CBackground( LPDIRECT3DDEVICE9 pDevice )
: m_pDeivce(pDevice)
{

}

CBackground::~CBackground( void )
{

}

void CBackground::Initialize( void )
{

}

void CBackground::Render( void )
{

}

void CBackground::Release( void )
{

}

void CBackground::KeyCheck( void )
{

}

void CBackground::Picking( void )
{

}

CBackground* CBackground::Create( LPDIRECT3DDEVICE9 pDevice )
{
	CBackground* pBack = new CBackground(pDevice);

	if (FAILED(pBack))
		Engine::Safe_Delete(pBack);

	return pBack;
}

#include "StdAfx.h"
#include "Background.h"


CBackground::CBackground( LPDIRECT3DDEVICE9 pDevice )
: m_pDeivce(pDevice)
{

}

CBackground::~CBackground( void )
{

}

CBackground* CBackground::Create( LPDIRECT3DDEVICE9 pDevice )
{
	CBackground* pBack = new CBackground(pDevice);

	if (FAILED(pBack))
		Engine::Safe_Delete(pBack);

	return pBack;
}

#include "StdAfx.h"
#include "CubeObj.h"
#include "CubeCol.h"

CCubeObj::CCubeObj( LPDIRECT3DDEVICE9 pDevice )
:m_pDevice(pDevice)
{

}

CCubeObj::~CCubeObj( void )
{
	Release();
}

HRESULT CCubeObj::Initialize()
{
	return S_OK;
}

void CCubeObj::Update()
{

}

void CCubeObj::Render()
{
	MAPCUBE::iterator iter = m_mapCube.begin();
	MAPCUBE::iterator iter_end = m_mapCube.end();

	for ( ; iter != iter_end; ++iter)
	{
		iter->second->Render();
	}
}

void CCubeObj::Release()
{
	MAPCUBE::iterator iter = m_mapCube.begin();
	MAPCUBE::iterator iter_end = m_mapCube.end();
	
	for_each(iter, iter_end, Engine::CDeleteMap());
	m_mapCube.clear();
}

CCubeObj* CCubeObj::Create( LPDIRECT3DDEVICE9 pDevice )
{
	CCubeObj* pCubeObj = new CCubeObj(pDevice);

	if (FAILED(pCubeObj->Initialize()))
		Engine::Safe_Delete(pCubeObj);

	return pCubeObj;
}
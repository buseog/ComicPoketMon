#include "ResourceMgr.h"
#include "RcCol.h"
#include "TriCol.h"
#include "RcTerrain.h"
#include "Texture.h"
#include "RcTex.h"
#include "TerrainTex.h"
#include "CubeTex.h"

IMPLEMENT_SINGLETON(Engine::CResourceMgr)

Engine::CResourceMgr::CResourceMgr(void)
: m_pResource(NULL)
{

}

Engine::CResourceMgr::~CResourceMgr(void)
{
	Release();
}

HRESULT Engine::CResourceMgr::AddBuffer(LPDIRECT3DDEVICE9 pDevice, 
										 RESOURCETYPE eResourceType, 
										 CVIBuffer::BUFFERTYPE eBufferType, 
										 const wstring& wstrResourceKey, 
										 const WORD& wCntX /*= 0*/, 
										 const WORD& wCntZ /*= 0*/, 
										 const WORD& wItv /*= 1*/)
{
	MAPRESOURCE::iterator		iter = m_MapResource[eResourceType].find(wstrResourceKey);

	/*MAPRESOURCE::iterator		iter = find_if(m_MapResource[eResourceType].begin(), 
												m_MapResource[eResourceType].end(), 
												CTagFinder(wstrResourceKey));*/

	if(iter != m_MapResource[eResourceType].end())
	{
		TAGMSG_BOX(wstrResourceKey.c_str(), L"중복된 리소스");
		return E_FAIL;
	}

	CResources*		pResources = NULL;

	switch(eBufferType)
	{
	case CVIBuffer::BUFFER_TRICOL:
		pResources = CTriCol::Create(pDevice);
		break;
		
	case CVIBuffer::BUFFER_RCCOL:
		pResources = CRcCol::Create(pDevice);
		break;

	case CVIBuffer::BUFFER_TERRAIN:
		pResources = CRcTerrain::Create(pDevice, wCntX, wCntZ, wItv);
		break;

	case CVIBuffer::BUFFER_RCTEX:
		pResources = CRcTex::Create(pDevice);
		break;

	case CVIBuffer::TERRAIN_TEX:
		pResources = CTerrainTex::Create(pDevice, wCntX, wCntZ, wItv);
		break;

	case CVIBuffer::BUFFER_CUBETEX:
		pResources = CCubeTex::Create(pDevice); 
		break;
	}
	
	NULL_CHECK_RETURN(pResources, E_FAIL);

	m_MapResource[eResourceType].insert(MAPRESOURCE::value_type(wstrResourceKey, pResources));


	return S_OK;
}

void Engine::CResourceMgr::Render(const wstring& wstrResourceKey)
{
	MAPRESOURCE::iterator		iter = m_MapResource[0].find(wstrResourceKey);

	if(iter == m_MapResource[0].end())
		return ;

	iter->second->Render();
}

void Engine::CResourceMgr::Release(void)
{
	for(int i = 0; i < RESOURCE_END; ++i)
	{
		for_each(m_MapResource[i].begin(), m_MapResource[i].end(), CDeleteMap());
		m_MapResource[i].clear();	
	}
}

HRESULT Engine::CResourceMgr::AddTexture(LPDIRECT3DDEVICE9 pDevice, 
										  RESOURCETYPE eResourceType, 
										  TEXTURETYPE eTextureType,
										  const wstring& wstrResourceKey, 
										  const wstring& wstrFilePath, 
										  const WORD& wCnt)
{
	MAPRESOURCE::iterator	iter = m_MapResource[eResourceType].find(wstrResourceKey);

	if(iter != m_MapResource[eResourceType].end())
	{
		TAGMSG_BOX(wstrResourceKey.c_str(), L"중복된 리소스");
		return E_FAIL;
	}

	CResources*		pResources = CTexture::Create(pDevice, eTextureType, wstrFilePath, wCnt);

	NULL_CHECK_RETURN(pResources, E_FAIL);

	m_MapResource[eResourceType].insert(MAPRESOURCE::value_type(wstrResourceKey, pResources));

	return S_OK;
}

void Engine::CResourceMgr::ResetDynamic(void)
{
	if(!m_MapResource[RESOURCE_DYNAMIC].empty())
	{
		for_each(m_MapResource[RESOURCE_DYNAMIC].begin(), 
			m_MapResource[RESOURCE_DYNAMIC].end(), 
			CDeleteMap());

		m_MapResource[RESOURCE_DYNAMIC].clear();
	}	
}

Engine::CComponent* Engine::CResourceMgr::CloneResource(RESOURCETYPE eResourceType, 
												 const wstring& wstrResourceKey)
{
	MAPRESOURCE::iterator	iter = m_MapResource[eResourceType].find(wstrResourceKey);

	if(iter == m_MapResource[eResourceType].end())
	{
		TAGMSG_BOX(wstrResourceKey.c_str(), L"복사 실패");
		return NULL;
	}

	return iter->second->CloneResource();
}

void Engine::CResourceMgr::SetVtxInfo(RESOURCETYPE eResourceType, 
									   const wstring& wstrResourceKey, 
									   void* pVertex)
{
	MAPRESOURCE::iterator	iter = m_MapResource[eResourceType].find(wstrResourceKey);

	if(iter == m_MapResource[eResourceType].end())
	{
		TAGMSG_BOX(wstrResourceKey.c_str(), L"버텍스를 찾을 수 없음");
		return;
	}

	((CVIBuffer*)iter->second)->SetVtxInfo(pVertex);
}

void Engine::CResourceMgr::GetVtxInfo(RESOURCETYPE eResourceType, 
									   const wstring& wstrResourceKey, 
									   void* pVertex)
{
	MAPRESOURCE::iterator	iter = m_MapResource[eResourceType].find(wstrResourceKey);

	if(iter == m_MapResource[eResourceType].end())
	{
		TAGMSG_BOX(wstrResourceKey.c_str(), L"버텍스를 찾을 수 없음");
		return;
	}

	((CVIBuffer*)iter->second)->GetVtxInfo(pVertex);
}


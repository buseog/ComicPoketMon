#ifndef ResourceMgr_h__
#define ResourceMgr_h__


#include "VIBuffer.h"

BEGIN(Engine)

class CResources;
class CComponent;
class ENGINE_DLL CResourceMgr
{
	DECLARE_SINGLETON(CResourceMgr)

private:
	typedef	map<wstring, CResources*>		MAPRESOURCE;
	MAPRESOURCE								m_MapResource[RESOURCE_END];

private:
	void	Release(void);

public:
	void	SetVtxInfo(RESOURCETYPE eResourceType, const wstring& wstrResourceKey, void* pVertex);
	void	GetVtxInfo(RESOURCETYPE eResourceType, const wstring& wstrResourceKey, void* pVertex);
	void	Render(const wstring& wstrResourceKey);
	void	ResetDynamic(void);

public:
	HRESULT			AddBuffer(LPDIRECT3DDEVICE9 pDevice, RESOURCETYPE eResourceType, CVIBuffer::BUFFERTYPE eBufferType, const wstring& wstrResourceKey, const WORD& wCntX = 0, const WORD& wCntZ = 0, const WORD& wItv = 1);
	HRESULT			AddTexture(LPDIRECT3DDEVICE9 pDevice, RESOURCETYPE eResourceType, TEXTURETYPE eTextureType, const wstring& wstrResourceKey,	const wstring& wstrFilePath, const WORD& wCnt);

	HRESULT			AddResource(RESOURCETYPE eResourceType, const wstring& wstrResourceKey, CResources* pResources);
	
	CComponent*		CloneResource(RESOURCETYPE eResourceType, const wstring& wstrResourceKey);

private:
	CResourceMgr(void);
	~CResourceMgr(void);
};

END
#endif // ResourceMgr_h__

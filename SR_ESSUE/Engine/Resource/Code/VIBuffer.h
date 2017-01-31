#ifndef VIBuffer_h__
#define VIBuffer_h__

#include "Resources.h"

BEGIN(Engine)

class ENGINE_DLL CVIBuffer
	:public CResources
{
public:
	enum BUFFERTYPE { BUFFER_TRICOL, BUFFER_RCCOL, BUFFER_TERRAIN, BUFFER_RCTEX, TERRAIN_TEX, BUFFER_CUBETEX, BUFFER_CUBECOL };

protected:
	LPDIRECT3DVERTEXBUFFER9		m_pVB;
	LPDIRECT3DINDEXBUFFER9		m_pIB;
	void*						m_pOriginVertex;
	void*						m_pOriginIndex;

	D3DXVECTOR3					m_vScale;

	DWORD						m_dwVtxSize;
	DWORD						m_dwVtxCnt;
	DWORD						m_dwVtxFVF;
	DWORD						m_dwTriCnt;

	DWORD						m_dwIdxSize;
	D3DFORMAT					m_IdxFmt;

public:
	void	Render(void);
	void	Release(void);

	void	SetScale(D3DXVECTOR3 vScale);
	D3DXVECTOR3*	GetScale(void);
	void	SetVtxInfo(void* pVertex);
	void	GetVtxInfo(void* pVertex);
	void	GetOriginVtxInfo(void* pVertex);
	void	SetOriginVtxInfo(void* pVertex);
	void	GetIdxInfo(void* pIndex);

public:
	virtual HRESULT		CreateBuffer(void);
	virtual CResources* CloneResource(void);


protected:
	explicit CVIBuffer(LPDIRECT3DDEVICE9 pDevice);
public:
	virtual ~CVIBuffer(void);

};

END
#endif // VIBuffer_h__

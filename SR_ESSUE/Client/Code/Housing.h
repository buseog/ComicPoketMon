#ifndef Housing_h__
#define Housing_h__

#include "GameObject.h"
#include "ZFrustum.h"
#include "BoundCol.h"
namespace Engine
{
	class CResourceMgr;
	class CTexture;
	class CVIBuffer;

	class CTransform;
	class CBoundBox;
	class CInfoSubject;
	class CVIBuffer;
}
class CStaticCamera;
class CCameraObserver;
class CCollisionMgr;

class CHousing
	: public Engine::CGameObject
{
protected:

	vector<Engine::CVIBuffer*>  m_vecBuffer;

	Engine::VTXCUBE*			m_pVertex;
	Engine::VTXCUBE*			m_pConvertVertex;

	Engine::CResourceMgr*		m_pResourceMgr;

	Engine::CTransform*			m_pInfo;
	Engine::CBoundBox*			m_pBox;
	CBoundCol*					m_pBoundCol;
	
	Engine::CInfoSubject*		m_pInfoSubject;

	CCameraObserver*			m_pCameraObserver;
	CCollisionMgr*				m_pCollisionMgr;
	CZFrustum*					m_pZFrustum;

	DWORD						m_dwVtxCnt;

	wstring						m_wstrStatekey;


public:
	void	Release(void);
	void	LoadFile(wstring wstrLoadKey);

public:
	virtual HRESULT Initialize( void );
	virtual void Update( void );
	virtual void Render( void );


protected:
	explicit	CHousing(LPDIRECT3DDEVICE9 pDevice);

public:
	virtual ~CHousing(void);
};
#endif // Housing_h_
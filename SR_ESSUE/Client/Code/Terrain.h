


#ifndef Terrain_h__
#define Terrain_h__

#include "GameObject.h"

namespace Engine
{
	class CTexture;
	class CVIBuffer;
	class CResourceMgr;
	class CTimeMgr;
	class CTransform;
	class CInfoSubject;

}
class CCameraObserver;
class CTerrain : public Engine::CGameObject
{
private:
	Engine::CResourceMgr*		m_pResourceMgr;
	Engine::CTimeMgr*			m_pTimeMgr;
	Engine::CTransform*			m_pInfo;
	float						m_fSpeed;

	Engine::CVIBuffer*			m_pBuffer;
	Engine::CTexture*			m_pTexture;

private:
	Engine::VTXTEX*				m_pVertex;
	Engine::VTXTEX*				m_pConvertVertex;
	DWORD						m_dwVtxCnt;

	Engine::CInfoSubject*		m_pInfoSubject;
	CCameraObserver*			m_pCameraObserver;

private:
	HRESULT						Initialize(void);
	void						SetDirection(void);

private:
	void	SetTransform(void);
	void	DataLoad(void);

public:
	static	CTerrain*	Create(LPDIRECT3DDEVICE9 pDevice);
	void				Update(void);
	void				Render(void);
	void				Release(void);
	HRESULT				AddComponent(void);
public:
	virtual const Engine::VTXTEX*	GetTerrainVertex(void);

private:
	explicit	CTerrain(LPDIRECT3DDEVICE9 pDevice);
public:
	~CTerrain(void);

};
#endif // Terrain_h__

//*!
// * \file FireEffect.h
// * \date 2017/01/24 15:27
// *
// * \author Jusin
// * Contact: user@company.com
// *
// * \brief ∆ƒ¿Ã∏Æ¿« ∫“≤… ¿Ã∆Â∆Æ
// *
// * TODO: long description
// *
// * \note
//*/

#ifndef FireEffect_h__
#define FireEffect_h__

#include "SingleGameObject.h"
#include "Include.h"
#include "Engine_Include.h"

namespace Engine
{
	class CTransform;
	class CObserver;
	class CInfoSubject;
	class CTimeMgr;
}

class CFireEffect : public CSingleGameObject
{
private:
	Engine::CTimeMgr*			m_pTimeMgr;
	IDirect3DVertexBuffer9*		m_pVB;
	Engine::CInfoSubject*		m_pInfoSubject;
	CCameraObserver*			m_pCameraObserver;

	Engine::VTXTEX*				m_pVertex;
	Engine::VTXTEX*				m_pConvertVertex;
	DWORD						m_dwVtxCnt;
	Engine::CVIBuffer*			m_pBuffer;
	Engine::CTexture*			m_pTexture;

	Engine::SPRITETEX*			m_pSprite;

	float						m_fDistance;
	float						m_fCameraAngle;

	float						m_fTime;
	float						m_fSpeed;

	//FRAME						m_tFrame;


public:
	static CFireEffect*			Create(LPDIRECT3DDEVICE9 pDevice);
	void						SetTransform(void);

	HRESULT						Initialize(void);
	void						Update(void);
	void						Render(void);
	void						Release(void);

	HRESULT						Addcomponent(void);
	void						SetPos(const D3DXVECTOR3& vPos);

	HRESULT						Sprite(void);


private:
	explicit CFireEffect(LPDIRECT3DDEVICE9 pDevice);
public:
	~CFireEffect();
};
#endif // FireEffect_h__
/*!
 * \file ElectricEffect.h
 * \date 2017/01/25 9:04
 *
 * \author Administrator
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/


#ifndef ElectricEffect_h__
#define ElectricEffect_h__

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

class CElectricEffect : public CSingleGameObject
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

public:
	static CElectricEffect*		Create(LPDIRECT3DDEVICE9 pDevice, const wstring& wstrKey, D3DXVECTOR3 vOrigin, D3DXVECTOR3 vDir, int iCount);
	void						SetTransform(void);

	HRESULT						Initialize(const wstring& wstrKey, D3DXVECTOR3 vOrigin, D3DXVECTOR3 vDir, int iCount);
	void						Update(void);
	void						Render(void);
	void						Release(void);

	HRESULT						Addcomponent(void);

	HRESULT						Sprite(void);


private:
	explicit CElectricEffect(LPDIRECT3DDEVICE9 pDevice);
public:
	~CElectricEffect();
};

#endif // ElectricEffect_h__
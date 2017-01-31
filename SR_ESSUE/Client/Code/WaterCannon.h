/*!
 * \file WaterCannon.h
 * \date 2017/01/25 8:16
 *
 * \author Administrator
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note µ¶½Ã¹ßÁð
*/
#include "Emanation.h"

#ifndef WaterCannon_h__
#define WaterCannon_h__

namespace Engine
{
	class CTransform;
	class CLayer;
}

class CWaterCannon : public CEmanation
{
private:
	Engine::CLayer* m_pLayer;

private:
	HRESULT				Initialize(Engine::CTransform* pTransform, D3DXVECTOR3 vDir);
	void				SetDirection(void);
	void				SetTransform(void);

	float				m_fCetTime;

public:
	virtual void		Update(void);
	virtual void		Render(void);
	void				Release(void);
	HRESULT				AddComponent(void);

public:
	static	CWaterCannon*		Create(LPDIRECT3DDEVICE9 pDevice, 
										Engine::CLayer* pLayer, 
										Engine::CTransform* pTransform, 
										D3DXVECTOR3 vDir);

private:
	explicit	CWaterCannon(LPDIRECT3DDEVICE9 pDevice, Engine::CLayer* pLayer);

public:
	virtual~CWaterCannon();

};

#endif // WaterCannon_h__
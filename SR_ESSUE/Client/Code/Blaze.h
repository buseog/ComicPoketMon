/*!
 * \file flame.h
 * \date 2017/01/24 4:45
 *
 * \author Administrator
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \ 활활타는 화염 입니다^^ 학원을 불태우는 핫함입니다.
*/

#include "Emanation.h"

#ifndef flame_h__
#define flame_h__

namespace Engine
{
	class CTransform;
	class CLayer;
}
class CBlaze : public CEmanation
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
	static	CBlaze*		Create(LPDIRECT3DDEVICE9 pDevice, 
								Engine::CLayer* pLayer, 
								Engine::CTransform* pTransform, 
								D3DXVECTOR3 vDir);

private:
	explicit	CBlaze(LPDIRECT3DDEVICE9 pDevice, Engine::CLayer* pLayer);

public:
	virtual~CBlaze();

};
#endif // flame_h__
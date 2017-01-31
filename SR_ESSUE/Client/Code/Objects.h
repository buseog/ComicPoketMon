/*!
 * \file Objects.h
 * \date 2017/01/25 4:54
 *
 * \author Administrator
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note ���ù��� �߰��Ѵ� ������Ʈ �ٵ� �����ۿ� ����
*/

#include "SingleGameObject.h"

#ifndef Objects_h__
#define Objects_h__

namespace Engine
{
	class CLayer;
}

class CObjects : public CSingleGameObject
{
private:
	Engine::VTXTEX*	m_pVertex;
	Engine::VTXTEX*	m_pConvertVertex;

	wstring			m_wstrTexKey;
	int				m_iTexCount;

private:
	HRESULT				Initialize(Engine::OBJINFO tObjInfo);
	void				SetTransform(void);

public:
	void				Update(void);
	void				Render(void);
	void				Release(void);
	HRESULT				AddComponent(void);


public:
	static	CObjects* Create(LPDIRECT3DDEVICE9 pDevice, Engine::OBJINFO tObjInfo);

private:
	explicit CObjects(LPDIRECT3DDEVICE9 pDevice);

public:
	virtual ~CObjects(void);
};
#endif // Objects_h__
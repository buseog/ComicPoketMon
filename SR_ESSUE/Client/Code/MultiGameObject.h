/*!
 * \file MultiGameObject.h
 * \date 2017/01/14 3:29
 *
 * \author ESSUE
 * Contact: user@company.com
 *
 * \brief 멀티 오브젝트 클래스
 *
 * TODO: long description
 *
 * \note 단일 버퍼가 아닌 다중 버퍼를 가진 클래스들을 대상으로 한 상위 클래스
*/

#ifndef MultiGameObject_h__
#define MultiGameObject_h__

#include "GameObject.h"

namespace Engine
{
	class CResources;
}

class CMultiGameObject
	: public Engine::CGameObject
{
protected:
	typedef vector<Engine::CResources*>		VECVERTEX;
	VECVERTEX								m_vecVertex;

public:
	void	Release(void);
	void	LoadFile(wstring wstrLoadKey);

public:
	virtual HRESULT Initialize( void );
	virtual void Update( D3DXMATRIX* matWorld, D3DXMATRIX* matView, D3DXMATRIX* matProj );
	virtual void Render( void );

public:
	static	CMultiGameObject*	Create(LPDIRECT3DDEVICE9 pDevice, wstring wstrLoadKey);

protected:
	explicit	CMultiGameObject(LPDIRECT3DDEVICE9 pDevice);

public:
	virtual ~CMultiGameObject(void);
};

#endif // MultiGameObject_h__
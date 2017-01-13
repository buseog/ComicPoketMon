/*!
 * \file MultiGameObject.h
 * \date 2017/01/14 3:29
 *
 * \author ESSUE
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
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
private:
	typedef vector<Engine::CResources*>			VECVERTEX;
	VECVERTEX							m_vecVertex;

public:
	void	Release(void);
	void	LoadFile(wstring wstrLoadKey);

public:
	virtual HRESULT Initialize( void );
	virtual void Update( void );
	virtual void Render( void );

public:
	static	CMultiGameObject*	Create(LPDIRECT3DDEVICE9 pDevice, wstring wstrLoadKey);

private:
	explicit	CMultiGameObject(LPDIRECT3DDEVICE9 pDevice);

public:
	~CMultiGameObject(void);
};

#endif // MultiGameObject_h__
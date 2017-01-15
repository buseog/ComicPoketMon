/*!
 * \file SingleGameObject.h
 * \date 2017/01/14 3:48
 *
 * \author ESSUE
 * Contact: user@company.com
 *
 * \brief �̱� ������Ʈ Ŭ����
 *
 * TODO: long description
 *
 * \note ���� ���۸� ���� Ŭ�������� ���� Ŭ����
*/

#ifndef SingleGameObject_h__
#define SingleGameObject_h__

#include "GameObject.h"

class CSingleGameObject
	: public Engine::CGameObject
{
public:
	void	Release(void);

public:
	virtual HRESULT Initialize( void );
	virtual void Update( void );
	virtual void Render( void );

public:
	static	CSingleGameObject*	Create(LPDIRECT3DDEVICE9 pDevice, wstring wstrLoadKey);

protected:
	explicit	CSingleGameObject(LPDIRECT3DDEVICE9 pDevice);

public:
	~CSingleGameObject(void);
};

#endif // SingleGameObject_h__
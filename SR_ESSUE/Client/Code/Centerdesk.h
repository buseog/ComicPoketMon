#ifndef Centerdesk_h__
#define Centerdesk_h__

#include "Housing.h"

namespace Engine
{
	class CResourceMgr;
	class CManagement;
	class CTexture;
	class CVIBuffer;

	class CTransform;
	class CBoundBox;
	class CInfoSubject;
	class CLayer;
}

class CBoundCol;

class CCenterdesk
	: public CHousing
{
private:
	Engine::CBoundBox*			m_pPotalBox;
	Engine::CLayer*				m_pLayer;
	Engine::CManagement*		m_pManagement;

	int							m_iState;
	Engine::CGameObject*		m_pPlayer;

public:
	void		Release(void);
	HRESULT		AddComponent(void);
	void		Load( void );
	void		SetTrensform(void);

	void		PotalSetting(void);
	void		SetPlayer(Engine::CGameObject* pPlayer);
	void		ColPlayer(void);
	void		ColMonster(void);

	void		SetLayer(Engine::CLayer* pLayer);

public:
	virtual HRESULT Initialize( int iState );
	virtual void Update( void );
	virtual void Render( void );

public:
	static	CCenterdesk*	Create(LPDIRECT3DDEVICE9 pDevice, int iState);

protected:
	explicit	CCenterdesk(LPDIRECT3DDEVICE9 pDevice);

public:
	virtual ~CCenterdesk(void);
};

#endif // Centerdesk_h__

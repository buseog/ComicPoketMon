#ifndef Wall_h__
#define Wall_h__

#include "Housing.h"
#include "Include.h"

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

class CWall
	: public CHousing
{
private:
	Engine::CBoundBox*			m_pPotalBox;
	Engine::CLayer*				m_pLayer;
	Engine::CManagement*		m_pManagement;

	SCENEID						m_eState;

public:
	void		Release(void);
	HRESULT		AddComponent(void);
	void		Load(SCENEID ID);
	void		SetTrensform(void);

	void		PotalSetting(void);
	void		SetLayer(Engine::CLayer* pLayer);

	void		ColPlayer(void);

public:
	virtual HRESULT Initialize( SCENEID ID );
	virtual void Update( void );
	virtual void Render( void );

public:
	static	CWall*	Create(LPDIRECT3DDEVICE9 pDevice, SCENEID ID);

protected:
	explicit	CWall(LPDIRECT3DDEVICE9 pDevice);

public:
	virtual ~CWall(void);
};
#endif // Wall_h_


#ifndef Npc_h__
#define Npc_h__

#include "MultiGameObject.h"

class CTerrainCol;
class CBoundCol;

class CNpc
	: public CMultiGameObject
{
private:
	CTerrainCol*				m_pTerrainCol;
	bool						m_bState;
	float						m_fPattenTime;

private:
	HRESULT		Initialize( void );
	void		Release(void);
	void		SetDirection(void);
	void		Load(void);
	void        Patten(void);

public:
	HRESULT		AddComponent(void);
	void		Update( void );
	void		Render( void );
	void		SetPos(const D3DXVECTOR3& vPos);

public:
	static	CNpc*	Create(LPDIRECT3DDEVICE9 pDevice);

private:
	explicit CNpc(LPDIRECT3DDEVICE9 pDevice);

public:
	virtual	~CNpc(void);
	
};
#endif // Npc_h__

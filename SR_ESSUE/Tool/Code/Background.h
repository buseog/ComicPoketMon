/*!
 * \file Background.h
 * \date 2017/01/08 23:42
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
#ifndef Background_h__
#define Background_h__

#include "GameObject.h"

namespace Engine
{
	class CVIBuffer;
	class CResourceMgr;
	class CTexture;
}

class CBackground :
	public Engine::CGameObject
{
public:
	//LPDIRECT3DDEVICE9	m_pDeivce;
	Engine::CTexture*	m_pTexture;

	list<Engine::CTexture*>	m_pObjectTexturelist;

	list<Engine::CComponent*>	m_Resorceslist;
	list<Engine::OBJINFO>		m_ObjList;

	float		m_fAngle[Engine::ANGLE_END];
	float		m_fDistance;

	D3DXVECTOR3 m_vEye, m_vAt;
	D3DXMATRIX	matView, matProj;

	LPD3DXLINE	m_pLine;

	int			m_iIndex;

	Engine::CResourceMgr*		m_pResourceMgr;
	Engine::VTXTEX*				m_pVertex;

public:
	Engine::CVIBuffer*	m_pBuffer;

public:
	void	Release(void);
	void	KeyCheck(void);
	void	Picking(void);
	void	DrawLine(void);
	void	Picking_AddObject(void);

	list<Engine::OBJINFO>* GetObjList(void);
public:
	void	AddTerrain(int iX, int iZ);

	void	SetIndex(int iIndex);

	Engine::VTXTEX* GetVtxcol(void);
	void			SetVtxcol(Engine::VTXTEX* pVertex);
	void			AddObject(D3DXVECTOR3 &vPos);

public:
	virtual HRESULT Initialize( void );
	virtual void Update( void );
	virtual void Render( void );

public:
	static CBackground* Create(LPDIRECT3DDEVICE9 pDevice);

private:
	explicit CBackground(LPDIRECT3DDEVICE9 pDevice);
public:
	virtual ~CBackground(void);
};

#endif // Background_h__

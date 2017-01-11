#ifndef ObjBack_h__
#define ObjBack_h__
#include "Gameobject.h"


namespace Engine
{
	class CVIBuffer;
	class CResourceMgr;
	class CTexture;
}

class CMainFrame;
class CObjBack :
	public Engine::CGameObject
{
public:
	LPDIRECT3DDEVICE9	m_pDeivce;
	Engine::CVIBuffer*	m_pBuffer;
	Engine::CTexture*	m_pTexture;

	list<Engine::CComponent*>	m_pCubeList;

	float		m_fAngle[Engine::ANGLE_END];
	float		m_fDistance;
	D3DXVECTOR3 m_vEye, m_vAt;
	D3DXMATRIX	matView, matProj;
	LPD3DXLINE	m_pLine;

public:
	void	Release(void);
	void	KeyCheck(void);
	void	DeletePicking(void);
	void	SelectPicking(void);
	void	AddPicking(void);
	void	SetTransCube(D3DXVECTOR3 vPos);
	void	DrawLine(void);

public:
	void	AddObject(wstring wstrTetureKey, D3DXVECTOR3 vScale, D3DXVECTOR3 vPos = D3DXVECTOR3(0.f, 0.f, 0.f));

public:
	virtual HRESULT Initialize( void );
	virtual void Update( void );
	virtual void Render( void );

public:
	static CObjBack* Create(LPDIRECT3DDEVICE9 pDevice);

private:
	explicit CObjBack(LPDIRECT3DDEVICE9 pDevice);
public:
	virtual ~CObjBack(void);
};
#endif
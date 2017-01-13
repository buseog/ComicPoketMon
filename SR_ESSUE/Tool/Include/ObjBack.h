#ifndef ObjBack_h__
#define ObjBack_h__
#include "Gameobject.h"


namespace Engine
{
	class CVIBuffer;
	class CResourceMgr;
	class CResources;
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

	map<wstring, Engine::CResources*>	m_mapChar;

	float		m_fAngle[Engine::ANGLE_END];
	float		m_fDistance;
	D3DXVECTOR3 m_vEye, m_vAt;
	D3DXMATRIX	matView, matProj;
	LPD3DXLINE	m_pLine;

	Engine::VTXCOL*		m_pVertex;
	Engine::INDEX32*	m_pIndex;

public:
	void	Release(void);
	void	KeyCheck(void);
	void	DeletePicking(void);
	void	SelectPicking(void);
	void	AddPicking(void);
	void	SetTransCube(D3DXVECTOR3 vPos, D3DXVECTOR3 vScale);
	void	SetRotationCube(int iFlag, float fAngle);
	void	SetApplyCube(void);
	void	SetColor(DWORD dwColor);
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
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
}

class CBackground :
	public Engine::CGameObject
{
private:
	LPDIRECT3DDEVICE9	m_pDeivce;
	Engine::CVIBuffer*	m_pBuffer;

	float		m_fAngle[Engine::ANGLE_END];
	float		m_fDistance;
	D3DXVECTOR3 m_vEye, m_vAt;
	D3DXMATRIX	matView, matProj;

public:
	void	Release(void);
	void	KeyCheck(void);
	void	Picking(void);

public:
	void	AddTerrain(int iX, int iZ);

public:
	virtual HRESULT Initialize( void );
	virtual void Update( void );
	virtual void Render( void );

public:
	static CBackground* Create(LPDIRECT3DDEVICE9 pDevice);

private:
	explicit CBackground(LPDIRECT3DDEVICE9 pDevice);
public:
	~CBackground(void);
};

#endif // Background_h__

/*!
 * \file UI.h
 * \date 2017/01/16 3:19
 *
 * \author ESSUE
 * Contact: user@company.com
 *
 * \brief UI �θ� Ŭ����
 *
 * TODO: long description
 *
 * \note ���� ������ �ϴ� UI�� �ʿ��� ������ �Լ����� ���⿹��
*/

#ifndef UI_h__
#define UI_h__


#include "GameObject.h"

BEGIN(Engine)

class ENGINE_DLL CUI 
	: public Engine::CGameObject
{
protected:
	D3DXVECTOR3		m_vPos;
	D3DXVECTOR3		m_vSize;
	D3DXMATRIX		m_matWorld, m_matView, m_matProj;
	RECT			m_rcRect;

public:
	void	SetUI(void);
	RECT	GetRect(void);

public:
	virtual void Update( void );

protected:
	explicit CUI(LPDIRECT3DDEVICE9 pDevice);

public:
	virtual ~CUI(void);


	
};

END
#endif // UI_h__
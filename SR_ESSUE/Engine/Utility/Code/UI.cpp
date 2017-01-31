#include "UI.h"
#include "Export_Function.h"

Engine::CUI::CUI( LPDIRECT3DDEVICE9 pDevice )
: CGameObject(pDevice)
, m_vPos(0.f, 0.f, 0.f)
, m_vSize(0.f, 0.f, 0.f)
{
	Engine::MyIdentity(&m_matWorld);
	Engine::MyIdentity(&m_matView);
	Engine::MyIdentity(&m_matProj);
}

Engine::CUI::~CUI( void )
{

}

void Engine::CUI::Update( void )
{
	// 월드는 0, 0이 왼쪽 끝이지만 투영 좌표계는 0,0이 화면 정가운데 (400,300) 이라서 변환이 필요함
	D3DXVECTOR3 vWolrdUI = D3DXVECTOR3(WINCX / 2.f, WINCY / 2.f, 0.f);
	D3DXVECTOR3 vProjUI = vWolrdUI;
	vProjUI.x *= -1.f;

	Engine::MyIdentity(&m_matView);

	m_matView._11 = m_vSize.x;
	m_matView._22 = m_vSize.y;
	m_matView._33 = 1.f;

	vProjUI.x += m_vPos.x;
	vProjUI.y -= m_vPos.y;

	RECT rc = {
		long(vWolrdUI.x + vProjUI.x - m_vSize.x),
		long(vWolrdUI.y - vProjUI.y - m_vSize.y),
		long(vWolrdUI.x + vProjUI.x + m_vSize.x),
		long(vWolrdUI.y - vProjUI.y + m_vSize.y)
	};

	m_rcRect = rc;

	memcpy(&m_matView.m[3][0], &vProjUI, sizeof(D3DXVECTOR3));
}

void Engine::CUI::SetUI( void )
{
	m_vSize /= 2.f;

	m_matView._11 = m_vSize.x;
	m_matView._22 = m_vSize.y;
	m_matView._33 = m_vSize.z;

	D3DXMatrixOrthoLH(&m_matProj, (float)WINCX, (float)WINCY, 0.f, 1.f);
}

RECT	Engine::CUI::GetRect(void)
{
	return m_rcRect;
}
#include "stdafx.h"
#include "Logo.h"

#include "Include.h"
#include "SceneSelector.h"
#include "Export_Function.h"
#include "TriCol.h"

CLogo::CLogo(LPDIRECT3DDEVICE9 pDevice)
: Engine::CScene(pDevice)
, m_pManagement(Engine::Get_Management())
, m_pTriCol(NULL)
{

}

CLogo::~CLogo(void)
{
	Engine::Safe_Delete(m_pTriCol);
}

HRESULT CLogo::InitScene(void)
{
	m_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	m_pTriCol = Engine::CTriCol::Create(m_pDevice);

	return S_OK;
}

void CLogo::Update(void)
{
	if(GetAsyncKeyState(VK_RETURN))
	{
		m_pManagement->SceneChange(CSceneSelector(SC_STAGE));
		return;
	}
}

void CLogo::Render(void)
{
	m_pTriCol->Render();

}

CLogo* CLogo::Create(LPDIRECT3DDEVICE9 pDevice)
{
	CLogo*	pLogo = new CLogo(pDevice);

	if (FAILED(pLogo->InitScene()))
		Engine::Safe_Delete(pLogo);

	return pLogo;
}


#include "stdafx.h"
#include "Logo.h"

#include "Include.h"
#include "SceneSelector.h"
#include "Export_Function.h"

CLogo::CLogo(LPDIRECT3DDEVICE9 pDevice)
: Engine::CScene(pDevice)
, m_pManagement(Engine::Get_Management())

{

}

CLogo::~CLogo(void)
{

}

HRESULT CLogo::InitScene(void)
{
	m_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);



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

}

CLogo* CLogo::Create(LPDIRECT3DDEVICE9 pDevice)
{
	CLogo*	pLogo = new CLogo(pDevice);

	if (FAILED(pLogo->InitScene()))
		Engine::Safe_Delete(pLogo);

	return pLogo;
}


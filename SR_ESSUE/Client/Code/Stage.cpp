#include "stdafx.h"
#include "Stage.h"

#include "Include.h"
#include "Export_Function.h"
#include "RcCol.h"

CStage::CStage(LPDIRECT3DDEVICE9 pDevice)
: Engine::CScene(pDevice)
, m_pRcCol(NULL)
{

}

CStage::~CStage(void)
{
	Engine::Safe_Delete(m_pRcCol);
}

HRESULT CStage::InitScene(void)
{
	m_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	m_pRcCol = Engine::CRcCol::Create(m_pDevice);

	return S_OK;
}

void CStage::Update(void)
{
	
}

void CStage::Render(void)
{
	m_pRcCol->Render();
}

CStage* CStage::Create(LPDIRECT3DDEVICE9 pDevice)
{
	CStage*		pStage = new CStage(pDevice);

	if (FAILED(pStage->InitScene()))
		Engine::Safe_Delete(pStage);

	return pStage;
}


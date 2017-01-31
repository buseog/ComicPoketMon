#include "StdAfx.h"
#include "Gauge.h"

#include "Export_Function.h"
#include "ResourceMgr.h"
#include "Include.h"
#include "Texture.h"

#include "StatSubject.h"
#include "UIObserver.h"
#include "Status.h"

CGauge::CGauge( LPDIRECT3DDEVICE9 pDevice )
: Engine::CUI(pDevice)
, m_pResourceMgr(Engine::Get_ResourceMgr())
, m_pConvertVertex(NULL)
, m_pVertex(NULL)
, m_pStatSubject(Engine::Get_StatSubject())
, m_wstrkey(L"")
{

}

CGauge::~CGauge( void )
{
	Release();
}

HRESULT CGauge::Initialize( const wstring& wstrKey )
{
	m_wstrkey = wstrKey;

	FAILED_CHECK(AddComponent());

	m_pUIObserver = CUIObserver::Create();
	m_pStatSubject->Subscribe(m_pUIObserver);

	m_dwVtxCnt			= 4;
	m_pVertex			= new Engine::VTXTEX[m_dwVtxCnt];
	m_pConvertVertex	= new Engine::VTXTEX[m_dwVtxCnt];

	if (m_wstrkey == L"HP Gauge")
	{
		m_vPos = D3DXVECTOR3(130.f, 520.f, 0.f);
		m_vSize = D3DXVECTOR3(90.f, 11.f, 0.f);
		m_pResourceMgr->GetVtxInfo(Engine::RESOURCE_STATIC, L"Buffer Gauge", m_pVertex);
	}
	else if (m_wstrkey == L"MP Gauge")
	{
		m_vPos = D3DXVECTOR3(130.f, 570.f, 0.f);
		m_vSize = D3DXVECTOR3(90.f, 11.f, 0.f);
		m_pResourceMgr->GetVtxInfo(Engine::RESOURCE_STATIC, L"Buffer Gauge", m_pVertex);
	}
	
	CUI::SetUI();



	return S_OK;
}

void CGauge::Update( void )
{
	RenewalSize();

	Engine::CGameObject::Update();
	Engine::CUI::Update();
	SetTransform();
}

void CGauge::Render( void )
{
	m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	m_pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00000088);
	m_pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	m_pResourceMgr->SetVtxInfo(Engine::RESOURCE_STATIC, L"Buffer Gauge", m_pConvertVertex);

	m_pTexture->Render(0);
	m_pBuffer->Render();

	m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

void CGauge::Release( void )
{
	if(m_pVertex)
	{
		Engine::Safe_Delete_Array(m_pVertex);
	}

	if(m_pConvertVertex)
	{
		Engine::Safe_Delete_Array(m_pConvertVertex);
	}
	Engine::Safe_Delete(m_pUIObserver);
}

HRESULT CGauge::AddComponent( void )
{
	Engine::CComponent*		pComponent = NULL;

	if (m_wstrkey == L"HP Gauge")
	{
		// Buffer
		pComponent = m_pResourceMgr->CloneResource(Engine::RESOURCE_STATIC, L"Buffer Gauge");
		m_pBuffer = dynamic_cast<Engine::CVIBuffer*>(pComponent);
		NULL_CHECK_RETURN(m_pBuffer, E_FAIL);
		m_mapComponent.insert(MAPCOMPONENT::value_type(L"Buffer", pComponent));

		//Texture
		pComponent = m_pResourceMgr->CloneResource(Engine::RESOURCE_STATIC, L"Texture HpGauge");
		m_pTexture = dynamic_cast<Engine::CTexture*>(pComponent);
		NULL_CHECK_RETURN(m_pTexture, E_FAIL);
		m_mapComponent.insert(MAPCOMPONENT::value_type(L"Texture", pComponent));
	}
	else if (m_wstrkey == L"MP Gauge")
	{
		// Buffer
		pComponent = m_pResourceMgr->CloneResource(Engine::RESOURCE_STATIC, L"Buffer Gauge");
		m_pBuffer = dynamic_cast<Engine::CVIBuffer*>(pComponent);
		NULL_CHECK_RETURN(m_pBuffer, E_FAIL);
		m_mapComponent.insert(MAPCOMPONENT::value_type(L"Buffer", pComponent));

		//Texture
		pComponent = m_pResourceMgr->CloneResource(Engine::RESOURCE_STATIC, L"Texture MpGauge");
		m_pTexture = dynamic_cast<Engine::CTexture*>(pComponent);
		NULL_CHECK_RETURN(m_pTexture, E_FAIL);
		m_mapComponent.insert(MAPCOMPONENT::value_type(L"Texture", pComponent));
	}


	return S_OK;
}

void CGauge::RenewalSize(void)
{
	Engine::CStatus* pStat = m_pUIObserver->GetStatus();

	if (pStat)
	{
		if (m_wstrkey == L"HP Gauge")
		{
			float fPercnet = pStat->fHp / pStat->fFullHp;
			m_vSize = D3DXVECTOR3(90.f * fPercnet, 11.f, 0.f);
			m_vPos.x = 130.f - (90.f - m_vSize.x) / 2.f;
		}
		if (m_wstrkey == L"MP Gauge")
		{
			float fPercnet = pStat->fMp / pStat->fFullMp;
			m_vSize = D3DXVECTOR3(90.f * fPercnet, 11.f, 0.f);
			m_vPos.x = 130.f - (90.f - m_vSize.x) / 2.f;
		}
	}

	SetUI();
}

void CGauge::SetTransform( void )
{
	D3DXMATRIX matPrint = m_matWorld * m_matView * m_matProj;

	for(size_t i = 0; i < m_dwVtxCnt; ++i)
	{
		m_pConvertVertex[i] = m_pVertex[i];

		Engine::MyTransformCoord(&m_pConvertVertex[i].vPos, 
			&m_pConvertVertex[i].vPos, 
			&matPrint);
	}
}

CGauge* CGauge::Create( LPDIRECT3DDEVICE9 pDevice ,const wstring& wstrKey)
{
	CGauge* pGuage = new CGauge(pDevice);

	if (FAILED(pGuage->Initialize(wstrKey)))
		Engine::Safe_Delete(pGuage);

	return pGuage;
}

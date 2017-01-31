#include "StdAfx.h"
#include "Effect.h"

CEffect::CEffect( LPDIRECT3DDEVICE9 pDevice )
:CSingleGameObject(pDevice)
, m_pVertex(NULL)
, m_pConvertVertex(NULL)
, m_pSprite(NULL)
{

}

CEffect::~CEffect( void )
{
	Release();
}

HRESULT CEffect::Initialize( D3DXVECTOR3 vPos, const wstring& wstrObjKey)
{
	m_pCameraObserver = CCameraObserver::Create();
	m_pInfoSubject->Subscribe(m_pCameraObserver);

	m_wstrObjkey = wstrObjKey;

	FAILED_CHECK(AddComponent());

	m_dwVtxCnt			=	4;
	m_pVertex			=	new Engine::VTXCUBE[m_dwVtxCnt];
	m_pConvertVertex	=	new Engine::VTXCUBE[m_dwVtxCnt];

	m_pResourceMgr->GetVtxInfo(Engine::RESOURCE_STATIC, L"Buffer Effect", m_pVertex);
	m_pInfo->vPos = vPos;

	if (m_wstrObjkey == L"Explosion")
	{
		m_pSprite->fSpriteMax = 6.f;
	}
	
	return S_OK;
}

void CEffect::Update( void )
{
	SetTransform();
	CGameObject::Update();
	m_pSprite->PlaySprite();
}

void CEffect::Render( void )
{
	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	m_pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00000088);
	m_pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	m_pResourceMgr->SetVtxInfo(Engine::RESOURCE_STATIC, L"Buffer RcTex", m_pConvertVertex);
	m_pTexture->Render((DWORD)m_pSprite->fSpriteCnt);
	m_pBuffer->Render();

	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

void CEffect::Release( void )
{
	if (m_pVertex)
	{
		Engine::Safe_Delete_Array(m_pVertex);
	}

	if (m_pConvertVertex)
	{
		Engine::Safe_Delete_Array(m_pConvertVertex);
	}

	if (m_pInfoSubject != NULL)
		m_pInfoSubject->UnSubscribe(m_pCameraObserver);

	Engine::Safe_Delete(m_pCameraObserver);
}

HRESULT CEffect::AddComponent( void )
{
	Engine::CComponent*		pComponent = NULL;

	// Transform
	pComponent = m_pInfo = Engine::CTransform::Create(g_vLook);
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Transform", pComponent));

	// Sprite
	pComponent = m_pSprite = Engine::CSprite::Create();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Sprite", pComponent));

	// Buffer
	pComponent = m_pResourceMgr->CloneResource(Engine::RESOURCE_STATIC, L"Buffer Effect");
	m_pBuffer = dynamic_cast<Engine::CVIBuffer*>(pComponent);
	NULL_CHECK_RETURN(m_pBuffer, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"HpBar Buffer", pComponent));

	// Texture
	if (m_wstrObjkey == L"Explosion")
	{
		pComponent = m_pResourceMgr->CloneResource(Engine::RESOURCE_STATIC, m_wstrObjkey);
		m_pTexture = dynamic_cast<Engine::CTexture*>(pComponent);
		NULL_CHECK_RETURN(m_pTexture, E_FAIL);
		m_mapComponent.insert(MAPCOMPONENT::value_type(m_wstrObjkey, pComponent));
	}

	return S_OK;
}

void CEffect::SetTransform( void )
{
	const D3DXMATRIX*		pMatView = m_pCameraObserver->GetView();
	NULL_CHECK(pMatView);

	const D3DXMATRIX*		pMatProj = m_pCameraObserver->GetProj();
	NULL_CHECK(pMatProj);

	D3DXMATRIX matBill;
	Engine::MyIdentity(&matBill);

	matBill = *pMatView;
	ZeroMemory(&matBill.m[3][0], sizeof(D3DXVECTOR3));
	D3DXMatrixInverse(&matBill, NULL, &matBill);

	D3DXMATRIX matWorld;
	Engine::MyIdentity(&matWorld);

	memcpy(&matWorld.m[3][0], m_pInfo->matWorld.m[3], sizeof(float) * 3);

	matWorld = matBill * matWorld * (*pMatView) * (*pMatProj);

	for(size_t i = 0; i < 4; ++i)
	{
		m_pConvertVertex[i] = m_pVertex[i];

		Engine::MyTransformCoord(&m_pConvertVertex[i].vPos, 
			&m_pConvertVertex[i].vPos, 
			&matWorld);
	}
}

CEffect* CEffect::Create( LPDIRECT3DDEVICE9 pDevice, D3DXVECTOR3 vPos, const wstring& wstrObjKey)
{
	CEffect* pEffect = new CEffect(pDevice);

	if (FAILED(pEffect->Initialize(vPos, wstrObjKey)))
		Engine::Safe_Delete(pEffect);

	return pEffect;
}

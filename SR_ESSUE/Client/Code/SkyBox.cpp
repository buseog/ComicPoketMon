#include "stdafx.h"
#include "SkyBox.h"

CSkyBox::CSkyBox(LPDIRECT3DDEVICE9 pDevice)
: CSingleGameObject(pDevice)
, m_iBoxCount(6)
, m_fSize(50.f)
, m_finterval(m_fSize/2.f)
{

}

CSkyBox::~CSkyBox(void)
{
	Release();
}

HRESULT CSkyBox::Initialize(void)
{
	m_pCameraObserver = CCameraObserver::Create();
	m_pInfoSubject->Subscribe(m_pCameraObserver);

	FAILED_CHECK(AddComponent());

	int		iVertxCount = 11;
	float	fAddToch	= 100.f;

	m_dwVtxCnt = iVertxCount * iVertxCount;
	
	for(size_t i = 0; i< m_iBoxCount; i++)
	{
		m_vecVertex.push_back(new Engine::VTXTEX[m_dwVtxCnt]);
		m_vecConvertVertex.push_back(new Engine::VTXTEX[m_dwVtxCnt]);
		m_pResourceMgr->GetVtxInfo(Engine::RESOURCE_STATIC, L"Buffer SkyBox", m_vecVertex[i]);
	}

	m_finterval = (float)iVertxCount * m_fSize / 2.f;

	D3DXMATRIX matScale, matRot, matTrans;

	D3DXMatrixScaling(&matScale, m_fSize, m_fSize, m_fSize);
	
	// 정면
	D3DXMatrixRotationX(&matRot, D3DXToRadian(90.f));
	D3DXMatrixTranslation(&matTrans, 
		-m_finterval + fAddToch, 
		m_finterval - m_fSize, 
		m_finterval - m_fSize + fAddToch);
	m_matBoxWorld[2] = matScale * matRot * matTrans;

	// 윗면
	D3DXMatrixRotationX(&matRot, D3DXToRadian(-180.f));
	D3DXMatrixTranslation(&matTrans, 
		-m_finterval + fAddToch, 
		-m_finterval, 
		m_finterval - m_fSize + fAddToch);
	m_matBoxWorld[1] = matScale * matRot * matTrans;
	
	// 뒷면
	D3DXMatrixRotationX(&matRot, D3DXToRadian(-90.f));
	D3DXMatrixTranslation(&matTrans, 
		-m_finterval + fAddToch, 
		-m_finterval, 
		-m_finterval + fAddToch);
	m_matBoxWorld[0] = matScale * matRot * matTrans;
	
	// 아랫면
	D3DXMatrixTranslation(&matTrans, 
		-m_finterval + fAddToch, 
		m_finterval - m_fSize, 
		-m_finterval + fAddToch);
	m_matBoxWorld[3] = matScale * matTrans;

	// 오른쪽면
	D3DXMatrixRotationZ(&matRot, D3DXToRadian(-90.f));
	D3DXMatrixTranslation(&matTrans, 
		m_finterval - m_fSize + fAddToch, 
		m_finterval - m_fSize, 
		-m_finterval + fAddToch);
	m_matBoxWorld[4] = matScale * matRot * matTrans;

	// 왼쪽면
	D3DXMatrixRotationZ(&matRot, D3DXToRadian(90.f));
	D3DXMatrixTranslation(&matTrans, 
		-m_finterval + fAddToch, 
		-m_finterval, 
		-m_finterval + fAddToch);
	m_matBoxWorld[5] = matScale * matRot * matTrans;


	return S_OK;
}

void CSkyBox::SetDirection(void)
{

}

CSkyBox* CSkyBox::Create(LPDIRECT3DDEVICE9 pDevice)
{
	CSkyBox*		pSkyBox = new CSkyBox(pDevice);

	if(FAILED(pSkyBox->Initialize()))
		Engine::Safe_Delete(pSkyBox);

	return pSkyBox;
}

void CSkyBox::Update(void)
{
	SetDirection();

	Engine::CGameObject::Update();

	SetTransform();
}

void CSkyBox::Render(void)
{
	m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

	//스테이지 스카이 박스
	if(Engine::CManagement::m_iScene == SC_STAGE)
	{
		for(size_t i = 0; i< m_iBoxCount; i++)
		{
			m_pResourceMgr->SetVtxInfo(Engine::RESOURCE_STATIC, L"Buffer SkyBox", m_vecConvertVertex[i]);
			if(i == 3)
				m_pTexture->Render(1);
			else
				m_pTexture->Render(0);
			m_pBuffer->Render();
		}
	}

	//센터 스카이 박스
	if(Engine::CManagement::m_iScene == SC_CENTER)
	{
		for(size_t i = 0; i< m_iBoxCount; i++)
		{
			m_pResourceMgr->SetVtxInfo(Engine::RESOURCE_STATIC, L"Buffer SkyBox", m_vecConvertVertex[i]);
			m_pTexture->Render(2);
			m_pBuffer->Render();
		}
	}

	m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

void CSkyBox::Release(void)
{
	vector<Engine::VTXTEX*>::iterator iter = m_vecVertex.begin();
	vector<Engine::VTXTEX*>::iterator iter_End = m_vecVertex.end();

	vector<Engine::VTXTEX*>::iterator convertiter = m_vecConvertVertex.begin();
	vector<Engine::VTXTEX*>::iterator convertiter_End = m_vecConvertVertex.end();

	for(; iter != iter_End; ++iter)
	{
		if((*iter))
			Engine::Safe_Delete_Array((*iter));
	}
	
	for(; convertiter != convertiter_End; ++convertiter)
	{
		if((*convertiter))
			Engine::Safe_Delete_Array((*convertiter));

	}
	Engine::Safe_Delete(m_pCameraObserver);
}

HRESULT CSkyBox::AddComponent(void)
{
	Engine::CComponent*		pComponent = NULL;

	pComponent = m_pInfo = Engine::CTransform::Create(g_vLook);
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Transform", pComponent));

	pComponent = m_pResourceMgr->CloneResource(Engine::RESOURCE_STATIC, L"Buffer SkyBox");
	m_pBuffer = dynamic_cast<Engine::CVIBuffer*>(pComponent);
	NULL_CHECK_RETURN(m_pBuffer, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Buffer", pComponent));

	pComponent = m_pResourceMgr->CloneResource(Engine::RESOURCE_STATIC, L"Texture SkyBox");
	m_pTexture = dynamic_cast<Engine::CTexture*>(pComponent);
	NULL_CHECK_RETURN(m_pTexture, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Texture", pComponent));

	return S_OK;
}

void CSkyBox::SetTransform(void)
{
	const D3DXMATRIX*		pMatView = m_pCameraObserver->GetView();
	NULL_CHECK(pMatView);

	const D3DXMATRIX*		pMatProj = m_pCameraObserver->GetProj();
	NULL_CHECK(pMatProj);

	D3DXMATRIX matPrint = (*pMatView) * (*pMatProj);

	for(size_t i= 0; i< m_iBoxCount; ++i)
	{
		for(size_t index = 0; index < m_dwVtxCnt; ++index)
		{
			m_vecConvertVertex[i][index] = m_vecVertex[i][index];

			Engine::MyTransformCoord(&m_vecConvertVertex[i][index].vPos,
				&m_vecConvertVertex[i][index].vPos,
				&m_matBoxWorld[i]);
	
			Engine::MyTransformCoord(&m_vecConvertVertex[i][index].vPos, 
				&m_vecConvertVertex[i][index].vPos, 
				&matPrint);
		}
	}	
}
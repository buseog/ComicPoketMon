#include "StdAfx.h"
#include "Gather.h"


#include "Export_Function.h"
#include "TimeMgr.h"
#include "CameraObserver.h"
#include "BoundBox.h"

CGather::CGather(LPDIRECT3DDEVICE9 pDevice)
: CParticleSystem(pDevice)
, m_pTimeMgr(Engine::Get_TimeMgr())
, m_pInfoSubject(Engine::Get_InfoSubject())
, m_pCameraObserver(NULL)
{

}

CGather::~CGather(void)
{
	CParticleSystem::Release();

	if (m_pInfoSubject != NULL)
		m_pInfoSubject->UnSubscribe(m_pCameraObserver);

	if (m_pCameraObserver)
		Engine::Safe_Delete(m_pCameraObserver);
}

HRESULT CGather::Initialize(const wstring& wstrKey, D3DXVECTOR3 vOrigin, D3DXVECTOR3 vDIr, int iCount)
{
	m_pCameraObserver = CCameraObserver::Create();
	m_pInfoSubject->Subscribe(m_pCameraObserver);

	m_vOrigin = vOrigin;
	m_vOrigin.y += 10.f;
	m_vDir = vDIr;
	m_vOrigin += m_vDir * 4.f;

	for (int i = 0; i < iCount; ++i)
	{
		AddParticle();
	}

	m_fSize = 1.f;
	m_dwVBSize = 2048;
	m_dwVBOffset = 0;
	m_dwVBBatchSize = 512;

	Engine::CParticleSystem::Initialize(wstrKey);

	return S_OK;
}

void CGather::ResetParticle(Engine::ATTRIBUTE* pAttribute)
{
	pAttribute->bAlive = true;

	Engine::GetRandomVector(&pAttribute->vPos, &D3DXVECTOR3(-5.f, -5.f, -5.f), &D3DXVECTOR3(5.f, 5.f, 5.f));
	pAttribute->vPos += m_vOrigin;

	D3DXVECTOR3 vTemp = m_vOrigin - pAttribute->vPos;
	Engine::MyNormalize(&vTemp, &vTemp);

	pAttribute->vVelocity = vTemp * 15.f;

	pAttribute->vColor = D3DXCOLOR(255.f, 228.f, 0.f, 255.f);


	pAttribute->fAge = 0.f;
	pAttribute->fLifeTime = 0.7f;
}

void CGather::Update(void)
{
	float fTime = m_pTimeMgr->GetTime();

	if (isDead())
		m_bDestroy = true;

	list<Engine::ATTRIBUTE*>::iterator iter = m_ParticleList.begin();
	list<Engine::ATTRIBUTE*>::iterator iter_end = m_ParticleList.end();

	for ( ; iter != iter_end; ++iter)
	{
		if ((*iter)->bAlive)
		{
			(*iter)->fAge += fTime;

			if ((*iter)->vPos.x > m_vOrigin.x - 1.f && (*iter)->vPos.x < m_vOrigin.x + 1.f && 
				(*iter)->vPos.y > m_vOrigin.y - 1.f && (*iter)->vPos.y < m_vOrigin.y + 1.f &&
				(*iter)->vPos.z > m_vOrigin.z - 1.f && (*iter)->vPos.z < m_vOrigin.z + 1.f)
			{
				
			}
			else
			{
				(*iter)->vPos += (*iter)->vVelocity * fTime;
			}

			if ((*iter)->fAge > (*iter)->fLifeTime)
			{
				(*iter)->bAlive = false;
			}
		}
	}
}

void CGather::Render(void)
{
	if (m_ParticleList.empty() == false)
	{
		// 렌더 상태를 지정

		preRender();

		m_pDevice->SetTexture(0, m_pTexture);
		m_pDevice->SetFVF(Engine::PARTICLEFVF);
		m_pDevice->SetStreamSource(0, m_pVB, 0, sizeof(Engine::PARTICLE));


		// 버텍스 버퍼를 벗어날 경우 처음부터 재시작

		if (m_dwVBOffset >= m_dwVBSize)
			m_dwVBOffset = 0;

		Engine::PARTICLE* pParticle = NULL;

		m_pVB->Lock(m_dwVBOffset * sizeof(Engine::PARTICLE), 
			m_dwVBBatchSize * sizeof(Engine::PARTICLE),
			(void**)&pParticle,
			m_dwVBOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD);

		DWORD numParticleInBatch = 0;

		// 모든 파티클이 렌더링될 때까지

		list<Engine::ATTRIBUTE*>::iterator iter = m_ParticleList.begin();
		list<Engine::ATTRIBUTE*>::iterator iter_end = m_ParticleList.end();

		D3DXMATRIX matIdentity, matView, matProj;
		Engine::MyIdentity(&matIdentity);
		matView = *m_pCameraObserver->GetView();
		matProj = *m_pCameraObserver->GetProj();
		matIdentity = matView * matProj;

		for (iter ; iter != iter_end; ++iter)
		{
			if ((*iter)->bAlive)
			{
				// 한 단계의 생존한 파티클을 다음 버텍스 버퍼로 복사한다.

				Engine::MyTransformCoord(&pParticle->vPos, &(*iter)->vPos, &matIdentity);
				pParticle->vColor = (D3DCOLOR)(*iter)->vColor;

				++pParticle;
				++numParticleInBatch;

				// 현재의 단계가 전부 채워져 있는지
				if (numParticleInBatch == m_dwVBBatchSize)
				{	
					// 버텍스 버퍼로 복사된 마지막 단계의 파티클을 그림

					m_pVB->Unlock();

					m_pDevice->DrawPrimitive(D3DPT_POINTLIST, m_dwVBOffset, m_dwVBBatchSize);

					// 단계가 그려지는 동안 다음 6단계를 파티클로 채움

					// 다음 단계의 처음 오프셋으로 이동함
					m_dwVBOffset += m_dwVBBatchSize;

					// 버텍스 버퍼의 경계를 넘는 메모리로 오프셋을 설정하지않음. 경계를 넘을 경우에 처음부터 시작함
					if (m_dwVBOffset >= m_dwVBSize)
						m_dwVBOffset = 0;

					m_pVB->Lock(m_dwVBOffset * sizeof(Engine::PARTICLE),
						m_dwVBBatchSize * sizeof(Engine::PARTICLE),
						(void**)&pParticle,
						m_dwVBOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD);

					numParticleInBatch = 0;
				}
			}
		}

		m_pVB->Unlock();

		// numParticlesInBatch == m_dwVBBatch 가 만족되지 않았을 경우 마지막 단계의 렌더링이 되지 않을수도 있다.
		// 일부만 채워진 단계는 이곳에서 렌더링 시킴

		if (numParticleInBatch)
		{
			m_pDevice->DrawPrimitive(D3DPT_POINTLIST, m_dwVBOffset, numParticleInBatch);
		}

		// 다음블록
		m_dwVBOffset += m_dwVBBatchSize;

		postRender();
	}
}

void CGather::preRender(void)
{
	// 렌더링에 앞서 지정해야될 렌더링 상태를 세팅함.
	// 시스템마다 다를수 있어서 가상화시킴.

	m_pDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, TRUE);
	m_pDevice->SetRenderState(D3DRS_POINTSCALEENABLE, TRUE);
	m_pDevice->SetRenderState(D3DRS_POINTSIZE, FToD(m_fSize));
	m_pDevice->SetRenderState(D3DRS_POINTSIZE_MIN, FToD(5.f));
	m_pDevice->SetRenderState(D3DRS_POINTSIZE_MAX, FToD(10.f));

	// 거리에 따른 파티클의 크기를 정해줌

	m_pDevice->SetRenderState(D3DRS_POINTSCALE_A, FToD(0.f));
	m_pDevice->SetRenderState(D3DRS_POINTSCALE_B, FToD(0.f));
	m_pDevice->SetRenderState(D3DRS_POINTSCALE_C, FToD(1.f));

	// 텍스처의 알파를 이용함.

	m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);

	// 알파 블렌드를 활성화해서 투명하게 했음. 이로인해 동그란 모양을 만들 수 있다.

	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	

	m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	m_pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00000088);
	m_pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
}

void CGather::postRender(void)
{
	m_pDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, FALSE);
	m_pDevice->SetRenderState(D3DRS_POINTSCALEENABLE, FALSE);
	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

CGather* CGather::Create(LPDIRECT3DDEVICE9 pDevice, const wstring& wstrKey, D3DXVECTOR3 vOrigin, D3DXVECTOR3 vDIr, int iCount)
{
	CGather* pGather = new CGather(pDevice);

	if (FAILED(pGather->Initialize(wstrKey, vOrigin, vDIr, iCount)))
		Engine::Safe_Delete(pGather);

	return pGather;
}

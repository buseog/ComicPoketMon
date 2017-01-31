#include "StdAfx.h"
#include "Snow.h"

#include "Export_Function.h"
#include "TimeMgr.h"
#include "CameraObserver.h"

CSnow::CSnow(LPDIRECT3DDEVICE9 pDevice)
: CParticleSystem(pDevice)
, m_pTimeMgr(Engine::Get_TimeMgr())
, m_pInfoSubject(Engine::Get_InfoSubject())
, m_pCameraObserver(NULL)
{
}

CSnow::~CSnow(void)
{
	CParticleSystem::Release();

	if (m_pCameraObserver)
		Engine::Safe_Delete(m_pCameraObserver);
}

HRESULT CSnow::Initialize(const wstring& wstrKey, Engine::CBoundBox* pBox, int iCount)
{
	m_pCameraObserver = CCameraObserver::Create();
	m_pInfoSubject->Subscribe(m_pCameraObserver);

	for (int i = 0; i < iCount; ++i)
	{
		AddParticle();
	}

	m_pBoundingBox = pBox;

	m_fSize = 1.f;
	m_dwVBSize = 2048;
	m_dwVBOffset = 0;
	m_dwVBBatchSize = 512;

	Engine::CParticleSystem::Initialize(wstrKey);

	return S_OK;
}

void CSnow::ResetParticle(Engine::ATTRIBUTE* pAttribute)
{
	pAttribute->bAlive = true;

	D3DXVECTOR3 vMin = D3DXVECTOR3(0.f, 0.f, 0.f);
	D3DXVECTOR3 vMax = D3DXVECTOR3(300.f, 10.f, 300.f);

	// 눈송이의 위치 지정을 위해 임의의 x, z좌표를 넣어줌
	Engine::GetRandomVector(&pAttribute->vPos, &vMin, &vMax);

	// 높이값 지정
	pAttribute->vPos.y = Engine::GetRandomFloat(50.f, 100.f);

	// 눈송이의 방향
	pAttribute->vVelocity.x = (Engine::GetRandomFloat(2.f, 15.f) * -2.f) + (Engine::GetRandomFloat(2.f, 15.f) * 2.f);
	pAttribute->vVelocity.y = Engine::GetRandomFloat(5.f, 15.f) * -2.f;
	pAttribute->vVelocity.z = 0.f;

	// 눈송이 색상
	pAttribute->vColor = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
}

void CSnow::Update(void)
{
	float fTime = m_pTimeMgr->GetTime();

	list<Engine::ATTRIBUTE*>::iterator iter = m_ParticleList.begin();
	list<Engine::ATTRIBUTE*>::iterator iter_end = m_ParticleList.end();

	for ( ; iter != iter_end; ++iter)
	{
		(*iter)->vPos += (*iter)->vVelocity * fTime;

		if (m_pBoundingBox->Inside(&(*iter)->vPos) == false)
		{
			ResetParticle(*iter);
		}
	}
}

void CSnow::Render(void)
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

void CSnow::preRender(void)
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
	m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	/*m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	m_pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00000088);
	m_pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);*/
}

void CSnow::postRender(void)
{
	m_pDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, FALSE);
	m_pDevice->SetRenderState(D3DRS_POINTSCALEENABLE, FALSE);
	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}

CSnow* CSnow::Create(LPDIRECT3DDEVICE9 pDevice, const wstring& wstrKey, Engine::CBoundBox* pBox, int iCount)
{
	CSnow* pSnow = new CSnow(pDevice);

	if (FAILED(pSnow->Initialize(wstrKey, pBox, iCount)))
		Engine::Safe_Delete(pSnow);

	return pSnow;
}

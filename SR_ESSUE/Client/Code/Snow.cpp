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

	// �������� ��ġ ������ ���� ������ x, z��ǥ�� �־���
	Engine::GetRandomVector(&pAttribute->vPos, &vMin, &vMax);

	// ���̰� ����
	pAttribute->vPos.y = Engine::GetRandomFloat(50.f, 100.f);

	// �������� ����
	pAttribute->vVelocity.x = (Engine::GetRandomFloat(2.f, 15.f) * -2.f) + (Engine::GetRandomFloat(2.f, 15.f) * 2.f);
	pAttribute->vVelocity.y = Engine::GetRandomFloat(5.f, 15.f) * -2.f;
	pAttribute->vVelocity.z = 0.f;

	// ������ ����
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
		// ���� ���¸� ����

		preRender();

		m_pDevice->SetTexture(0, m_pTexture);
		m_pDevice->SetFVF(Engine::PARTICLEFVF);
		m_pDevice->SetStreamSource(0, m_pVB, 0, sizeof(Engine::PARTICLE));


		// ���ؽ� ���۸� ��� ��� ó������ �����

		if (m_dwVBOffset >= m_dwVBSize)
			m_dwVBOffset = 0;

		Engine::PARTICLE* pParticle = NULL;

		m_pVB->Lock(m_dwVBOffset * sizeof(Engine::PARTICLE), 
			m_dwVBBatchSize * sizeof(Engine::PARTICLE),
			(void**)&pParticle,
			m_dwVBOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD);

		DWORD numParticleInBatch = 0;

		// ��� ��ƼŬ�� �������� ������

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
				// �� �ܰ��� ������ ��ƼŬ�� ���� ���ؽ� ���۷� �����Ѵ�.

				Engine::MyTransformCoord(&pParticle->vPos, &(*iter)->vPos, &matIdentity);
				pParticle->vColor = (D3DCOLOR)(*iter)->vColor;

				++pParticle;
				++numParticleInBatch;

				// ������ �ܰ谡 ���� ä���� �ִ���
				if (numParticleInBatch == m_dwVBBatchSize)
				{	
					// ���ؽ� ���۷� ����� ������ �ܰ��� ��ƼŬ�� �׸�

					m_pVB->Unlock();

					m_pDevice->DrawPrimitive(D3DPT_POINTLIST, m_dwVBOffset, m_dwVBBatchSize);

					// �ܰ谡 �׷����� ���� ���� 6�ܰ踦 ��ƼŬ�� ä��

					// ���� �ܰ��� ó�� ���������� �̵���
					m_dwVBOffset += m_dwVBBatchSize;

					// ���ؽ� ������ ��踦 �Ѵ� �޸𸮷� �������� ������������. ��踦 ���� ��쿡 ó������ ������
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

		// numParticlesInBatch == m_dwVBBatch �� �������� �ʾ��� ��� ������ �ܰ��� �������� ���� �������� �ִ�.
		// �Ϻθ� ä���� �ܰ�� �̰����� ������ ��Ŵ

		if (numParticleInBatch)
		{
			m_pDevice->DrawPrimitive(D3DPT_POINTLIST, m_dwVBOffset, numParticleInBatch);
		}

		// �������
		m_dwVBOffset += m_dwVBBatchSize;

		postRender();
	}
}

void CSnow::preRender(void)
{
	// �������� �ռ� �����ؾߵ� ������ ���¸� ������.
	// �ý��۸��� �ٸ��� �־ ����ȭ��Ŵ.

	m_pDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, TRUE);
	m_pDevice->SetRenderState(D3DRS_POINTSCALEENABLE, TRUE);
	m_pDevice->SetRenderState(D3DRS_POINTSIZE, FToD(m_fSize));
	m_pDevice->SetRenderState(D3DRS_POINTSIZE_MIN, FToD(5.f));
	m_pDevice->SetRenderState(D3DRS_POINTSIZE_MAX, FToD(10.f));

	// �Ÿ��� ���� ��ƼŬ�� ũ�⸦ ������

	m_pDevice->SetRenderState(D3DRS_POINTSCALE_A, FToD(0.f));
	m_pDevice->SetRenderState(D3DRS_POINTSCALE_B, FToD(0.f));
	m_pDevice->SetRenderState(D3DRS_POINTSCALE_C, FToD(1.f));

	// �ؽ�ó�� ���ĸ� �̿���.

	m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);

	// ���� ���带 Ȱ��ȭ�ؼ� �����ϰ� ����. �̷����� ���׶� ����� ���� �� �ִ�.

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

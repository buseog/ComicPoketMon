#include "StdAfx.h"
#include "Hit.h"

#include "Export_Function.h"
#include "TimeMgr.h"
#include "CameraObserver.h"

CHit::CHit( LPDIRECT3DDEVICE9 pDevice )
: CParticleSystem(pDevice)
, m_pTimeMgr(Engine::Get_TimeMgr())
, m_pInfoSubject(Engine::Get_InfoSubject())
, m_pCameraObserver(NULL)
{

}

CHit::~CHit( void )
{
	CParticleSystem::Release();

	if (m_pInfoSubject != NULL)
		m_pInfoSubject->UnSubscribe(m_pCameraObserver);

	if (m_pCameraObserver)
		Engine::Safe_Delete(m_pCameraObserver);
}

HRESULT CHit::Initialize( const wstring& wstrKey, D3DXVECTOR3 vOrigin, D3DXVECTOR3 vDir)
{
	m_pCameraObserver = CCameraObserver::Create();
	m_pInfoSubject->Subscribe(m_pCameraObserver);

	m_vOrigin = vOrigin;
	m_vOrigin.y += 5.f;
	m_vDir = vDir;

	int iRan = rand() % 50;

	for (int i = 0; i < iRan; ++i)
	{
		AddParticle();
	}

	m_fSize = Engine::GetRandomFloat(15.f, 20.f);
	m_dwVBSize = 2048;
	m_dwVBOffset = 0;
	m_dwVBBatchSize = 512;

	Engine::CParticleSystem::Initialize(wstrKey);

	return S_OK;
}

void CHit::ResetParticle( Engine::ATTRIBUTE* pAttribute )
{
	pAttribute->bAlive = true;

	pAttribute->vPos = m_vOrigin + m_vDir * 2.5f;

	D3DXVECTOR3 vTemp = D3DXVECTOR3(1.f, 1.f, 1.f);

	Engine::GetRandomVector(&pAttribute->vVelocity, &-vTemp, &vTemp);
	
	pAttribute->vVelocity += m_vDir;
	pAttribute->vVelocity *= 3.f;

	pAttribute->vAcceleration = D3DXVECTOR3(0.f, 1.f, 0.f);

	// �� ����
	pAttribute->vColor = D3DXCOLOR(1.f, 0.f, 0.f, 255.f);

	pAttribute->fAge = 0.f;
	pAttribute->fLifeTime = 1.f;
}

void CHit::Update( void )
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
			(*iter)->vPos += (*iter)->vVelocity * fTime - (*iter)->vAcceleration * fTime;
			(*iter)->fAge += fTime;

			if ((*iter)->fAge > (*iter)->fLifeTime)
			{
				(*iter)->bAlive = false;
			}
		}
	}
}

void CHit::Render( void )
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

void CHit::preRender( void )
{
	// �������� �ռ� �����ؾߵ� ������ ���¸� ������.
	// �ý��۸��� �ٸ��� �־ ����ȭ��Ŵ.

	m_pDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, TRUE);
	m_pDevice->SetRenderState(D3DRS_POINTSCALEENABLE, TRUE);
	m_pDevice->SetRenderState(D3DRS_POINTSIZE, FToD(m_fSize));
	m_pDevice->SetRenderState(D3DRS_POINTSIZE_MIN, FToD(15.f));
	m_pDevice->SetRenderState(D3DRS_POINTSIZE_MAX, FToD(20.f));

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

	m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	m_pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00000088);
	m_pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
}

void CHit::postRender( void )
{
	m_pDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, FALSE);
	m_pDevice->SetRenderState(D3DRS_POINTSCALEENABLE, FALSE);
	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

CHit* CHit::Create(LPDIRECT3DDEVICE9 pDevice, const wstring& wstrKey, D3DXVECTOR3 vOrigin, D3DXVECTOR3 vDir)
{
	CHit* pHit = new CHit(pDevice);

	if (FAILED(pHit->Initialize(wstrKey, vOrigin, vDir)))
		Engine::Safe_Delete(pHit);

	return pHit;
}

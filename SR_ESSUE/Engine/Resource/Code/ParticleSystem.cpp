#include "ParticleSystem.h"

Engine::CParticleSystem::CParticleSystem( LPDIRECT3DDEVICE9 pDevice )
: CGameObject(pDevice)
, m_pVB(NULL)
, m_pTexture(NULL)
, m_pBoundingBox(NULL)
, m_vOrigin(0.f, 0.f, 0.f)
, m_fRate(0.f)
, m_fSize(0.f)
, m_iMaxCount(0)
, m_dwVBSize(0)
, m_dwVBOffset(0)
, m_dwVBBatchSize(0)
{

}

Engine::CParticleSystem::~CParticleSystem(void)
{
	Release();
}

HRESULT Engine::CParticleSystem::Initialize( const wstring& wstrFileName )
{
	// ���ؽ��� �����ϰ� �ؽ�ó�� ����µ��� �ʱ�ȭ �۾�

	HRESULT	hr = NULL;

	hr = m_pDevice->CreateVertexBuffer(m_dwVBSize * sizeof(Engine::PARTICLE),
										D3DUSAGE_DYNAMIC | D3DUSAGE_POINTS | D3DUSAGE_WRITEONLY, 
										Engine::PARTICLEFVF, 
										D3DPOOL_DEFAULT, &m_pVB, NULL);

	hr = D3DXCreateTextureFromFile(m_pDevice, wstrFileName.c_str(), (LPDIRECT3DTEXTURE9*)&m_pTexture);

	return S_OK;

}

void Engine::CParticleSystem::Reset( void )
{
	// ��� ��ƼŬ �ʱ�ȭ

	list<Engine::ATTRIBUTE*>::iterator iter = m_ParticleList.begin();
	list<Engine::ATTRIBUTE*>::iterator iter_end = m_ParticleList.end();

	for (iter ; iter != iter_end; ++iter)
	{
		ResetParticle(*iter);
	}
}

void Engine::CParticleSystem::AddParticle( void )
{
	Engine::ATTRIBUTE* pAttribute = new Engine::ATTRIBUTE;

	ResetParticle(pAttribute);

	m_ParticleList.push_back(pAttribute);
}

void Engine::CParticleSystem::preRender( void )
{
	// �������� �ռ� �����ؾߵ� ������ ���¸� ������.
	// �ý��۸��� �ٸ��� �־ ����ȭ��Ŵ.

	m_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
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
}


void Engine::CParticleSystem::Render( void )
{
	if (m_ParticleList.empty() == false)
	{
		// ���� ���¸� ����

		preRender();

		m_pDevice->SetTexture(0, m_pTexture);
		m_pDevice->SetStreamSource(0, m_pVB, 0, sizeof(Engine::PARTICLE));
		m_pDevice->SetFVF(Engine::PARTICLEFVF);
		

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

		for (iter ; iter != iter_end; ++iter)
		{
			if ((*iter)->bAlive == true)
			{
				// �� �ܰ��� ������ ��ƼŬ�� ���� ���ؽ� ���۷� �����Ѵ�.

				pParticle->vPos = (*iter)->vPos;
				pParticle->vColor = (D3DCOLOR)(*iter)->vColor;
				++pParticle;
				++numParticleInBatch;

				// ������ �ܰ谡 ���� ä���� �ִ���
				if (numParticleInBatch == m_dwVBBatchSize)
				{	
					// ���ؽ� ���۷� ����� ������ �ܰ��� ��ƼŬ�� �׸�

					m_pVB->Unlock();

					m_pDevice->DrawPrimitive(D3DPT_POINTLIST, m_dwVBOffset, m_dwVBBatchSize);
					
					// �ܰ谡 �׷����� ���� ���� �ܰ踦 ��ƼŬ�� ä��

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

void Engine::CParticleSystem::postRender( void )
{
	// ��ƼŬ �ý����� ������ ������ �����Ѵ�. ����ȭ��Ŵ.

	//m_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_pDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, FALSE);
	m_pDevice->SetRenderState(D3DRS_POINTSCALEENABLE, FALSE);
	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}

bool Engine::CParticleSystem::isEmpty( void )
{
	return m_ParticleList.empty();
}

bool Engine::CParticleSystem::isDead( void )
{
	list<Engine::ATTRIBUTE*>::iterator iter = m_ParticleList.begin();
	list<Engine::ATTRIBUTE*>::iterator iter_end = m_ParticleList.end();

	for (iter ; iter != iter_end; ++iter)
	{
		if ((*iter)->bAlive)
			return false;
	}

	return true;
}

void Engine::CParticleSystem::RemoveDeadParticle( void )
{
	// ���� ��ƼŬ���� ����Ʈ���� ������

	list<Engine::ATTRIBUTE*>::iterator iter = m_ParticleList.begin();
	list<Engine::ATTRIBUTE*>::iterator iter_end = m_ParticleList.end();

	for (iter ; iter != iter_end;)
	{
		if ((*iter)->bAlive == false)
		{
			m_ParticleList.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

DWORD Engine::CParticleSystem::FToD(float f)
{
	return *((DWORD*)&f);
}

void Engine::CParticleSystem::Release(void)
{
	list<Engine::ATTRIBUTE*>::iterator iter = m_ParticleList.begin();
	list<Engine::ATTRIBUTE*>::iterator iter_end = m_ParticleList.end();

	for (iter ; iter != iter_end; ++iter)
	{
		Engine::Safe_Delete(*iter);
	}
	m_ParticleList.clear();

	if (m_pBoundingBox)
		Engine::Safe_Delete(m_pBoundingBox);
}

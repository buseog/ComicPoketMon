/*!
 * \file PaticleSystem.h
 * \date 2017/01/20 2:45
 *
 * \author ESSUE
 * Contact: user@company.com
 *
 * \brief �̺�Ʈ & Ư��ȿ������ ����� Ŭ����
 *
 * TODO: long description
 *
 * \note
*/

#ifndef ParticleSystem_h__
#define ParticleSystem_h__

#include "GameObject.h"
#include "Engine_Include.h"
#include "BoundBox.h"

BEGIN(Engine)

class ENGINE_DLL CParticleSystem
	:public Engine::CGameObject
{
protected:
	IDirect3DBaseTexture9*		m_pTexture;
	IDirect3DVertexBuffer9*		m_pVB;
	Engine::CBoundBox*			m_pBoundingBox;	// ��ƼŬ�� ���Ǹ� �����ϴ� �� �̿��. ��迵���� �̻��ڷ� �����ϸ� ������ ��� ��ƼŬ���� �����ȴ�.
	D3DXVECTOR3					m_vOrigin;		// ��ƼŬ�� ���۵Ǵ����

	float						m_fRate;		// ��ƼŬ�� �߰��Ǵ� ����. �ʴ� ��ƼŬ��
	float						m_fSize;		// ��ƼŬ�� ũ��
	int							m_iMaxCount;	// ������ �ð����� ������ �ִ� ��ƼŬ�� ��. �ı��Ǵ� �ӵ����� ��������� �ӵ��� �������� ��ġ�� ������ ������.
	list<Engine::ATTRIBUTE*>	m_ParticleList;	// ��ƼŬ���� ������ ����Ʈ. 

	DWORD						m_dwVBSize;	// ���ؽ� ���۰� ������ �� �ִ� ��ƼŬ�� ��. �̰��� ��ƼŬ �ý��� ���� ��ƼŬ ���ʹ� ������
	DWORD						m_dwVBOffset;	// ���ؽ� ���ۿ��� ������ ��ƼŬ �� ���� �ܰ���� ������(��ƼŬ����)
	DWORD						m_dwVBBatchSize;	// �ϳ��� �ܰ迡 ���ǵ� ��ƼŬ ��

protected:
	void			Release(void);
	virtual void	RemoveDeadParticle(void);

public:
	virtual HRESULT	Initialize(const wstring& wstrFileName);
	virtual void	Reset(void);
	virtual void	ResetParticle(Engine::ATTRIBUTE* pAttribute) PURE;	// �ý��۸��� ����°� �޶� ���������Լ��θ���
	virtual void	AddParticle(void);

	virtual void	Update(void) PURE;	// �ý��۸��� ������ �޶� ���������Լ��� ����.
	virtual void	preRender(void);
	virtual void	Render(void);
	virtual void	postRender(void);

	bool isEmpty(void);
	bool isDead(void);
	DWORD FToD(float f);


protected:
	explicit CParticleSystem(LPDIRECT3DDEVICE9 pDevice);

public:
	virtual ~CParticleSystem(void);
};

END
#endif // ParticleSystem_h__
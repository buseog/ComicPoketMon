/*!
 * \file Gauge.h
 * \date 2017/01/16 22:56
 *
 * \author ESSUE
 * Contact: user@company.com
 *
 * \brief ���� ü�°� ������ ������ ������
 *
 * TODO: long description
 *
 * \note �����ҋ� Ű���� �޾Ƽ� �÷��׷� ����� ���̹Ƿ� ��������� wstring���� ���ϰ�����.
*/

#ifndef Gauge_h__
#define Gauge_h__

#include "UI.h"

namespace Engine
{
	class CResourceMgr;
	class CTexture;
	class CVIBuffer;
	class CStatSubject;
}

class CUIObserver;
class CGauge
	:public Engine::CUI
{
private:
	Engine::CResourceMgr*		m_pResourceMgr;
	Engine::CVIBuffer*			m_pBuffer;
	Engine::CTexture*			m_pTexture;

	Engine::CStatSubject*		m_pStatSubject;
	CUIObserver*				m_pUIObserver;

	Engine::VTXTEX*				m_pVertex;
	Engine::VTXTEX*				m_pConvertVertex;
	DWORD						m_dwVtxCnt;

	wstring						m_wstrkey;

private:
	HRESULT			Initialize(const wstring& wstrKey);
	void			SetTransform(void);

public:
	void			Update(void);
	void			Render(void);
	void			Release(void);
	HRESULT			AddComponent(void);

	void			RenewalSize(void);

public:
	static	CGauge*	Create(LPDIRECT3DDEVICE9 pDevice, const wstring& wstrKey);

private:
	explicit CGauge(LPDIRECT3DDEVICE9 pDevice);

public:
	virtual ~CGauge(void);
};

#endif // Gauge_h__
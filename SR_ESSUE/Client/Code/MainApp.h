#ifndef MainApp_h__
#define MainApp_h__

#include "Include.h"

namespace Engine
{
	class CGraphicDev;
	class CManagement;
	class CTimeMgr;
	class CKeyMgr;
}

class CMainApp
{
private:
	Engine::CGraphicDev*			m_pGraphicDev;
	Engine::CManagement*			m_pManagement;
	LPDIRECT3DDEVICE9				m_pDevice;
	Engine::CTimeMgr*				m_pTimeMgr;

private:
	HRESULT	Initialize(void);
	void	Release(void);

public:
	void	Update(void);
	void	Render(void);

public:
	static CMainApp*	Create(void);

private:
	CMainApp(void);
public:
	~CMainApp(void);
};


#endif // MainApp_h__

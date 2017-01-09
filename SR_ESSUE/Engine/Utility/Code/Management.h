#ifndef Management_h__
#define Management_h__

#include "Engine_Include.h"
#include "Renderer.h"

BEGIN(Engine)

class CRenderer;
class CScene;
class ENGINE_DLL CManagement
{
	DECLARE_SINGLETON(CManagement)

private:
	LPDIRECT3DDEVICE9		m_pDevice;
	CRenderer*				m_pRenderer;
	CScene*					m_pScene;

private:
	void	Release(void);

public:
	HRESULT	InitManagement(LPDIRECT3DDEVICE9	_pDevice);
	void	Update(void);
	void	Render(void);

public:
	template <typename T>
	HRESULT SceneChange(T& Functor);

private:
	CManagement();
	~CManagement();
};

template <typename T>
HRESULT Engine::CManagement::SceneChange( T& Functor )
{
	if(NULL != m_pScene)
		Engine::Safe_Delete(m_pScene);

	FAILED_CHECK(Functor(&m_pScene, m_pDevice));

	m_pRenderer->SetScene(m_pScene);

	return S_OK;
}

END
#endif // Management_h__

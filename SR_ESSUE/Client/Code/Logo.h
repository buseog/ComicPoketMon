#ifndef Logo_h__
#define Logo_h__

#include "Scene.h"

namespace Engine
{
	class CManagement;
}

class CLogo
	: public Engine::CScene
{
private:
	Engine::CManagement*	m_pManagement;


public:
	virtual HRESULT InitScene(void);
	virtual void Update(void);
	virtual void Render(void);

public:
	static CLogo*	Create(LPDIRECT3DDEVICE9 pDevice);

private:
	explicit CLogo(LPDIRECT3DDEVICE9 pDevice);
public:
	virtual ~CLogo(void);

};


#endif // Logo_h__

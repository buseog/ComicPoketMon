#ifndef Stage_h__
#define Stage_h__

#include "Scene.h"

namespace Engine
{
	class CManagement;
	class CRcCol;
}

class CStage
	: public Engine::CScene
{
private:
	Engine::CManagement*		m_pManagement;
	Engine::CRcCol*				m_pRcCol;

public:
	virtual HRESULT InitScene(void);
	virtual void Update(void);
	virtual void Render(void);

public:
	static CStage*	Create(LPDIRECT3DDEVICE9 pDevice);

private:
	explicit CStage(LPDIRECT3DDEVICE9 pDevice);
public:
	~CStage(void);

};
#endif // Stage_h__

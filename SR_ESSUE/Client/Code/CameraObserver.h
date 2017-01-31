
#ifndef CameraObserver_h__
#define CameraObserver_h__

#include "Observer.h"

namespace Engine
{
	class CInfoSubject;
}

class CCameraObserver : public Engine::CObserver
{
private:
	CCameraObserver(void);
public:
	virtual ~CCameraObserver(void);

public:
	D3DXMATRIX*	GetView(void);
	D3DXMATRIX*	GetProj(void);
	static CCameraObserver*	Create(void);

public:
	virtual void Update(int iMessage, void* pData);

private:
	Engine::CInfoSubject*		m_pInfoSubject;

	D3DXMATRIX		m_matView;
	D3DXMATRIX		m_matProj;

};

#endif // CameraObserver_h__
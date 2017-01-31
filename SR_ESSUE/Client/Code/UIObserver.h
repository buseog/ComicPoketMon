/*!
 * \file UIObserver.h
 * \date 2017/01/16 1:00
 *
 * \author ESSUE
 * Contact: user@company.com
 *
 * \brief UI에서 플레이어 정보를 가져오기 위한 옵저버
 *
 * TODO: long description
 *
 * \note 플레이어 & 몬스터의 체력 / 월드매트릭스 정보등을 가져올 예정이다
*/

#ifndef UIObserver_h__
#define UIObserver_h__

#include "Observer.h"

namespace Engine
{
	class CStatSubject;
	class CStatus;
}

class CUIObserver
	:public Engine::CObserver
{
private:
	Engine::CStatSubject*			m_pStatusSubject;
	Engine::CStatus*				m_pStatus;

public:
	Engine::CStatus* GetStatus(void);

public:
	virtual void Update(int iMessage, void* pData);

public:
	static CUIObserver*	Create(void);

private:
	CUIObserver(void);
public:
	~CUIObserver(void);
};

#endif // UIObserver_h__
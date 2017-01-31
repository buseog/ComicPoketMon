/*!
 * \file UIObserver.h
 * \date 2017/01/16 1:00
 *
 * \author ESSUE
 * Contact: user@company.com
 *
 * \brief UI���� �÷��̾� ������ �������� ���� ������
 *
 * TODO: long description
 *
 * \note �÷��̾� & ������ ü�� / �����Ʈ���� �������� ������ �����̴�
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
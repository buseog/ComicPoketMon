/*!
 * \file Subject.h
 * \date 2017/01/08 19:43
 *
 * \author Administrator
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/

#ifndef Subject_h__
#define Subject_h__

#include "Engine_Include.h"

BEGIN(Engine)

class CObserver;
class ENGINE_DLL CSubject
{
protected:
	typedef list<CObserver*>		OBSERVERLIST;
	OBSERVERLIST					m_ObserverList;

private:
	void Release(void);

public:
	virtual void Subscribe(CObserver* pObserver);
	virtual void UnSubscribe(CObserver* pObserver);
	virtual void Notify(int iMessage, void* pData);

protected:
	CSubject(void);
	virtual ~CSubject(void);
};

END
#endif // Subject_h__
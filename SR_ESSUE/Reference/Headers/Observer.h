/*!
 * \file Observer.h
 * \date 2017/01/08 19:41
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

#ifndef Observer_h__
#define Observer_h__

#include "Engine_Include.h"

BEGIN(Engine)

class ENGINE_DLL CObserver
{
public:
	virtual void Update(int iMessage) PURE;

protected:
	CObserver(void);

public:
	virtual ~CObserver(void);
};

END
#endif // Observer_h__
/*!
 * \file Component.h
 * \date 2017/01/07 1:38
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

#ifndef Component_h__
#define Component_h__

#include "Engine_Include.h"

BEGIN(Engine)

class ENGINE_DLL CComponent abstract
{
public:
	virtual void Update(void) {};

protected:
	CComponent(void);

public:
	virtual ~CComponent(void);
};

END
#endif // Component_h__
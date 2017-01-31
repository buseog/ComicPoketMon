/*!
 * \file InfoSubject.h
 * \date 2017/01/10 6:57
 *
 * \author ESSUE
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/


#ifndef InfoSubject_h__
#define InfoSubject_h__

#include "Subject.h"

BEGIN(Engine)

typedef	vector<void*>			VECDATA;
typedef map<int, VECDATA>		MAPDATALIST;

class ENGINE_DLL CInfoSubject 
	: public CSubject
{
	DECLARE_SINGLETON(CInfoSubject)

private:
	MAPDATALIST			m_MapDataList;

public:
	VECDATA*	GetDataList(int iMessage);

public:
	void	AddData(int iMessage, void* pData);
	void	RemoveData(int iMessage, void* pData);

private:
	void	Release(void);

private:
	CInfoSubject(void);
	virtual ~CInfoSubject(void);
};


END
#endif // InfoSubject_h__
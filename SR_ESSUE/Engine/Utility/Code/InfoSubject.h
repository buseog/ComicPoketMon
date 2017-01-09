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

typedef	list<void*>				DATALIST;
typedef map<int, DATALIST>		MAPDATALIST;

class ENGINE_DLL CInfoSubject : public CSubject
{
	DECLARE_SINGLETON(CInfoSubject)

private:
	CInfoSubject(void);
	virtual ~CInfoSubject(void);

public:
	DATALIST*	GetDataList(int iMessage);

public:
	void	AddData(int iMessage, void* pData);
	void	RemoveData(int iMessage, void* pData);

private:
	void	Release(void);

private:
	MAPDATALIST			m_MapDataList;

};


END
#endif // InfoSubject_h__
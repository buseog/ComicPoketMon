/*!
 * \file StatSubject.h
 * \date 2017/01/16 23:08
 *
 * \author ESSUE
 * Contact: user@company.com
 *
 * \brief 스텟값을 받을 싱글톤 클래스
 *
 * TODO: long description
 *
 * \note 싱글톤으로 플레이어의 스텟값을 저장하고 있을것임.
*/

#ifndef StatSubject_h__
#define StatSubject_h__

#include "Subject.h"

BEGIN(Engine)

typedef	vector<void*>			VECDATA;
typedef map<int, VECDATA>		MAPDATALIST;

class ENGINE_DLL CStatSubject
	:public CSubject
{
	DECLARE_SINGLETON(CStatSubject)

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
	CStatSubject(void);
	virtual ~CStatSubject(void);

};

END
#endif // StatSubject_h__
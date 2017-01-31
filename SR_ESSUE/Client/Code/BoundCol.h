/*!
 * \file BoundCol.h
 * \date 2017/01/15 19:00
 *
 * \author ESSUE
 * Contact: user@company.com
 *
 * \brief 바운드 박스를 이용해서 충돌처리를할 클래스
 *
 * TODO: long description
 *
 * \note 인자값으로 2개의 바운드 박스를 받아서, 두개의 충돌처리를 확인할 예정.
         1차적으로 원충돌 검사를 수행한뒤에, true가 나온다면 AABB박스 충돌 검사를 시행할 예정.
		 상대적으로 가격이 비싼 AABB충돌 검사를 줄임으로써 퍼포먼스를 올려보려함.
*/
#ifndef BoundCol_h__
#define BoundCol_h__

#include "Collision.h"

namespace Engine
{
	class CBoundBox;
}

class CBoundCol
	:public Engine::CCollision
{
private:
	HRESULT Initialize(void);
	void	Release(void);

private:
	bool	ColSphere(Engine::CBoundBox* pTemp, Engine::CBoundBox* pDest);
	bool	ColAABB(Engine::CBoundBox* pTemp, Engine::CBoundBox* pDest);

public:
	bool	ColBoundBox(Engine::CBoundBox* pTemp, Engine::CBoundBox* pDest);

public:
	virtual Engine::CCollision* Clone(void);
	static CBoundCol* Create(void);

private:
	CBoundCol(void);

public:
	virtual ~CBoundCol(void);
};

#endif // BoundCol_h__
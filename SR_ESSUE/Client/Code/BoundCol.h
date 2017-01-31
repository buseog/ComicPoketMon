/*!
 * \file BoundCol.h
 * \date 2017/01/15 19:00
 *
 * \author ESSUE
 * Contact: user@company.com
 *
 * \brief �ٿ�� �ڽ��� �̿��ؼ� �浹ó������ Ŭ����
 *
 * TODO: long description
 *
 * \note ���ڰ����� 2���� �ٿ�� �ڽ��� �޾Ƽ�, �ΰ��� �浹ó���� Ȯ���� ����.
         1�������� ���浹 �˻縦 �����ѵڿ�, true�� ���´ٸ� AABB�ڽ� �浹 �˻縦 ������ ����.
		 ��������� ������ ��� AABB�浹 �˻縦 �������ν� �����ս��� �÷�������.
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
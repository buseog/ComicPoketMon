/*!
 * \file BoundBox.h
 * \date 2017/01/15 18:50
 *
 * \author ESSUE
 * Contact: user@company.com
 *
 * \brief 공격이나 기타등등에 대한 충돌 처리를 하기위해 필요한 클래스
 *
 * TODO: long description
 *
 * \note 이클래스는 원충돌과 AABB충돌을 하기위해 필요한 변수들을 지니고있다.
*/

#ifndef BoundBox_h__
#define BoundBox_h__

#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL CBoundBox
	:public CComponent
{
public:
	// 원충돌을 하기위한 중점좌표 + 반지름값
	D3DXVECTOR3 vCenter;
	D3DXVECTOR3 vSize;

	float		fRadius;
	// AABB충돌을 하기 위한 min, max값
	D3DXVECTOR3	vMin;
	D3DXVECTOR3	vMax;

public:
	bool	Inside(D3DXVECTOR3* vPos);

public:
	HRESULT	Initialize(D3DXVECTOR3* pPos, D3DXVECTOR3* pScale);
	void Update(  D3DXVECTOR3* pPos );

public:
	static CBoundBox* Create(D3DXVECTOR3* pPos, D3DXVECTOR3* pScale);

private:
	CBoundBox(void);

public:
	virtual ~CBoundBox(void);

};

END
#endif // BoundBox_h__
/*!
 * \file BoundBox.h
 * \date 2017/01/15 18:50
 *
 * \author ESSUE
 * Contact: user@company.com
 *
 * \brief �����̳� ��Ÿ�� ���� �浹 ó���� �ϱ����� �ʿ��� Ŭ����
 *
 * TODO: long description
 *
 * \note ��Ŭ������ ���浹�� AABB�浹�� �ϱ����� �ʿ��� �������� ���ϰ��ִ�.
*/

#ifndef BoundBox_h__
#define BoundBox_h__

#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL CBoundBox
	:public CComponent
{
public:
	// ���浹�� �ϱ����� ������ǥ + ��������
	D3DXVECTOR3 vCenter;
	D3DXVECTOR3 vSize;

	float		fRadius;
	// AABB�浹�� �ϱ� ���� min, max��
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
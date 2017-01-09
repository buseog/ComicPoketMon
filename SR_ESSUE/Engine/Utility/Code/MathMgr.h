/*!
 * \file MathMgr.h
 * \date 2017/01/08 17:16
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

#ifndef MathMgr_h__
#define MathMgr_h__

#include "Engine_Include.h"

BEGIN(Engine)

class ENGINE_DLL CMathMgr
{
public:
	static float			MyLength(D3DXVECTOR3* vDest, D3DXVECTOR3* vDepa);
	static void				MyNormalize(D3DXVECTOR3* vOut, D3DXVECTOR3* vIn);
	static float			MyDot(D3DXVECTOR3* vDest, D3DXVECTOR3* vDepa);
	static D3DXVECTOR3		MyCross(D3DXVECTOR3* vDest, D3DXVECTOR3* vDepa);
	
	static void				MyIdentity(D3DXMATRIX* matWorld);
	static void				MyScaling(D3DXMATRIX* matScale, float fX, float fY, float fZ);
	static void				MyScaling(D3DXMATRIX* matScale, D3DXVECTOR3* vScale);

	static void				MyRotationX(D3DXMATRIX* matRotX, float fAngle);
	static void				MyRotationY(D3DXMATRIX* matRotX, float fAngle);
	static void				MyRotationZ(D3DXMATRIX* matRotX, float fAngle);

	static void				MyRotationX(D3DXVECTOR3* pOut, D3DXVECTOR3* pIn, float fAngle);
	static void				MyRotationY(D3DXVECTOR3* pOut, D3DXVECTOR3* pIn, float fAngle);
	static void				MyRotationZ(D3DXVECTOR3* pOut, D3DXVECTOR3* pIn, float fAngle);

	static void				MyTranslation(D3DXMATRIX* matTrans, D3DXVECTOR3* vTrans);

private:
	CMathMgr(void);
	~CMathMgr(void);
};

END
#endif // MathMgr_h__
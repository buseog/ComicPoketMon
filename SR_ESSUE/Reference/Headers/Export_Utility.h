#ifndef Export_Utility_h__
#define Export_Utility_h__

#include "Management.h"
#include "InfoSubject.h"
#include "StatSubject.h"

BEGIN(Engine)

inline CManagement* Get_Management(void);
inline CInfoSubject* Get_InfoSubject(void);
inline CStatSubject* Get_StatSubject(void);

inline void	MyTransformCoord(D3DXVECTOR3* vOut, const D3DXVECTOR3* vVec, const D3DXMATRIX* matWorld);
inline void	MyIdentity(D3DXMATRIX* matWorld);

inline float			MyLength(const D3DXVECTOR3* vDest, const D3DXVECTOR3* vDepa);
inline void				MyNormalize(D3DXVECTOR3* vOut, D3DXVECTOR3* vIn);
inline float			MyDot(D3DXVECTOR3* vDest, D3DXVECTOR3* vDepa);
inline D3DXVECTOR3		MyCross(D3DXVECTOR3* vDest, D3DXVECTOR3* vDepa);

#include "Export_Utility.inl"

END
#endif // Export_Utility_h__
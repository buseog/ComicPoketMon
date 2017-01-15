#ifndef Export_Utility_h__
#define Export_Utility_h__

#include "Management.h"
#include "InfoSubject.h"

BEGIN(Engine)

inline CManagement* Get_Management(void);
inline CInfoSubject* Get_InfoSubject(void);

inline void	MyTransformCoord(D3DXVECTOR3* vOut, const D3DXVECTOR3* vVec, const D3DXMATRIX* matWorld);
inline void	MyIdentity(D3DXMATRIX* matWorld);

#include "Export_Utility.inl"

END
#endif // Export_Utility_h__
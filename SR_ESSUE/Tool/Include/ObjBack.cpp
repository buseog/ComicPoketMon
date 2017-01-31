#include "StdAfx.h"
#include "ObjBack.h"
#include "Resources.h"
#include "VIBuffer.h"
#include "Include.h"
#include "..\Include\MainFrm.h"

#include "Texture.h"
#include "CubeObj.h"
#include "CubeCol.h"
#include "CubeTex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CObjBack::CObjBack(LPDIRECT3DDEVICE9 pDevice)
: CGameObject(pDevice)
, m_pBuffer(NULL)
, m_fDistance(0)
, m_pVertex(NULL)
, m_dwType(0)
{

}

CObjBack::~CObjBack(void)
{
	Release();
}

void CObjBack::Release( void )
{
	for_each (m_mapChar.begin(), m_mapChar.end(), Engine::CDeleteMap());
	m_mapChar.clear();

	vector<Engine::CResources*>::iterator iter = m_vecObject.begin();
	vector<Engine::CResources*>::iterator iter_End = m_vecObject.end();

	for(; iter!=iter_End; ++iter)
	{
		Engine::Safe_Delete((*iter));
	}

	Engine::Safe_Delete_Array(m_pVertex);
	Engine::Safe_Delete_Array(m_pIndex);
}

void CObjBack::KeyCheck( void )
{
	if(GetAsyncKeyState('W') & 0x8000)
	{
		m_fDistance -= 1.f;
		D3DXVec3Normalize(&m_vAt, &m_vAt);
		m_vEye = m_vAt * -m_fDistance;
	}

	if(GetAsyncKeyState('S') & 0x8000)
	{
		m_fDistance += 1.f;
		D3DXVec3Normalize(&m_vAt, &m_vAt);
		m_vEye = m_vAt * -m_fDistance;
	}

	if(GetAsyncKeyState('A') & 0x8000)
	{
		m_fAngle[Engine::ANGLE_Y] = D3DXToRadian(-5.f);
		D3DXMATRIX matRotY;
		D3DXMatrixRotationY(&matRotY, m_fAngle[Engine::ANGLE_Y]);
		D3DXVec3TransformNormal(&m_vAt, &m_vAt, &matRotY);
		D3DXVec3Normalize(&m_vAt, &m_vAt);
		m_vEye = -m_vAt * m_fDistance;
	}

	if(GetAsyncKeyState('D') & 0x8000)
	{
		m_fAngle[Engine::ANGLE_Y] = D3DXToRadian(5.f);
		D3DXMATRIX matRotY;
		D3DXMatrixRotationY(&matRotY, m_fAngle[Engine::ANGLE_Y]);
		D3DXVec3TransformNormal(&m_vAt, &m_vAt, &matRotY);
		D3DXVec3Normalize(&m_vAt, &m_vAt);
		m_vEye = -m_vAt * m_fDistance;
	}

	if(GetAsyncKeyState('Q') & 0x8000)
	{
		m_fAngle[Engine::ANGLE_X] = D3DXToRadian(5.f);
		D3DXMATRIX matAxis;
		D3DXVECTOR3 vDirX;
		D3DXVec3Cross(&vDirX, &D3DXVECTOR3(0.f, 1.f, 0.f), &m_vAt);
		D3DXMatrixRotationAxis(&matAxis, &vDirX, m_fAngle[Engine::ANGLE_X]);
		D3DXVec3TransformNormal(&m_vAt, &m_vAt, &matAxis);
		m_vEye = -m_vAt * m_fDistance;

	}

	if(GetAsyncKeyState('E') & 0x8000)
	{
		m_fAngle[Engine::ANGLE_X] = D3DXToRadian(-5.f);
		D3DXMATRIX matAxis;
		D3DXVECTOR3 vDirX;
		D3DXVec3Cross(&vDirX, &D3DXVECTOR3(0.f, 1.f, 0.f), &m_vAt);
		D3DXMatrixRotationAxis(&matAxis, &vDirX, m_fAngle[Engine::ANGLE_X]);
		D3DXVec3TransformNormal(&m_vAt, &m_vAt, &matAxis);
		m_vEye = -m_vAt * m_fDistance;
	}

	if (m_pBuffer != NULL)
	{
		if(GetAsyncKeyState(VK_NUMPAD4) & 0x8000)
		{
			((Engine::CVIBuffer*)m_pBuffer)->GetVtxInfo(m_pVertex);

			for (int i = 0; i < 8; ++i)
			{
				m_pVertex[i].vPos += D3DXVECTOR3(-0.1f, 0.f, 0.f);
			}

			((Engine::CVIBuffer*)m_pBuffer)->SetVtxInfo(m_pVertex);
			((Engine::CVIBuffer*)m_pBuffer)->SetOriginVtxInfo(m_pVertex);
		}

		if(GetAsyncKeyState(VK_NUMPAD6) & 0x8000)
		{
			((Engine::CVIBuffer*)m_pBuffer)->GetVtxInfo(m_pVertex);

			for (int i = 0; i < 8; ++i)
			{
				m_pVertex[i].vPos += D3DXVECTOR3(0.1f, 0.f, 0.f);
			}

			((Engine::CVIBuffer*)m_pBuffer)->SetVtxInfo(m_pVertex);
			((Engine::CVIBuffer*)m_pBuffer)->SetOriginVtxInfo(m_pVertex);
		}

		if(GetAsyncKeyState(VK_NUMPAD2) & 0x8000)
		{
			((Engine::CVIBuffer*)m_pBuffer)->GetVtxInfo(m_pVertex);

			for (int i = 0; i < 8; ++i)
			{
				m_pVertex[i].vPos += D3DXVECTOR3(0.f, -0.1f, 0.f);
			}

			((Engine::CVIBuffer*)m_pBuffer)->SetVtxInfo(m_pVertex);
			((Engine::CVIBuffer*)m_pBuffer)->SetOriginVtxInfo(m_pVertex);
		}

		if(GetAsyncKeyState(VK_NUMPAD8) & 0x8000)
		{
			((Engine::CVIBuffer*)m_pBuffer)->GetVtxInfo(m_pVertex);

			for (int i = 0; i < 8; ++i)
			{
				m_pVertex[i].vPos += D3DXVECTOR3(0.f, 0.1f, 0.f);
			}

			((Engine::CVIBuffer*)m_pBuffer)->SetVtxInfo(m_pVertex);
			((Engine::CVIBuffer*)m_pBuffer)->SetOriginVtxInfo(m_pVertex);
		}

		if(GetAsyncKeyState(VK_NUMPAD5) & 0x8000)
		{
			((Engine::CVIBuffer*)m_pBuffer)->GetVtxInfo(m_pVertex);

			for (int i = 0; i < 8; ++i)
			{
				m_pVertex[i].vPos += D3DXVECTOR3(0.f, 0.f, 0.1f);
			}

			((Engine::CVIBuffer*)m_pBuffer)->SetVtxInfo(m_pVertex);
			((Engine::CVIBuffer*)m_pBuffer)->SetOriginVtxInfo(m_pVertex);
		}

		if(GetAsyncKeyState(VK_NUMPAD0) & 0x8000)
		{
			((Engine::CVIBuffer*)m_pBuffer)->GetVtxInfo(m_pVertex);

			for (int i = 0; i < 8; ++i)
			{
				m_pVertex[i].vPos += D3DXVECTOR3(0.f, 0.f, -0.1f);
			}

			((Engine::CVIBuffer*)m_pBuffer)->SetVtxInfo(m_pVertex);
			((Engine::CVIBuffer*)m_pBuffer)->SetOriginVtxInfo(m_pVertex);
		}
	}

	if(GetAsyncKeyState('I') & 0x8000)
	{
		for (map<wstring, Engine::CResources*>::iterator iter = m_mapChar.begin(); iter!= m_mapChar.end(); ++iter )
		{
			((Engine::CVIBuffer*)iter->second)->GetVtxInfo(m_pVertex);

			for (int i = 0; i < 8; ++i)
			{
				m_pVertex[i].vPos += D3DXVECTOR3(0.f, 0.3f, 0.f);
			}

			((Engine::CVIBuffer*)iter->second)->SetVtxInfo(m_pVertex);
			((Engine::CVIBuffer*)iter->second)->SetOriginVtxInfo(m_pVertex);
		}
	}

	if(GetAsyncKeyState('K') & 0x8000)
	{
		for (map<wstring, Engine::CResources*>::iterator iter = m_mapChar.begin(); iter!= m_mapChar.end(); ++iter )
		{
			((Engine::CVIBuffer*)iter->second)->GetVtxInfo(m_pVertex);

			for (int i = 0; i < 8; ++i)
			{
				m_pVertex[i].vPos += D3DXVECTOR3(0.f, -.3f, 0.f);
			}

			((Engine::CVIBuffer*)iter->second)->SetVtxInfo(m_pVertex);
			((Engine::CVIBuffer*)iter->second)->SetOriginVtxInfo(m_pVertex);
		}
	}

	if(GetAsyncKeyState('U') & 0x8000)
	{
		for (map<wstring, Engine::CResources*>::iterator iter = m_mapChar.begin(); iter!= m_mapChar.end(); ++iter )
		{
			((Engine::CVIBuffer*)iter->second)->GetVtxInfo(m_pVertex);

			for (int i = 0; i < 8; ++i)
			{
				m_pVertex[i].vPos += D3DXVECTOR3(0.f, 0.f, 0.3f);
			}

			((Engine::CVIBuffer*)iter->second)->SetVtxInfo(m_pVertex);
			((Engine::CVIBuffer*)iter->second)->SetOriginVtxInfo(m_pVertex);
		}
	}

	if(GetAsyncKeyState('Y') & 0x8000)
	{
		for (map<wstring, Engine::CResources*>::iterator iter = m_mapChar.begin(); iter!= m_mapChar.end(); ++iter )
		{
			((Engine::CVIBuffer*)iter->second)->GetVtxInfo(m_pVertex);

			for (int i = 0; i < 8; ++i)
			{
				m_pVertex[i].vPos += D3DXVECTOR3(0.f, 0.f, -0.3f);
			}

			((Engine::CVIBuffer*)iter->second)->SetVtxInfo(m_pVertex);
			((Engine::CVIBuffer*)iter->second)->SetOriginVtxInfo(m_pVertex);
		}
	}

	if(GetAsyncKeyState('J') & 0x8000)
	{
		D3DXMATRIX matRot;

		D3DXMatrixRotationY(&matRot, D3DXToRadian(-3.f));

		for (map<wstring, Engine::CResources*>::iterator iter = m_mapChar.begin(); iter!= m_mapChar.end(); ++iter )
		{
			((Engine::CVIBuffer*)iter->second)->GetVtxInfo(m_pVertex);

			D3DXVECTOR3 vTemp;
			vTemp.x = (m_pVertex[1].vPos.x - m_pVertex[0].vTex.x);
			vTemp.y = (m_pVertex[0].vPos.y - m_pVertex[3].vPos.y);
			vTemp.z = (m_pVertex[4].vPos.z - m_pVertex[0].vPos.z);
			vTemp /= 3.f;

			for (int i = 0; i < 8; ++i)
			{
				D3DXVec3TransformCoord(&m_pVertex[i].vPos, &m_pVertex[i].vPos, &matRot);
			}
			((Engine::CVIBuffer*)iter->second)->SetVtxInfo(m_pVertex);
			((Engine::CVIBuffer*)iter->second)->SetOriginVtxInfo(m_pVertex);
		}
	}

	if(GetAsyncKeyState('L') & 0x8000)
	{
		D3DXMATRIX matRot;

		D3DXMatrixRotationY(&matRot, D3DXToRadian(3.f));

		for (map<wstring, Engine::CResources*>::iterator iter = m_mapChar.begin(); iter!= m_mapChar.end(); ++iter )
		{
			((Engine::CVIBuffer*)iter->second)->GetVtxInfo(m_pVertex);

			D3DXVECTOR3 vTemp;
			vTemp.x = (m_pVertex[1].vPos.x - m_pVertex[0].vTex.x);
			vTemp.y = (m_pVertex[0].vPos.y - m_pVertex[3].vPos.y);
			vTemp.z = (m_pVertex[4].vPos.z - m_pVertex[0].vPos.z);
			vTemp /= 3.f;

			for (int i = 0; i < 8; ++i)
			{
				D3DXVec3TransformCoord(&m_pVertex[i].vPos, &m_pVertex[i].vPos, &matRot);
			}
			((Engine::CVIBuffer*)iter->second)->SetVtxInfo(m_pVertex);
			((Engine::CVIBuffer*)iter->second)->SetOriginVtxInfo(m_pVertex);
		}
	}

	if(GetAsyncKeyState('O') & 0x8000)
	{
		D3DXMATRIX matRot;

		D3DXMatrixRotationX(&matRot, D3DXToRadian(3.f));

		for (map<wstring, Engine::CResources*>::iterator iter = m_mapChar.begin(); iter!= m_mapChar.end(); ++iter )
		{
			((Engine::CVIBuffer*)iter->second)->GetVtxInfo(m_pVertex);

			D3DXVECTOR3 vTemp;
			vTemp.x = (m_pVertex[1].vPos.x - m_pVertex[0].vTex.x);
			vTemp.y = (m_pVertex[0].vPos.y - m_pVertex[3].vPos.y);
			vTemp.z = (m_pVertex[4].vPos.z - m_pVertex[0].vPos.z);
			vTemp /= 3.f;

			for (int i = 0; i < 8; ++i)
			{
				D3DXVec3TransformCoord(&m_pVertex[i].vPos, &m_pVertex[i].vPos, &matRot);
			}
			((Engine::CVIBuffer*)iter->second)->SetVtxInfo(m_pVertex);
			((Engine::CVIBuffer*)iter->second)->SetOriginVtxInfo(m_pVertex);
		}
	}

	if(GetAsyncKeyState('P') & 0x8000)
	{
		D3DXMATRIX matRot;

		D3DXMatrixRotationX(&matRot, D3DXToRadian(-3.f));

		for (map<wstring, Engine::CResources*>::iterator iter = m_mapChar.begin(); iter!= m_mapChar.end(); ++iter )
		{
			((Engine::CVIBuffer*)iter->second)->GetVtxInfo(m_pVertex);

			D3DXVECTOR3 vTemp;
			vTemp.x = (m_pVertex[1].vPos.x - m_pVertex[0].vTex.x);
			vTemp.y = (m_pVertex[0].vPos.y - m_pVertex[3].vPos.y);
			vTemp.z = (m_pVertex[4].vPos.z - m_pVertex[0].vPos.z);
			vTemp /= 3.f;

			for (int i = 0; i < 8; ++i)
			{
				D3DXVec3TransformCoord(&m_pVertex[i].vPos, &m_pVertex[i].vPos, &matRot);
			}
			((Engine::CVIBuffer*)iter->second)->SetVtxInfo(m_pVertex);
			((Engine::CVIBuffer*)iter->second)->SetOriginVtxInfo(m_pVertex);
		}
	}


	if (GetAsyncKeyState(VK_F11) & 0x8000)
	{
		m_dwType = 0;
	}


	if (GetAsyncKeyState(VK_F12) & 0x8000)
	{
		m_dwType = 1;
	}

	D3DXMatrixLookAtLH(&matView, &m_vEye, &m_vAt, &D3DXVECTOR3(0.f,1.f,0.f));
	m_pDevice->SetTransform(D3DTS_VIEW, &matView);
}

void CObjBack::DeletePicking( void )
{
	POINT	pt;

	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	D3DXMATRIX matRView, matRProj;

	D3DXVECTOR3 vMouse;

	vMouse.x = (float(pt.x)  / (WINCX / 2) - 1.f) / matProj._11;
	vMouse.y = (float(-pt.y) / (WINCY / 2) + 1.f) / matProj._22;
	vMouse.z = 1.f;

	D3DXVECTOR3 vRayPos, vRayDir;
	vRayPos = D3DXVECTOR3(0.f,0.f,0.f);
	vRayDir = vMouse;

	D3DXMatrixInverse(&matRView, 0, &matView);
	D3DXVec3TransformCoord(&vRayPos, &vRayPos, &matRView);
	D3DXVec3TransformNormal(&vRayDir, &vRayDir, &matRView);

	D3DXMATRIX matRWorld;
	D3DXMatrixIdentity(&matRWorld);
	D3DXMatrixInverse(&matRWorld, 0, &matRWorld);
	D3DXVec3TransformCoord(&vRayPos, &vRayPos, &matRWorld);
	D3DXVec3TransformNormal(&vRayDir, &vRayDir, &matRWorld);


	float	fU, fV, fDist;

	if (m_dwType == 1)
	{
		for (vector<Engine::CResources*>::iterator iter = m_vecObject.begin(); iter != m_vecObject.end(); ++iter)
		{
			((Engine::CVIBuffer*)*iter)->GetVtxInfo(m_pVertex);
			((Engine::CVIBuffer*)*iter)->GetIdxInfo(m_pIndex);

			for (int j = 0; j < 12; ++j)
			{
				if(D3DXIntersectTri(&m_pVertex[m_pIndex[j]._2].vPos, &m_pVertex[m_pIndex[j]._1].vPos,	&m_pVertex[m_pIndex[j]._3].vPos,
					&vRayPos, &vRayDir, &fU, &fV, &fDist))
				{
					Engine::Safe_Delete(*iter);
					iter = m_vecObject.erase(iter);

					return;
				}
			}
		}
	}

	for (map<wstring, Engine::CResources*>::iterator iter = m_mapChar.begin(); iter != m_mapChar.end(); ++iter)
	{
		((Engine::CVIBuffer*)iter->second)->GetVtxInfo(m_pVertex);
		((Engine::CVIBuffer*)iter->second)->GetIdxInfo(m_pIndex);

		for (int i = 0; i < 12; ++i)
		{
			if(D3DXIntersectTri(&m_pVertex[m_pIndex[i]._2].vPos, &m_pVertex[m_pIndex[i]._1].vPos,	&m_pVertex[m_pIndex[i]._3].vPos,
				&vRayPos, &vRayDir, &fU, &fV, &fDist))
			{
				Engine::Safe_Delete(iter->second);
				iter = m_mapChar.erase(iter);
				
				return;
			}
		}
	}
}

void CObjBack::AddPicking( void )
{
	POINT	pt;

	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	D3DXMATRIX matRView, matRProj;

	D3DXVECTOR3 vMouse;

	vMouse.x = (float(pt.x)  / (WINCX / 2) - 1.f) / matProj._11;
	vMouse.y = (float(-pt.y) / (WINCY / 2) + 1.f) / matProj._22;
	vMouse.z = 1.f;

	D3DXVECTOR3 vRayPos, vRayDir;
	vRayPos = D3DXVECTOR3(0.f,0.f,0.f);
	vRayDir = vMouse;

	D3DXMatrixInverse(&matRView, 0, &matView);
	D3DXVec3TransformCoord(&vRayPos, &vRayPos, &matRView);
	D3DXVec3TransformNormal(&vRayDir, &vRayDir, &matRView);

	D3DXMATRIX matRWorld;
	D3DXMatrixIdentity(&matRWorld);
	D3DXMatrixInverse(&matRWorld, 0, &matRWorld);
	D3DXVec3TransformCoord(&vRayPos, &vRayPos, &matRWorld);
	D3DXVec3TransformNormal(&vRayDir, &vRayDir, &matRWorld);


	float	fU, fV, fDist;


	multimap<float, map<Engine::CComponent*, int>> multimapTemp; 

	wstring wstrTexKey = ((CMainFrame*)AfxGetMainWnd())->m_pMainForm->m_pUnit.m_wstrTexKey;
	wstring wstrName = (LPWSTR)((CMainFrame*)AfxGetMainWnd())->m_pMainForm->m_pUnit.m_TexKey.operator LPCWSTR();

	CString strKey;
	strKey = wstrName.c_str();
	PathRemoveExtension((LPWSTR)strKey.operator LPCWSTR());
	wstrName = (LPWSTR)strKey.operator LPCWSTR();

	/// 오브젝트 피킹
	if (m_dwType == 1)
	{
		for (size_t i = 0; i < m_vecObject.size(); ++i)
		{
			((Engine::CVIBuffer*)m_vecObject[i])->GetVtxInfo(m_pVertex);
			((Engine::CVIBuffer*)m_vecObject[i])->GetIdxInfo(m_pIndex);

			for (int j = 0; j < 12; ++j)
			{
				if(D3DXIntersectTri(&m_pVertex[m_pIndex[j]._2].vPos, &m_pVertex[m_pIndex[j]._1].vPos,	&m_pVertex[m_pIndex[j]._3].vPos,
					&vRayPos, &vRayDir, &fU, &fV, &fDist))
				{
					map<Engine::CComponent*, int> mapTemp;

					mapTemp.insert(make_pair(m_vecObject[i], j));

					multimapTemp.insert(make_pair(fDist, mapTemp));
				}
			}
		}

		if (multimapTemp.empty())
			return;

		map<Engine::CComponent*, int>::iterator		iter = multimapTemp.begin()->second.begin();

		// 오브젝트 추가
		m_vecObject.push_back(Engine::CCubeTex::Create(m_pDevice, wstrTexKey));

		Engine::VTXCUBE*	pNew = new Engine::VTXCUBE[8];

		((Engine::CVIBuffer*)iter->first)->GetVtxInfo(m_pVertex);
		((Engine::CVIBuffer*)iter->first)->GetVtxInfo(pNew);

		if (iter->second <= 1)
		{
			for (int p = 0; p < 8 ; ++p)
				pNew[p].vPos = m_pVertex[p].vPos + D3DXVECTOR3(2.f, 0.f, 0.f);
		}
		else if (iter->second <= 3)
		{
			for (int p = 0; p < 8 ; ++p)
				pNew[p].vPos = m_pVertex[p].vPos + D3DXVECTOR3(-2.f, 0.f, 0.f);
		}

		else if (iter->second <= 5)
		{
			for (int p = 0; p < 8 ; ++p)
				pNew[p].vPos = m_pVertex[p].vPos + D3DXVECTOR3(0.f, 2.f, 0.f);
		}

		else if (iter->second <= 7)
		{
			for (int p = 0; p < 8 ; ++p)
				pNew[p].vPos = m_pVertex[p].vPos + D3DXVECTOR3(0.f, -2.f, 0.f);
		}

		else if (iter->second <= 9)
		{
			for (int p = 0; p < 8 ; ++p)
				pNew[p].vPos = m_pVertex[p].vPos + D3DXVECTOR3(0.f, 0.f, 2.f);
		}

		else if (iter->second <= 11)
		{
			for (int p = 0; p < 8 ; ++p)
				pNew[p].vPos = m_pVertex[p].vPos + D3DXVECTOR3(0.f, 0.f, -2.f);
		}

		((Engine::CVIBuffer*)m_vecObject.back())->SetVtxInfo(pNew);
		((Engine::CVIBuffer*)m_vecObject.back())->SetOriginVtxInfo(pNew);

		Engine::Safe_Delete_Array(pNew);

		return;
	}

	// 유닛 충돌검사

	for (map<wstring, Engine::CResources*>::iterator iter = m_mapChar.begin(); iter != m_mapChar.end(); ++iter)
	{
		((Engine::CVIBuffer*)iter->second)->GetVtxInfo(m_pVertex);
		((Engine::CVIBuffer*)iter->second)->GetIdxInfo(m_pIndex);

		for (int i = 0; i < 12; ++i)
		{
			if(D3DXIntersectTri(&m_pVertex[m_pIndex[i]._2].vPos, &m_pVertex[m_pIndex[i]._1].vPos,	&m_pVertex[m_pIndex[i]._3].vPos,
				&vRayPos, &vRayDir, &fU, &fV, &fDist))
			{
				map<Engine::CComponent*, int> mapTemp;

				mapTemp.insert(make_pair(iter->second, i));

				multimapTemp.insert(make_pair(fDist, mapTemp));
			}
		}
	}

	if (multimapTemp.empty())
		return;

	 map<Engine::CComponent*, int>::iterator		iter = multimapTemp.begin()->second.begin();

	/// 유닛 피킹

	if (((CMainFrame*)AfxGetMainWnd())->m_pMainForm->m_pUnit.m_iCubetype == 0)
	{
		m_mapChar.insert(make_pair(wstrName, Engine::CCubeCol::Create(m_pDevice)));

		Engine::VTXCOL*		pNew = new Engine::VTXCOL[8];

		map<wstring, Engine::CResources*>::iterator iter2 = m_mapChar.find(wstrName);
		((Engine::CVIBuffer*)iter->first)->GetVtxInfo(m_pVertex);
		((Engine::CVIBuffer*)iter2->second)->GetVtxInfo(pNew);

		if (iter->second <= 1)
		{
			for (int p = 0; p < 8 ; ++p)
				pNew[p].vPos = m_pVertex[p].vPos + D3DXVECTOR3(2.f, 0.f, 0.f);
		}
		else if (iter->second <= 3)
		{
			for (int p = 0; p < 8 ; ++p)
				pNew[p].vPos = m_pVertex[p].vPos + D3DXVECTOR3(-2.f, 0.f, 0.f);
		}

		else if (iter->second <= 5)
		{
			for (int p = 0; p < 8 ; ++p)
				pNew[p].vPos = m_pVertex[p].vPos + D3DXVECTOR3(0.f, 2.f, 0.f);
		}

		else if (iter->second <= 7)
		{
			for (int p = 0; p < 8 ; ++p)
				pNew[p].vPos = m_pVertex[p].vPos + D3DXVECTOR3(0.f, -2.f, 0.f);
		}

		else if (iter->second <= 9)
		{
			for (int p = 0; p < 8 ; ++p)
				pNew[p].vPos = m_pVertex[p].vPos + D3DXVECTOR3(0.f, 0.f, 2.f);
		}

		else if (iter->second <= 11)
		{
			for (int p = 0; p < 8 ; ++p)
				pNew[p].vPos = m_pVertex[p].vPos + D3DXVECTOR3(0.f, 0.f, -2.f);
		}

		((Engine::CVIBuffer*)iter2->second)->SetVtxInfo(pNew);
		((Engine::CVIBuffer*)iter2->second)->SetOriginVtxInfo(pNew);

		Engine::Safe_Delete_Array(pNew);
	}
	else if (((CMainFrame*)AfxGetMainWnd())->m_pMainForm->m_pUnit.m_iCubetype == 1)
	{
   		m_mapChar.insert(make_pair(wstrName, Engine::CCubeTex::Create(m_pDevice, wstrTexKey)));

		Engine::VTXCUBE*	pNew = new Engine::VTXCUBE[8];

		map<wstring, Engine::CResources*>::iterator iter2 = m_mapChar.find(wstrName);
		((Engine::CVIBuffer*)iter->first)->GetVtxInfo(m_pVertex);
		((Engine::CVIBuffer*)iter2->second)->GetVtxInfo(pNew);

		if (iter->second <= 1)
		{
			for (int p = 0; p < 8 ; ++p)
				pNew[p].vPos = m_pVertex[p].vPos + D3DXVECTOR3(2.f, 0.f, 0.f);
		}
		else if (iter->second <= 3)
		{
			for (int p = 0; p < 8 ; ++p)
				pNew[p].vPos = m_pVertex[p].vPos + D3DXVECTOR3(-2.f, 0.f, 0.f);
		}

		else if (iter->second <= 5)
		{
			for (int p = 0; p < 8 ; ++p)
				pNew[p].vPos = m_pVertex[p].vPos + D3DXVECTOR3(0.f, 2.f, 0.f);
		}

		else if (iter->second <= 7)
		{
			for (int p = 0; p < 8 ; ++p)
				pNew[p].vPos = m_pVertex[p].vPos + D3DXVECTOR3(0.f, -2.f, 0.f);
		}

		else if (iter->second <= 9)
		{
			for (int p = 0; p < 8 ; ++p)
				pNew[p].vPos = m_pVertex[p].vPos + D3DXVECTOR3(0.f, 0.f, 2.f);
		}

		else if (iter->second <= 11)
		{
			for (int p = 0; p < 8 ; ++p)
				pNew[p].vPos = m_pVertex[p].vPos + D3DXVECTOR3(0.f, 0.f, -2.f);
		}

		((Engine::CVIBuffer*)iter2->second)->SetVtxInfo(pNew);
		((Engine::CVIBuffer*)iter2->second)->SetOriginVtxInfo(pNew);

		Engine::Safe_Delete_Array(pNew);
	}
}

void CObjBack::SelectPicking( void )
{
	POINT	pt;

	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	D3DXMATRIX matRView, matRProj;

	D3DXVECTOR3 vMouse;

	vMouse.x = (float(pt.x)  / (WINCX / 2) - 1.f) / matProj._11;
	vMouse.y = (float(-pt.y) / (WINCY / 2) + 1.f) / matProj._22;
	vMouse.z = 1.f;

	D3DXVECTOR3 vRayPos, vRayDir;
	vRayPos = D3DXVECTOR3(0.f,0.f,0.f);
	vRayDir = vMouse;

	D3DXMatrixInverse(&matRView, 0, &matView);
	D3DXVec3TransformCoord(&vRayPos, &vRayPos, &matRView);
	D3DXVec3TransformNormal(&vRayDir, &vRayDir, &matRView);

	D3DXMATRIX matRWorld;
	D3DXMatrixIdentity(&matRWorld);
	D3DXMatrixInverse(&matRWorld, 0, &matRWorld);
	D3DXVec3TransformCoord(&vRayPos, &vRayPos, &matRWorld);
	D3DXVec3TransformNormal(&vRayDir, &vRayDir, &matRWorld);


	float	fU, fV, fDist;

	if (m_dwType == 1)
	{
		for (vector<Engine::CResources*>::iterator iter = m_vecObject.begin(); iter != m_vecObject.end(); ++iter)
		{
			((Engine::CVIBuffer*)*iter)->GetVtxInfo(m_pVertex);
			((Engine::CVIBuffer*)*iter)->GetIdxInfo(m_pIndex);

			for (int j = 0; j < 12; ++j)
			{
				if(D3DXIntersectTri(&m_pVertex[m_pIndex[j]._2].vPos, &m_pVertex[m_pIndex[j]._1].vPos,	&m_pVertex[m_pIndex[j]._3].vPos,
					&vRayPos, &vRayDir, &fU, &fV, &fDist))
				{
					m_pBuffer = dynamic_cast<Engine::CVIBuffer*>(*iter);
					D3DXVECTOR3 vTemp;
					vTemp.x = (m_pVertex[0].vPos.x + m_pVertex[1].vPos.x) / 2;
					vTemp.y = (m_pVertex[0].vPos.y + m_pVertex[3].vPos.y) / 2;
					vTemp.z = (m_pVertex[0].vPos.z + m_pVertex[5].vPos.z) / 2;

					((CMainFrame*)AfxGetMainWnd())->m_pMainForm->m_pUnit.SetPos(vTemp, *m_pBuffer->GetScale());

					return;
				}
			}
		}
	}
	

	for (map<wstring, Engine::CResources*>::iterator iter = m_mapChar.begin(); iter != m_mapChar.end(); ++iter)
	{
		((Engine::CVIBuffer*)iter->second)->GetVtxInfo(m_pVertex);
		((Engine::CVIBuffer*)iter->second)->GetIdxInfo(m_pIndex);

		for (int i = 0; i < 12; ++i)
		{
			if(D3DXIntersectTri(&m_pVertex[m_pIndex[i]._2].vPos, &m_pVertex[m_pIndex[i]._1].vPos,	&m_pVertex[m_pIndex[i]._3].vPos,
				&vRayPos, &vRayDir, &fU, &fV, &fDist))
			{
				m_pBuffer = dynamic_cast<Engine::CVIBuffer*>(iter->second);
				D3DXVECTOR3 vTemp;
				vTemp.x = (m_pVertex[0].vPos.x + m_pVertex[1].vPos.x) / 2;
				vTemp.y = (m_pVertex[0].vPos.y + m_pVertex[3].vPos.y) / 2;
				vTemp.z = (m_pVertex[0].vPos.z + m_pVertex[5].vPos.z) / 2;
				
				((CMainFrame*)AfxGetMainWnd())->m_pMainForm->m_pUnit.SetPos(vTemp, *m_pBuffer->GetScale());

				return;
			}
		}
	}
}

void CObjBack::SetScaleCube( D3DXVECTOR3 vScale )
{
	if (m_pBuffer == NULL)
		return;

	((Engine::CVIBuffer*)m_pBuffer)->GetVtxInfo(m_pVertex);

	for (int i = 0; i < 8; ++i)
	{
		m_pVertex[i].vPos.x *= vScale.x;
		m_pVertex[i].vPos.y *= vScale.y;
		m_pVertex[i].vPos.z *= vScale.z;
	}

	m_pBuffer->SetScale(vScale);
	((Engine::CVIBuffer*)m_pBuffer)->SetVtxInfo(m_pVertex);
	((Engine::CVIBuffer*)m_pBuffer)->SetOriginVtxInfo(m_pVertex);
}


void CObjBack::SetTransCube( D3DXVECTOR3 vPos)
{
	if (m_pBuffer == NULL)
		return;

	((Engine::CVIBuffer*)m_pBuffer)->GetVtxInfo(m_pVertex);

	D3DXVECTOR3 pScale = *((Engine::CVIBuffer*)m_pBuffer)->GetScale();

	m_pVertex[0].vPos = D3DXVECTOR3(-1.f, 1.f, -1.f);

	m_pVertex[1].vPos = D3DXVECTOR3(1.f, 1.f ,-1.f);

	m_pVertex[2].vPos = D3DXVECTOR3(1.f, -1.f ,-1.f);

	m_pVertex[3].vPos = D3DXVECTOR3(-1.f, -1.f ,-1.f);

	m_pVertex[4].vPos = D3DXVECTOR3(-1.f, 1.f ,1.f);

	m_pVertex[5].vPos = D3DXVECTOR3(1.f, 1.f ,1.f);

	m_pVertex[6].vPos = D3DXVECTOR3(1.f, -1.f ,1.f);

	m_pVertex[7].vPos = D3DXVECTOR3(-1.f, -1.f ,1.f);

	for (int i = 0; i < 8; ++i)
	{
		m_pVertex[i].vPos.x *= pScale.x;
		m_pVertex[i].vPos.y *= pScale.y;
		m_pVertex[i].vPos.z *= pScale.z;
		m_pVertex[i].vPos += vPos;
	}

	((Engine::CVIBuffer*)m_pBuffer)->SetVtxInfo(m_pVertex);
	((Engine::CVIBuffer*)m_pBuffer)->SetOriginVtxInfo(m_pVertex);
}

void CObjBack::SetRotationCube( int iFlag, float fAngle, D3DXVECTOR3 vPos )
{
	if (m_pBuffer == NULL)
		return;

	((Engine::CVIBuffer*)m_pBuffer)->GetOriginVtxInfo(m_pVertex);

	D3DXMATRIX matRot;

	switch (iFlag)
	{
	case 0:
		D3DXMatrixRotationX(&matRot, D3DXToRadian(fAngle));
		break;
	case 1:
		D3DXMatrixRotationY(&matRot, D3DXToRadian(fAngle));
		break;
	case 2:
		D3DXMatrixRotationZ(&matRot, D3DXToRadian(fAngle));
		break;
	}
	
	for (int i = 0; i < 8; ++i)
	{
		m_pVertex[i].vPos -= vPos;
		D3DXVec3TransformCoord(&m_pVertex[i].vPos, &m_pVertex[i].vPos, &matRot);
		m_pVertex[i].vPos += vPos;
	}

	((Engine::CVIBuffer*)m_pBuffer)->SetVtxInfo(m_pVertex);
}

void CObjBack::SetApplyCube( void )
{
	((Engine::CVIBuffer*)m_pBuffer)->SetOriginVtxInfo(m_pVertex);
}

void CObjBack::SetColor( DWORD dwColor )
{
	if (m_pBuffer == NULL)
		return;

	((Engine::CVIBuffer*)m_pBuffer)->GetOriginVtxInfo(m_pVertex);

	/*for (int i = 0; i < 8; ++i)
	{
		m_pVertex[i].dwColor = dwColor;
	}*/
	
	((Engine::CVIBuffer*)m_pBuffer)->SetVtxInfo(m_pVertex);
	((Engine::CVIBuffer*)m_pBuffer)->SetOriginVtxInfo(m_pVertex);
}

void CObjBack::DrawLine( void )
{
	D3DXMATRIX	matWorld;
	D3DXMatrixIdentity(&matWorld);
	matWorld = matView * matProj;

	D3DXCreateLine(m_pDevice, &m_pLine);

	m_pLine->SetWidth(5.f);
	m_pLine->SetAntialias(TRUE);
	m_pLine->Begin();

	D3DXVECTOR3 vLinePosX[2] = {D3DXVECTOR3(-0.01f, 0.f, 0.f), D3DXVECTOR3(10.f, 0.f, 0.f)};
	m_pLine->DrawTransform(vLinePosX, 2, &matWorld, 0xff0000ff);

	m_pLine->End();
	m_pLine->Release();

	D3DXCreateLine(m_pDevice, &m_pLine);
	m_pLine->SetWidth(5.f);
	m_pLine->SetAntialias(TRUE);
	m_pLine->Begin();

	D3DXVECTOR3 vLinePosY[2] = {D3DXVECTOR3(0.f, -0.01f, 0.f), D3DXVECTOR3(0.f, 10.f, 0.f)};
	m_pLine->DrawTransform(vLinePosY, 2, &matWorld, 0xffff0000);

	m_pLine->End();
	m_pLine->Release();

	D3DXCreateLine(m_pDevice, &m_pLine);
	m_pLine->SetWidth(5.f);
	m_pLine->SetAntialias(TRUE);
	m_pLine->Begin();

	D3DXVECTOR3 vLinePosZ[2] = {D3DXVECTOR3(0.f, 0.f, -0.01f), D3DXVECTOR3(0.f, 0.f, 10.f)};
	m_pLine->DrawTransform(vLinePosZ, 2, &matWorld, 0xff00ff00);

	m_pLine->End();
	m_pLine->Release();
}

void CObjBack::AddObject( wstring wstrTetureKey, D3DXVECTOR3 vScale, D3DXVECTOR3 vPos)
{
	Engine::CComponent*		pResources = NULL;

	pResources = Engine::CCubeCol::Create(m_pDevice);

	m_pBuffer = dynamic_cast<Engine::CVIBuffer*>(pResources);

	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Col Cube3", pResources));	

	//Engine::CCubeCol::Create(m_pDevice, D3DXVECTOR3(pVertex[m_pIndex[i]._1].vPos.x, 0.f, 0.f))
}

HRESULT CObjBack::Initialize( void )
{
	m_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	m_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	m_pVertex = new Engine::VTXCUBE[8];
	m_pIndex = new Engine::INDEX32[12];
	

	ZeroMemory(m_fAngle, sizeof(float) * 3);
	m_fDistance = 10.f;

	D3DXMatrixIdentity(&matView);
	D3DXMatrixIdentity(&matProj);

	m_vEye = D3DXVECTOR3(0.f, 10.f, -1.f);
	m_vAt = D3DXVECTOR3(0.f, -1.f, 1.f);
	D3DXVec3Normalize(&m_vAt, &m_vAt);

	D3DXMatrixLookAtLH(&matView, &m_vEye, &m_vAt, &D3DXVECTOR3(0.f, 1.f, 0.f));

	m_pDevice->SetTransform(D3DTS_VIEW, &matView);

	// 투영행렬 함수
	D3DXMatrixPerspectiveFovLH(&matProj, 
		D3DXToRadian(45.f),					// fovY 값
		float(WINCX) / float(WINCY),		// Aspect값
		1.f,								// near 평면의 z값
		1000.f);							// far 평면의 z값

	m_pDevice->SetTransform(D3DTS_PROJECTION, &matProj);


	Engine::CResources*		pResources = NULL;
	pResources = Engine::CCubeTex::Create(m_pDevice);
	m_mapChar.insert(make_pair(L"Default", pResources));	

	pResources = NULL;
	pResources = Engine::CCubeTex::Create(m_pDevice);
	m_vecObject.push_back(pResources);


	DrawLine();



	return S_OK;
}

void CObjBack::Update( void )
{

}

void CObjBack::Render( void )
{
	if (m_dwType == 0)
	{
		for (map<wstring, Engine::CResources*>::iterator iter = m_mapChar.begin(); iter != m_mapChar.end(); ++iter)
		{
			((Engine::CVIBuffer*)(iter->second))->Render();
		}
	}
	else if (m_dwType == 1)
	{
		for (size_t i = 0; i < m_vecObject.size(); ++i)
		{
			m_vecObject[i]->Render();
		}
	}
	DrawLine();
}

CObjBack* CObjBack::Create( LPDIRECT3DDEVICE9 pDevice )
{
	CObjBack* pBack = new CObjBack(pDevice);

	if (FAILED(pBack->Initialize()))
		Engine::Safe_Delete(pBack);

	return pBack;
}

#include "stdafx.h"
#include "Background.h"
#include "RcTerrain.h"
#include "Resources.h"
#include "VIBuffer.h"
#include "Include.h"
#include "ResourceMgr.h"
#include "..\Include\MainFrm.h"
#include "..\Include\MapTab.h"

#include "Export_Function.h"
#include "Texture.h"

#include "CubeObj.h"
#include "CubeCol.h"

#include "TerrainTex.h"
#include "RcTex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CBackground::CBackground( LPDIRECT3DDEVICE9 pDevice )
: CGameObject(pDevice)
, m_pBuffer(NULL)
, m_fDistance(0)
, m_pResourceMgr(Engine::Get_ResourceMgr())
, m_iIndex(0)
, m_pVertex(NULL)
{

}

CBackground::~CBackground( void )
{
	CBackground::Release();
}


void CBackground::Release( void )
{
	list<Engine::CComponent*>::iterator iter = m_Resorceslist.begin();
	list<Engine::CComponent*>::iterator iter_end = m_Resorceslist.end();

	for(; iter != iter_end; ++iter)
	{
		if((*iter) != NULL)
			Engine::Safe_Delete((*iter));
	}

	m_pResourceMgr->DestroyInstance();
	Engine::Safe_Delete_Array(m_pVertex);
}

void CBackground::KeyCheck( void )
{
	/*if(GetAsyncKeyState('W') & 0x8000)
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
	}*/

	if(GetAsyncKeyState('Q') & 0x8000)
	{
		m_fDistance -= 1.f;
		m_vEye.y -= m_fDistance;
	}

	if(GetAsyncKeyState('E') & 0x8000)
	{
		m_fDistance += 1.f;
		m_vEye.y += m_fDistance;
	}

	if(GetAsyncKeyState('W') & 0x8000)
	{
		m_vAt.z += 5;
		m_vEye.z +=5;
	}

	if(GetAsyncKeyState('S') & 0x8000)
	{
		m_vAt.z -= 5;
		m_vEye.z -= 5;
	}

	if(GetAsyncKeyState('A') & 0x8000)
	{
		m_vAt.x -= 5;
		m_vEye.x -=5;
	}

	if(GetAsyncKeyState('D') & 0x8000)
	{
		m_vAt.x += 5;
		m_vEye.x +=5;
	}

	if(GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_fAngle[Engine::ANGLE_Y] = D3DXToRadian(-5.f);
		D3DXMATRIX matRotY;
		D3DXMatrixRotationY(&matRotY, m_fAngle[Engine::ANGLE_Y]);
		D3DXVec3TransformNormal(&m_vAt, &m_vAt, &matRotY);
		D3DXVec3Normalize(&m_vAt, &m_vAt);
		m_vEye = -m_vAt * m_fDistance;
	}

	if(GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_fAngle[Engine::ANGLE_Y] = D3DXToRadian(5.f);
		D3DXMATRIX matRotY;
		D3DXMatrixRotationY(&matRotY, m_fAngle[Engine::ANGLE_Y]);
		D3DXVec3TransformNormal(&m_vAt, &m_vAt, &matRotY);
		D3DXVec3Normalize(&m_vAt, &m_vAt);
		m_vEye = -m_vAt * m_fDistance;
	}

	if(GetAsyncKeyState(VK_UP) & 0x8000)
	{
		m_fAngle[Engine::ANGLE_X] = D3DXToRadian(5.f);
		D3DXMATRIX matAxis;
		D3DXVECTOR3 vDirX;
		D3DXVec3Cross(&vDirX, &D3DXVECTOR3(0.f, 1.f, 0.f), &m_vAt);
		D3DXMatrixRotationAxis(&matAxis, &vDirX, m_fAngle[Engine::ANGLE_X]);
		D3DXVec3TransformNormal(&m_vAt, &m_vAt, &matAxis);
		m_vEye = -m_vAt * m_fDistance;

	}

	if(GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		m_fAngle[Engine::ANGLE_X] = D3DXToRadian(-5.f);
		D3DXMATRIX matAxis;
		D3DXVECTOR3 vDirX;
		D3DXVec3Cross(&vDirX, &D3DXVECTOR3(0.f, 1.f, 0.f), &m_vAt);
		D3DXMatrixRotationAxis(&matAxis, &vDirX, m_fAngle[Engine::ANGLE_X]);
		D3DXVec3TransformNormal(&m_vAt, &m_vAt, &matAxis);
		m_vEye = -m_vAt * m_fDistance;
	}

	D3DXMatrixLookAtLH(&matView, &m_vEye, &m_vAt, &D3DXVECTOR3(0.f,1.f,0.f));
	m_pDevice->SetTransform(D3DTS_VIEW, &matView);

}

void CBackground::Picking( void )
{
	if (m_pVertex == NULL)
		return;

	POINT	pt;

	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	D3DXVECTOR3 vMouse;

	vMouse.x = (float(pt.x)  / (WINCX / 2) - 1.f) / matProj._11;
	vMouse.y = (float(-pt.y) / (WINCY / 2) + 1.f) / matProj._22;
	vMouse.z = 1.f;

	D3DXVECTOR3 vRayPos, vRayDir;
	vRayPos = D3DXVECTOR3(0.f,0.f,0.f);
	vRayDir = vMouse - vRayPos;
	D3DXVec3Normalize(&vRayDir, &vRayDir);

	D3DXMATRIX matRView, matRWorld;

	D3DXMatrixInverse(&matRView, 0, &matView);
	D3DXVec3TransformCoord(&vRayPos, &vRayPos, &matRView);
	D3DXVec3TransformNormal(&vRayDir, &vRayDir, &matRView);

	D3DXMatrixIdentity(&matRWorld);
	D3DXMatrixInverse(&matRWorld, 0, &matRWorld);
	D3DXVec3TransformCoord(&vRayPos, &vRayPos, &matRWorld);
	D3DXVec3TransformNormal(&vRayDir, &vRayDir, &matRWorld);


	

	float	fU, fV, fDist;
	int VTXCNTZ = 257;
	int VTXCNTX = 257;
	int iHeight = ((CMainFrame*)AfxGetMainWnd())->m_pMainForm->m_pMap.m_iHeight;

	D3DXVECTOR3 vOut;

	for(int z = 0; z < VTXCNTZ - 1; ++z)
	{
		for(int x = 0; x < VTXCNTX - 1; ++x)
		{
			int iIndex = z * VTXCNTX + x;

			// 오른쪽 위
			if(D3DXIntersectTri(&m_pVertex[iIndex + VTXCNTX + 1].vPos,
				&m_pVertex[iIndex + VTXCNTX].vPos,
				&m_pVertex[iIndex + 1].vPos,
				&vRayPos,
				&vRayDir,
				&fU, &fV, &fDist))
			{
				m_pVertex[iIndex + VTXCNTX + 1].vPos.y = (float)iHeight;
				m_pVertex[iIndex + VTXCNTX].vPos.y = (float)iHeight;
				m_pVertex[iIndex + 1].vPos.y = (float)iHeight;

				((Engine::CVIBuffer*)m_pBuffer)->SetVtxInfo(m_pVertex);

				return;
			}

			// 왼쪽 아래
			else if(D3DXIntersectTri(&m_pVertex[iIndex].vPos,
				&m_pVertex[iIndex + 1].vPos,
				&m_pVertex[iIndex + VTXCNTX].vPos,
				&vRayPos,
				&vRayDir,
				&fU, &fV, &fDist))
			{
				m_pVertex[iIndex].vPos.y = (float)iHeight;
				m_pVertex[iIndex + 1].vPos.y = (float)iHeight;
				m_pVertex[iIndex + VTXCNTX].vPos.y = (float)iHeight;

				((Engine::CVIBuffer*)m_pBuffer)->SetVtxInfo(m_pVertex);

				return;
			}

		}
	}
	
}

void CBackground::AddTerrain( int iX, int iZ )
{
	MAPCOMPONENT::iterator iter = m_mapComponent.find(L"Tex Terrain");

	if (iter != m_mapComponent.end())
	{
		Engine::Safe_Delete(iter->second);
		m_mapComponent.erase(iter);
	}

	Engine::CComponent*		pResources = NULL;

	pResources = Engine::CTerrainTex::Create(m_pDevice, iX, iZ, 1);

	m_pBuffer = dynamic_cast<Engine::CVIBuffer*>(pResources);

	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Tex Terrain", pResources));

	m_pVertex = new Engine::VTXTEX[iX * iZ];

	((Engine::CVIBuffer*)m_pBuffer)->GetVtxInfo(m_pVertex);
}

HRESULT CBackground::Initialize( void )
{
	HRESULT hr = NULL;

	hr = m_pResourceMgr->AddTexture(m_pDevice, 
		Engine::RESOURCE_DYNAMIC, 
		Engine::TEX_NORMAL, 
		L"Texture Terrain", 
		L"../bin/Resources/Texture/Terrain/Terrain_grass%d.png", 
		2);

	hr = m_pResourceMgr->AddTexture(((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pDevice,
		Engine::RESOURCE_DYNAMIC,
		Engine::TEX_NORMAL,
		L"Tree", 
		L"../bin/Resources/Texture/Etc/tree0%d.png",
		5);

	FAILED_CHECK_MSG(hr, L"Texture Terrain Create Failed");

	m_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	//m_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

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

	DrawLine();

	Engine::CComponent*		pComponent = NULL;

	pComponent = m_pResourceMgr->CloneResource(Engine::RESOURCE_DYNAMIC, L"Texture Terrain");
	m_pTexture = dynamic_cast<Engine::CTexture*>(pComponent);
	NULL_CHECK_RETURN(m_pTexture, E_FAIL);

	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Texture", pComponent));

	return S_OK;
}

void CBackground::Update( void )
{
	
}

void CBackground::Render( void )
{

	if (m_pBuffer != NULL)
	{
		m_pTexture->Render(m_iIndex);
		m_pBuffer->Render();
		DrawLine();
	}


	list<Engine::CComponent*>::iterator iter = m_Resorceslist.begin();
	list<Engine::CComponent*>::iterator iter_end = m_Resorceslist.end();
	for(; iter != iter_end; ++iter)
	{
		if((*iter) != NULL)
		{
			Engine::CComponent*		pComponent = m_pResourceMgr->CloneResource(Engine::RESOURCE_DYNAMIC, ((Engine::CRcTex*)(*iter))->GetKey());
			if(pComponent == NULL)
				return;

			Engine::CTexture* m_pTexture = dynamic_cast<Engine::CTexture*>(pComponent);
	
			m_pTexture->Render(((Engine::CRcTex*)(*iter))->GetTexCount());
			((Engine::CRcTex*)(*iter))->Render();

			Engine::Safe_Delete(m_pTexture);
		}
	}
}

CBackground* CBackground::Create( LPDIRECT3DDEVICE9 pDevice )
{
	CBackground* pBack = new CBackground(pDevice);

	if (FAILED(pBack->Initialize()))
		Engine::Safe_Delete(pBack);

	return pBack;
}


void CBackground::DrawLine( void )
{
	D3DXMATRIX	matWorld;
	D3DXMatrixIdentity(&matWorld);
	matWorld = matView * matProj;

	D3DXCreateLine(m_pDevice, &m_pLine);

	m_pLine->SetWidth(5.f);
	m_pLine->SetAntialias(TRUE);
	m_pLine->Begin();

	D3DXVECTOR3 vLinePosX[2] = {D3DXVECTOR3(-0.01f, 0.f, 0.f), D3DXVECTOR3(2.f, 0.f, 0.f)};
	m_pLine->DrawTransform(vLinePosX, 2, &matWorld, 0xff0000ff);

	m_pLine->End();
	m_pLine->Release();

	D3DXCreateLine(m_pDevice, &m_pLine);
	m_pLine->SetWidth(5.f);
	m_pLine->SetAntialias(TRUE);
	m_pLine->Begin();

	D3DXVECTOR3 vLinePosY[2] = {D3DXVECTOR3(0.f, -0.01f, 0.f), D3DXVECTOR3(0.f, 2.f, 0.f)};
	m_pLine->DrawTransform(vLinePosY, 2, &matWorld, 0xffff0000);

	m_pLine->End();
	m_pLine->Release();

	D3DXCreateLine(m_pDevice, &m_pLine);
	m_pLine->SetWidth(5.f);
	m_pLine->SetAntialias(TRUE);
	m_pLine->Begin();

	D3DXVECTOR3 vLinePosZ[2] = {D3DXVECTOR3(0.f, 0.f, -0.01f), D3DXVECTOR3(0.f, 0.f, 2.f)};
	m_pLine->DrawTransform(vLinePosZ, 2, &matWorld, 0xff00ff00);

	m_pLine->End();
	m_pLine->Release();
}


void CBackground::Picking_AddObject(void)
{
//
	if (m_pVertex == NULL)
		return;

	POINT	pt;

	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	D3DXVECTOR3 vMouse;

	vMouse.x = (float(pt.x)  / (WINCX / 2) - 1.f) / matProj._11;
	vMouse.y = (float(-pt.y) / (WINCY / 2) + 1.f) / matProj._22;
	vMouse.z = 1.f;

	D3DXVECTOR3 vRayPos, vRayDir;
	vRayPos = D3DXVECTOR3(0.f,0.f,0.f);
	vRayDir = vMouse - vRayPos;
	D3DXVec3Normalize(&vRayDir, &vRayDir);

	D3DXMATRIX matRView, matRWorld;

	D3DXMatrixInverse(&matRView, 0, &matView);
	D3DXVec3TransformCoord(&vRayPos, &vRayPos, &matRView);
	D3DXVec3TransformNormal(&vRayDir, &vRayDir, &matRView);

	D3DXMatrixIdentity(&matRWorld);
	D3DXMatrixInverse(&matRWorld, 0, &matRWorld);
	D3DXVec3TransformCoord(&vRayPos, &vRayPos, &matRWorld);
	D3DXVec3TransformNormal(&vRayDir, &vRayDir, &matRWorld);




	float	fU, fV, fDist;
	int VTXCNTZ = 257;
	int VTXCNTX = 257;
	int iHeight = ((CMainFrame*)AfxGetMainWnd())->m_pMainForm->m_pMap.m_iHeight;

	D3DXVECTOR3 vOut;

	for(int z = 0; z < VTXCNTZ - 1; ++z)
	{
		for(int x = 0; x < VTXCNTX - 1; ++x)
		{
			int iIndex = z * VTXCNTX + x;

			// 오른쪽 위
			if(D3DXIntersectTri(&m_pVertex[iIndex + VTXCNTX + 1].vPos,
				&m_pVertex[iIndex + VTXCNTX].vPos,
				&m_pVertex[iIndex + 1].vPos,
				&vRayPos,
				&vRayDir,
				&fU, &fV, &fDist))
			{
				D3DXPLANE	plnPlane;

				D3DXPlaneFromPoints(&plnPlane,
					&m_pVertex[iIndex + VTXCNTX].vPos,
					&m_pVertex[iIndex + VTXCNTX + 1].vPos,
					&m_pVertex[iIndex + 1].vPos);

				float fX = m_pVertex[iIndex + VTXCNTX + 1].vPos.x - fU;
				float z = m_pVertex[iIndex + VTXCNTX + 1].vPos.z - fV;
				float fHeight = (-plnPlane.a * x - plnPlane.c * z - plnPlane.d) / plnPlane.b;
				D3DXVECTOR3 vObjectPos = D3DXVECTOR3((float)x, (float)fHeight + 1.f, (float)z);

				AddObject(vObjectPos);

				return;
			}

			// 왼쪽 아래
			else if(D3DXIntersectTri(&m_pVertex[iIndex].vPos,
				&m_pVertex[iIndex + 1].vPos,
				&m_pVertex[iIndex + VTXCNTX].vPos,
				&vRayPos,
				&vRayDir,
				&fU, &fV, &fDist))
			{
				D3DXPLANE	plnPlane;

				D3DXPlaneFromPoints(&plnPlane,
					&m_pVertex[iIndex + VTXCNTX].vPos,
					&m_pVertex[iIndex + 1].vPos,
					&m_pVertex[iIndex].vPos);

				float x = m_pVertex[iIndex].vPos.x + fU;
				float z = m_pVertex[iIndex].vPos.z + fV;
				float fHeight = (-plnPlane.a * x - plnPlane.c * z - plnPlane.d) / plnPlane.b;

				D3DXVECTOR3 vObjectPos = D3DXVECTOR3(x, fHeight + 1.f, z);

				AddObject(vObjectPos);

				return;
			}

		}
	}
}

list<Engine::OBJINFO>* CBackground::GetObjList(void)
{
	return &m_ObjList;
}

void CBackground::SetIndex( int iIndex )
{
	m_iIndex = iIndex;
}

Engine::VTXTEX* CBackground::GetVtxcol( void )
{
	return m_pVertex;
}

void CBackground::SetVtxcol( Engine::VTXTEX* pVertex )
{
	memcpy(m_pVertex, pVertex, sizeof(Engine::VTXTEX) * (257*257));
}

void CBackground::AddObject(D3DXVECTOR3 &vPos)
{
	Engine::CComponent*		pComponent = NULL;

	int i = rand() % 5;
	pComponent = Engine::CRcTex::Create(m_pDevice, L"Tree", vPos, i);
	m_Resorceslist.push_back(dynamic_cast<Engine::CVIBuffer*>(pComponent));
	Engine::OBJINFO tObjInfo;
	tObjInfo.iTexCount = i;
	tObjInfo.wstrTexKey = L"Tree";
	tObjInfo.vPos = vPos;
	m_ObjList.push_back(tObjInfo);
}

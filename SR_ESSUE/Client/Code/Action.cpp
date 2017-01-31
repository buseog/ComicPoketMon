#include "stdafx.h"
#include "Action.h"
#include "MathMgr.h"
#include "Pipeline.h"
#include "GameObject.h"
#include "Transform.h"
#include "TerrainCol.h"
#include "TimeMgr.h"
#include "Export_Function.h"


CAction::CAction( Engine::CGameObject* pGameObj )
: m_pGameObj(pGameObj)
, m_pTransform(NULL)
, m_pTerrainCol(NULL)
, m_fGravity(0.98f)
, m_fStartEnergy(20.f)
, m_fAcceleration(0.f)
, m_pTimeMgr(Engine::Get_TimeMgr())
, m_fTime(m_pTimeMgr->GetTime())
, m_bJump(false)
, m_bFall(false)
, m_bJumpStart(false)
{
	m_pTransform = m_pGameObj->GetComponent(L"Transform");
	m_pTerrainCol = m_pGameObj->GetComponent(L"TerrainCol");
}

void CAction::JumpMove( void )
{
	if(m_bFall)
		return;

	m_fTime = m_pTimeMgr->GetTime();
 	m_bJump = true;
	m_bJumpStart = true;
	((Engine::CTransform*)m_pTransform)->vPos.y += m_fStartEnergy * m_fTime;

}

void CAction::Attack( void )
{

}

void CAction::Update( void )
{
	m_fTime = m_pTimeMgr->GetTime();

	if(((CTerrainCol*)m_pTerrainCol)->GetColTerrainStat())
	{
		m_bFall = false;
		m_bJump = false;
	}
	else
		m_bFall = true;
	
	if(m_bJump)
	{
		if(!m_bJumpStart)
		((Engine::CTransform*)m_pTransform)->vPos.y += m_fStartEnergy * m_fTime;// + m_fAcceleration;

		m_bJumpStart = false;
	}
	if(m_bFall)
	{
		m_fAcceleration += m_fGravity * m_fTime;
		((Engine::CTransform*)m_pTransform)->vPos.y -= m_fAcceleration;
	}
	else
	{
		m_fAcceleration = 0.f;
	}
}

CAction* CAction::Create( Engine::CGameObject* pGameObj )
{
	CAction* pAction = new CAction(pGameObj);

	return pAction;
}

CAction::~CAction( void )
{

}

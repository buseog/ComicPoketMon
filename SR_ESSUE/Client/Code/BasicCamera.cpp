#include "StdAfx.h"
#include "BasicCamera.h"

CAMID CBasicCamera::m_eCamType = CAM_STATIC;

CBasicCamera::CBasicCamera(LPDIRECT3DDEVICE9 pDevice)
: CCamera(pDevice)
{

}

CBasicCamera::~CBasicCamera(void)
{
}

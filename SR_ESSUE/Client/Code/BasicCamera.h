/*!
 * \file BasicCamera.h
 * \date 2017/01/22 22:32
 *
 * \author Administrator
 * Contact: user@company.com
 *
 * \brief ī�޶���� �θ� �� Ŭ����
 *
 * TODO: long description
 *
 * \note
*/

#ifndef BasicCamera_h__
#define BasicCamera_h__

#include "Camera.h"

// �Ŵ���
#include "Export_Function.h"
#include "TimeMgr.h"
#include "ZFrustum.h"
#include "Include.h"

// ������Ʈ
#include "Transform.h"
#include "InfoSubject.h"

class CBasicCamera
	: public Engine::CCamera
{
public:
	static CAMID m_eCamType;

protected:
	explicit CBasicCamera(LPDIRECT3DDEVICE9 pDevice);

public:
	virtual ~CBasicCamera(void);
};

#endif // BasicCamera_h__
/*!
 * \file Logo.h
 * \date 2017/01/15 21:57
 *
 * \author ESSUE
 * Contact: user@company.com
 *
 * \brief ���� ������ �ʿ��� ���ҽ����� �ҷ����� �ε���
 *
 * TODO: long description
 *
 * \note �����带 �̿��� ���ȭ�� + ��������� Ʋ����� �� ���ȿ� ���ҽ��� �ҷ����� �۾����Ѵ�.
*/

#ifndef Logo_h__
#define Logo_h__

#include "Scene.h"

namespace Engine
{
	class CManagement;
	class CResourceMgr;
}

class CLogo
	: public Engine::CScene
{
public:
	enum LAYERID { LAYER_ENVIRONMENT, LAYER_GAMELOGIC, LAYER_UI };

private:
	Engine::CManagement*		m_pManagement;
	Engine::CResourceMgr*		m_pResourceMgr;

private:
	HANDLE				m_hThread;
	CRITICAL_SECTION	m_Crt;
	HWND				m_hVideo;
	float				m_fCount;
	float				m_fMaxCount;

public:
	static unsigned int __stdcall ImgLoadThreadFunc(void* pArg);
	CRITICAL_SECTION	GetCrt(void);
	LPDIRECT3DDEVICE9	GetDevice(void);

private:
	HRESULT		Add_Environment_Layer(void);
	HRESULT		Add_GameLogic_Layer(void);
	void		Release(void);

public:
	virtual HRESULT InitScene(void);
	virtual void Update(void);
	virtual void Render(void);

public:
	static CLogo*	Create(LPDIRECT3DDEVICE9 pDevice);

private:
	explicit CLogo(LPDIRECT3DDEVICE9 pDevice);

public:
	virtual ~CLogo(void);

};


#endif // Logo_h__

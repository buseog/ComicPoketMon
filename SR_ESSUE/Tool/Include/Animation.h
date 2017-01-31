#pragma once
#include "afxwin.h"


// CAnimation ��ȭ �����Դϴ�.

#include "Engine_Include.h"

namespace Engine
{
	class CCubeObj;
	class CCubeMotion;
}

class CAnimation : public CDialog
{
	DECLARE_DYNAMIC(CAnimation)

public:
	CAnimation(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CAnimation();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ANIMATION };

public:
	Engine::CCubeObj*									m_pCUbeObj;
	Engine::CCubeMotion*								m_pCubeMotion;


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	bool	m_bPlay;
	DWORD	m_dwFrame;
	DWORD	m_dwMaxFrame;

	CListBox m_StateListCtrl;
	CListBox m_FrameListCtrl;
	CComboBox m_StateComboCtrl;

	afx_msg void OnUp();

	afx_msg void OnFrameAdd();
	afx_msg void OnFrameDelete();
	afx_msg void OnStateComboCtrl();
	afx_msg void OnSave();
	
	virtual BOOL OnInitDialog();
	
	afx_msg void OnStateList();
	afx_msg void OnPlay();
	afx_msg void OnStop();
	afx_msg void OnDown();
	afx_msg void OnLoad();
	afx_msg void OnFrameList();

	afx_msg void OnTimer(UINT nIDEvent);
	void	PlayAnimation(void);

	afx_msg void OnArrange();
};


// ToolView.cpp : CToolView Ŭ������ ����
//

#include "stdafx.h"
#include "Tool.h"

#include "ToolDoc.h"
#include "ToolView.h"
#include "MainFrm.h"

#include "Background.h"
#include "ObjBack.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "Export_Function.h"

// CToolView

IMPLEMENT_DYNCREATE(CToolView, CScrollView)

BEGIN_MESSAGE_MAP(CToolView, CScrollView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CToolView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CToolView ����/�Ҹ�

HWND g_hWnd;

CToolView::CToolView()
: m_pGraphicDev(Engine::Get_GraphicDev())
, m_pDevice(NULL)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	for(int i = 0; i< BK_END; ++i)
		m_pBackground[i] = NULL;
}

CToolView::~CToolView()
{
	
}

BOOL CToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CToolView �׸���

void CToolView::OnDraw(CDC* /*pDC*/)
{
	CToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	m_pDevice->Clear(0,0,D3DCLEAR_STENCIL | D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(255,0,0,0),1.f,0);
	m_pDevice->BeginScene();

	switch(m_eBACK)
	{
	case BK_MAP:
		((CBackground*)m_pBackground[BK_MAP])->Render();
		break;

	case BK_OBJ:
		((CBackground*)m_pBackground[BK_MAP])->Render();
		break;

	case BK_UNIT:
		((CObjBack*)m_pBackground[BK_UNIT])->Render();
		break;
	}

	m_pDevice->EndScene();
	m_pDevice->Present(NULL,NULL,NULL,NULL);

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}


// CToolView �μ�


void CToolView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}

void CToolView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CToolView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CToolView ����

#ifdef _DEBUG
void CToolView::AssertValid() const
{
	CView::AssertValid();
}

void CToolView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Engine::CGameObject* CToolView::GetBackground( BACKID eBack )
{
	return m_pBackground[eBack];
}

void CToolView::SetBack( BACKID eBack )
{
	switch(eBack)
	{
	case BK_MAP:
		if(m_pBackground[eBack] == NULL)
		{
			m_pBackground[BK_MAP]  = CBackground::Create(m_pDevice);
			m_pBackground[BK_MAP]->Initialize();
		}
		m_eBACK = eBack;
		break;

	case BK_UNIT:
		if(m_pBackground[eBack] == NULL)
		{
			m_pBackground[BK_UNIT]  = CObjBack::Create(m_pDevice);
			m_pBackground[BK_UNIT]->Initialize();
		}
		m_eBACK = eBack;
		break;
	}
}

CToolDoc* CToolView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CToolDoc)));
	return (CToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CToolView �޽��� ó����

void CToolView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
	m_eBACK = BK_MAP;
	SetScrollSizes(MM_TEXT, CSize(129 * 129, (129 / 2) * 129));

	g_hWnd = m_hWnd;

	CMainFrame*		pMainFrm = ((CMainFrame*)AfxGetMainWnd());

	RECT		rcWindow;
	pMainFrm->GetWindowRect(&rcWindow);


	SetRect(&rcWindow, 0, 0, rcWindow.right - rcWindow.left, rcWindow.bottom - rcWindow.top);

	RECT		rcMainView;
	GetClientRect(&rcMainView);

	float		fRowFrm = float(rcWindow.right - rcMainView.right);
	float		fColFrm = float(rcWindow.bottom - rcMainView.bottom);

	pMainFrm->SetWindowPos(NULL, 400, 100, int(WINCX + fRowFrm), int(WINCY + fColFrm), SWP_NOZORDER);

	Engine::CGraphicDev::GetInstance()->InitGraphicDev
		(Engine::CGraphicDev::MODE_WIN, g_hWnd, WINCX, WINCY);

	m_pDevice = m_pGraphicDev->GetDevice();

	CBackground* pBack = CBackground::Create(m_pDevice);
	
	m_pBackground[BK_MAP]  = dynamic_cast<Engine::CGameObject*>(pBack);

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
}

void CToolView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	switch(m_eBACK)
	{
	case BK_MAP:
		((CBackground*)m_pBackground[m_eBACK])->KeyCheck();
		break;


	case BK_UNIT:
		((CObjBack*)m_pBackground[m_eBACK])->KeyCheck();
		break;
	}
	

	Invalidate(FALSE);

	CScrollView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CToolView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	switch(m_eBACK)
	{
	case BK_MAP:
		((CBackground*)m_pBackground[m_eBACK])->Picking();
		break;

	case BK_UNIT:
		switch (((CMainFrame*)AfxGetMainWnd())->m_pMainForm->m_pUnit.m_iActionRadio)
		{
		case 0:
			((CObjBack*)m_pBackground[m_eBACK])->AddPicking();
			break;
		case 1:
			((CObjBack*)m_pBackground[m_eBACK])->DeletePicking();
			break;
		case 2:
			((CObjBack*)m_pBackground[m_eBACK])->SelectPicking();
			break;
		}
		break;
	}
	Invalidate(FALSE);

	CScrollView::OnLButtonDown(nFlags, point);

}

void CToolView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	if (GetAsyncKeyState(VK_LBUTTON))
		OnLButtonDown(nFlags, point);

	CScrollView::OnMouseMove(nFlags, point);
}

void CToolView::OnDestroy()
{
	CScrollView::OnDestroy();

	m_pGraphicDev->GetInstance()->DestroyInstance();

	for(int i = 0; i < BK_END; ++i)
	{
		if(m_pBackground[i] != NULL)
			Engine::Safe_Delete(m_pBackground[i]);
	}

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}

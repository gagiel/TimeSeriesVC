// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "TimeSeriesVC.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_UPDATE_COMMAND_UI(IDC_XTOTAL, OnUpdateXtotal)
	ON_UPDATE_COMMAND_UI(IDC_YTOTAL, OnUpdateYtotal)
	ON_UPDATE_COMMAND_UI(IDC_AUTOMATIC, OnUpdateAutomatic)
	ON_UPDATE_COMMAND_UI(IDC_HANDCRAFT, OnUpdateHandcraft)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	// ID_INDICATOR_CAPS,
	// ID_INDICATOR_NUM,
	// ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	xchecked = ychecked = false;
	width = 1000;
	height = 640; // easy to split
	method = TRUE;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndStatusBar.Create(this, WS_CHILD | WS_VISIBLE | CBRS_BOTTOM, ID_NEW_STATUS_BAR) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.lpszName = "分布式数据库-2010 年秋季学期期中作业-时间序列相关性分析-THINK-高等";
	cs.style = WS_OVERLAPPED | WS_SYSMENU | WS_BORDER;		// | FWS_ADDTOTITLE is so disgusting.

	cs.cy = height;
	cs.cx = width;
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


void CMainFrame::OnUpdateXtotal(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(xchecked);
	pCmdUI->Enable(TRUE);

	TRACE ("OnUpdateXTotal\n");
}

void CMainFrame::OnUpdateYtotal(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(ychecked);
	pCmdUI->Enable(TRUE);

	TRACE ("OnUpdateYTotal\n");	
}

void CMainFrame::OnUpdateAutomatic(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnUpdateHandcraft(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(TRUE);

}

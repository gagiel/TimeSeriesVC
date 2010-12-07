// TimeSeriesVCView.cpp : implementation of the CTimeSeriesVCView class
//

#include "stdafx.h"
#include "TimeSeriesVC.h"

#include "TimeSeriesVCDoc.h"
#include "TimeSeriesVCView.h"

#include "MainFrm.h"


#include <string>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTimeSeriesVCView

IMPLEMENT_DYNCREATE(CTimeSeriesVCView, CView)

BEGIN_MESSAGE_MAP(CTimeSeriesVCView, CView)
	//{{AFX_MSG_MAP(CTimeSeriesVCView)
	ON_WM_MOUSEMOVE()
	ON_WM_CANCELMODE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTimeSeriesVCView construction/destruction

CTimeSeriesVCView::CTimeSeriesVCView()
{
	// TODO: add construction code here
	//memset(lag, 0, sizeof(lag));	// I couldn't find zero func, so it's stupid using memset.
	//memset(relate, 0,sizeof(relate));	// maybe i should use posix bzero?

	handcraft = 0;
	
	cluex = cluey = 0;
	newrect = oldrect = CRect(NULL);
}

CTimeSeriesVCView::~CTimeSeriesVCView()
{
}

BOOL CTimeSeriesVCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here y modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CTimeSeriesVCView drawing

void CTimeSeriesVCView::OnDraw(CDC* pDC)
{

	CTimeSeriesVCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	TRACE("CTimeSeriesVCView::OnDraw\n");


	CString str;
	char status[2048];

	// memcpy (lag, pDoc->lag, sizeof(lag));		// really stupid but i cannot find better writings.
	// memcpy (relate, pDoc->relate, sizeof(relate));	// as it is.

	handcraft = pDoc->handcraft;
	// TODO: add draw code for native data here
	
	for (int i=0;i<3;i++) {			// split the view
		pDC->MoveTo(0, (i+1) * 512 / 4);
		pDC->LineTo(1000, (i+1) * 512 /4);
	}

	DrawXaxis(pDC) || pDC->TextOut(0, 0, "X_Total Needed");
	DrawYaxis(pDC) || pDC->TextOut(0, 128, "Y_Total Needed");;

	if(handcraft==1)	{	// aha, it's auto.
		if (pDoc->progress < 700) {

			CPen penBlack;  // Construct it, then initialize
			if( penBlack.CreatePen( PS_SOLID, 2, RGB(0,0,255) ) )	{
				// Select it into the device context
				// Save the old pen at the same time
				CPen* pOldPen = pDC->SelectObject( &penBlack );

				// Draw with the pen
				pDC->SelectStockObject(NULL_BRUSH);
				pDC->Rectangle(pDoc->progress, 0, pDoc->progress+300, 256);	// still magic number~
				pDC->SelectStockObject(GRAY_BRUSH);			// restore the brush

				// Restore the old pen to the device context
				pDC->SelectObject( pOldPen );
			}
			else {
				MessageBox("OOPS", "CPen", MB_OK);
			// Alert the user that resources are low
			}

		
		}
	
		float min,max;
		int   point;
		
		min=Min(pDoc->lag, pDoc->progress+1);
		max=Max(pDoc->lag, pDoc->progress+1);

		pDC->MoveTo(0,384);

		for(int i=0; i<pDoc->progress; i++)
		{
			point = (pDoc->lag[i]-min)*90/(max-min);		// magic number~
			pDC->LineTo(i,384-point);
		}
		pDC->TextOut(50,20+128*2,"相关系数最大值");		// tired of magic number~

		min=Min(pDoc->relate, pDoc->progress+1);
		max=Max(pDoc->relate, pDoc->progress+1);

		pDC->MoveTo(0,512);

		for(i=0; i<pDoc->progress; i++)
		{
			point = (pDoc->relate[i]-min)*90/(max-min);		// magic number~
			pDC->LineTo(i,512-point);
		}
		pDC->TextOut(50,20+128*3,"延迟lag");

				
		CStatusBar * pStatus=(CStatusBar*) AfxGetApp()->m_pMainWnd->GetDescendantWindow(ID_NEW_STATUS_BAR);
		ASSERT_VALID(pStatus);

		wsprintf (status, 
			"时间序列X_Total长度=1000, 时间序列Y_Total长度=1000  当前已经计算: %d%%", 
			pDoc->progress/7);

		pStatus->SetPaneText(0, status, TRUE);
	}
	

	else if(handcraft==2) {			// handy
		TRACE("OnDraw handcraft\n");

		pDC->SelectStockObject(NULL_BRUSH);
		pDC->Rectangle(oldrect);
		pDC->SelectStockObject(GRAY_BRUSH);			// restore the brush

		pDoc->ComputeFormula(cluex);


		str.Format("滑动窗口当前位置locate=%d,  相关系数最大值r_max=%f, 延迟lag=%f",
			cluex, pDoc->relate[cluex], pDoc->lag[cluex]);		
		
		CStatusBar * pStatus=(CStatusBar*) AfxGetApp()->m_pMainWnd->GetDescendantWindow(ID_NEW_STATUS_BAR);
		ASSERT_VALID(pStatus);

		wsprintf (status, "%s", str);

		pStatus->SetPaneText(0, status, TRUE);

	}
	else if(handcraft==0) {
		// nothing
	}
	else {
		MessageBox("What the hell?", "WARNING", MB_OK);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CTimeSeriesVCView diagnostics

#ifdef _DEBUG
void CTimeSeriesVCView::AssertValid() const
{
	CView::AssertValid();
}

void CTimeSeriesVCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTimeSeriesVCDoc* CTimeSeriesVCView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTimeSeriesVCDoc)));
	return (CTimeSeriesVCDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTimeSeriesVCView message handlers

void CTimeSeriesVCView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TRACE("CTimeSeriesVCView::OnMouseMove\n");

	// TODO: Add your message handler code here and/or call default
	// char text[1024];

	// Nice idiom to get parent wnd
	CStatusBar * pStatus=(CStatusBar*) AfxGetApp()->m_pMainWnd->GetDescendantWindow(ID_NEW_STATUS_BAR);
	ASSERT_VALID(pStatus);

	// wsprintf (text, "滑动窗口当前位置 locate = %d， mouse_y = %d", point.x, point.y);
	// wsprintf (text, "滑动窗口当前位置 locate = %d，相关系数最大值 r_max= %f，延迟 lag = %f，mouse_y = %d", 
	//	point.x, lag[point.x], relate[point.x], point.y);
	// pStatus->SetPaneText(0, text, TRUE);
	// wsprintf (text, "mouse_y = %d cluey = %d", , cluey);
	// pStatus->SetPaneText(1, text, TRUE);

	if(handcraft==2) {		
		CRect invalidRect;
		oldrect = CRect(cluex, 0, cluex+300, 256);

		cluex=point.x<700?point.x:700;

		newrect = CRect(cluex, 0, cluex+300, 256);
		invalidRect.UnionRect(oldrect, newrect);
		InvalidateRect(invalidRect, TRUE);
		
		// Invalidate(TRUE);
		oldrect = newrect;


		// cluex=point.x<700?point.x:700;
		// cluey=point.x<700?point.x:700;
	}

	CView::OnMouseMove(nFlags, point);
}

void CTimeSeriesVCView::OnCancelMode() 
{
	CView::OnCancelMode();
	
	// TODO: Add your message handler code here
	
}

double CTimeSeriesVCView::Min(double *n, int length)
{
	double min=65535.0;		// shit, i can get a pre-define from vc6.
	for(int i=0; i<length; i++) {
		min>n[i]?min=n[i]:false;
	}
	min>=65535.0?MessageBox("min() warning", "WARNING", MB_OK):false;
	return min;
}


double CTimeSeriesVCView::Max(double *n, int length)
{
	double max=-65535.0;		// shit, i can get a pre-define from vc6.
	for(int i=0; i<length; i++) {
		max<n[i]?max=n[i]:false;
	}
	max<=-65535.0?MessageBox("max() warning", "WARNING", MB_OK):false;
	return max;
}

BOOL CTimeSeriesVCView::DrawXaxis(CDC *pDC)
{
	CTimeSeriesVCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if(pDoc->Redrawx)	// ready to draw x~
	{
		TRACE("CTimeSeriesVCView::OnDraw pDoc->Redrawx\n");
		double min,max;
		int point;
		
		min=Min(pDoc->x, 1000);
		max=Max(pDoc->x, 1000);
	
		pDC->MoveTo(0,0);

		for(int i=0; i<1000 ; i++)
		{
			point = (pDoc->x[i]-min)*90/(max-min);		// magic number~
			pDC->LineTo(i,128-point);
		}
		pDC->TextOut(50,20,"时间序列 X_Total");
		return true;
	}
	return false;
}

BOOL CTimeSeriesVCView::DrawYaxis(CDC *pDC)
{	
	CTimeSeriesVCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if(pDoc->Redrawy)	// ready to draw y~
	{
		TRACE("CTimeSeriesVCView::OnDraw pDoc->Redrawy\n");
		double min,max;
		int point;
		
		min=Min(pDoc->y, 1000);
		max=Max(pDoc->y, 1000);
	
		pDC->MoveTo(0,128);

		for(int i=0; i<1000 ; i++)
		{
			point = (pDoc->y[i]-min)*90/(max-min);		// magic number~
			pDC->LineTo(i, 256-point);
		}
		pDC->TextOut(50,20+128,"时间序列 Y_Total");

		return true;
	}
	return false;
}

//DEL BOOL CTimeSeriesVCView::DrawAuto(CDC *pDC)
//DEL {
//DEL 	CTimeSeriesVCDoc* pDoc = GetDocument();
//DEL 	ASSERT_VALID(pDoc);
//DEL 
//DEL 	return true;
//DEL }

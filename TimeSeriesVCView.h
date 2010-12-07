// TimeSeriesVCView.h : interface of the CTimeSeriesVCView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TIMESERIESVCVIEW_H__76639B3E_5FEA_4182_B5F2_540E19F5B9E4__INCLUDED_)
#define AFX_TIMESERIESVCVIEW_H__76639B3E_5FEA_4182_B5F2_540E19F5B9E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CTimeSeriesVCView : public CView
{
protected: // create from serialization only
	CTimeSeriesVCView();
	DECLARE_DYNCREATE(CTimeSeriesVCView)

// Attributes
public:
	CTimeSeriesVCDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTimeSeriesVCView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL DrawYaxis(CDC *pDC);
	BOOL DrawXaxis(CDC *pDC);
	double Min(double * n, int length);		// vc6 is a shit to require CAPS on func
	double Max(double * n, int length);
	BOOL handcraft;
	CRect newrect;
	CRect oldrect;
	int cluex;
	int cluey;
//	double relate[1000];
//	double lag[1000];
	virtual ~CTimeSeriesVCView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTimeSeriesVCView)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnCancelMode();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in TimeSeriesVCView.cpp
inline CTimeSeriesVCDoc* CTimeSeriesVCView::GetDocument()
   { return (CTimeSeriesVCDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TIMESERIESVCVIEW_H__76639B3E_5FEA_4182_B5F2_540E19F5B9E4__INCLUDED_)

// TimeSeriesVC.h : main header file for the TIMESERIESVC application
//

#if !defined(AFX_TIMESERIESVC_H__8FB0B3F8_2B19_4D4C_B0B5_A3EAB08AA191__INCLUDED_)
#define AFX_TIMESERIESVC_H__8FB0B3F8_2B19_4D4C_B0B5_A3EAB08AA191__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CTimeSeriesVCApp:
// See TimeSeriesVC.cpp for the implementation of this class
//

class CTimeSeriesVCApp : public CWinApp
{
public:
	CTimeSeriesVCApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTimeSeriesVCApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CTimeSeriesVCApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TIMESERIESVC_H__8FB0B3F8_2B19_4D4C_B0B5_A3EAB08AA191__INCLUDED_)

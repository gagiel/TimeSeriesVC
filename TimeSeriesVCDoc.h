// TimeSeriesVCDoc.h : interface of the CTimeSeriesVCDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TIMESERIESVCDOC_H__364D6A3F_9BE9_456C_A267_906FC6A288A4__INCLUDED_)
#define AFX_TIMESERIESVCDOC_H__364D6A3F_9BE9_456C_A267_906FC6A288A4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CTimeSeriesVCDoc : public CDocument
{
protected: // create from serialization only
	CTimeSeriesVCDoc();
	DECLARE_DYNCREATE(CTimeSeriesVCDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTimeSeriesVCDoc)
	public:
	//}}AFX_VIRTUAL

// Implementation
public:
	void ComputeFormula(int pos);
	int progress;
	double lag[1000];
	double relate[1000];
	char handcraft;
	BOOL Redrawx;
	BOOL Redrawy;
	double y[1000];		// what a shame it's hardcoded.
	double x[1000];		// same thought as above.
	void Readmy(char);
	virtual ~CTimeSeriesVCDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTimeSeriesVCDoc)
	afx_msg void OnXtotal();
	afx_msg void OnYtotal();
	afx_msg void OnHandcraft();
	afx_msg void OnAutomatic();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TIMESERIESVCDOC_H__364D6A3F_9BE9_456C_A267_906FC6A288A4__INCLUDED_)

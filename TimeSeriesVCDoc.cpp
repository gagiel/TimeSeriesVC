// TimeSeriesVCDoc.cpp : implementation of the CTimeSeriesVCDoc class
//

#include "stdafx.h"
#include "TimeSeriesVC.h"

#include "TimeSeriesVCDoc.h"

#include "MainFrm.h"	// oh shit, it's needed to visit other Timeseries classes.

#include <fstream>
#include <string>
#include <math.h>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTimeSeriesVCDoc

IMPLEMENT_DYNCREATE(CTimeSeriesVCDoc, CDocument)

BEGIN_MESSAGE_MAP(CTimeSeriesVCDoc, CDocument)
	//{{AFX_MSG_MAP(CTimeSeriesVCDoc)
	ON_COMMAND(IDC_XTOTAL, OnXtotal)
	ON_COMMAND(IDC_YTOTAL, OnYtotal)
	ON_COMMAND(IDC_HANDCRAFT, OnHandcraft)
	ON_COMMAND(IDC_AUTOMATIC, OnAutomatic)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTimeSeriesVCDoc construction/destruction

CTimeSeriesVCDoc::CTimeSeriesVCDoc()
{
	// TODO: add one-time construction code here
	Redrawx=false;
	Redrawy=false;
	memset(x,0,sizeof(x));	// I couldn't find zero func, so it's stupid using memset.
	memset(y,0,sizeof(y));	// maybe i should use posix bzero?

	progress = 0;
	handcraft = 0;

	memset(relate,0,sizeof(relate));
	memset(lag,0,sizeof(lag));
}

CTimeSeriesVCDoc::~CTimeSeriesVCDoc()
{
}

//DEL BOOL CTimeSeriesVCDoc::OnNewDocument()
//DEL {
//DEL 	if (!CDocument::OnNewDocument())
//DEL 		return FALSE;
//DEL 
//DEL 	// TODO: add reinitialization code here
//DEL 	// (SDI documents will reuse this document)
//DEL 
//DEL 	return TRUE;
//DEL }

/////////////////////////////////////////////////////////////////////////////
// CTimeSeriesVCDoc commands

//DEL double CTimeSeriesVCDoc::Rfunc(const int linear) {	// actually it's l for long
//DEL 	double r;
//DEL 	int i;
//DEL 	//int linear;		// which is t, lower bound.
//DEL 	double xsum, avg_x, avg_y, ysum, lower1, lower2, upper;
//DEL 	const int LINES = 300+linear;		// which is n, upper bound. 300 seems to fit in by homework.
//DEL 	for (i=(linear+1)-1;i<LINES;i++) {
//DEL 				xsum += x[i];
//DEL 				}
//DEL 	avg_x = xsum / (LINES - linear);		// get avg of x
//DEL 	
//DEL 	for (i=(1)-1;i<LINES - linear;i++) {
//DEL 				ysum += y[i];
//DEL 				}
//DEL 	avg_y = ysum / (LINES - linear);	// get avg of y
//DEL 
//DEL 	for (i=(linear+1)-1;i<LINES;i++) {
//DEL 		upper += (x[i]-avg_x)*(y[i-linear]-avg_y);
//DEL 		}
//DEL 
//DEL 	for (i=(linear+1)-1;i<LINES;i++) {
//DEL 		lower1 += (x[i]-avg_x)*(x[i]-avg_x);
//DEL 		}
//DEL 
//DEL 	for (i=(1)-1;i<LINES-linear;i++) {
//DEL 		lower2 += (y[i]-avg_y)*(y[i]-avg_y);
//DEL 		}
//DEL 	lower1 = sqrt(lower1);
//DEL 	lower2 = sqrt(lower2);
//DEL 
//DEL 	TRACE("%f / %f * %f\n", upper, lower1, lower2);
//DEL 	r = upper/lower1/lower2;	// done.
//DEL 
//DEL 	return r;		// funny thing is that i wrote this func under linux. 
//DEL }

/////////////////////////////////////////////////////////////////////////////
// CTimeSeriesVCDoc serialization

//DEL void CTimeSeriesVCDoc::Serialize(CArchive& ar)
//DEL {
//DEL 	if (ar.IsStoring())
//DEL 	{
//DEL 		// TODO: add storing code here
//DEL 	}
//DEL 	else
//DEL 	{
//DEL 		// TODO: add loading code here
//DEL 	}
//DEL }

/////////////////////////////////////////////////////////////////////////////
// CTimeSeriesVCDoc diagnostics

#ifdef _DEBUG
void CTimeSeriesVCDoc::AssertValid() const
{
	CDocument::AssertValid();
}

//DEL void CTimeSeriesVCDoc::Dump(CDumpContext& dc) const
//DEL {
//DEL 	CDocument::Dump(dc);
//DEL }
#endif //_DEBUG

void CTimeSeriesVCDoc::OnXtotal() 
{
	// TODO: Add your command handler code here
	Readmy('x');
	this->UpdateAllViews(NULL);		// Call ondraw
}

void CTimeSeriesVCDoc::OnYtotal() 
{
	// TODO: Add your command handler code here
	Readmy('y');
	this->UpdateAllViews(NULL);		// Call ondraw
}

void CTimeSeriesVCDoc::Readmy(char type)	// Hope it can be for more.
{
    CString FilePath;
	string first;
	double second, third;
	CFileDialog Filedlg(TRUE,NULL,NULL,OFN_READONLY | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST, 
		"时间序列文件(*.txt)|*.txt||",NULL);	// strange huh? see msdn for that || shit.
	Filedlg.m_ofn.lpstrTitle = "打开时间序列文件";

	if(Filedlg.DoModal() == IDOK)
	{
		FilePath = Filedlg.GetFileName();
	}
	else 
	{
		MessageBox(NULL, "未读入", "没有选择文件", MB_OK);
		return;
	}

	ifstream TxtDataInput((LPCTSTR)FilePath,ios::in);
	
	if(type=='x')
	{
		TRACE("x reading\n");
		for(int i=0; i<1000; i++)
		{
			TxtDataInput>>first>>second>>third;
			x[i] = third;
			getline(TxtDataInput,first);	// dump others
		}
		Redrawx=true;

		CMainFrame * pActiveFrame;    // don't ask me. I got it from msdn.
		pActiveFrame = (CMainFrame*) AfxGetMainWnd();
		pActiveFrame->xchecked = Redrawx;		// pass checked sign to menu

	}
	if(type=='y')
	{
		TRACE("y reading\n");
		for(int i=0; i<1000; i++)
		{
			TxtDataInput>>first>>second>>third;
			y[i] = third;
			getline(TxtDataInput,first);	// dump others
		}
		Redrawy=true;

		CMainFrame * pActiveFrame;    // don't ask me. I got it from msdn.
		pActiveFrame = (CMainFrame*) AfxGetMainWnd();
		pActiveFrame->ychecked = Redrawy;

	}
	TxtDataInput.close();

	return;
}

void CTimeSeriesVCDoc::OnHandcraft() 
{
	TRACE("CTimeSeriesVCDoc::OnHandcraft\n");
	// TODO: Add your command handler code here
	if(!(Redrawx && Redrawy)) {
		Redrawx? true: MessageBox(NULL, "尚未读入 X 序列", "错误", MB_OK);	// nice show
		Redrawy? true: MessageBox(NULL, "尚未读入 Y 序列", "错误", MB_OK);	// but hard to understand...
		return;
	}
	handcraft = 2;		// means handy
	this->UpdateAllViews(NULL);		// Call ondraw
}

void CTimeSeriesVCDoc::OnAutomatic() 
{
	TRACE("CTimeSeriesVCDoc::OnAutomatic\n");
	// TODO: Add your command handler code here
	if(!(Redrawx && Redrawy)) {
		Redrawx? true: MessageBox(NULL, "尚未读入 X 序列", "错误", MB_OK);	// nice show
		Redrawy? true: MessageBox(NULL, "尚未读入 Y 序列", "错误", MB_OK);	// sorry it's copied from func above.
		return;
	}
	// or else
	handcraft = 1;	// means auto

	for(progress=0; progress<700; progress++) {	// 1000-300=700

		//relate[progress]=Rfunc(progress);		// just to 393?
		//lag[progress]=MaxR(progress);		// computing normally.
		
		POSITION   pos = GetFirstViewPosition();
		
		while (pos != NULL) {
			CView* pView = GetNextView(pos);
			pView->UpdateWindow();
		}
		
		this->UpdateAllViews(NULL);		// Call ondraw

		TRACE("CTimeSeriesVCDoc::OnAutomatic %d / 700\n", progress);
		ComputeFormula(progress);
		// ::Sleep(20);
		

	}

	TRACE("CTimeSeriesVCDoc::OnAutomatic leaving at %d\n", progress);
	this->UpdateAllViews(NULL);		// Call ondraw
}

//DEL double CTimeSeriesVCDoc::MaxR(const int loop)
//DEL {
//DEL 	// TRACE("CTimeSeriesVCDoc::MaxR\n");
//DEL 
//DEL 	double max=0;
//DEL 	for (int i=loop; i<300/2+loop; i++) {
//DEL 		max<Rfunc(i)?max=Rfunc(i):max=max;
//DEL 	}
//DEL 
//DEL 	return max;
//DEL }

void CTimeSeriesVCDoc::ComputeFormula(int pos)
{
	double result,tempMax,avg_x,avg_y,upper,lower1,lower2;
	int t,l,j,tempnPos;


	for(l = 0; l <150; l++)
	{
		avg_x=avg_y=0;
		upper=lower1=lower2=0;

		for(t = l,j=0; t < 300 ; t++,j++)
		{
			avg_x+= x[pos+t];
			avg_y+= y[pos+j];
		}
		avg_x = avg_x/(300-l);
		avg_y = avg_y/(300-l);

		for(t = l,j=0 ; t < 300 ; t++,j++)
		{
			upper += (x[pos+t]-avg_x)*(y[pos+t-l]-avg_y);
			lower1 += pow((x[pos+t]-avg_x),2);
			lower2 += pow((y[pos+j]-avg_y),2);
		}

		lower1 = sqrt(lower1);
		lower2 = sqrt(lower2);
		result=upper/(lower1*lower2);
         
		if(0 == l)
		{
			tempMax = result;
			tempnPos = l;
		}
		else
		{
			if(tempMax < result)
			{
				tempMax = result;
				tempnPos = l;
			}
		}
	}

	relate[pos] = tempMax;
	lag[pos] = tempnPos;

	MSG message;
	while (::PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) {
		::TranslateMessage(&message);
		::DispatchMessage(&message);
	}

	TRACE("ComputeFormula %f %f\n", relate[pos], lag[pos]);		// nice way to createlagrelation
}

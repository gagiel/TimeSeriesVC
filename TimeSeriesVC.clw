; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMainFrame
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "TimeSeriesVC.h"
LastPage=0

ClassCount=5
Class1=CTimeSeriesVCApp
Class2=CTimeSeriesVCDoc
Class3=CTimeSeriesVCView
Class4=CMainFrame

ResourceCount=2
Resource1=IDR_MAINFRAME
Class5=CAboutDlg
Resource2=IDD_ABOUTBOX

[CLS:CTimeSeriesVCApp]
Type=0
HeaderFile=TimeSeriesVC.h
ImplementationFile=TimeSeriesVC.cpp
Filter=N

[CLS:CTimeSeriesVCDoc]
Type=0
HeaderFile=TimeSeriesVCDoc.h
ImplementationFile=TimeSeriesVCDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC
LastObject=IDC_AUTOMATIC

[CLS:CTimeSeriesVCView]
Type=0
HeaderFile=TimeSeriesVCView.h
ImplementationFile=TimeSeriesVCView.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC
LastObject=CTimeSeriesVCView


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=IDC_XTOTAL
BaseClass=CFrameWnd
VirtualFilter=fWC




[CLS:CAboutDlg]
Type=0
HeaderFile=TimeSeriesVC.cpp
ImplementationFile=TimeSeriesVC.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=IDC_XTOTAL
Command2=IDC_YTOTAL
Command3=IDC_HANDCRAFT
Command4=IDC_AUTOMATIC
CommandCount=4

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_UNDO
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_NEXT_PANE
Command13=ID_PREV_PANE
CommandCount=13


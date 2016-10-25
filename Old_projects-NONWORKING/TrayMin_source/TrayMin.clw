; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CTrayMinDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "TrayMin.h"

ClassCount=3
Class1=CTrayMinApp
Class2=CTrayMinDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_TRAYMIN_DIALOG
Resource4=IDR_MENU1

[CLS:CTrayMinApp]
Type=0
HeaderFile=TrayMin.h
ImplementationFile=TrayMin.cpp
Filter=N

[CLS:CTrayMinDlg]
Type=0
HeaderFile=TrayMinDlg.h
ImplementationFile=TrayMinDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDM_MENU1

[CLS:CAboutDlg]
Type=0
HeaderFile=TrayMinDlg.h
ImplementationFile=TrayMinDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_TRAYMIN_DIALOG]
Type=1
Class=CTrayMinDlg
ControlCount=1
Control1=IDC_MINIMIZE,button,1342242816

[MNU:IDR_MENU1]
Type=1
Class=?
Command1=IDM_MENU1
Command2=IDM_EXIT
CommandCount=2


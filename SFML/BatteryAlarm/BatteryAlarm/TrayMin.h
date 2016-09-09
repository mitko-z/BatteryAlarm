// TrayMin.h : main header file for the TRAYMIN application
//

#if !defined(AFX_TRAYMIN_H__2A4BB765_52F5_11D8_BD12_E92FFA94AE40__INCLUDED_)
#define AFX_TRAYMIN_H__2A4BB765_52F5_11D8_BD12_E92FFA94AE40__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTrayMinApp:
// See TrayMin.cpp for the implementation of this class
//

class CTrayMinApp : public CWinApp
{
public:
	CTrayMinApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTrayMinApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTrayMinApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRAYMIN_H__2A4BB765_52F5_11D8_BD12_E92FFA94AE40__INCLUDED_)

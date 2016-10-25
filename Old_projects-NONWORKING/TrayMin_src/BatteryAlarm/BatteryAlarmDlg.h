// BatteryAlarmDlg.h : header file
//

#if !defined(AFX_BATTERYALARMDLG_H__2A4BB767_52F5_11D8_BD12_E92FFA94AE40__INCLUDED_)
#define AFX_BATTERYALARMDLG_H__2A4BB767_52F5_11D8_BD12_E92FFA94AE40__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string> // for std::string variables

#define WM_TRAY_MESSAGE (WM_USER + 1)

/////////////////////////////////////////////////////////////////////////////
// CBatteryAlarmDlg dialog

class CBatteryAlarmDlg : public CDialog
{
// Construction
public:
	CMenu m_menu;
	NOTIFYICONDATA m_TrayData;
	void OnTrayRButtonDown(CPoint pt);
	void OnTrayLButtonDown(CPoint pt);
	CBatteryAlarmDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CBatteryAlarmDlg)
	enum { IDD = IDD_BATTERYALARM_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBatteryAlarmDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CBatteryAlarmDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnTrayNotify(WPARAM wParam, LPARAM lParam);
	afx_msg void OnMinimize();
	afx_msg void OnExit();
	afx_msg void OnMenu1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BATTERYALARMDLG_H__2A4BB767_52F5_11D8_BD12_E92FFA94AE40__INCLUDED_)

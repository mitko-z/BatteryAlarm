// BatteryAlarmDlg.h : header file
//

#if !defined(AFX_BATTERYALARMDLG_H__2A4BB767_52F5_11D8_BD12_E92FFA94AE40__INCLUDED_)
#define AFX_BATTERYALARMDLG_H__2A4BB767_52F5_11D8_BD12_E92FFA94AE40__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string> // for std::string variables
#include <sstream> // string conversions

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "Timer.h"

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

	CBatteryAlarmDlg(CWnd* pParent = NULL);

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

	// system power management members
	HPOWERNOTIFY m_hPowerSchemeNotify, m_hPowerSourceNotify, m_hBatteryPowerNotify;
	bool m_bOnBattery;
	CStatic m_cPowerScheme, m_cPowerSource, m_cBatteryPower, m_cMessage;
	int m_nBatteryPower;
	SYSTEM_POWER_STATUS m_spsPower;
	int m_iPowerChange;

	// timers
	Timer m_tPowerCheck;
	Timer m_tWindowRefresh;

	// sounds
	sf::SoundBuffer m_sfsbWarningMessageBuffer;
	sf::Sound m_sfsWarningMessageSound;
	std::string m_sPathToWarningMessageSoundFile;

	// sfml window management support
	sf::RenderWindow m_sfwChangePowerMessage;
	sf::Texture m_sftChangePowerMessage;
	sf::RectangleShape m_sfrChangePowerMessage;
	sf::Vector2f m_sfv2WindowChangePowerMessageSize;
	bool m_bIsWindowAlive;
	sf::Event m_sfeEvent;

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
	
public:
	afx_msg UINT OnPowerBroadcast(UINT nPowerEvent, LPARAM nEventData);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BATTERYALARMDLG_H__2A4BB767_52F5_11D8_BD12_E92FFA94AE40__INCLUDED_)

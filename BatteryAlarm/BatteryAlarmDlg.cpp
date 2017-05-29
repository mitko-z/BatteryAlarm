// BatteryAlarmDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BatteryAlarm.h"
#include "BatteryAlarmDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBatteryAlarmDlg dialog

CBatteryAlarmDlg::CBatteryAlarmDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBatteryAlarmDlg::IDD, pParent), 
	m_bOnBattery(false), m_nBatteryPower(100),
	m_hPowerSchemeNotify(NULL), m_hPowerSourceNotify(NULL),
	m_hBatteryPowerNotify(NULL)
{
	m_iPowerChange = m_spsPower.ACLineStatus;
	//{{AFX_DATA_INIT(CBatteryAlarmDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBatteryAlarmDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBatteryAlarmDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBatteryAlarmDlg, CDialog)
	//{{AFX_MSG_MAP(CBatteryAlarmDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_TRAY_MESSAGE,OnTrayNotify)
	ON_BN_CLICKED(IDC_MINIMIZE, OnMinimize)
	ON_COMMAND(IDM_EXIT, OnExit)
	ON_COMMAND(IDM_MENU1, OnMenu1)
	//}}AFX_MSG_MAP
	ON_WM_POWERBROADCAST()
	ON_WM_TIMER()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBatteryAlarmDlg message handlers

BOOL CBatteryAlarmDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	/// power management preparation ///
	m_hPowerSchemeNotify = RegisterPowerSettingNotification(m_hWnd, &GUID_POWERSCHEME_PERSONALITY, DEVICE_NOTIFY_WINDOW_HANDLE);
	if (NULL == m_hPowerSchemeNotify)
		ATLTRACE("Failed to register for notification of power scheme changes!\n");

	if (GetSystemPowerStatus(&m_spsPower) == 0)
	{
		MessageBox("Error: Could not get the system power status in initialization!");
	}
	else
	{
		m_iPowerChange = m_spsPower.ACLineStatus;
	}

	/// init timers ///
	m_tPowerCheck = Timer(42, 1000);
	SetTimer(m_tPowerCheck.id, m_tPowerCheck.duration, nullptr);
	m_tWindowRefresh = Timer(1, 15);
	SetTimer(m_tWindowRefresh.id, m_tWindowRefresh.duration, nullptr);

	/// init sounds ///
	m_sPathToWarningMessageSoundFile = "warning-message-2.wav";
	if (!m_sfsbWarningMessageBuffer.loadFromFile(m_sPathToWarningMessageSoundFile))
	{
		MessageBox("Error loading of warning message sound file!");
	}
	m_sfsWarningMessageSound.setBuffer(m_sfsbWarningMessageBuffer);

	/// init messages windows ///
	m_sfwChangePowerMessage.setFramerateLimit(60);
	if (!m_sftChangePowerMessage.loadFromFile("ChagePowerMessage.png"))
	{
		MessageBox("Error loading of warning message image file!");
	}
	m_sfv2WindowChangePowerMessageSize.x = 640;
	m_sfv2WindowChangePowerMessageSize.y = 480;
	m_sfrChangePowerMessage.setSize(m_sfv2WindowChangePowerMessageSize);
	
	m_sfrChangePowerMessage.setPosition(0, 0);
	m_sfrChangePowerMessage.setTexture(&m_sftChangePowerMessage);
	m_bIsWindowAlive = false;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CBatteryAlarmDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CBatteryAlarmDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CBatteryAlarmDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

afx_msg LRESULT CBatteryAlarmDlg::OnTrayNotify(WPARAM wParam, LPARAM lParam)
	{
		LRESULT valueToReturn = 0;
		UINT uID; 
		UINT uMsg; 
 
		uID = (UINT) wParam;
		uMsg = (UINT) lParam; 
 
	
		if (uID != 1)
			return valueToReturn;
	
		CPoint pt;	
	
	
		switch (uMsg ) 
		{ 

		case WM_LBUTTONDOWN:
			GetCursorPos(&pt);
			ClientToScreen(&pt);
			OnTrayLButtonDown(pt);
			break;
	
		case WM_RBUTTONDOWN:
		case WM_CONTEXTMENU:
			GetCursorPos(&pt);
			OnTrayRButtonDown(pt);
			break;

		} 
		return valueToReturn;
	}

void CBatteryAlarmDlg::OnTrayLButtonDown(CPoint pt)
{
	
	std::string message;

	if (GetSystemPowerStatus(&m_spsPower) == 0)
	{
		message = "Error: Could not get the system power status!";
	}

	switch (m_spsPower.ACLineStatus)
	{
	case 1:
		message = 
			"You are now on AC power. \nThe battery curently is on " + 
			std::to_string(m_spsPower.BatteryLifePercent) + " percents";
		break;
	case 0:
		message = 
			"You are now on battery power. \nThe battery curently is on " + 
			std::to_string(m_spsPower.BatteryLifePercent) + " percents";
		break;
	default:
		message = "Warning! The battery status cannot be read!";
	}
	MessageBox(message.c_str());

}

void CBatteryAlarmDlg::OnTrayRButtonDown(CPoint pt)
{
	//m_menu is the member of CBatteryAlarmDlg as CMenu m_menu;
			m_menu.GetSubMenu(0)->TrackPopupMenu(TPM_BOTTOMALIGN|TPM_LEFTBUTTON|TPM_RIGHTBUTTON,pt.x,pt.y,this);
			

}

void CBatteryAlarmDlg::OnMinimize() 
{

	m_TrayData.cbSize = sizeof(NOTIFYICONDATA);
		//Size of this structure, in bytes. 
		
		
		m_TrayData.hWnd	= this->m_hWnd;
		//Handle to the window that receives notification 
		//messages associated with an icon in the taskbar 
		//status area. The Shell uses hWnd and uID to 
		//identify which icon to operate on when Shell_NotifyIcon is invoked. 
	
		m_TrayData.uID = 1;
		//Application-defined identifier of the taskbar icon.
		//The Shell uses hWnd and uID to identify which icon 
		//to operate on when Shell_NotifyIcon is invoked. You
		// can have multiple icons associated with a single 
		//hWnd by assigning each a different uID. 

		m_TrayData.uCallbackMessage	= WM_TRAY_MESSAGE;
		//Application-defined message identifier. The system 
		//uses this identifier to send notifications to the 
		//window identified in hWnd. These notifications are 
		//sent when a mouse event occurs in the bounding 
		//rectangle of the icon, or when the icon is selected 
		//or activated with the keyboard. The wParam parameter 
		//of the message contains the identifier of the taskbar 
		//icon in which the event occurred. The lParam parameter 
		//holds the mouse or keyboard message associated with the
		// event. For example, when the pointer moves over a 
		//taskbar icon, lParam is set to WM_MOUSEMOVE. 
		


		m_TrayData.hIcon = this->m_hIcon;
		//Handle to the icon to be added, modified, or deleted
		
		strcpy(m_TrayData.szTip,"My Icon");
		//Pointer to a null-terminated string with the text 
		//for a standard ToolTip. It can have a maximum of 64 
		//characters including the terminating NULL. 
		
		
		m_TrayData.uFlags = NIF_ICON|NIF_MESSAGE;
		//Flags that indicate which of the other members contain 
		//valid data.  
	

		BOOL bSuccess = FALSE;
		BOOL BSus = FALSE;

		BSus = m_menu.LoadMenu(IDR_MENU1);
		if(!(BSus))
			MessageBox("Unable to Load menu");

		bSuccess = Shell_NotifyIcon(NIM_ADD, &m_TrayData);

		if(!(bSuccess))
			MessageBox("Unable to Set Tary Icon");
		else
		{
			this->ShowWindow(SW_MINIMIZE);
			this->ShowWindow(SW_HIDE);

		}

}

void CBatteryAlarmDlg::OnExit() 
{
	KillTimer(m_tPowerCheck.id);
	if(m_sfwChangePowerMessage.isOpen())
	{ 
		m_sfwChangePowerMessage.close(); 
	}
	KillTimer(m_tWindowRefresh.id);
	Shell_NotifyIcon(NIM_DELETE, &m_TrayData);
	DestroyWindow();
	
}

void CBatteryAlarmDlg::OnMenu1() 
{

	MessageBox("You have Clicked Menu1");

}



UINT CBatteryAlarmDlg::OnPowerBroadcast(UINT nPowerEvent, LPARAM nEventData)
{

	std::string message = "";

	if (GetSystemPowerStatus(&m_spsPower) == 0)
	{
		message = "Error: Could not get the system power status!";
	}

	
	if (PBT_POWERSETTINGCHANGE != nPowerEvent)
	{
		return 0;
	}

	if (m_spsPower.ACLineStatus == 0 & m_iPowerChange == 1)
	{
		message = "Warning! You just went on battery power.";
		m_iPowerChange = 0;
	}

	if (m_spsPower.ACLineStatus == 1 & m_iPowerChange == 0)
	{
		m_iPowerChange = 1;
	}

	if (message != "")
	{
		MessageBox(message.c_str());
	}
	
	//POWERBROADCAST_SETTING* pps = (POWERBROADCAST_SETTING*)nEventData;

	//if (sizeof(GUID) == pps->DataLength &&
	//	pps->PowerSetting == GUID_POWERSCHEME_PERSONALITY)
	//{

	//	// This is a power scheme change notification
	//	GUID newScheme = *(GUID*)(DWORD_PTR)pps->Data;
	//	
	//	if (sizeof(int) == pps->DataLength &&
	//		pps->PowerSetting == GUID_ACDC_POWER_SOURCE)
	//	{
	//		MessageBox("next if 1");
	//		// This is a power source change notification
	//		int nPowerSrc = *(int*)(DWORD_PTR)pps->Data;

	//		m_bOnBattery = (0 != nPowerSrc);

	//		m_cPowerSource.SetWindowText(m_bOnBattery ? _T("Battery") : _T("AC power"));

	//		if (m_bOnBattery)
	//		{
	//			MessageBox("Warning: You just went on battery power!");

	//		}

	//	}
	//	else if (sizeof(int) == pps->DataLength &&
	//		pps->PowerSetting == GUID_BATTERY_PERCENTAGE_REMAINING)
	//	{
	//		MessageBox("next if 2");
	//		// This is a battery power notification
	//		int nPercentLeft = *(int*)(DWORD_PTR)pps->Data;
	//		CString sPercentLeft;

	//		sPercentLeft.Format(_T("%d"), nPercentLeft);
	//		m_cBatteryPower.SetWindowText(sPercentLeft);
	//		m_nBatteryPower = nPercentLeft;
	//	}
	//}


	return CDialog::OnPowerBroadcast(nPowerEvent, nEventData);
}


void CBatteryAlarmDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == m_tPowerCheck.id)
	{

		if (GetSystemPowerStatus(&m_spsPower) == 0)
		{
			// message = "Error: Could not get the system power status!";
			MessageBox("Error: Could not get the system power status!");
		}

		// debug
		/*message = 
			"m_spsPower = " + std::to_string(m_spsPower.ACLineStatus) + 
			"; powerChange = " + std::to_string(m_iPowerChange);*/
		
		if (m_spsPower.ACLineStatus == 0 & m_iPowerChange == 1)
		{
			// message = "Warning! You just went on battery power.";
			if (!m_sfwChangePowerMessage.isOpen())
			{
				m_sfwChangePowerMessage.create
					(
						sf::VideoMode
							(
								m_sfv2WindowChangePowerMessageSize.x, 
								m_sfv2WindowChangePowerMessageSize.y
							),
						"Battery allarm : System Power Changed!"
					);
			}
			m_sfwChangePowerMessage.clear();
			m_sfwChangePowerMessage.draw(m_sfrChangePowerMessage);
			m_sfwChangePowerMessage.display();
			m_iPowerChange = 0;
			m_sfsWarningMessageSound.play();
			m_bIsWindowAlive = true;
			//MessageBox(message.c_str());
		}

		if (m_spsPower.ACLineStatus == 1 & m_iPowerChange == 0)
		{
			m_iPowerChange = 1;
		}

	}


	if (nIDEvent = m_tWindowRefresh.id)
	{
		if (m_bIsWindowAlive)
		{
			while (m_sfwChangePowerMessage.pollEvent(m_sfeEvent))
			{
				if
					(
						m_sfeEvent.type == sf::Event::Closed ||
						(m_sfeEvent.type == sf::Event::KeyPressed && m_sfeEvent.key.code == sf::Keyboard::Escape)
					)
				{
					m_bIsWindowAlive = false;
				}
			}
			
			/*m_sfwChangePowerMessage.clear();
			m_sfwChangePowerMessage.draw(m_sfrChangePowerMessage);

			m_sfwChangePowerMessage.display();*/
		}

		if (m_sfwChangePowerMessage.isOpen())
		{
			if (!m_bIsWindowAlive || m_spsPower.ACLineStatus == 1)
			{
				m_sfwChangePowerMessage.close();
			}
		}
	}
	CDialog::OnTimer(nIDEvent);
}

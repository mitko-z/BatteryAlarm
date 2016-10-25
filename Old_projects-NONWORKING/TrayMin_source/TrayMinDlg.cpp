// TrayMinDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TrayMin.h"
#include "TrayMinDlg.h"

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
// CTrayMinDlg dialog

CTrayMinDlg::CTrayMinDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTrayMinDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTrayMinDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTrayMinDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTrayMinDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTrayMinDlg, CDialog)
	//{{AFX_MSG_MAP(CTrayMinDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_TRAY_MESSAGE,OnTrayNotify)
	ON_BN_CLICKED(IDC_MINIMIZE, OnMinimize)
	ON_COMMAND(IDM_EXIT, OnExit)
	ON_COMMAND(IDM_MENU1, OnMenu1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTrayMinDlg message handlers

BOOL CTrayMinDlg::OnInitDialog()
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
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTrayMinDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTrayMinDlg::OnPaint() 
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
HCURSOR CTrayMinDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

afx_msg LRESULT CTrayMinDlg::OnTrayNotify(WPARAM wParam, LPARAM lParam)
	{
		LRESULT valueToReturn;
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

void CTrayMinDlg::OnTrayLButtonDown(CPoint pt)
{
	MessageBox("You have clicked Left mouse Button ");

}

void CTrayMinDlg::OnTrayRButtonDown(CPoint pt)
{
	//m_menu is the member of CTrayMinDlg as CMenu m_menu;
			m_menu.GetSubMenu(0)->TrackPopupMenu(TPM_BOTTOMALIGN|TPM_LEFTBUTTON|TPM_RIGHTBUTTON,pt.x,pt.y,this);
			

}

void CTrayMinDlg::OnMinimize() 
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
			MessageBox("Unabled to Loa menu");

		bSuccess = Shell_NotifyIcon(NIM_ADD,&m_TrayData);

		if(!(bSuccess))
			MessageBox("Unable to Set Tary Icon");
		else
		{
			this->ShowWindow(SW_MINIMIZE);
			this->ShowWindow(SW_HIDE);

		}

}

void CTrayMinDlg::OnExit() 
{
Shell_NotifyIcon(NIM_DELETE,&m_TrayData);
	DestroyWindow();
	
}

void CTrayMinDlg::OnMenu1() 
{

	MessageBox("You have Clicked Menu1");

}

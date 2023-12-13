
// Task_ManagerDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Task_Manager.h"
#include "Task_ManagerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTaskManagerDlg dialog



CTaskManagerDlg::CTaskManagerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TASK_MANAGER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTaskManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, Path);
}

BEGIN_MESSAGE_MAP(CTaskManagerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CTaskManagerDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CTaskManagerDlg::OnBnClickedButton2)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CTaskManagerDlg message handlers

BOOL CTaskManagerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	int x = 0;
	int y = 0;

	CTaskManagerApp* application = (CTaskManagerApp*)AfxGetApp();

	if (application != nullptr)
	{
		x = application->x;
		y = application->y;
	}

	SetWindowPos(nullptr, x, y, 0, 0,SWP_NOSIZE);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTaskManagerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTaskManagerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTaskManagerDlg::OnBnClickedButton1()
{
	CFileDialog FileDialog(TRUE);

	if (FileDialog.DoModal() == IDOK)
	{
		Path.SetWindowTextW(FileDialog.GetPathName());
	}
}


void CTaskManagerDlg::OnBnClickedButton2()
{
	CStringW ApplicationPath;
	Path.GetWindowTextW(ApplicationPath);

	CStringW ApplicationFolderPath(ApplicationPath);

	while (true)
	{
		int ApplicationFolderPathCurrentLength = ApplicationFolderPath.GetLength();
		if (ApplicationFolderPathCurrentLength > 0)
		{
			if (ApplicationFolderPath.GetAt(ApplicationFolderPathCurrentLength - 1) != L'\\')
			{
				CStringW ApplicationFolderPathCorrected;
				for (int Counter = 0; Counter < ApplicationFolderPathCurrentLength - 1; Counter++)
				{
					ApplicationFolderPathCorrected += ApplicationFolderPath.GetAt(Counter);
				}

				ApplicationFolderPath = ApplicationFolderPathCorrected;
			}
			else
			{
				break;
			}
		}
		else
		{
			break;
		}
	}

	ShellExecuteW(nullptr, L"Open", ApplicationPath, nullptr, ApplicationFolderPath, SW_SHOW);
}


void CTaskManagerDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	int x = 0;
	int y = 0;

	auto main_window = AfxGetMainWnd();

	if (main_window != nullptr)
	{
		RECT window_rectangle = {};
		main_window->GetWindowRect(&window_rectangle);

		x = window_rectangle.left;
		y = window_rectangle.top;
	}

	CTaskManagerApp* application = (CTaskManagerApp *)AfxGetApp();

	if (application != nullptr)
	{
		application->x = x;
		application->y = y;
	}

	CDialogEx::OnClose();
}


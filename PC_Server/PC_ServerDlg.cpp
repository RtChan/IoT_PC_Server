
// PC_ServerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PC_Server.h"
#include "PC_ServerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPC_ServerDlg 对话框



CPC_ServerDlg::CPC_ServerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PC_SERVER_DIALOG, pParent)
	, m_LogDir(_T(""))
	, m_UserCount(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPC_ServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_LOGDIR, m_LogDir);
	DDX_Control(pDX, IDC_EventRecord, m_Event);
	DDX_Text(pDX, IDC_STATIC_USERCOUNT, m_UserCount);
}

BEGIN_MESSAGE_MAP(CPC_ServerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_StartServer, &CPC_ServerDlg::OnBnClickedStartserver)
	ON_BN_CLICKED(IDC_BUTTON_SELETDIR, &CPC_ServerDlg::OnBnClickedButtonSeletdir)
	ON_EN_CHANGE(IDC_EDIT_LOGDIR, &CPC_ServerDlg::OnEnChangeEditLogdir)
END_MESSAGE_MAP()


// CPC_ServerDlg 消息处理程序

BOOL CPC_ServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CPC_ServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CPC_ServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPC_ServerDlg::OnBnClickedStartserver()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CPC_ServerDlg::OnBnClickedButtonSeletdir()
{
	// TODO: 在此添加控件通知处理程序代码
	
	CString timestr;
	CTime time = CTime::GetCurrentTime();
	timestr = time.Format(_T("%Y-%m-%d"));


	// 设置过滤器   
	TCHAR szFilter[] = _T("日志文件(*.log)|*.log|文本文件(*.txt)|*.txt|所有文件(*.*)|*.*||");
	// 构造保存文件对话框   
	CFileDialog fileDlg(FALSE, _T("log"), timestr, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
	//CString strFilePath;

	// 显示保存文件对话框   
	if (IDOK == fileDlg.DoModal())
	{
		// 如果点击了文件对话框上的“保存”按钮，则将选择的文件路径显示到编辑框里   
		//strFilePath = fileDlg.GetPathName();
		m_LogDir = fileDlg.GetPathName();
		UpdateData(false);
	}
}


void CPC_ServerDlg::OnEnChangeEditLogdir()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);
}

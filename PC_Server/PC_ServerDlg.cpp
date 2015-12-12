
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
	ON_BN_CLICKED(IDCANCEL, &CPC_ServerDlg::OnBnClickedCancel)
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
	UINT m_port = 6000;

	/* 文件IO部分 */
	if (m_LogDir.GetLength() == 0) {
		AfxMessageBox(_T("请先设置日志文件路径！"));
		return;
	}

	if (logfile.m_pStream != nullptr) logfile.Close();	//关闭已打开的日志

	try {
		logfile.Open(m_LogDir, CFile::modeCreate | CFile::modeWrite | CFile::typeText);
	}
	catch(CFileException* e) {
		e->ReportError();
		e->Delete();
	}

	if (logfile.m_pStream == nullptr) {
		AfxMessageBox(_T("写日志文件失败，请检查文件是否可用！"));
		UpdateEvent(_T("打开日志文件失败。"));
		return;
	}

	GetDlgItem(IDC_EDIT_LOGDIR)->EnableWindow(false);

	/* Socket连接部分 */
	if (m_connect) {
		delete listenSocket;
		listenSocket = nullptr;
		m_connect = false;

		logfile.Close();	//关闭日志文件
		GetDlgItem(IDC_EDIT_LOGDIR)->EnableWindow(true);
		SetDlgItemText(IDC_StartServer, _T("打开服务器"));
		UpdateEvent(_T("系统关闭服务器。"));
		return;
	}

	listenSocket = new CServerSocket();
	listenSocket->m_pDlg = this;

	if (!listenSocket) {
		AfxMessageBox(_T("创建套接字出错！"));
		return;
	}

	UpdateData(true);	// 从控件获取数据到变量

	if (!listenSocket->Create(m_port)) {
		AfxMessageBox(_T("创建套接字错误！"));
		listenSocket->Close();
		return;
	}

	if (!listenSocket->Listen()) {
		AfxMessageBox(_T("监听失败！"));
		listenSocket->Close();
		return;
	}

	m_connect = true;
	SetDlgItemText(IDC_StartServer, _T("关闭服务器"));
	UpdateEvent(_T("系统打开服务器。"));
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

void CPC_ServerDlg::UpdateLogfile(CString str)
{
	CString string;
	CTime time = CTime::GetCurrentTime();
		
	if (logfile.m_pStream == nullptr) {
		return;
	}

	string = time.Format(_T("%Y/%m/%d %H:%M:%S ")) + str + _T("\r\n");

	try {
		//logfile.Seek(0, CStdioFile::end);
		logfile.SeekToEnd();
		logfile.WriteString(string);
	}
	catch (CFileException* e) {
		e->ReportError();
		e->Delete();
	}
}

void CPC_ServerDlg::AddClient()
{
	CServerSocket *pSocket = new CServerSocket();
	pSocket->m_pDlg = this;
	if (!pSocket) {
		AfxMessageBox(_T("客户连接服务器失败!"));
		delete pSocket;
		return;
	}

	listenSocket->Accept(*pSocket);
	pSocket->AsyncSelect(FD_WRITE | FD_READ | FD_CLOSE);

	m_clientList.AddTail(pSocket);
	m_UserCount = m_clientList.GetCount();

	UpdateData(false);			// 从变量获取数据到控件显示
	UpdateEvent(_T("用户连接服务器。"));

	//SendMSG(_T("Hello!"));
}

void CPC_ServerDlg::RemoveClient(CServerSocket * pSocket)
{
	POSITION nPos = m_clientList.GetHeadPosition();
	POSITION nTmpPos = nPos;

	while (nPos) {
		CServerSocket* pSocketItem = (CServerSocket*)m_clientList.GetNext(nPos);

		if (pSocketItem->m_hSocket == pSocket->m_hSocket) {
			pSocketItem->Close();
			delete pSocketItem;

			m_clientList.RemoveAt(nTmpPos);
			m_UserCount = m_clientList.GetCount();

			UpdateData(false);
			UpdateEvent(_T("客户端下线。"));
			return;
		}

		nTmpPos = nPos;
	}
}

void CPC_ServerDlg::RecvData(CServerSocket * pSocket)
{
	char *pData = nullptr;
	pData = new char[1024];
	memset(pData, 0, sizeof(char) * 1024);

	UCHAR leng = 0;
	CString str;

	if (pSocket->Receive(pData, 1024, 0) != SOCKET_ERROR) {
		str = pData;
		//SendMSG(str);

		CString IPadd;
		UINT port;
		pSocket->GetPeerName(IPadd, port);	// 重载的方法

		str = _T("接收") + IPadd + _T("的数据：") + str;

		UpdateData(false);
		UpdateEvent(str);

		UpdateLogfile(str);
	}

	delete pData;
	pData = nullptr;
}

void CPC_ServerDlg::UpdateEvent(CString str)
{
	CString string;
	CTime time = CTime::GetCurrentTime();

	//str += _T("\r\n");
	// 格式化当前时间
	if (str.GetLength() <= 30)
		string = time.Format(_T("%Y/%m/%d %H:%M:%S ")) + str + _T("\r\n");
	else 
		string = time.Format(_T("%Y/%m/%d %H:%M:%S\r\n")) + str + _T("\r\n");

	//获取编辑框最后一行索引
	int lastLine = m_Event.LineIndex(m_Event.GetLineCount() - 1);
	m_Event.SetSel(lastLine + 1, lastLine + 2, 0);

	m_Event.ReplaceSel(string);
}

void CPC_ServerDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	if (logfile.m_pStream != nullptr) logfile.Close();	//关闭已打开的日志
	CDialogEx::OnCancel();
}

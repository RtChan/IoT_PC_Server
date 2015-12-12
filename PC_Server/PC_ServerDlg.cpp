
// PC_ServerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PC_Server.h"
#include "PC_ServerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPC_ServerDlg �Ի���



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


// CPC_ServerDlg ��Ϣ�������

BOOL CPC_ServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CPC_ServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CPC_ServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPC_ServerDlg::OnBnClickedStartserver()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UINT m_port = 6000;

	/* �ļ�IO���� */
	if (m_LogDir.GetLength() == 0) {
		AfxMessageBox(_T("����������־�ļ�·����"));
		return;
	}

	if (logfile.m_pStream != nullptr) logfile.Close();	//�ر��Ѵ򿪵���־

	try {
		logfile.Open(m_LogDir, CFile::modeCreate | CFile::modeWrite | CFile::typeText);
	}
	catch(CFileException* e) {
		e->ReportError();
		e->Delete();
	}

	if (logfile.m_pStream == nullptr) {
		AfxMessageBox(_T("д��־�ļ�ʧ�ܣ������ļ��Ƿ���ã�"));
		UpdateEvent(_T("����־�ļ�ʧ�ܡ�"));
		return;
	}

	GetDlgItem(IDC_EDIT_LOGDIR)->EnableWindow(false);

	/* Socket���Ӳ��� */
	if (m_connect) {
		delete listenSocket;
		listenSocket = nullptr;
		m_connect = false;

		logfile.Close();	//�ر���־�ļ�
		GetDlgItem(IDC_EDIT_LOGDIR)->EnableWindow(true);
		SetDlgItemText(IDC_StartServer, _T("�򿪷�����"));
		UpdateEvent(_T("ϵͳ�رշ�������"));
		return;
	}

	listenSocket = new CServerSocket();
	listenSocket->m_pDlg = this;

	if (!listenSocket) {
		AfxMessageBox(_T("�����׽��ֳ���"));
		return;
	}

	UpdateData(true);	// �ӿؼ���ȡ���ݵ�����

	if (!listenSocket->Create(m_port)) {
		AfxMessageBox(_T("�����׽��ִ���"));
		listenSocket->Close();
		return;
	}

	if (!listenSocket->Listen()) {
		AfxMessageBox(_T("����ʧ�ܣ�"));
		listenSocket->Close();
		return;
	}

	m_connect = true;
	SetDlgItemText(IDC_StartServer, _T("�رշ�����"));
	UpdateEvent(_T("ϵͳ�򿪷�������"));
}

void CPC_ServerDlg::OnBnClickedButtonSeletdir()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	CString timestr;
	CTime time = CTime::GetCurrentTime();
	timestr = time.Format(_T("%Y-%m-%d"));


	// ���ù�����   
	TCHAR szFilter[] = _T("��־�ļ�(*.log)|*.log|�ı��ļ�(*.txt)|*.txt|�����ļ�(*.*)|*.*||");
	// ���챣���ļ��Ի���   
	CFileDialog fileDlg(FALSE, _T("log"), timestr, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
	//CString strFilePath;

	// ��ʾ�����ļ��Ի���   
	if (IDOK == fileDlg.DoModal())
	{
		// ���������ļ��Ի����ϵġ����桱��ť����ѡ����ļ�·����ʾ���༭����   
		//strFilePath = fileDlg.GetPathName();
		m_LogDir = fileDlg.GetPathName();
		UpdateData(false);
	}
}

void CPC_ServerDlg::OnEnChangeEditLogdir()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
		AfxMessageBox(_T("�ͻ����ӷ�����ʧ��!"));
		delete pSocket;
		return;
	}

	listenSocket->Accept(*pSocket);
	pSocket->AsyncSelect(FD_WRITE | FD_READ | FD_CLOSE);

	m_clientList.AddTail(pSocket);
	m_UserCount = m_clientList.GetCount();

	UpdateData(false);			// �ӱ�����ȡ���ݵ��ؼ���ʾ
	UpdateEvent(_T("�û����ӷ�������"));

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
			UpdateEvent(_T("�ͻ������ߡ�"));
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
		pSocket->GetPeerName(IPadd, port);	// ���صķ���

		str = _T("����") + IPadd + _T("�����ݣ�") + str;

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
	// ��ʽ����ǰʱ��
	if (str.GetLength() <= 30)
		string = time.Format(_T("%Y/%m/%d %H:%M:%S ")) + str + _T("\r\n");
	else 
		string = time.Format(_T("%Y/%m/%d %H:%M:%S\r\n")) + str + _T("\r\n");

	//��ȡ�༭�����һ������
	int lastLine = m_Event.LineIndex(m_Event.GetLineCount() - 1);
	m_Event.SetSel(lastLine + 1, lastLine + 2, 0);

	m_Event.ReplaceSel(string);
}

void CPC_ServerDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (logfile.m_pStream != nullptr) logfile.Close();	//�ر��Ѵ򿪵���־
	CDialogEx::OnCancel();
}

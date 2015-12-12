
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

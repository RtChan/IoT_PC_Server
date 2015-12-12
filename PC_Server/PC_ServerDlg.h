
// PC_ServerDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"

#include "ServerSocket.h"
class CServerSocket;

// CPC_ServerDlg �Ի���
class CPC_ServerDlg : public CDialogEx
{
// ����
public:
	CPC_ServerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PC_SERVER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_LogDir;
	CEdit m_Event;
	UINT m_UserCount;
	afx_msg void OnBnClickedStartserver();
	afx_msg void OnBnClickedButtonSeletdir();
	afx_msg void OnEnChangeEditLogdir();

//�ļ�IO���
public:
	CStdioFile logfile;
	void UpdateLogfile(CString str);

//Socket���
public:
	CServerSocket* listenSocket;		// ���ڴ򿪷�����
	CPtrList m_clientList;				// �������ڴ洢�û�
	bool m_connect;						// ���ڱ�Ƿ�����״̬
	void AddClient();					// �����û�����Ӧ�û�����
	void RemoveClient(CServerSocket* pSocket);		// �Ƴ����ߵ��û�
	void RecvData(CServerSocket* pSocket);			// ��ȡ����
	void UpdateEvent(CString str);					// �����¼���־
	//BOOL WChar2MByte(LPCWSTR srcBuff, LPSTR destBuff, int nlen);	//�ַ�ת��
	afx_msg void OnBnClickedCancel();
};


// PC_ServerDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


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
};


// PC_ServerDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CPC_ServerDlg 对话框
class CPC_ServerDlg : public CDialogEx
{
// 构造
public:
	CPC_ServerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PC_SERVER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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

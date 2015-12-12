
// PC_ServerDlg.h : 头文件
//

#pragma once
#include "afxwin.h"

#include "ServerSocket.h"
class CServerSocket;

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

//文件IO相关
public:
	CStdioFile logfile;
	void UpdateLogfile(CString str);

//Socket相关
public:
	CServerSocket* listenSocket;		// 用于打开服务器
	CPtrList m_clientList;				// 链表用于存储用户
	bool m_connect;						// 用于标记服务器状态
	void AddClient();					// 增加用户，响应用户请求
	void RemoveClient(CServerSocket* pSocket);		// 移除下线的用户
	void RecvData(CServerSocket* pSocket);			// 获取数据
	void UpdateEvent(CString str);					// 更新事件日志
	//BOOL WChar2MByte(LPCWSTR srcBuff, LPSTR destBuff, int nlen);	//字符转换
	afx_msg void OnBnClickedCancel();
};

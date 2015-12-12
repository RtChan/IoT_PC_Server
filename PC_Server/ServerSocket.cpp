#include "stdafx.h"
#include "ServerSocket.h"


CServerSocket::CServerSocket()
{
}


CServerSocket::~CServerSocket()
{
}


void CServerSocket::OnAccept(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	m_pDlg->AddClient();						//添加上线用户
	CSocket::OnAccept(nErrorCode);
}


void CServerSocket::OnClose(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	m_pDlg->RemoveClient(this);					// 删除下线用户
	CSocket::OnClose(nErrorCode);
}


void CServerSocket::OnReceive(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类

	m_pDlg->RecvData(this);						// 接收数据
	CSocket::OnReceive(nErrorCode);
}

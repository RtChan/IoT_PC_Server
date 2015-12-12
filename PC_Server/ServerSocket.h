#pragma once
#include "afxsock.h"

#include "PC_ServerDlg.h"
class CPC_ServerDlg;

class CServerSocket :
	public CSocket
{
public:
	CServerSocket();
	~CServerSocket();

	CPC_ServerDlg* m_pDlg;

	virtual void OnAccept(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
};


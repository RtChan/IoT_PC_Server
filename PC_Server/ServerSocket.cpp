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
	// TODO: �ڴ����ר�ô����/����û���
	m_pDlg->AddClient();						//��������û�
	CSocket::OnAccept(nErrorCode);
}


void CServerSocket::OnClose(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	m_pDlg->RemoveClient(this);					// ɾ�������û�
	CSocket::OnClose(nErrorCode);
}


void CServerSocket::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���

	m_pDlg->RecvData(this);						// ��������
	CSocket::OnReceive(nErrorCode);
}

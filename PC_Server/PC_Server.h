
// PC_Server.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CPC_ServerApp: 
// �йش����ʵ�֣������ PC_Server.cpp
//

class CPC_ServerApp : public CWinApp
{
public:
	CPC_ServerApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CPC_ServerApp theApp;
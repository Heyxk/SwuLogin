
// LOGIN.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CLOGINApp: 
// �йش����ʵ�֣������ LOGIN.cpp
//

class CLOGINApp : public CWinApp
{
public:
	CLOGINApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CLOGINApp theApp;
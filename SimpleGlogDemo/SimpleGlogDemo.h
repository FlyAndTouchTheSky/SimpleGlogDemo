
// SimpleGlogDemo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CSimpleGlogDemoApp: 
// �йش����ʵ�֣������ SimpleGlogDemo.cpp
//

class CSimpleGlogDemoApp : public CWinApp
{
public:
	CSimpleGlogDemoApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CSimpleGlogDemoApp theApp;
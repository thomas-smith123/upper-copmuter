
// qwewq.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CqwewqApp:
// �йش����ʵ�֣������ qwewq.cpp
//

class CqwewqApp : public CWinApp
{
public:
	CqwewqApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CqwewqApp theApp;
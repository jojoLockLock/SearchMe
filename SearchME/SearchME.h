
// SeachME.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CSeachMEApp:
// �йش����ʵ�֣������ SeachME.cpp
//

class CSeachMEApp : public CWinAppEx
{
public:
	CSeachMEApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CSeachMEApp theApp;
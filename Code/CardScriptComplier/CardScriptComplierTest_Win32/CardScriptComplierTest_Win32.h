
// CardScriptComplierTest_Win32.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCardScriptComplierTest_Win32App: 
// �йش����ʵ�֣������ CardScriptComplierTest_Win32.cpp
//

class CCardScriptComplierTest_Win32App : public CWinApp
{
public:
	CCardScriptComplierTest_Win32App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CCardScriptComplierTest_Win32App theApp;
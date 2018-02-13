
// CardScriptComplierTest_Win32.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// CCardScriptComplierTest_Win32App: 
// 有关此类的实现，请参阅 CardScriptComplierTest_Win32.cpp
//

class CCardScriptComplierTest_Win32App : public CWinApp
{
public:
	CCardScriptComplierTest_Win32App();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CCardScriptComplierTest_Win32App theApp;
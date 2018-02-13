
// CardScriptComplierTest_Win32Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CardScriptComplierTest_Win32.h"
#include "CardScriptComplierTest_Win32Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCardScriptComplierTest_Win32Dlg 对话框



CCardScriptComplierTest_Win32Dlg::CCardScriptComplierTest_Win32Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CARDSCRIPTCOMPLIERTEST_WIN32_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCardScriptComplierTest_Win32Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCardScriptComplierTest_Win32Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CCardScriptComplierTest_Win32Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CCardScriptComplierTest_Win32Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &CCardScriptComplierTest_Win32Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON3, &CCardScriptComplierTest_Win32Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON5, &CCardScriptComplierTest_Win32Dlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CCardScriptComplierTest_Win32Dlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CCardScriptComplierTest_Win32Dlg::OnBnClickedButton7)
END_MESSAGE_MAP()


// CCardScriptComplierTest_Win32Dlg 消息处理程序

BOOL CCardScriptComplierTest_Win32Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCardScriptComplierTest_Win32Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCardScriptComplierTest_Win32Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCardScriptComplierTest_Win32Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

#include "libmain.h"
#pragma comment(lib, "CardScriptComplier.lib")

void CCardScriptComplierTest_Win32Dlg::OnBnClickedButton1()
{
	int ret = 0;
	char szVer[512] = {0};
	
	ret = get_version(szVer);

	if (!ret)
	{
		MessageBox(szVer);
	}
	else 
	{
		MessageBox("调用失败");
	}

}


void CCardScriptComplierTest_Win32Dlg::OnBnClickedButton2()
{
	int ret = 0;

	ret = csc("E:\\work\\git\\coding_net\\tmp\\CardScriptCoplimer\\lex\\lex\\cardscript\\testcase\\1.简单赋值.txt");

	if (!ret)
	{
		MessageBox("调用成功");
	}
	else
	{
		MessageBox("调用失败");
	}
}


void CCardScriptComplierTest_Win32Dlg::OnBnClickedButton4()
{
	int ret = 0;

	ret = csc("E:\\work\\git\\coding_net\\tmp\\CardScriptCoplimer\\lex\\lex\\cardscript\\testcase\\2-1-参数替换-赋值表达式中的参数替换.txt");

	if (!ret)
	{
		MessageBox("调用成功");
	}
	else
	{
		MessageBox("调用失败");
	}
}


void CCardScriptComplierTest_Win32Dlg::OnBnClickedButton3()
{
	int ret = 0;

	ret = csc("E:\\work\\git\\coding_net\\tmp\\CardScriptCoplimer\\lex\\lex\\cardscript\\testcase\\2.常量替换赋值.txt");

	if (!ret)
	{
		MessageBox("调用成功");
	}
	else
	{
		MessageBox("调用失败");
	}
}


void CCardScriptComplierTest_Win32Dlg::OnBnClickedButton5()
{
	int ret = 0;

	ret = csc("E:\\work\\git\\coding_net\\tmp\\CardScriptCoplimer\\lex\\lex\\cardscript\\testcase\\2-2-参数替换-卡片指令中的参数替换.txt");

	if (!ret)
	{
		MessageBox("调用成功");
	}
	else
	{
		MessageBox("调用失败");
	}
}


void CCardScriptComplierTest_Win32Dlg::OnBnClickedButton6()
{
	int ret = 0;

	ret = csc("E:\\work\\git\\coding_net\\tmp\\CardScriptCoplimer\\lex\\lex\\cardscript\\testcase\\2-3-参数替换-含有多个参数替换.txt");

	if (!ret)
	{
		MessageBox("调用成功");
	}
	else
	{
		MessageBox("调用失败");
	}
}


void CCardScriptComplierTest_Win32Dlg::OnBnClickedButton7()
{
	int ret = 0;

	ret = csc("E:\\work\\git\\coding_net\\tmp\\CardScriptCoplimer\\lex\\lex\\cardscript\\testcase\\3-1-算术表达式求值.txt");

	if (!ret)
	{
		MessageBox("调用成功");
	}
	else
	{
		MessageBox("调用失败");
	}
}


// CardScriptComplierTest_Win32Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CardScriptComplierTest_Win32.h"
#include "CardScriptComplierTest_Win32Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CCardScriptComplierTest_Win32Dlg �Ի���



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


// CCardScriptComplierTest_Win32Dlg ��Ϣ�������

BOOL CCardScriptComplierTest_Win32Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCardScriptComplierTest_Win32Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
		MessageBox("����ʧ��");
	}

}


void CCardScriptComplierTest_Win32Dlg::OnBnClickedButton2()
{
	int ret = 0;

	ret = csc("E:\\work\\git\\coding_net\\tmp\\CardScriptCoplimer\\lex\\lex\\cardscript\\testcase\\1.�򵥸�ֵ.txt");

	if (!ret)
	{
		MessageBox("���óɹ�");
	}
	else
	{
		MessageBox("����ʧ��");
	}
}


void CCardScriptComplierTest_Win32Dlg::OnBnClickedButton4()
{
	int ret = 0;

	ret = csc("E:\\work\\git\\coding_net\\tmp\\CardScriptCoplimer\\lex\\lex\\cardscript\\testcase\\2-1-�����滻-��ֵ���ʽ�еĲ����滻.txt");

	if (!ret)
	{
		MessageBox("���óɹ�");
	}
	else
	{
		MessageBox("����ʧ��");
	}
}


void CCardScriptComplierTest_Win32Dlg::OnBnClickedButton3()
{
	int ret = 0;

	ret = csc("E:\\work\\git\\coding_net\\tmp\\CardScriptCoplimer\\lex\\lex\\cardscript\\testcase\\2.�����滻��ֵ.txt");

	if (!ret)
	{
		MessageBox("���óɹ�");
	}
	else
	{
		MessageBox("����ʧ��");
	}
}


void CCardScriptComplierTest_Win32Dlg::OnBnClickedButton5()
{
	int ret = 0;

	ret = csc("E:\\work\\git\\coding_net\\tmp\\CardScriptCoplimer\\lex\\lex\\cardscript\\testcase\\2-2-�����滻-��Ƭָ���еĲ����滻.txt");

	if (!ret)
	{
		MessageBox("���óɹ�");
	}
	else
	{
		MessageBox("����ʧ��");
	}
}


void CCardScriptComplierTest_Win32Dlg::OnBnClickedButton6()
{
	int ret = 0;

	ret = csc("E:\\work\\git\\coding_net\\tmp\\CardScriptCoplimer\\lex\\lex\\cardscript\\testcase\\2-3-�����滻-���ж�������滻.txt");

	if (!ret)
	{
		MessageBox("���óɹ�");
	}
	else
	{
		MessageBox("����ʧ��");
	}
}


void CCardScriptComplierTest_Win32Dlg::OnBnClickedButton7()
{
	int ret = 0;

	ret = csc("E:\\work\\git\\coding_net\\tmp\\CardScriptCoplimer\\lex\\lex\\cardscript\\testcase\\3-1-�������ʽ��ֵ.txt");

	if (!ret)
	{
		MessageBox("���óɹ�");
	}
	else
	{
		MessageBox("����ʧ��");
	}
}

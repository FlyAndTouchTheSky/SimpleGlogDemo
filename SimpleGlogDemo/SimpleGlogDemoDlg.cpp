
// SimpleGlogDemoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SimpleGlogDemo.h"
#include "SimpleGlogDemoDlg.h"
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
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSimpleGlogDemoDlg 对话框



CSimpleGlogDemoDlg::CSimpleGlogDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSimpleGlogDemoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSimpleGlogDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSimpleGlogDemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CSimpleGlogDemoDlg 消息处理程序



/*

这个工程 包含了glog0.3.3
首先需要先编译glog0.33才能使用这个工程

glog包含的工程有：
libglog  //动态库？
libglog_static  //静态库？
logging_unittest  //测试工程
logging_unitest_static  //测试工程

如何编译glog0.3.3

打开google-glog.sln，编译

有报错，修复问题

1.std::min问题

	在报错文件里，添加#include <algorithm>

2._asm int 3 问题

	在logging_fail()中，注释掉_asm int 3这一行，并且在下一行添加__debugbreak();

编译即可
*/


/*

目录设置

glog工程目录与SimpleGlogDemo.sln在同一个目录下
需要注意下工程的包含目录和库目录的设置，相对路径
VC++目录--包含目录:..\glog-0.3.3\src\windows;
VC++目录--库目录：..\glog-0.3.3\Debug;

*/

//这个宏是根据编译器报错的提示来加的
#define GLOG_NO_ABBREVIATED_SEVERITIES
#include "glog/logging.h"
#pragma comment(lib,"libglog.lib")

//写几行测试代码就可以运行了。
//运行之后，清掉所有的生成项，然后上传到github。

BOOL CSimpleGlogDemoDlg::OnInitDialog()
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

	// TODO:  在此添加额外的初始化代码

	char path[MAX_PATH] = { 0 };
	::GetModuleFileNameA(NULL, path, MAX_PATH);

	//如何截取路径

	//方法一
	char* p = strrchr(path, '\\');
	if (p)
	{
		*p = '\0';
	}

	//方法二
	//char* p = strstr(path, "\\SimpleGlogDemo.exe");
	//if (p)
	//{
	//	*p = '\0';
	//}

	//在debug目录下直接执行程序，InitGoogleLogging正常
	//用vs执行程序，日志反而在.vcxproj文件所在的目录下生成

	google::InitGoogleLogging(path);//设置工作目录
	google::SetLogDestination(google::GLOG_INFO, "./glog_log_");//设置日志前缀
	LOG(INFO) << "abc123"<<std::endl;
	//第二行在程序关闭之后才显示出来
	LOG(INFO) << "中文要是乱码的话，就要从GB2312转为UTF8"<<std::endl;//不能显示中文？

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CSimpleGlogDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSimpleGlogDemoDlg::OnPaint()
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
HCURSOR CSimpleGlogDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


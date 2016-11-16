
// SimpleGlogDemoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SimpleGlogDemo.h"
#include "SimpleGlogDemoDlg.h"
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
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CSimpleGlogDemoDlg �Ի���



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


// CSimpleGlogDemoDlg ��Ϣ�������



/*

������� ������glog0.3.3
������Ҫ�ȱ���glog0.33����ʹ���������

glog�����Ĺ����У�
libglog  //��̬�⣿
libglog_static  //��̬�⣿
logging_unittest  //���Թ���
logging_unitest_static  //���Թ���

��α���glog0.3.3

��google-glog.sln������

�б����޸�����

1.std::min����

	�ڱ����ļ�����#include <algorithm>

2._asm int 3 ����

	��logging_fail()�У�ע�͵�_asm int 3��һ�У���������һ�����__debugbreak();

���뼴��
*/


/*

Ŀ¼����

glog����Ŀ¼��SimpleGlogDemo.sln��ͬһ��Ŀ¼��
��Ҫע���¹��̵İ���Ŀ¼�Ϳ�Ŀ¼�����ã����·��
VC++Ŀ¼--����Ŀ¼:..\glog-0.3.3\src\windows;
VC++Ŀ¼--��Ŀ¼��..\glog-0.3.3\Debug;

*/

//������Ǹ��ݱ������������ʾ���ӵ�
#define GLOG_NO_ABBREVIATED_SEVERITIES
#include "glog/logging.h"
#pragma comment(lib,"libglog.lib")

//д���в��Դ���Ϳ��������ˡ�
//����֮��������е������Ȼ���ϴ���github��

BOOL CSimpleGlogDemoDlg::OnInitDialog()
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

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	char path[MAX_PATH] = { 0 };
	::GetModuleFileNameA(NULL, path, MAX_PATH);

	//��ν�ȡ·��

	//����һ
	char* p = strrchr(path, '\\');
	if (p)
	{
		*p = '\0';
	}

	//������
	//char* p = strstr(path, "\\SimpleGlogDemo.exe");
	//if (p)
	//{
	//	*p = '\0';
	//}

	//��debugĿ¼��ֱ��ִ�г���InitGoogleLogging����
	//��vsִ�г�����־������.vcxproj�ļ����ڵ�Ŀ¼������

	google::InitGoogleLogging(path);//���ù���Ŀ¼
	google::SetLogDestination(google::GLOG_INFO, "./glog_log_");//������־ǰ׺
	LOG(INFO) << "abc123"<<std::endl;
	//�ڶ����ڳ���ر�֮�����ʾ����
	LOG(INFO) << "����Ҫ������Ļ�����Ҫ��GB2312תΪUTF8"<<std::endl;//������ʾ���ģ�

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSimpleGlogDemoDlg::OnPaint()
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
HCURSOR CSimpleGlogDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


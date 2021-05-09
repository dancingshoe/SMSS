
// SMSSDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "SMSS.h"
#include "SMSSDlg.h"
#include "afxdialogex.h"
#include "Register.h"
#include "Admin.h"
#include "User.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CFont font;
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


// CSMSSDlg 对话框



CSMSSDlg::CSMSSDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SMSS_DIALOG, pParent)
	, m_LoginZH(_T(""))
	, m_LoginMM(_T(""))
	, m_ISAdmin(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSMSSDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_zh, m_SetFontZH);
	DDX_Control(pDX, IDC_STATIC_mm, m_SetFontmm);
	//  DDX_Radio(pDX, IDC_RADIO_ISAdmin, m_LoginISAdmin);
	DDX_Text(pDX, IDC_EDIT_LoginZH, m_LoginZH);
	DDX_Text(pDX, IDC_EDIT_LoginMM, m_LoginMM);
	DDX_Check(pDX, IDC_CHECK_ISAdmin, m_ISAdmin);
}

BEGIN_MESSAGE_MAP(CSMSSDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_Register, &CSMSSDlg::OnBnClickedButtonRegister)
	ON_BN_CLICKED(IDC_CHECK_LoginShow, &CSMSSDlg::OnBnClickedCheckLoginshow)
	ON_BN_CLICKED(IDC_BUTTON_Login, &CSMSSDlg::OnBnClickedButtonLogin)
END_MESSAGE_MAP()


// CSMSSDlg 消息处理程序

BOOL CSMSSDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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
	font.CreatePointFont(200, _T("宋体"));
	m_SetFontZH.SetFont(&font);
	m_SetFontmm.SetFont(&font);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CSMSSDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSMSSDlg::OnPaint()
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
HCURSOR CSMSSDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSMSSDlg::OnBnClickedButtonRegister()
{
	// TODO: 在此添加控件通知处理程序代码
	Register dlg;
	dlg.DoModal();
}


void CSMSSDlg::OnBnClickedCheckLoginshow()
{
	// TODO: 在此添加控件通知处理程序代码
	if (IsDlgButtonChecked(IDC_CHECK_LoginShow) == BST_CHECKED)
	{
		UpdateData(true);
		CEdit* pEdit = (CEdit*)(this)->GetDlgItem(IDC_EDIT_LoginMM);
		pEdit->SetPasswordChar(0);
		SetDlgItemText(IDC_EDIT_LoginMM, m_LoginMM);
		UpdateData(false);
	}
	else {
		UpdateData(true);
		CEdit* pEdit = (CEdit*)(this)->GetDlgItem(IDC_EDIT_LoginMM);
		pEdit->SetPasswordChar('*');
		SetDlgItemText(IDC_EDIT_LoginMM, m_LoginMM);
		UpdateData(false);
	}
	GetDlgItem(IDC_EDIT_LoginMM)->SetFocus();
}


void CSMSSDlg::OnBnClickedButtonLogin()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_LoginZH == "" || m_LoginMM == "") {
		MessageBox(_T("账号或者密码不可为空！"), _T("错误提示"));
		return;
	}
	//CString strCmd;
	CString ID, Password;
	_bstr_t strCmd;
	AdoSql SSMS;
	SSMS.InitialConn();
	//_RecordsetPtr pPtr;
	if (m_ISAdmin == 0)
	{
		SSMS.GetRecordSet(_T("select * from tblUser"));
		while (!SSMS.m_pRecordSet->adoEOF)
		{
			ID = (char*)(_bstr_t)SSMS.m_pRecordSet->GetCollect("UserID");
			Password = (char*)(_bstr_t)SSMS.m_pRecordSet->GetCollect("UserPasswod");
			if (m_LoginZH == ID && m_LoginMM == Password)
			{
				MessageBox(_T("用户登陆成功"));
				CDialogEx::OnOK();
				User dlg;
				dlg.DoModal();
				break;
			}
			SSMS.m_pRecordSet->MoveNext();
		}
		//MessageBox(_T("登陆失败,请检查账号或密码是否正确!"), _T("错误提示!"));
	}
	else
	{
		SSMS.GetRecordSet(_T("select * from tblAdministrator"));
		while (!SSMS.m_pRecordSet->adoEOF)
		{
			ID = (char*)(_bstr_t)SSMS.m_pRecordSet->GetCollect("AdminID");
			Password = (char*)(_bstr_t)SSMS.m_pRecordSet->GetCollect("AdminPasswod");
			if (m_LoginZH == ID && m_LoginMM == Password)
			{
				MessageBox(_T("管理员登陆成功"));
				CDialogEx::OnOK();
				Admin dlg;
				dlg.DoModal();
				break;
			}
			SSMS.m_pRecordSet->MoveNext();
		}
		//MessageBox(_T("登陆失败,请检查账号或密码是否正确!"),_T("错误提示!"));
	}
	UpdateData(FALSE);
}

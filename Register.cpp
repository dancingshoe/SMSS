// Register.cpp: 实现文件
//

#include "pch.h"
#include "SMSS.h"
#include "Register.h"
#include "afxdialogex.h"


// Register 对话框
CFont Rfont;
IMPLEMENT_DYNAMIC(Register, CDialogEx)

Register::Register(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_Register, pParent)
	//, m_ISUser(FALSE)
	, m_ZH(_T(""))
	, m_MM(_T(""))
	, m_ISUser(FALSE)
{

}

Register::~Register()
{
}

void Register::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_zh, m_FontSetZH);
	DDX_Control(pDX, IDC_STATIC_mm, m_FontSetMM);
	//  DDX_Radio(pDX, IDC_RADIO1, m_ISUser);
	DDX_Text(pDX, IDC_EDIT_ZH, m_ZH);
	DDX_Text(pDX, IDC_EDIT_MM, m_MM);
	DDX_Radio(pDX, IDC_RADIO1, m_ISUser);
}


BEGIN_MESSAGE_MAP(Register, CDialogEx)
	ON_BN_CLICKED(IDOK, &Register::OnBnClickedOk)
	ON_BN_CLICKED(IDC_CHECK_Show, &Register::OnBnClickedCheckShow)
END_MESSAGE_MAP()


// Register 消息处理程序


void Register::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_ZH == "" || m_MM == "") {
		MessageBox(_T("账号或者密码不可为空！"), _T("错误提示"));
		return;
	}
	CString strCmd;
	if (m_ISUser == 0)
		strCmd.Format(_T("insert into tblAdministrator values('%s','%s')"), m_ZH, m_MM);
	else
		strCmd.Format(_T("insert into tblUser values('%s','%s')"), m_ZH, m_MM);
	AdoSql SSMS;
	SSMS.InitialConn();
	SSMS.ExcuteCmd(strCmd);
	UpdateData(FALSE);
	MessageBox(_T("注册成功!"), _T("注册成功提示"));
	Register::OnOK();
}


BOOL Register::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	Rfont.CreatePointFont(150, _T("宋体"));
	m_FontSetZH.SetFont(&Rfont);
	m_FontSetMM.SetFont(&Rfont);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void Register::OnBnClickedCheckShow()
{
	// TODO: 在此添加控件通知处理程序代码
	if (IsDlgButtonChecked(IDC_CHECK_Show) == BST_CHECKED)
	{
		UpdateData(true);
		CEdit* pEdit = (CEdit*)(this)->GetDlgItem(IDC_EDIT_MM);
		pEdit->SetPasswordChar(0);
		SetDlgItemText(IDC_EDIT_MM, m_MM);
		UpdateData(false);
	}
	else {
		UpdateData(true);
		CEdit* pEdit = (CEdit*)(this)->GetDlgItem(IDC_EDIT_MM);
		pEdit->SetPasswordChar('*');
		SetDlgItemText(IDC_EDIT_MM, m_MM);
		UpdateData(false);
	}
	GetDlgItem(IDC_EDIT_MM)->SetFocus();
}

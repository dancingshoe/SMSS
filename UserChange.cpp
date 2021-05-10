// UserChange.cpp: 实现文件
//

#include "pch.h"
#include "SMSS.h"
#include "UserChange.h"
#include "afxdialogex.h"
#include "User.h"

// UserChange 对话框

IMPLEMENT_DYNAMIC(UserChange, CDialogEx)

UserChange::UserChange(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_UserChange, pParent)
	, m_Pass(_T(""))
	, m_New(_T(""))
	, m_New2(_T(""))
{

}

UserChange::~UserChange()
{
}

void UserChange::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_Pass, m_Pass);
	DDX_Text(pDX, IDC_EDIT_New, m_New);
	DDX_Text(pDX, IDC_EDIT_New2, m_New2);
	DDX_Control(pDX, IDC_CHECK1, m_EditShow);
}


BEGIN_MESSAGE_MAP(UserChange, CDialogEx)
	ON_BN_CLICKED(IDOK, &UserChange::OnBnClickedOk)
	ON_BN_CLICKED(IDC_CHECK1, &UserChange::OnBnClickedCheck1)
END_MESSAGE_MAP()


// UserChange 消息处理程序


void UserChange::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
	UpdateData(TRUE);
	User* pdlg = User::pUserdlg;
	CString str = pdlg->m_UserIFO;
	CString Password;
	CString Pass;
	_bstr_t strCmd;
	AdoSql SSMS;
	SSMS.InitialConn();
	SSMS.GetRecordSet(_T("select * from tblUser"));
	while (!SSMS.m_pRecordSet->adoEOF)
	{
		if (str == (char*)(_bstr_t)SSMS.m_pRecordSet->GetCollect("UserID"))
		{
			Password = (char*)(_bstr_t)SSMS.m_pRecordSet->GetCollect("UserPasswod");
			break;
		}
		SSMS.m_pRecordSet->MoveNext();
	}
	if (m_Pass == Password) {
		if (m_New == m_New2)
		{
			Pass.Format(_T("Update tblUser set UserPasswod = '%s' where UserID = '%s'"), m_New, str);
			SSMS.ExcuteCmd(Pass);
			MessageBox(_T("密码修改成功!"));
			UserChange::OnOK();
		}
		else
			MessageBox(_T("两次密码应相同!"));
	}
	else
		MessageBox(_T("旧密码输入错误!"));
}


void UserChange::OnBnClickedCheck1()
{
	// TODO: 在此添加控件通知处理程序代码
	if (IsDlgButtonChecked(IDC_CHECK1) == BST_CHECKED)
	{
		UpdateData(true);
		CEdit* pEdit = (CEdit*)(this)->GetDlgItem(IDC_EDIT_New);
		pEdit->SetPasswordChar(0);
		SetDlgItemText(IDC_EDIT_New2, m_New2);
		CEdit* pEdit2 = (CEdit*)(this)->GetDlgItem(IDC_EDIT_New2);
		pEdit2->SetPasswordChar(0);
		SetDlgItemText(IDC_EDIT_New2, m_New2);
		UpdateData(false);
	}
	else {
		UpdateData(true);
		CEdit* pEdit = (CEdit*)(this)->GetDlgItem(IDC_EDIT_New);
		pEdit->SetPasswordChar('*');
		SetDlgItemText(IDC_EDIT_New, m_New);
		CEdit* pEdit2 = (CEdit*)(this)->GetDlgItem(IDC_EDIT_New2);
		pEdit2->SetPasswordChar('*');
		SetDlgItemText(IDC_EDIT_New2, m_New2);
		UpdateData(false);
	}
	GetDlgItem(IDC_EDIT_New)->SetFocus();
}

// AddCom.cpp: 实现文件
//

#include "pch.h"
#include "SMSS.h"
#include "AddCom.h"
#include "afxdialogex.h"


// AddCom 对话框

IMPLEMENT_DYNAMIC(AddCom, CDialogEx)

AddCom::AddCom(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_AddCom, pParent)
	, m_AddID(_T(""))
	, m_AddName(_T(""))
	, m_AddPDate(_T(""))
	, m_AddPrice(0)
	, m_AddSLife(_T(""))
	, m_AddIven(0)
{

}

AddCom::~AddCom()
{
}

void AddCom::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_AddID, m_AddID);
	//  DDX_Text(pDX, IDC_EDIT_AddIven, m_AddIven);
	DDX_Text(pDX, IDC_EDIT_AddName, m_AddName);
	DDX_Text(pDX, IDC_EDIT_AddPDate, m_AddPDate);
	DDX_Text(pDX, IDC_EDIT_AddPrice, m_AddPrice);
	DDX_Text(pDX, IDC_EDIT_AddSLife, m_AddSLife);
	DDX_Text(pDX, IDC_EDIT_AddIven, m_AddIven);
}


BEGIN_MESSAGE_MAP(AddCom, CDialogEx)
	ON_BN_CLICKED(IDOK, &AddCom::OnBnClickedOk)
END_MESSAGE_MAP()


// AddCom 消息处理程序


void AddCom::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	AdoSql adosql;
	adosql.InitialConn();
	CString strCmd;
	strCmd.Format(_T("insert into tblCommodity values('%s','%s','%d','%s','%s','%d')"),m_AddID,m_AddName,m_AddPrice,m_AddPDate,m_AddSLife,m_AddIven);
	adosql.ExcuteCmd(strCmd);
	MessageBox(_T("入库成功!"));
	CDialogEx::OnOK();
}

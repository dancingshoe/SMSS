// ComChange.cpp: 实现文件
//

#include "pch.h"
#include "SMSS.h"
#include "ComChange.h"
#include "afxdialogex.h"
#include "Admin.h"

// ComChange 对话框

IMPLEMENT_DYNAMIC(ComChange, CDialogEx)

ComChange::ComChange(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_ComChange, pParent)
	, m_CIven(0)
	, m_CName(_T(""))
	, m_CPDate(_T(""))
	, m_CPrice(0)
	, m_CSLife(_T(""))
	, m_ShowCom(_T(""))
{

}

ComChange::~ComChange()
{
}

void ComChange::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_EDIT_CAddID, m_CID);
	DDX_Text(pDX, IDC_EDIT_CAddIven, m_CIven);
	//  DDX_Text(pDX, IDC_EDIT_CAddName, M);
	DDX_Text(pDX, IDC_EDIT_CAddName, m_CName);
	DDX_Text(pDX, IDC_EDIT_CAddPDate, m_CPDate);
	DDX_Text(pDX, IDC_EDIT_CAddPrice, m_CPrice);
	DDX_Text(pDX, IDC_EDIT_CAddSLife, m_CSLife);
	DDX_Text(pDX, IDC_EDIT_ShouCom, m_ShowCom);
}


BEGIN_MESSAGE_MAP(ComChange, CDialogEx)
	ON_BN_CLICKED(IDOK, &ComChange::OnBnClickedOk)
END_MESSAGE_MAP()


// ComChange 消息处理程序


void ComChange::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	AdoSql adosql;
	adosql.InitialConn();
	CString strCmd;
	Admin* pdlg1 = Admin::pAdmindlg;
	CString str = pdlg1->m_ListAdmin.GetItemText(AdminnItem,0);
	strCmd.Format(_T("update tblCommodity set ComName = '%s', ComPrice = '%d', ComPDate = '%s',ComSLife = '%s',ComInventory = '%d' where ComID = '%s'"),m_CName,m_CPrice,m_CPDate,m_CSLife,m_CIven,str);
	adosql.ExcuteCmd(strCmd);
	MessageBox(_T("信息修改成功!"));
	CDialogEx::OnOK();
}


BOOL ComChange::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	Admin* pdlg = Admin::pAdmindlg;
	m_ShowCom = pdlg->m_ListAdmin.GetItemText(AdminnItem,1);
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

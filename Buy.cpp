// Buy.cpp: 实现文件
//

#include "pch.h"
#include "SMSS.h"
#include "Buy.h"
#include "afxdialogex.h"
#include "User.h"
#include <time.h> 

// Buy 对话框

IMPLEMENT_DYNAMIC(Buy, CDialogEx)

Buy::Buy(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_Buy, pParent)
	, m_BuyNum(0)
{

}

Buy::~Buy()
{
}

void Buy::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_BuyNum);
}


BEGIN_MESSAGE_MAP(Buy, CDialogEx)
	ON_BN_CLICKED(IDOK, &Buy::OnBnClickedOk)
END_MESSAGE_MAP()


// Buy 消息处理程序


void Buy::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	AdoSql adoSql;
	UpdateData(TRUE);
	User* pdlg = User::pUserdlg;
	CString str = pdlg->m_ListUser.GetItemText(nItem,0);//商品号
	CString strCmd;
	adoSql.InitialConn();
	strCmd.Format(_T("update tblCommodity set ComInventory -= '%d' where ComID = '%s' "),m_BuyNum,str);
	adoSql.ExcuteCmd(strCmd);
	MessageBox(_T("购买成功!"));

	int temp = 1000 + rand() % 9999;
	CString Ord;
	Ord.Format(_T("%d"), temp);
	CString UserIFO = pdlg->m_UserIFO;//用户名
	strCmd.Format(_T("insert into tblOrder values('%s','%s','%s','%d',GETDATE()) "),Ord,str,UserIFO,m_BuyNum);
	adoSql.ExcuteCmd(strCmd);
	CDialogEx::OnOK();
}

// User.cpp: 实现文件
//

#include "pch.h"
#include "SMSS.h"
#include "User.h"
#include "SMSSDlg.h"
#include "afxdialogex.h"
#include "Buy.h"
#include "UserChange.h"

// User 对话框
CFont RFont;
int nItem;
User* User::pUserdlg = NULL;

IMPLEMENT_DYNAMIC(User, CDialogEx)

User::User(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_User, pParent)
	, m_OrdMess(_T(""))
	, m_UserIFO(_T(""))
{

}

User::~User()
{
}

void User::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_OrderMessage, m_OrdMess);
	DDX_Control(pDX, IDC_LIST_User, m_ListUser);
	DDX_Control(pDX, IDC_STATIC_Find, m_StaticFind);
	DDX_Text(pDX, IDC_EDIT3, m_UserIFO);
}


BEGIN_MESSAGE_MAP(User, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_Store, &User::OnBnClickedButtonStore)
	ON_BN_CLICKED(IDC_BUTTON_Buy, &User::OnBnClickedButtonBuy)
	ON_BN_CLICKED(IDC_BUTTON_Manage, &User::OnBnClickedButtonManage)
	ON_BN_CLICKED(IDC_BUTTON_Return, &User::OnBnClickedButtonReturn)
	ON_BN_CLICKED(IDC_BUTTON_Change, &User::OnBnClickedButtonChange)
	ON_BN_CLICKED(IDC_BUTTON_FindUser, &User::OnBnClickedButtonFinduser)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_User, &User::OnLvnItemchangedListUser)
	ON_BN_CLICKED(IDCANCEL_User, &User::OnBnClickedUser)
END_MESSAGE_MAP()

void User::Display()
{
	AdoSql adoSql;
	adoSql.GetRecordSet(_T("select * from tblCommodity"));
	//初始化数据表
	m_ListUser.SetExtendedStyle(m_ListUser.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	//先清空数据表
	CRect rect;
	m_ListUser.GetClientRect(&rect);
	m_ListUser.DeleteAllItems();
	int nColumnCount = m_ListUser.GetHeaderCtrl()->GetItemCount();
	for (int i = 0; i < nColumnCount; i++)
	{
		m_ListUser.DeleteColumn(0);
	}
	m_ListUser.InsertColumn(0, _T("商品号"), LVCFMT_LEFT, rect.Width() / 5);
	m_ListUser.InsertColumn(1, _T("商品名"), LVCFMT_LEFT, rect.Width() / 5);
	m_ListUser.InsertColumn(2, _T("价格"), LVCFMT_LEFT, rect.Width() / 5);
	m_ListUser.InsertColumn(3, _T("生产日期"), LVCFMT_LEFT, rect.Width() / 5);
	m_ListUser.InsertColumn(4, _T("保质期"), LVCFMT_LEFT, rect.Width() / 5);

	int i = 0;
	while (!adoSql.m_pRecordSet->adoEOF)
	{
		m_ListUser.InsertItem(i,_T(""));
		m_ListUser.SetItemText(i, 0, (_bstr_t)adoSql.m_pRecordSet->GetCollect("ComID"));
		m_ListUser.SetItemText(i, 1, (_bstr_t)adoSql.m_pRecordSet->GetCollect("ComName"));
		m_ListUser.SetItemText(i, 2, (_bstr_t)adoSql.m_pRecordSet->GetCollect("ComPrice"));
		m_ListUser.SetItemText(i, 3, (_bstr_t)adoSql.m_pRecordSet->GetCollect("ComPDate"));
		m_ListUser.SetItemText(i, 4, (_bstr_t)adoSql.m_pRecordSet->GetCollect("ComSLife"));

		adoSql.m_pRecordSet->MoveNext();
		i++;
	}
	adoSql.ExitConn();
}

void User::DisplayOrder()
{	
	AdoSql adoSql;
	adoSql.GetRecordSet(_T("select * from tblOrder"));
	//初始化数据表
	m_ListUser.SetExtendedStyle(m_ListUser.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	//先清空数据表
	CRect rect;
	m_ListUser.GetClientRect(&rect);
	m_ListUser.DeleteAllItems();
	int nColumnCount = m_ListUser.GetHeaderCtrl()->GetItemCount();
	for (int i = 0; i < nColumnCount; i++)
	{
		m_ListUser.DeleteColumn(0);
	}
	m_ListUser.InsertColumn(0, _T("订单号"), LVCFMT_LEFT, rect.Width() / 5);
	m_ListUser.InsertColumn(1, _T("商品号"), LVCFMT_LEFT, rect.Width() / 5);
	m_ListUser.InsertColumn(2, _T("用户"), LVCFMT_LEFT, rect.Width() / 5);
	m_ListUser.InsertColumn(3, _T("购买数量"), LVCFMT_LEFT, rect.Width() / 5);
	m_ListUser.InsertColumn(4, _T("购买日期"), LVCFMT_LEFT, rect.Width() / 5);

	int i = 0;
	UpdateData(TRUE);
	while (!adoSql.m_pRecordSet->adoEOF)
	{
		if ((char*)(_bstr_t)adoSql.m_pRecordSet->GetCollect("UserID") == m_UserIFO)
		{
			m_ListUser.InsertItem(i, _T(""));
			m_ListUser.SetItemText(i, 0, (_bstr_t)adoSql.m_pRecordSet->GetCollect("OrdID"));
			m_ListUser.SetItemText(i, 1, (_bstr_t)adoSql.m_pRecordSet->GetCollect("ComID"));
			m_ListUser.SetItemText(i, 2, (_bstr_t)adoSql.m_pRecordSet->GetCollect("UserID"));
			m_ListUser.SetItemText(i, 3, (_bstr_t)adoSql.m_pRecordSet->GetCollect("ordQuantity"));
			m_ListUser.SetItemText(i, 4, (_bstr_t)adoSql.m_pRecordSet->GetCollect("OrdDate"));
		}
		adoSql.m_pRecordSet->MoveNext();
		i++;
	}
	adoSql.ExitConn();
}
// User 消息处理程序

BOOL User::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	Display();
	RFont.CreatePointFont(200, _T("宋体"));
	m_StaticFind.SetFont(&RFont);
	pUserdlg = this;  //为这个之前定义的指针变量赋值为主对话框指针

	CSMSSDlg* pdlg = CSMSSDlg::pUser;
	m_UserIFO = pdlg->m_LoginZH;
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


//显示商城
void User::OnBnClickedButtonStore()
{
	Display();
}

//购买
void User::OnBnClickedButtonBuy()
{
	// TODO: 在此添加控件通知处理程序代码
	Buy dlg;
	dlg.DoModal();
}

//订单管理
void User::OnBnClickedButtonManage()
{
	// TODO: 在此添加控件通知处理程序代码
	DisplayOrder();
}

//退货
void User::OnBnClickedButtonReturn()
{
	// TODO: 在此添加控件通知处理程序代码
	AdoSql adoSql;
	UpdateData(TRUE);
	CString strCmd;
	int k;
	k = MessageBox(_T("确认退货吗?"), _T("退货提示"), MB_YESNO);
	if (k == 7);
	else {
		strCmd.Format(_T("delete from tblOrder where OrdID = '%s'"), m_ListUser.GetItemText(nItem, 0));
		adoSql.InitialConn();
		adoSql.ExcuteCmd(strCmd);
		MessageBox(_T("退货成功!"));
	}
	DisplayOrder();
}

//个人信息修改
void User::OnBnClickedButtonChange()
{
	// TODO: 在此添加控件通知处理程序代码
	UserChange dlg;
	dlg.DoModal();
}

//订单查询
void User::OnBnClickedButtonFinduser()
{
	// TODO: 在此添加控件通知处理程序代码
}

//ListControl
void User::OnLvnItemchangedListUser(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	//*pResult = 0;
	DWORD dwPos = GetMessagePos();
	CPoint point(LOWORD(dwPos), HIWORD(dwPos));//得到鼠标位置
	m_ListUser.ScreenToClient(&point);//该函数可以将屏幕上鼠标的位置转换为程序的客户区的坐标
	LVHITTESTINFO lvinfo;
	lvinfo.pt = point;
	lvinfo.flags = LVHT_ABOVE;
	nItem = m_ListUser.SubItemHitTest(&lvinfo);//获取点击列
}


void User::OnBnClickedUser()
{
	// TODO: 在此添加控件通知处理程序代码
	User::OnOK();
}

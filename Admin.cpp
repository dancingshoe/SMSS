﻿// Admin.cpp: 实现文件
//

#include "pch.h"
#include "SMSS.h"
#include "Admin.h"
#include "afxdialogex.h"
#include "AddCom.h"
#include "ComChange.h"

int AdminnItem;
CFont Sfont;
Admin* Admin::pAdmindlg = NULL;
// Admin 对话框
IMPLEMENT_DYNAMIC(Admin, CDialogEx)

Admin::Admin(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_Admin, pParent)
	, m_OrderIFO(_T(""))
{

}

Admin::~Admin()
{
}

void Admin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_OrderIFO, m_OrderIFO);
	DDX_Control(pDX, IDC_STATIC_FindOrd, m_FindOrder);
	DDX_Control(pDX, IDC_LIST_AdminCom, m_ListAdmin);
}


BEGIN_MESSAGE_MAP(Admin, CDialogEx)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_AdminCom, &Admin::OnLvnItemchangedListAdmincom)
	ON_BN_CLICKED(IDC_BUTTON_Store, &Admin::OnBnClickedButtonStore)
	ON_BN_CLICKED(IDC_BUTTON_Enter, &Admin::OnBnClickedButtonEnter)
	ON_BN_CLICKED(IDC_BUTTON_Delete, &Admin::OnBnClickedButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_ChangeCom, &Admin::OnBnClickedButtonChangecom)
	ON_BN_CLICKED(IDC_BUTTON_OrdManage, &Admin::OnBnClickedButtonOrdmanage)
END_MESSAGE_MAP()


// Admin 消息处理程序


void Admin::OnLvnItemchangedListAdmincom(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	//*pResult = 0;
	DWORD dwPos = GetMessagePos();
	CPoint point(LOWORD(dwPos), HIWORD(dwPos));//得到鼠标位置
	m_ListAdmin.ScreenToClient(&point);//该函数可以将屏幕上鼠标的位置转换为程序的客户区的坐标
	LVHITTESTINFO lvinfo;
	lvinfo.pt = point;
	lvinfo.flags = LVHT_ABOVE;
	AdminnItem = m_ListAdmin.SubItemHitTest(&lvinfo);//获取点击列
}


BOOL Admin::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	pAdmindlg = this;
	Sfont.CreatePointFont(150, _T("宋体"));
	m_FindOrder.SetFont(&Sfont);
	AdminDisPlay();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void Admin::AdminDisPlay()
{
	AdoSql adoSql;
	adoSql.GetRecordSet(_T("select * from tblCommodity"));
	//初始化数据表
	m_ListAdmin.SetExtendedStyle(m_ListAdmin.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	//先清空数据表
	CRect rect;
	m_ListAdmin.GetClientRect(&rect);
	m_ListAdmin.DeleteAllItems();
	int nColumnCount = m_ListAdmin.GetHeaderCtrl()->GetItemCount();
	for (int i = 0; i < nColumnCount; i++)
	{
		m_ListAdmin.DeleteColumn(0);
	}
	m_ListAdmin.InsertColumn(0, _T("商品号"), LVCFMT_LEFT, rect.Width() / 6);
	m_ListAdmin.InsertColumn(1, _T("商品名"), LVCFMT_LEFT, rect.Width() / 6);
	m_ListAdmin.InsertColumn(2, _T("价格"), LVCFMT_LEFT, rect.Width() / 6);
	m_ListAdmin.InsertColumn(3, _T("生产日期"), LVCFMT_LEFT, rect.Width() / 6);
	m_ListAdmin.InsertColumn(4, _T("保质期"), LVCFMT_LEFT, rect.Width() / 6);
	m_ListAdmin.InsertColumn(5, _T("库存"), LVCFMT_LEFT, rect.Width() / 6);

	int i = 0;
	UpdateData(TRUE);
	while (!adoSql.m_pRecordSet->adoEOF)
	{
		m_ListAdmin.InsertItem(i, _T(""));
		m_ListAdmin.SetItemText(i, 0, (_bstr_t)adoSql.m_pRecordSet->GetCollect("ComID"));
		m_ListAdmin.SetItemText(i, 1, (_bstr_t)adoSql.m_pRecordSet->GetCollect("ComName"));
		m_ListAdmin.SetItemText(i, 2, (_bstr_t)adoSql.m_pRecordSet->GetCollect("ComPrice"));
		m_ListAdmin.SetItemText(i, 3, (_bstr_t)adoSql.m_pRecordSet->GetCollect("ComPDate"));
		m_ListAdmin.SetItemText(i, 4, (_bstr_t)adoSql.m_pRecordSet->GetCollect("ComSLife"));
		m_ListAdmin.SetItemText(i, 5, (_bstr_t)adoSql.m_pRecordSet->GetCollect("ComInventory"));

		adoSql.m_pRecordSet->MoveNext();
		i++;
	}
	adoSql.ExitConn();
}

void Admin::AdminOrdDisPlay()
{
	AdoSql adoSql;
	adoSql.GetRecordSet(_T("select * from tblOrder"));
	//初始化数据表
	m_ListAdmin.SetExtendedStyle(m_ListAdmin.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	//先清空数据表
	CRect rect;
	m_ListAdmin.GetClientRect(&rect);
	m_ListAdmin.DeleteAllItems();
	int nColumnCount = m_ListAdmin.GetHeaderCtrl()->GetItemCount();
	for (int i = 0; i < nColumnCount; i++)
	{
		m_ListAdmin.DeleteColumn(0);
	}
	m_ListAdmin.InsertColumn(0, _T("订单号"), LVCFMT_LEFT, rect.Width() / 5);
	m_ListAdmin.InsertColumn(1, _T("商品号"), LVCFMT_LEFT, rect.Width() / 5);
	m_ListAdmin.InsertColumn(2, _T("用户"), LVCFMT_LEFT, rect.Width() / 5);
	m_ListAdmin.InsertColumn(3, _T("购买数量"), LVCFMT_LEFT, rect.Width() / 5);
	m_ListAdmin.InsertColumn(4, _T("购买日期"), LVCFMT_LEFT, rect.Width() / 5);

	int i = 0;
	UpdateData(TRUE);
	while (!adoSql.m_pRecordSet->adoEOF)
	{
		m_ListAdmin.InsertItem(i, _T(""));
		m_ListAdmin.SetItemText(i, 0, (_bstr_t)adoSql.m_pRecordSet->GetCollect("OrdID"));
		m_ListAdmin.SetItemText(i, 1, (_bstr_t)adoSql.m_pRecordSet->GetCollect("ComID"));
		m_ListAdmin.SetItemText(i, 2, (_bstr_t)adoSql.m_pRecordSet->GetCollect("UserID"));
		m_ListAdmin.SetItemText(i, 3, (_bstr_t)adoSql.m_pRecordSet->GetCollect("ordQuantity"));
		m_ListAdmin.SetItemText(i, 4, (_bstr_t)adoSql.m_pRecordSet->GetCollect("OrdDate"));
		
		adoSql.m_pRecordSet->MoveNext();
		i++;
	}
	adoSql.ExitConn();
}


void Admin::OnBnClickedButtonStore()
{
	// TODO: 在此添加控件通知处理程序代码
	AdminDisPlay();
}


//商品入库
void Admin::OnBnClickedButtonEnter()
{
	// TODO: 在此添加控件通知处理程序代码
	AddCom dlg;
	dlg.DoModal();
}


//清除过期商品
void Admin::OnBnClickedButtonDelete()
{
	// TODO: 在此添加控件通知处理程序代码
	AdoSql adosql;
	adosql.InitialConn();
	CString strCmd;
	strCmd.Format(_T("delete from  tblCommodity where GETDATE() > ComSLife"));
	adosql.ExcuteCmd(strCmd);
	MessageBox(_T("清除过期库存成功!"));
}


//商品信息修改
void Admin::OnBnClickedButtonChangecom()
{
	// TODO: 在此添加控件通知处理程序代码
	ComChange dlg;
	dlg.DoModal();
}


void Admin::OnBnClickedButtonOrdmanage()
{
	// TODO: 在此添加控件通知处理程序代码
	AdminOrdDisPlay();
}

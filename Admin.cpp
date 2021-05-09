// Admin.cpp: 实现文件
//

#include "pch.h"
#include "SMSS.h"
#include "Admin.h"
#include "afxdialogex.h"


// Admin 对话框

IMPLEMENT_DYNAMIC(Admin, CDialogEx)

Admin::Admin(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_Admin, pParent)
{

}

Admin::~Admin()
{
}

void Admin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Admin, CDialogEx)
END_MESSAGE_MAP()


// Admin 消息处理程序

// User.cpp: 实现文件
//

#include "pch.h"
#include "SMSS.h"
#include "User.h"
#include "afxdialogex.h"


// User 对话框

IMPLEMENT_DYNAMIC(User, CDialogEx)

User::User(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_User, pParent)
{

}

User::~User()
{
}

void User::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(User, CDialogEx)
END_MESSAGE_MAP()


// User 消息处理程序

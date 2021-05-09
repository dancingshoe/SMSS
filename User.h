#pragma once


// User 对话框

class User : public CDialogEx
{
	DECLARE_DYNAMIC(User)

public:
	User(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~User();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_User };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};

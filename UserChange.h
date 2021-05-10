#pragma once


// UserChange 对话框

class UserChange : public CDialogEx
{
	DECLARE_DYNAMIC(UserChange)

public:
	UserChange(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~UserChange();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_UserChange };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_Pass;
	CString m_New;
	CString m_New2;
	afx_msg void OnBnClickedOk();
	CButton m_EditShow;
	afx_msg void OnBnClickedCheck1();
};

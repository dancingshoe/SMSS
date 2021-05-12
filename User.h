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
public:
	CString m_OrdMess;
	afx_msg void OnBnClickedButtonStore();
	afx_msg void OnBnClickedButtonBuy();
	afx_msg void OnBnClickedButtonManage();
	afx_msg void OnBnClickedButtonReturn();
	afx_msg void OnBnClickedButtonChange();
	afx_msg void OnBnClickedButtonFinduser();
	virtual BOOL OnInitDialog();
	CListCtrl m_ListUser;
	CStatic m_StaticFind;
	void Display();
	void DisplayOrder();
	afx_msg void OnLvnItemchangedListUser(NMHDR* pNMHDR, LRESULT* pResult);
	static User* pUserdlg;
//	CString m_BuyMessage;
	CString m_UserIFO;
	afx_msg void OnBnClickedUser();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
};

extern int nItem;

#pragma once


// Admin 对话框

class Admin : public CDialogEx
{
	DECLARE_DYNAMIC(Admin)

public:
	Admin(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Admin();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_Admin };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_OrderIFO;
	CStatic m_FindOrder;
	CListCtrl m_ListAdmin;
	void AdminDisPlay();
	void AdminOrdDisPlay();
	afx_msg void OnLvnItemchangedListAdmincom(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonStore();
	afx_msg void OnBnClickedButtonEnter();
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnBnClickedButtonChangecom();
	afx_msg void OnBnClickedButtonOrdmanage();
	static Admin* pAdmindlg;
	afx_msg void OnBnClickedButtonFindorder();
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};

extern int AdminnItem;

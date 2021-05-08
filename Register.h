#pragma once


// Register 对话框

class Register : public CDialogEx
{
	DECLARE_DYNAMIC(Register)

public:
	Register(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Register();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_Register };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_FontSetZH;
	CStatic m_FontSetMM;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
//	BOOL m_ISUser;
	CString m_ZH;
	CString m_MM;
	afx_msg void OnBnClickedCheckShow();
	BOOL m_ISUser;
};

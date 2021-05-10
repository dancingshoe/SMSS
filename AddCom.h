#pragma once


// AddCom 对话框

class AddCom : public CDialogEx
{
	DECLARE_DYNAMIC(AddCom)

public:
	AddCom(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~AddCom();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_AddCom };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_AddID;
//	CString m_AddIven;
	CString m_AddName;
	CString m_AddPDate;
	int m_AddPrice;
	CString m_AddSLife;
	int m_AddIven;
	afx_msg void OnBnClickedOk();
};

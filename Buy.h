#pragma once


// Buy 对话框

class Buy : public CDialogEx
{
	DECLARE_DYNAMIC(Buy)

public:
	Buy(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Buy();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_Buy };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
//	CString m_BuyNum;
	afx_msg void OnBnClickedOk();
	int m_BuyNum;
//	CString m_F;
};

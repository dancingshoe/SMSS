#pragma once


// ComChange 对话框

class ComChange : public CDialogEx
{
	DECLARE_DYNAMIC(ComChange)

public:
	ComChange(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~ComChange();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ComChange };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
//	CString m_CID;
	int m_CIven;
//	CString M;
	CString m_CName;
	CString m_CPDate;
	int m_CPrice;
	CString m_CSLife;
	CString m_ShowCom;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};

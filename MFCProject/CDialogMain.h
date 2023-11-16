#pragma once


// CDialogMain dialog

class CDialogMain : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogMain)

public:
	CDialogMain(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CDialogMain();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MAIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnClickedButtonDebug();
};

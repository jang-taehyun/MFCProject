#pragma once


// CDialogModify dialog

class CDialogModify : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogModify)

public:
	CDialogModify(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CDialogModify();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MOD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};

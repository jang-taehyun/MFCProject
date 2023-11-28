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
public:
	afx_msg void OnClickedButtonAdd();
	afx_msg void OnClickedButtonDelete();
	afx_msg void OnClickedButtonModify();
	CDateTimeCtrl m_dtpSelectDate;
	CDateTimeCtrl m_dtpStartTime;
	CDateTimeCtrl m_dtpEndTime;

	COleDateTime GivenDate;
	virtual BOOL OnInitDialog();
	CListBox m_listCategory;
	afx_msg void OnSelchangeListCategory();
	afx_msg void OnDatetimechangeDatetimepickerSelectDate(NMHDR* pNMHDR, LRESULT* pResult);
};

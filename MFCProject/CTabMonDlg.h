#pragma once
#include "afxdialogex.h"


// CTabMonDlg 대화 상자

class CTabMonDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTabMonDlg)

public:
	CTabMonDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CTabMonDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_OBJECT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_strSchedule;
	virtual BOOL OnInitDialog();
	int m_SunToSat;
	// ---------- 13주차 추가 코드 ---------- //
	afx_msg void OnChangeEditSchedule();
	// ---------- 13주차 추가 코드 ---------- //
};

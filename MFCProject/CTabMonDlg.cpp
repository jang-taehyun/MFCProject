// CTabMonDlg.cpp: 구현 파일
//

#include "pch.h"
#include "MFCProject.h"
#include "afxdialogex.h"
#include "CTabMonDlg.h"


// CTabMonDlg 대화 상자

IMPLEMENT_DYNAMIC(CTabMonDlg, CDialogEx)

CTabMonDlg::CTabMonDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_OBJECT, pParent)
	, m_strSchedule(_T(""))
{

}

CTabMonDlg::~CTabMonDlg()
{
}

void CTabMonDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SCHEDULE, m_strSchedule);
}


BEGIN_MESSAGE_MAP(CTabMonDlg, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT_SCHEDULE, &CTabMonDlg::OnChangeEditSchedule)
END_MESSAGE_MAP()


// CTabMonDlg 메시지 처리기


BOOL CTabMonDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	//m_strSchedule = _T("Schedule Init");
	//m_strSchedule.Format("%d", m_SunToSat);
	UpdateData(FALSE);


	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


// ---------- 13주차 추가 코드 ---------- //
void CTabMonDlg::OnChangeEditSchedule()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	SetDlgItemText(IDC_EDIT_SCHEDULE, m_strSchedule);
}
// ---------- 13주차 추가 코드 ---------- //
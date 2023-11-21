// CDialogModify.cpp : implementation file
//

#include "pch.h"
#include "MFCProject.h"
#include "CDialogModify.h"
#include "afxdialogex.h"

#include "CCSVFile.h"
#include "CChangeDataFormat.h"

// CDialogModify dialog

IMPLEMENT_DYNAMIC(CDialogModify, CDialogEx)

CDialogModify::CDialogModify(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_MOD, pParent)
{

}

CDialogModify::~CDialogModify()
{
}

void CDialogModify::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIMEPICKER_SELECT_DATE, m_dtpSelectDate);
	DDX_Control(pDX, IDC_DATETIMEPICKER_START, m_dtpStartTime);
	DDX_Control(pDX, IDC_DATETIMEPICKER_END, m_dtpEndTime);
}


BEGIN_MESSAGE_MAP(CDialogModify, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CDialogModify::OnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CDialogModify::OnClickedButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY, &CDialogModify::OnClickedButtonModify)
END_MESSAGE_MAP()


// CDialogModify message handlers


void CDialogModify::OnClickedButtonAdd()
{
	// TODO: Add your control notification handler code here
	AfxMessageBox(_T("추가 버튼이 눌렸습니다."));

	// dialog에 설정되어 있는 값들을 CSV 형식으로 만들기
	FILEDATA data;
	CCSVFile::GetCSVFileInterface()->MakeDataFormat(data, m_dtpSelectDate, m_dtpStartTime, m_dtpEndTime);

	// CSV 파일에 데이터 추가
	CCSVFile::GetCSVFileInterface()->AddData(data);
}


void CDialogModify::OnClickedButtonDelete()
{
	// TODO: Add your control notification handler code here
	AfxMessageBox(_T("삭제 버튼이 눌렸습니다."));

	FILEDATA data;
	CString strCurrentDate = _T("");

	// 현재 날짜를 CString 타입으로 변환
	CChangeDataFormat::GetInst()->ChangeDateToCString(strCurrentDate, m_dtpSelectDate);

	// CSV 파일 안에 저장된 데이터 중, 현재 날짜로 저장된 데이터를 찾아 삭제
	int count = CCSVFile::GetCSVFileInterface()->GetDataCount();
	for (int i = 0; i < count; i++)
	{
		CCSVFile::GetCSVFileInterface()->GetData(i, data);
		if (data.m_strDate == strCurrentDate)
		{
			CCSVFile::GetCSVFileInterface()->DeleteData(i);
			break;
		}
	}
}


void CDialogModify::OnClickedButtonModify()
{
	// TODO: Add your control notification handler code here
	AfxMessageBox(_T("수정 버튼이 눌렸습니다."));

	FILEDATA data;
	CString strCurrentDate = _T("");

	// dialog에 설정되어 있는 값들을 CSV 형식으로 만들기
	CCSVFile::GetCSVFileInterface()->MakeDataFormat(data, m_dtpSelectDate, m_dtpStartTime, m_dtpEndTime);

	// 현재 설정된 날짜를 CString 형식으로 바꾸기
	CChangeDataFormat::GetInst()->ChangeDateToCString(strCurrentDate, m_dtpSelectDate);

	// CSV 파일 안에 저장된 데이터 중, 현재 날짜로 저장된 데이터를 찾아 수정
	int count = CCSVFile::GetCSVFileInterface()->GetDataCount();
	for (int i = 0; i < count; i++)
	{
		CCSVFile::GetCSVFileInterface()->GetData(i, data);
		if (data.m_strDate == strCurrentDate)
		{
			CCSVFile::GetCSVFileInterface()->ModifyData(i, data);
			break;
		}
	}
}


BOOL CDialogModify::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	VERIFY(m_dtpSelectDate.SetTime(GivenDate));
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

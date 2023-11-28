// CDialogModify.cpp : implementation file
//

#include "pch.h"
#include "MFCProject.h"
#include "CDialogModify.h"
#include "afxdialogex.h"

#include "CCSVFile.h"
#include "CChangeDataFormat.h"
#include <queue>

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
	DDX_Control(pDX, IDC_LIST_CATEGORY, m_listCategory);
}


BEGIN_MESSAGE_MAP(CDialogModify, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CDialogModify::OnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CDialogModify::OnClickedButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY, &CDialogModify::OnClickedButtonModify)
	ON_LBN_SELCHANGE(IDC_LIST_CATEGORY, &CDialogModify::OnSelchangeListCategory)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER_SELECT_DATE, &CDialogModify::OnDatetimechangeDatetimepickerSelectDate)
END_MESSAGE_MAP()


// CDialogModify message handlers


void CDialogModify::OnClickedButtonAdd()
{
	// TODO: Add your control notification handler code here
	AfxMessageBox(_T("추가 버튼이 눌렸습니다."));

	// dialog에 설정되어 있는 값들을 CSV 형식으로 만들기
	FILEDATA data;
	CCSVFile::GetCSVFileInterface()->MakeDataFormat(data, m_dtpSelectDate, m_dtpStartTime, m_dtpEndTime);

	// edit control에 입력된 내용을 가져와 FILEDATA 구조체에 저장한다.
	CString strtmp;
	GetDlgItemText(IDC_EDIT_TEXT_INPUT, strtmp);
	data.m_strCategory = strtmp;

	// CSV 파일에 데이터 추가
	CCSVFile::GetCSVFileInterface()->AddData(data);

	// edit control에 입력된 문자열을 list box에 저장
	m_listCategory.AddString(strtmp);
}


void CDialogModify::OnClickedButtonDelete()
{
	// TODO: Add your control notification handler code here
	AfxMessageBox(_T("삭제 버튼이 눌렸습니다."));

	FILEDATA data;
	CString strCurrentDate = _T("");
	CString strCurrentCategory = _T("");

	// 현재 list box에서 선택된 data를 가져온다.
	int index = m_listCategory.GetCurSel();
	m_listCategory.GetText(index, strCurrentCategory);

	// 현재 날짜를 CString 타입으로 변환
	CChangeDataFormat::ChangeDateToCString(strCurrentDate, m_dtpSelectDate);

	// CSV 파일 안에 저장된 데이터 중, 현재 날짜와 선택된 category로 저장된 데이터를 찾아 삭제
	int count = CCSVFile::GetCSVFileInterface()->GetDataCount();
	for (int i = 0; i < count; i++)
	{
		CCSVFile::GetCSVFileInterface()->GetData(i, data);
		// ---------- 13주차 추가 코드 ---------- //
		if (data.m_strDate == strCurrentDate && data.m_strCategory == strCurrentCategory)
			// ---------- 13주차 추가 코드 ---------- //
		{
			CCSVFile::GetCSVFileInterface()->DeleteData(i);

			// listbox에 저장된 data 삭제
			int index = m_listCategory.FindString(0, data.m_strCategory);
			m_listCategory.DeleteString(index);
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
	// ---------- 13주차 추가 코드 ---------- //
	CString strCurrentCategory = _T("");

	// 현재 list box에서 선택된 data를 가져온다.
	int index = m_listCategory.GetCurSel();
	m_listCategory.GetText(index, strCurrentCategory);
	// ---------- 13주차 추가 코드 ---------- //

	// 현재 날짜를 CString 타입으로 변환
	CChangeDataFormat::ChangeDateToCString(strCurrentDate, m_dtpSelectDate);

	// CSV 파일 안에 저장된 데이터 중, 현재 날짜로 저장된 데이터와 category를 찾아 수정
	int count = CCSVFile::GetCSVFileInterface()->GetDataCount();
	for (int i = 0; i < count; i++)
	{
		CCSVFile::GetCSVFileInterface()->GetData(i, data);
		// ---------- 13주차 추가 코드 ---------- //
		if (data.m_strDate == strCurrentDate && data.m_strCategory == strCurrentCategory)
		{
			// dialog에 설정되어 있는 값들을 CSV 형식으로 만들기
			CCSVFile::GetCSVFileInterface()->MakeDataFormat(data, m_dtpSelectDate, m_dtpStartTime, m_dtpEndTime);

			// listbox에 저장된 문자열을 지우고
			int index = m_listCategory.GetCurSel();
			if (index == LB_ERR)
				break;
			m_listCategory.DeleteString(index);

			// edit control에 입력된 문자열을 삽입한다.
			CString strtmp;
			GetDlgItemText(IDC_EDIT_TEXT_INPUT, strtmp);
			data.m_strCategory = strtmp;

			// 데이터 수정
			CCSVFile::GetCSVFileInterface()->ModifyData(i, data);

			// listbox에 저장된 데이터 수정
			m_listCategory.InsertString(index, strtmp);

			// ---------- 13주차 추가 코드 ---------- //

			break;
		}
	}
}


BOOL CDialogModify::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ---------- 13주차 추가 코드 ---------- //
	// list box와 edit control 초기화
	m_listCategory.ResetContent();
	SetDlgItemText(IDC_EDIT_TEXT_INPUT, NULL);
	// ---------- 13주차 추가 코드 ---------- //

	// TODO:  Add extra initialization here
	VERIFY(m_dtpSelectDate.SetTime(GivenDate));
	
	// 현재 날짜를 CString 타입으로 변환
	CString strCurrentDate;
	CChangeDataFormat::ChangeDateToCString(strCurrentDate, m_dtpSelectDate);

	// 데이터 찾기
	FILEDATA _data;
	std::queue<int> IndexStorage;
	int index = 0;
	int count = CCSVFile::GetCSVFileInterface()->GetDataCount();
	while (true)
	{
		if (index >= count)
			break;

		CCSVFile::GetCSVFileInterface()->GetData(index, _data);
		if (_data.m_strDate == strCurrentDate)
			IndexStorage.push(index);

		index++;
	}

	// 데이터를 찾았다면 list 박스에 데이터을 넣는다.
	if (!IndexStorage.empty())
	{
		// 처음 data를 받아온다.
		int cur = IndexStorage.front();
		IndexStorage.pop();
		CCSVFile::GetCSVFileInterface()->GetData(cur, _data);

		// 처음 data를 선택하게 한다.
		m_listCategory.AddString(_T(_data.m_strCategory));
		m_listCategory.SetCurSel(0);

		// 시작 시간 설정
		COleDateTime tmp;
		int hour, min, sec;
		CChangeDataFormat::GetTimeToInt(hour, _data.m_strStartTime, 0);
		CChangeDataFormat::GetTimeToInt(min, _data.m_strStartTime, 1);
		CChangeDataFormat::GetTimeToInt(sec, _data.m_strStartTime, 2);
		tmp.SetTime(hour, min, sec);
		m_dtpStartTime.SetTime(tmp);

		// 끝나는 시간 설정
		CChangeDataFormat::GetTimeToInt(hour, _data.m_strEndTime, 0);
		CChangeDataFormat::GetTimeToInt(min, _data.m_strEndTime, 1);
		CChangeDataFormat::GetTimeToInt(sec, _data.m_strEndTime, 2);
		tmp.SetTime(hour, min, sec);
		m_dtpEndTime.SetTime(tmp);

		// edit control에 category 데이터 전송
		SetDlgItemText(IDC_EDIT_TEXT_INPUT, _data.m_strCategory);

		// category 데이터를 가져와 list box에 넣는다.
		while (!IndexStorage.empty())
		{
			cur = IndexStorage.front();
			IndexStorage.pop();
			CCSVFile::GetCSVFileInterface()->GetData(cur, _data);
			m_listCategory.AddString(_T(_data.m_strCategory));
		}
	}
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void CDialogModify::OnSelchangeListCategory()
{
	// TODO: Add your control notification handler code here

	FILEDATA _data;
	CString strCurrentDate;
	CString strCategory;
	int index = 0;

	// 현재 선택된 날짜를 CString 타입으로 변환해서 가져오기
	CChangeDataFormat::ChangeDateToCString(strCurrentDate, m_dtpSelectDate);

	// list box에 선택된 data 가져오기
	int SelectIndex = m_listCategory.GetCurSel();
	if (LB_ERR == SelectIndex)
		return;
	m_listCategory.GetText(SelectIndex, strCategory);

	// 데이터 찾기
	int count = CCSVFile::GetCSVFileInterface()->GetDataCount();
	while (true)
	{
		if (index >= count)
			break;

		CCSVFile::GetCSVFileInterface()->GetData(index, _data);
		if (_data.m_strDate == strCurrentDate && _data.m_strCategory == strCategory)
			break;

		index++;
	}

	// 찾은 데이터의 시간 data를 date time picker control에 적용
	// 시작 시간 설정
	COleDateTime tmp;
	int hour, min, sec;
	CChangeDataFormat::GetTimeToInt(hour, _data.m_strStartTime, 0);
	CChangeDataFormat::GetTimeToInt(min, _data.m_strStartTime, 1);
	CChangeDataFormat::GetTimeToInt(sec, _data.m_strStartTime, 2);
	tmp.SetTime(hour, min, sec);
	m_dtpStartTime.SetTime(tmp);

	// 끝나는 시간 설정
	CChangeDataFormat::GetTimeToInt(hour, _data.m_strEndTime, 0);
	CChangeDataFormat::GetTimeToInt(min, _data.m_strEndTime, 1);
	CChangeDataFormat::GetTimeToInt(sec, _data.m_strEndTime, 2);
	tmp.SetTime(hour, min, sec);
	m_dtpEndTime.SetTime(tmp);

	// edit control에 category 데이터 전송
	SetDlgItemText(IDC_EDIT_TEXT_INPUT, _data.m_strCategory);
}

// ---------- 13주차 추가 코드 ---------- //
void CDialogModify::OnDatetimechangeDatetimepickerSelectDate(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: Add your control notification handler code here
	COleDateTime ChangeDate;
	CChangeDataFormat::ChangeDateToCOleDateTime(ChangeDate, m_dtpSelectDate);
	GivenDate = ChangeDate;
	OnInitDialog();
	*pResult = 0;
}
// ---------- 13주차 추가 코드 ---------- //
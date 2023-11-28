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
	AfxMessageBox(_T("�߰� ��ư�� ���Ƚ��ϴ�."));

	// dialog�� �����Ǿ� �ִ� ������ CSV �������� �����
	FILEDATA data;
	CCSVFile::GetCSVFileInterface()->MakeDataFormat(data, m_dtpSelectDate, m_dtpStartTime, m_dtpEndTime);

	// edit control�� �Էµ� ������ ������ FILEDATA ����ü�� �����Ѵ�.
	CString strtmp;
	GetDlgItemText(IDC_EDIT_TEXT_INPUT, strtmp);
	data.m_strCategory = strtmp;

	// CSV ���Ͽ� ������ �߰�
	CCSVFile::GetCSVFileInterface()->AddData(data);

	// edit control�� �Էµ� ���ڿ��� list box�� ����
	m_listCategory.AddString(strtmp);
}


void CDialogModify::OnClickedButtonDelete()
{
	// TODO: Add your control notification handler code here
	AfxMessageBox(_T("���� ��ư�� ���Ƚ��ϴ�."));

	FILEDATA data;
	CString strCurrentDate = _T("");
	CString strCurrentCategory = _T("");

	// ���� list box���� ���õ� data�� �����´�.
	int index = m_listCategory.GetCurSel();
	m_listCategory.GetText(index, strCurrentCategory);

	// ���� ��¥�� CString Ÿ������ ��ȯ
	CChangeDataFormat::ChangeDateToCString(strCurrentDate, m_dtpSelectDate);

	// CSV ���� �ȿ� ����� ������ ��, ���� ��¥�� ���õ� category�� ����� �����͸� ã�� ����
	int count = CCSVFile::GetCSVFileInterface()->GetDataCount();
	for (int i = 0; i < count; i++)
	{
		CCSVFile::GetCSVFileInterface()->GetData(i, data);
		// ---------- 13���� �߰� �ڵ� ---------- //
		if (data.m_strDate == strCurrentDate && data.m_strCategory == strCurrentCategory)
			// ---------- 13���� �߰� �ڵ� ---------- //
		{
			CCSVFile::GetCSVFileInterface()->DeleteData(i);

			// listbox�� ����� data ����
			int index = m_listCategory.FindString(0, data.m_strCategory);
			m_listCategory.DeleteString(index);
			break;
		}
	}
}


void CDialogModify::OnClickedButtonModify()
{
	// TODO: Add your control notification handler code here
	AfxMessageBox(_T("���� ��ư�� ���Ƚ��ϴ�."));

	FILEDATA data;
	CString strCurrentDate = _T("");
	// ---------- 13���� �߰� �ڵ� ---------- //
	CString strCurrentCategory = _T("");

	// ���� list box���� ���õ� data�� �����´�.
	int index = m_listCategory.GetCurSel();
	m_listCategory.GetText(index, strCurrentCategory);
	// ---------- 13���� �߰� �ڵ� ---------- //

	// ���� ��¥�� CString Ÿ������ ��ȯ
	CChangeDataFormat::ChangeDateToCString(strCurrentDate, m_dtpSelectDate);

	// CSV ���� �ȿ� ����� ������ ��, ���� ��¥�� ����� �����Ϳ� category�� ã�� ����
	int count = CCSVFile::GetCSVFileInterface()->GetDataCount();
	for (int i = 0; i < count; i++)
	{
		CCSVFile::GetCSVFileInterface()->GetData(i, data);
		// ---------- 13���� �߰� �ڵ� ---------- //
		if (data.m_strDate == strCurrentDate && data.m_strCategory == strCurrentCategory)
		{
			// dialog�� �����Ǿ� �ִ� ������ CSV �������� �����
			CCSVFile::GetCSVFileInterface()->MakeDataFormat(data, m_dtpSelectDate, m_dtpStartTime, m_dtpEndTime);

			// listbox�� ����� ���ڿ��� �����
			int index = m_listCategory.GetCurSel();
			if (index == LB_ERR)
				break;
			m_listCategory.DeleteString(index);

			// edit control�� �Էµ� ���ڿ��� �����Ѵ�.
			CString strtmp;
			GetDlgItemText(IDC_EDIT_TEXT_INPUT, strtmp);
			data.m_strCategory = strtmp;

			// ������ ����
			CCSVFile::GetCSVFileInterface()->ModifyData(i, data);

			// listbox�� ����� ������ ����
			m_listCategory.InsertString(index, strtmp);

			// ---------- 13���� �߰� �ڵ� ---------- //

			break;
		}
	}
}


BOOL CDialogModify::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ---------- 13���� �߰� �ڵ� ---------- //
	// list box�� edit control �ʱ�ȭ
	m_listCategory.ResetContent();
	SetDlgItemText(IDC_EDIT_TEXT_INPUT, NULL);
	// ---------- 13���� �߰� �ڵ� ---------- //

	// TODO:  Add extra initialization here
	VERIFY(m_dtpSelectDate.SetTime(GivenDate));
	
	// ���� ��¥�� CString Ÿ������ ��ȯ
	CString strCurrentDate;
	CChangeDataFormat::ChangeDateToCString(strCurrentDate, m_dtpSelectDate);

	// ������ ã��
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

	// �����͸� ã�Ҵٸ� list �ڽ��� �������� �ִ´�.
	if (!IndexStorage.empty())
	{
		// ó�� data�� �޾ƿ´�.
		int cur = IndexStorage.front();
		IndexStorage.pop();
		CCSVFile::GetCSVFileInterface()->GetData(cur, _data);

		// ó�� data�� �����ϰ� �Ѵ�.
		m_listCategory.AddString(_T(_data.m_strCategory));
		m_listCategory.SetCurSel(0);

		// ���� �ð� ����
		COleDateTime tmp;
		int hour, min, sec;
		CChangeDataFormat::GetTimeToInt(hour, _data.m_strStartTime, 0);
		CChangeDataFormat::GetTimeToInt(min, _data.m_strStartTime, 1);
		CChangeDataFormat::GetTimeToInt(sec, _data.m_strStartTime, 2);
		tmp.SetTime(hour, min, sec);
		m_dtpStartTime.SetTime(tmp);

		// ������ �ð� ����
		CChangeDataFormat::GetTimeToInt(hour, _data.m_strEndTime, 0);
		CChangeDataFormat::GetTimeToInt(min, _data.m_strEndTime, 1);
		CChangeDataFormat::GetTimeToInt(sec, _data.m_strEndTime, 2);
		tmp.SetTime(hour, min, sec);
		m_dtpEndTime.SetTime(tmp);

		// edit control�� category ������ ����
		SetDlgItemText(IDC_EDIT_TEXT_INPUT, _data.m_strCategory);

		// category �����͸� ������ list box�� �ִ´�.
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

	// ���� ���õ� ��¥�� CString Ÿ������ ��ȯ�ؼ� ��������
	CChangeDataFormat::ChangeDateToCString(strCurrentDate, m_dtpSelectDate);

	// list box�� ���õ� data ��������
	int SelectIndex = m_listCategory.GetCurSel();
	if (LB_ERR == SelectIndex)
		return;
	m_listCategory.GetText(SelectIndex, strCategory);

	// ������ ã��
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

	// ã�� �������� �ð� data�� date time picker control�� ����
	// ���� �ð� ����
	COleDateTime tmp;
	int hour, min, sec;
	CChangeDataFormat::GetTimeToInt(hour, _data.m_strStartTime, 0);
	CChangeDataFormat::GetTimeToInt(min, _data.m_strStartTime, 1);
	CChangeDataFormat::GetTimeToInt(sec, _data.m_strStartTime, 2);
	tmp.SetTime(hour, min, sec);
	m_dtpStartTime.SetTime(tmp);

	// ������ �ð� ����
	CChangeDataFormat::GetTimeToInt(hour, _data.m_strEndTime, 0);
	CChangeDataFormat::GetTimeToInt(min, _data.m_strEndTime, 1);
	CChangeDataFormat::GetTimeToInt(sec, _data.m_strEndTime, 2);
	tmp.SetTime(hour, min, sec);
	m_dtpEndTime.SetTime(tmp);

	// edit control�� category ������ ����
	SetDlgItemText(IDC_EDIT_TEXT_INPUT, _data.m_strCategory);
}

// ---------- 13���� �߰� �ڵ� ---------- //
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
// ---------- 13���� �߰� �ڵ� ---------- //
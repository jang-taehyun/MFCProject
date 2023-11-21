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
	AfxMessageBox(_T("�߰� ��ư�� ���Ƚ��ϴ�."));

	// dialog�� �����Ǿ� �ִ� ������ CSV �������� �����
	FILEDATA data;
	CCSVFile::GetCSVFileInterface()->MakeDataFormat(data, m_dtpSelectDate, m_dtpStartTime, m_dtpEndTime);

	// CSV ���Ͽ� ������ �߰�
	CCSVFile::GetCSVFileInterface()->AddData(data);
}


void CDialogModify::OnClickedButtonDelete()
{
	// TODO: Add your control notification handler code here
	AfxMessageBox(_T("���� ��ư�� ���Ƚ��ϴ�."));

	FILEDATA data;
	CString strCurrentDate = _T("");

	// ���� ��¥�� CString Ÿ������ ��ȯ
	CChangeDataFormat::GetInst()->ChangeDateToCString(strCurrentDate, m_dtpSelectDate);

	// CSV ���� �ȿ� ����� ������ ��, ���� ��¥�� ����� �����͸� ã�� ����
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
	AfxMessageBox(_T("���� ��ư�� ���Ƚ��ϴ�."));

	FILEDATA data;
	CString strCurrentDate = _T("");

	// dialog�� �����Ǿ� �ִ� ������ CSV �������� �����
	CCSVFile::GetCSVFileInterface()->MakeDataFormat(data, m_dtpSelectDate, m_dtpStartTime, m_dtpEndTime);

	// ���� ������ ��¥�� CString �������� �ٲٱ�
	CChangeDataFormat::GetInst()->ChangeDateToCString(strCurrentDate, m_dtpSelectDate);

	// CSV ���� �ȿ� ����� ������ ��, ���� ��¥�� ����� �����͸� ã�� ����
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

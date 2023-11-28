
// MFCProjectDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCProject.h"
#include "MFCProjectDlg.h"
#include "afxdialogex.h"


#include "CCSVFile.h"
#include "CChangeDataFormat.h"
#include "CDialogModify.h"
#include <queue>
#define CurTimer 1000

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCProjectDlg 대화 상자



CMFCProjectDlg::CMFCProjectDlg(CWnd* pParent /*=nullptr*/)
	//: CDialogEx(IDD_MFCPROJECT_DIALOG, pParent)
	:CDialogEx(IDD_DIALOG_MAIN, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCProjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_WEEK, m_tabSelection);
	DDX_Control(pDX, IDC_EDIT_CUR_TIME, m_ctrlCurTime);
}

BEGIN_MESSAGE_MAP(CMFCProjectDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_ENTER_MOD_DIALOG, &CMFCProjectDlg::OnClickedButtonEnterModDialog)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_WEEK, &CMFCProjectDlg::OnSelchangeTabWeek)
	ON_NOTIFY(MCN_SELECT, IDC_MONTHCALENDAR_MONTH, &CMFCProjectDlg::OnSelectMonthcalendarMonth)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CMFCProjectDlg 메시지 처리기

BOOL CMFCProjectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_tabSelection.DeleteAllItems();
	m_tabSelection.InsertItem(0, _T("Sun"));
	m_tabSelection.InsertItem(1, _T("Mon"));
	m_tabSelection.InsertItem(2, _T("Tue"));
	m_tabSelection.InsertItem(3, _T("Wed"));
	m_tabSelection.InsertItem(4, _T("Thr"));
	m_tabSelection.InsertItem(5, _T("Fir"));
	m_tabSelection.InsertItem(6, _T("Sat"));

	CRect rect;
	m_dlgObject.Create(IDD_DIALOG_OBJECT, &m_tabSelection);
	m_dlgObject.GetWindowRect(&rect);
	m_dlgObject.MoveWindow(5, 50, rect.Width(), rect.Height());
	m_dlgObject.ShowWindow(SW_SHOW);

	SetTimer(CurTimer, 1000, 0);
	font.CreatePointFont(150, "굴림");
	GetDlgItem(IDC_EDIT_CUR_TIME)->SetFont(&font);
	font.Detach();

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCProjectDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCProjectDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCProjectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCProjectDlg::OnClickedButtonEnterModDialog()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogModify NewDlg;
	COleDateTime currentTime;
	CString strMsg;
	CMonthCalCtrl* pCalendar = (CMonthCalCtrl*)GetDlgItem(IDC_MONTHCALENDAR_MONTH);
	pCalendar->GetCurSel(currentTime);
	strMsg.Format("%d년 %d월 %d일", currentTime.GetYear(), currentTime.GetMonth(), currentTime.GetDay());
	MessageBox(strMsg);
	NewDlg.GivenDate = currentTime;
	NewDlg.DoModal();
}


void CMFCProjectDlg::OnSelchangeTabWeek(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CTabMonDlg NewDlg;
	int nSelection = m_tabSelection.GetCurSel();
	NewDlg.m_SunToSat = nSelection;
	//NewDlg.DoModal(); // create

	// ------------- 태현 추가 ------------- //	// ---------- 13주차 추가 코드 ---------- //
	COleDateTime selectedDate;
	CMonthCalCtrl* pCalendar = (CMonthCalCtrl*)GetDlgItem(IDC_MONTHCALENDAR_MONTH);
	pCalendar->GetCurSel(selectedDate);
	
	CString PrintData;

	// 그 주의 해당 요일에 저장된 category 데이터를 가져온다.
	CCSVFile::GetCSVFileInterface()->GetCategoryInWeek(PrintData, selectedDate, nSelection);

	// 기준점이 되는 요일과 시작 요일(일요일)의 차이를 구하고 저장한다.
	COleDateTimeSpan diff1(selectedDate.GetDayOfWeek() - 1, 0, 0, 0);

	// 기준점이 되는 날짜와 '기준점이 되는 요일과 시작 요일(일요일)의 차이'를 뺀다.
	selectedDate -= diff1;

	// 연산 결과에서 flag 값을 더한다.
	COleDateTimeSpan diff2(nSelection, 0, 0, 0);
	selectedDate += diff2;

	// 선택된 날짜를 month calendar에서 선택하게 한다.
	pCalendar->SetCurSel(selectedDate);

	// tab control에서 하나로 합친 data들을 출력하게 한다.
	m_dlgObject.m_strSchedule = PrintData;
	m_dlgObject.OnChangeEditSchedule();

	// ------------- 태현 추가 ------------- //	// ---------- 13주차 추가 코드 ---------- //

	*pResult = 0;
}


void CMFCProjectDlg::OnSelectMonthcalendarMonth(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMSELCHANGE pSelChange = reinterpret_cast<LPNMSELCHANGE>(pNMHDR);
	// TODO: Add your control notification handler code here
	COleDateTime selectedDate;
	CMonthCalCtrl* pCalendar = (CMonthCalCtrl*)GetDlgItem(IDC_MONTHCALENDAR_MONTH);
	pCalendar->GetCurSel(selectedDate);

	int dayOfWeek = selectedDate.GetDayOfWeek();
	m_tabSelection.SetCurSel(dayOfWeek - 1);

	// ------------- 태현 추가 ------------- //	// ---------- 13주차 추가 코드 ---------- //
	CString curDate;
	std::queue<int> storage;

	// 받아온 날짜를 CString 타입으로 변환
	CChangeDataFormat::ChangeDateToCString(curDate, selectedDate);

	// 선택된 날짜에 관련된 CSV data들을 받아온다.
	FILEDATA data;
	int bound = CCSVFile::GetCSVFileInterface()->GetDataCount();
	for (int i = 0; i < bound; i++)
	{
		CCSVFile::GetCSVFileInterface()->GetData(i, data);
		if (data.m_strDate == curDate)
			storage.push(i);
	}

	// 관련된 CSV data들의 category data를 하나로 합친다.
	CString PrintData = _T("");
	int tmp;
	while (!storage.empty())
	{
		tmp = storage.front();
		storage.pop();

		CCSVFile::GetCSVFileInterface()->GetData(tmp, data);
		PrintData += (data.m_strCategory + _T("\r\n"));
	}

	// tab control에서 하나로 합친 data들을 출력하게 한다.
	m_dlgObject.m_strSchedule = PrintData;
	m_dlgObject.OnChangeEditSchedule();
	// ------------- 태현 추가 ------------- //	// ---------- 13주차 추가 코드 ---------- //

	*pResult = 0;
}


void CMFCProjectDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	switch (nIDEvent)
	{
	case CurTimer:
		CString strTime = CTime::GetCurrentTime().Format(_T("%Y - %m - %d    %H : %M : %S"));
		m_ctrlCurTime.SetWindowText(strTime);
		break;
	}
	CDialogEx::OnTimer(nIDEvent);
}

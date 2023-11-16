// CDialogMain.cpp : implementation file
//

#include "pch.h"
#include "MFCProject.h"
#include "CDialogMain.h"
#include "afxdialogex.h"

// CDialogMain dialog

IMPLEMENT_DYNAMIC(CDialogMain, CDialogEx)

CDialogMain::CDialogMain(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_MAIN, pParent)
{
	
}

CDialogMain::~CDialogMain()
{
}

void CDialogMain::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDialogMain, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_DEBUG, &CDialogMain::OnClickedButtonDebug)
END_MESSAGE_MAP()


// CDialogMain message handlers


void CDialogMain::OnClickedButtonDebug()
{
	// TODO: Add your control notification handler code here

}

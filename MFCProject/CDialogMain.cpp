// CDialogMain.cpp : implementation file
//

#include "pch.h"
#include "MFCProject.h"
#include "CDialogMain.h"
#include "afxdialogex.h"

#include "CDialogModify.h"

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
	//  DDX_Control(pDX, IDC_BUTTON_ENTER_MOD_DIALOG, m_buttonEnterModifyDialog);
}


BEGIN_MESSAGE_MAP(CDialogMain, CDialogEx)
//	ON_BN_CLICKED(IDC_BUTTON_DEBUG, &CDialogMain::OnClickedButtonDebug)
//ON_BN_CLICKED(IDC_BUTTON_ENTER_MOD_DIALOG, &CDialogMain::OnClickedButtonEnterModDialog)
END_MESSAGE_MAP()


// CDialogMain message handlers


//void CDialogMain::OnClickedButtonDebug()
//{
//	// TODO: Add your control notification handler code here
//
//}


//void CDialogMain::OnClickedButtonEnterModDialog()
//{
//	// TODO: Add your control notification handler code here
//	AfxMessageBox(_T("Modify ���̾�α׷� �Ѿ�ϴ�."));
//	MessageBox(_T("Modify ���̾�α׷� �Ѿ�ϴ�."));
//	CDialogModify dlg;
//	dlg.DoModal();
//}

// CDialogModify.cpp : implementation file
//

#include "pch.h"
#include "MFCProject.h"
#include "CDialogModify.h"
#include "afxdialogex.h"


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
}


BEGIN_MESSAGE_MAP(CDialogModify, CDialogEx)
END_MESSAGE_MAP()


// CDialogModify message handlers

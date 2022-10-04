// CDlg_SYSINIT.cpp: 구현 파일
//

#include "pch.h"
#include "주성.h"
#include "afxdialogex.h"
#include "CDlg_SYSINIT.h"


// CDlg_SYSINIT 대화 상자

IMPLEMENT_DYNAMIC(CDlg_SYSINIT, CDialogEx)

CDlg_SYSINIT::CDlg_SYSINIT(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SYS_INIT, pParent)
{

}

CDlg_SYSINIT::~CDlg_SYSINIT()
{
}

void CDlg_SYSINIT::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlg_SYSINIT, CDialogEx)
END_MESSAGE_MAP()


// CDlg_SYSINIT 메시지 처리기

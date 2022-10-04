// CDlgShowLoad.cpp: 구현 파일
//

#include "pch.h"
#include "주성.h"
#include "주성Dlg.h"
#include "afxdialogex.h"
#include "CDlgShowLoad.h"


// CDlgShowLoad 대화 상자

IMPLEMENT_DYNAMIC(CDlgShowLoad, CDialogEx)

CDlgShowLoad::CDlgShowLoad(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SHOW_LOAD, pParent)
{

}

CDlgShowLoad::~CDlgShowLoad()
{
}

void CDlgShowLoad::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgShowLoad, CDialogEx)
END_MESSAGE_MAP()


// CDlgShowLoad 메시지 처리기


BOOL CDlgShowLoad::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

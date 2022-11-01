// CSetProcessDlg.cpp: 구현 파일
//

#include "pch.h"
#include "주성.h"
#include "afxdialogex.h"
#include "CSetProcessDlg.h"
#include "CSysInfoDlg.h"

// CSetProcessDlg 대화 상자

IMPLEMENT_DYNAMIC(CSetProcessDlg, CDialogEx)

CSetProcessDlg::CSetProcessDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SET_PROCESS_TIME, pParent)
	, m_nPMProcess01(0)
	, m_nPMProcess02(0)
	, m_nPMProcess03(0)
	, m_nPMProcess04(0)
	, m_nPMProcess05(0)
	, m_nPMProcess06(0)
{

}

CSetProcessDlg::~CSetProcessDlg()
{
}

void CSetProcessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PM_PROCESS1, m_nPMProcess01);
	DDX_Text(pDX, IDC_EDIT_PM_PROCESS2, m_nPMProcess02);
	DDX_Text(pDX, IDC_EDIT_PM_PROCESS3, m_nPMProcess03);
	DDX_Text(pDX, IDC_EDIT_PM_PROCESS4, m_nPMProcess04);
	DDX_Text(pDX, IDC_EDIT_PM_PROCESS5, m_nPMProcess05);
	DDX_Text(pDX, IDC_EDIT_PM_PROCESS6, m_nPMProcess06);
}


BEGIN_MESSAGE_MAP(CSetProcessDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CSetProcessDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CSetProcessDlg 메시지 처리기

BOOL CSetProcessDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	CSysInfoDlg* pDlgSysInfo = (CSysInfoDlg*)GetParent();
	
	UpdateData(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CSetProcessDlg::OnBnClickedOk()
{
	UpdateData(1);
	CDialogEx::OnOK();
}

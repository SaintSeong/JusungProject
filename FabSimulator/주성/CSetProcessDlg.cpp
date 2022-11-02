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
{
	m_arrPMProcess.resize(6);
	for (int nIdx = 0; nIdx < 6; nIdx++)
	{
		m_arrPMProcess[nIdx] = 0;
	}
}

CSetProcessDlg::~CSetProcessDlg()
{
}

void CSetProcessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSetProcessDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CSetProcessDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CSetProcessDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CSetProcessDlg 메시지 처리기

BOOL CSetProcessDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	CString strTime;
	CSysInfoDlg* pDlgSysInfo = (CSysInfoDlg*)GetParent();

	for (int nIdx = 0; nIdx < pDlgSysInfo->m_nPMModule; nIdx++)
	{
		GetDlgItem(IDC_EDIT_PM_PROCESS1 + nIdx)->EnableWindow(TRUE);
		strTime.Format(_T("%d"), pDlgSysInfo->m_arrPMProcess[nIdx]);
		GetDlgItem(IDC_EDIT_PM_PROCESS1 + nIdx)->SetWindowText(strTime);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CSetProcessDlg::OnBnClickedOk()
{
	CSysInfoDlg* pDlgSysInfo = (CSysInfoDlg*)GetParent();
	CString strTime;
	int nTime;
	for (int nIdx = 0; nIdx < pDlgSysInfo->m_nPMModule; nIdx++)
	{
		GetDlgItem(IDC_EDIT_PM_PROCESS1 + nIdx)->GetWindowText(strTime);
		nTime = _ttoi(strTime);
		m_arrPMProcess[nIdx] = nTime;
	}
	CDialogEx::OnOK();
}


void CSetProcessDlg::OnBnClickedCancel()
{
	if (IDYES == AfxMessageBox(_T("설정이 적용되지 않습니다. 취소하시겠습니까?"), MB_YESNO))
	{
		CDialogEx::OnCancel();
	}
}

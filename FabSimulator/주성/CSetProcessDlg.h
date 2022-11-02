#pragma once
#include "afxdialogex.h"
#include <vector>
using namespace std;
// CSetProcessDlg 대화 상자

class CSetProcessDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSetProcessDlg)

public:
	CSetProcessDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CSetProcessDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SET_PROCESS_TIME };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	vector<int> m_arrPMProcess;
	afx_msg void OnBnClickedCancel();
};

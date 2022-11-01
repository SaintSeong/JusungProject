#pragma once
#include "afxdialogex.h"

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

	int m_nPMProcess01;
	int m_nPMProcess02;
	int m_nPMProcess03;
	int m_nPMProcess04;
	int m_nPMProcess05;
	int m_nPMProcess06;
};

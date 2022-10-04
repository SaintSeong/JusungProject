#pragma once
#include "afxdialogex.h"


// CDlgShowLoad 대화 상자

class CDlgShowLoad : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgShowLoad)

public:
	CDlgShowLoad(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDlgShowLoad();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SHOW_LOAD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};

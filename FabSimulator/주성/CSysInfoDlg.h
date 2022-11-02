#pragma once
#include "afxdialogex.h"
#include "CSetProcessDlg.h"
#include <vector>
using namespace std;
// CDlg_SYSINIT 대화 상자

class CSysInfoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSysInfoDlg)

public:
	CSysInfoDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CSysInfoDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SysInfo };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	
	virtual BOOL OnInitDialog();

	void InitComboBox();
	afx_msg void OnBnClickedOk();
	afx_msg void OnCbnSelchangeComboVacArm();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedSetProcessTime();

	CComboBox m_ctrlComboLLModule;
	CComboBox m_ctrlComboLLSlot;
	CComboBox m_ctrlComboVacArm;
	CComboBox m_ctrlComboPMModule;
	CComboBox m_ctrlComboPMSlot;

	CString m_strLLModuleCount;
	CString m_strLLSlotCount;
	CString m_strVacArmCount;
	CString m_strPMModuleCount;
	CString m_strPMSlotCount;

	CSetProcessDlg m_dlgSetProcess;

	int m_nEFEMPickTime;
	int m_nEFEMMoveTime;
	int m_nEFEMPlaceTime;
	double m_nEFEMRotateTime;
	int m_nLLPumpTime;
	int m_nLLPumpStableTime;
	int m_nLLVentTime;
	int m_nLLVentStableTime;
	int m_nLLSlotOpenTime;
	int m_nLLSlotCloseTime;
	int m_nLLDoorOpenTime;
	int m_nLLDoorCloseTime;
	int m_nTMRotate;
	int m_nTMPickTime;
	int m_nTMPlaceTime;
	int m_nPMSlotOpenTime;
	int m_nPMSlotCloseTime;
	int m_nCleanCount;
	int m_nPMModule;

	vector<int> m_arrPMProcess;
	vector<int> m_arrCleanProcess;
};

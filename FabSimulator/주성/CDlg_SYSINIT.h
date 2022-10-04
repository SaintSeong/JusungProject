﻿#pragma once
#include "afxdialogex.h"


// CDlg_SYSINIT 대화 상자

class CDlg_SYSINIT : public CDialogEx
{
	DECLARE_DYNAMIC(CDlg_SYSINIT)

public:
	CDlg_SYSINIT(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDlg_SYSINIT();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SYS_INIT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedOk();
	afx_msg void OnCbnSelchangeComboVacArm();
	afx_msg void OnCbnSelchangeComboPmSlot();

	CComboBox m_ctrlComboLLModule;
	CComboBox m_ctrlComboLLSlot;
	CComboBox m_ctrlComboVacArm;
	CComboBox m_ctrlComboPMModule;
	CComboBox m_ctrlComboPMSlot;
	
	int m_nEFEMPickTime;
	int m_nMoveTime;
	int m_nEFEMPlaceTime;
	int m_nEFEMRotateTime;
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
	int m_nPMProcessTime;
	int m_nPMSlotOpenTime;
	int m_nPMSlotCloseTime;
	int m_nLLModuleCount;
	int m_nLLSlotCount;
	int m_nVacArm;
	int m_nPMModuleCount;
	int m_nPMSlotCount;
};

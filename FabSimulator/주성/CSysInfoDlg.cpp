// CDlg_SYSINIT.cpp: 구현 파일
//

#include "pch.h"
#include "주성.h"
#include "주성Dlg.h"
#include "afxdialogex.h"
#include "CSysInfoDlg.h"

#define MSEC 1000

// CDlg_SYSINIT 대화 상자

IMPLEMENT_DYNAMIC(CSysInfoDlg, CDialogEx)

CSysInfoDlg::CSysInfoDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SysInfo, pParent)
	, m_nEFEMPickTime(0)
	, m_nEFEMMoveTime(0)
	, m_nEFEMPlaceTime(0)
	, m_nEFEMRotateTime(0.0)
	, m_nLLPumpTime(0)
	, m_nLLPumpStableTime(0)
	, m_nLLVentTime(0)
	, m_nLLVentStableTime(0)
	, m_nLLSlotOpenTime(0)
	, m_nLLSlotCloseTime(0)
	, m_nLLDoorOpenTime(0)
	, m_nLLDoorCloseTime(0)
	, m_nTMRotate(0)
	, m_nTMPickTime(0)
	, m_nTMPlaceTime(0)
	, m_nPMSlotOpenTime(0)
	, m_nPMSlotCloseTime(0)
	, m_strLLModuleCount(_T(""))
	, m_strLLSlotCount(_T(""))
	, m_strVacArmCount(_T(""))
	, m_strPMModuleCount(_T(""))
	, m_strPMSlotCount(_T(""))
	, m_nCleanCount(0)
{
	m_arrPMProcess.resize(6);
	m_arrCleanProcess.resize(6);
	for (int nIdx = 0; nIdx < 6; nIdx++)
	{
		m_arrPMProcess[nIdx] = 600;
		m_arrCleanProcess[nIdx] = m_arrPMProcess[nIdx] * 2;
	}
}

CSysInfoDlg::~CSysInfoDlg()
{
}

void CSysInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_MODULE_COUNT, m_ctrlComboLLModule);
	DDX_Control(pDX, IDC_COMBO_MODULESLOT, m_ctrlComboLLSlot);
	DDX_Control(pDX, IDC_COMBO_VAC_ARM, m_ctrlComboVacArm);
	DDX_Control(pDX, IDC_COMBO_PM_MODULE, m_ctrlComboPMModule);
	DDX_Control(pDX, IDC_COMBO_PM_SLOT, m_ctrlComboPMSlot);

	DDX_Text(pDX, IDC_EDIT_EFEM_PICKTIME, m_nEFEMPickTime);
	DDX_Text(pDX, IDC_EDIT_EFEM_MOVETIME, m_nEFEMMoveTime);
	DDX_Text(pDX, IDC_EDIT_EFEM_PLACETIME, m_nEFEMPlaceTime);
	DDX_Text(pDX, IDC_EDIT_ROTATETIME, m_nEFEMRotateTime);
	DDX_Text(pDX, IDC_EDIT_PUMP_TIME, m_nLLPumpTime);
	DDX_Text(pDX, IDC_EDIT_LL_PUMP_STABLETIME, m_nLLPumpStableTime);
	DDX_Text(pDX, IDC_EDIT_LL_VENT_TIME, m_nLLVentTime);
	DDX_Text(pDX, IDC_EDIT_VENT_STABLETIME, m_nLLVentStableTime);
	DDX_Text(pDX, IDC_EDIT_LL_SLOT_OPEN_TIME, m_nLLSlotOpenTime);
	DDX_Text(pDX, IDC_EDIT_LL_SLOT_CLOSE_TIME, m_nLLSlotCloseTime);
	DDX_Text(pDX, IDC_EDIT_LL_DOOR_OPEN_TIME, m_nLLDoorOpenTime);
	DDX_Text(pDX, IDC_EDIT_LL_DOOR_CLOSE_TIME, m_nLLDoorCloseTime);
	DDX_Text(pDX, IDC_EDIT_TM_ROTATE, m_nTMRotate);
	DDX_Text(pDX, IDC_EDIT_TM_PICK_TIME, m_nTMPickTime);
	DDX_Text(pDX, IDC_EDIT_TM_PLACE_TIME, m_nTMPlaceTime);
	DDX_Text(pDX, IDC_EDIT_PM_SLOT_OPEN_TIME, m_nPMSlotOpenTime);
	DDX_Text(pDX, IDC_EDIT_PM_SLOT_CLOSE_TIME, m_nPMSlotCloseTime);

	DDX_CBString(pDX, IDC_COMBO_MODULE_COUNT, m_strLLModuleCount);
	DDX_CBString(pDX, IDC_COMBO_MODULESLOT, m_strLLSlotCount);
	DDX_CBString(pDX, IDC_COMBO_VAC_ARM, m_strVacArmCount);
	DDX_CBString(pDX, IDC_COMBO_PM_MODULE, m_strPMModuleCount);
	DDX_CBString(pDX, IDC_COMBO_PM_SLOT, m_strPMSlotCount);
	DDX_Text(pDX, IDC_EDIT_CLEANCOUNT, m_nCleanCount);
}


BEGIN_MESSAGE_MAP(CSysInfoDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CSysInfoDlg::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COMBO_VAC_ARM, &CSysInfoDlg::OnCbnSelchangeComboVacArm)
	ON_BN_CLICKED(IDCANCEL, &CSysInfoDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_SET_PROCESS_TIME, &CSysInfoDlg::OnBnClickedSetProcessTime)
END_MESSAGE_MAP()


// CDlg_SYSINIT 메시지 처리기
void CSysInfoDlg::InitComboBox()
{

	CString strFormat;
	m_ctrlComboVacArm.AddString(_T("2"));
	m_ctrlComboVacArm.AddString(_T("4"));

	for (int i  = 1; i < 7; i++)
	{
		strFormat.Format(_T("%d"), i);
		m_ctrlComboPMSlot.AddString(strFormat);
	}

	for (int i = 1; i < 7; i++)
	{
		strFormat.Format(_T("%d"), i);
		m_ctrlComboPMModule.AddString(strFormat);
	}

	for (int i = 1; i < 7; i++)
	{
		strFormat.Format(_T("%d"), i);
		m_ctrlComboLLSlot.AddString(strFormat);
	}

	for (int i = 1; i < 5; i++)
	{
		strFormat.Format(_T("%d"), i);
		m_ctrlComboLLModule.AddString(strFormat);
	}
}

BOOL CSysInfoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	C주성Dlg* pMainDlg = (C주성Dlg*)GetParent();

	// EFEM 설정
	m_nEFEMPickTime = pMainDlg->m_nATM_Pick / MSEC;
	m_nEFEMPlaceTime = pMainDlg->m_nATM_Place / MSEC;
	m_nEFEMMoveTime = pMainDlg->m_nATM_ZRotate / MSEC;
	m_nEFEMRotateTime = pMainDlg->m_nATM_Rotate / (double)MSEC;

	// LL 설정
	m_strLLModuleCount = pMainDlg->m_strLLModuleCnt;
	m_strLLSlotCount = pMainDlg->m_strLLSlotCnt;
	m_nLLPumpTime = pMainDlg->m_nLL_Pump / MSEC;
	m_nLLPumpStableTime = pMainDlg->m_nLL_Pump_Stable_Time / MSEC;
	m_nLLVentTime = pMainDlg->m_nLL_Vent / MSEC;
	m_nLLVentStableTime = pMainDlg->m_nLL_Vent_Stable_Time / MSEC;
	m_nLLSlotOpenTime = pMainDlg->m_nLL_Slot_Valve_Open / MSEC;
	m_nLLSlotCloseTime = pMainDlg->m_nLL_Slot_Valve_Close / MSEC;
	m_nLLDoorOpenTime = pMainDlg->m_nLL_Door_Valve_Open / MSEC;
	m_nLLDoorCloseTime = pMainDlg->m_nLL_Door_Valve_Close / MSEC;

	// TM 설정
	m_strVacArmCount = pMainDlg->m_strVacArmCnt;
	m_nTMPickTime = pMainDlg->m_nVAC_Pick / MSEC;
	m_nTMPlaceTime = pMainDlg->m_nVAC_Place / MSEC;
	m_nTMRotate = pMainDlg->m_nRotate / MSEC;

	// PM 설정
	m_strPMModuleCount = pMainDlg->m_strPMModuleCnt;
	m_strPMSlotCount = pMainDlg->m_strPMSlotCnt;
	m_nCleanCount = pMainDlg->m_nPM_Clean_Wafer_Count;
	m_nPMSlotOpenTime = pMainDlg->m_nPM_Slot_Valve_Open / MSEC;
	m_nPMSlotCloseTime = pMainDlg->m_nPM_Slot_Valve_Close / MSEC;
	for (int nIdx = 0; nIdx < _ttoi(m_strPMModuleCount); nIdx++)
	{
		m_arrPMProcess[nIdx] = pMainDlg->m_arrPMProcess[nIdx] / MSEC;
	}

	int nLLModuleIdx = 0;
	int nLLSlotIdx = 0;
	int nVacArmIdx = 0;
	int nPMModuleIdx = 0;
	int nPMSlotIdx = 0;
	int nValue = 0;

	InitComboBox();

	nVacArmIdx = m_ctrlComboVacArm.FindStringExact(0, m_strVacArmCount);
	m_ctrlComboVacArm.SetCurSel(nLLModuleIdx);
	
	CString strValue;
	
	m_ctrlComboVacArm.GetLBText(nVacArmIdx, strValue);
	nValue = _ttoi(strValue);

	m_ctrlComboLLSlot.ResetContent();
	m_ctrlComboPMSlot.ResetContent();
	m_ctrlComboPMModule.ResetContent();


	for (int i = 1; i < 7; i++)
	{
		strValue.Format(_T("%d"), i);
		m_ctrlComboPMModule.AddString(strValue);
	}

	if (nValue == 2)
	{
		for (int i = 1; i < 7; i++)
		{
			strValue.Format(_T("%d"), i);
			m_ctrlComboPMSlot.AddString(strValue);
		}

		for (int i = 1; i < 7; i++)
		{
			strValue.Format(_T("%d"), i);
			m_ctrlComboLLSlot.AddString(strValue);
		}
	}
	else
	{
		m_ctrlComboPMSlot.AddString(_T("2"));
		m_ctrlComboPMSlot.AddString(_T("4"));
		m_ctrlComboPMSlot.AddString(_T("6"));

		m_ctrlComboLLSlot.AddString(_T("2"));
		m_ctrlComboLLSlot.AddString(_T("4"));
		m_ctrlComboLLSlot.AddString(_T("6"));
	}

	nLLModuleIdx = m_ctrlComboLLModule.FindStringExact(0, m_strLLModuleCount);
	m_ctrlComboLLModule.SetCurSel(nLLModuleIdx);

	nLLSlotIdx = m_ctrlComboLLSlot.FindStringExact(0, m_strLLSlotCount);
	m_ctrlComboLLSlot.SetCurSel(nLLSlotIdx);

	nVacArmIdx = m_ctrlComboVacArm.FindStringExact(0, m_strVacArmCount);
	m_ctrlComboVacArm.SetCurSel(nVacArmIdx);

	nPMModuleIdx = m_ctrlComboPMModule.FindStringExact(0, m_strPMModuleCount);
	m_ctrlComboPMModule.SetCurSel(nPMModuleIdx);

	nPMSlotIdx = m_ctrlComboPMSlot.FindStringExact(0, m_strPMSlotCount);
	m_ctrlComboPMSlot.SetCurSel(nPMSlotIdx);

	UpdateData(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CSysInfoDlg::OnBnClickedOk()
{

	int nLLSlotIdx = m_ctrlComboLLSlot.GetCurSel();
	int nLLModuleIdx = m_ctrlComboLLModule.GetCurSel();
	int nPMSlotIdx = m_ctrlComboPMSlot.GetCurSel();
	int nPMModuleIdx = m_ctrlComboPMModule.GetCurSel();

	CString strLLSlotIdx;
	CString strLLModuleIdx;
	CString strPMSlotIdx;
	CString strPMModuleIdx;


	m_ctrlComboLLSlot.GetLBText(nLLSlotIdx, strLLSlotIdx);
	int nLLSlot = _ttoi(strLLSlotIdx);

	m_ctrlComboLLModule.GetLBText(nLLModuleIdx, strLLModuleIdx);
	int nLLModule = _ttoi(strLLModuleIdx);

	m_ctrlComboPMSlot.GetLBText(nPMSlotIdx, strPMSlotIdx);
	int nPMSlot = _ttoi(strPMSlotIdx);

	m_ctrlComboPMModule.GetLBText(nPMModuleIdx, strPMModuleIdx);
	int nPMModule = _ttoi(strPMModuleIdx);

	if ((nLLSlot * nLLModule) > (nPMSlot * nPMModule))
	{
		AfxMessageBox(
			_T("LoadLock의 총 Wafer수는 \nProcessModule의 총 Wafer수보다\n작아야합니다."),
			MB_ICONERROR);
	}

	else
	{
		CDialogEx::OnOK();
	}
}

void CSysInfoDlg::OnCbnSelchangeComboVacArm()
{

	CString strVacArm;
	CString strValue;

	m_ctrlComboPMSlot.ResetContent();
	m_ctrlComboPMModule.ResetContent();
	m_ctrlComboLLSlot.ResetContent();

	for (int i = 1; i < 7; i++)
	{
		strValue.Format(_T("%d"), i);
		m_ctrlComboPMModule.AddString(strValue);
	}
	m_ctrlComboPMModule.SetCurSel(0);

	int nVacArmIdx = m_ctrlComboVacArm.GetCurSel();
	m_ctrlComboVacArm.GetLBText(nVacArmIdx, strVacArm);
	int nVacArm = _ttoi(strVacArm);

	if (nVacArm == 2)
	{
		for (int i = 1; i < 7; i++)
		{
			strValue.Format(_T("%d"), i);
			m_ctrlComboPMSlot.AddString(strValue);
		}
		m_ctrlComboPMSlot.SetCurSel(0);


		for (int i = 1; i < 7; i++)
		{
			strValue.Format(_T("%d"), i);
			m_ctrlComboLLSlot.AddString(strValue);
		}
		m_ctrlComboLLSlot.SetCurSel(0);
	}
	else
	{
		m_ctrlComboPMSlot.AddString(_T("2"));
		m_ctrlComboPMSlot.AddString(_T("4"));
		m_ctrlComboPMSlot.AddString(_T("6"));
		m_ctrlComboPMSlot.SetCurSel(0);

		m_ctrlComboLLSlot.AddString(_T("2"));
		m_ctrlComboLLSlot.AddString(_T("4"));
		m_ctrlComboLLSlot.AddString(_T("6"));
		m_ctrlComboLLSlot.SetCurSel(0);
	}
}

void CSysInfoDlg::OnBnClickedCancel()
{
	if (IDYES == AfxMessageBox(_T("설정이 적용되지 않습니다. 취소하시겠습니까?"), MB_YESNO))
	{
		CDialogEx::OnCancel();
	}
}

// 기본적으로 600으로 설정
// Clean Time도 동시에 설정되있음
void CSysInfoDlg::OnBnClickedSetProcessTime()
{
	CString strPMModuleIdx;
	int nPMModuleIdx = m_ctrlComboPMModule.GetCurSel();
	m_ctrlComboPMModule.GetLBText(nPMModuleIdx, strPMModuleIdx);
	m_nPMModule = _ttoi(strPMModuleIdx);

	if (m_dlgSetProcess.DoModal() == IDOK)
	{
		for (int nIdx = 0; nIdx < m_nPMModule; nIdx++)
		{
			m_arrPMProcess[nIdx] = m_dlgSetProcess.m_arrPMProcess[nIdx];
			m_arrCleanProcess[nIdx] = m_dlgSetProcess.m_arrPMProcess[nIdx] * 2; 
		}
	}
}

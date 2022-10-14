// CDlg_SYSINIT.cpp: 구현 파일
//

#include "pch.h"
#include "주성.h"
#include "주성Dlg.h"
#include "afxdialogex.h"
#include "CDlg_SYSINIT.h"

#define MSEC 1000

// CDlg_SYSINIT 대화 상자

IMPLEMENT_DYNAMIC(CDlg_SYSINIT, CDialogEx)

CDlg_SYSINIT::CDlg_SYSINIT(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SYS_INIT, pParent)
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
	, m_nPMProcessTime(0)
	, m_nPMSlotOpenTime(0)
	, m_nPMSlotCloseTime(0)
	, m_strLLModuleCount(_T(""))
	, m_strLLSlotCount(_T(""))
	, m_strVacArmCount(_T(""))
	, m_strPMModuleCount(_T(""))
	, m_strPMSlotCount(_T(""))
	, m_nCleanCount(0)
{
}

CDlg_SYSINIT::~CDlg_SYSINIT()
{
}

void CDlg_SYSINIT::DoDataExchange(CDataExchange* pDX)
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
	DDX_Text(pDX, IDC_EDIT_PM_PROCESS_TIME, m_nPMProcessTime);
	DDX_Text(pDX, IDC_EDIT_PM_SLOT_OPEN_TIME, m_nPMSlotOpenTime);
	DDX_Text(pDX, IDC_EDIT_PM_SLOT_CLOSE_TIME, m_nPMSlotCloseTime);

	DDX_CBString(pDX, IDC_COMBO_MODULE_COUNT, m_strLLModuleCount);
	DDX_CBString(pDX, IDC_COMBO_MODULESLOT, m_strLLSlotCount);
	DDX_CBString(pDX, IDC_COMBO_VAC_ARM, m_strVacArmCount);
	DDX_CBString(pDX, IDC_COMBO_PM_MODULE, m_strPMModuleCount);
	DDX_CBString(pDX, IDC_COMBO_PM_SLOT, m_strPMSlotCount);
	DDX_Text(pDX, IDC_EDIT_CLEANCOUNT, m_nCleanCount);
}


BEGIN_MESSAGE_MAP(CDlg_SYSINIT, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlg_SYSINIT::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COMBO_VAC_ARM, &CDlg_SYSINIT::OnCbnSelchangeComboVacArm)
	//ON_CBN_SELCHANGE(IDC_COMBO_PM_SLOT, &CDlg_SYSINIT::OnCbnSelchangeComboPmSlot)
	//ON_BN_CLICKED(IDC_BUTTON_LOAD, &CDlg_SYSINIT::OnBnClickedButtonLoad)
	//ON_BN_CLICKED(IDC_BUTTON_Save, &CDlg_SYSINIT::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDCANCEL, &CDlg_SYSINIT::OnBnClickedCancel)
END_MESSAGE_MAP()


// CDlg_SYSINIT 메시지 처리기
void CDlg_SYSINIT::InitComboBox()
{
	m_ctrlComboVacArm.InsertString(0, _T("2"));
	m_ctrlComboVacArm.AddString(_T("4"));

	m_ctrlComboPMSlot.InsertString(0, _T("1"));
	m_ctrlComboPMSlot.AddString(_T("2"));
	m_ctrlComboPMSlot.AddString(_T("3"));
	m_ctrlComboPMSlot.AddString(_T("4"));
	m_ctrlComboPMSlot.AddString(_T("5"));
	m_ctrlComboPMSlot.AddString(_T("6"));

	m_ctrlComboPMModule.InsertString(0, _T("1"));
	m_ctrlComboPMModule.AddString(_T("2"));
	m_ctrlComboPMModule.AddString(_T("3"));
	m_ctrlComboPMModule.AddString(_T("4"));
	m_ctrlComboPMModule.AddString(_T("5"));
	m_ctrlComboPMModule.AddString(_T("6"));

	m_ctrlComboLLModule.InsertString(0, _T("1"));
	m_ctrlComboLLModule.AddString(_T("2"));
	m_ctrlComboLLModule.AddString(_T("3"));
	m_ctrlComboLLModule.AddString(_T("4"));

	m_ctrlComboLLSlot.InsertString(0, _T("1"));
	m_ctrlComboLLSlot.AddString(_T("2"));
	m_ctrlComboLLSlot.AddString(_T("3"));
	m_ctrlComboLLSlot.AddString(_T("4"));
	m_ctrlComboLLSlot.AddString(_T("5"));
	m_ctrlComboLLSlot.AddString(_T("6"));
	m_ctrlComboLLSlot.AddString(_T("7"));
	m_ctrlComboLLSlot.AddString(_T("8"));
	m_ctrlComboLLSlot.AddString(_T("9"));
	m_ctrlComboLLSlot.AddString(_T("10"));
	m_ctrlComboLLSlot.AddString(_T("11"));
	m_ctrlComboLLSlot.AddString(_T("12"));
	m_ctrlComboLLSlot.AddString(_T("13"));
	m_ctrlComboLLSlot.AddString(_T("14"));
	m_ctrlComboLLSlot.AddString(_T("15"));
	m_ctrlComboLLSlot.AddString(_T("16"));
	m_ctrlComboLLSlot.AddString(_T("17"));
	m_ctrlComboLLSlot.AddString(_T("18"));
	m_ctrlComboLLSlot.AddString(_T("19"));
	m_ctrlComboLLSlot.AddString(_T("20"));
	m_ctrlComboLLSlot.AddString(_T("21"));
	m_ctrlComboLLSlot.AddString(_T("22"));
	m_ctrlComboLLSlot.AddString(_T("23"));
	m_ctrlComboLLSlot.AddString(_T("24"));
	m_ctrlComboLLSlot.AddString(_T("25"));
}

BOOL CDlg_SYSINIT::OnInitDialog()
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
	m_nPMProcessTime = pMainDlg->m_nPM_Time / MSEC;
	m_nCleanCount = pMainDlg->m_nPM_Clean_Wafer_Count;
	m_nPMSlotOpenTime = pMainDlg->m_nPM_Slot_Valve_Open / MSEC;
	m_nPMSlotCloseTime = pMainDlg->m_nPM_Slot_Valve_Close / MSEC;

	CString strValue;

	strValue.Format(_T("%d"), m_nEFEMPickTime);
	GetDlgItem(IDC_EDIT_EFEM_PICKTIME)->SetWindowText(strValue);
	strValue.Format(_T("%d"), m_nEFEMMoveTime);
	GetDlgItem(IDC_EDIT_EFEM_MOVETIME)->SetWindowText(strValue);
	strValue.Format(_T("%d"), m_nEFEMPlaceTime);
	GetDlgItem(IDC_EDIT_EFEM_PLACETIME)->SetWindowText(strValue);
	strValue.Format(_T("%.1f"), m_nEFEMRotateTime);
	GetDlgItem(IDC_EDIT_ROTATETIME)->SetWindowText(strValue);

	strValue.Format(_T("%d"), m_nLLPumpTime);
	GetDlgItem(IDC_EDIT_PUMP_TIME)->SetWindowText(strValue);
	strValue.Format(_T("%d"), m_nLLPumpStableTime);
	GetDlgItem(IDC_EDIT_LL_PUMP_STABLETIME)->SetWindowText(strValue);
	strValue.Format(_T("%d"), m_nLLVentTime);
	GetDlgItem(IDC_EDIT_LL_VENT_TIME)->SetWindowText(strValue);
	strValue.Format(_T("%d"), m_nLLVentStableTime);
	GetDlgItem(IDC_EDIT_VENT_STABLETIME)->SetWindowText(strValue);
	strValue.Format(_T("%d"), m_nLLSlotOpenTime);
	GetDlgItem(IDC_EDIT_LL_SLOT_OPEN_TIME)->SetWindowText(strValue);
	strValue.Format(_T("%d"), m_nLLSlotCloseTime);
	GetDlgItem(IDC_EDIT_LL_SLOT_CLOSE_TIME)->SetWindowText(strValue);
	strValue.Format(_T("%d"), m_nLLDoorOpenTime);
	GetDlgItem(IDC_EDIT_LL_DOOR_OPEN_TIME)->SetWindowText(strValue);
	strValue.Format(_T("%d"), m_nLLDoorCloseTime);
	GetDlgItem(IDC_EDIT_LL_DOOR_CLOSE_TIME)->SetWindowText(strValue);

	strValue.Format(_T("%d"), m_nTMRotate);
	GetDlgItem(IDC_EDIT_TM_ROTATE)->SetWindowText(strValue);
	strValue.Format(_T("%d"), m_nTMPickTime);
	GetDlgItem(IDC_EDIT_TM_PICK_TIME)->SetWindowText(strValue);
	strValue.Format(_T("%d"), m_nTMPlaceTime);
	GetDlgItem(IDC_EDIT_TM_PLACE_TIME)->SetWindowText(strValue);

	strValue.Format(_T("%d"), m_nPMProcessTime);
	GetDlgItem(IDC_EDIT_PM_PROCESS_TIME)->SetWindowText(strValue);
	strValue.Format(_T("%d"), m_nCleanCount);
	GetDlgItem(IDC_EDIT_CLEANCOUNT)->SetWindowText(strValue);
	strValue.Format(_T("%d"), m_nPMSlotOpenTime);
	GetDlgItem(IDC_EDIT_PM_SLOT_OPEN_TIME)->SetWindowText(strValue);
	strValue.Format(_T("%d"), m_nPMSlotCloseTime);
	GetDlgItem(IDC_EDIT_PM_SLOT_CLOSE_TIME)->SetWindowText(strValue);

	int nLLModuleIdx = 0;
	int nLLSlotIdx = 0;
	int nVacArmIdx = 0;
	int nPMModuleIdx = 0;
	int nPMSlotIdx = 0;
	int nValue = 0;

	InitComboBox();

	nVacArmIdx = m_ctrlComboVacArm.FindStringExact(0, m_strVacArmCount);
	m_ctrlComboVacArm.SetCurSel(nLLModuleIdx);

	m_ctrlComboVacArm.GetLBText(nVacArmIdx, strValue);
	nValue = _ttoi(strValue);

	for (int i = m_ctrlComboLLSlot.GetCount() - 1; i >= 0; i--)
	{
		m_ctrlComboLLSlot.DeleteString(i);
	}

	for (int i = m_ctrlComboPMSlot.GetCount() - 1; i >= 0; i--)
	{
		m_ctrlComboPMSlot.DeleteString(i);
	}

	for (int i = m_ctrlComboPMModule.GetCount() - 1; i >= 0; i--)
	{
		m_ctrlComboPMModule.DeleteString(i);
	}

	if (nValue == 2)
	{
		m_ctrlComboPMSlot.InsertString(0, _T("1"));
		m_ctrlComboPMSlot.AddString(_T("2"));
		m_ctrlComboPMSlot.AddString(_T("3"));
		m_ctrlComboPMSlot.AddString(_T("4"));
		m_ctrlComboPMSlot.AddString(_T("5"));
		m_ctrlComboPMSlot.AddString(_T("6"));

		m_ctrlComboPMModule.InsertString(0, _T("1"));
		m_ctrlComboPMModule.AddString(_T("2"));
		m_ctrlComboPMModule.AddString(_T("3"));
		m_ctrlComboPMModule.AddString(_T("4"));
		m_ctrlComboPMModule.AddString(_T("5"));
		m_ctrlComboPMModule.AddString(_T("6"));

		m_ctrlComboLLSlot.InsertString(0, _T("1"));
		m_ctrlComboLLSlot.AddString(_T("2"));
		m_ctrlComboLLSlot.AddString(_T("3"));
		m_ctrlComboLLSlot.AddString(_T("4"));
		m_ctrlComboLLSlot.AddString(_T("5"));
		m_ctrlComboLLSlot.AddString(_T("6"));
	}

	else
	{
		m_ctrlComboPMModule.InsertString(0, _T("1"));
		m_ctrlComboPMModule.AddString(_T("2"));
		m_ctrlComboPMModule.AddString(_T("3"));
		m_ctrlComboPMModule.AddString(_T("4"));
		m_ctrlComboPMModule.AddString(_T("5"));
		m_ctrlComboPMModule.AddString(_T("6"));

		m_ctrlComboPMSlot.InsertString(0, _T("2"));
		m_ctrlComboPMSlot.AddString(_T("4"));
		m_ctrlComboPMSlot.AddString(_T("6"));

		m_ctrlComboLLSlot.InsertString(0, _T("2"));
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


void CDlg_SYSINIT::OnBnClickedOk()
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
		UpdateData(1);

		C주성Dlg* pMainDlg = (C주성Dlg*)GetParent();
		pMainDlg->m_nATM_Pick = m_nEFEMPickTime * MSEC;
		pMainDlg->m_nATM_Place = m_nEFEMPlaceTime * MSEC;
		pMainDlg->m_nATM_Rotate = m_nEFEMRotateTime * MSEC;
		pMainDlg->m_nATM_ZRotate = m_nEFEMMoveTime * MSEC;

		pMainDlg->m_strLLModuleCnt = m_strLLModuleCount;
		pMainDlg->m_strLLSlotCnt = m_strLLSlotCount;
		pMainDlg->m_nLL_Pump = m_nLLPumpTime * MSEC;
		pMainDlg->m_nLL_Pump_Stable_Time = m_nLLPumpStableTime * MSEC;
		pMainDlg->m_nLL_Vent = m_nLLVentTime * MSEC;
		pMainDlg->m_nLL_Vent_Stable_Time = m_nLLVentStableTime * MSEC;
		pMainDlg->m_nLL_Slot_Valve_Open = m_nLLSlotOpenTime * MSEC;
		pMainDlg->m_nLL_Slot_Valve_Close = m_nLLSlotCloseTime * MSEC;
		pMainDlg->m_nLL_Door_Valve_Open = m_nLLDoorOpenTime * MSEC;
		pMainDlg->m_nLL_Door_Valve_Close = m_nLLDoorCloseTime * MSEC;

		pMainDlg->m_strVacArmCnt = m_strVacArmCount;
		pMainDlg->m_nVAC_Pick = m_nTMPickTime * MSEC;
		pMainDlg->m_nVAC_Place = m_nTMPlaceTime * MSEC;
		pMainDlg->m_nRotate = m_nTMRotate * MSEC;

		pMainDlg->m_strPMModuleCnt = m_strPMModuleCount;
		pMainDlg->m_strPMSlotCnt = m_strPMSlotCount;
		pMainDlg->m_nPM_Clean_Time = m_nPMProcessTime * 2 * MSEC;
		pMainDlg->m_nPM_Clean_Wafer_Count = m_nCleanCount;
		pMainDlg->m_nPM_Time = m_nPMProcessTime * MSEC;
		pMainDlg->m_nPM_Slot_Valve_Open = m_nPMSlotOpenTime * MSEC;
		pMainDlg->m_nPM_Slot_Valve_Close = m_nPMSlotCloseTime * MSEC;

		pMainDlg->GetDlgItem(IDC_START)->EnableWindow(TRUE);
		pMainDlg->GetDlgItem(IDC_BUTTON_SAVE_SYSTEMCONFIG)->EnableWindow(TRUE);
		pMainDlg->GetDlgItem(IDC_BUTTON_LOAD_SYSTEMCONFIG)->EnableWindow(TRUE);
		pMainDlg->GetDlgItem(IDC_BUTTON_SAVE_THROUGHPUT)->EnableWindow(TRUE);
		pMainDlg->GetDlgItem(IDC_BUTTON_LOAD_THROUGHPUT)->EnableWindow(TRUE);

		CDialogEx::OnOK();
	}
}


void CDlg_SYSINIT::OnCbnSelchangeComboVacArm()
{
	for (int i = m_ctrlComboPMSlot.GetCount() - 1; i >= 0; i--)
	{
		m_ctrlComboPMSlot.DeleteString(i);
	}

	for (int i = m_ctrlComboPMModule.GetCount() - 1; i >= 0; i--)
	{
		m_ctrlComboPMModule.DeleteString(i);
	}

	for (short i = m_ctrlComboLLSlot.GetCount() - 1; i >= 0; i--)
	{
		m_ctrlComboLLSlot.DeleteString(i);
	}

	int nVacArmIdx = m_ctrlComboVacArm.GetCurSel();
	CString strVacArm;
	m_ctrlComboVacArm.GetLBText(nVacArmIdx, strVacArm);
	int nVacArm = _ttoi(strVacArm);

	if (nVacArm == 2)
	{
		m_ctrlComboPMSlot.InsertString(0, _T("1"));
		m_ctrlComboPMSlot.AddString(_T("2"));
		m_ctrlComboPMSlot.AddString(_T("3"));
		m_ctrlComboPMSlot.AddString(_T("4"));
		m_ctrlComboPMSlot.AddString(_T("5"));
		m_ctrlComboPMSlot.AddString(_T("6"));
		m_ctrlComboPMSlot.SetCurSel(0);

		m_ctrlComboPMModule.InsertString(0, _T("1"));
		m_ctrlComboPMModule.AddString(_T("2"));
		m_ctrlComboPMModule.AddString(_T("3"));
		m_ctrlComboPMModule.AddString(_T("4"));
		m_ctrlComboPMModule.AddString(_T("5"));
		m_ctrlComboPMModule.AddString(_T("6"));
		m_ctrlComboPMModule.SetCurSel(0);

		m_ctrlComboLLSlot.InsertString(0, _T("1"));
		m_ctrlComboLLSlot.AddString(_T("2"));
		m_ctrlComboLLSlot.AddString(_T("3"));
		m_ctrlComboLLSlot.AddString(_T("4"));
		m_ctrlComboLLSlot.AddString(_T("5"));
		m_ctrlComboLLSlot.AddString(_T("6"));/*
		m_ctrlComboLLSlot.AddString(_T("7"));
		m_ctrlComboLLSlot.AddString(_T("8"));
		m_ctrlComboLLSlot.AddString(_T("9"));
		m_ctrlComboLLSlot.AddString(_T("10"));
		m_ctrlComboLLSlot.AddString(_T("11"));
		m_ctrlComboLLSlot.AddString(_T("12"));
		m_ctrlComboLLSlot.AddString(_T("13"));
		m_ctrlComboLLSlot.AddString(_T("14"));
		m_ctrlComboLLSlot.AddString(_T("15"));
		m_ctrlComboLLSlot.AddString(_T("16"));
		m_ctrlComboLLSlot.AddString(_T("17"));
		m_ctrlComboLLSlot.AddString(_T("18"));
		m_ctrlComboLLSlot.AddString(_T("19"));
		m_ctrlComboLLSlot.AddString(_T("20"));
		m_ctrlComboLLSlot.AddString(_T("21"));
		m_ctrlComboLLSlot.AddString(_T("22"));
		m_ctrlComboLLSlot.AddString(_T("23"));
		m_ctrlComboLLSlot.AddString(_T("24"));
		m_ctrlComboLLSlot.AddString(_T("25"));*/
		m_ctrlComboLLSlot.SetCurSel(0);
	}

	else
	{
		m_ctrlComboPMSlot.InsertString(0, _T("1"));
		m_ctrlComboPMSlot.AddString(_T("2"));
		m_ctrlComboPMSlot.AddString(_T("3"));
		m_ctrlComboPMSlot.AddString(_T("4"));
		m_ctrlComboPMSlot.AddString(_T("5"));
		m_ctrlComboPMSlot.AddString(_T("6"));
		m_ctrlComboPMSlot.SetCurSel(0);

		m_ctrlComboPMModule.InsertString(0, _T("1"));
		m_ctrlComboPMModule.AddString(_T("2"));
		m_ctrlComboPMModule.AddString(_T("3"));
		m_ctrlComboPMModule.SetCurSel(0);

		m_ctrlComboLLSlot.InsertString(0, _T("2"));
		m_ctrlComboLLSlot.AddString(_T("4"));
		m_ctrlComboLLSlot.AddString(_T("6"));/*
		m_ctrlComboLLSlot.AddString(_T("8"));
		m_ctrlComboLLSlot.AddString(_T("10"));
		m_ctrlComboLLSlot.AddString(_T("12"));
		m_ctrlComboLLSlot.AddString(_T("14"));
		m_ctrlComboLLSlot.AddString(_T("16"));
		m_ctrlComboLLSlot.AddString(_T("18"));
		m_ctrlComboLLSlot.AddString(_T("20"));
		m_ctrlComboLLSlot.AddString(_T("22"));
		m_ctrlComboLLSlot.AddString(_T("24"));*/
		m_ctrlComboLLSlot.SetCurSel(0);
	}
}

void CDlg_SYSINIT::OnBnClickedCancel()
{
	if (IDYES == AfxMessageBox(_T("설정이 적용되지 않습니다. 취소하시겠습니까?"), MB_YESNO))
	{
		CDialogEx::OnCancel();
	}
}
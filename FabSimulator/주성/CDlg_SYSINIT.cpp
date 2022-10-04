// CDlg_SYSINIT.cpp: 구현 파일
//

#include "pch.h"
#include "주성.h"
#include "주성Dlg.h"
#include "afxdialogex.h"
#include "CDlg_SYSINIT.h"


// CDlg_SYSINIT 대화 상자

IMPLEMENT_DYNAMIC(CDlg_SYSINIT, CDialogEx)

CDlg_SYSINIT::CDlg_SYSINIT(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SYS_INIT, pParent)
	, m_nEFEMPickTime(0)
	, m_nMoveTime(0)
	, m_nEFEMPlaceTime(0)
	, m_nEFEMRotateTime(0)
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
	, m_nLLModuleCount(0)
	, m_nLLSlotCount(0)
	, m_nVacArm(0)
	, m_nPMModuleCount(0)
	, m_nPMSlotCount(0)
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
	DDX_Text(pDX, IDC_EDIT_EFEM_MOVETIME, m_nMoveTime);
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
	DDX_Text(pDX, IDC_EDIT_SLOT_CLOSE_TIME, m_nPMSlotCloseTime);
	DDX_CBIndex(pDX, IDC_COMBO_MODULE_COUNT, m_nLLModuleCount);
	DDX_CBIndex(pDX, IDC_COMBO_MODULESLOT, m_nLLSlotCount);
	DDX_CBIndex(pDX, IDC_COMBO_VAC_ARM, m_nVacArm);
	DDX_CBIndex(pDX, IDC_COMBO_PM_MODULE, m_nPMModuleCount);
	DDX_CBIndex(pDX, IDC_COMBO_PM_SLOT, m_nPMSlotCount);
}


BEGIN_MESSAGE_MAP(CDlg_SYSINIT, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlg_SYSINIT::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COMBO_VAC_ARM, &CDlg_SYSINIT::OnCbnSelchangeComboVacArm)
	ON_CBN_SELCHANGE(IDC_COMBO_PM_SLOT, &CDlg_SYSINIT::OnCbnSelchangeComboPmSlot)
END_MESSAGE_MAP()


// CDlg_SYSINIT 메시지 처리기


BOOL CDlg_SYSINIT::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_ctrlComboVacArm.InsertString(0, _T("2"));
	m_ctrlComboVacArm.AddString(_T("4"));
	m_ctrlComboVacArm.SetCurSel(0);

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

	m_ctrlComboLLModule.InsertString(0, _T("1"));
	m_ctrlComboLLModule.AddString(_T("2"));
	m_ctrlComboLLModule.AddString(_T("3"));
	m_ctrlComboLLModule.AddString(_T("4"));
	m_ctrlComboLLModule.SetCurSel(0);

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
	m_ctrlComboLLSlot.SetCurSel(0);

	C주성Dlg* pMainDlg = (C주성Dlg*)GetParent();


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
		m_ctrlComboLLSlot.SetCurSel(0);
	}

	else
	{
		m_ctrlComboPMSlot.InsertString(0, _T("2"));
		m_ctrlComboPMSlot.AddString(_T("4"));
		m_ctrlComboPMSlot.AddString(_T("6"));
		m_ctrlComboPMSlot.SetCurSel(0);

		m_ctrlComboPMModule.InsertString(0, _T("1"));
		m_ctrlComboPMModule.AddString(_T("2"));
		m_ctrlComboPMModule.AddString(_T("3"));
		m_ctrlComboPMModule.SetCurSel(0);

		m_ctrlComboLLSlot.InsertString(0, _T("2"));
		m_ctrlComboLLSlot.AddString(_T("4"));
		m_ctrlComboLLSlot.AddString(_T("6"));
		m_ctrlComboLLSlot.AddString(_T("8"));
		m_ctrlComboLLSlot.AddString(_T("10"));
		m_ctrlComboLLSlot.AddString(_T("12"));
		m_ctrlComboLLSlot.AddString(_T("14"));
		m_ctrlComboLLSlot.AddString(_T("16"));
		m_ctrlComboLLSlot.AddString(_T("18"));
		m_ctrlComboLLSlot.AddString(_T("20"));
		m_ctrlComboLLSlot.AddString(_T("22"));
		m_ctrlComboLLSlot.AddString(_T("24"));
		m_ctrlComboLLSlot.SetCurSel(0);
	}
}


void CDlg_SYSINIT::OnCbnSelchangeComboPmSlot()
{
	for (short i = m_ctrlComboPMModule.GetCount() - 1; i >= 0; i--)
	{
		m_ctrlComboPMModule.DeleteString(i);
	}

	int nPM_SlotIdx = m_ctrlComboPMSlot.GetCurSel();
	CString strPMSlot;
	m_ctrlComboPMSlot.GetLBText(nPM_SlotIdx, strPMSlot);
	int nPMSlot = _ttoi(strPMSlot);

	if (nPMSlot == 1)
	{
		m_ctrlComboPMModule.InsertString(0, _T("1"));
		m_ctrlComboPMModule.AddString(_T("2"));
		m_ctrlComboPMModule.AddString(_T("3"));
		m_ctrlComboPMModule.AddString(_T("4"));
		m_ctrlComboPMModule.AddString(_T("5"));
		m_ctrlComboPMModule.AddString(_T("6"));
		m_ctrlComboPMModule.SetCurSel(0);
	}
	else
	{
		m_ctrlComboPMModule.InsertString(0, _T("1"));
		m_ctrlComboPMModule.AddString(_T("2"));
		m_ctrlComboPMModule.AddString(_T("3"));
		m_ctrlComboPMModule.SetCurSel(0);
	}
}

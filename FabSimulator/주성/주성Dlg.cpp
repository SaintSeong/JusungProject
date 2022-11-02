
// 주성Dlg.cpp: 구현 파일
//
#include "pch.h"
#include "framework.h"
#include "주성.h"
#include "주성Dlg.h"
#include "afxdialogex.h"
#include "CSysInfoDlg.h"
#ifdef _DEBUGasdasdasd
#define new DEBUG_NEW
#endif

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
    CAboutDlg();

    // 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_ABOUTBOX };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

    // 구현입니다.
protected:
    DECLARE_MESSAGE_MAP()
public:
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// C주성Dlg 메시지 처리기
C주성Dlg* g_pMainDlg;
CSysInfoDlg* g_pSubDlg;
CRect g_CRtemp(0, 0, 2, 2);/*
CRect g_CR_LL1(940, 130, 1080, 300);
CRect g_CR_LL2(1100, 137, 1240, 300);
CRect g_CR_LL3(940, 360, 1080, 530);
CRect g_CR_LL4(1100, 360, 1240, 530);*/
HANDLE g_hEventStart;
HANDLE g_hEventPM_Array;
HANDLE g_hEventLL_Modul_one_Thread4and1;
HANDLE g_hEventLL_Modul_one_Thread1and2;
HANDLE g_hEventcount;
HANDLE g_hEvent_Thread3_Wait;
HANDLE g_hEventThread_Time_Error; //쓰레드 시간이 안맞을때 관리하는 이벤트
HANDLE g_hEventThread4_wait;
HANDLE g_hEvent_PM_MAX;
HANDLE g_hThread1[2], g_hThread2, g_hThread3, g_hThread4,
g_hThread_PM[6], g_hThread_LL[4],
g_hThread_TotalTime, g_hThread_Thread_Start;
// C주성Dlg 대화 상자
C주성Dlg::C주성Dlg(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_MAINVIEW, pParent)
    , m_strLLModuleCnt(_T("1"))
    , m_strLLSlotCnt(_T("1"))
    , m_strVacArmCnt(_T("2"))
    , m_strPMModuleCnt(_T("1"))
    , m_strPMSlotCnt(_T("1"))
    , m_nTotalSec(0)
    , m_nCleanSec(0)
    , m_brGreen(RGB(0, 255, 0))
    , m_brBlue(RGB(0, 0, 255))
    , m_brRed(RGB(255, 0, 0))
    , m_brGray(RGB(140, 140, 140))
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    m_nWafer_Count = 0;
    m_nLLMAX = 0;

    g_pMainDlg = this;
}

void C주성Dlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    // 버튼 컨트롤
    DDX_Control(pDX, IDC_EFEMARM, m_ctrEFEM);
    DDX_Control(pDX, IDC_ALIGNER, m_ctrALIGNER);
    DDX_Control(pDX, IDC_TM, m_ctrTM);
    DDX_Control(pDX, IDC_LPM, m_ctrLPM);
    DDX_Control(pDX, IDC_LL_STATIC1, m_ctrLL1);
    DDX_Control(pDX, IDC_LL_STATIC2, m_ctrLL2);
    DDX_Control(pDX, IDC_LL_STATIC3, m_ctrLL3);
    DDX_Control(pDX, IDC_LL_STATIC4, m_ctrLL4);
    // PM 스태틱 컨트롤
    DDX_Control(pDX, IDC_STATIC_PM1, m_CtrStatic_PM1);
    DDX_Control(pDX, IDC_STATIC_PM2, m_CtrStatic_PM2);
    DDX_Control(pDX, IDC_STATIC_PM3, m_CtrStatic_PM3);
    DDX_Control(pDX, IDC_STATIC_PM4, m_CtrStatic_PM4);
    DDX_Control(pDX, IDC_STATIC_PM5, m_CtrStatic_PM5);
    DDX_Control(pDX, IDC_STATIC_PM6, m_CtrStatic_PM6);
    // 콤보박스 컨트롤
    DDX_Control(pDX, IDC_COMBO_SPEED, m_ctrSpeed);
    // 콤보박스 값
    DDX_CBString(pDX, IDC_COMBO_SPEED, m_strSpeed);

    //프로그래스바
    DDX_Control(pDX, IDC_PROGRESS_PM1, m_ctrPROGRESS_PM1);
    DDX_Control(pDX, IDC_PROGRESS_PM2, m_ctrPROGRESS_PM2);
    DDX_Control(pDX, IDC_PROGRESS_PM3, m_ctrPROGRESS_PM3);
    DDX_Control(pDX, IDC_PROGRESS_PM4, m_ctrPROGRESS_PM4);
    DDX_Control(pDX, IDC_PROGRESS_PM5, m_ctrPROGRESS_PM5);
    DDX_Control(pDX, IDC_PROGRESS_PM6, m_ctrPROGRESS_PM6);
    DDX_Control(pDX, IDC_PROGRESS_LL1, m_ctrPROGRESS_LL1);
    DDX_Control(pDX, IDC_PROGRESS_LL2, m_ctrPROGRESS_LL2);
    DDX_Control(pDX, IDC_PROGRESS_LL3, m_ctrPROGRESS_LL3);
    DDX_Control(pDX, IDC_PROGRESS_LL4, m_ctrPROGRESS_LL4);
    DDX_Control(pDX, IDC_STATIC_Time, m_ctrlStaticTotalTime);

    DDX_Control(pDX, IDC_STATIC_SPEED, m_ctrStatic_Speed);//
    //LPM UI 스태틱 변수
    DDX_Control(pDX, IDC_NUM_LPM1, m_ctrLPMUI1);
    DDX_Control(pDX, IDC_NUM_LPM2, m_ctrLPMUI2);
    DDX_Control(pDX, IDC_GUI_TM, m_Gui_TM);
    DDX_Control(pDX, IDC_GUI_PM1, m_Ctrl_Gui_PM1);
    DDX_Control(pDX, IDC_GUI_PM2, m_Ctrl_Gui_PM2);
    DDX_Control(pDX, IDC_GUI_PM3, m_Ctrl_Gui_PM3);
    DDX_Control(pDX, IDC_GUI_PM4, m_Ctrl_Gui_PM4);
    DDX_Control(pDX, IDC_GUI_PM5, m_Ctrl_Gui_PM5);
    DDX_Control(pDX, IDC_GUI_PM6, m_Ctrl_Gui_PM6);
    DDX_Control(pDX, IDC_GUI_LL1, m_ctrGUI_LL1);
    DDX_Control(pDX, IDC_GUI_LL2, m_ctrGUI_LL2);
    DDX_Control(pDX, IDC_GUI_LL3, m_ctrGUI_LL3);
    DDX_Control(pDX, IDC_GUI_LL4, m_ctrGUI_LL4);
    DDX_Control(pDX, IDC_GUI_EFEM, m_Ctrl_Gui_EFEM);
    DDX_Control(pDX, IDC_PM_COUNT1, m_ctrPM_Count1);
    DDX_Control(pDX, IDC_PM_COUNT2, m_ctrPM_Count2);
    DDX_Control(pDX, IDC_PM_COUNT3, m_ctrPM_Count3);
    DDX_Control(pDX, IDC_PM_COUNT4, m_ctrPM_Count4);
    DDX_Control(pDX, IDC_PM_COUNT5, m_ctrPM_Count5);
    DDX_Control(pDX, IDC_PM_COUNT6, m_ctrPM_Count6);
    DDX_Control(pDX, IDC_STATIC_CLEAN_TIME, m_ctrTotal_Clean_Time);
    DDX_Control(pDX, IDC_RADIO_Process1, m_ctrRadio_Process1);
    DDX_Control(pDX, IDC_RADIO_Process2, m_ctrRadio_Process2);
    DDX_Control(pDX, IDC_RADIO_Process3, m_ctrRadio_Process3);
    DDX_Control(pDX, IDC_RADIO_Process4, m_ctrRadio_Process4);
    DDX_Control(pDX, IDC_RADIO_Process5, m_ctrRadio_Process5);
    DDX_Control(pDX, IDC_RADIO_Process6, m_ctrRadio_Process6);
    DDX_Control(pDX, IDC_RADIO_Clean1, m_ctrRadio_Clean1);
    DDX_Control(pDX, IDC_RADIO_Clean2, m_ctrRadio_Clean2);
    DDX_Control(pDX, IDC_RADIO_Clean3, m_ctrRadio_Clean3);
    DDX_Control(pDX, IDC_RADIO_Clean4, m_ctrRadio_Clean4);
    DDX_Control(pDX, IDC_RADIO_Clean5, m_ctrRadio_Clean5);
    DDX_Control(pDX, IDC_RADIO_Clean6, m_ctrRadio_Clean6);
    DDX_Control(pDX, IDC_STATIC_OUTPUT, m_ctrOutput);
    DDX_Control(pDX, IDC_STATIC_THROUGHTPUT, m_ctrThrought);
    DDX_Control(pDX, IDC_PM_STATIC1, m_ctrPM1);
    DDX_Control(pDX, IDC_PM_STATIC2, m_ctrPM2);
    DDX_Control(pDX, IDC_PM_STATIC3, m_ctrPM3);
    DDX_Control(pDX, IDC_PM_STATIC4, m_ctrPM4);
    DDX_Control(pDX, IDC_PM_STATIC5, m_ctrPM5);
    DDX_Control(pDX, IDC_PM_STATIC6, m_ctrPM6);
    DDX_Control(pDX, IDC_STATIC_GREEN, m_ctrStaticGreen);
    DDX_Control(pDX, IDC_STATIC_BLUE, m_ctrStaticBlue);
    DDX_Control(pDX, IDC_STATIC_RED, m_ctrStaticRed);
    DDX_Control(pDX, IDC_PICTURE_BACK, m_ctrPicture_Back);
    DDX_Control(pDX, IDC_STATIC_GRAY, m_ctrStaticGray);
}

BEGIN_MESSAGE_MAP(C주성Dlg, CDialogEx)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_SYS_INFO, &C주성Dlg::OnBnClickedSysInitial)
    ON_BN_CLICKED(IDC_START, &C주성Dlg::OnBnClickedStart)
    ON_BN_CLICKED(IDC_BUTTON_SAVE_SYSTEMCONFIG, &C주성Dlg::OnBnClickedButtonSaveSystemconfig)
    ON_BN_CLICKED(IDC_BUTTON_SAVE_THROUGHPUT, &C주성Dlg::OnBnClickedButtonSaveThroughput)
    ON_COMMAND(IDC_SET_SPEED, &C주성Dlg::OnBnClickedSetSpeed)
    ON_BN_CLICKED(IDC_BUTTON_LOAD_SYSTEMCONFIG, &C주성Dlg::OnBnClickedButtonLoadSystemconfig)
    ON_BN_CLICKED(IDC_BUTTON_LOAD_THROUGHPUT, &C주성Dlg::OnBnClickedButtonLoadThroughput)
    ON_BN_CLICKED(IDC_CLEAR, &C주성Dlg::OnBnClickedClear)

END_MESSAGE_MAP()



BOOL C주성Dlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();
    // 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

    // IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ASSERT(IDM_ABOUTBOX < 0xF000);

    CMenu* pSysMenu = GetSystemMenu(FALSE);
    if (pSysMenu != nullptr)
    {
        BOOL bNameValid;
        CString strAboutMenu;
        bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
        ASSERT(bNameValid);
        if (!strAboutMenu.IsEmpty())
        {
            pSysMenu->AppendMenu(MF_SEPARATOR);
            pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
        }
    }

    // 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
    //  프레임워크가 이 작업을 자동으로 수행합니다.
    SetIcon(m_hIcon, TRUE);         // 큰 아이콘을 설정합니다.
    SetIcon(m_hIcon, FALSE);      // 작은 아이콘을 설정합니다.

    // TODO: 여기에 추가 초기화 작업을 추가합니다.
    m_nWafer_Count = 0;
    g_hEventStart = CreateEvent(NULL, FALSE, FALSE, NULL);//자동리셋 이벤트
    g_hEventLL_Modul_one_Thread1and2 = CreateEvent(NULL, FALSE, FALSE, NULL);//자동리셋 이벤트
    g_hEventThread_Time_Error = CreateEvent(NULL, FALSE, FALSE, NULL);//자동리셋 이벤트
    g_hEventcount = CreateEvent(NULL, TRUE, FALSE, NULL);
    g_hEvent_Thread3_Wait = CreateEvent(NULL, TRUE, FALSE, NULL);
    g_hEventThread4_wait = CreateEvent(NULL, FALSE, FALSE, NULL);
    g_hEvent_PM_MAX = CreateEvent(NULL, FALSE, FALSE, NULL);
    g_hEventLL_Modul_one_Thread4and1 = CreateEvent(NULL, FALSE, FALSE, NULL);
    g_hThread_TotalTime = CreateEvent(NULL, FALSE, FALSE, NULL);
    g_hEventPM_Array = CreateEvent(NULL, FALSE, FALSE, NULL);
    g_pMainDlg->m_ctrTotal_Clean_Time.SetWindowText(_T("00:00:00:00"));
    g_pMainDlg->m_ctrlStaticTotalTime.SetWindowText(_T("00:00:00:00"));

    m_bLL_Dummy = false;
    m_bClean_Time_Start = false;
    m_ctrSpeed.AddString(_T("1"));
    m_ctrSpeed.AddString(_T("20"));
    m_ctrSpeed.AddString(_T("30"));
    m_ctrSpeed.AddString(_T("40"));
    m_ctrSpeed.AddString(_T("50"));

    m_strLLSlotCnt = (_T("6"));
    m_strLLModuleCnt = (_T("4"));
    m_strVacArmCnt = (_T("4"));
    m_strPMModuleCnt = (_T("6"));
    m_strPMSlotCnt = (_T("6"));
    m_strSpeed = _T("50");

    m_noutput_count = 0;
    m_nThread1_LL = 0;
    m_nThread2_LL = 0;
    m_nThread3_LL = 1;
    m_nThread4_LL = 1;
    m_nThread_Time_Error = 0;
    m_Thread3start = 0;

    m_nATM_Pick = 4000;
    m_nATM_Place = 4000;
    m_nATM_Rotate = 1000;
    m_nATM_ZRotate = 1000;
    m_nLL_Pump = 15000;
    m_nLL_Pump_Stable_Time = 5000;
    m_nLL_Vent = 15000;
    m_nLL_Vent_Stable_Time = 5000;
    m_nLL_Slot_Valve_Open = 2000;
    m_nLL_Slot_Valve_Close = 2000;
    m_nLL_Door_Valve_Open = 2000;
    m_nLL_Door_Valve_Close = 2000;
    m_nVAC_Pick = 5000;
    m_nVAC_Place = 5000;
    m_nRotate = 5000;
    m_nPM_Time = 60000;
    m_nPM_Clean_Time = 1200000;
    m_nPM_Clean_Wafer_Count = 10;
    m_nPM_Slot_Valve_Open = 2000;
    m_nPM_Slot_Valve_Close = 2000;
    m_nSpeed = 0;

    m_ctrPROGRESS_PM1.SetRange(0, 100);
    m_ctrPROGRESS_PM2.SetRange(0, 100);
    m_ctrPROGRESS_PM3.SetRange(0, 100);
    m_ctrPROGRESS_PM4.SetRange(0, 100);
    m_ctrPROGRESS_PM5.SetRange(0, 100);
    m_ctrPROGRESS_PM6.SetRange(0, 100);

    m_ctrPROGRESS_LL1.SetRange(0, 50);
    m_ctrPROGRESS_LL2.SetRange(0, 50);
    m_ctrPROGRESS_LL3.SetRange(0, 50);
    m_ctrPROGRESS_LL4.SetRange(0, 50);

    m_ctrEFEM.ShowWindow(SW_HIDE);
    m_ctrALIGNER.ShowWindow(SW_HIDE);
    m_ctrTM.ShowWindow(SW_HIDE);
    m_ctrLPM.ShowWindow(SW_HIDE);

    m_fontTime.CreateFont(45,// nHeight 
        30, // nWidth                               
        0, // nEscapement                               
        0, // nOrientation                               
        5, // nWeight                                
        0, // bItalic                                
        0, // bUnderline                               
        0, // cStrikeOut                               
        0, // nCharSet                                
        OUT_DEFAULT_PRECIS, // nOutPrecision                               
        0, // nClipPrecision                               
        DEFAULT_QUALITY,// nQuality                               
        DEFAULT_PITCH | FF_DONTCARE,// nPitchAndFamily                               
        _T("고딕"));
    m_ctrlStaticTotalTime.SetFont(&m_fontTime, TRUE);
    m_ctrTotal_Clean_Time.SetFont(&m_fontTime, TRUE);

    GetDlgItem(IDC_START)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON_SAVE_SYSTEMCONFIG)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON_LOAD_SYSTEMCONFIG)->EnableWindow(TRUE);
    GetDlgItem(IDC_BUTTON_SAVE_THROUGHPUT)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON_LOAD_THROUGHPUT)->EnableWindow(TRUE);
    UpdateData(0);
    return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void C주성Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
    if ((nID & 0xFFF0) == IDM_ABOUTBOX)
    {
        CAboutDlg dlgAbout;
        dlgAbout.DoModal();
    }
    else
    {
        CDialogEx::OnSysCommand(nID, lParam);
    }
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void C주성Dlg::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

        // 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // 아이콘을 그립니다.
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDC* pDC = GetDC();
        CBrush* oldBrush = NULL;

        // //LPM1 빈공간
        {
            oldBrush = pDC->SelectObject(&m_brGray);
            for (int i = 24; i >= 0; i--)
            {
                pDC->Rectangle(85, 118 + (14.6 * i), 151, 132.6 + (14.6 * i));
            }
            pDC->SelectObject(oldBrush);
        }
        // //LPM1
        {
            oldBrush = pDC->SelectObject(&m_brGreen);

            for (int i = m_ctrLPMUI1.GetWindowInt() - 1; i >= 0; i--)
            {
                pDC->Rectangle(85, 118 + (14.6 * i), 151, 132.6 + (14.6 * i));
            }
            pDC->SelectObject(oldBrush);
        }
        // //LPM2 빈공간
        {
            oldBrush = pDC->SelectObject(&m_brGray);
            for (int i = 24; i >= 0; i--)
            {
                pDC->Rectangle(190, 118 + (14.6 * i), 255, 132.6 + (14.6 * i));
            }
            pDC->SelectObject(oldBrush);
        }
        // //LPM2 공정후
        {
            oldBrush = pDC->SelectObject(&m_brBlue);
            for (int i = 24; i > 24 - m_ctrLPMUI2.GetWindowInt(); i--)
            {
                pDC->Rectangle(190, 118 + (14.6 * i), 255, 132.6 + (14.6 * i));
            }
            pDC->SelectObject(oldBrush);
        }
        // //LL1 빈공간
        {
            oldBrush = pDC->SelectObject(&m_brGray);
            for (int i = _ttoi(m_strLLSlotCnt) - 1; i >= 0; i--)
            {
                pDC->Rectangle(970, 110 + (21.8 * i), 1035, 131.8 + (21.8 * i));
            }
            pDC->SelectObject(oldBrush);
        }
        // //LL1
        {
            oldBrush = pDC->SelectObject(&m_brGreen);
            for (int i = (m_ctrLL1.GetWindowInt() - 1); i >= 0; i--)
            {
                pDC->Rectangle(970, 110 + (21.8 * i), 1035, 131.8 + (21.8 * i));
            }
            pDC->SelectObject(oldBrush);
        }
        // //LL1 의 공정 끝낸 웨이퍼 개수
        {
            oldBrush = pDC->SelectObject(&m_brBlue);
            for (int i = m_nWafer_Process[0] - 1; i >= 0; i--)
            {
                pDC->Rectangle(970, 110 + (21.8 * i), 1035, 131.8 + (21.8 * i));
            }
            pDC->SelectObject(oldBrush);
        }
        if (_ttoi(m_strLLModuleCnt) > 1) //LL2 빈공간
        {
            oldBrush = pDC->SelectObject(&m_brGray);
            for (int i = _ttoi(m_strLLSlotCnt) - 1; i >= 0; i--)
            {
                pDC->Rectangle(1100, 110 + (21.8 * i), 1165, 131.8 + (21.8 * i));
            }
            pDC->SelectObject(oldBrush);
        }
        if (_ttoi(m_strLLModuleCnt) > 1) //LL2
        {
            oldBrush = pDC->SelectObject(&m_brGreen);
            for (int i = (m_ctrLL2.GetWindowInt() - 1); i >= 0; i--)
            {
                pDC->Rectangle(1100, 110 + (21.8 * i), 1165, 131.8 + (21.8 * i));
            }
            pDC->SelectObject(oldBrush);
        }
        if (_ttoi(m_strLLModuleCnt) > 1) //LL2 의 공정 끝낸 웨이퍼 개수
        {
            oldBrush = pDC->SelectObject(&m_brBlue);
            for (int i = m_nWafer_Process[1] - 1; i >= 0; i--)
            {
                pDC->Rectangle(1100, 110 + (21.8 * i), 1165, 131.8 + (21.8 * i));
            }
            pDC->SelectObject(oldBrush);
        }
        if (_ttoi(m_strLLModuleCnt) > 2) //LL3 빈공간
        {
            oldBrush = pDC->SelectObject(&m_brGray);
            for (int i = _ttoi(m_strLLSlotCnt) - 1; i >= 0; i--)
            {
                pDC->Rectangle(970, 331 + (21.8 * i), 1035, 352.8 + (21.8 * i));
            }
            pDC->SelectObject(oldBrush);
        }
        if (_ttoi(m_strLLModuleCnt) > 2) //LL3
        {
            oldBrush = pDC->SelectObject(&m_brGreen);
            for (int i = (m_ctrLL3.GetWindowInt() - 1); i >= 0; i--)
            {
                pDC->Rectangle(970, 331 + (21.8 * i), 1035, 352.8 + (21.8 * i));
            }
            pDC->SelectObject(oldBrush);
        }

        if (_ttoi(m_strLLModuleCnt) > 2) //LL3 의 공정끝낸 웨이퍼 개수
        {
            oldBrush = pDC->SelectObject(&m_brBlue);
            for (int i = m_nWafer_Process[2] - 1; i >= 0; i--)
            {
                pDC->Rectangle(970, 331 + (21.8 * i), 1035, 352.8 + (21.8 * i));
            }
            pDC->SelectObject(oldBrush);
        }
        if (_ttoi(m_strLLModuleCnt) > 3) //LL4 빈공간
        {
            oldBrush = pDC->SelectObject(&m_brGray);
            for (int i = _ttoi(m_strLLSlotCnt) - 1; i >= 0; i--)
            {
                pDC->Rectangle(1100, 331 + (21.8 * i), 1165, 352.8 + (21.8 * i));

            }
            pDC->SelectObject(oldBrush);
        }
        if (_ttoi(m_strLLModuleCnt) > 3) //LL4
        {
            oldBrush = pDC->SelectObject(&m_brGreen);
            for (int i = (m_ctrLL4.GetWindowInt() - 1); i >= 0; i--)
            {
                pDC->Rectangle(1100, 331 + (21.8 * i), 1165, 352.8 + (21.8 * i));
            }
            pDC->SelectObject(oldBrush);
        }
        if (_ttoi(m_strLLModuleCnt) > 3) //LL4 의 공정끝낸 웨이퍼 개수
        {
            oldBrush = pDC->SelectObject(&m_brBlue);
            for (int i = m_nWafer_Process[3] - 1; i >= 0; i--)
            {
                pDC->Rectangle(1100, 331 + (21.8 * i), 1165, 352.8 + (21.8 * i));
            }
            pDC->SelectObject(oldBrush);
        }

        CRect rect;

        m_ctrStaticGreen.GetWindowRect(&rect);
        ScreenToClient(rect);
        oldBrush = pDC->SelectObject(&m_brGreen);
        pDC->Rectangle(rect);
        pDC->SelectObject(oldBrush);

        m_ctrStaticBlue.GetWindowRect(&rect);
        ScreenToClient(rect);
        oldBrush = pDC->SelectObject(&m_brBlue);
        pDC->Rectangle(rect);
        pDC->SelectObject(oldBrush);

        m_ctrStaticRed.GetWindowRect(&rect);
        ScreenToClient(rect);
        oldBrush = pDC->SelectObject(&m_brRed);
        pDC->Rectangle(rect);
        pDC->SelectObject(oldBrush);

        m_ctrStaticGray.GetWindowRect(&rect);
        ScreenToClient(rect);
        oldBrush = pDC->SelectObject(&m_brGray);
        pDC->Rectangle(rect);
        pDC->SelectObject(oldBrush);

        ReleaseDC(pDC);
        CDialogEx::OnPaint();
    }
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR C주성Dlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}

//===============================================================
//                      실행 Code
//===============================================================
DWORD WINAPI Thread_Start(LPVOID p);      //FINAL RESULT (THROUGHPUT)
DWORD WINAPI Thread_1_LPM2LL(LPVOID p);     //EFEM Pre-Process(EFEM-IN)
DWORD WINAPI Thread_2_LL2PM(LPVOID p);      //TM Pre-Process(TM-IN)  
DWORD WINAPI Thread_3_PM2LL(LPVOID p);      //TM Post-Process(TM-OUT)
DWORD WINAPI Thread_4_LL2OUT(LPVOID p);     //EFEM Post-Process(EFEM-OUT)
DWORD WINAPI PM(LPVOID p);
DWORD WINAPI LL(LPVOID p);
DWORD WINAPI TotalTime(LPVOID p); // Total time 표시

//EFEM Pre-Process(EFEM-IN)
void C주성Dlg::DrawSemiconductor(CWnd* pWnd, CString strImageName)
{
    CImage image;
    if (E_FAIL != image.Load(strImageName))//이미지 로드
    {
        CRect rect;
        pWnd->GetWindowRect(rect);

        CDC* dc = pWnd->GetDC();
        image.StretchBlt(dc->m_hDC, 0, 0, rect.Width(), rect.Height(), SRCCOPY);
        pWnd->ReleaseDC(dc);
    }
}
DWORD WINAPI Thread_1_LPM2LL(LPVOID p)
{
    int nLPM_cnt;
    int nLL_cnt;
    int nEFEM_cnt;
    int nINPUT_cnt;
    int nAligner_cnt;
    CString strImage;

    nLPM_cnt = g_pMainDlg->m_ctrLPM.GetWindowInt();
    if (g_pMainDlg->m_strLLModuleCnt == _T("1"))
    {
        if ((g_pMainDlg->m_ctrLL1.GetWindowInt() == 0 && g_pMainDlg->m_ctrPM1.GetWindowInt() == 0))
        {
            g_pMainDlg->m_nThread1_LL = 0;
            strImage.Format(_T("UI\\LL\\슬라이드%d.png"), 8);
            g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_ctrGUI_LL1, strImage);
        }
    }
    else if (g_pMainDlg->m_strLLModuleCnt == _T("2"))
    {
        if ((g_pMainDlg->m_ctrLL1.GetWindowInt() == 0 && g_pMainDlg->m_ctrPM1.GetWindowInt() == 0))
        {
            g_pMainDlg->m_nThread1_LL = 0;
            strImage.Format(_T("UI\\LL\\슬라이드%d.png"), 8);
            g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_ctrGUI_LL1, strImage);
        }
        else if ((g_pMainDlg->m_ctrLL2.GetWindowInt() == 0 && g_pMainDlg->m_nThread1_LL == 0))
        {
            g_pMainDlg->m_nThread1_LL = 1;
            strImage.Format(_T("UI\\LL\\슬라이드%d.png"), 8);
            g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_ctrGUI_LL2, strImage);
        }
        else if ((g_pMainDlg->m_ctrLL1.GetWindowInt() == 0 && g_pMainDlg->m_nThread1_LL == 1))
        {
            g_pMainDlg->m_nThread1_LL = 0;
            strImage.Format(_T("UI\\LL\\슬라이드%d.png"), 8);
            g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_ctrGUI_LL1, strImage);
        }
    }
    else if (g_pMainDlg->m_strLLModuleCnt == _T("3"))
    {
        if ((g_pMainDlg->m_ctrLL1.GetWindowInt() == 0 && g_pMainDlg->m_ctrPM1.GetWindowInt() == 0))
        {
            g_pMainDlg->m_nThread1_LL = 0;
            strImage.Format(_T("UI\\LL\\슬라이드%d.png"), 8);
            g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_ctrGUI_LL1, strImage);
        }
        else if ((g_pMainDlg->m_ctrLL2.GetWindowInt() == 0 && g_pMainDlg->m_nThread1_LL == 0))
        {
            g_pMainDlg->m_nThread1_LL = 1;
            strImage.Format(_T("UI\\LL\\슬라이드%d.png"), 8);
            g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_ctrGUI_LL2, strImage);
        }
        else if ((g_pMainDlg->m_ctrLL3.GetWindowInt() == 0 && g_pMainDlg->m_nThread1_LL == 1))
        {
            g_pMainDlg->m_nThread1_LL = 2;
            strImage.Format(_T("UI\\LL\\슬라이드%d.png"), 8);
            g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_ctrGUI_LL3, strImage);
        }
        else if ((g_pMainDlg->m_ctrLL1.GetWindowInt() == 0 && g_pMainDlg->m_nThread1_LL == 2))
        {
            g_pMainDlg->m_nThread1_LL = 0;
            strImage.Format(_T("UI\\LL\\슬라이드%d.png"), 8);
            g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_ctrGUI_LL1, strImage);
        }
    }
    else if (g_pMainDlg->m_strLLModuleCnt == _T("4"))
    {
        if ((g_pMainDlg->m_ctrLL1.GetWindowInt() == 0 && g_pMainDlg->m_ctrPM1.GetWindowInt() == 0 && g_pMainDlg->m_nThread1_LL != 1) || (g_pMainDlg->m_ctrLL1.GetWindowInt() == 0 && g_pMainDlg->m_Thread3start == 1))
        {
            g_pMainDlg->m_nThread1_LL = 0;
            strImage.Format(_T("UI\\LL\\슬라이드%d.png"), 8);
            g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_ctrGUI_LL1, strImage);
        }
        else if ((g_pMainDlg->m_ctrLL2.GetWindowInt() == 0 && g_pMainDlg->m_nThread1_LL == 0))
        {
            g_pMainDlg->m_nThread1_LL = 1;
            strImage.Format(_T("UI\\LL\\슬라이드%d.png"), 8);
            g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_ctrGUI_LL2, strImage);
        }
        else if ((g_pMainDlg->m_ctrLL3.GetWindowInt() == 0 && g_pMainDlg->m_nThread1_LL == 1))
        {
            g_pMainDlg->m_nThread1_LL = 2;
            strImage.Format(_T("UI\\LL\\슬라이드%d.png"), 8);
            g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_ctrGUI_LL3, strImage);
        }
        else if ((g_pMainDlg->m_ctrLL4.GetWindowInt() == 0 && g_pMainDlg->m_nThread1_LL == 2))
        {
            g_pMainDlg->m_nThread1_LL = 3;
            strImage.Format(_T("UI\\LL\\슬라이드%d.png"), 8);
            g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_ctrGUI_LL4, strImage);
        }
        else if ((g_pMainDlg->m_ctrLL1.GetWindowInt() == 0 && g_pMainDlg->m_nThread1_LL == 3))
        {
            g_pMainDlg->m_nThread1_LL = 0;
            strImage.Format(_T("UI\\LL\\슬라이드%d.png"), 8);
            g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_ctrGUI_LL1, strImage);
        }
    }
    if (g_pMainDlg->m_Thread3start == 1)
        g_pMainDlg->m_nThread1_LL = g_pMainDlg->m_nThread4_LL - 1;

    nINPUT_cnt = g_pMainDlg->m_ctrLPM.GetWindowInt();
    if (g_pMainDlg->m_nThread1_LL == 0)
        nLL_cnt = g_pMainDlg->m_ctrLL1.GetWindowInt();
    else if (g_pMainDlg->m_nThread1_LL == 1)
        nLL_cnt = g_pMainDlg->m_ctrLL2.GetWindowInt();
    else if (g_pMainDlg->m_nThread1_LL == 2)
        nLL_cnt = g_pMainDlg->m_ctrLL3.GetWindowInt();
    else if (g_pMainDlg->m_nThread1_LL == 3)
        nLL_cnt = g_pMainDlg->m_ctrLL4.GetWindowInt();

    //1. PICK : LPM -> ATM ROBOT
    Sleep(g_pMainDlg->m_nATM_ZRotate / g_pMainDlg->m_nSpeed);
    Sleep(g_pMainDlg->m_nATM_Pick / g_pMainDlg->m_nSpeed);
    for (int i = 1; i < 5; i++)
    {
        strImage.Format(_T("UI\\EFEM1\\슬라이드%d.png"), i);
        g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Ctrl_Gui_EFEM, strImage);
    }
    for (int i = 0;; i++)
    {
        if (nLL_cnt == g_pMainDlg->m_nLLMAX / _ttoi(g_pMainDlg->m_strLLModuleCnt)) break;  //LL이 꽉 찼다면 wafer 잡지마
        if (nLL_cnt == nINPUT_cnt) break;  //LL에 있는 wafer 공정 끝날 때까지 잡지 말고 대기

        g_pMainDlg->m_ctrLPM.SetWindowInt(nLPM_cnt);
        g_pMainDlg->m_ctrEFEM.SetWindowInt(i);

        //모든 LL과 모든 PM의 슬롯이 가득차 있으면 더 넣지않는다.
        if (g_pMainDlg->m_nWafer_Count == (_ttoi(g_pMainDlg->m_strPMModuleCnt) * _ttoi(g_pMainDlg->m_strPMSlotCnt)) + g_pMainDlg->m_nLLMAX) break;

        g_pMainDlg->m_nWafer_Count = g_pMainDlg->m_nWafer_Count + i;

        if (nLPM_cnt == 0) break;  //LPM에 남아있는 wafer가 없다
        if (i == 1) break;  //ATM ROBOT이 wafer를 한 개씩 잡는다

        nLPM_cnt--;

        g_pMainDlg->m_nTotal_Input++;
        if ((g_pMainDlg->m_nTotal_Input - 1) % (_ttoi(g_pMainDlg->m_strPMModuleCnt) * _ttoi(g_pMainDlg->m_strPMSlotCnt) * g_pMainDlg->m_nPM_Clean_Wafer_Count) == 0
            && (g_pMainDlg->m_nTotal_Input - 1) != 0)
        {
            g_pMainDlg->m_bClean_Time_Start = true;
        }
        g_pMainDlg->m_ctrLPMUI1.SetWindowInt(g_pMainDlg->m_ctrLPMUI1.GetWindowInt() - 1);
        if (g_pMainDlg->m_ctrLPMUI1.GetWindowInt() == 0)
            g_pMainDlg->m_ctrLPMUI1.SetWindowInt(25);
    }
    g_pMainDlg->InvalidateRect(g_CRtemp, false);
    nEFEM_cnt = g_pMainDlg->m_ctrEFEM.GetWindowInt();
    nLPM_cnt = g_pMainDlg->m_ctrLPM.GetWindowInt();

    //2. PLACE : ATM ROBOT -> ALIGNER
    Sleep(g_pMainDlg->m_nATM_Rotate / g_pMainDlg->m_nSpeed);
    Sleep(g_pMainDlg->m_nATM_ZRotate / g_pMainDlg->m_nSpeed);
    Sleep(g_pMainDlg->m_nATM_Place / g_pMainDlg->m_nSpeed);
    for (int i = 5; i < 7; i++)
    {
        strImage.Format(_T("UI\\EFEM1\\슬라이드%d.png"), i);
        g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Ctrl_Gui_EFEM, strImage);
    }
    for (int i = 0; ; i++)
    {
        if (nLL_cnt == g_pMainDlg->m_nLLMAX / _ttoi(g_pMainDlg->m_strLLModuleCnt)) break;  //LL이 꽉 찼다면 wafer 잡지마
        if (nLL_cnt == nINPUT_cnt) break;  //LL에 있는 wafer 공정 끝날 때까지 잡지 말고 대기

        g_pMainDlg->m_ctrEFEM.SetWindowInt(nEFEM_cnt);
        g_pMainDlg->m_ctrALIGNER.SetWindowInt(i);

        if (nEFEM_cnt == 0) break;  //EFEM(ATM ROBOT)에 남아있는 wafer가 없다
        if (i == 1) break;  //ATM ROBOT이 wafer를 한 개씩 잡는다

        nEFEM_cnt--;

    }

    //3. PICK & PLACE (LPM -> ATM ROBOT -> LL)
    while (nLPM_cnt != 0 && nLL_cnt != (g_pMainDlg->m_nLLMAX / _ttoi(g_pMainDlg->m_strLLModuleCnt)) - 1)
    {
        //한번에 LL과 PM에 넣을 수 있는 wafer의 갯수는 같다(비례)
        if (g_pMainDlg->m_nWafer_Count == (_ttoi(g_pMainDlg->m_strPMModuleCnt) * _ttoi(g_pMainDlg->m_strPMSlotCnt) + g_pMainDlg->m_nLLMAX)) break;

        nLPM_cnt = g_pMainDlg->m_ctrLPM.GetWindowInt();

        //1) PICK : LPM -> ATM ROBOT
        Sleep(g_pMainDlg->m_nATM_Rotate / g_pMainDlg->m_nSpeed);
        Sleep(g_pMainDlg->m_nATM_ZRotate / g_pMainDlg->m_nSpeed);
        Sleep(g_pMainDlg->m_nATM_Pick / g_pMainDlg->m_nSpeed);
        for (int i = 7; i < 10; i++)
        {
            strImage.Format(_T("UI\\EFEM1\\슬라이드%d.png"), i);
            g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Ctrl_Gui_EFEM, strImage);
        }
        for (int i = 0; ; i++)
        {
            if (nLL_cnt == nINPUT_cnt) break;  //LL에 있는 wafer 공정 끝날 때까지 잡지 말고 대기

            g_pMainDlg->m_ctrLPM.SetWindowInt(nLPM_cnt);
            g_pMainDlg->m_ctrEFEM.SetWindowInt(i);

            if (nLPM_cnt == 0) break;  //LPM에 남아있는 wafer가 없다

            //한번에 LL과 PM에 넣을 수 있는 wafer의 갯수는 같다(비례)
            if (g_pMainDlg->m_nWafer_Count == (_ttoi(g_pMainDlg->m_strPMModuleCnt) * _ttoi(g_pMainDlg->m_strPMSlotCnt) + g_pMainDlg->m_nLLMAX))break;

            g_pMainDlg->m_nWafer_Count = g_pMainDlg->m_nWafer_Count + i;

            if (i == 1) break;  //ATM ROBOT이 wafer를 한 개씩 잡는다

            nLPM_cnt--;

            g_pMainDlg->m_nTotal_Input++;
            if ((g_pMainDlg->m_nTotal_Input - 1) % (_ttoi(g_pMainDlg->m_strPMModuleCnt) * _ttoi(g_pMainDlg->m_strPMSlotCnt) * g_pMainDlg->m_nPM_Clean_Wafer_Count) == 0
                && (g_pMainDlg->m_nTotal_Input - 1) != 0)
            {
                g_pMainDlg->m_bClean_Time_Start = true;
            }

            g_pMainDlg->m_ctrLPMUI1.SetWindowInt(g_pMainDlg->m_ctrLPMUI1.GetWindowInt() - 1);
            if (g_pMainDlg->m_ctrLPMUI1.GetWindowInt() == 0)
                g_pMainDlg->m_ctrLPMUI1.SetWindowInt(25);

        }
        g_pMainDlg->InvalidateRect(g_CRtemp, false);
        nAligner_cnt = g_pMainDlg->m_ctrALIGNER.GetWindowInt();

        //2) PICK : ALIGNER -> ATM ROBOT
        Sleep(g_pMainDlg->m_nATM_Rotate / g_pMainDlg->m_nSpeed);
        Sleep(g_pMainDlg->m_nATM_ZRotate / g_pMainDlg->m_nSpeed);
        Sleep(g_pMainDlg->m_nATM_Pick / g_pMainDlg->m_nSpeed);

        for (int i = 10; i < 12; i++)
        {
            strImage.Format(_T("UI\\EFEM1\\슬라이드%d.png"), i);
            g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Ctrl_Gui_EFEM, strImage);
        }
        for (int i = 1; ; i++)
        {
            if (nLL_cnt == g_pMainDlg->m_nLLMAX / _ttoi(g_pMainDlg->m_strLLModuleCnt)) break;  //LL이 꽉 찼다면 wafer 잡지마
            if (nLL_cnt == nINPUT_cnt) break;  //LL에 있는 wafer 공정 끝날 때까지 잡지 말고 대기

            g_pMainDlg->m_ctrALIGNER.SetWindowInt(nAligner_cnt);
            g_pMainDlg->m_ctrEFEM.SetWindowInt(i);

            if (i == 2) break;  //ATM ROBOT이 최대로 잡을 수 있는 wafer는 2장(MAX)
            if (nAligner_cnt == 0) break;  //Aligner에 남아있는 wafer가 없다

            nAligner_cnt--;

        }
        nEFEM_cnt = g_pMainDlg->m_ctrEFEM.GetWindowInt();

        //3) PLACE : ATM ROBOT -> ALIGNER
        Sleep(g_pMainDlg->m_nATM_ZRotate / g_pMainDlg->m_nSpeed);
        Sleep(g_pMainDlg->m_nATM_Place / g_pMainDlg->m_nSpeed);
        for (int i = 12; i < 13; i++)
        {
            strImage.Format(_T("UI\\EFEM1\\슬라이드%d.png"), i);
            g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Ctrl_Gui_EFEM, strImage);
        }
        for (int i = 0;; i++)
        {
            if (nLL_cnt == g_pMainDlg->m_nLLMAX / _ttoi(g_pMainDlg->m_strLLModuleCnt)) break;  //LL이 꽉 찼다면 wafer 잡지마
            if (nLL_cnt == nINPUT_cnt) break;  //LL에 있는 wafer 공정 끝날 때까지 잡지 말고 대기

            g_pMainDlg->m_ctrEFEM.SetWindowInt(nEFEM_cnt);
            g_pMainDlg->m_ctrALIGNER.SetWindowInt(i);

            if (i == 1) break;  //Aligner에 놓을 수 있는 wafer는 1개(MAX)
            if (nEFEM_cnt == 0) break;  //EFEM(ATM ROBOT)에 남아있는 wafer가 없다

            nEFEM_cnt--;

        }

        nEFEM_cnt = g_pMainDlg->m_ctrEFEM.GetWindowInt();
        if (g_pMainDlg->m_nThread1_LL == 0)
            nLL_cnt = g_pMainDlg->m_ctrLL1.GetWindowInt();
        else if (g_pMainDlg->m_nThread1_LL == 1)
            nLL_cnt = g_pMainDlg->m_ctrLL2.GetWindowInt();
        else if (g_pMainDlg->m_nThread1_LL == 2)
            nLL_cnt = g_pMainDlg->m_ctrLL3.GetWindowInt();
        else if (g_pMainDlg->m_nThread1_LL == 3)
            nLL_cnt = g_pMainDlg->m_ctrLL4.GetWindowInt();
        //4) PLACE : ATM ROBOT -> LL
        Sleep(g_pMainDlg->m_nATM_Rotate / g_pMainDlg->m_nSpeed);
        Sleep(g_pMainDlg->m_nLL_Door_Valve_Open / g_pMainDlg->m_nSpeed);
        Sleep(g_pMainDlg->m_nATM_ZRotate / g_pMainDlg->m_nSpeed);
        Sleep(g_pMainDlg->m_nATM_Place / g_pMainDlg->m_nSpeed);

        
        for (int i = 13; i < 16; i++)
        {
            strImage.Format(_T("UI\\EFEM1\\슬라이드%d.png"), i);
            g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Ctrl_Gui_EFEM, strImage);
        }
        for (int i = nLL_cnt;; i++)
        {
            if (nLL_cnt == g_pMainDlg->m_nLLMAX / _ttoi(g_pMainDlg->m_strLLModuleCnt)) break;  //LL이 꽉 찼다면 wafer 잡지마
            if (nLL_cnt == nINPUT_cnt) break;  //LL에 있는 wafer 공정 끝날 때까지 잡지 말고 대기

            g_pMainDlg->m_ctrEFEM.SetWindowInt(nEFEM_cnt);
            if (g_pMainDlg->m_nThread1_LL == 0)
            {
                g_pMainDlg->m_ctrLL1.SetWindowInt(i);
                strImage.Format(_T("UI\\LL\\슬라이드%d.png"), 3);
                g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_ctrGUI_LL1, strImage);
            }
            else if (g_pMainDlg->m_nThread1_LL == 1)
            {
                g_pMainDlg->m_ctrLL2.SetWindowInt(i);
                strImage.Format(_T("UI\\LL\\슬라이드%d.png"), 3);
                g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_ctrGUI_LL2, strImage);
            }
            else if (g_pMainDlg->m_nThread1_LL == 2)
            {
                g_pMainDlg->m_ctrLL3.SetWindowInt(i);
                strImage.Format(_T("UI\\LL\\슬라이드%d.png"), 3);
                g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_ctrGUI_LL3, strImage);
            }
            else if (g_pMainDlg->m_nThread1_LL == 3)
            {
                g_pMainDlg->m_ctrLL4.SetWindowInt(i);
                strImage.Format(_T("UI\\LL\\슬라이드%d.png"), 3);
                g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_ctrGUI_LL4, strImage);
            }

            if (nEFEM_cnt == 0) break;  //EFEM(ATM ROBOT)에 남아있는 wafer가 없다

            nEFEM_cnt--;

        }
        g_pMainDlg->InvalidateRect(g_CRtemp, false);
        Sleep(g_pMainDlg->m_nLL_Door_Valve_Close / g_pMainDlg->m_nSpeed);
        if (g_pMainDlg->m_nThread1_LL == 0)
            nLL_cnt = g_pMainDlg->m_ctrLL1.GetWindowInt();
        else if (g_pMainDlg->m_nThread1_LL == 1)
            nLL_cnt = g_pMainDlg->m_ctrLL2.GetWindowInt();
        else if (g_pMainDlg->m_nThread1_LL == 2)
            nLL_cnt = g_pMainDlg->m_ctrLL3.GetWindowInt();
        else if (g_pMainDlg->m_nThread1_LL == 3)
            nLL_cnt = g_pMainDlg->m_ctrLL4.GetWindowInt();
        nLPM_cnt = g_pMainDlg->m_ctrLPM.GetWindowInt();

    }

    nAligner_cnt = g_pMainDlg->m_ctrALIGNER.GetWindowInt();

    //4. PICK : ALIGNER -> ATM ROBOT(Last One)
    Sleep(g_pMainDlg->m_nATM_Rotate / g_pMainDlg->m_nSpeed);
    Sleep(g_pMainDlg->m_nATM_ZRotate / g_pMainDlg->m_nSpeed);
    Sleep(g_pMainDlg->m_nATM_Pick / g_pMainDlg->m_nSpeed);
    for (int i = 25; i < 27; i++)
    {
        strImage.Format(_T("UI\\EFEM1\\슬라이드%d.png"), i);
        g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Ctrl_Gui_EFEM, strImage);
    }
    for (int i = 0;; i++)
    {
        if (nLL_cnt == g_pMainDlg->m_nLLMAX / _ttoi(g_pMainDlg->m_strLLModuleCnt)) break;  //LL이 꽉 찼다면 wafer 잡지마
        if (nLL_cnt == nINPUT_cnt) break;  //LL에 있는 wafer 공정 끝날 때까지 잡지 말고 대기

        g_pMainDlg->m_ctrALIGNER.SetWindowInt(nAligner_cnt);
        g_pMainDlg->m_ctrEFEM.SetWindowInt(i);

        if (i == 1) break;  //ATM ROBOT이 wafer를 한 개씩 잡는다
        if (nAligner_cnt == 0)break;  //Aligner에 남아있는 wafer가 없다

        nAligner_cnt--;

    }

    nEFEM_cnt = g_pMainDlg->m_ctrEFEM.GetWindowInt();

    //5. PLACE : ATM ROBOT -> LL(Last One)
    Sleep(g_pMainDlg->m_nATM_Rotate / g_pMainDlg->m_nSpeed);
    Sleep(g_pMainDlg->m_nLL_Door_Valve_Open / g_pMainDlg->m_nSpeed);
    Sleep(g_pMainDlg->m_nATM_ZRotate / g_pMainDlg->m_nSpeed);
    Sleep(g_pMainDlg->m_nATM_Place / g_pMainDlg->m_nSpeed);
    for (int i = 27; i < 30; i++)
    {
        strImage.Format(_T("UI\\EFEM1\\슬라이드%d.png"), i);
        g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Ctrl_Gui_EFEM, strImage);
    }
    for (int i = nLL_cnt;; i++)
    {
        if (nLL_cnt == g_pMainDlg->m_nLLMAX / _ttoi(g_pMainDlg->m_strLLModuleCnt)) break;  //LL이 꽉 찼다면 wafer 잡지마
        if (nLL_cnt == nINPUT_cnt) break;  //LL에 있는 wafer 공정 끝날 때까지 잡지 말고 대기

        g_pMainDlg->m_ctrEFEM.SetWindowInt(nEFEM_cnt);
        if (g_pMainDlg->m_nThread1_LL == 0)
            g_pMainDlg->m_ctrLL1.SetWindowInt(i);
        else if (g_pMainDlg->m_nThread1_LL == 1)
            g_pMainDlg->m_ctrLL2.SetWindowInt(i);
        else if (g_pMainDlg->m_nThread1_LL == 2)
            g_pMainDlg->m_ctrLL3.SetWindowInt(i);
        else if (g_pMainDlg->m_nThread1_LL == 3)
            g_pMainDlg->m_ctrLL4.SetWindowInt(i);

        if (nEFEM_cnt == 0) break;  //EFEM(ATM ROBOT)에 남아있는 wafer가 없다 

        nEFEM_cnt--;

    }
    g_pMainDlg->InvalidateRect(g_CRtemp, false);
    Sleep(g_pMainDlg->m_nLL_Door_Valve_Close / g_pMainDlg->m_nSpeed);

    if (g_pMainDlg->m_nThread_Time_Error == _ttoi(g_pMainDlg->m_strLLModuleCnt))
    {
        g_pMainDlg->m_nThread_Time_Error--;
    }
    else if (g_pMainDlg->m_Thread3start != 0)
    {
        g_pMainDlg->m_nThread_Time_Error--;
    }
    SetEvent(g_hEventStart);
    if (g_pMainDlg->m_ctrLL1.GetWindowInt() != 0 && g_pMainDlg->m_nThread1_LL == 0)
    {
        strImage.Format(_T("UI\\LL\\슬라이드%d.png"), 1);
        g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_ctrGUI_LL1, strImage);
        for (int i = 1; i <= 50; i++)
        {
            g_pMainDlg->m_ctrPROGRESS_LL1.SetPos(i);
            Sleep(g_pMainDlg->m_nLL_Pump / (g_pMainDlg->m_nSpeed * 50));
            Sleep(g_pMainDlg->m_nLL_Pump_Stable_Time / (g_pMainDlg->m_nSpeed * 50));
        }
        g_pMainDlg->m_ctrPROGRESS_LL1.SetPos(0);
    }
    else if (g_pMainDlg->m_ctrLL2.GetWindowInt() != 0 && g_pMainDlg->m_nThread1_LL == 1)
    {
        strImage.Format(_T("UI\\LL\\슬라이드%d.png"), 1);
        g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_ctrGUI_LL2, strImage);
        for (int i = 1; i <= 50; i++)
        {
            g_pMainDlg->m_ctrPROGRESS_LL2.SetPos(i);
            Sleep(g_pMainDlg->m_nLL_Pump / (g_pMainDlg->m_nSpeed * 50));
            Sleep(g_pMainDlg->m_nLL_Pump_Stable_Time / (g_pMainDlg->m_nSpeed * 50));
        }
        g_pMainDlg->m_ctrPROGRESS_LL2.SetPos(0);
    }
    else if (g_pMainDlg->m_ctrLL3.GetWindowInt() != 0 && g_pMainDlg->m_nThread1_LL == 2)
    {
        strImage.Format(_T("UI\\LL\\슬라이드%d.png"), 1);
        g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_ctrGUI_LL3, strImage);
        for (int i = 1; i <= 50; i++)
        {
            g_pMainDlg->m_ctrPROGRESS_LL3.SetPos(i);
            Sleep(g_pMainDlg->m_nLL_Pump / (g_pMainDlg->m_nSpeed * 50));
            Sleep(g_pMainDlg->m_nLL_Pump_Stable_Time / (g_pMainDlg->m_nSpeed * 50));
        }
        g_pMainDlg->m_ctrPROGRESS_LL3.SetPos(0);
    }
    else if (g_pMainDlg->m_ctrLL4.GetWindowInt() != 0 && g_pMainDlg->m_nThread1_LL == 3)
    {
        strImage.Format(_T("UI\\LL\\슬라이드%d.png"), 1);
        g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_ctrGUI_LL4, strImage);
        for (int i = 1; i <= 50; i++)
        {
            g_pMainDlg->m_ctrPROGRESS_LL4.SetPos(i);
            Sleep(g_pMainDlg->m_nLL_Pump / (g_pMainDlg->m_nSpeed * 50));
            Sleep(g_pMainDlg->m_nLL_Pump_Stable_Time / (g_pMainDlg->m_nSpeed * 50));
        }
        g_pMainDlg->m_ctrPROGRESS_LL4.SetPos(0);
    }
    if (g_pMainDlg->m_nThread_Time_Error + 1 == _ttoi(g_pMainDlg->m_strLLModuleCnt))
        SetEvent(g_hEventThread_Time_Error);
    int nPM_MAX = _ttoi(g_pMainDlg->m_strPMSlotCnt) * _ttoi(g_pMainDlg->m_strPMModuleCnt);
    int PM_Count = g_pMainDlg->m_ctrPM1.GetWindowInt() +
        g_pMainDlg->m_ctrPM2.GetWindowInt() +
        g_pMainDlg->m_ctrPM3.GetWindowInt() +
        g_pMainDlg->m_ctrPM4.GetWindowInt() +
        g_pMainDlg->m_ctrPM5.GetWindowInt() +
        g_pMainDlg->m_ctrPM6.GetWindowInt();
    if (PM_Count != nPM_MAX && g_pMainDlg->m_Thread3start == 0)
    {
        g_hThread2 = (CreateThread(NULL, 0, Thread_2_LL2PM, 0, 0, 0));
    }
    return 0;
}
//TM Pre-Process(TM-IN)
DWORD WINAPI Thread_2_LL2PM(LPVOID p)
{
    int nTM_cnt = 0;
    int nLL_cnt = 0;
    int nPM_cnt = 0;
    int nLPM_cnt = 0;
    CString strImage;
    //g_pMainDlg->InvalidateRect(g_CRtemp2, false);

    if (g_pMainDlg->m_ctrLL1.GetWindowInt() != 0 && g_pMainDlg->m_nThread2_LL == 0)
    {
        g_pMainDlg->m_nThread2_LL = 1;
        strImage.Format(_T("UI\\LL\\슬라이드%d.png"), 2);
        g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_ctrGUI_LL1, strImage);

    }
    else if (g_pMainDlg->m_ctrLL2.GetWindowInt() != 0 && g_pMainDlg->m_nThread2_LL == 1)
    {
        g_pMainDlg->m_nThread2_LL = 2;
        strImage.Format(_T("UI\\LL\\슬라이드%d.png"), 2);
        g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_ctrGUI_LL2, strImage);
    }
    else if (g_pMainDlg->m_ctrLL3.GetWindowInt() != 0 && g_pMainDlg->m_nThread2_LL == 2)
    {
        g_pMainDlg->m_nThread2_LL = 3;
        strImage.Format(_T("UI\\LL\\슬라이드%d.png"), 2);
        g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_ctrGUI_LL3, strImage);
    }
    else if (g_pMainDlg->m_ctrLL4.GetWindowInt() != 0 && g_pMainDlg->m_nThread2_LL == 3)
    {
        g_pMainDlg->m_nThread2_LL = 4;
        strImage.Format(_T("UI\\LL\\슬라이드%d.png"), 2);
        g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_ctrGUI_LL4, strImage);
    }
    else if (g_pMainDlg->m_ctrLL1.GetWindowInt() != 0 && g_pMainDlg->m_nThread2_LL == 4)
    {
        g_pMainDlg->m_nThread2_LL = 1;
        strImage.Format(_T("UI\\LL\\슬라이드%d.png"), 2);
        g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_ctrGUI_LL1, strImage);
    }
    else if (g_pMainDlg->m_nThread2_LL == _ttoi(g_pMainDlg->m_strLLModuleCnt))
        g_pMainDlg->m_nThread2_LL = 1;
    nLPM_cnt = g_pMainDlg->m_ctrLPM.GetWindowInt();
    {
        //PICK & PLACE (LL -> VAC ROBOT -> PM1)
        while (true)
        {
            int PM_Count = g_pMainDlg->m_ctrPM1.GetWindowInt() +
                g_pMainDlg->m_ctrPM2.GetWindowInt() +
                g_pMainDlg->m_ctrPM3.GetWindowInt() +
                g_pMainDlg->m_ctrPM4.GetWindowInt() +
                g_pMainDlg->m_ctrPM5.GetWindowInt() +
                g_pMainDlg->m_ctrPM6.GetWindowInt();
            int nPM_MAX = _ttoi(g_pMainDlg->m_strPMSlotCnt) * _ttoi(g_pMainDlg->m_strPMModuleCnt);
            if (PM_Count == nPM_MAX)break;

            if (g_pMainDlg->m_nThread2_LL == 1)
                nLL_cnt = g_pMainDlg->m_ctrLL1.GetWindowInt();

            if (g_pMainDlg->m_nThread2_LL == 2)
                nLL_cnt = g_pMainDlg->m_ctrLL2.GetWindowInt();

            if (g_pMainDlg->m_nThread2_LL == 3)
                nLL_cnt = g_pMainDlg->m_ctrLL3.GetWindowInt();

            if (g_pMainDlg->m_nThread2_LL == 4)
                nLL_cnt = g_pMainDlg->m_ctrLL4.GetWindowInt();

            // if (g_pMainDlg->m_strPMModuleCnt == _T("6"))

            if ((g_pMainDlg->m_ctrPM1.GetWindowInt() != _ttoi(g_pMainDlg->m_strPMSlotCnt)) && _ttoi(g_pMainDlg->m_strPMModuleCnt) >= 1)
                nPM_cnt = g_pMainDlg->m_ctrPM1.GetWindowInt();

            else if ((g_pMainDlg->m_ctrPM2.GetWindowInt() != _ttoi(g_pMainDlg->m_strPMSlotCnt)) && _ttoi(g_pMainDlg->m_strPMModuleCnt) >= 2)
                nPM_cnt = g_pMainDlg->m_ctrPM2.GetWindowInt();

            else if ((g_pMainDlg->m_ctrPM3.GetWindowInt() != _ttoi(g_pMainDlg->m_strPMSlotCnt)) && _ttoi(g_pMainDlg->m_strPMModuleCnt) >= 3)
                nPM_cnt = g_pMainDlg->m_ctrPM3.GetWindowInt();

            else if ((g_pMainDlg->m_ctrPM4.GetWindowInt() != _ttoi(g_pMainDlg->m_strPMSlotCnt)) && _ttoi(g_pMainDlg->m_strPMModuleCnt) >= 4)
                nPM_cnt = g_pMainDlg->m_ctrPM4.GetWindowInt();

            else if ((g_pMainDlg->m_ctrPM5.GetWindowInt() != _ttoi(g_pMainDlg->m_strPMSlotCnt)) && _ttoi(g_pMainDlg->m_strPMModuleCnt) >= 5)
                nPM_cnt = g_pMainDlg->m_ctrPM5.GetWindowInt();

            else if ((g_pMainDlg->m_ctrPM6.GetWindowInt() != _ttoi(g_pMainDlg->m_strPMSlotCnt)) && _ttoi(g_pMainDlg->m_strPMModuleCnt) >= 6)
                nPM_cnt = g_pMainDlg->m_ctrPM6.GetWindowInt();

            nTM_cnt = g_pMainDlg->m_ctrTM.GetWindowInt();

            //PM이 가득 찼거나, LL에 남아있는 wafer가 없다면 종료

            if (nPM_cnt == _ttoi(g_pMainDlg->m_strPMSlotCnt) || (nLL_cnt == 0 && nTM_cnt == 0)) break;
            //PICK : LL -> VAC ROBOT
            Sleep(g_pMainDlg->m_nRotate / g_pMainDlg->m_nSpeed);
            Sleep(g_pMainDlg->m_nVAC_Pick / g_pMainDlg->m_nSpeed);
            for (int i = 1; i <= 4; i++)
            {
                strImage.Format(_T("UI\\TM(Quad)\\슬라이드%d.png"), i);
                g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Gui_TM, strImage);
            }
            for (int i = 0; nTM_cnt == 0; i++)
            {
                if (nPM_cnt == _ttoi(g_pMainDlg->m_strPMSlotCnt)) break;  //PM이 가득 찼다면 종료
                if (g_pMainDlg->m_strVacArmCnt == _T("4"))
                {
                    if (i % 2 == 0)
                    {
                        g_pMainDlg->m_ctrTM.SetWindowInt(i);
                        if (g_pMainDlg->m_nThread2_LL == 1)
                        {
                            g_pMainDlg->m_ctrLL1.SetWindowInt(nLL_cnt);
                            g_pMainDlg->InvalidateRect(g_CRtemp, false);
                        }
                        if (g_pMainDlg->m_nThread2_LL == 2)
                        {
                            g_pMainDlg->m_ctrLL2.SetWindowInt(nLL_cnt);
                            g_pMainDlg->InvalidateRect(g_CRtemp, false);
                        }
                        if (g_pMainDlg->m_nThread2_LL == 3)
                        {
                            g_pMainDlg->m_ctrLL3.SetWindowInt(nLL_cnt);
                            g_pMainDlg->InvalidateRect(g_CRtemp, false);
                        }
                        if (g_pMainDlg->m_nThread2_LL == 4)
                        {
                            g_pMainDlg->m_ctrLL4.SetWindowInt(nLL_cnt);
                            g_pMainDlg->InvalidateRect(g_CRtemp, false);
                        }
                    }
                }
                else if (g_pMainDlg->m_strVacArmCnt == _T("2"))
                {
                    g_pMainDlg->m_ctrTM.SetWindowInt(i);
                    if (g_pMainDlg->m_nThread2_LL == 1)
                    {
                        g_pMainDlg->m_ctrLL1.SetWindowInt(nLL_cnt);
                        g_pMainDlg->InvalidateRect(g_CRtemp, false);
                    }
                    if (g_pMainDlg->m_nThread2_LL == 2)
                    {
                        g_pMainDlg->m_ctrLL2.SetWindowInt(nLL_cnt);
                        g_pMainDlg->InvalidateRect(g_CRtemp, false);
                    }
                    if (g_pMainDlg->m_nThread2_LL == 3)
                    {
                        g_pMainDlg->m_ctrLL3.SetWindowInt(nLL_cnt);
                        g_pMainDlg->InvalidateRect(g_CRtemp, false);
                    }
                    if (g_pMainDlg->m_nThread2_LL == 4)
                    {
                        g_pMainDlg->m_ctrLL4.SetWindowInt(nLL_cnt);
                        g_pMainDlg->InvalidateRect(g_CRtemp, false);
                    }
                }
                if (nLL_cnt == 0) break;  //LL에 남아있는 wafer가 없다면 종료
                

                nLL_cnt--;

                if (i == _ttoi(g_pMainDlg->m_strVacArmCnt) / 2) break;  //TM(VAC ROBOT)이 Dual Arm일 땐 wafer 2장,
                //Quad Arm일 때 wafer를 4장 들고 있다면 대기
            }
          
            if (g_pMainDlg->m_nThread2_LL == 1 && g_pMainDlg->m_ctrLL1.GetWindowInt()==0)
            {
                strImage.Format(_T("UI\\LL\\슬라이드%d.png"), 9);
                g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_ctrGUI_LL1, strImage);
            }
            if (g_pMainDlg->m_nThread2_LL == 2 && g_pMainDlg->m_ctrLL2.GetWindowInt() == 0)
            {
                strImage.Format(_T("UI\\LL\\슬라이드%d.png"), 9);
                g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_ctrGUI_LL2, strImage);
            }
            if (g_pMainDlg->m_nThread2_LL == 3 && g_pMainDlg->m_ctrLL3.GetWindowInt() == 0)
            {
                strImage.Format(_T("UI\\LL\\슬라이드%d.png"), 9);
                g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_ctrGUI_LL3, strImage);
            }
            if (g_pMainDlg->m_nThread2_LL == 4 && g_pMainDlg->m_ctrLL4.GetWindowInt() == 0)
            {
                strImage.Format(_T("UI\\LL\\슬라이드%d.png"), 9);
                g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_ctrGUI_LL4, strImage);
            }
            nTM_cnt = g_pMainDlg->m_ctrTM.GetWindowInt();
            //PLACE : VAC ROBOT -> PM
            Sleep(g_pMainDlg->m_nRotate / g_pMainDlg->m_nSpeed);
            Sleep(g_pMainDlg->m_nVAC_Place / g_pMainDlg->m_nSpeed);
            if (g_pMainDlg->m_nThread2_LL == 1 && g_pMainDlg->m_ctrLL1.GetWindowInt() == 0)
            {
                strImage.Format(_T("UI\\LL\\슬라이드%d.png"), 7);
                g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_ctrGUI_LL1, strImage);
            }
            if (g_pMainDlg->m_nThread2_LL == 2 && g_pMainDlg->m_ctrLL2.GetWindowInt() == 0)
            {
                strImage.Format(_T("UI\\LL\\슬라이드%d.png"), 7);
                g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_ctrGUI_LL2, strImage);
            }
            if (g_pMainDlg->m_nThread2_LL == 3 && g_pMainDlg->m_ctrLL3.GetWindowInt() == 0)
            {
                strImage.Format(_T("UI\\LL\\슬라이드%d.png"), 7);
                g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_ctrGUI_LL3, strImage);
            }
            if (g_pMainDlg->m_nThread2_LL == 4 && g_pMainDlg->m_ctrLL4.GetWindowInt() == 0)
            {
                strImage.Format(_T("UI\\LL\\슬라이드%d.png"), 7);
                g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_ctrGUI_LL4, strImage);
            }
            if ((g_pMainDlg->m_ctrPM1.GetWindowInt() < _ttoi(g_pMainDlg->m_strPMSlotCnt)) && _ttoi(g_pMainDlg->m_strPMModuleCnt) >= 1)
            {

                {
                    strImage.Format(_T("UI\\PM_Left\\슬라이드2.png"));
                    g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Ctrl_Gui_PM1, strImage);
                }
                for (int i = 5; i <= 7; i++)
                {
                    strImage.Format(_T("UI\\TM(Quad)\\슬라이드%d.png"), i);
                    g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Gui_TM, strImage);
                }

                {
                    strImage.Format(_T("UI\\PM_Left\\슬라이드3.png"));
                    g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Ctrl_Gui_PM1, strImage);
                }
            }
            else if ((g_pMainDlg->m_ctrPM2.GetWindowInt() < _ttoi(g_pMainDlg->m_strPMSlotCnt)) && _ttoi(g_pMainDlg->m_strPMModuleCnt) >= 2)
            {

                {
                    strImage.Format(_T("UI\\PM_Left\\슬라이드2.png"));
                    g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Ctrl_Gui_PM2, strImage);
                }
                for (int i = 8; i <= 10; i++)
                {
                    strImage.Format(_T("UI\\TM(Quad)\\슬라이드%d.png"), i);
                    g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Gui_TM, strImage);
                }

                {
                    strImage.Format(_T("UI\\PM_Left\\슬라이드3.png"));
                    g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Ctrl_Gui_PM2, strImage);
                }
            }

            else if ((g_pMainDlg->m_ctrPM3.GetWindowInt() < _ttoi(g_pMainDlg->m_strPMSlotCnt)) && _ttoi(g_pMainDlg->m_strPMModuleCnt) >= 3)
            {

                {
                    strImage.Format(_T("UI\\PM_Upper\\슬라이드2.png"));
                    g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Ctrl_Gui_PM3, strImage);
                }
                for (int i = 11; i <= 13; i++)
                {
                    strImage.Format(_T("UI\\TM(Quad)\\슬라이드%d.png"), i);
                    g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Gui_TM, strImage);
                }

                {
                    strImage.Format(_T("UI\\PM_Upper\\슬라이드3.png"));
                    g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Ctrl_Gui_PM3, strImage);
                }
            }

            else if ((g_pMainDlg->m_ctrPM4.GetWindowInt() < _ttoi(g_pMainDlg->m_strPMSlotCnt)) && _ttoi(g_pMainDlg->m_strPMModuleCnt) >= 4)
            {

                {
                    strImage.Format(_T("UI\\PM_Upper\\슬라이드2.png"));
                    g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Ctrl_Gui_PM4, strImage);
                }
                for (int i = 14; i <= 16; i++)
                {
                    strImage.Format(_T("UI\\TM(Quad)\\슬라이드%d.png"), i);
                    g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Gui_TM, strImage);
                }

                {
                    strImage.Format(_T("UI\\PM_Upper\\슬라이드3.png"));
                    g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Ctrl_Gui_PM4, strImage);
                }
            }

            else if ((g_pMainDlg->m_ctrPM5.GetWindowInt() < _ttoi(g_pMainDlg->m_strPMSlotCnt)) && _ttoi(g_pMainDlg->m_strPMModuleCnt) >= 5)
            {

                {
                    strImage.Format(_T("UI\\PM_Right\\슬라이드2.png"));
                    g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Ctrl_Gui_PM5, strImage);
                }
                for (int i = 17; i <= 19; i++)
                {
                    strImage.Format(_T("UI\\TM(Quad)\\슬라이드%d.png"), i);
                    g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Gui_TM, strImage);
                }

                {
                    strImage.Format(_T("UI\\PM_Right\\슬라이드3.png"));
                    g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Ctrl_Gui_PM5, strImage);
                }
            }

            else if ((g_pMainDlg->m_ctrPM6.GetWindowInt() < _ttoi(g_pMainDlg->m_strPMSlotCnt)) && _ttoi(g_pMainDlg->m_strPMModuleCnt) >= 6)
            {

                {
                    strImage.Format(_T("UI\\PM_Right\\슬라이드2.png"));
                    g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Ctrl_Gui_PM6, strImage);
                }
                for (int i = 20; i <= 22; i++)
                {
                    strImage.Format(_T("UI\\TM(Quad)\\슬라이드%d.png"), i);
                    g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Gui_TM, strImage);
                }

                {
                    strImage.Format(_T("UI\\PM_Right\\슬라이드3.png"));
                    g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Ctrl_Gui_PM6, strImage);
                }
            }
            for (int i = nPM_cnt;; i++)
            {

                if (g_pMainDlg->m_strVacArmCnt == _T("4"))
                {
                    if (i % 2 == 0)
                    {
                        g_pMainDlg->m_ctrTM.SetWindowInt(nTM_cnt);
                        if ((g_pMainDlg->m_ctrPM1.GetWindowInt() < _ttoi(g_pMainDlg->m_strPMSlotCnt)) && _ttoi(g_pMainDlg->m_strPMModuleCnt) >= 1)
                            g_pMainDlg->m_ctrPM1.SetWindowInt(i);

                        else if ((g_pMainDlg->m_ctrPM2.GetWindowInt() < _ttoi(g_pMainDlg->m_strPMSlotCnt)) && _ttoi(g_pMainDlg->m_strPMModuleCnt) >= 2)
                            g_pMainDlg->m_ctrPM2.SetWindowInt(i);

                        else if ((g_pMainDlg->m_ctrPM3.GetWindowInt() < _ttoi(g_pMainDlg->m_strPMSlotCnt)) && _ttoi(g_pMainDlg->m_strPMModuleCnt) >= 3)
                            g_pMainDlg->m_ctrPM3.SetWindowInt(i);

                        else if ((g_pMainDlg->m_ctrPM4.GetWindowInt() < _ttoi(g_pMainDlg->m_strPMSlotCnt)) && _ttoi(g_pMainDlg->m_strPMModuleCnt) >= 4)
                            g_pMainDlg->m_ctrPM4.SetWindowInt(i);

                        else if ((g_pMainDlg->m_ctrPM5.GetWindowInt() < _ttoi(g_pMainDlg->m_strPMSlotCnt)) && _ttoi(g_pMainDlg->m_strPMModuleCnt) >= 5)
                            g_pMainDlg->m_ctrPM5.SetWindowInt(i);

                        else if ((g_pMainDlg->m_ctrPM6.GetWindowInt() < _ttoi(g_pMainDlg->m_strPMSlotCnt)) && _ttoi(g_pMainDlg->m_strPMModuleCnt) >= 6)
                            g_pMainDlg->m_ctrPM6.SetWindowInt(i);
                    }
                }
                else if (g_pMainDlg->m_strVacArmCnt == _T("2"))
                {
                    g_pMainDlg->m_ctrTM.SetWindowInt(nTM_cnt);
                    if ((g_pMainDlg->m_ctrPM1.GetWindowInt() < _ttoi(g_pMainDlg->m_strPMSlotCnt)) && _ttoi(g_pMainDlg->m_strPMModuleCnt) >= 1)
                        g_pMainDlg->m_ctrPM1.SetWindowInt(i);

                    else if ((g_pMainDlg->m_ctrPM2.GetWindowInt() < _ttoi(g_pMainDlg->m_strPMSlotCnt)) && _ttoi(g_pMainDlg->m_strPMModuleCnt) >= 2)
                        g_pMainDlg->m_ctrPM2.SetWindowInt(i);

                    else if ((g_pMainDlg->m_ctrPM3.GetWindowInt() < _ttoi(g_pMainDlg->m_strPMSlotCnt)) && _ttoi(g_pMainDlg->m_strPMModuleCnt) >= 3)
                        g_pMainDlg->m_ctrPM3.SetWindowInt(i);

                    else if ((g_pMainDlg->m_ctrPM4.GetWindowInt() < _ttoi(g_pMainDlg->m_strPMSlotCnt)) && _ttoi(g_pMainDlg->m_strPMModuleCnt) >= 4)
                        g_pMainDlg->m_ctrPM4.SetWindowInt(i);

                    else if ((g_pMainDlg->m_ctrPM5.GetWindowInt() < _ttoi(g_pMainDlg->m_strPMSlotCnt)) && _ttoi(g_pMainDlg->m_strPMModuleCnt) >= 5)
                        g_pMainDlg->m_ctrPM5.SetWindowInt(i);

                    else if ((g_pMainDlg->m_ctrPM6.GetWindowInt() < _ttoi(g_pMainDlg->m_strPMSlotCnt)) && _ttoi(g_pMainDlg->m_strPMModuleCnt) >= 6)
                        g_pMainDlg->m_ctrPM6.SetWindowInt(i);
                }
                if (nTM_cnt == 0) break;  //TM(VAC ROBOT)에 남아있는 wafer가 없다면 종료
                if (i == _ttoi(g_pMainDlg->m_strPMSlotCnt)) break;  //PM이 가득 찼다면 종료

                nTM_cnt--;
            }
            if ((g_pMainDlg->m_ctrPM1.GetWindowInt() == _ttoi(g_pMainDlg->m_strPMSlotCnt)) && _ttoi(g_pMainDlg->m_strPMModuleCnt) >= 1 && g_pMainDlg->m_nPM_Thread2 == 0)
            {
                g_pMainDlg->m_nPM_Thread2++;
                g_pMainDlg->m_nPM_Processing++;
                g_hThread_PM[0] = (CreateThread(NULL, 0, PM, 0, 0, 0));
            }
            else if ((g_pMainDlg->m_ctrPM2.GetWindowInt() == _ttoi(g_pMainDlg->m_strPMSlotCnt)) && _ttoi(g_pMainDlg->m_strPMModuleCnt) >= 2 && g_pMainDlg->m_nPM_Thread2 == 1)
            {
                g_pMainDlg->m_nPM_Thread2++;
                g_pMainDlg->m_nPM_Processing++;
                g_hThread_PM[1] = (CreateThread(NULL, 0, PM, 0, 0, 0));
            }
            else if ((g_pMainDlg->m_ctrPM3.GetWindowInt() == _ttoi(g_pMainDlg->m_strPMSlotCnt)) && _ttoi(g_pMainDlg->m_strPMModuleCnt) >= 3 && g_pMainDlg->m_nPM_Thread2 == 2)
            {
                g_pMainDlg->m_nPM_Thread2++;
                g_pMainDlg->m_nPM_Processing++;
                g_hThread_PM[2] = (CreateThread(NULL, 0, PM, 0, 0, 0));
            }
            else if ((g_pMainDlg->m_ctrPM4.GetWindowInt() == _ttoi(g_pMainDlg->m_strPMSlotCnt)) && _ttoi(g_pMainDlg->m_strPMModuleCnt) >= 4 && g_pMainDlg->m_nPM_Thread2 == 3)
            {
                g_pMainDlg->m_nPM_Thread2++;
                g_pMainDlg->m_nPM_Processing++;
                g_hThread_PM[3] = (CreateThread(NULL, 0, PM, 0, 0, 0));
            }
            else if ((g_pMainDlg->m_ctrPM5.GetWindowInt() == _ttoi(g_pMainDlg->m_strPMSlotCnt)) && _ttoi(g_pMainDlg->m_strPMModuleCnt) >= 5 && g_pMainDlg->m_nPM_Thread2 == 4)
            {
                g_pMainDlg->m_nPM_Thread2++;
                g_pMainDlg->m_nPM_Processing++;
                g_hThread_PM[4] = (CreateThread(NULL, 0, PM, 0, 0, 0));
            }
            else if ((g_pMainDlg->m_ctrPM6.GetWindowInt() == _ttoi(g_pMainDlg->m_strPMSlotCnt)) && _ttoi(g_pMainDlg->m_strPMModuleCnt) >= 6 && g_pMainDlg->m_nPM_Thread2 == 5)
            {
                g_pMainDlg->m_nPM_Thread2++;
                g_pMainDlg->m_nPM_Processing++;
                g_hThread_PM[5] = (CreateThread(NULL, 0, PM, 0, 0, 0));
            }
        }
    }

    nLPM_cnt = g_pMainDlg->m_ctrLPM.GetWindowInt();
    int PM_Count = g_pMainDlg->m_ctrPM1.GetWindowInt() +
        g_pMainDlg->m_ctrPM2.GetWindowInt() +
        g_pMainDlg->m_ctrPM3.GetWindowInt() +
        g_pMainDlg->m_ctrPM4.GetWindowInt() +
        g_pMainDlg->m_ctrPM5.GetWindowInt() +
        g_pMainDlg->m_ctrPM6.GetWindowInt();
    int nPM_MAX = _ttoi(g_pMainDlg->m_strPMSlotCnt) * _ttoi(g_pMainDlg->m_strPMModuleCnt);
    SetEvent(g_hEventLL_Modul_one_Thread1and2);

    return 0;
}

//TM Post-Process(TM-OUT)
DWORD WINAPI Thread_3_PM2LL(LPVOID p)
{
    int nTM_cnt;
    int nLL_cnt;
    int nPM_cnt;
    int LL_Count = 0;
    int PM_Count = 0;
    CString strImage;
    //PICK & PLACE (PM1 -> VAC ROBOT -> LL)
    while (true)
    {
        if (g_pMainDlg->m_nThread3_PM[0] == 1)
            nPM_cnt = g_pMainDlg->m_ctrPM1.GetWindowInt();

        if (g_pMainDlg->m_nThread3_PM[0] == 2)
            nPM_cnt = g_pMainDlg->m_ctrPM2.GetWindowInt();

        if (g_pMainDlg->m_nThread3_PM[0] == 3)
            nPM_cnt = g_pMainDlg->m_ctrPM3.GetWindowInt();

        if (g_pMainDlg->m_nThread3_PM[0] == 4)
            nPM_cnt = g_pMainDlg->m_ctrPM4.GetWindowInt();

        if (g_pMainDlg->m_nThread3_PM[0] == 5)
            nPM_cnt = g_pMainDlg->m_ctrPM5.GetWindowInt();

        if (g_pMainDlg->m_nThread3_PM[0] == 6)
            nPM_cnt = g_pMainDlg->m_ctrPM6.GetWindowInt();

        nTM_cnt = g_pMainDlg->m_ctrTM.GetWindowInt();
        if (nPM_cnt == 0) break;  //PM에 남아있는 wafer가 없다면 종료
        if (g_pMainDlg->m_nPM_Processing == _ttoi(g_pMainDlg->m_strPMModuleCnt))
        {
            ResetEvent(g_hEvent_PM_MAX);
            WaitForSingleObject(g_hEvent_PM_MAX, INFINITE);
            g_pMainDlg->m_nThread_Time_Error = 0;
            g_pMainDlg->m_nThread4_LL = 1;
        }
        //PICK : PM1 -> VAC ROBOT
        Sleep(g_pMainDlg->m_nRotate / g_pMainDlg->m_nSpeed);
        Sleep(g_pMainDlg->m_nPM_Slot_Valve_Open / g_pMainDlg->m_nSpeed);
        Sleep(g_pMainDlg->m_nVAC_Pick / g_pMainDlg->m_nSpeed);
        for (int i = 23; i <= 27; i++)
        {
            strImage.Format(_T("UI\\TM(Quad)\\슬라이드%d.png"), i);
            g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Gui_TM, strImage);
        }
        for (int i = nTM_cnt; ; i++)
        {
            if (g_pMainDlg->m_strVacArmCnt == _T("4"))
            {
                if (i % 2 == 0)
                {
                    g_pMainDlg->m_ctrTM.SetWindowInt(i);
                    if (g_pMainDlg->m_ctrPM1.GetWindowInt() != 0 && g_pMainDlg->m_nThread3_PM[0] == 1)
                        g_pMainDlg->m_ctrPM1.SetWindowInt(nPM_cnt);

                    else if (g_pMainDlg->m_ctrPM2.GetWindowInt() != 0 && g_pMainDlg->m_nThread3_PM[0] == 2)
                        g_pMainDlg->m_ctrPM2.SetWindowInt(nPM_cnt);

                    else if (g_pMainDlg->m_ctrPM3.GetWindowInt() != 0 && g_pMainDlg->m_nThread3_PM[0] == 3)
                        g_pMainDlg->m_ctrPM3.SetWindowInt(nPM_cnt);

                    else if (g_pMainDlg->m_ctrPM4.GetWindowInt() != 0 && g_pMainDlg->m_nThread3_PM[0] == 4)
                        g_pMainDlg->m_ctrPM4.SetWindowInt(nPM_cnt);

                    else if (g_pMainDlg->m_ctrPM5.GetWindowInt() != 0 && g_pMainDlg->m_nThread3_PM[0] == 5)
                        g_pMainDlg->m_ctrPM5.SetWindowInt(nPM_cnt);

                    else if (g_pMainDlg->m_ctrPM6.GetWindowInt() != 0 && g_pMainDlg->m_nThread3_PM[0] == 6)
                        g_pMainDlg->m_ctrPM6.SetWindowInt(nPM_cnt);
                }
            }
            else if (g_pMainDlg->m_strVacArmCnt == _T("2"))
            {
                g_pMainDlg->m_ctrTM.SetWindowInt(i);
                if (g_pMainDlg->m_ctrPM1.GetWindowInt() != 0 && g_pMainDlg->m_nThread3_PM[0] == 1)
                    g_pMainDlg->m_ctrPM1.SetWindowInt(nPM_cnt);

                else if (g_pMainDlg->m_ctrPM2.GetWindowInt() != 0 && g_pMainDlg->m_nThread3_PM[0] == 2)
                    g_pMainDlg->m_ctrPM2.SetWindowInt(nPM_cnt);

                else if (g_pMainDlg->m_ctrPM3.GetWindowInt() != 0 && g_pMainDlg->m_nThread3_PM[0] == 3)
                    g_pMainDlg->m_ctrPM3.SetWindowInt(nPM_cnt);

                else if (g_pMainDlg->m_ctrPM4.GetWindowInt() != 0 && g_pMainDlg->m_nThread3_PM[0] == 4)
                    g_pMainDlg->m_ctrPM4.SetWindowInt(nPM_cnt);

                else if (g_pMainDlg->m_ctrPM5.GetWindowInt() != 0 && g_pMainDlg->m_nThread3_PM[0] == 5)
                    g_pMainDlg->m_ctrPM5.SetWindowInt(nPM_cnt);

                else if (g_pMainDlg->m_ctrPM6.GetWindowInt() != 0 && g_pMainDlg->m_nThread3_PM[0] == 6)
                    g_pMainDlg->m_ctrPM6.SetWindowInt(nPM_cnt);
            }
            //현재 LL에 있는 wafer의 수와 VAC ROBOT이 들고 있는 wafer 갯수의 합이
            //LL의 최대치(MAX:24장)와 같다면 PM에서 더 꺼내지 말고 대기
            //if (nLL_cnt + i == g_pMainDlg->m_nLLMAX) break;
            if (nPM_cnt == 0) break;  //PM에 남아있는 wafer가 없다면 종료

            nPM_cnt--;

            if (i == _ttoi(g_pMainDlg->m_strVacArmCnt) / 2) break;  //TM(VAC ROBOT)이 Dual Arm일 땐 wafer 2장,
            //Quad Arm일 때 wafer를 4장 들고 있다면 대기
        }
        nTM_cnt = g_pMainDlg->m_ctrTM.GetWindowInt();
        if (g_pMainDlg->m_nThread3_LL == 1)
            nLL_cnt = g_pMainDlg->m_ctrLL1.GetWindowInt();

        if (g_pMainDlg->m_nThread3_LL == 2)
            nLL_cnt = g_pMainDlg->m_ctrLL2.GetWindowInt();

        if (g_pMainDlg->m_nThread3_LL == 3)
            nLL_cnt = g_pMainDlg->m_ctrLL3.GetWindowInt();

        if (g_pMainDlg->m_nThread3_LL == 4)
            nLL_cnt = g_pMainDlg->m_ctrLL4.GetWindowInt();

        //LL->VAC
        Sleep(g_pMainDlg->m_nRotate / g_pMainDlg->m_nSpeed);
        Sleep(g_pMainDlg->m_nLL_Slot_Valve_Open / g_pMainDlg->m_nSpeed);
        Sleep(g_pMainDlg->m_nVAC_Pick / g_pMainDlg->m_nSpeed);

        for (int i = 27; i <= 30; i++)
        {
            strImage.Format(_T("UI\\TM(Quad)\\슬라이드%d.png"), i);
            g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Gui_TM, strImage);
        }
        if (g_pMainDlg->m_nThread3_LL == 1)
        {
            nLL_cnt = g_pMainDlg->m_ctrLL1.GetWindowInt();
            strImage.Format(_T("UI\\LL\\슬라이드%d.png"), 2);
            g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_ctrGUI_LL1, strImage);
        }
        if (g_pMainDlg->m_nThread3_LL == 2)
        {
            nLL_cnt = g_pMainDlg->m_ctrLL2.GetWindowInt();
            strImage.Format(_T("UI\\LL\\슬라이드%d.png"), 2);
            g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_ctrGUI_LL2, strImage);
        }
        if (g_pMainDlg->m_nThread3_LL == 3)
        {
            nLL_cnt = g_pMainDlg->m_ctrLL3.GetWindowInt();
            strImage.Format(_T("UI\\LL\\슬라이드%d.png"), 2);
            g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_ctrGUI_LL3, strImage);
        }
        if (g_pMainDlg->m_nThread3_LL == 4)
        {
            nLL_cnt = g_pMainDlg->m_ctrLL4.GetWindowInt();
            strImage.Format(_T("UI\\LL\\슬라이드%d.png"), 2);
            g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_ctrGUI_LL4, strImage);
        }
        if (g_pMainDlg->m_nThread3_LL == 1 && g_pMainDlg->m_ctrLL1.GetWindowInt() == 0)
        {
            nLL_cnt = g_pMainDlg->m_ctrLL1.GetWindowInt();
            strImage.Format(_T("UI\\LL\\슬라이드%d.png"), 9);
            g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_ctrGUI_LL1, strImage);
        }
        if (g_pMainDlg->m_nThread3_LL == 2 && g_pMainDlg->m_ctrLL2.GetWindowInt() == 0)
        {
            nLL_cnt = g_pMainDlg->m_ctrLL2.GetWindowInt();
            strImage.Format(_T("UI\\LL\\슬라이드%d.png"), 9);
            g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_ctrGUI_LL2, strImage);
        }
        if (g_pMainDlg->m_nThread3_LL == 3 && g_pMainDlg->m_ctrLL3.GetWindowInt() == 0)
        {
            nLL_cnt = g_pMainDlg->m_ctrLL3.GetWindowInt();
            strImage.Format(_T("UI\\LL\\슬라이드%d.png"), 9);
            g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_ctrGUI_LL3, strImage);
        }
        if (g_pMainDlg->m_nThread3_LL == 4 && g_pMainDlg->m_ctrLL4.GetWindowInt() == 0)
        {
            nLL_cnt = g_pMainDlg->m_ctrLL4.GetWindowInt();
            strImage.Format(_T("UI\\LL\\슬라이드%d.png"), 9);
            g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_ctrGUI_LL4, strImage);
        }
        for (int i = nTM_cnt;; i++)
        {
            if (nPM_cnt == _ttoi(g_pMainDlg->m_strPMSlotCnt)) break;  //PM이 가득 찼다면 종료
            if (g_pMainDlg->m_strVacArmCnt == _T("4"))
            {
                if (i % 2 == 0)
                {
                    g_pMainDlg->m_ctrTM.SetWindowInt(i);
                    if (g_pMainDlg->m_nThread3_LL == 1)
                        g_pMainDlg->m_ctrLL1.SetWindowInt(nLL_cnt);
                    if (g_pMainDlg->m_nThread3_LL == 2)
                        g_pMainDlg->m_ctrLL2.SetWindowInt(nLL_cnt);
                    if (g_pMainDlg->m_nThread3_LL == 3)
                        g_pMainDlg->m_ctrLL3.SetWindowInt(nLL_cnt);
                    if (g_pMainDlg->m_nThread3_LL == 4)
                        g_pMainDlg->m_ctrLL4.SetWindowInt(nLL_cnt);
                    g_pMainDlg->InvalidateRect(g_CRtemp, false);
                }
            }
            else if (g_pMainDlg->m_strVacArmCnt == _T("2"))
            {
                g_pMainDlg->m_ctrTM.SetWindowInt(i);
                if (g_pMainDlg->m_nThread3_LL == 1)
                    g_pMainDlg->m_ctrLL1.SetWindowInt(nLL_cnt);
                if (g_pMainDlg->m_nThread3_LL == 2)
                    g_pMainDlg->m_ctrLL2.SetWindowInt(nLL_cnt);
                if (g_pMainDlg->m_nThread3_LL == 3)
                    g_pMainDlg->m_ctrLL3.SetWindowInt(nLL_cnt);
                if (g_pMainDlg->m_nThread3_LL == 4)
                    g_pMainDlg->m_ctrLL4.SetWindowInt(nLL_cnt);
                g_pMainDlg->InvalidateRect(g_CRtemp, false);
            }
            if (nLL_cnt == 0) break;  //LL에 남아있는 wafer가 없다면 종료

            nLL_cnt--;
            if (i == _ttoi(g_pMainDlg->m_strVacArmCnt)) break;  //TM(VAC ROBOT)이 Dual Arm일 땐 wafer 2장,
            //Quad Arm일 때 wafer를 4장 들고 있다면 대기
        }

        nTM_cnt = g_pMainDlg->m_ctrTM.GetWindowInt();
        

        for (int i = 1; ; i++)
        {
            nTM_cnt = g_pMainDlg->m_ctrTM.GetWindowInt();
            if (g_pMainDlg->m_nThread3_LL == 1)
            {
                nLL_cnt = g_pMainDlg->m_ctrLL1.GetWindowInt();
            }
            if (g_pMainDlg->m_nThread3_LL == 2)
            {
                nLL_cnt = g_pMainDlg->m_ctrLL2.GetWindowInt();
            }
            if (g_pMainDlg->m_nThread3_LL == 3)
            {
                nLL_cnt = g_pMainDlg->m_ctrLL3.GetWindowInt();
            }
            if (g_pMainDlg->m_nThread3_LL == 4)
            {
                nLL_cnt = g_pMainDlg->m_ctrLL4.GetWindowInt();
            }
            //PLACE : VAC ROBOT -> LL
            Sleep(g_pMainDlg->m_nRotate / g_pMainDlg->m_nSpeed);
            Sleep(g_pMainDlg->m_nVAC_Place / g_pMainDlg->m_nSpeed);
            for (int i = 30; i <= 32; i++)
            {
                strImage.Format(_T("UI\\TM(Quad)\\슬라이드%d.png"), i);
                g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Gui_TM, strImage);
            }
            for (int i = nLL_cnt;; i++)
            {
                if (g_pMainDlg->m_strVacArmCnt == _T("4"))
                {
                    if (i % 2 == 0)
                    {
                        g_pMainDlg->m_ctrTM.SetWindowInt(nTM_cnt);
                        if (g_pMainDlg->m_nThread3_LL == 1)
                            g_pMainDlg->m_ctrLL1.SetWindowInt(i);
                        if (g_pMainDlg->m_nThread3_LL == 2)
                            g_pMainDlg->m_ctrLL2.SetWindowInt(i);
                        if (g_pMainDlg->m_nThread3_LL == 3)
                            g_pMainDlg->m_ctrLL3.SetWindowInt(i);
                        if (g_pMainDlg->m_nThread3_LL == 4)
                            g_pMainDlg->m_ctrLL4.SetWindowInt(i);
                        g_pMainDlg->InvalidateRect(g_CRtemp, false);
                    }
                }
                else if (g_pMainDlg->m_strVacArmCnt == _T("2"))
                {
                    g_pMainDlg->m_ctrTM.SetWindowInt(nTM_cnt);
                    if (g_pMainDlg->m_nThread3_LL == 1)
                        g_pMainDlg->m_ctrLL1.SetWindowInt(i);
                    if (g_pMainDlg->m_nThread3_LL == 2)
                        g_pMainDlg->m_ctrLL2.SetWindowInt(i);
                    if (g_pMainDlg->m_nThread3_LL == 3)
                        g_pMainDlg->m_ctrLL3.SetWindowInt(i);
                    if (g_pMainDlg->m_nThread3_LL == 4)
                        g_pMainDlg->m_ctrLL4.SetWindowInt(i);
                    g_pMainDlg->InvalidateRect(g_CRtemp, false);
                }
                if (nTM_cnt == _ttoi(g_pMainDlg->m_strVacArmCnt) / 2) break;  //TM(VAC ROBOT)에 남아있는 wafer가 없다면 종료
                LL_Count++;
                g_pMainDlg->m_nWafer_Process[g_pMainDlg->m_nThread3_LL - 1] = LL_Count;
                nTM_cnt--;
            }
            if (g_pMainDlg->m_nThread3_LL == 1)
            {
                strImage.Format(_T("UI\\LL\\슬라이드%d.png"), 5);
                g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_ctrGUI_LL1, strImage);
            }
            if (g_pMainDlg->m_nThread3_LL == 2)
            {
                strImage.Format(_T("UI\\LL\\슬라이드%d.png"), 5);
                g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_ctrGUI_LL2, strImage);
            }
            if (g_pMainDlg->m_nThread3_LL == 3)
            {
                strImage.Format(_T("UI\\LL\\슬라이드%d.png"), 5);
                g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_ctrGUI_LL3, strImage);
            }
            if (g_pMainDlg->m_nThread3_LL == 4)
            {
                strImage.Format(_T("UI\\LL\\슬라이드%d.png"), 5);
                g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_ctrGUI_LL4, strImage);
            }
            g_pMainDlg->InvalidateRect(g_CRtemp, false);
            if (LL_Count == _ttoi(g_pMainDlg->m_strLLSlotCnt))
            {
                Sleep(g_pMainDlg->m_nLL_Slot_Valve_Close / g_pMainDlg->m_nSpeed);
                LL_Count = 0;
                g_pMainDlg->m_nThread3_LL++;
                g_pMainDlg->m_nLL_Thread = g_pMainDlg->m_nThread3_LL;
                g_pMainDlg->m_nThread_Time_Error++;
                g_hThread_LL[g_pMainDlg->m_nLL_Thread - 2] = (CreateThread(NULL, 0, LL, 0, 0, 0));
                Sleep(g_pMainDlg->m_nLL_Slot_Valve_Open / g_pMainDlg->m_nSpeed);
            }
            if (g_pMainDlg->m_nThread_Time_Error == _ttoi(g_pMainDlg->m_strLLModuleCnt))
            {
                ResetEvent(g_hEventThread_Time_Error);
                WaitForSingleObject(g_hEventThread_Time_Error, INFINITE);
            }
            if (g_pMainDlg->m_nThread3_LL == _ttoi(g_pMainDlg->m_strLLModuleCnt) + 1)
                g_pMainDlg->m_nThread3_LL = 1;

            nTM_cnt = g_pMainDlg->m_ctrTM.GetWindowInt();
            if (g_pMainDlg->m_nThread3_LL == 1)
                nLL_cnt = g_pMainDlg->m_ctrLL1.GetWindowInt();
            if (g_pMainDlg->m_nThread3_LL == 2)
                nLL_cnt = g_pMainDlg->m_ctrLL2.GetWindowInt();
            if (g_pMainDlg->m_nThread3_LL == 3)
                nLL_cnt = g_pMainDlg->m_ctrLL3.GetWindowInt();
            if (g_pMainDlg->m_nThread3_LL == 4)
                nLL_cnt = g_pMainDlg->m_ctrLL4.GetWindowInt();
            //LL->TM
            Sleep(g_pMainDlg->m_nRotate / g_pMainDlg->m_nSpeed);
            Sleep(g_pMainDlg->m_nVAC_Pick / g_pMainDlg->m_nSpeed);
            for (int i = 32; i <= 35; i++)
            {
                strImage.Format(_T("UI\\TM(Quad)\\슬라이드%d.png"), i);
                g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Gui_TM, strImage);
            }
            
            for (int i = nTM_cnt;; i++)
            {
                if (nPM_cnt == _ttoi(g_pMainDlg->m_strPMSlotCnt)) break;  //PM이 가득 찼다면 종료
                if (g_pMainDlg->m_strVacArmCnt == _T("4"))
                {
                    if (i % 2 == 0)
                    {
                        g_pMainDlg->m_ctrTM.SetWindowInt(i);
                        if (g_pMainDlg->m_nThread3_LL == 1)
                            g_pMainDlg->m_ctrLL1.SetWindowInt(nLL_cnt);
                        if (g_pMainDlg->m_nThread3_LL == 2)
                            g_pMainDlg->m_ctrLL2.SetWindowInt(nLL_cnt);
                        if (g_pMainDlg->m_nThread3_LL == 3)
                            g_pMainDlg->m_ctrLL3.SetWindowInt(nLL_cnt);
                        if (g_pMainDlg->m_nThread3_LL == 4)
                            g_pMainDlg->m_ctrLL4.SetWindowInt(nLL_cnt);
                        g_pMainDlg->InvalidateRect(g_CRtemp, false);
                    }
                }
                else if (g_pMainDlg->m_strVacArmCnt == _T("2"))
                {
                    g_pMainDlg->m_ctrTM.SetWindowInt(i);
                    if (g_pMainDlg->m_nThread3_LL == 1)
                        g_pMainDlg->m_ctrLL1.SetWindowInt(nLL_cnt);
                    if (g_pMainDlg->m_nThread3_LL == 2)
                        g_pMainDlg->m_ctrLL2.SetWindowInt(nLL_cnt);
                    if (g_pMainDlg->m_nThread3_LL == 3)
                        g_pMainDlg->m_ctrLL3.SetWindowInt(nLL_cnt);
                    if (g_pMainDlg->m_nThread3_LL == 4)
                        g_pMainDlg->m_ctrLL4.SetWindowInt(nLL_cnt);
                    g_pMainDlg->InvalidateRect(g_CRtemp, false);
                }
                if (nLL_cnt == 0) break;  //LL에 남아있는 wafer가 없다면 종료

                nLL_cnt--;

                if (i == _ttoi(g_pMainDlg->m_strVacArmCnt)) break;  //TM(VAC ROBOT)이 Dual Arm일 땐 wafer 2장,
                //Quad Arm일 때 wafer를 4장 들고 있다면 대기
            }

            if (g_pMainDlg->m_nThread3_LL == 1 && g_pMainDlg->m_ctrLL1.GetWindowInt() == 0)
            {
                nLL_cnt = g_pMainDlg->m_ctrLL1.GetWindowInt();
                strImage.Format(_T("UI\\LL\\슬라이드%d.png"), 9);
                g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_ctrGUI_LL1, strImage);
            }
            if (g_pMainDlg->m_nThread3_LL == 2 && g_pMainDlg->m_ctrLL2.GetWindowInt() == 0)
            {
                nLL_cnt = g_pMainDlg->m_ctrLL2.GetWindowInt();
                strImage.Format(_T("UI\\LL\\슬라이드%d.png"), 9);
                g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_ctrGUI_LL2, strImage);
            }
            if (g_pMainDlg->m_nThread3_LL == 3 && g_pMainDlg->m_ctrLL3.GetWindowInt() == 0)
            {
                nLL_cnt = g_pMainDlg->m_ctrLL3.GetWindowInt();
                strImage.Format(_T("UI\\LL\\슬라이드%d.png"), 9);
                g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_ctrGUI_LL3, strImage);
            }
            if (g_pMainDlg->m_nThread3_LL == 4 && g_pMainDlg->m_ctrLL4.GetWindowInt() == 0)
            {
                nLL_cnt = g_pMainDlg->m_ctrLL4.GetWindowInt();
                strImage.Format(_T("UI\\LL\\슬라이드%d.png"), 9);
                g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_ctrGUI_LL4, strImage);
            }
            nTM_cnt = g_pMainDlg->m_ctrTM.GetWindowInt();
            if (g_pMainDlg->m_nThread3_PM[0] == 1 && _ttoi(g_pMainDlg->m_strPMModuleCnt) >= 1)
            {
                g_pMainDlg->m_nPM_Thread3 = 1;
                nPM_cnt = g_pMainDlg->m_ctrPM1.GetWindowInt();
            }
            if (g_pMainDlg->m_nThread3_PM[0] == 2 && _ttoi(g_pMainDlg->m_strPMModuleCnt) >= 2)
            {
                g_pMainDlg->m_nPM_Thread3 = 2;
                nPM_cnt = g_pMainDlg->m_ctrPM2.GetWindowInt();
            }

            if (g_pMainDlg->m_nThread3_PM[0] == 3 && _ttoi(g_pMainDlg->m_strPMModuleCnt) >= 3)
            {
                g_pMainDlg->m_nPM_Thread3 = 3;
                nPM_cnt = g_pMainDlg->m_ctrPM3.GetWindowInt();
            }

            if (g_pMainDlg->m_nThread3_PM[0] == 4 && _ttoi(g_pMainDlg->m_strPMModuleCnt) >= 4)
            {
                g_pMainDlg->m_nPM_Thread3 = 4;
                nPM_cnt = g_pMainDlg->m_ctrPM4.GetWindowInt();
            }

            if (g_pMainDlg->m_nThread3_PM[0] == 5 && _ttoi(g_pMainDlg->m_strPMModuleCnt) >= 5)
            {
                g_pMainDlg->m_nPM_Thread3 = 5;
                nPM_cnt = g_pMainDlg->m_ctrPM5.GetWindowInt();
            }

            if (g_pMainDlg->m_nThread3_PM[0] == 6 && _ttoi(g_pMainDlg->m_strPMModuleCnt) >= 6)
            {
                g_pMainDlg->m_nPM_Thread3 = 6;
                nPM_cnt = g_pMainDlg->m_ctrPM6.GetWindowInt();
            }

            //TM->PM
            Sleep(g_pMainDlg->m_nRotate / g_pMainDlg->m_nSpeed);
            Sleep(g_pMainDlg->m_nPM_Slot_Valve_Open / g_pMainDlg->m_nSpeed);
            Sleep(g_pMainDlg->m_nVAC_Place / g_pMainDlg->m_nSpeed);

            if (g_pMainDlg->m_nThread3_PM[0] == 1 && _ttoi(g_pMainDlg->m_strPMModuleCnt) >= 1)
            {
                for (int i = 36; i <= 38; i++)
                {
                    strImage.Format(_T("UI\\TM(Quad)\\슬라이드%d.png"), i);
                    g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Gui_TM, strImage);
                }
            }
            if (g_pMainDlg->m_nThread3_PM[0] == 2 && _ttoi(g_pMainDlg->m_strPMModuleCnt) >= 2)
            {
                for (int i = 54; i <= 56; i++)
                {
                    strImage.Format(_T("UI\\TM(Quad)\\슬라이드%d.png"), i);
                    g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Gui_TM, strImage);
                }
            }
            if (g_pMainDlg->m_nThread3_PM[0] == 3 && _ttoi(g_pMainDlg->m_strPMModuleCnt) >= 3)
            {
                for (int i = 72; i <= 74; i++)
                {
                    strImage.Format(_T("UI\\TM(Quad)\\슬라이드%d.png"), i);
                    g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Gui_TM, strImage);
                }
            }
            if (g_pMainDlg->m_nThread3_PM[0] == 4 && _ttoi(g_pMainDlg->m_strPMModuleCnt) >= 4)
            {
                for (int i = 90; i <= 92; i++)
                {
                    strImage.Format(_T("UI\\TM(Quad)\\슬라이드%d.png"), i);
                    g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Gui_TM, strImage);
                }
            }
            if (g_pMainDlg->m_nThread3_PM[0] == 5 && _ttoi(g_pMainDlg->m_strPMModuleCnt) >= 5)
            {
                for (int i = 108; i <= 110; i++)
                {
                    strImage.Format(_T("UI\\TM(Quad)\\슬라이드%d.png"), i);
                    g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Gui_TM, strImage);
                }
            }
            if (g_pMainDlg->m_nThread3_PM[0] == 6 && _ttoi(g_pMainDlg->m_strPMModuleCnt) >= 6)
            {
                for (int i = 126; i <= 128; i++)
                {
                    strImage.Format(_T("UI\\TM(Quad)\\슬라이드%d.png"), i);
                    g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Gui_TM, strImage);
                }
            }

            for (int i = nPM_cnt;; i++)
            {
                if (g_pMainDlg->m_strVacArmCnt == _T("4"))
                {
                    if (i % 2 == 0)
                    {
                        g_pMainDlg->m_ctrTM.SetWindowInt(nTM_cnt);
                        if (g_pMainDlg->m_nThread3_PM[0] == 1 && _ttoi(g_pMainDlg->m_strPMModuleCnt) >= 1)
                            g_pMainDlg->m_ctrPM1.SetWindowInt(i);

                        if (g_pMainDlg->m_nThread3_PM[0] == 2 && _ttoi(g_pMainDlg->m_strPMModuleCnt) >= 2)
                            g_pMainDlg->m_ctrPM2.SetWindowInt(i);

                        if (g_pMainDlg->m_nThread3_PM[0] == 3 && _ttoi(g_pMainDlg->m_strPMModuleCnt) >= 3)
                            g_pMainDlg->m_ctrPM3.SetWindowInt(i);

                        if (g_pMainDlg->m_nThread3_PM[0] == 4 && _ttoi(g_pMainDlg->m_strPMModuleCnt) >= 4)
                            g_pMainDlg->m_ctrPM4.SetWindowInt(i);

                        if (g_pMainDlg->m_nThread3_PM[0] == 5 && _ttoi(g_pMainDlg->m_strPMModuleCnt) >= 5)
                            g_pMainDlg->m_ctrPM5.SetWindowInt(i);

                        if (g_pMainDlg->m_nThread3_PM[0] == 6 && _ttoi(g_pMainDlg->m_strPMModuleCnt) >= 6)
                            g_pMainDlg->m_ctrPM6.SetWindowInt(i);
                    }
                }
                else if (g_pMainDlg->m_strVacArmCnt == _T("2"))
                {
                    g_pMainDlg->m_ctrTM.SetWindowInt(nTM_cnt);
                    if (g_pMainDlg->m_nThread3_PM[0] == 1 && _ttoi(g_pMainDlg->m_strPMModuleCnt) >= 1)
                        g_pMainDlg->m_ctrPM1.SetWindowInt(i);

                    if (g_pMainDlg->m_nThread3_PM[0] == 2 && _ttoi(g_pMainDlg->m_strPMModuleCnt) >= 2)
                        g_pMainDlg->m_ctrPM2.SetWindowInt(i);

                    if (g_pMainDlg->m_nThread3_PM[0] == 3 && _ttoi(g_pMainDlg->m_strPMModuleCnt) >= 3)
                        g_pMainDlg->m_ctrPM3.SetWindowInt(i);

                    if (g_pMainDlg->m_nThread3_PM[0] == 4 && _ttoi(g_pMainDlg->m_strPMModuleCnt) >= 4)
                        g_pMainDlg->m_ctrPM4.SetWindowInt(i);

                    if (g_pMainDlg->m_nThread3_PM[0] == 5 && _ttoi(g_pMainDlg->m_strPMModuleCnt) >= 5)
                        g_pMainDlg->m_ctrPM5.SetWindowInt(i);

                    if (g_pMainDlg->m_nThread3_PM[0] == 6 && _ttoi(g_pMainDlg->m_strPMModuleCnt) >= 6)
                        g_pMainDlg->m_ctrPM6.SetWindowInt(i);
                }

                if (nTM_cnt == 0) break;  //TM(VAC ROBOT)에 남아있는 wafer가 없다면 종료
                if (i == _ttoi(g_pMainDlg->m_strPMSlotCnt)) break;  //PM이 가득 찼다면 종료
                PM_Count++;
                nTM_cnt--;
            }

            if (PM_Count == _ttoi(g_pMainDlg->m_strPMSlotCnt))
            {
                Sleep(g_pMainDlg->m_nPM_Slot_Valve_Close / g_pMainDlg->m_nSpeed);
                Sleep(g_pMainDlg->m_nPM_Slot_Valve_Open / g_pMainDlg->m_nSpeed);
                PM_Count = 0;
                g_pMainDlg->m_nPM_Processing++;
                g_hThread_PM[g_pMainDlg->m_nThread3_PM[0] - 1] = (CreateThread(NULL, 0, PM, 0, 0, 0));
                for (int i = 0; i < 9; i++)
                {
                    g_pMainDlg->m_nThread3_PM[i] = g_pMainDlg->m_nThread3_PM[i + 1];
                }
            }
            if (g_pMainDlg->m_nThread3_PM[0] == 0)
            {
                ResetEvent(g_hEventPM_Array);
                WaitForSingleObject(g_hEventPM_Array, INFINITE);
            }
            nTM_cnt = g_pMainDlg->m_ctrTM.GetWindowInt();
            if (g_pMainDlg->m_nThread3_PM[0] == 1 && _ttoi(g_pMainDlg->m_strPMModuleCnt) >= 1)
                nPM_cnt = g_pMainDlg->m_ctrPM1.GetWindowInt();

            if (g_pMainDlg->m_nThread3_PM[0] == 2 && _ttoi(g_pMainDlg->m_strPMModuleCnt) >= 2)
                nPM_cnt = g_pMainDlg->m_ctrPM2.GetWindowInt();

            if (g_pMainDlg->m_nThread3_PM[0] == 3 && _ttoi(g_pMainDlg->m_strPMModuleCnt) >= 3)
                nPM_cnt = g_pMainDlg->m_ctrPM3.GetWindowInt();

            if (g_pMainDlg->m_nThread3_PM[0] == 4 && _ttoi(g_pMainDlg->m_strPMModuleCnt) >= 4)
                nPM_cnt = g_pMainDlg->m_ctrPM4.GetWindowInt();

            if (g_pMainDlg->m_nThread3_PM[0] == 5 && _ttoi(g_pMainDlg->m_strPMModuleCnt) >= 5)
                nPM_cnt = g_pMainDlg->m_ctrPM5.GetWindowInt();

            if (g_pMainDlg->m_nThread3_PM[0] == 6 && _ttoi(g_pMainDlg->m_strPMModuleCnt) >= 6)
                nPM_cnt = g_pMainDlg->m_ctrPM6.GetWindowInt();

            //PM->TM
            Sleep(g_pMainDlg->m_nRotate / g_pMainDlg->m_nSpeed);
            Sleep(g_pMainDlg->m_nVAC_Pick / g_pMainDlg->m_nSpeed);

            if (g_pMainDlg->m_ctrPM1.GetWindowInt() != 0 && g_pMainDlg->m_nThread3_PM[0] == 1)
            {
                for (int i = 38; i <= 40; i++)
                {
                    strImage.Format(_T("UI\\TM(Quad)\\슬라이드%d.png"), i);
                    g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Gui_TM, strImage);
                }
            }
            if (g_pMainDlg->m_ctrPM2.GetWindowInt() != 0 && g_pMainDlg->m_nThread3_PM[0] == 2)
            {
                for (int i = 56; i <= 58; i++)
                {
                    strImage.Format(_T("UI\\TM(Quad)\\슬라이드%d.png"), i);
                    g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Gui_TM, strImage);
                }
            }

            if (g_pMainDlg->m_ctrPM3.GetWindowInt() != 0 && g_pMainDlg->m_nThread3_PM[0] == 3)
            {
                for (int i = 74; i <= 76; i++)
                {
                    strImage.Format(_T("UI\\TM(Quad)\\슬라이드%d.png"), i);
                    g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Gui_TM, strImage);
                }
            }

            if (g_pMainDlg->m_ctrPM4.GetWindowInt() != 0 && g_pMainDlg->m_nThread3_PM[0] == 4)
            {
                for (int i = 92; i <= 94; i++)
                {
                    strImage.Format(_T("UI\\TM(Quad)\\슬라이드%d.png"), i);
                    g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Gui_TM, strImage);
                }
            }

            if (g_pMainDlg->m_ctrPM5.GetWindowInt() != 0 && g_pMainDlg->m_nThread3_PM[0] == 5)
            {
                for (int i = 110; i <= 112; i++)
                {
                    strImage.Format(_T("UI\\TM(Quad)\\슬라이드%d.png"), i);
                    g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Gui_TM, strImage);
                }
            }

            if (g_pMainDlg->m_ctrPM6.GetWindowInt() != 0 && g_pMainDlg->m_nThread3_PM[0] == 6)
            {
                for (int i = 128; i <= 130; i++)
                {
                    strImage.Format(_T("UI\\TM(Quad)\\슬라이드%d.png"), i);
                    g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Gui_TM, strImage);
                }
            }

            if (g_pMainDlg->m_nPM_Processing == _ttoi(g_pMainDlg->m_strPMModuleCnt))
            {
                ResetEvent(g_hEvent_PM_MAX);
                WaitForSingleObject(g_hEvent_PM_MAX, INFINITE);
            }

            for (int i = nTM_cnt; ; i++)
            {
                if (g_pMainDlg->m_strVacArmCnt == _T("4"))
                {
                    if (i % 2 == 0)
                    {
                        g_pMainDlg->m_ctrTM.SetWindowInt(i);
                        if (g_pMainDlg->m_ctrPM1.GetWindowInt() != 0 && g_pMainDlg->m_nThread3_PM[0] == 1)
                            g_pMainDlg->m_ctrPM1.SetWindowInt(nPM_cnt);

                        if (g_pMainDlg->m_ctrPM2.GetWindowInt() != 0 && g_pMainDlg->m_nThread3_PM[0] == 2)
                            g_pMainDlg->m_ctrPM2.SetWindowInt(nPM_cnt);

                        if (g_pMainDlg->m_ctrPM3.GetWindowInt() != 0 && g_pMainDlg->m_nThread3_PM[0] == 3)
                            g_pMainDlg->m_ctrPM3.SetWindowInt(nPM_cnt);

                        if (g_pMainDlg->m_ctrPM4.GetWindowInt() != 0 && g_pMainDlg->m_nThread3_PM[0] == 4)
                            g_pMainDlg->m_ctrPM4.SetWindowInt(nPM_cnt);

                        if (g_pMainDlg->m_ctrPM5.GetWindowInt() != 0 && g_pMainDlg->m_nThread3_PM[0] == 5)
                            g_pMainDlg->m_ctrPM5.SetWindowInt(nPM_cnt);

                        if (g_pMainDlg->m_ctrPM6.GetWindowInt() != 0 && g_pMainDlg->m_nThread3_PM[0] == 6)
                            g_pMainDlg->m_ctrPM6.SetWindowInt(nPM_cnt);
                    }
                }
                else if (g_pMainDlg->m_strVacArmCnt == _T("2"))
                {
                    g_pMainDlg->m_ctrTM.SetWindowInt(i);
                    if (g_pMainDlg->m_ctrPM1.GetWindowInt() != 0 && g_pMainDlg->m_nThread3_PM[0] == 1)
                        g_pMainDlg->m_ctrPM1.SetWindowInt(nPM_cnt);

                    if (g_pMainDlg->m_ctrPM2.GetWindowInt() != 0 && g_pMainDlg->m_nThread3_PM[0] == 2)
                        g_pMainDlg->m_ctrPM2.SetWindowInt(nPM_cnt);

                    if (g_pMainDlg->m_ctrPM3.GetWindowInt() != 0 && g_pMainDlg->m_nThread3_PM[0] == 3)
                        g_pMainDlg->m_ctrPM3.SetWindowInt(nPM_cnt);

                    if (g_pMainDlg->m_ctrPM4.GetWindowInt() != 0 && g_pMainDlg->m_nThread3_PM[0] == 4)
                        g_pMainDlg->m_ctrPM4.SetWindowInt(nPM_cnt);

                    if (g_pMainDlg->m_ctrPM5.GetWindowInt() != 0 && g_pMainDlg->m_nThread3_PM[0] == 5)
                        g_pMainDlg->m_ctrPM5.SetWindowInt(nPM_cnt);

                    if (g_pMainDlg->m_ctrPM6.GetWindowInt() != 0 && g_pMainDlg->m_nThread3_PM[0] == 6)
                        g_pMainDlg->m_ctrPM6.SetWindowInt(nPM_cnt);
                }
                //현재 LL에 있는 wafer의 수와 VAC ROBOT이 들고 있는 wafer 갯수의 합이
                //LL의 최대치(MAX:24장)와 같다면 PM에서 더 꺼내지 말고 대기
                //if (nLL_cnt + i == g_pMainDlg->m_nLLMAX) break;
                if (nPM_cnt == 0) break;  //PM에 남아있는 wafer가 없다면 종료

                nPM_cnt--;

                if (i == _ttoi(g_pMainDlg->m_strVacArmCnt)) break;  //TM(VAC ROBOT)이 Dual Arm일 땐 wafer 2장,
                //Quad Arm일 때 wafer를 4장 들고 있다면 대기
            }

        }
        nTM_cnt = g_pMainDlg->m_ctrTM.GetWindowInt();
        if (g_pMainDlg->m_nThread3_LL == 1)
            nLL_cnt = g_pMainDlg->m_ctrLL1.GetWindowInt();
        if (g_pMainDlg->m_nThread3_LL == 2)
            nLL_cnt = g_pMainDlg->m_ctrLL2.GetWindowInt();
        if (g_pMainDlg->m_nThread3_LL == 3)
            nLL_cnt = g_pMainDlg->m_ctrLL3.GetWindowInt();
        if (g_pMainDlg->m_nThread3_LL == 4)
            nLL_cnt = g_pMainDlg->m_ctrLL4.GetWindowInt();
        //PLACE : VAC ROBOT -> LL
        for (int i = nLL_cnt;; i++)
        {
            if (g_pMainDlg->m_strVacArmCnt == _T("4"))
            {
                if (i % 2 == 0)
                {
                    g_pMainDlg->m_ctrTM.SetWindowInt(nTM_cnt);
                    if (g_pMainDlg->m_nThread3_LL == 1)
                        g_pMainDlg->m_ctrLL1.SetWindowInt(i);
                    if (g_pMainDlg->m_nThread3_LL == 2)
                        g_pMainDlg->m_ctrLL2.SetWindowInt(i);
                    if (g_pMainDlg->m_nThread3_LL == 3)
                        g_pMainDlg->m_ctrLL3.SetWindowInt(i);
                    if (g_pMainDlg->m_nThread3_LL == 4)
                        g_pMainDlg->m_ctrLL4.SetWindowInt(i);
                }
                g_pMainDlg->InvalidateRect(g_CRtemp, false);
            }
            else if (g_pMainDlg->m_strVacArmCnt == _T("2"))
            {
                g_pMainDlg->m_ctrTM.SetWindowInt(nTM_cnt);
                if (g_pMainDlg->m_nThread3_LL == 1)
                    g_pMainDlg->m_ctrLL1.SetWindowInt(i);
                if (g_pMainDlg->m_nThread3_LL == 2)
                    g_pMainDlg->m_ctrLL2.SetWindowInt(i);
                if (g_pMainDlg->m_nThread3_LL == 3)
                    g_pMainDlg->m_ctrLL3.SetWindowInt(i);
                if (g_pMainDlg->m_nThread3_LL == 4)
                    g_pMainDlg->m_ctrLL4.SetWindowInt(i);
                g_pMainDlg->InvalidateRect(g_CRtemp, false);
            }

            if (nTM_cnt == _ttoi(g_pMainDlg->m_strVacArmCnt) / 2) break;  //TM(VAC ROBOT)에 남아있는 wafer가 없다면 종료
            LL_Count++;
            nTM_cnt--;
        }

        if (LL_Count == _ttoi(g_pMainDlg->m_strLLSlotCnt))
        {
            LL_Count = 0;
            g_pMainDlg->m_nThread3_LL++;

            if (g_pMainDlg->m_nThread_Time_Error == _ttoi(g_pMainDlg->m_strLLModuleCnt))
                WaitForSingleObject(g_hEventThread_Time_Error, INFINITE);
        }
        if (g_pMainDlg->m_nThread3_LL == _ttoi(g_pMainDlg->m_strLLModuleCnt) + 1)
            g_pMainDlg->m_nThread3_LL = 1;

        nTM_cnt = g_pMainDlg->m_ctrTM.GetWindowInt();
        if (g_pMainDlg->m_nThread3_PM[0] == 1 && _ttoi(g_pMainDlg->m_strPMModuleCnt) >= 1)
            nPM_cnt = g_pMainDlg->m_ctrPM1.GetWindowInt();

        if (g_pMainDlg->m_nThread3_PM[0] == 2 && _ttoi(g_pMainDlg->m_strPMModuleCnt) >= 2)
            nPM_cnt = g_pMainDlg->m_ctrPM2.GetWindowInt();

        if (g_pMainDlg->m_nThread3_PM[0] == 3 && _ttoi(g_pMainDlg->m_strPMModuleCnt) >= 3)
            nPM_cnt = g_pMainDlg->m_ctrPM3.GetWindowInt();

        if (g_pMainDlg->m_nThread3_PM[0] == 4 && _ttoi(g_pMainDlg->m_strPMModuleCnt) >= 4)
            nPM_cnt = g_pMainDlg->m_ctrPM4.GetWindowInt();

        if (g_pMainDlg->m_nThread3_PM[0] == 5 && _ttoi(g_pMainDlg->m_strPMModuleCnt) >= 5)
            nPM_cnt = g_pMainDlg->m_ctrPM5.GetWindowInt();

        if (g_pMainDlg->m_nThread3_PM[0] == 6 && _ttoi(g_pMainDlg->m_strPMModuleCnt) >= 6)
            nPM_cnt = g_pMainDlg->m_ctrPM6.GetWindowInt();

        //TM->PM
        for (int i = nPM_cnt;; i++)
        {
            if (g_pMainDlg->m_strVacArmCnt == _T("4"))
            {
                if (i % 2 == 0)
                {
                    g_pMainDlg->m_ctrTM.SetWindowInt(nTM_cnt);
                    if (g_pMainDlg->m_nThread3_PM[0] == 1 && _ttoi(g_pMainDlg->m_strPMModuleCnt) >= 1)
                        g_pMainDlg->m_ctrPM1.SetWindowInt(i);

                    if (g_pMainDlg->m_nThread3_PM[0] == 2 && _ttoi(g_pMainDlg->m_strPMModuleCnt) >= 2)
                        g_pMainDlg->m_ctrPM2.SetWindowInt(i);

                    if (g_pMainDlg->m_nThread3_PM[0] == 3 && _ttoi(g_pMainDlg->m_strPMModuleCnt) >= 3)
                        g_pMainDlg->m_ctrPM3.SetWindowInt(i);

                    if (g_pMainDlg->m_nThread3_PM[0] == 4 && _ttoi(g_pMainDlg->m_strPMModuleCnt) >= 4)
                        g_pMainDlg->m_ctrPM4.SetWindowInt(i);

                    if (g_pMainDlg->m_nThread3_PM[0] == 5 && _ttoi(g_pMainDlg->m_strPMModuleCnt) >= 5)
                        g_pMainDlg->m_ctrPM5.SetWindowInt(i);

                    if (g_pMainDlg->m_nThread3_PM[0] == 6 && _ttoi(g_pMainDlg->m_strPMModuleCnt) >= 6)
                        g_pMainDlg->m_ctrPM6.SetWindowInt(i);
                }
            }
            else if (g_pMainDlg->m_strVacArmCnt == _T("2"))
            {
                g_pMainDlg->m_ctrTM.SetWindowInt(nTM_cnt);
                if (g_pMainDlg->m_nThread3_PM[0] == 1 && _ttoi(g_pMainDlg->m_strPMModuleCnt) >= 1)
                    g_pMainDlg->m_ctrPM1.SetWindowInt(i);

                if (g_pMainDlg->m_nThread3_PM[0] == 2 && _ttoi(g_pMainDlg->m_strPMModuleCnt) >= 2)
                    g_pMainDlg->m_ctrPM2.SetWindowInt(i);

                if (g_pMainDlg->m_nThread3_PM[0] == 3 && _ttoi(g_pMainDlg->m_strPMModuleCnt) >= 3)
                    g_pMainDlg->m_ctrPM3.SetWindowInt(i);

                if (g_pMainDlg->m_nThread3_PM[0] == 4 && _ttoi(g_pMainDlg->m_strPMModuleCnt) >= 4)
                    g_pMainDlg->m_ctrPM4.SetWindowInt(i);

                if (g_pMainDlg->m_nThread3_PM[0] == 5 && _ttoi(g_pMainDlg->m_strPMModuleCnt) >= 5)
                    g_pMainDlg->m_ctrPM5.SetWindowInt(i);

                if (g_pMainDlg->m_nThread3_PM[0] == 6 && _ttoi(g_pMainDlg->m_strPMModuleCnt) >= 6)
                    g_pMainDlg->m_ctrPM6.SetWindowInt(i);
            }

            if (nTM_cnt == 0) break;  //TM(VAC ROBOT)에 남아있는 wafer가 없다면 종료
            if (i == _ttoi(g_pMainDlg->m_strPMSlotCnt)) break;  //PM이 가득 찼다면 종료
            PM_Count++;
            nTM_cnt--;
        }

        if (PM_Count == _ttoi(g_pMainDlg->m_strPMSlotCnt))
        {
            for (int i = 0; i < 10; i++)
            {
                g_pMainDlg->m_nThread3_PM[i] = g_pMainDlg->m_nThread3_PM[i + 1];
            }
            PM_Count = 0;
        }
        if (g_pMainDlg->m_nPM_Processing + 1 == g_pMainDlg->m_strPMModuleCnt)
        {
            ResetEvent(g_hEvent_PM_MAX);
            WaitForSingleObject(g_hEvent_PM_MAX, INFINITE);
        }


    }
    return 0;
}

DWORD WINAPI LL(LPVOID p)
{
    int nThread4_LL = g_pMainDlg->m_nLL_Thread - 1;
    if (nThread4_LL == 1)
    {
        for (int i = 1; i <= 50; i++)
        {
            g_pMainDlg->m_ctrPROGRESS_LL1.SetPos(i);
            Sleep(g_pMainDlg->m_nLL_Vent / (g_pMainDlg->m_nSpeed * 50));
            Sleep(g_pMainDlg->m_nLL_Vent_Stable_Time / (g_pMainDlg->m_nSpeed * 50));
        }
    }
    else if (nThread4_LL == 2)
    {
        for (int i = 1; i <= 50; i++)
        {
            g_pMainDlg->m_ctrPROGRESS_LL2.SetPos(i);
            Sleep(g_pMainDlg->m_nLL_Vent / (g_pMainDlg->m_nSpeed * 50));
            Sleep(g_pMainDlg->m_nLL_Vent_Stable_Time / (g_pMainDlg->m_nSpeed * 50));
        }
    }
    else if (nThread4_LL == 3)
    {
        for (int i = 1; i <= 50; i++)
        {
            g_pMainDlg->m_ctrPROGRESS_LL3.SetPos(i);
            Sleep(g_pMainDlg->m_nLL_Vent / (g_pMainDlg->m_nSpeed * 50));
            Sleep(g_pMainDlg->m_nLL_Vent_Stable_Time / (g_pMainDlg->m_nSpeed * 50));
        }
    }
    else if (nThread4_LL == 4)
    {
        for (int i = 1; i <= 50; i++)
        {
            g_pMainDlg->m_ctrPROGRESS_LL4.SetPos(i);
            Sleep(g_pMainDlg->m_nLL_Vent / (g_pMainDlg->m_nSpeed * 50));
            Sleep(g_pMainDlg->m_nLL_Vent_Stable_Time / (g_pMainDlg->m_nSpeed * 50));
        }
    }
    SetEvent(g_hEventcount);
    if (_ttoi(g_pMainDlg->m_strLLModuleCnt) == 1 || _ttoi(g_pMainDlg->m_strLLModuleCnt) == 2 || _ttoi(g_pMainDlg->m_strLLSlotCnt) < 3)
        SetEvent(g_hEventLL_Modul_one_Thread4and1);

    return 0;
}

//EFEM Post-Process(EFEM-OUT)
DWORD WINAPI Thread_4_LL2OUT(LPVOID p)
{
    int nLL_cnt;
    int nEFEM_cnt;
    int nOUTPUT_cnt;
    int nPM_cnt;
    int nALLPM_cnt = 0;
    int nThread4_LL = 0;
    CString Image_Load;
    CString strImage;
    nThread4_LL = g_pMainDlg->m_nThread4_LL;

    /*if (nLL_cnt = g_pMainDlg->m_ctrLL1.GetWindowInt() != 0)
        nThread4_LL = 1;
    else if (nLL_cnt = g_pMainDlg->m_ctrLL2.GetWindowInt() != 0)
        nThread4_LL = 2;
    else if (nLL_cnt = g_pMainDlg->m_ctrLL3.GetWindowInt() != 0)
        nThread4_LL = 3;
    else if (nLL_cnt = g_pMainDlg->m_ctrLL4.GetWindowInt() != 0)
        nThread4_LL = 4;
    */
    //LLROOM[nThread4_LL - 1] == TRUE;
    nPM_cnt = g_pMainDlg->m_ctrPM1.GetWindowInt();
    nALLPM_cnt = nALLPM_cnt + nPM_cnt;

    nPM_cnt = g_pMainDlg->m_ctrPM2.GetWindowInt();
    nALLPM_cnt = nALLPM_cnt + nPM_cnt;

    nPM_cnt = g_pMainDlg->m_ctrPM3.GetWindowInt();
    nALLPM_cnt = nALLPM_cnt + nPM_cnt;

    nPM_cnt = g_pMainDlg->m_ctrPM4.GetWindowInt();
    nALLPM_cnt = nALLPM_cnt + nPM_cnt;

    nPM_cnt = g_pMainDlg->m_ctrPM5.GetWindowInt();
    nALLPM_cnt = nALLPM_cnt + nPM_cnt;

    nPM_cnt = g_pMainDlg->m_ctrPM6.GetWindowInt();
    nALLPM_cnt = nALLPM_cnt + nPM_cnt;

    if (nThread4_LL == 1)
    {
        strImage.Format(_T("UI\\LL\\슬라이드%d.png"), 6);
        g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_ctrGUI_LL1, strImage);
    }
    else if (nThread4_LL == 2)
    {
        strImage.Format(_T("UI\\LL\\슬라이드%d.png"), 6);
        g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_ctrGUI_LL2, strImage);
    }
    else if (nThread4_LL == 3)
    {
        strImage.Format(_T("UI\\LL\\슬라이드%d.png"), 6);
        g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_ctrGUI_LL3, strImage);
    }
    else if (nThread4_LL == 4)
    {
        strImage.Format(_T("UI\\LL\\슬라이드%d.png"), 6);
        g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_ctrGUI_LL4, strImage);
    }
    //PICK & PLACE (LL -> ATM ROBOT -> LPM(OUTPUT))
    while (true)
    {
        if (nThread4_LL == 1)
            nLL_cnt = g_pMainDlg->m_ctrLL1.GetWindowInt();
        else if (nThread4_LL == 2)
            nLL_cnt = g_pMainDlg->m_ctrLL2.GetWindowInt();
        else if (nThread4_LL == 3)
            nLL_cnt = g_pMainDlg->m_ctrLL3.GetWindowInt();
        else if (nThread4_LL == 4)
            nLL_cnt = g_pMainDlg->m_ctrLL4.GetWindowInt();

        if (nLL_cnt == 0) break;  //LL에 남아있는 wafer가 없다면 종료


        nEFEM_cnt = g_pMainDlg->m_ctrEFEM.GetWindowInt();

        //PICK : LL -> ATM ROBOT
        Sleep(g_pMainDlg->m_nATM_Rotate / g_pMainDlg->m_nSpeed);
        Sleep(g_pMainDlg->m_nATM_ZRotate / g_pMainDlg->m_nSpeed);
        Sleep(g_pMainDlg->m_nLL_Slot_Valve_Open / g_pMainDlg->m_nSpeed);
        Sleep(g_pMainDlg->m_nATM_Pick / g_pMainDlg->m_nSpeed);
        for (int i = 1; i <= 3; i++)
        {
            strImage.Format(_T("UI\\EFEM2\\슬라이드%d.png"), i);
            g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Ctrl_Gui_EFEM, strImage);
        }
        for (int i = 0;; i++)
        {
            if (nThread4_LL == 1)
                g_pMainDlg->m_ctrLL1.SetWindowInt(nLL_cnt);
            else if (nThread4_LL == 2)
                g_pMainDlg->m_ctrLL2.SetWindowInt(nLL_cnt);
            else if (nThread4_LL == 3)
                g_pMainDlg->m_ctrLL3.SetWindowInt(nLL_cnt);
            else if (nThread4_LL == 4)
                g_pMainDlg->m_ctrLL4.SetWindowInt(nLL_cnt);
            g_pMainDlg->m_nWafer_Process[nThread4_LL - 1] = nLL_cnt;
            g_pMainDlg->InvalidateRect(g_CRtemp, false);
            g_pMainDlg->m_ctrEFEM.SetWindowInt(i);

            if (nLL_cnt == 0) break;  //LL에 남아있는 wafer가 없다면 종료

            nLL_cnt--;

            if (i == 1) break;  //ATM ROBOT이 최대로 잡을 수 있는 wafer는 2장(MAX)
        }

        nEFEM_cnt = g_pMainDlg->m_ctrEFEM.GetWindowInt();
        nOUTPUT_cnt = g_pMainDlg->m_ctrOutput.GetWindowInt();
        //PLACE : ATM ROBOT -> LPM(OUTPUT)
        Sleep(g_pMainDlg->m_nATM_Rotate / g_pMainDlg->m_nSpeed);
        Sleep(g_pMainDlg->m_nATM_ZRotate / g_pMainDlg->m_nSpeed);
        Sleep(g_pMainDlg->m_nATM_Place / g_pMainDlg->m_nSpeed);
        for (int i = 4; i <= 7; i++)
        {
            strImage.Format(_T("UI\\EFEM2\\슬라이드%d.png"), i);
            g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Ctrl_Gui_EFEM, strImage);
        }
        for (int i = nOUTPUT_cnt;; i++)
        {
            g_pMainDlg->m_ctrEFEM.SetWindowInt(nEFEM_cnt);
            if (g_pMainDlg->m_bDummy == false)
            {
                g_pMainDlg->m_ctrOutput.SetWindowInt(i);

                g_pMainDlg->m_ctrLPMUI2.SetWindowInt(g_pMainDlg->m_ctrLPMUI2.GetWindowInt() + nEFEM_cnt);
                if (g_pMainDlg->m_ctrLPMUI2.GetWindowInt() == 25)
                    g_pMainDlg->m_ctrLPMUI2.SetWindowInt(0);
            }
            if (g_pMainDlg->m_bDummy == true)
            {
                g_pMainDlg->m_nDummy_Count = g_pMainDlg->m_nDummy_Count + nEFEM_cnt;
            }
            if (g_pMainDlg->m_ctrOutput.GetWindowInt() != 0
                && g_pMainDlg->m_ctrOutput.GetWindowInt() % (_ttoi(g_pMainDlg->m_strPMModuleCnt) * _ttoi(g_pMainDlg->m_strPMSlotCnt) * (g_pMainDlg->m_nPM_Clean_Wafer_Count)) == 0)
            {
                g_pMainDlg->m_bDummy = true;
            }
            if (g_pMainDlg->m_nDummy_Count == (_ttoi(g_pMainDlg->m_strPMModuleCnt) * _ttoi(g_pMainDlg->m_strPMSlotCnt)))
            {
                g_pMainDlg->m_bClean_Time_Start = false;
                g_pMainDlg->m_bDummy = false;
                g_pMainDlg->m_nDummy_Count = 0;
            }
            g_pMainDlg->m_nWafer_Count--;
            if (nEFEM_cnt == 0) break;  //EFEM(ATM ROBOT)에 남아있는 wafer가 없다

            nEFEM_cnt--;

        }
    }
    g_pMainDlg->m_noutput_count = g_pMainDlg->m_ctrOutput.GetWindowInt();
    //if (g_pMainDlg->m_noutput_count == 0)
    
    if (nThread4_LL == 1)
    {
        strImage.Format(_T("UI\\LL\\슬라이드%d.png"), 7);
        g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_ctrGUI_LL1, strImage);
    }
    else if (nThread4_LL == 2)
    {
        strImage.Format(_T("UI\\LL\\슬라이드%d.png"), 7);
        g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_ctrGUI_LL2, strImage);
    }
    else if (nThread4_LL == 3)
    {
        strImage.Format(_T("UI\\LL\\슬라이드%d.png"), 7);
        g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_ctrGUI_LL3, strImage);
    }
    else if (nThread4_LL == 4)
    {
        strImage.Format(_T("UI\\LL\\슬라이드%d.png"), 7);
        g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_ctrGUI_LL4, strImage);
    }
    //g_pMainDlg->m_nThread_Time_Error--;

    SetEvent(g_hEventThread4_wait);
    return 0;
}

DWORD WINAPI PM(LPVOID p)
{
    //if 프로세스 동작 / 클린 동작 구분
    int nPM_Check;
    
    int nPM_Time = g_pMainDlg->m_nPM_Time;
    CString strImage;

    if (g_pMainDlg->m_bPM_Thread_Check == false)
    {
        if (g_pMainDlg->m_nPM_Thread2 == _ttoi(g_pMainDlg->m_strPMModuleCnt))
            g_pMainDlg->m_bPM_Thread_Check = true;

        nPM_Check = g_pMainDlg->m_nPM_Thread2;
        if (nPM_Check == 1)
        {
            
            if (g_pMainDlg->m_CtrStatic_PM1.GetWindowInt() % (_ttoi(g_pMainDlg->m_strPMSlotCnt) * g_pMainDlg->m_nPM_Clean_Wafer_Count) == 0
                && g_pMainDlg->m_CtrStatic_PM1.GetWindowInt() != 0)
            {
                nPM_Time = g_pMainDlg->m_arrCleanProcess[0] * 1000;
                g_pMainDlg->GetDlgItem(IDC_RADIO_Process1)->EnableWindow(FALSE);
                g_pMainDlg->GetDlgItem(IDC_RADIO_Clean1)->EnableWindow(TRUE);
                g_pMainDlg->m_ctrRadio_Clean1.SetCheck(TRUE);
                g_pMainDlg->m_ctrRadio_Process1.SetCheck(FALSE);
            }
            else
            {
                nPM_Time = g_pMainDlg->m_arrPMProcess[0] * 1000;
                g_pMainDlg->GetDlgItem(IDC_RADIO_Clean1)->EnableWindow(FALSE);
                g_pMainDlg->GetDlgItem(IDC_RADIO_Process1)->EnableWindow(TRUE);
                g_pMainDlg->m_ctrRadio_Process1.SetCheck(TRUE);
                g_pMainDlg->m_ctrRadio_Clean1.SetCheck(FALSE);
            }
            for (int i = 4; i <= 4; i++)
            {
                strImage.Format(_T("UI\\PM_Left\\슬라이드%d.png"), i);
                g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Ctrl_Gui_PM1, strImage);
            }
        }
        else if (nPM_Check == 2)
        {
            
            g_pMainDlg->m_CtrStatic_PM2.SetWindowInt(0);
            if (g_pMainDlg->m_CtrStatic_PM2.GetWindowInt() != 0 &&
                g_pMainDlg->m_CtrStatic_PM2.GetWindowInt() % _ttoi(g_pMainDlg->m_strPMSlotCnt) * g_pMainDlg->m_nPM_Clean_Wafer_Count == 0)
            {
                nPM_Time = g_pMainDlg->m_arrCleanProcess[1] * 1000;
                g_pMainDlg->GetDlgItem(IDC_RADIO_Process2)->EnableWindow(FALSE);
                g_pMainDlg->GetDlgItem(IDC_RADIO_Clean2)->EnableWindow(TRUE);
                g_pMainDlg->m_ctrRadio_Clean2.SetCheck(TRUE);
                g_pMainDlg->m_ctrRadio_Process2.SetCheck(FALSE);
            }
            else
            {
                nPM_Time = g_pMainDlg->m_arrPMProcess[1] * 1000;
                g_pMainDlg->GetDlgItem(IDC_RADIO_Clean2)->EnableWindow(FALSE);
                g_pMainDlg->GetDlgItem(IDC_RADIO_Process2)->EnableWindow(TRUE);
                g_pMainDlg->m_ctrRadio_Process2.SetCheck(TRUE);
                g_pMainDlg->m_ctrRadio_Clean2.SetCheck(FALSE);
            }
            for (int i = 4; i <= 4; i++)
            {
                strImage.Format(_T("UI\\PM_Left\\슬라이드%d.png"), i);
                g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Ctrl_Gui_PM2, strImage);
            }
        }
        else if (nPM_Check == 3)
        {
           
            g_pMainDlg->m_CtrStatic_PM3.SetWindowInt(0);
            if (g_pMainDlg->m_CtrStatic_PM3.GetWindowInt() != 0 && g_pMainDlg->m_CtrStatic_PM3.GetWindowInt() % _ttoi(g_pMainDlg->m_strPMSlotCnt) * g_pMainDlg->m_nPM_Clean_Wafer_Count == 0)
            {
                nPM_Time = g_pMainDlg->m_arrCleanProcess[2] * 1000;
                g_pMainDlg->GetDlgItem(IDC_RADIO_Process3)->EnableWindow(FALSE);
                g_pMainDlg->GetDlgItem(IDC_RADIO_Clean3)->EnableWindow(TRUE);
                g_pMainDlg->m_ctrRadio_Clean3.SetCheck(TRUE);
                g_pMainDlg->m_ctrRadio_Process3.SetCheck(FALSE);
            }
            else
            {
                nPM_Time = g_pMainDlg->m_arrPMProcess[2] * 1000;
                g_pMainDlg->GetDlgItem(IDC_RADIO_Clean3)->EnableWindow(FALSE);
                g_pMainDlg->GetDlgItem(IDC_RADIO_Process3)->EnableWindow(TRUE);
                g_pMainDlg->m_ctrRadio_Process3.SetCheck(TRUE);
                g_pMainDlg->m_ctrRadio_Clean3.SetCheck(FALSE);
            }
            for (int i = 4; i <= 4; i++)
            {
                strImage.Format(_T("UI\\PM_Upper\\슬라이드%d.png"), i);
                g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Ctrl_Gui_PM3, strImage);
            }
        }
        else if (nPM_Check == 4)
        {
            
            g_pMainDlg->m_CtrStatic_PM4.SetWindowInt(0);
            if (g_pMainDlg->m_CtrStatic_PM4.GetWindowInt() != 0 && g_pMainDlg->m_CtrStatic_PM4.GetWindowInt() % _ttoi(g_pMainDlg->m_strPMSlotCnt) * g_pMainDlg->m_nPM_Clean_Wafer_Count == 0)
            {
                nPM_Time = g_pMainDlg->m_arrCleanProcess[3] * 1000;
                g_pMainDlg->GetDlgItem(IDC_RADIO_Process4)->EnableWindow(FALSE);
                g_pMainDlg->GetDlgItem(IDC_RADIO_Clean4)->EnableWindow(TRUE);
                g_pMainDlg->m_ctrRadio_Clean4.SetCheck(TRUE);
                g_pMainDlg->m_ctrRadio_Process4.SetCheck(FALSE);
            }
            else
            {
                nPM_Time = g_pMainDlg->m_arrPMProcess[3] * 1000;
                g_pMainDlg->GetDlgItem(IDC_RADIO_Clean4)->EnableWindow(FALSE);
                g_pMainDlg->GetDlgItem(IDC_RADIO_Process4)->EnableWindow(TRUE);
                g_pMainDlg->m_ctrRadio_Process4.SetCheck(TRUE);
                g_pMainDlg->m_ctrRadio_Clean4.SetCheck(FALSE);
            }
            for (int i = 4; i <= 4; i++)
            {
                strImage.Format(_T("UI\\PM_Upper\\슬라이드%d.png"), i);
                g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Ctrl_Gui_PM4, strImage);
            }
        }
        else if (nPM_Check == 5)
        {
        
            g_pMainDlg->m_CtrStatic_PM5.SetWindowInt(0);
            if (g_pMainDlg->m_CtrStatic_PM5.GetWindowInt() != 0 && g_pMainDlg->m_CtrStatic_PM5.GetWindowInt() % _ttoi(g_pMainDlg->m_strPMSlotCnt) * g_pMainDlg->m_nPM_Clean_Wafer_Count == 0)
            {
                nPM_Time = g_pMainDlg->m_arrCleanProcess[4] * 1000;
                g_pMainDlg->GetDlgItem(IDC_RADIO_Process5)->EnableWindow(FALSE);
                g_pMainDlg->GetDlgItem(IDC_RADIO_Clean5)->EnableWindow(TRUE);
                g_pMainDlg->m_ctrRadio_Clean5.SetCheck(TRUE);
                g_pMainDlg->m_ctrRadio_Process5.SetCheck(FALSE);
            }
            else
            {
                nPM_Time = g_pMainDlg->m_arrPMProcess[4] * 1000;
                g_pMainDlg->GetDlgItem(IDC_RADIO_Clean5)->EnableWindow(FALSE);
                g_pMainDlg->GetDlgItem(IDC_RADIO_Process5)->EnableWindow(TRUE);
                g_pMainDlg->m_ctrRadio_Process5.SetCheck(TRUE);
                g_pMainDlg->m_ctrRadio_Clean5.SetCheck(FALSE);
            }
            for (int i = 4; i <= 4; i++)
            {
                strImage.Format(_T("UI\\PM_Right\\슬라이드%d.png"), i);
                g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Ctrl_Gui_PM5, strImage);
            }
        }
        else if (nPM_Check == 6)
        {
           
            g_pMainDlg->m_CtrStatic_PM6.SetWindowInt(0);
            if (g_pMainDlg->m_CtrStatic_PM6.GetWindowInt() != 0 && g_pMainDlg->m_CtrStatic_PM6.GetWindowInt() % _ttoi(g_pMainDlg->m_strPMSlotCnt) * g_pMainDlg->m_nPM_Clean_Wafer_Count == 0)
            {
                nPM_Time = g_pMainDlg->m_arrCleanProcess[5] * 1000;
                g_pMainDlg->GetDlgItem(IDC_RADIO_Process6)->EnableWindow(FALSE);
                g_pMainDlg->GetDlgItem(IDC_RADIO_Clean6)->EnableWindow(TRUE);
                g_pMainDlg->m_ctrRadio_Clean6.SetCheck(TRUE);
                g_pMainDlg->m_ctrRadio_Process6.SetCheck(FALSE);
            }
            else
            {
                nPM_Time = g_pMainDlg->m_arrPMProcess[5] * 1000;
                g_pMainDlg->GetDlgItem(IDC_RADIO_Clean6)->EnableWindow(FALSE);
                g_pMainDlg->GetDlgItem(IDC_RADIO_Process6)->EnableWindow(TRUE);
                g_pMainDlg->m_ctrRadio_Process6.SetCheck(TRUE);
                g_pMainDlg->m_ctrRadio_Clean6.SetCheck(FALSE);
            }
            for (int i = 4; i <= 4; i++)
            {
                strImage.Format(_T("UI\\PM_Right\\슬라이드%d.png"), i);
                g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Ctrl_Gui_PM6, strImage);
            }
        }

        for (int i = 1; i <= 100; i++)
        {
            Sleep(nPM_Time / (g_pMainDlg->m_nSpeed * 100));
            if (nPM_Check == 1)
            {
                g_pMainDlg->m_ctrPROGRESS_PM1.SetPos(i);
                g_pMainDlg->m_ctrPM_Count1.SetWindowInt(i);
                if (i > 99)
                {
                    for (int i = 5; i <= 5; i++)
                    {
                        strImage.Format(_T("UI\\PM_Left\\슬라이드%d.png"), i);
                        g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Ctrl_Gui_PM1, strImage);
                    }
                }
            }
            else if (nPM_Check == 2)
            {
                g_pMainDlg->m_ctrPROGRESS_PM2.SetPos(i);
                g_pMainDlg->m_ctrPM_Count2.SetWindowInt(i);
                if (i > 99)
                {
                    for (int i = 5; i <= 5; i++)
                    {
                        strImage.Format(_T("UI\\PM_Left\\슬라이드%d.png"), i);
                        g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Ctrl_Gui_PM2, strImage);
                    }
                }
            }
            else if (nPM_Check == 3)
            {
                g_pMainDlg->m_ctrPROGRESS_PM3.SetPos(i);
                g_pMainDlg->m_ctrPM_Count3.SetWindowInt(i);
                if (i > 99)
                {
                    for (int i = 5; i <= 5; i++)
                    {
                        strImage.Format(_T("UI\\PM_Upper\\슬라이드%d.png"), i);
                        g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Ctrl_Gui_PM3, strImage);
                    }
                }
            }
            else if (nPM_Check == 4)
            {
                g_pMainDlg->m_ctrPROGRESS_PM4.SetPos(i);
                g_pMainDlg->m_ctrPM_Count4.SetWindowInt(i);
                if (i > 99)
                {
                    for (int i = 5; i <= 5; i++)
                    {
                        strImage.Format(_T("UI\\PM_Upper\\슬라이드%d.png"), i);
                        g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Ctrl_Gui_PM4, strImage);
                    }
                }
            }
            else if (nPM_Check == 5)
            {
                g_pMainDlg->m_ctrPROGRESS_PM5.SetPos(i);
                g_pMainDlg->m_ctrPM_Count5.SetWindowInt(i);
                if (i > 99)
                {
                    for (int i = 5; i <= 5; i++)
                    {
                        strImage.Format(_T("UI\\PM_Right\\슬라이드%d.png"), i);
                        g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Ctrl_Gui_PM5, strImage);
                    }
                }
            }
            else if (nPM_Check == 6)
            {
                g_pMainDlg->m_ctrPROGRESS_PM6.SetPos(i);
                g_pMainDlg->m_ctrPM_Count6.SetWindowInt(i);
                if (i > 99)
                {
                    for (int i = 5; i <= 5; i++)
                    {
                        strImage.Format(_T("UI\\PM_Right\\슬라이드%d.png"), i);
                        g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Ctrl_Gui_PM6, strImage);
                    }
                }
            }

            //프로그래스바 1/100 충전
        }
    }
    else if (g_pMainDlg->m_bPM_Thread_Check == true)
    {
        nPM_Check = g_pMainDlg->m_nPM_Thread3;
        if (nPM_Check == 1)
        {
            if (g_pMainDlg->m_CtrStatic_PM1.GetWindowInt() % (_ttoi(g_pMainDlg->m_strPMSlotCnt) * g_pMainDlg->m_nPM_Clean_Wafer_Count) == 0)
            {
                nPM_Time = g_pMainDlg->m_nPM_Clean_Time;
                g_pMainDlg->GetDlgItem(IDC_RADIO_Process1)->EnableWindow(FALSE);
                g_pMainDlg->GetDlgItem(IDC_RADIO_Clean1)->EnableWindow(TRUE);
                g_pMainDlg->m_ctrRadio_Clean1.SetCheck(TRUE);
                g_pMainDlg->m_ctrRadio_Process1.SetCheck(FALSE);
            }
            else
            {
                nPM_Time = 600000;
                g_pMainDlg->GetDlgItem(IDC_RADIO_Clean1)->EnableWindow(FALSE);
                g_pMainDlg->GetDlgItem(IDC_RADIO_Process1)->EnableWindow(TRUE);
                g_pMainDlg->m_ctrRadio_Process1.SetCheck(TRUE);
                g_pMainDlg->m_ctrRadio_Clean1.SetCheck(FALSE);
            }
            for (int i = 4; i <= 4; i++)
            {
                strImage.Format(_T("UI\\PM_Left\\슬라이드%d.png"), i);
                g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Ctrl_Gui_PM1, strImage);
            }
        }
        else if (nPM_Check == 2)
        {
            if (g_pMainDlg->m_CtrStatic_PM2.GetWindowInt() % (_ttoi(g_pMainDlg->m_strPMSlotCnt) * g_pMainDlg->m_nPM_Clean_Wafer_Count) == 0)
            {
                g_pMainDlg->GetDlgItem(IDC_RADIO_Process2)->EnableWindow(FALSE);
                g_pMainDlg->GetDlgItem(IDC_RADIO_Clean2)->EnableWindow(TRUE);
                g_pMainDlg->m_ctrRadio_Clean2.SetCheck(TRUE);
                g_pMainDlg->m_ctrRadio_Process2.SetCheck(FALSE);
            }
            else
            {
                nPM_Time = 300000;
                g_pMainDlg->GetDlgItem(IDC_RADIO_Clean2)->EnableWindow(FALSE);
                g_pMainDlg->GetDlgItem(IDC_RADIO_Process2)->EnableWindow(TRUE);
                g_pMainDlg->m_ctrRadio_Process2.SetCheck(TRUE);
                g_pMainDlg->m_ctrRadio_Clean2.SetCheck(FALSE);
            }
            for (int i = 4; i <= 4; i++)
            {
                strImage.Format(_T("UI\\PM_Left\\슬라이드%d.png"), i);
                g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Ctrl_Gui_PM2, strImage);
            }
        }
        else if (nPM_Check == 3)
        {
            if (g_pMainDlg->m_CtrStatic_PM3.GetWindowInt() % (_ttoi(g_pMainDlg->m_strPMSlotCnt) * g_pMainDlg->m_nPM_Clean_Wafer_Count) == 0)
            {
                g_pMainDlg->GetDlgItem(IDC_RADIO_Process3)->EnableWindow(FALSE);
                g_pMainDlg->GetDlgItem(IDC_RADIO_Clean3)->EnableWindow(TRUE);
                g_pMainDlg->m_ctrRadio_Clean3.SetCheck(TRUE);
                g_pMainDlg->m_ctrRadio_Process3.SetCheck(FALSE);
            }
            else
            {
                nPM_Time = 3000000;
                g_pMainDlg->GetDlgItem(IDC_RADIO_Clean3)->EnableWindow(FALSE);
                g_pMainDlg->GetDlgItem(IDC_RADIO_Process3)->EnableWindow(TRUE);
                g_pMainDlg->m_ctrRadio_Process3.SetCheck(TRUE);
                g_pMainDlg->m_ctrRadio_Clean3.SetCheck(FALSE);
            }
            for (int i = 4; i <= 4; i++)
            {
                strImage.Format(_T("UI\\PM_Upper\\슬라이드%d.png"), i);
                g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Ctrl_Gui_PM3, strImage);
            }
        }
        else if (nPM_Check == 4)
        {
            if (g_pMainDlg->m_CtrStatic_PM4.GetWindowInt() % (_ttoi(g_pMainDlg->m_strPMSlotCnt) * g_pMainDlg->m_nPM_Clean_Wafer_Count) == 0)
            {
                g_pMainDlg->GetDlgItem(IDC_RADIO_Process4)->EnableWindow(FALSE);
                g_pMainDlg->GetDlgItem(IDC_RADIO_Clean4)->EnableWindow(TRUE);
                g_pMainDlg->m_ctrRadio_Clean4.SetCheck(TRUE);
                g_pMainDlg->m_ctrRadio_Process4.SetCheck(FALSE);
            }
            else
            {
                nPM_Time = 2000000;
                g_pMainDlg->GetDlgItem(IDC_RADIO_Clean4)->EnableWindow(FALSE);
                g_pMainDlg->GetDlgItem(IDC_RADIO_Process4)->EnableWindow(TRUE);
                g_pMainDlg->m_ctrRadio_Process4.SetCheck(TRUE);
                g_pMainDlg->m_ctrRadio_Clean4.SetCheck(FALSE);
            }
            for (int i = 4; i <= 4; i++)
            {
                strImage.Format(_T("UI\\PM_Upper\\슬라이드%d.png"), i);
                g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Ctrl_Gui_PM4, strImage);
            }
        }
        else if (nPM_Check == 5)
        {
            if (g_pMainDlg->m_CtrStatic_PM5.GetWindowInt() % (_ttoi(g_pMainDlg->m_strPMSlotCnt) * g_pMainDlg->m_nPM_Clean_Wafer_Count) == 0)
            {
                g_pMainDlg->GetDlgItem(IDC_RADIO_Process5)->EnableWindow(FALSE);
                g_pMainDlg->GetDlgItem(IDC_RADIO_Clean5)->EnableWindow(TRUE);
                g_pMainDlg->m_ctrRadio_Clean5.SetCheck(TRUE);
                g_pMainDlg->m_ctrRadio_Process5.SetCheck(FALSE);
            }
            else
            {
                nPM_Time = 1000000;
                g_pMainDlg->GetDlgItem(IDC_RADIO_Clean5)->EnableWindow(FALSE);
                g_pMainDlg->GetDlgItem(IDC_RADIO_Process5)->EnableWindow(TRUE);
                g_pMainDlg->m_ctrRadio_Process5.SetCheck(TRUE);
                g_pMainDlg->m_ctrRadio_Clean5.SetCheck(FALSE);
            }
            for (int i = 4; i <= 4; i++)
            {
                strImage.Format(_T("UI\\PM_Right\\슬라이드%d.png"), i);
                g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Ctrl_Gui_PM5, strImage);
            }
        }
        else if (nPM_Check == 6)
        {
            if (g_pMainDlg->m_CtrStatic_PM6.GetWindowInt() % (_ttoi(g_pMainDlg->m_strPMSlotCnt) * g_pMainDlg->m_nPM_Clean_Wafer_Count) == 0)
            {
                g_pMainDlg->GetDlgItem(IDC_RADIO_Process6)->EnableWindow(FALSE);
                g_pMainDlg->GetDlgItem(IDC_RADIO_Clean6)->EnableWindow(TRUE);
                g_pMainDlg->m_ctrRadio_Clean6.SetCheck(TRUE);
                g_pMainDlg->m_ctrRadio_Process6.SetCheck(FALSE);
            }
            else
            {
                nPM_Time = 600000;
                g_pMainDlg->GetDlgItem(IDC_RADIO_Clean6)->EnableWindow(FALSE);
                g_pMainDlg->GetDlgItem(IDC_RADIO_Process6)->EnableWindow(TRUE);
                g_pMainDlg->m_ctrRadio_Process6.SetCheck(TRUE);
                g_pMainDlg->m_ctrRadio_Clean6.SetCheck(FALSE);
            }
            for (int i = 4; i <= 4; i++)
            {
                strImage.Format(_T("UI\\PM_Right\\슬라이드%d.png"), i);
                g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Ctrl_Gui_PM6, strImage);
            }
        }
        for (int i = 1; i <= 100; i++)
        {
            Sleep(nPM_Time / (g_pMainDlg->m_nSpeed * 100));
            if (nPM_Check == 1)
            {
                g_pMainDlg->m_ctrPROGRESS_PM1.SetPos(i);
                g_pMainDlg->m_ctrPM_Count1.SetWindowInt(i);
                if (i > 99)
                {
                    for (int i = 5; i <= 5; i++)
                    {
                        strImage.Format(_T("UI\\PM_Left\\슬라이드%d.png"), i);
                        g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Ctrl_Gui_PM1, strImage);
                    }
                }
            }
            else if (nPM_Check == 2)
            {
                g_pMainDlg->m_ctrPROGRESS_PM2.SetPos(i);
                g_pMainDlg->m_ctrPM_Count2.SetWindowInt(i);
                if (i > 99)
                {
                    for (int i = 5; i <= 5; i++)
                    {
                        strImage.Format(_T("UI\\PM_Left\\슬라이드%d.png"), i);
                        g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Ctrl_Gui_PM2, strImage);
                    }
                }
            }
            else if (nPM_Check == 3)
            {
                g_pMainDlg->m_ctrPROGRESS_PM3.SetPos(i);
                g_pMainDlg->m_ctrPM_Count3.SetWindowInt(i);
                if (i > 99)
                {
                    for (int i = 5; i <= 5; i++)
                    {
                        strImage.Format(_T("UI\\PM_Upper\\슬라이드%d.png"), i);
                        g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Ctrl_Gui_PM3, strImage);
                    }
                }
            }
            else if (nPM_Check == 4)
            {
                g_pMainDlg->m_ctrPROGRESS_PM4.SetPos(i);
                g_pMainDlg->m_ctrPM_Count4.SetWindowInt(i);
                if (i > 99)
                {
                    for (int i = 5; i <= 5; i++)
                    {
                        strImage.Format(_T("UI\\PM_Upper\\슬라이드%d.png"), i);
                        g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Ctrl_Gui_PM4, strImage);
                    }
                }
            }
            else if (nPM_Check == 5)
            {
                g_pMainDlg->m_ctrPROGRESS_PM5.SetPos(i);
                g_pMainDlg->m_ctrPM_Count5.SetWindowInt(i);
                if (i > 99)
                {
                    for (int i = 5; i <= 5; i++)
                    {
                        strImage.Format(_T("UI\\PM_Right\\슬라이드%d.png"), i);
                        g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Ctrl_Gui_PM5, strImage);
                    }
                }
            }
            else if (nPM_Check == 6)
            {
                g_pMainDlg->m_ctrPROGRESS_PM6.SetPos(i);
                g_pMainDlg->m_ctrPM_Count6.SetWindowInt(i);
                if (i > 99)
                {
                    for (int i = 5; i <= 5; i++)
                    {
                        strImage.Format(_T("UI\\PM_Right\\슬라이드%d.png"), i);
                        g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Ctrl_Gui_PM6, strImage);
                    }
                }
            }
        }
    }

    if (nPM_Check == 1)
    {
        g_pMainDlg->m_CtrStatic_PM1.SetWindowInt(_ttoi(g_pMainDlg->m_strPMSlotCnt) + g_pMainDlg->m_CtrStatic_PM1.GetWindowInt());
        for (int i = 0; i < 10; i++)
        {
            if (g_pMainDlg->m_nThread3_PM[i] == 0)
            {
                g_pMainDlg->m_nThread3_PM[i] = 1;
                break;
            }
        }
    }
    else if (nPM_Check == 2)
    {
        g_pMainDlg->m_CtrStatic_PM2.SetWindowInt(_ttoi(g_pMainDlg->m_strPMSlotCnt) + g_pMainDlg->m_CtrStatic_PM2.GetWindowInt());
        for (int i = 0; i < 10; i++)
        {
            if (g_pMainDlg->m_nThread3_PM[i] == 0)
            {
                g_pMainDlg->m_nThread3_PM[i] = 2;
                break;
            }
        }
    }
    else if (nPM_Check == 3)
    {
        g_pMainDlg->m_CtrStatic_PM3.SetWindowInt(_ttoi(g_pMainDlg->m_strPMSlotCnt) + g_pMainDlg->m_CtrStatic_PM3.GetWindowInt());
        for (int i = 0; i < 10; i++)
        {
            if (g_pMainDlg->m_nThread3_PM[i] == 0)
            {
                g_pMainDlg->m_nThread3_PM[i] = 3;
                break;
            }
        }
    }
    else if (nPM_Check == 4)
    {
        g_pMainDlg->m_CtrStatic_PM4.SetWindowInt(_ttoi(g_pMainDlg->m_strPMSlotCnt) + g_pMainDlg->m_CtrStatic_PM4.GetWindowInt());
        for (int i = 0; i < 10; i++)
        {
            if (g_pMainDlg->m_nThread3_PM[i] == 0)
            {
                g_pMainDlg->m_nThread3_PM[i] = 4;
                break;
            }
        }
    }
    else if (nPM_Check == 5)
    {
        g_pMainDlg->m_CtrStatic_PM5.SetWindowInt(_ttoi(g_pMainDlg->m_strPMSlotCnt) + g_pMainDlg->m_CtrStatic_PM5.GetWindowInt());
        for (int i = 0; i < 10; i++)
        {
            if (g_pMainDlg->m_nThread3_PM[i] == 0)
            {
                g_pMainDlg->m_nThread3_PM[i] = 5;
                break;
            }
        }
    }
    else if (nPM_Check == 6)
    {
        g_pMainDlg->m_CtrStatic_PM6.SetWindowInt(_ttoi(g_pMainDlg->m_strPMSlotCnt) + g_pMainDlg->m_CtrStatic_PM6.GetWindowInt());
        for (int i = 0; i < 10; i++)
        {
            if (g_pMainDlg->m_nThread3_PM[i] == 0)
            {
                g_pMainDlg->m_nThread3_PM[i] = 6;
                break;
            }
        }
    }

    if (g_pMainDlg->m_nPM_Processing == _ttoi(g_pMainDlg->m_strPMModuleCnt))
        SetEvent(g_hEvent_PM_MAX);
    g_pMainDlg->m_nPM_Processing--;
    SetEvent(g_hEventPM_Array);
    SetEvent(g_hEvent_Thread3_Wait);
    return 0;
}
//FINAL RESULT (THROUGHPUT)
DWORD WINAPI Thread_Start(LPVOID p)
{
    int nLPM_input_cnt = g_pMainDlg->m_ctrLPM.GetWindowInt();
    int nPM_MAX = _ttoi(g_pMainDlg->m_strPMSlotCnt) * _ttoi(g_pMainDlg->m_strPMModuleCnt);
    int nLL_MAX = _ttoi(g_pMainDlg->m_strLLSlotCnt) * _ttoi(g_pMainDlg->m_strLLModuleCnt);
    int nLPM_cnt = g_pMainDlg->m_ctrLPM.GetWindowInt();
    int nLL_Count = g_pMainDlg->m_ctrLL1.GetWindowInt() +
        g_pMainDlg->m_ctrLL2.GetWindowInt() +
        g_pMainDlg->m_ctrLL3.GetWindowInt() +
        g_pMainDlg->m_ctrLL4.GetWindowInt();
    int PM_Count;
    int n_Thread1_Suspend = 0;
    while (nLPM_cnt != 0)
    {
        if (nLPM_input_cnt - nLPM_cnt - g_pMainDlg->m_noutput_count >= nPM_MAX + nLL_MAX)
        {
            if (g_pMainDlg->m_nThread_Time_Error > 0)
            {
                if (_ttoi(g_pMainDlg->m_strLLModuleCnt) == 1 || _ttoi(g_pMainDlg->m_strLLModuleCnt) == 2 || _ttoi(g_pMainDlg->m_strLLSlotCnt) < 3)
                    WaitForSingleObject(g_hEventLL_Modul_one_Thread4and1, INFINITE);

                g_hThread4 = (CreateThread(NULL, 0, Thread_4_LL2OUT, 0, 0, 0));
                WaitForSingleObject(g_hEventThread4_wait, INFINITE);

                g_hThread1[n_Thread1_Suspend] = (CreateThread(NULL, 0, Thread_1_LPM2LL, 0, 0, 0));
                WaitForSingleObject(g_hEventStart, INFINITE);
                if (n_Thread1_Suspend == 0)
                    n_Thread1_Suspend = 1;
                else if (n_Thread1_Suspend == 1)
                    n_Thread1_Suspend = 0;
                g_pMainDlg->m_nThread4_LL++;
                if (g_pMainDlg->m_nThread4_LL == _ttoi(g_pMainDlg->m_strLLModuleCnt) + 1)
                    g_pMainDlg->m_nThread4_LL = 1;
            }
            if (g_pMainDlg->m_noutput_count == _ttoi(g_pMainDlg->m_strLLSlotCnt))
                g_pMainDlg->m_nThread1_LL = 0;
        }

        if (g_pMainDlg->m_Thread3start == 0)
        {
            g_hThread1[n_Thread1_Suspend] = (CreateThread(NULL, 0, Thread_1_LPM2LL, 0, 0, 0));
            WaitForSingleObject(g_hEventStart, INFINITE);
            if (n_Thread1_Suspend == 0)
                n_Thread1_Suspend = 1;
            else if (n_Thread1_Suspend == 1)
                n_Thread1_Suspend = 0;
        }

        nLPM_cnt = g_pMainDlg->m_ctrLPM.GetWindowInt();
        PM_Count = g_pMainDlg->m_ctrPM1.GetWindowInt() +
            g_pMainDlg->m_ctrPM2.GetWindowInt() +
            g_pMainDlg->m_ctrPM3.GetWindowInt() +
            g_pMainDlg->m_ctrPM4.GetWindowInt() +
            g_pMainDlg->m_ctrPM5.GetWindowInt() +
            g_pMainDlg->m_ctrPM6.GetWindowInt();
        nLL_Count = g_pMainDlg->m_ctrLL1.GetWindowInt() +
            g_pMainDlg->m_ctrLL2.GetWindowInt() +
            g_pMainDlg->m_ctrLL3.GetWindowInt() +
            g_pMainDlg->m_ctrLL4.GetWindowInt();

        if (PM_Count != nPM_MAX && g_pMainDlg->m_Thread3start == 0)
        {
            ResetEvent(g_hEventLL_Modul_one_Thread1and2);
            if (nLL_Count == nLL_MAX)
                WaitForSingleObject(g_hEventLL_Modul_one_Thread1and2, INFINITE);
        }

        if (g_pMainDlg->m_Thread3start == 0 && (PM_Count == nPM_MAX && g_pMainDlg->m_nWafer_Count == nPM_MAX + g_pMainDlg->m_nLLMAX))
        {
            //for (int i = 0; i < g_pMainDlg->m_nThread2_LL; i++)
            {
                if (g_pMainDlg->m_nThread3_PM[0] == 0)
                    WaitForSingleObject(g_hEvent_Thread3_Wait, INFINITE);
                g_hThread3 = (CreateThread(NULL, 0, Thread_3_PM2LL, 0, 0, 0));
                g_pMainDlg->m_Thread3start++;
                
                //WaitForSingleObject(g_hEventPMtoLL, INFINITE);
            }
        }
    }

    return 0;
}

DWORD WINAPI TotalTime(LPVOID p)
{
    CString strTime_Total;
    int n_D_Total = 0;
    int n_H_Total = 0;
    int n_M_Total = 0;
    int n_S_Total = 0;
    int i = g_pMainDlg->m_ctrOutput.GetWindowInt();
    CString strTmep;
    CString strTime_Clean;
    int n_D_Clean = 0;
    int n_H_Clean = 0;
    int n_M_Clean = 0;
    int n_S_Clean = 0;

    while (true)
    {

        Sleep(1000 / g_pMainDlg->m_nSpeed);
        if (g_pMainDlg->m_bTime_STOP == true)
        {
            ResetEvent(g_hThread_TotalTime);
            WaitForSingleObject(g_hThread_TotalTime, INFINITE);

        }
        n_S_Total++;
        if (n_S_Total == 60)
        {
            n_S_Total = 0;
            n_M_Total++;
        }
        if (n_M_Total == 60)
        {
            n_M_Total = 0;
            n_H_Total++;
        }
        if (n_H_Total == 24)
        {
            n_H_Total = 0;
            n_D_Total++;
        }
        //g_pMainDlg->m_strCurTime = CTime::GetCurrentTime();
        //g_pMainDlg->m_strDiffTime = g_pMainDlg->m_strCurTime - g_pMainDlg->m_strInitTime;
        strTime_Total.Format(_T("%02d:%02d:%02d:%02d"), n_D_Total, n_H_Total, n_M_Total, n_S_Total);

        if (g_pMainDlg->m_ctrStatic_Speed.GetWindowInt() == 1)
            g_pMainDlg->m_ctrlStaticTotalTime.SetWindowText(strTime_Total);
        else if (n_S_Total % 3 == 0)
            g_pMainDlg->m_ctrlStaticTotalTime.SetWindowText(strTime_Total);
        g_pMainDlg->m_nTotalSec++;
        if (g_pMainDlg->m_bClean_Time_Start == true)
        {
            n_S_Clean++;
            if (n_S_Clean == 60)
            {
                n_S_Clean = 0;
                n_M_Clean++;
            }
            if (n_M_Clean == 60)
            {
                n_M_Clean = 0;
                n_H_Clean++;
            }
            if (n_H_Clean == 24)
            {
                n_H_Clean = 0;
                n_D_Clean++;
            }
            strTime_Clean.Format(_T("%02d:%02d:%02d:%02d"), n_D_Clean, n_H_Clean, n_M_Clean, n_S_Clean);
            if (g_pMainDlg->m_ctrStatic_Speed.GetWindowInt() == 1)
                g_pMainDlg->m_ctrTotal_Clean_Time.SetWindowText(strTime_Clean);
            else if (n_S_Clean % 3 == 0)
                g_pMainDlg->m_ctrTotal_Clean_Time.SetWindowText(strTime_Clean);
            g_pMainDlg->m_nCleanSec++;
        }

        double dTotalSec = g_pMainDlg->m_nTotalSec - g_pMainDlg->m_nCleanSec;
        double dTotalHour = dTotalSec / 3600;
        i = g_pMainDlg->m_ctrOutput.GetWindowInt();
        strTmep.Format(_T("%.2f"), (i / dTotalHour));
        g_pMainDlg->m_ctrThrought.SetWindowText(strTmep);
    }
    return 0;
}

void C주성Dlg::OnBnClickedStart()
{


    CString strLL_UI;
    CString strPM_UI;
    strLL_UI.Format(_T("/ %d"), _ttoi(m_strLLSlotCnt));
    strPM_UI.Format(_T("/ %d"), _ttoi(m_strPMSlotCnt));
    CString strValue;
    GetDlgItem(IDC_START)->GetWindowText(strValue);
    if (strValue == _T("START"))
    {
        CString strImage;

        strImage.Format(_T("UI\\EFEM1\\슬라이드1.png"));
        g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Ctrl_Gui_EFEM, strImage);
        strImage.Format(_T("UI\\TM(Quad)\\슬라이드1.png"));
        g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Gui_TM, strImage);
        strImage.Format(_T("UI\\PM_Left\\슬라이드1.png"));
        g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Ctrl_Gui_PM1, strImage);
        strImage.Format(_T("UI\\PM_Left\\슬라이드1.png"));
        g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Ctrl_Gui_PM2, strImage);
        strImage.Format(_T("UI\\PM_Upper\\슬라이드1.png"));
        g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Ctrl_Gui_PM3, strImage);
        strImage.Format(_T("UI\\PM_Upper\\슬라이드1.png"));
        g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Ctrl_Gui_PM4, strImage);
        strImage.Format(_T("UI\\PM_Right\\슬라이드1.png"));
        g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Ctrl_Gui_PM5, strImage);
        strImage.Format(_T("UI\\PM_Right\\슬라이드1.png"));
        g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Ctrl_Gui_PM6, strImage);
        GetDlgItem(IDC_LL_SLOT_MAX1)->SetWindowText(strLL_UI);
        GetDlgItem(IDC_LL_SLOT_MAX2)->SetWindowText(strLL_UI);
        GetDlgItem(IDC_LL_SLOT_MAX3)->SetWindowText(strLL_UI);
        GetDlgItem(IDC_LL_SLOT_MAX4)->SetWindowText(strLL_UI);

        GetDlgItem(IDC_PM_SLOT_MAX1)->SetWindowText(strPM_UI);
        GetDlgItem(IDC_PM_SLOT_MAX2)->SetWindowText(strPM_UI);
        GetDlgItem(IDC_PM_SLOT_MAX3)->SetWindowText(strPM_UI);
        GetDlgItem(IDC_PM_SLOT_MAX4)->SetWindowText(strPM_UI);
        GetDlgItem(IDC_PM_SLOT_MAX5)->SetWindowText(strPM_UI);
        GetDlgItem(IDC_PM_SLOT_MAX6)->SetWindowText(strPM_UI);
        GetDlgItem(IDC_START)->SetWindowText(_T("STOP"));
        GetDlgItem(IDC_BUTTON_SAVE_SYSTEMCONFIG)->EnableWindow(FALSE);
        GetDlgItem(IDC_BUTTON_LOAD_SYSTEMCONFIG)->EnableWindow(FALSE);
        GetDlgItem(IDC_BUTTON_SAVE_THROUGHPUT)->EnableWindow(FALSE);
        GetDlgItem(IDC_BUTTON_LOAD_THROUGHPUT)->EnableWindow(FALSE);
        GetDlgItem(IDC_SYS_INFO)->EnableWindow(FALSE);
        UpdateData(1);
        g_pMainDlg->InvalidateRect(g_CRtemp, false);
        m_nSpeed = _ttoi(m_strSpeed);
        m_ctrStatic_Speed.SetWindowInt(_ttoi(m_strSpeed));
        m_ctrLPM.SetWindowInt(99999999);
        m_nLLMAX = _ttoi(m_strLLSlotCnt) * _ttoi(m_strLLModuleCnt);
        (CreateThread(NULL, 0, TotalTime, 0, 0, 0));
        g_hThread_Thread_Start = (CreateThread(NULL, 0, Thread_Start, 0, 0, 0));
        m_bTime_STOP = false;
        //ResumeThread()
    }
    else if (strValue == _T("STOP"))
    {
        GetDlgItem(IDC_START)->SetWindowText(_T("Resume"));
        GetDlgItem(IDC_BUTTON_SAVE_SYSTEMCONFIG)->EnableWindow(TRUE);
        GetDlgItem(IDC_BUTTON_LOAD_SYSTEMCONFIG)->EnableWindow(FALSE);
        GetDlgItem(IDC_BUTTON_SAVE_THROUGHPUT)->EnableWindow(TRUE);
        GetDlgItem(IDC_BUTTON_LOAD_THROUGHPUT)->EnableWindow(TRUE);

        SuspendThread(g_hThread1[0]);
        SuspendThread(g_hThread1[1]);
        SuspendThread(g_hThread2);
        SuspendThread(g_hThread3);
        SuspendThread(g_hThread4);
        SuspendThread(g_hThread_Thread_Start);
        for (int i = 0; i < 4; i++)
        {
            SuspendThread(g_hThread_LL[i]);
        }
        for (int i = 0; i < 6; i++)
        {
            SuspendThread(g_hThread_PM[i]);
        }
        m_bTime_STOP = true;
    }
    else if (strValue == _T("Resume"))
    {
        GetDlgItem(IDC_START)->SetWindowText(_T("STOP"));
        GetDlgItem(IDC_START)->EnableWindow(FALSE);
        GetDlgItem(IDC_BUTTON_SAVE_SYSTEMCONFIG)->EnableWindow(FALSE);
        GetDlgItem(IDC_BUTTON_LOAD_SYSTEMCONFIG)->EnableWindow(FALSE);
        GetDlgItem(IDC_BUTTON_SAVE_THROUGHPUT)->EnableWindow(FALSE);
        GetDlgItem(IDC_BUTTON_LOAD_THROUGHPUT)->EnableWindow(FALSE);
        ResumeThread(g_hThread1[0]);
        ResumeThread(g_hThread1[1]);
        ResumeThread(g_hThread2);
        ResumeThread(g_hThread3);
        ResumeThread(g_hThread4);
        ResumeThread(g_hThread_Thread_Start);
        for (int i = 0; i < 4; i++)
        {
            ResumeThread(g_hThread_LL[i]);
        }
        for (int i = 0; i < 6; i++)
        {
            ResumeThread(g_hThread_PM[i]);
        }
        m_bTime_STOP = false;
        SetEvent(g_hThread_TotalTime);
        GetDlgItem(IDC_START)->EnableWindow(TRUE);
    }


}

void C주성Dlg::OnBnClickedSetSpeed()
{
    UpdateData(1);
    g_pMainDlg->m_nSpeed = _ttoi(m_strSpeed);
    m_ctrStatic_Speed.SetWindowInt(_ttoi(m_strSpeed));
    g_pSubDlg->m_nEFEMPickTime;

    UpdateData(0);
}

#define MSEC 1000
void C주성Dlg::OnBnClickedSysInitial()
{
    CSysInfoDlg dlgSysInfo;
    if (dlgSysInfo.DoModal() == IDOK)
    {
        for (int i = 0; i < 6; i++)
        {
            m_arrPMProcess[i] = dlgSysInfo.m_arrPMProcess[i];
            m_arrCleanProcess[i] = dlgSysInfo.m_arrCleanProcess[i];
        }
        m_nATM_Pick = dlgSysInfo.m_nEFEMPickTime * MSEC;
        m_nATM_Place = dlgSysInfo.m_nEFEMPlaceTime * MSEC;
        m_nATM_Rotate = dlgSysInfo.m_nEFEMRotateTime * MSEC;
        m_nATM_ZRotate = dlgSysInfo.m_nEFEMMoveTime * MSEC;

        m_strLLModuleCnt = dlgSysInfo.m_strLLModuleCount;
        m_strLLSlotCnt = dlgSysInfo.m_strLLSlotCount;
        m_nLL_Pump = dlgSysInfo.m_nLLPumpTime * MSEC;
        m_nLL_Pump_Stable_Time = dlgSysInfo.m_nLLPumpStableTime * MSEC;
        m_nLL_Vent = dlgSysInfo.m_nLLVentTime * MSEC;
        m_nLL_Vent_Stable_Time = dlgSysInfo.m_nLLVentStableTime * MSEC;
        m_nLL_Slot_Valve_Open = dlgSysInfo.m_nLLSlotOpenTime * MSEC;
        m_nLL_Slot_Valve_Close = dlgSysInfo.m_nLLSlotCloseTime * MSEC;
        m_nLL_Door_Valve_Open = dlgSysInfo.m_nLLDoorOpenTime * MSEC;
        m_nLL_Door_Valve_Close = dlgSysInfo.m_nLLDoorCloseTime * MSEC;

        m_strVacArmCnt = dlgSysInfo.m_strVacArmCount;
        m_nVAC_Pick = dlgSysInfo.m_nTMPickTime * MSEC;
        m_nVAC_Place = dlgSysInfo.m_nTMPlaceTime * MSEC;
        m_nRotate = dlgSysInfo.m_nTMRotate * MSEC;

        m_strPMModuleCnt = dlgSysInfo.m_strPMModuleCount;
        m_strPMSlotCnt = dlgSysInfo.m_strPMSlotCount;
        m_nPM_Clean_Time = dlgSysInfo.m_nPMProcessTime * 2 * MSEC;
        m_nPM_Clean_Wafer_Count = dlgSysInfo.m_nCleanCount;
        m_nPM_Time = dlgSysInfo.m_nPMProcessTime * MSEC;
        m_nPM_Slot_Valve_Open = dlgSysInfo.m_nPMSlotOpenTime * MSEC;
        m_nPM_Slot_Valve_Close = dlgSysInfo.m_nPMSlotCloseTime * MSEC;

        GetDlgItem(IDC_START)->EnableWindow(TRUE);
        GetDlgItem(IDC_BUTTON_SAVE_SYSTEMCONFIG)->EnableWindow(TRUE);
        GetDlgItem(IDC_BUTTON_LOAD_SYSTEMCONFIG)->EnableWindow(TRUE);
        GetDlgItem(IDC_BUTTON_SAVE_THROUGHPUT)->EnableWindow(TRUE);
        GetDlgItem(IDC_BUTTON_LOAD_THROUGHPUT)->EnableWindow(TRUE);
    }
}

void C주성Dlg::OnBnClickedButtonSaveSystemconfig()
{
    CFileDialog saveFile(0, _T("*.cfg")
        , 0
        , OFN_OVERWRITEPROMPT | OFN_LONGNAMES
        , _T("System Configulation Files (*.cfg)|*.cfg||")
    );
    CString strValue;
    if (saveFile.DoModal() == IDOK)
    {
        CString strSaveName(saveFile.GetPathName());

        // EFEM
        strValue.Format(_T("%d"), m_nATM_Pick / 1000);
        ::WritePrivateProfileString(_T("EFEM"), _T("Pick"), strValue, strSaveName);
        strValue.Format(_T("%d"), m_nATM_Place / 1000);
        ::WritePrivateProfileString(_T("EFEM"), _T("Place"), strValue, strSaveName);
        //strValue.Format(_T("%d"), m_ctrALIGNER);
        //::WritePrivateProfileString(_T("EFEM"), _T("Aligner"), strValue, strSaveName);
        strValue.Format(_T("%d"), m_nATM_ZRotate / 1000);
        ::WritePrivateProfileString(_T("EFEM"), _T("Z_Move"), strValue, strSaveName);
        strValue.Format(_T("%.1f"), (double)m_nATM_Rotate / 1000.0);
        ::WritePrivateProfileString(_T("EFEM"), _T("Rotate"), strValue, strSaveName);

        // LL
        ::WritePrivateProfileString(_T("LL"), _T("ModuleCount"), m_strLLModuleCnt, strSaveName);
        ::WritePrivateProfileString(_T("LL"), _T("SlotCount"), m_strLLSlotCnt, strSaveName);
        strValue.Format(_T("%d"), m_nLL_Vent / 1000);
        ::WritePrivateProfileString(_T("LL"), _T("VentTime"), strValue, strSaveName);
        strValue.Format(_T("%d"), m_nLL_Vent_Stable_Time / 1000);
        ::WritePrivateProfileString(_T("LL"), _T("VentStableTime"), strValue, strSaveName);
        strValue.Format(_T("%d"), m_nLL_Pump / 1000);
        ::WritePrivateProfileString(_T("LL"), _T("PumpTime"), strValue, strSaveName);
        strValue.Format(_T("%d"), m_nLL_Pump_Stable_Time / 1000);
        ::WritePrivateProfileString(_T("LL"), _T("PumpStableTime"), strValue, strSaveName);
        strValue.Format(_T("%d"), m_nLL_Slot_Valve_Open / 1000);
        ::WritePrivateProfileString(_T("LL"), _T("SlotOpenTime"), strValue, strSaveName);
        strValue.Format(_T("%d"), m_nLL_Slot_Valve_Close / 1000);
        ::WritePrivateProfileString(_T("LL"), _T("SlotCloseTime"), strValue, strSaveName);
        strValue.Format(_T("%d"), m_nLL_Door_Valve_Open / 1000);
        ::WritePrivateProfileString(_T("LL"), _T("DoorOpenTime"), strValue, strSaveName);
        strValue.Format(_T("%d"), m_nLL_Door_Valve_Close / 1000);
        ::WritePrivateProfileString(_T("LL"), _T("DoorCloseTime"), strValue, strSaveName);

        // TM-Vac
        ::WritePrivateProfileString(_T("TM"), _T("ArmCount"), m_strVacArmCnt, strSaveName);
        strValue.Format(_T("%d"), m_nVAC_Pick / 1000);
        ::WritePrivateProfileString(_T("TM"), _T("Pick"), strValue, strSaveName);
        strValue.Format(_T("%d"), m_nVAC_Place / 1000);
        ::WritePrivateProfileString(_T("TM"), _T("Place"), strValue, strSaveName);
        strValue.Format(_T("%d"), m_nRotate / 1000);
        ::WritePrivateProfileString(_T("TM"), _T("Rotate"), strValue, strSaveName);

        // PM
        ::WritePrivateProfileString(_T("PM"), _T("ModuleCount"), m_strPMModuleCnt, strSaveName);
        ::WritePrivateProfileString(_T("PM"), _T("SlotCount"), m_strPMSlotCnt, strSaveName);
        strValue.Format(_T("%d"), m_nPM_Time / 1000);
        ::WritePrivateProfileString(_T("PM"), _T("ProcessTime"), strValue, strSaveName);
        strValue.Format(_T("%d"), m_nPM_Clean_Time / 1000);
        ::WritePrivateProfileString(_T("PM"), _T("CleanTime"), strValue, strSaveName);
        strValue.Format(_T("%d"), m_nPM_Clean_Wafer_Count);
        ::WritePrivateProfileString(_T("PM"), _T("CleanCount"), strValue, strSaveName);
        strValue.Format(_T("%d"), m_nPM_Slot_Valve_Open / 1000);
        ::WritePrivateProfileString(_T("PM"), _T("SlotOpenTime"), strValue, strSaveName);
        strValue.Format(_T("%d"), m_nPM_Slot_Valve_Close / 1000);
        ::WritePrivateProfileString(_T("PM"), _T("SlotCloseTime"), strValue, strSaveName);

    }
}

void C주성Dlg::OnBnClickedButtonLoadSystemconfig()
{
    CFileDialog loadFile(1, _T("*.cfg")
        , 0
        , OFN_OVERWRITEPROMPT | OFN_LONGNAMES | OFN_FILEMUSTEXIST
        , _T("System Configulation Files (*.cfg)|*.cfg||")
    );
    if (loadFile.DoModal() == IDOK)
    {
        CString strLoadName(loadFile.GetPathName());
        TCHAR strReadIni[20] = { 0 };

        // EFEM
        m_nATM_Pick = ::GetPrivateProfileInt(_T("EFEM"), _T("Pick"), -1, strLoadName) * 1000;
        m_nATM_Place = ::GetPrivateProfileInt(_T("EFEM"), _T("Place"), -1, strLoadName) * 1000;
        m_nATM_ZRotate = ::GetPrivateProfileInt(_T("EFEM"), _T("Z_Move"), -1, strLoadName) * 1000;
        m_nATM_Rotate = ::GetPrivateProfileInt(_T("EFEM"), _T("Rotate"), -1, strLoadName) * 1000;

        // LL
        ::GetPrivateProfileString(_T("LL"), _T("ModuleCount"), _T("1"), strReadIni, 20, strLoadName);
        m_strLLModuleCnt.Format(_T("%s"), strReadIni);
        ::GetPrivateProfileString(_T("LL"), _T("SlotCount"), _T("1"), strReadIni, 20, strLoadName);
        m_strLLSlotCnt.Format(_T("%s"), strReadIni);
        m_nLL_Vent = ::GetPrivateProfileInt(_T("LL"), _T("VentTime"), -1, strLoadName) * 1000;
        m_nLL_Vent_Stable_Time = ::GetPrivateProfileInt(_T("LL"), _T("VentStableTime"), -1, strLoadName) * 1000;
        m_nLL_Pump = ::GetPrivateProfileInt(_T("LL"), _T("PumpTime"), -1, strLoadName) * 1000;
        m_nLL_Pump_Stable_Time = ::GetPrivateProfileInt(_T("LL"), _T("PumpStableTime"), -1, strLoadName) * 1000;
        m_nLL_Slot_Valve_Open = ::GetPrivateProfileInt(_T("LL"), _T("SlotOpenTime"), -1, strLoadName) * 1000;
        m_nLL_Slot_Valve_Close = ::GetPrivateProfileInt(_T("LL"), _T("SlotCloseTime"), -1, strLoadName) * 1000;
        m_nLL_Door_Valve_Open = ::GetPrivateProfileInt(_T("LL"), _T("DoorOpenTime"), -1, strLoadName) * 1000;
        m_nLL_Door_Valve_Close = ::GetPrivateProfileInt(_T("LL"), _T("DoorCloseTime"), -1, strLoadName) * 1000;

        // TM-Vac
        ::GetPrivateProfileString(_T("TM"), _T("ArmCount"), _T("2"), strReadIni, 20, strLoadName);
        m_strVacArmCnt.Format(_T("%s"), strReadIni);
        m_nVAC_Pick = ::GetPrivateProfileInt(_T("TM"), _T("Pick"), -1, strLoadName) * 1000;
        m_nVAC_Place = ::GetPrivateProfileInt(_T("TM"), _T("Place"), -1, strLoadName) * 1000;
        m_nRotate = ::GetPrivateProfileInt(_T("TM"), _T("Rotate"), -1, strLoadName) * 1000;

        // PM
        ::GetPrivateProfileString(_T("PM"), _T("ModuleCount"), _T("1"), strReadIni, 20, strLoadName);
        m_strPMModuleCnt.Format(_T("%s"), strReadIni);
        ::GetPrivateProfileString(_T("PM"), _T("SlotCount"), _T("1"), strReadIni, 20, strLoadName);
        m_strPMSlotCnt.Format(_T("%s"), strReadIni);
        m_nPM_Time = ::GetPrivateProfileInt(_T("PM"), _T("ProcessTime"), -1, strLoadName) * 1000;
        m_nPM_Clean_Time = ::GetPrivateProfileInt(_T("PM"), _T("CleanTime"), -1, strLoadName) * 1000;
        m_nPM_Clean_Wafer_Count = ::GetPrivateProfileInt(_T("PM"), _T("CleanCount"), -1, strLoadName);
        m_nPM_Slot_Valve_Open = ::GetPrivateProfileInt(_T("PM"), _T("SlotOpenTime"), -1, strLoadName) * 1000;
        m_nPM_Slot_Valve_Close = ::GetPrivateProfileInt(_T("PM"), _T("SlotCloseTime"), -1, strLoadName) * 1000;

        GetDlgItem(IDC_START)->EnableWindow(TRUE);
        GetDlgItem(IDC_BUTTON_SAVE_SYSTEMCONFIG)->EnableWindow(TRUE);
        GetDlgItem(IDC_BUTTON_LOAD_SYSTEMCONFIG)->EnableWindow(TRUE);
        GetDlgItem(IDC_BUTTON_SAVE_THROUGHPUT)->EnableWindow(TRUE);
        GetDlgItem(IDC_BUTTON_LOAD_THROUGHPUT)->EnableWindow(TRUE);

    }
}

void C주성Dlg::OnBnClickedButtonSaveThroughput()
{
    CFileDialog saveResult(0, _T("*.csv")
        , 0
        , OFN_OVERWRITEPROMPT | OFN_LONGNAMES
        , _T("Save Throughput (*.csv)|*.csv||"));

    CString strName;
    if (saveResult.DoModal() == IDOK)
    {
        strName = saveResult.GetPathName();

        CFile cfile;
        CString strValue;
        CString strTotalTime;
        CString strCleanTime;
        CTime curTime = CTime::GetCurrentTime();

        strValue.Format(_T("Jusung Fab Simulator, %d/%d/%d, %d:%d:%d\n")
            , curTime.GetYear(), curTime.GetMonth(), curTime.GetDay()
            , curTime.GetHour(), curTime.GetMinute(), curTime.GetSecond());
        cfile.Open(strName, CFile::modeCreate | CFile::modeWrite);
        cfile.Write(strValue, strValue.GetLength() * sizeof(TCHAR));
        strValue = _T("/////////////////////////////////////////////////////\n");
        cfile.Write(strValue, strValue.GetLength() * sizeof(TCHAR));

        strValue = _T("TotalTime, CleanTime, Throughput\n");
        cfile.Write(strValue, strValue.GetLength() * sizeof(TCHAR));

        strValue = _T("");
        m_ctrlStaticTotalTime.GetWindowText(strTotalTime);
        m_ctrTotal_Clean_Time.GetWindowText(strCleanTime);
        double dTotalSec = m_nTotalSec - m_nCleanSec;
        m_ctrOutput.GetWindowText(strValue);
        double dOutput = _ttof(strValue);
        strValue.Format(_T("%s, %s, %.2f\n"), strTotalTime, strCleanTime, dOutput / (dTotalSec / 3600.0));
        cfile.Write(strValue, strValue.GetLength() * sizeof(TCHAR));

        strValue = _T("/////////////////////////////////////////////////////\n");
        cfile.Write(strValue, strValue.GetLength() * sizeof(TCHAR));
        strValue = _T("LL_M, LL_S, PM_M, PM_S, VAC\n");
        cfile.Write(strValue, strValue.GetLength() * sizeof(TCHAR));
        strValue = _T("");
        strValue += m_strLLModuleCnt;
        strValue += _T(", ");
        strValue += m_strLLSlotCnt;
        strValue += _T(", ");
        strValue += m_strPMModuleCnt;
        strValue += _T(", ");
        strValue += m_strPMSlotCnt;
        strValue += _T(", ");
        strValue += m_strVacArmCnt;
        strValue += _T("\n");
        cfile.Write(strValue, strValue.GetLength() * sizeof(TCHAR));

        strValue = _T("/////////////////////////////////////////////////////");
        cfile.Write(strValue, strValue.GetLength() * sizeof(TCHAR));

        cfile.Close();
    }

}

void C주성Dlg::OnBnClickedButtonLoadThroughput()
{
    CFileDialog fileDlg(1, _T("*.csv")
        , 0
        , OFN_OVERWRITEPROMPT | OFN_LONGNAMES | OFN_FILEMUSTEXIST
        , _T("Result Files (*.csv)|*.csv||"));
    if (fileDlg.DoModal() == IDOK)
    {
        ShellExecute(NULL, _T("open"), fileDlg.GetPathName(), NULL, NULL, SW_SHOW);
    }
}


void C주성Dlg::OnBnClickedClear()
{
    DWORD A = 0;
    TerminateThread(g_hThread1[0], A);
    TerminateThread(g_hThread1[1], A);
    TerminateThread(g_hThread2, A);
    TerminateThread(g_hThread3, A);
    TerminateThread(g_hThread4, A);
    TerminateThread(g_hThread_Thread_Start, A);
    for (int i = 0; i < 4; i++)
    {
        TerminateThread(g_hThread_LL[i], A);
    }
    for (int i = 0; i < 6; i++)
    {
        TerminateThread(g_hThread_PM[i], A);
    }
    Sleep(100);
    m_nWafer_Count = 0; //장비에 집어넣은 웨이퍼 현재 개수
    m_nLLMAX = 0; //LL의 방 개수 x 웨이퍼 개수= LL이 수용할수 있는 최대치
    m_noutput_count = 0; // output에 들어오는 웨이퍼를 담고있는 변수
    m_nThread1_LL = 0; //쓰레드 1번에서 사용 하고 어떤 LL을 사용해야 할지 파악하는 변수 
    m_nThread2_LL = 0; //쓰레드 2번에서 사용 하고 어떤 LL을 사용해야 할지 파악하는 변수 
    for (int i = 0; i < 10; i++)
    {
        m_nThread3_PM[i] = 0;
    }
    m_nLL_Thread = 0;
    for (int i = 0; i < 4; i++)
    {
        m_nWafer_Process[i] = 0;
    }
    m_Thread3start = 0;		//3번 쓰레드 부르는 타이밍
    m_bTime_STOP = true;
    m_nWafer_Count = 0;

    g_pMainDlg->m_ctrTotal_Clean_Time.SetWindowText(_T("00:00:00:00"));
    g_pMainDlg->m_ctrlStaticTotalTime.SetWindowText(_T("00:00:00:00"));

    m_bLL_Dummy = false;
    m_bClean_Time_Start = false;
    m_bPM_Thread_Check = false;

    m_nPM_Thread2 = 0;
    m_nPM_Processing = 0;
    m_noutput_count = 0;
    m_nThread1_LL = 0;
    m_nThread2_LL = 0;
    m_nThread3_LL = 1;
    m_nThread4_LL = 1;
    m_nThread_Time_Error = 0;
    m_Thread3start = 0;
    m_ctrLL1.SetWindowInt(0);
    m_ctrLL2.SetWindowInt(0);
    m_ctrLL3.SetWindowInt(0);
    m_ctrLL4.SetWindowInt(0);
    m_ctrPM1.SetWindowInt(0);
    m_ctrPM2.SetWindowInt(0);
    m_ctrPM3.SetWindowInt(0);
    m_ctrPM4.SetWindowInt(0);
    m_ctrPM5.SetWindowInt(0);
    m_ctrPM6.SetWindowInt(0);
    m_ctrLPMUI1.SetWindowInt(25);
    m_ctrLPMUI2.SetWindowInt(0);
    m_ctrPROGRESS_LL1.SetPos(0);
    m_ctrPROGRESS_LL2.SetPos(0);
    m_ctrPROGRESS_LL3.SetPos(0);
    m_ctrPROGRESS_LL4.SetPos(0);
    m_ctrPROGRESS_PM1.SetPos(0);
    m_ctrPROGRESS_PM2.SetPos(0);
    m_ctrPROGRESS_PM3.SetPos(0);
    m_ctrPROGRESS_PM4.SetPos(0);
    m_ctrPROGRESS_PM5.SetPos(0);
    m_ctrPROGRESS_PM6.SetPos(0);
    m_ctrOutput.SetWindowInt(0);
    m_ctrPM_Count1.SetWindowInt(0);
    m_ctrPM_Count2.SetWindowInt(0);
    m_ctrPM_Count3.SetWindowInt(0);
    m_ctrPM_Count4.SetWindowInt(0);
    m_ctrPM_Count5.SetWindowInt(0);
    m_ctrPM_Count6.SetWindowInt(0);
    m_CtrStatic_PM1.SetWindowInt(0);
    m_CtrStatic_PM2.SetWindowInt(0);
    m_CtrStatic_PM3.SetWindowInt(0);
    m_CtrStatic_PM4.SetWindowInt(0);
    m_CtrStatic_PM5.SetWindowInt(0);
    m_CtrStatic_PM6.SetWindowInt(0);
    m_ctrlStaticTotalTime.SetFont(&m_fontTime, TRUE);
    m_ctrTotal_Clean_Time.SetFont(&m_fontTime, TRUE);
    m_nATM_Pick = 4000;
    m_nATM_Place = 4000;
    m_nATM_Rotate = 1000;
    m_nATM_ZRotate = 1000;
    m_nLL_Pump = 15000;
    m_nLL_Pump_Stable_Time = 5000;
    m_nLL_Vent = 15000;
    m_nLL_Vent_Stable_Time = 5000;
    m_nLL_Slot_Valve_Open = 2000;
    m_nLL_Slot_Valve_Close = 2000;
    m_nLL_Door_Valve_Open = 2000;
    m_nLL_Door_Valve_Close = 2000;
    m_nVAC_Pick = 5000;
    m_nVAC_Place = 5000;
    m_nRotate = 5000;
    m_nPM_Time = 600000;
    m_nPM_Clean_Time = 1200000;
    m_nPM_Clean_Wafer_Count = 10;
    m_nPM_Slot_Valve_Open = 2000;
    m_nPM_Slot_Valve_Close = 2000;

    GetDlgItem(IDC_START)->SetWindowText(_T("START"));
    GetDlgItem(IDC_START)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON_SAVE_SYSTEMCONFIG)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON_LOAD_SYSTEMCONFIG)->EnableWindow(TRUE);
    GetDlgItem(IDC_BUTTON_SAVE_THROUGHPUT)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON_LOAD_THROUGHPUT)->EnableWindow(TRUE);
    GetDlgItem(IDC_SYSTEM_INFO)->EnableWindow(TRUE);
    CString strImage;

    strImage.Format(_T("UI\\EFEM1\\슬라이드1.png"));
    g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Ctrl_Gui_EFEM, strImage);
    strImage.Format(_T("UI\\TM(Quad)\\슬라이드1.png"));
    g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Gui_TM, strImage);
    strImage.Format(_T("UI\\PM_Left\\슬라이드1.png"));
    g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Ctrl_Gui_PM1, strImage);
    strImage.Format(_T("UI\\PM_Left\\슬라이드1.png"));
    g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Ctrl_Gui_PM2, strImage);
    strImage.Format(_T("UI\\PM_Upper\\슬라이드1.png"));
    g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Ctrl_Gui_PM3, strImage);
    strImage.Format(_T("UI\\PM_Upper\\슬라이드1.png"));
    g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Ctrl_Gui_PM4, strImage);
    strImage.Format(_T("UI\\PM_Right\\슬라이드1.png"));
    g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Ctrl_Gui_PM5, strImage);
    strImage.Format(_T("UI\\PM_Right\\슬라이드1.png"));
    g_pMainDlg->DrawSemiconductor(&g_pMainDlg->m_Ctrl_Gui_PM6, strImage);

    g_pMainDlg->InvalidateRect(g_CRtemp, false);

    UpdateData(0);

}

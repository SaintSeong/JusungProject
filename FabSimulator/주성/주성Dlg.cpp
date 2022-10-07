
// 주성Dlg.cpp: 구현 파일
//
#include "pch.h"
#include "framework.h"
#include "주성.h"
#include "주성Dlg.h"
#include "afxdialogex.h"
#include "CDlg_SYSINIT.h"
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
CDlg_SYSINIT* g_pSubDlg;
CRect g_CRtemp(0, 0, 2, 2);/*
CRect g_CR_LL1(940, 130, 1080, 300);
CRect g_CR_LL2(1100, 137, 1240, 300);
CRect g_CR_LL3(940, 360, 1080, 530);
CRect g_CR_LL4(1100, 360, 1240, 530);*/
HANDLE g_hEventStart;
HANDLE g_hEventLL_Modul_one_Thread4and1;
HANDLE g_hEventLL_Modul_one_Thread1and2;
HANDLE g_hEventcount;
HANDLE g_hEventThread_Time_Error; //쓰레드 시간이 안맞을때 관리하는 이벤트
HANDLE g_hEventThread4_wait;
HANDLE g_hEvent_PM_MAX;
// C주성Dlg 대화 상자
C주성Dlg::C주성Dlg(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_MAINVIEW, pParent)
    , m_strLLWaferCount(_T(""))
    , m_strLLRoomCount(_T(""))
    , m_strTMCount(_T(""))
    , m_strPMModuleCount(_T(""))
    , m_strPMWaferCount(_T(""))
    , m_strLLModuleCnt(_T("1"))
    , m_strLLSlotCnt(_T("1"))
    , m_strVacArmCnt(_T("2"))
    , m_strPMModuleCnt(_T("1"))
    , m_strPMSlotCnt(_T("1"))

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
    DDX_Control(pDX, IDC_PM1, m_ctrPM1);
    DDX_Control(pDX, IDC_PM2, m_ctrPM2);
    DDX_Control(pDX, IDC_PM3, m_ctrPM3);
    DDX_Control(pDX, IDC_PM4, m_ctrPM4);
    DDX_Control(pDX, IDC_PM5, m_ctrPM5);
    DDX_Control(pDX, IDC_PM6, m_ctrPM6);
    DDX_Control(pDX, IDC_OUTPUT, m_ctrOUTPUT);
    DDX_Control(pDX, IDC_LPM, m_ctrLPM);
    DDX_Control(pDX, IDC_LL1, m_ctrLL1);
    // PM 스태틱 컨트롤
    DDX_Control(pDX, IDC_STATIC_PM1, m_CtrStatic_PM1);
    DDX_Control(pDX, IDC_STATIC_PM2, m_CtrStatic_PM2);
    DDX_Control(pDX, IDC_STATIC_PM3, m_CtrStatic_PM3);
    DDX_Control(pDX, IDC_STATIC_PM4, m_CtrStatic_PM4);
    DDX_Control(pDX, IDC_STATIC_PM5, m_CtrStatic_PM5);
    DDX_Control(pDX, IDC_STATIC_PM6, m_CtrStatic_PM6);
    // 콤보박스 컨트롤
    DDX_Control(pDX, IDC_COMBO_SPEED, m_ctrSpeed);
    DDX_Control(pDX, IDC_LL_WAFER, m_ctrLLWaferCount);
    DDX_Control(pDX, IDC_LL_ROOM, m_ctrLLRoomCount);
    DDX_Control(pDX, IDC_TM_ARM, m_ctrTMWaferCount);
    DDX_Control(pDX, IDC_PM_MODUL, m_ctrPMModuleCount);
    DDX_Control(pDX, IDC_PM_WAFER, m_ctrPMWaferCount);
    // 콤보박스 값
    DDX_CBString(pDX, IDC_COMBO_SPEED, m_strSpeed);
    DDX_CBString(pDX, IDC_LL_WAFER, m_strLLWaferCount);
    DDX_CBString(pDX, IDC_LL_ROOM, m_strLLRoomCount);
    DDX_CBString(pDX, IDC_TM_ARM, m_strTMCount);
    DDX_CBString(pDX, IDC_PM_MODUL, m_strPMModuleCount);
    DDX_CBString(pDX, IDC_PM_WAFER, m_strPMWaferCount);
    DDX_Control(pDX, IDC_LL2, m_ctrLL2);
    DDX_Control(pDX, IDC_LL3, m_ctrLL3);
    DDX_Control(pDX, IDC_LL4, m_ctrLL4);
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
}

BEGIN_MESSAGE_MAP(C주성Dlg, CDialogEx)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_WM_CLOSE()
    ON_CBN_SELCHANGE(IDC_TM_ARM, &C주성Dlg::OnCbnSelchangeTmArm)
    ON_CBN_SELCHANGE(IDC_LL_WAFER, &C주성Dlg::OnCbnSelchangeLlWafer)
    ON_CBN_SELCHANGE(IDC_PM_WAFER, &C주성Dlg::OnCbnSelchangePmWafer)
    ON_CBN_SELCHANGE(IDC_LL_ROOM, &C주성Dlg::OnCbnSelchangeLlRoom)
    ON_CBN_SELCHANGE(IDC_PM_MODUL, &C주성Dlg::OnCbnSelchangePmModul)
    ON_BN_CLICKED(IDC_SYS_INITIAL, &C주성Dlg::OnBnClickedSysInitial)
    ON_BN_CLICKED(IDC_START, &C주성Dlg::OnBnClickedStart)
    ON_BN_CLICKED(IDC_BUTTON_SAVE_SYSTEMCONFIG, &C주성Dlg::OnBnClickedButtonSaveSystemconfig)
    ON_BN_CLICKED(IDC_BUTTON_SAVE_THROUGHPUT, &C주성Dlg::OnBnClickedButtonSaveThroughput)
    ON_COMMAND(IDC_SET_SPEED, &C주성Dlg::OnBnClickedSetSpeed)
    ON_WM_RBUTTONDOWN()
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
    g_hEventThread4_wait = CreateEvent(NULL, FALSE, FALSE, NULL);
    g_hEvent_PM_MAX = CreateEvent(NULL, FALSE, FALSE, NULL);
    g_hEventLL_Modul_one_Thread4and1= CreateEvent(NULL, FALSE, FALSE, NULL);
    m_ctrLLRoomCount.AddString(_T("1"));
    m_ctrLLRoomCount.AddString(_T("2"));
    m_ctrLLRoomCount.AddString(_T("3"));
    m_ctrLLRoomCount.AddString(_T("4"));

    m_ctrLLWaferCount.AddString(_T("2"));
    m_ctrLLWaferCount.AddString(_T("4"));
    m_ctrLLWaferCount.AddString(_T("6"));

    m_ctrPMWaferCount.AddString(_T("2"));
    m_ctrPMWaferCount.AddString(_T("4"));
    m_ctrPMWaferCount.AddString(_T("6"));

    m_ctrTMWaferCount.AddString(_T("2"));
    m_ctrTMWaferCount.AddString(_T("4"));

    m_ctrPMModuleCount.AddString(_T("1"));
    m_ctrPMModuleCount.AddString(_T("2"));
    m_ctrPMModuleCount.AddString(_T("3"));
    m_ctrPMModuleCount.AddString(_T("4"));
    m_ctrPMModuleCount.AddString(_T("5"));
    m_ctrPMModuleCount.AddString(_T("6"));

    m_ctrSpeed.AddString(_T("20"));
    m_ctrSpeed.AddString(_T("30"));
    m_ctrSpeed.AddString(_T("40"));
    m_ctrSpeed.AddString(_T("50"));

    m_strLLWaferCount = (_T("6"));
    m_strLLRoomCount = (_T("4"));
    m_strTMCount = (_T("4"));
    m_strPMModuleCount = (_T("6"));
    m_strPMWaferCount = (_T("6"));
    m_strSpeed = _T("50");

    m_noutput_count = 0;
    m_nThread1_LL = 0;
    m_nThread2_LL = 0;
    m_nThread3_LL = 1;
    m_nThread3_PM = 1;
    m_nThread4_LL = 1;
    m_nThread_Time_Error = 0;
    m_Thread3start = 0;

    m_nATM_Pick = 4000;
    m_nATM_Place = 4000;
    m_nATM_Rotate = 500;
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

    m_font.CreateFont(45,// nHeight 
        40, // nWidth                               
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
    m_ctrlStaticTotalTime.SetFont(&m_font, TRUE);

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
        //핑크 255,100,200
        CDC* pDC = g_pMainDlg->GetDC();
        if (true)//LPM1
        {
            CBrush brush;
            CBrush* oldBrush;
            brush.CreateSolidBrush(RGB(0, 255, 0));    
            oldBrush = pDC->SelectObject(&brush);

            for (int i = 24; i >= 0; i--)
            {
                pDC->Rectangle(55, 140 + (14.6 * i), 121, 154.6 + (14.6 * i));
            }
        }
        if (true)//LPM2
        {

            
            CBrush brush;
            CBrush* oldBrush;
            brush.CreateSolidBrush(RGB(0, 255, 0));    
            oldBrush = pDC->SelectObject(&brush);

            for (int i = 24; i >= 0; i--)
            {
                pDC->Rectangle(160, 140 + (14.6 * i), 225, 154.6 + (14.6 * i));
            }

        }
        if (true)//LPM3
        {

            
            CBrush brush;
            CBrush* oldBrush;
            brush.CreateSolidBrush(RGB(0, 255, 0));    
            oldBrush = pDC->SelectObject(&brush);

            for (int i = 24; i >= 0; i--)
            {
                pDC->Rectangle(265, 140 + (14.6 * i), 330, 154.6 + (14.6 * i));
            }

        }
        if (true)//LL1 빈공간
        {
            
            CBrush brush;
            CBrush* oldBrush;
            brush.CreateSolidBrush(RGB(140, 140, 140));     // 공정 전
            oldBrush = pDC->SelectObject(&brush);

            for (int i = _ttoi(m_strLLWaferCount)-1; i >= 0; i--)
            {
                pDC->Rectangle(950, 139 + (21.8 * i), 1077, 160.8 + (21.8 * i));
            }

        }
        if (true)//LL1
        {
            CBrush brush;
            CBrush* oldBrush;
            brush.CreateSolidBrush(RGB(0, 255, 0));     // 공정 전
            oldBrush = pDC->SelectObject(&brush);

            for (int i = m_ctrLL1.GetWindowInt()-1; i >= 0; i--)
            {
                pDC->Rectangle(950, 139 + (21.8 * i), 1077, 160.8 + (21.8 * i));
            }

        }
        if (true)//LL1 의 공정 끝낸 웨이퍼 개수
        {
            CBrush brush;
            CBrush* oldBrush;
            brush.CreateSolidBrush(RGB(0, 0, 255));     // 공정 전
            oldBrush = pDC->SelectObject(&brush);

            for (int i = m_nWafer_Process[0] - 1; i >= 0; i--)
            {
                pDC->Rectangle(950, 139 + (21.8 * i), 1077, 160.8 + (21.8 * i));
            }

        }
        if (true)//LL2 빈공간
        {

            CBrush brush;
            CBrush* oldBrush;
            brush.CreateSolidBrush(RGB(140, 140, 140));     // 공정 전
            oldBrush = pDC->SelectObject(&brush);

            for (int i = _ttoi(m_strLLWaferCount)-1; i >= 0; i--)
            {
                pDC->Rectangle(1103, 139 + (21.8 * i), 1229, 160.8 + (21.8 * i));

            }

        }
        
        if (true)//LL2
        {

            CBrush brush;
            CBrush* oldBrush;
            brush.CreateSolidBrush(RGB(0, 255, 0));     // 공정 전
            oldBrush = pDC->SelectObject(&brush);

            for (int i = m_ctrLL2.GetWindowInt() - 1; i >= 0; i--)
            {
                pDC->Rectangle(1103, 139 + (21.8 * i), 1229, 160.8 + (21.8 * i));
                
            }

        }
        if (true)//LL2 의 공정 끝낸 웨이퍼 개수
        {

            CBrush brush;
            CBrush* oldBrush;
            brush.CreateSolidBrush(RGB(0, 0, 255));    
            oldBrush = pDC->SelectObject(&brush);

            for (int i = m_nWafer_Process[1] - 1; i >= 0; i--)
            {
                pDC->Rectangle(1103, 139 + (21.8 * i), 1229, 160.8 + (21.8 * i));

            }

        }
        if (true)//LL3 빈공간
        {

            CBrush brush;
            CBrush* oldBrush;
            brush.CreateSolidBrush(RGB(140, 140, 140));     // 공정 전
            oldBrush = pDC->SelectObject(&brush);

            for (int i = _ttoi(m_strLLWaferCount)-1; i >= 0; i--)
            {
                pDC->Rectangle(950, 364 + (22.5 * i), 1077, 386.5 + (22.5 * i));

            }

        }
        if (true)//LL3
        {

            CBrush brush;
            CBrush* oldBrush;
            brush.CreateSolidBrush(RGB(0, 255, 0));     // 공정 전
            oldBrush = pDC->SelectObject(&brush);

            for (int i = m_ctrLL3.GetWindowInt() - 1; i >= 0; i--)
            {
                pDC->Rectangle(950, 364 + (22.5 * i), 1077, 386.5 + (22.5 * i));
               
            }

        }
        if (true)//LL3 의 공정끝낸 웨이퍼 개수
        {

            CBrush brush;
            CBrush* oldBrush;
            brush.CreateSolidBrush(RGB(0, 0, 255));     
            oldBrush = pDC->SelectObject(&brush);

            for (int i = m_nWafer_Process[2] - 1; i >= 0; i--)
            {
                pDC->Rectangle(950, 364 + (22.5 * i), 1077, 386.5 + (22.5 * i));

            }

        }
        if (true)//LL4 빈공간
        {
            CBrush brush;
            CBrush* oldBrush;
            brush.CreateSolidBrush(RGB(140, 140, 140));     // 공정 전
            oldBrush = pDC->SelectObject(&brush);

            for (int i = _ttoi(m_strLLWaferCount)-1; i >= 0; i--)
            {
                pDC->Rectangle(1103, 364 + (22.5 * i), 1229, 386.5 + (22.5 * i));

            }

        }
        if (true)//LL4
        {

            CBrush brush;
            CBrush* oldBrush;
            brush.CreateSolidBrush(RGB(0, 255, 0));     // 공정 전
            oldBrush = pDC->SelectObject(&brush);

            for (int i = m_ctrLL4.GetWindowInt() - 1; i >= 0; i--)
            {
                pDC->Rectangle(1103, 364 + (22.5 * i), 1229, 386.5 + (22.5 * i));
               
            }

        }
        if (true)//LL4 의 공정끝낸 웨이퍼 개수
        {

            CBrush brush;
            CBrush* oldBrush;
            brush.CreateSolidBrush(RGB(0, 0, 255));     // 공정 전
            oldBrush = pDC->SelectObject(&brush);

            for (int i = m_nWafer_Process[3] - 1; i >= 0; i--)
            {
                pDC->Rectangle(1103, 364 + (22.5 * i), 1229, 386.5 + (22.5 * i));

            }

        }
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
DWORD WINAPI Thread_1_LPM2LL(LPVOID p)
 {
    int nLPM_cnt;
    int nLL_cnt;
    int nEFEM_cnt;
    int nINPUT_cnt;
    int nAligner_cnt;
   

    nLPM_cnt = g_pMainDlg->m_ctrLPM.GetWindowInt();
    if (g_pMainDlg->m_strLLRoomCount == _T("1"))
    {
        if ((g_pMainDlg->m_ctrLL1.GetWindowInt() == 0 && g_pMainDlg->m_ctrPM1.GetWindowInt() == 0))
            g_pMainDlg->m_nThread1_LL = 0;

    }
    else if (g_pMainDlg->m_strLLRoomCount == _T("2"))
    {
        if ((g_pMainDlg->m_ctrLL1.GetWindowInt() == 0 && g_pMainDlg->m_ctrPM1.GetWindowInt() == 0))
            g_pMainDlg->m_nThread1_LL = 0;
        else if ((g_pMainDlg->m_ctrLL2.GetWindowInt() == 0 && g_pMainDlg->m_nThread1_LL == 0))
            g_pMainDlg->m_nThread1_LL = 1;
        else if ((g_pMainDlg->m_ctrLL1.GetWindowInt() == 0 && g_pMainDlg->m_nThread1_LL == 1))
            g_pMainDlg->m_nThread1_LL = 0;
    }
    else if (g_pMainDlg->m_strLLRoomCount == _T("3"))
    {
        if ((g_pMainDlg->m_ctrLL1.GetWindowInt() == 0 && g_pMainDlg->m_ctrPM1.GetWindowInt() == 0))
            g_pMainDlg->m_nThread1_LL = 0;
        else if ((g_pMainDlg->m_ctrLL2.GetWindowInt() == 0 && g_pMainDlg->m_nThread1_LL == 0))
            g_pMainDlg->m_nThread1_LL = 1;
        else if ((g_pMainDlg->m_ctrLL3.GetWindowInt() == 0 && g_pMainDlg->m_nThread1_LL == 1))
            g_pMainDlg->m_nThread1_LL = 2;
        else if ((g_pMainDlg->m_ctrLL1.GetWindowInt() == 0 && g_pMainDlg->m_nThread1_LL == 2))
            g_pMainDlg->m_nThread1_LL = 0;
    }
    else if (g_pMainDlg->m_strLLRoomCount == _T("4"))
    {
        if ((g_pMainDlg->m_ctrLL1.GetWindowInt() == 0 && g_pMainDlg->m_ctrPM1.GetWindowInt() == 0 && g_pMainDlg->m_nThread1_LL != 1)||(g_pMainDlg->m_ctrLL1.GetWindowInt() == 0 && g_pMainDlg->m_Thread3start==1))
            g_pMainDlg->m_nThread1_LL = 0;
        else if ((g_pMainDlg->m_ctrLL2.GetWindowInt() == 0 && g_pMainDlg->m_nThread1_LL == 0))
            g_pMainDlg->m_nThread1_LL = 1;
        else if ((g_pMainDlg->m_ctrLL3.GetWindowInt() == 0 && g_pMainDlg->m_nThread1_LL == 1))
            g_pMainDlg->m_nThread1_LL = 2;
        else if ((g_pMainDlg->m_ctrLL4.GetWindowInt() == 0 && g_pMainDlg->m_nThread1_LL == 2))
            g_pMainDlg->m_nThread1_LL = 3;
        else if ((g_pMainDlg->m_ctrLL1.GetWindowInt() == 0 && g_pMainDlg->m_nThread1_LL == 3))
            g_pMainDlg->m_nThread1_LL = 0;
    }
    if (g_pMainDlg->m_Thread3start==1)
        g_pMainDlg->m_nThread1_LL = g_pMainDlg->m_nThread4_LL-1;

    nINPUT_cnt = g_pMainDlg->m_ctrLPM.GetWindowInt();
    if (g_pMainDlg->m_nThread1_LL == 0)
        nLL_cnt = g_pMainDlg->m_ctrLL1.GetWindowInt();
    else if (g_pMainDlg->m_nThread1_LL == 1)
        nLL_cnt = g_pMainDlg->m_ctrLL2.GetWindowInt();
    else if (g_pMainDlg->m_nThread1_LL == 2)
        nLL_cnt = g_pMainDlg->m_ctrLL3.GetWindowInt();
    else if (g_pMainDlg->m_nThread1_LL == 3)
        nLL_cnt = g_pMainDlg->m_ctrLL4.GetWindowInt();
   /* if (g_pMainDlg->m_nThread_Time_Error == _ttoi(g_pMainDlg->m_strLLRoomCount))
    {
        if (g_pMainDlg->m_nThread1_LL == 0)
        {
            for (int i = 1; i <= 50; i++)
            {
                g_pMainDlg->m_ctrPROGRESS_LL1.SetPos(i);
                Sleep(g_pMainDlg->m_nLL_Pump / (g_pMainDlg->m_nSpeed * 50));
                Sleep(g_pMainDlg->m_nLL_Pump_Stable_Time / (g_pMainDlg->m_nSpeed * 50));
            }
        }
        else if (g_pMainDlg->m_nThread1_LL == 1)
        {
            for (int i = 1; i <= 50; i++)
            {
                g_pMainDlg->m_ctrPROGRESS_LL2.SetPos(i);
                Sleep(g_pMainDlg->m_nLL_Pump / (g_pMainDlg->m_nSpeed * 50));
                Sleep(g_pMainDlg->m_nLL_Pump_Stable_Time / (g_pMainDlg->m_nSpeed * 50));
            }
        }
        else if (g_pMainDlg->m_nThread1_LL == 2)
        {
            for (int i = 1; i <= 50; i++)
            {
                g_pMainDlg->m_ctrPROGRESS_LL3.SetPos(i);
                Sleep(g_pMainDlg->m_nLL_Pump / (g_pMainDlg->m_nSpeed * 50));
                Sleep(g_pMainDlg->m_nLL_Pump_Stable_Time / (g_pMainDlg->m_nSpeed * 50));
            }
        }
        else if (g_pMainDlg->m_nThread1_LL == 3)
        {
            for (int i = 1; i <= 50; i++)
            {
                g_pMainDlg->m_ctrPROGRESS_LL4.SetPos(i);
                Sleep(g_pMainDlg->m_nLL_Pump / (g_pMainDlg->m_nSpeed * 50));
                Sleep(g_pMainDlg->m_nLL_Pump_Stable_Time / (g_pMainDlg->m_nSpeed * 50));
            }
        }
    }*/

    //1. PICK : LPM -> ATM ROBOT
    Sleep(g_pMainDlg->m_nATM_Pick / g_pMainDlg->m_nSpeed);
    for (int i = 0;; i++)
    {
        if (nLL_cnt == g_pMainDlg->m_nLLMAX / _ttoi(g_pMainDlg->m_strLLRoomCount)) break;  //LL이 꽉 찼다면 wafer 잡지마
        if (nLL_cnt == nINPUT_cnt) break;  //LL에 있는 wafer 공정 끝날 때까지 잡지 말고 대기

        g_pMainDlg->m_ctrLPM.SetWindowInt(nLPM_cnt);
        g_pMainDlg->m_ctrEFEM.SetWindowInt(i);

        //모든 LL과 모든 PM의 슬롯이 가득차 있으면 더 넣지않는다.
        if (g_pMainDlg->m_nWafer_Count == (_ttoi(g_pMainDlg->m_strPMModuleCount) * _ttoi(g_pMainDlg->m_strPMWaferCount)) + g_pMainDlg->m_nLLMAX) break;

        g_pMainDlg->m_nWafer_Count = g_pMainDlg->m_nWafer_Count + i;

        if (nLPM_cnt == 0) break;  //LPM에 남아있는 wafer가 없다
        if (i == 1) break;  //ATM ROBOT이 wafer를 한 개씩 잡는다

        nLPM_cnt--;

    }

    nEFEM_cnt = g_pMainDlg->m_ctrEFEM.GetWindowInt();
    nLPM_cnt = g_pMainDlg->m_ctrLPM.GetWindowInt();

    //2. PLACE : ATM ROBOT -> ALIGNER
    Sleep(g_pMainDlg->m_nATM_Rotate / g_pMainDlg->m_nSpeed);
    Sleep(g_pMainDlg->m_nATM_ZRotate / g_pMainDlg->m_nSpeed);
    Sleep(g_pMainDlg->m_nATM_Place / g_pMainDlg->m_nSpeed);
    for (int i = 0; ; i++)
    {
        if (nLL_cnt == g_pMainDlg->m_nLLMAX / _ttoi(g_pMainDlg->m_strLLRoomCount)) break;  //LL이 꽉 찼다면 wafer 잡지마
        if (nLL_cnt == nINPUT_cnt) break;  //LL에 있는 wafer 공정 끝날 때까지 잡지 말고 대기

        g_pMainDlg->m_ctrEFEM.SetWindowInt(nEFEM_cnt);
        g_pMainDlg->m_ctrALIGNER.SetWindowInt(i);

        if (nEFEM_cnt == 0) break;  //EFEM(ATM ROBOT)에 남아있는 wafer가 없다
        if (i == 1) break;  //ATM ROBOT이 wafer를 한 개씩 잡는다

        nEFEM_cnt--;

    }

    //3. PICK & PLACE (LPM -> ATM ROBOT -> LL)
    while (nLPM_cnt != 0 && nLL_cnt != (g_pMainDlg->m_nLLMAX / _ttoi(g_pMainDlg->m_strLLRoomCount)) - 1)
    {
        
        
        //한번에 LL과 PM에 넣을 수 있는 wafer의 갯수는 같다(비례)
        if (g_pMainDlg->m_nWafer_Count == (_ttoi(g_pMainDlg->m_strPMModuleCount) * _ttoi(g_pMainDlg->m_strPMWaferCount) + g_pMainDlg->m_nLLMAX)) break;

        nLPM_cnt = g_pMainDlg->m_ctrLPM.GetWindowInt();

        //1) PICK : LPM -> ATM ROBOT
        Sleep(g_pMainDlg->m_nATM_Rotate / g_pMainDlg->m_nSpeed);
        Sleep(g_pMainDlg->m_nATM_ZRotate / g_pMainDlg->m_nSpeed);
        Sleep(g_pMainDlg->m_nATM_Pick / g_pMainDlg->m_nSpeed);
        for (int i = 0; ; i++)
        {
            if (nLL_cnt == nINPUT_cnt) break;  //LL에 있는 wafer 공정 끝날 때까지 잡지 말고 대기

            g_pMainDlg->m_ctrLPM.SetWindowInt(nLPM_cnt);
            g_pMainDlg->m_ctrEFEM.SetWindowInt(i);

            if (nLPM_cnt == 0) break;  //LPM에 남아있는 wafer가 없다

            //한번에 LL과 PM에 넣을 수 있는 wafer의 갯수는 같다(비례)
            if (g_pMainDlg->m_nWafer_Count == (_ttoi(g_pMainDlg->m_strPMModuleCount) * _ttoi(g_pMainDlg->m_strPMWaferCount) + g_pMainDlg->m_nLLMAX))break;

            g_pMainDlg->m_nWafer_Count = g_pMainDlg->m_nWafer_Count + i;

            if (i == 1) break;  //ATM ROBOT이 wafer를 한 개씩 잡는다

            nLPM_cnt--;

        }

        nAligner_cnt = g_pMainDlg->m_ctrALIGNER.GetWindowInt();

        //2) PICK : ALIGNER -> ATM ROBOT
        Sleep(g_pMainDlg->m_nATM_Rotate / g_pMainDlg->m_nSpeed);
        Sleep(g_pMainDlg->m_nATM_ZRotate / g_pMainDlg->m_nSpeed);
        Sleep(g_pMainDlg->m_nATM_Pick / g_pMainDlg->m_nSpeed);
        for (int i = 1; ; i++)
        {
            if (nLL_cnt == g_pMainDlg->m_nLLMAX / _ttoi(g_pMainDlg->m_strLLRoomCount)) break;  //LL이 꽉 찼다면 wafer 잡지마
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
        for (int i = 0;; i++)
        {
            if (nLL_cnt == g_pMainDlg->m_nLLMAX / _ttoi(g_pMainDlg->m_strLLRoomCount)) break;  //LL이 꽉 찼다면 wafer 잡지마
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
        Sleep(g_pMainDlg->m_nATM_ZRotate / g_pMainDlg->m_nSpeed);
        Sleep(g_pMainDlg->m_nATM_Place / g_pMainDlg->m_nSpeed);
        Sleep(g_pMainDlg->m_nLL_Door_Valve_Open / g_pMainDlg->m_nSpeed);
        for (int i = nLL_cnt;; i++)
        {
            if (nLL_cnt == g_pMainDlg->m_nLLMAX / _ttoi(g_pMainDlg->m_strLLRoomCount)) break;  //LL이 꽉 찼다면 wafer 잡지마
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
    for (int i = 0;; i++)
    {
        if (nLL_cnt == g_pMainDlg->m_nLLMAX / _ttoi(g_pMainDlg->m_strLLRoomCount)) break;  //LL이 꽉 찼다면 wafer 잡지마
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
    Sleep(g_pMainDlg->m_nATM_ZRotate / g_pMainDlg->m_nSpeed);
    Sleep(g_pMainDlg->m_nATM_Place / g_pMainDlg->m_nSpeed);
    Sleep(g_pMainDlg->m_nLL_Door_Valve_Open / g_pMainDlg->m_nSpeed);
    for (int i = nLL_cnt;; i++)
    {
        if (nLL_cnt == g_pMainDlg->m_nLLMAX / _ttoi(g_pMainDlg->m_strLLRoomCount)) break;  //LL이 꽉 찼다면 wafer 잡지마
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
    
    if (g_pMainDlg->m_nThread_Time_Error == _ttoi(g_pMainDlg->m_strLLRoomCount))
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
        for (int i = 1; i <= 50; i++)
        {
            g_pMainDlg->m_ctrPROGRESS_LL4.SetPos(i);
            Sleep(g_pMainDlg->m_nLL_Pump / (g_pMainDlg->m_nSpeed * 50));
            Sleep(g_pMainDlg->m_nLL_Pump_Stable_Time / (g_pMainDlg->m_nSpeed * 50));
        }
        g_pMainDlg->m_ctrPROGRESS_LL4.SetPos(0);
    }
    if (g_pMainDlg->m_nThread_Time_Error+1 == _ttoi(g_pMainDlg->m_strLLRoomCount))
        SetEvent(g_hEventThread_Time_Error);
    int nPM_MAX = _ttoi(g_pMainDlg->m_strPMWaferCount) * _ttoi(g_pMainDlg->m_strPMModuleCount);
    int PM_Count = g_pMainDlg->m_ctrPM1.GetWindowInt() +
        g_pMainDlg->m_ctrPM2.GetWindowInt() +
        g_pMainDlg->m_ctrPM3.GetWindowInt() +
        g_pMainDlg->m_ctrPM4.GetWindowInt() +
        g_pMainDlg->m_ctrPM5.GetWindowInt() +
        g_pMainDlg->m_ctrPM6.GetWindowInt();
    if (PM_Count != nPM_MAX && g_pMainDlg->m_Thread3start == 0)
    {
        CloseHandle(CreateThread(NULL, 0, Thread_2_LL2PM, 0, 0, 0));
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
    //g_pMainDlg->InvalidateRect(g_CRtemp2, false);
    
    if (g_pMainDlg->m_ctrLL1.GetWindowInt() != 0 && g_pMainDlg->m_nThread2_LL == 0)
        g_pMainDlg->m_nThread2_LL = 1;
    else if (g_pMainDlg->m_ctrLL2.GetWindowInt() != 0 && g_pMainDlg->m_nThread2_LL == 1)
        g_pMainDlg->m_nThread2_LL = 2;
    else if (g_pMainDlg->m_ctrLL3.GetWindowInt() != 0 && g_pMainDlg->m_nThread2_LL == 2)
        g_pMainDlg->m_nThread2_LL = 3;
    else if (g_pMainDlg->m_ctrLL4.GetWindowInt() != 0 && g_pMainDlg->m_nThread2_LL == 3)
        g_pMainDlg->m_nThread2_LL = 4;
    else if (g_pMainDlg->m_ctrLL1.GetWindowInt() != 0 && g_pMainDlg->m_nThread2_LL == 4)
        g_pMainDlg->m_nThread2_LL = 1;
    else if (g_pMainDlg->m_nThread2_LL == _ttoi(g_pMainDlg->m_strLLRoomCount))
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
            int nPM_MAX = _ttoi(g_pMainDlg->m_strPMWaferCount) * _ttoi(g_pMainDlg->m_strPMModuleCount);
            if (PM_Count == nPM_MAX)break;

            if (g_pMainDlg->m_nThread2_LL == 1)
                nLL_cnt = g_pMainDlg->m_ctrLL1.GetWindowInt();

            if (g_pMainDlg->m_nThread2_LL == 2)
                nLL_cnt = g_pMainDlg->m_ctrLL2.GetWindowInt();

            if (g_pMainDlg->m_nThread2_LL == 3)
                nLL_cnt = g_pMainDlg->m_ctrLL3.GetWindowInt();

            if (g_pMainDlg->m_nThread2_LL == 4)
                nLL_cnt = g_pMainDlg->m_ctrLL4.GetWindowInt();

            // if (g_pMainDlg->m_strPMModuleCount == _T("6"))

            if ((g_pMainDlg->m_ctrPM1.GetWindowInt() != _ttoi(g_pMainDlg->m_strPMWaferCount)) && _ttoi(g_pMainDlg->m_strPMModuleCount) >= 1)
                nPM_cnt = g_pMainDlg->m_ctrPM1.GetWindowInt();

            else if ((g_pMainDlg->m_ctrPM2.GetWindowInt() != _ttoi(g_pMainDlg->m_strPMWaferCount)) && _ttoi(g_pMainDlg->m_strPMModuleCount) >= 2)
                nPM_cnt = g_pMainDlg->m_ctrPM2.GetWindowInt();

            else if ((g_pMainDlg->m_ctrPM3.GetWindowInt() != _ttoi(g_pMainDlg->m_strPMWaferCount)) && _ttoi(g_pMainDlg->m_strPMModuleCount) >= 3)
                nPM_cnt = g_pMainDlg->m_ctrPM3.GetWindowInt();

            else if ((g_pMainDlg->m_ctrPM4.GetWindowInt() != _ttoi(g_pMainDlg->m_strPMWaferCount)) && _ttoi(g_pMainDlg->m_strPMModuleCount) >= 4)
                nPM_cnt = g_pMainDlg->m_ctrPM4.GetWindowInt();

            else if ((g_pMainDlg->m_ctrPM5.GetWindowInt() != _ttoi(g_pMainDlg->m_strPMWaferCount)) && _ttoi(g_pMainDlg->m_strPMModuleCount) >= 5)
                nPM_cnt = g_pMainDlg->m_ctrPM5.GetWindowInt();

            else if ((g_pMainDlg->m_ctrPM6.GetWindowInt() != _ttoi(g_pMainDlg->m_strPMWaferCount)) && _ttoi(g_pMainDlg->m_strPMModuleCount) >= 6)
                nPM_cnt = g_pMainDlg->m_ctrPM6.GetWindowInt();

            nTM_cnt = g_pMainDlg->m_ctrTM.GetWindowInt();

            //PM이 가득 찼거나, LL에 남아있는 wafer가 없다면 종료

            if (nPM_cnt == _ttoi(g_pMainDlg->m_strPMWaferCount) || (nLL_cnt == 0 && nTM_cnt == 0)) break;
            //PICK : LL -> VAC ROBOT
            Sleep(g_pMainDlg->m_nRotate / g_pMainDlg->m_nSpeed);
            Sleep(g_pMainDlg->m_nVAC_Pick / g_pMainDlg->m_nSpeed);
           
            for (int i = 0; nTM_cnt == 0; i++)
            {
                if (nPM_cnt == _ttoi(g_pMainDlg->m_strPMWaferCount)) break;  //PM이 가득 찼다면 종료
                if (g_pMainDlg->m_strTMCount == _T("4"))
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
                else if (g_pMainDlg->m_strTMCount == _T("2"))
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


                if (i == _ttoi(g_pMainDlg->m_strTMCount) / 2) break;  //TM(VAC ROBOT)이 Dual Arm일 땐 wafer 2장,
                //Quad Arm일 때 wafer를 4장 들고 있다면 대기
            }
            
            
            nTM_cnt = g_pMainDlg->m_ctrTM.GetWindowInt();
            /* if (g_pMainDlg->m_ctrPM1.GetWindowInt() < _ttoi(g_pMainDlg->m_strPMWaferCount))
                 nPM_cnt = g_pMainDlg->m_ctrPM1.GetWindowInt();

             else if (g_pMainDlg->m_ctrPM2.GetWindowInt() < _ttoi(g_pMainDlg->m_strPMWaferCount))
                 nPM_cnt = g_pMainDlg->m_ctrPM2.GetWindowInt();

             else if (g_pMainDlg->m_ctrPM3.GetWindowInt() < _ttoi(g_pMainDlg->m_strPMWaferCount))
                 nPM_cnt = g_pMainDlg->m_ctrPM3.GetWindowInt();

             else if (g_pMainDlg->m_ctrPM4.GetWindowInt() < _ttoi(g_pMainDlg->m_strPMWaferCount))
                 nPM_cnt = g_pMainDlg->m_ctrPM4.GetWindowInt();

             else if (g_pMainDlg->m_ctrPM5.GetWindowInt() < _ttoi(g_pMainDlg->m_strPMWaferCount))
                 nPM_cnt = g_pMainDlg->m_ctrPM5.GetWindowInt();

             else if (g_pMainDlg->m_ctrPM6.GetWindowInt() < _ttoi(g_pMainDlg->m_strPMWaferCount))
                 nPM_cnt = g_pMainDlg->m_ctrPM6.GetWindowInt();*/

                 //PLACE : VAC ROBOT -> PM
            Sleep(g_pMainDlg->m_nRotate / g_pMainDlg->m_nSpeed);
            Sleep(g_pMainDlg->m_nVAC_Place / g_pMainDlg->m_nSpeed);
            for (int i = nPM_cnt;; i++)
            {

                if (g_pMainDlg->m_strTMCount == _T("4"))
                {
                    if (i % 2 == 0)
                    {
                        g_pMainDlg->m_ctrTM.SetWindowInt(nTM_cnt);
                        if ((g_pMainDlg->m_ctrPM1.GetWindowInt() < _ttoi(g_pMainDlg->m_strPMWaferCount)) && _ttoi(g_pMainDlg->m_strPMModuleCount) >= 1)
                            g_pMainDlg->m_ctrPM1.SetWindowInt(i);

                        else if ((g_pMainDlg->m_ctrPM2.GetWindowInt() < _ttoi(g_pMainDlg->m_strPMWaferCount)) && _ttoi(g_pMainDlg->m_strPMModuleCount) >= 2)
                            g_pMainDlg->m_ctrPM2.SetWindowInt(i);

                        else if ((g_pMainDlg->m_ctrPM3.GetWindowInt() < _ttoi(g_pMainDlg->m_strPMWaferCount)) && _ttoi(g_pMainDlg->m_strPMModuleCount) >= 3)
                            g_pMainDlg->m_ctrPM3.SetWindowInt(i);

                        else if ((g_pMainDlg->m_ctrPM4.GetWindowInt() < _ttoi(g_pMainDlg->m_strPMWaferCount)) && _ttoi(g_pMainDlg->m_strPMModuleCount) >= 4)
                            g_pMainDlg->m_ctrPM4.SetWindowInt(i);

                        else if ((g_pMainDlg->m_ctrPM5.GetWindowInt() < _ttoi(g_pMainDlg->m_strPMWaferCount)) && _ttoi(g_pMainDlg->m_strPMModuleCount) >= 5)
                            g_pMainDlg->m_ctrPM5.SetWindowInt(i);

                        else if ((g_pMainDlg->m_ctrPM6.GetWindowInt() < _ttoi(g_pMainDlg->m_strPMWaferCount)) && _ttoi(g_pMainDlg->m_strPMModuleCount) >= 6)
                            g_pMainDlg->m_ctrPM6.SetWindowInt(i);
                    }
                }
                else if (g_pMainDlg->m_strTMCount == _T("2"))
                {
                    g_pMainDlg->m_ctrTM.SetWindowInt(nTM_cnt);
                    if ((g_pMainDlg->m_ctrPM1.GetWindowInt() < _ttoi(g_pMainDlg->m_strPMWaferCount)) && _ttoi(g_pMainDlg->m_strPMModuleCount) >= 1)
                        g_pMainDlg->m_ctrPM1.SetWindowInt(i);

                    else if ((g_pMainDlg->m_ctrPM2.GetWindowInt() < _ttoi(g_pMainDlg->m_strPMWaferCount)) && _ttoi(g_pMainDlg->m_strPMModuleCount) >= 2)
                        g_pMainDlg->m_ctrPM2.SetWindowInt(i);

                    else if ((g_pMainDlg->m_ctrPM3.GetWindowInt() < _ttoi(g_pMainDlg->m_strPMWaferCount)) && _ttoi(g_pMainDlg->m_strPMModuleCount) >= 3)
                        g_pMainDlg->m_ctrPM3.SetWindowInt(i);

                    else if ((g_pMainDlg->m_ctrPM4.GetWindowInt() < _ttoi(g_pMainDlg->m_strPMWaferCount)) && _ttoi(g_pMainDlg->m_strPMModuleCount) >= 4)
                        g_pMainDlg->m_ctrPM4.SetWindowInt(i);

                    else if ((g_pMainDlg->m_ctrPM5.GetWindowInt() < _ttoi(g_pMainDlg->m_strPMWaferCount)) && _ttoi(g_pMainDlg->m_strPMModuleCount) >= 5)
                        g_pMainDlg->m_ctrPM5.SetWindowInt(i);

                    else if ((g_pMainDlg->m_ctrPM6.GetWindowInt() < _ttoi(g_pMainDlg->m_strPMWaferCount)) && _ttoi(g_pMainDlg->m_strPMModuleCount) >= 6)
                        g_pMainDlg->m_ctrPM6.SetWindowInt(i);
                }
                //if (nTM_cnt == 0 && nLL_cnt == 0)  //PM이 가득차지 않았다면 다시 처음으로 돌아가 wafer 가져오기
                //{
                //    CloseHandle(CreateThread(NULL, 0, Thread_1_LPM2LL, 0, 0, 0));
                //    //WaitForSingleObject(g_hEventLLtoPM, INFINITE);
                //}

                if (nTM_cnt == 0) break;  //TM(VAC ROBOT)에 남아있는 wafer가 없다면 종료
                if (i == _ttoi(g_pMainDlg->m_strPMWaferCount)) break;  //PM이 가득 찼다면 종료

                nTM_cnt--;


            }
            if ((g_pMainDlg->m_ctrPM1.GetWindowInt() == _ttoi(g_pMainDlg->m_strPMWaferCount)) && _ttoi(g_pMainDlg->m_strPMModuleCount) >= 1 && g_pMainDlg->m_nPM_Thread2 == 0)
            {
                g_pMainDlg->m_nPM_Thread2++;
                g_pMainDlg->m_nPM_Processing++;
                CloseHandle(CreateThread(NULL, 0, PM, 0, 0, 0));

            }
            else if ((g_pMainDlg->m_ctrPM2.GetWindowInt() == _ttoi(g_pMainDlg->m_strPMWaferCount)) && _ttoi(g_pMainDlg->m_strPMModuleCount) >= 2 && g_pMainDlg->m_nPM_Thread2 == 1)
            {
                g_pMainDlg->m_nPM_Thread2++;
                g_pMainDlg->m_nPM_Processing++;
                CloseHandle(CreateThread(NULL, 0, PM, 0, 0, 0));

            }

            else if ((g_pMainDlg->m_ctrPM3.GetWindowInt() == _ttoi(g_pMainDlg->m_strPMWaferCount)) && _ttoi(g_pMainDlg->m_strPMModuleCount) >= 3 && g_pMainDlg->m_nPM_Thread2 == 2)
            {
                g_pMainDlg->m_nPM_Thread2++;
                g_pMainDlg->m_nPM_Processing++;
                CloseHandle(CreateThread(NULL, 0, PM, 0, 0, 0));

            }

            else if ((g_pMainDlg->m_ctrPM4.GetWindowInt() == _ttoi(g_pMainDlg->m_strPMWaferCount)) && _ttoi(g_pMainDlg->m_strPMModuleCount) >= 4 && g_pMainDlg->m_nPM_Thread2 == 3)
            {
                g_pMainDlg->m_nPM_Thread2++;
                g_pMainDlg->m_nPM_Processing++;
                CloseHandle(CreateThread(NULL, 0, PM, 0, 0, 0));

            }

            else if ((g_pMainDlg->m_ctrPM5.GetWindowInt() == _ttoi(g_pMainDlg->m_strPMWaferCount)) && _ttoi(g_pMainDlg->m_strPMModuleCount) >= 5 && g_pMainDlg->m_nPM_Thread2 == 4)
            {
                g_pMainDlg->m_nPM_Thread2++;
                g_pMainDlg->m_nPM_Processing++;
                CloseHandle(CreateThread(NULL, 0, PM, 0, 0, 0));

            }

            else if ((g_pMainDlg->m_ctrPM6.GetWindowInt() == _ttoi(g_pMainDlg->m_strPMWaferCount)) && _ttoi(g_pMainDlg->m_strPMModuleCount) >= 6 && g_pMainDlg->m_nPM_Thread2 == 5)
            {
                g_pMainDlg->m_nPM_Thread2++;
                g_pMainDlg->m_nPM_Processing++;
                CloseHandle(CreateThread(NULL, 0, PM, 0, 0, 0));

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
    int nPM_MAX = _ttoi(g_pMainDlg->m_strPMWaferCount) * _ttoi(g_pMainDlg->m_strPMModuleCount);
    //if (PM_Count == nPM_MAX &&g_pMainDlg->m_nWafer_Count==nPM_MAX+ g_pMainDlg->m_nLLMAX)
    //{
    //    

    //    //for (int i = 0; i < g_pMainDlg->m_nThread2_LL; i++)
    //    {
    //        //g_pMainDlg->MessageBox(_T("헤헿 웨이퍼 꽉찼당"));
    //        CloseHandle(CreateThread(NULL, 0, Thread_3_PM2LL, 0, 0, 0));
    //        //WaitForSingleObject(g_hEventPMtoLL, INFINITE);
    //    }
    //}

    //CloseHandle(CreateThread(NULL, 0, Thread_3_PM2LL, 0, 0, 0));
    if (_ttoi(g_pMainDlg->m_strLLRoomCount) == 1)
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

    //PICK & PLACE (PM1 -> VAC ROBOT -> LL)
    while (true)
    {

        /*if (g_pMainDlg->m_strLLRoomCount == _T("1"))
        {
            if ((g_pMainDlg->m_ctrLL1.GetWindowInt() == 0 && g_pMainDlg->m_ctrPM1.GetWindowInt() != 0))
                g_pMainDlg->m_nThread3_LL = 1;

        }
        else if (g_pMainDlg->m_strLLRoomCount == _T("2"))
        {
            if ((g_pMainDlg->m_ctrLL1.GetWindowInt() == 0 && g_pMainDlg->m_ctrPM1.GetWindowInt() != 0))
                g_pMainDlg->m_nThread3_LL = 1;
            else if ((g_pMainDlg->m_ctrLL2.GetWindowInt() == 0 && g_pMainDlg->m_nThread3_LL == 1))
                g_pMainDlg->m_nThread3_LL = 2;
            else if ((g_pMainDlg->m_ctrLL1.GetWindowInt() == 0 && g_pMainDlg->m_nThread3_LL == 2))
                g_pMainDlg->m_nThread3_LL = 1;
        }
        else if (g_pMainDlg->m_strLLRoomCount == _T("3"))
        {
            if ((g_pMainDlg->m_ctrLL1.GetWindowInt() == 0 && g_pMainDlg->m_ctrPM1.GetWindowInt() != 0))
                g_pMainDlg->m_nThread3_LL = 1;
            else if ((g_pMainDlg->m_ctrLL2.GetWindowInt() == 0 && g_pMainDlg->m_nThread3_LL == 1))
                g_pMainDlg->m_nThread3_LL = 2;
            else if ((g_pMainDlg->m_ctrLL3.GetWindowInt() == 0 && g_pMainDlg->m_nThread3_LL == 2))
                g_pMainDlg->m_nThread3_LL = 3;
            else if ((g_pMainDlg->m_ctrLL1.GetWindowInt() == 0 && g_pMainDlg->m_nThread3_LL == 3))
                g_pMainDlg->m_nThread3_LL = 1;
        }
        else if (g_pMainDlg->m_strLLRoomCount == _T("4"))
        {
            if ((g_pMainDlg->m_ctrLL1.GetWindowInt() == 0 && g_pMainDlg->m_ctrPM1.GetWindowInt() != 0))
                g_pMainDlg->m_nThread3_LL = 1;
            else if ((g_pMainDlg->m_ctrLL2.GetWindowInt() == 0 && g_pMainDlg->m_nThread3_LL == 1))
                g_pMainDlg->m_nThread3_LL = 2;
            else if ((g_pMainDlg->m_ctrLL3.GetWindowInt() == 0 && g_pMainDlg->m_nThread3_LL == 2))
                g_pMainDlg->m_nThread3_LL = 3;
            else if ((g_pMainDlg->m_ctrLL4.GetWindowInt() == 0 && g_pMainDlg->m_nThread3_LL == 3))
                g_pMainDlg->m_nThread3_LL = 4;
            else if ((g_pMainDlg->m_ctrLL1.GetWindowInt() == 0 && g_pMainDlg->m_nThread3_LL == 4))
                g_pMainDlg->m_nThread3_LL = 1;
        }*/


       
        if (g_pMainDlg->m_nThread3_PM == 1)
            nPM_cnt = g_pMainDlg->m_ctrPM1.GetWindowInt();

        if (g_pMainDlg->m_nThread3_PM == 2)
            nPM_cnt = g_pMainDlg->m_ctrPM2.GetWindowInt();

        if (g_pMainDlg->m_nThread3_PM == 3)
            nPM_cnt = g_pMainDlg->m_ctrPM3.GetWindowInt();

        if (g_pMainDlg->m_nThread3_PM == 4)
            nPM_cnt = g_pMainDlg->m_ctrPM4.GetWindowInt();

        if (g_pMainDlg->m_nThread3_PM == 5)
            nPM_cnt = g_pMainDlg->m_ctrPM5.GetWindowInt();

        if (g_pMainDlg->m_nThread3_PM == 6)
            nPM_cnt = g_pMainDlg->m_ctrPM6.GetWindowInt();


        nTM_cnt = g_pMainDlg->m_ctrTM.GetWindowInt();
        if (nPM_cnt == 0) break;  //PM에 남아있는 wafer가 없다면 종료
        if (g_pMainDlg->m_nPM_Processing == _ttoi(g_pMainDlg->m_strPMModuleCount))
        {
            ResetEvent(g_hEvent_PM_MAX);
            WaitForSingleObject(g_hEvent_PM_MAX, INFINITE);
            g_pMainDlg->m_nThread_Time_Error=0;
            g_pMainDlg->m_nThread4_LL = 1;
        }
        //PICK : PM1 -> VAC ROBOT
        Sleep(g_pMainDlg->m_nPM_Slot_Valve_Open / g_pMainDlg->m_nSpeed);
        Sleep(g_pMainDlg->m_nVAC_Pick / g_pMainDlg->m_nSpeed);
        for (int i = nTM_cnt; ; i++)
        {

            if (g_pMainDlg->m_strTMCount == _T("4"))
            {
                if (i % 2 == 0)
                {
                    g_pMainDlg->m_ctrTM.SetWindowInt(i);
                    if (g_pMainDlg->m_ctrPM1.GetWindowInt() != 0 && g_pMainDlg->m_nThread3_PM == 1)
                        g_pMainDlg->m_ctrPM1.SetWindowInt(nPM_cnt);

                    else if (g_pMainDlg->m_ctrPM2.GetWindowInt() != 0 && g_pMainDlg->m_nThread3_PM == 2)
                        g_pMainDlg->m_ctrPM2.SetWindowInt(nPM_cnt);

                    else if (g_pMainDlg->m_ctrPM3.GetWindowInt() != 0 && g_pMainDlg->m_nThread3_PM == 3)
                        g_pMainDlg->m_ctrPM3.SetWindowInt(nPM_cnt);

                    else if (g_pMainDlg->m_ctrPM4.GetWindowInt() != 0 && g_pMainDlg->m_nThread3_PM == 4)
                        g_pMainDlg->m_ctrPM4.SetWindowInt(nPM_cnt);

                    else if (g_pMainDlg->m_ctrPM5.GetWindowInt() != 0 && g_pMainDlg->m_nThread3_PM == 5)
                        g_pMainDlg->m_ctrPM5.SetWindowInt(nPM_cnt);

                    else if (g_pMainDlg->m_ctrPM6.GetWindowInt() != 0 && g_pMainDlg->m_nThread3_PM == 6)
                        g_pMainDlg->m_ctrPM6.SetWindowInt(nPM_cnt);
                }
            }
            else if (g_pMainDlg->m_strTMCount == _T("2"))
            {
                g_pMainDlg->m_ctrTM.SetWindowInt(i);
                if (g_pMainDlg->m_ctrPM1.GetWindowInt() != 0 && g_pMainDlg->m_nThread3_PM == 1)
                    g_pMainDlg->m_ctrPM1.SetWindowInt(nPM_cnt);

                else if (g_pMainDlg->m_ctrPM2.GetWindowInt() != 0 && g_pMainDlg->m_nThread3_PM == 2)
                    g_pMainDlg->m_ctrPM2.SetWindowInt(nPM_cnt);

                else if (g_pMainDlg->m_ctrPM3.GetWindowInt() != 0 && g_pMainDlg->m_nThread3_PM == 3)
                    g_pMainDlg->m_ctrPM3.SetWindowInt(nPM_cnt);

                else if (g_pMainDlg->m_ctrPM4.GetWindowInt() != 0 && g_pMainDlg->m_nThread3_PM == 4)
                    g_pMainDlg->m_ctrPM4.SetWindowInt(nPM_cnt);

                else if (g_pMainDlg->m_ctrPM5.GetWindowInt() != 0 && g_pMainDlg->m_nThread3_PM == 5)
                    g_pMainDlg->m_ctrPM5.SetWindowInt(nPM_cnt);

                else if (g_pMainDlg->m_ctrPM6.GetWindowInt() != 0 && g_pMainDlg->m_nThread3_PM == 6)
                    g_pMainDlg->m_ctrPM6.SetWindowInt(nPM_cnt);
            }
            //현재 LL에 있는 wafer의 수와 VAC ROBOT이 들고 있는 wafer 갯수의 합이
            //LL의 최대치(MAX:24장)와 같다면 PM에서 더 꺼내지 말고 대기
            //if (nLL_cnt + i == g_pMainDlg->m_nLLMAX) break;
            if (nPM_cnt == 0) break;  //PM에 남아있는 wafer가 없다면 종료

            nPM_cnt--;

            if (i == _ttoi(g_pMainDlg->m_strTMCount) / 2) break;  //TM(VAC ROBOT)이 Dual Arm일 땐 wafer 2장,
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
        Sleep(g_pMainDlg->m_nLL_Slot_Valve_Open / g_pMainDlg->m_nSpeed);
        Sleep(g_pMainDlg->m_nRotate / g_pMainDlg->m_nSpeed);
        Sleep(g_pMainDlg->m_nVAC_Pick / g_pMainDlg->m_nSpeed);
        for (int i = nTM_cnt;; i++)
        {
            if (nPM_cnt == _ttoi(g_pMainDlg->m_strPMWaferCount)) break;  //PM이 가득 찼다면 종료
            if (g_pMainDlg->m_strTMCount == _T("4"))
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
            else if (g_pMainDlg->m_strTMCount == _T("2"))
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
            if (i == _ttoi(g_pMainDlg->m_strTMCount)) break;  //TM(VAC ROBOT)이 Dual Arm일 땐 wafer 2장,
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
        for (int i = 1; ; i++)
        {
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
            Sleep(g_pMainDlg->m_nRotate / g_pMainDlg->m_nSpeed);
            Sleep(g_pMainDlg->m_nVAC_Place / g_pMainDlg->m_nSpeed);
            for (int i = nLL_cnt;; i++)
            {
                if (g_pMainDlg->m_strTMCount == _T("4"))
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
                else if (g_pMainDlg->m_strTMCount == _T("2"))
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
                //if (i == g_pMainDlg->m_nLLMAX)  //LL에 wafer가 MAX치만큼 채워졌다면 다음 실행
                //{
                //    //ResetEvent(g_hEventPMtoLL);
                //    CloseHandle(CreateThread(NULL, 0, Thread_4_LL2OUT, 0, 0, 0));
                //    WaitForSingleObject(g_hEventPMtoLL, INFINITE);
                //    break;
                //}

                if (nTM_cnt == _ttoi(g_pMainDlg->m_strTMCount) / 2) break;  //TM(VAC ROBOT)에 남아있는 wafer가 없다면 종료
                LL_Count++;
                g_pMainDlg->m_nWafer_Process[g_pMainDlg->m_nThread3_LL-1] = LL_Count;
                nTM_cnt--;
            }
            g_pMainDlg->InvalidateRect(g_CRtemp, false);
            if (LL_Count == _ttoi(g_pMainDlg->m_strLLWaferCount))
            {
                Sleep(g_pMainDlg->m_nLL_Slot_Valve_Close / g_pMainDlg->m_nSpeed);
                LL_Count = 0;
                g_pMainDlg->m_nThread3_LL++;
                g_pMainDlg->m_nLL_Thread = g_pMainDlg->m_nThread3_LL;
                g_pMainDlg->m_nThread_Time_Error++;
                CloseHandle(CreateThread(NULL, 0, LL, 0, 0, 0));
                Sleep(g_pMainDlg->m_nLL_Slot_Valve_Open / g_pMainDlg->m_nSpeed);
            }
            if (g_pMainDlg->m_nThread_Time_Error == _ttoi(g_pMainDlg->m_strLLRoomCount))
            {
                ResetEvent(g_hEventThread_Time_Error);
                WaitForSingleObject(g_hEventThread_Time_Error, INFINITE);
            }
            if (g_pMainDlg->m_nThread3_LL == _ttoi(g_pMainDlg->m_strLLRoomCount) + 1)
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
            
            for (int i = nTM_cnt;; i++)
            {
                if (nPM_cnt == _ttoi(g_pMainDlg->m_strPMWaferCount)) break;  //PM이 가득 찼다면 종료
                if (g_pMainDlg->m_strTMCount == _T("4"))
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
                else if (g_pMainDlg->m_strTMCount == _T("2"))
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

                

                if (i == _ttoi(g_pMainDlg->m_strTMCount)) break;  //TM(VAC ROBOT)이 Dual Arm일 땐 wafer 2장,
                //Quad Arm일 때 wafer를 4장 들고 있다면 대기
            }
             

            nTM_cnt = g_pMainDlg->m_ctrTM.GetWindowInt();
            if (g_pMainDlg->m_nThread3_PM == 1 && _ttoi(g_pMainDlg->m_strPMModuleCount) >= 1)
            {
                g_pMainDlg->m_nPM_Thread3 = 1;
                nPM_cnt = g_pMainDlg->m_ctrPM1.GetWindowInt();
            }
            if (g_pMainDlg->m_nThread3_PM == 2 && _ttoi(g_pMainDlg->m_strPMModuleCount) >= 2)
            {
                g_pMainDlg->m_nPM_Thread3 = 2;
                nPM_cnt = g_pMainDlg->m_ctrPM2.GetWindowInt();
            }

            if (g_pMainDlg->m_nThread3_PM == 3 && _ttoi(g_pMainDlg->m_strPMModuleCount) >= 3)
            {
                g_pMainDlg->m_nPM_Thread3 = 3;
                nPM_cnt = g_pMainDlg->m_ctrPM3.GetWindowInt();
            }

            if (g_pMainDlg->m_nThread3_PM == 4 && _ttoi(g_pMainDlg->m_strPMModuleCount) >= 4)
            {
                g_pMainDlg->m_nPM_Thread3 = 4;
                nPM_cnt = g_pMainDlg->m_ctrPM4.GetWindowInt();
            }

            if (g_pMainDlg->m_nThread3_PM == 5 && _ttoi(g_pMainDlg->m_strPMModuleCount) >= 5)
            {
                g_pMainDlg->m_nPM_Thread3 = 5;
                nPM_cnt = g_pMainDlg->m_ctrPM5.GetWindowInt();
            }

            if (g_pMainDlg->m_nThread3_PM == 6 && _ttoi(g_pMainDlg->m_strPMModuleCount) >= 6)
            {
                g_pMainDlg->m_nPM_Thread3 = 6;
                nPM_cnt = g_pMainDlg->m_ctrPM6.GetWindowInt();
            }

            //TM->PM
            Sleep(g_pMainDlg->m_nRotate / g_pMainDlg->m_nSpeed);
            Sleep(g_pMainDlg->m_nVAC_Place / g_pMainDlg->m_nSpeed);
            for (int i = nPM_cnt;; i++)
            {

                if (g_pMainDlg->m_strTMCount == _T("4"))
                {
                    if (i % 2 == 0)
                    {
                        g_pMainDlg->m_ctrTM.SetWindowInt(nTM_cnt);
                        if (g_pMainDlg->m_nThread3_PM == 1 && _ttoi(g_pMainDlg->m_strPMModuleCount) >= 1)
                            g_pMainDlg->m_ctrPM1.SetWindowInt(i);

                        if (g_pMainDlg->m_nThread3_PM == 2 && _ttoi(g_pMainDlg->m_strPMModuleCount) >= 2)
                            g_pMainDlg->m_ctrPM2.SetWindowInt(i);

                        if (g_pMainDlg->m_nThread3_PM == 3 && _ttoi(g_pMainDlg->m_strPMModuleCount) >= 3)
                            g_pMainDlg->m_ctrPM3.SetWindowInt(i);

                        if (g_pMainDlg->m_nThread3_PM == 4 && _ttoi(g_pMainDlg->m_strPMModuleCount) >= 4)
                            g_pMainDlg->m_ctrPM4.SetWindowInt(i);

                        if (g_pMainDlg->m_nThread3_PM == 5 && _ttoi(g_pMainDlg->m_strPMModuleCount) >= 5)
                            g_pMainDlg->m_ctrPM5.SetWindowInt(i);

                        if (g_pMainDlg->m_nThread3_PM == 6 && _ttoi(g_pMainDlg->m_strPMModuleCount) >= 6)
                            g_pMainDlg->m_ctrPM6.SetWindowInt(i);
                    }
                }
                else if (g_pMainDlg->m_strTMCount == _T("2"))
                {
                    g_pMainDlg->m_ctrTM.SetWindowInt(nTM_cnt);
                    if (g_pMainDlg->m_nThread3_PM == 1 && _ttoi(g_pMainDlg->m_strPMModuleCount) >= 1)
                        g_pMainDlg->m_ctrPM1.SetWindowInt(i);

                    if (g_pMainDlg->m_nThread3_PM == 2 && _ttoi(g_pMainDlg->m_strPMModuleCount) >= 2)
                        g_pMainDlg->m_ctrPM2.SetWindowInt(i);

                    if (g_pMainDlg->m_nThread3_PM == 3 && _ttoi(g_pMainDlg->m_strPMModuleCount) >= 3)
                        g_pMainDlg->m_ctrPM3.SetWindowInt(i);

                    if (g_pMainDlg->m_nThread3_PM == 4 && _ttoi(g_pMainDlg->m_strPMModuleCount) >= 4)
                        g_pMainDlg->m_ctrPM4.SetWindowInt(i);

                    if (g_pMainDlg->m_nThread3_PM == 5 && _ttoi(g_pMainDlg->m_strPMModuleCount) >= 5)
                        g_pMainDlg->m_ctrPM5.SetWindowInt(i);

                    if (g_pMainDlg->m_nThread3_PM == 6 && _ttoi(g_pMainDlg->m_strPMModuleCount) >= 6)
                        g_pMainDlg->m_ctrPM6.SetWindowInt(i);
                }
                //if (nTM_cnt == 0 && nLL_cnt == 0)  //PM이 가득차지 않았다면 다시 처음으로 돌아가 wafer 가져오기
                //{
                //    CloseHandle(CreateThread(NULL, 0, Thread_1_LPM2LL, 0, 0, 0));
                //    //WaitForSingleObject(g_hEventLLtoPM, INFINITE);
                //}

                if (nTM_cnt == 0) break;  //TM(VAC ROBOT)에 남아있는 wafer가 없다면 종료
                if (i == _ttoi(g_pMainDlg->m_strPMWaferCount)) break;  //PM이 가득 찼다면 종료
                PM_Count++;
                nTM_cnt--;

                

            }

             
            if (PM_Count == _ttoi(g_pMainDlg->m_strPMWaferCount))
            {
                Sleep(g_pMainDlg->m_nPM_Slot_Valve_Close / g_pMainDlg->m_nSpeed);
                Sleep(g_pMainDlg->m_nPM_Slot_Valve_Open / g_pMainDlg->m_nSpeed);
                PM_Count = 0;
                g_pMainDlg->m_nThread3_PM++;
                g_pMainDlg->m_nPM_Processing++;
                CloseHandle(CreateThread(NULL, 0, PM, 0, 0, 0));
            }
            
            if (g_pMainDlg->m_nThread3_PM == _ttoi(g_pMainDlg->m_strPMModuleCount) + 1)
                g_pMainDlg->m_nThread3_PM = 1;
            nTM_cnt = g_pMainDlg->m_ctrTM.GetWindowInt();
            if (g_pMainDlg->m_nThread3_PM == 1 && _ttoi(g_pMainDlg->m_strPMModuleCount) >= 1)
                nPM_cnt = g_pMainDlg->m_ctrPM1.GetWindowInt();

            if (g_pMainDlg->m_nThread3_PM == 2 && _ttoi(g_pMainDlg->m_strPMModuleCount) >= 2)
                nPM_cnt = g_pMainDlg->m_ctrPM2.GetWindowInt();

            if (g_pMainDlg->m_nThread3_PM == 3 && _ttoi(g_pMainDlg->m_strPMModuleCount) >= 3)
                nPM_cnt = g_pMainDlg->m_ctrPM3.GetWindowInt();

            if (g_pMainDlg->m_nThread3_PM == 4 && _ttoi(g_pMainDlg->m_strPMModuleCount) >= 4)
                nPM_cnt = g_pMainDlg->m_ctrPM4.GetWindowInt();

            if (g_pMainDlg->m_nThread3_PM == 5 && _ttoi(g_pMainDlg->m_strPMModuleCount) >= 5)
                nPM_cnt = g_pMainDlg->m_ctrPM5.GetWindowInt();

            if (g_pMainDlg->m_nThread3_PM == 6 && _ttoi(g_pMainDlg->m_strPMModuleCount) >= 6)
                nPM_cnt = g_pMainDlg->m_ctrPM6.GetWindowInt();
            //PM->TM
            Sleep(g_pMainDlg->m_nRotate / g_pMainDlg->m_nSpeed);
            Sleep(g_pMainDlg->m_nVAC_Pick / g_pMainDlg->m_nSpeed);
            if (g_pMainDlg->m_nPM_Processing == _ttoi(g_pMainDlg->m_strPMModuleCount))
            {
                ResetEvent(g_hEvent_PM_MAX);
                WaitForSingleObject(g_hEvent_PM_MAX, INFINITE);
            }
            for (int i = nTM_cnt; ; i++)
            {

                if (g_pMainDlg->m_strTMCount == _T("4"))
                {
                    if (i % 2 == 0)
                    {
                        g_pMainDlg->m_ctrTM.SetWindowInt(i);
                        if (g_pMainDlg->m_ctrPM1.GetWindowInt() != 0 && g_pMainDlg->m_nThread3_PM == 1)
                            g_pMainDlg->m_ctrPM1.SetWindowInt(nPM_cnt);

                        if (g_pMainDlg->m_ctrPM2.GetWindowInt() != 0 && g_pMainDlg->m_nThread3_PM == 2)
                            g_pMainDlg->m_ctrPM2.SetWindowInt(nPM_cnt);

                        if (g_pMainDlg->m_ctrPM3.GetWindowInt() != 0 && g_pMainDlg->m_nThread3_PM == 3)
                            g_pMainDlg->m_ctrPM3.SetWindowInt(nPM_cnt);

                        if (g_pMainDlg->m_ctrPM4.GetWindowInt() != 0 && g_pMainDlg->m_nThread3_PM == 4)
                            g_pMainDlg->m_ctrPM4.SetWindowInt(nPM_cnt);

                        if (g_pMainDlg->m_ctrPM5.GetWindowInt() != 0 && g_pMainDlg->m_nThread3_PM == 5)
                            g_pMainDlg->m_ctrPM5.SetWindowInt(nPM_cnt);

                        if (g_pMainDlg->m_ctrPM6.GetWindowInt() != 0 && g_pMainDlg->m_nThread3_PM == 6)
                            g_pMainDlg->m_ctrPM6.SetWindowInt(nPM_cnt);
                    }
                }
                else if (g_pMainDlg->m_strTMCount == _T("2"))
                {
                    g_pMainDlg->m_ctrTM.SetWindowInt(i);
                    if (g_pMainDlg->m_ctrPM1.GetWindowInt() != 0 && g_pMainDlg->m_nThread3_PM == 1)
                        g_pMainDlg->m_ctrPM1.SetWindowInt(nPM_cnt);

                    if (g_pMainDlg->m_ctrPM2.GetWindowInt() != 0 && g_pMainDlg->m_nThread3_PM == 2)
                        g_pMainDlg->m_ctrPM2.SetWindowInt(nPM_cnt);

                    if (g_pMainDlg->m_ctrPM3.GetWindowInt() != 0 && g_pMainDlg->m_nThread3_PM == 3)
                        g_pMainDlg->m_ctrPM3.SetWindowInt(nPM_cnt);

                    if (g_pMainDlg->m_ctrPM4.GetWindowInt() != 0 && g_pMainDlg->m_nThread3_PM == 4)
                        g_pMainDlg->m_ctrPM4.SetWindowInt(nPM_cnt);

                    if (g_pMainDlg->m_ctrPM5.GetWindowInt() != 0 && g_pMainDlg->m_nThread3_PM == 5)
                        g_pMainDlg->m_ctrPM5.SetWindowInt(nPM_cnt);

                    if (g_pMainDlg->m_ctrPM6.GetWindowInt() != 0 && g_pMainDlg->m_nThread3_PM == 6)
                        g_pMainDlg->m_ctrPM6.SetWindowInt(nPM_cnt);
                }
                //현재 LL에 있는 wafer의 수와 VAC ROBOT이 들고 있는 wafer 갯수의 합이
                //LL의 최대치(MAX:24장)와 같다면 PM에서 더 꺼내지 말고 대기
                //if (nLL_cnt + i == g_pMainDlg->m_nLLMAX) break;
                if (nPM_cnt == 0) break;  //PM에 남아있는 wafer가 없다면 종료

                nPM_cnt--;

                

                if (i == _ttoi(g_pMainDlg->m_strTMCount)) break;  //TM(VAC ROBOT)이 Dual Arm일 땐 wafer 2장,
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
            if (g_pMainDlg->m_strTMCount == _T("4"))
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
            else if (g_pMainDlg->m_strTMCount == _T("2"))
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
            //if (i == g_pMainDlg->m_nLLMAX)  //LL에 wafer가 MAX치만큼 채워졌다면 다음 실행
            //{
            //    //ResetEvent(g_hEventPMtoLL);
            //    CloseHandle(CreateThread(NULL, 0, Thread_4_LL2OUT, 0, 0, 0));
            //    WaitForSingleObject(g_hEventPMtoLL, INFINITE);
            //    break;
            //}

            if (nTM_cnt == _ttoi(g_pMainDlg->m_strTMCount) / 2) break;  //TM(VAC ROBOT)에 남아있는 wafer가 없다면 종료
            LL_Count++;
            nTM_cnt--;

        }

        if (LL_Count == _ttoi(g_pMainDlg->m_strLLWaferCount))
        {
            /*g_pMainDlg->m_nThread4_LL = g_pMainDlg->m_nThread3_LL;*/
            /*CloseHandle(CreateThread(NULL, 0, Thread_4_LL2OUT, 0, 0, 0));*/
            //g_pMainDlg->m_nThread4_Buffer[g_pMainDlg->m_nThread3_LL - 1] = 5;
            LL_Count = 0;
            g_pMainDlg->m_nThread3_LL++;
            //SetEvent(g_hEventcount);
            if (g_pMainDlg->m_nThread_Time_Error == _ttoi(g_pMainDlg->m_strLLRoomCount))
                WaitForSingleObject(g_hEventThread_Time_Error, INFINITE);
            
            
        }
        if (g_pMainDlg->m_nThread3_LL == _ttoi(g_pMainDlg->m_strLLRoomCount) + 1)
            g_pMainDlg->m_nThread3_LL = 1;

         

        nTM_cnt = g_pMainDlg->m_ctrTM.GetWindowInt();
        if (g_pMainDlg->m_nThread3_PM == 1 && _ttoi(g_pMainDlg->m_strPMModuleCount) >= 1)
            nPM_cnt = g_pMainDlg->m_ctrPM1.GetWindowInt();

        if (g_pMainDlg->m_nThread3_PM == 2 && _ttoi(g_pMainDlg->m_strPMModuleCount) >= 2)
            nPM_cnt = g_pMainDlg->m_ctrPM2.GetWindowInt();

        if (g_pMainDlg->m_nThread3_PM == 3 && _ttoi(g_pMainDlg->m_strPMModuleCount) >= 3)
            nPM_cnt = g_pMainDlg->m_ctrPM3.GetWindowInt();

        if (g_pMainDlg->m_nThread3_PM == 4 && _ttoi(g_pMainDlg->m_strPMModuleCount) >= 4)
            nPM_cnt = g_pMainDlg->m_ctrPM4.GetWindowInt();

        if (g_pMainDlg->m_nThread3_PM == 5 && _ttoi(g_pMainDlg->m_strPMModuleCount) >= 5)
            nPM_cnt = g_pMainDlg->m_ctrPM5.GetWindowInt();

        if (g_pMainDlg->m_nThread3_PM == 6 && _ttoi(g_pMainDlg->m_strPMModuleCount) >= 6)
            nPM_cnt = g_pMainDlg->m_ctrPM6.GetWindowInt();

        //TM->PM
        for (int i = nPM_cnt;; i++)
        {

            if (g_pMainDlg->m_strTMCount == _T("4"))
            {
                if (i % 2 == 0)
                {
                    g_pMainDlg->m_ctrTM.SetWindowInt(nTM_cnt);
                    if (g_pMainDlg->m_nThread3_PM == 1 && _ttoi(g_pMainDlg->m_strPMModuleCount) >= 1)
                        g_pMainDlg->m_ctrPM1.SetWindowInt(i);

                    if (g_pMainDlg->m_nThread3_PM == 2 && _ttoi(g_pMainDlg->m_strPMModuleCount) >= 2)
                        g_pMainDlg->m_ctrPM2.SetWindowInt(i);

                    if (g_pMainDlg->m_nThread3_PM == 3 && _ttoi(g_pMainDlg->m_strPMModuleCount) >= 3)
                        g_pMainDlg->m_ctrPM3.SetWindowInt(i);

                    if (g_pMainDlg->m_nThread3_PM == 4 && _ttoi(g_pMainDlg->m_strPMModuleCount) >= 4)
                        g_pMainDlg->m_ctrPM4.SetWindowInt(i);

                    if (g_pMainDlg->m_nThread3_PM == 5 && _ttoi(g_pMainDlg->m_strPMModuleCount) >= 5)
                        g_pMainDlg->m_ctrPM5.SetWindowInt(i);

                    if (g_pMainDlg->m_nThread3_PM == 6 && _ttoi(g_pMainDlg->m_strPMModuleCount) >= 6)
                        g_pMainDlg->m_ctrPM6.SetWindowInt(i);
                }
            }
            else if (g_pMainDlg->m_strTMCount == _T("2"))
            {
                g_pMainDlg->m_ctrTM.SetWindowInt(nTM_cnt);
                if (g_pMainDlg->m_nThread3_PM == 1 && _ttoi(g_pMainDlg->m_strPMModuleCount) >= 1)
                    g_pMainDlg->m_ctrPM1.SetWindowInt(i);

                if (g_pMainDlg->m_nThread3_PM == 2 && _ttoi(g_pMainDlg->m_strPMModuleCount) >= 2)
                    g_pMainDlg->m_ctrPM2.SetWindowInt(i);

                if (g_pMainDlg->m_nThread3_PM == 3 && _ttoi(g_pMainDlg->m_strPMModuleCount) >= 3)
                    g_pMainDlg->m_ctrPM3.SetWindowInt(i);

                if (g_pMainDlg->m_nThread3_PM == 4 && _ttoi(g_pMainDlg->m_strPMModuleCount) >= 4)
                    g_pMainDlg->m_ctrPM4.SetWindowInt(i);

                if (g_pMainDlg->m_nThread3_PM == 5 && _ttoi(g_pMainDlg->m_strPMModuleCount) >= 5)
                    g_pMainDlg->m_ctrPM5.SetWindowInt(i);

                if (g_pMainDlg->m_nThread3_PM == 6 && _ttoi(g_pMainDlg->m_strPMModuleCount) >= 6)
                    g_pMainDlg->m_ctrPM6.SetWindowInt(i);
            }
            //if (nTM_cnt == 0 && nLL_cnt == 0)  //PM이 가득차지 않았다면 다시 처음으로 돌아가 wafer 가져오기
            //{
            //    CloseHandle(CreateThread(NULL, 0, Thread_1_LPM2LL, 0, 0, 0));
            //    //WaitForSingleObject(g_hEventLLtoPM, INFINITE);
            //}

            if (nTM_cnt == 0) break;  //TM(VAC ROBOT)에 남아있는 wafer가 없다면 종료
            if (i == _ttoi(g_pMainDlg->m_strPMWaferCount)) break;  //PM이 가득 찼다면 종료
            PM_Count++;
            nTM_cnt--;

            

        }

        if (PM_Count == _ttoi(g_pMainDlg->m_strPMWaferCount))
        {
            g_pMainDlg->m_nThread3_PM++;
            PM_Count = 0;
        }
        if (g_pMainDlg->m_nPM_Processing + 1 == g_pMainDlg->m_strPMModuleCount)
        {
            ResetEvent(g_hEvent_PM_MAX);
            WaitForSingleObject(g_hEvent_PM_MAX, INFINITE);
        }
        if (g_pMainDlg->m_nThread3_PM == _ttoi(g_pMainDlg->m_strPMModuleCount) + 1)
            g_pMainDlg->m_nThread3_PM = 1;
        /* if (g_pMainDlg->m_ctrLL1.GetWindowInt() == g_pMainDlg->m_nLLMAX)
             CloseHandle(CreateThread(NULL, 0, Thread_4_LL2OUT, 0, 0, 0));
         if (g_pMainDlg->m_ctrLL2.GetWindowInt() == g_pMainDlg->m_nLLMAX)
             CloseHandle(CreateThread(NULL, 0, Thread_4_LL2OUT, 0, 0, 0));
         if (g_pMainDlg->m_ctrLL3.GetWindowInt() == g_pMainDlg->m_nLLMAX)
             CloseHandle(CreateThread(NULL, 0, Thread_4_LL2OUT, 0, 0, 0));
         if (g_pMainDlg->m_ctrLL4.GetWindowInt() == g_pMainDlg->m_nLLMAX)
             CloseHandle(CreateThread(NULL, 0, Thread_4_LL2OUT, 0, 0, 0));*/

             //WaitForSingleObject(g_hEventLLtoOUTPUT, INFINITE);

    }
     
    //SetEvent(g_hEventPMtoLL);
    return 0;
}
DWORD WINAPI LL(LPVOID p)
{
    int nThread4_LL = g_pMainDlg->m_nLL_Thread -1;
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
    if (_ttoi(g_pMainDlg->m_strLLRoomCount) == 1|| _ttoi(g_pMainDlg->m_strLLRoomCount) == 2)
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
        Sleep(g_pMainDlg->m_nATM_Pick / g_pMainDlg->m_nSpeed);
        Sleep(g_pMainDlg->m_nATM_Rotate / g_pMainDlg->m_nSpeed);
        
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
            g_pMainDlg->m_nWafer_Process[nThread4_LL - 1]=nLL_cnt;
            g_pMainDlg->InvalidateRect(g_CRtemp, false);
            g_pMainDlg->m_ctrEFEM.SetWindowInt(i);

            if (nLL_cnt == 0) break;  //LL에 남아있는 wafer가 없다면 종료

            nLL_cnt--;
            
            if (i == 1) break;  //ATM ROBOT이 최대로 잡을 수 있는 wafer는 2장(MAX)
        }

        nEFEM_cnt = g_pMainDlg->m_ctrEFEM.GetWindowInt();
        nOUTPUT_cnt = g_pMainDlg->m_ctrOUTPUT.GetWindowInt();
        //PLACE : ATM ROBOT -> LPM(OUTPUT)
        Sleep(g_pMainDlg->m_nATM_Place / g_pMainDlg->m_nSpeed);
        Sleep(g_pMainDlg->m_nATM_Rotate / g_pMainDlg->m_nSpeed);
        for (int i = nOUTPUT_cnt;; i++)
        {
            g_pMainDlg->m_ctrEFEM.SetWindowInt(nEFEM_cnt);
            g_pMainDlg->m_ctrOUTPUT.SetWindowInt(i);
            g_pMainDlg->m_nWafer_Count--;
            if (nEFEM_cnt == 0) break;  //EFEM(ATM ROBOT)에 남아있는 wafer가 없다

            nEFEM_cnt--; 
        }
    }
    g_pMainDlg->m_noutput_count = g_pMainDlg->m_ctrOUTPUT.GetWindowInt();
    //if (g_pMainDlg->m_noutput_count == 0)


    //g_pMainDlg->m_nThread_Time_Error--;

    SetEvent(g_hEventThread4_wait);

    return 0;
}

DWORD WINAPI PM(LPVOID p)
{
    //if 프로세스 동작 / 클린 동작 구분
    int nPM_Cheak;
    
    if (g_pMainDlg->m_bPM_Thread_Cheak == false)
    {
        if (g_pMainDlg->m_nPM_Thread2 == _ttoi(g_pMainDlg->m_strPMModuleCount))
            g_pMainDlg->m_bPM_Thread_Cheak = true;
        nPM_Cheak = g_pMainDlg->m_nPM_Thread2;
        for (int i = 1; i <= 100; i++)
        {
            Sleep(g_pMainDlg->m_nPM_Time / (g_pMainDlg->m_nSpeed* 100));
            if (nPM_Cheak == 1)
                g_pMainDlg->m_ctrPROGRESS_PM1.SetPos(i);
            else if (nPM_Cheak == 2)
                g_pMainDlg->m_ctrPROGRESS_PM2.SetPos(i);
            else if (nPM_Cheak == 3)
                g_pMainDlg->m_ctrPROGRESS_PM3.SetPos(i);
            else if (nPM_Cheak == 4)
                g_pMainDlg->m_ctrPROGRESS_PM4.SetPos(i);
            else if (nPM_Cheak == 5)
                g_pMainDlg->m_ctrPROGRESS_PM5.SetPos(i);
            else if (nPM_Cheak == 6)
                g_pMainDlg->m_ctrPROGRESS_PM6.SetPos(i);

            //프로그래스바 1/100 충전
        }
    }
    else if(g_pMainDlg->m_bPM_Thread_Cheak==true)
    {
        nPM_Cheak = g_pMainDlg->m_nPM_Thread3;
        for (int i = 1; i <= 100; i++)
        {
            Sleep(g_pMainDlg->m_nPM_Time / (g_pMainDlg->m_nSpeed * 100));
            if (nPM_Cheak == 1)
                g_pMainDlg->m_ctrPROGRESS_PM1.SetPos(i);
            else if (nPM_Cheak == 2)
                g_pMainDlg->m_ctrPROGRESS_PM2.SetPos(i);
            else if (nPM_Cheak == 3)
                g_pMainDlg->m_ctrPROGRESS_PM3.SetPos(i);
            else if (nPM_Cheak == 4)
                g_pMainDlg->m_ctrPROGRESS_PM4.SetPos(i);
            else if (nPM_Cheak == 5)
                g_pMainDlg->m_ctrPROGRESS_PM5.SetPos(i);
            else if (nPM_Cheak == 6)
                g_pMainDlg->m_ctrPROGRESS_PM6.SetPos(i);

            //프로그래스바 1/100 충전
        }
    }
    else
    {
        for (int i = 1; i <= 100; i++)
        {
            Sleep(g_pMainDlg->m_nPM_Clean_Time / (g_pMainDlg->m_nSpeed * 100));
            //프로그래스바 1/100 충전
        }
    }
    
    if (nPM_Cheak == 1)
    {
        g_pMainDlg->m_Static_Count++;
        g_pMainDlg->m_CtrStatic_PM1.SetWindowInt(_ttoi(g_pMainDlg->m_strPMModuleCount) * g_pMainDlg->m_Static_Count);
    }
    else if (nPM_Cheak == 2)
        g_pMainDlg->m_CtrStatic_PM2.SetWindowInt(_ttoi(g_pMainDlg->m_strPMModuleCount) * g_pMainDlg->m_Static_Count);
    else if (nPM_Cheak == 3)
        g_pMainDlg->m_CtrStatic_PM3.SetWindowInt(_ttoi(g_pMainDlg->m_strPMModuleCount) * g_pMainDlg->m_Static_Count);
    else if (nPM_Cheak == 4)
        g_pMainDlg->m_CtrStatic_PM4.SetWindowInt(_ttoi(g_pMainDlg->m_strPMModuleCount) * g_pMainDlg->m_Static_Count);
    else if (nPM_Cheak == 5)
        g_pMainDlg->m_CtrStatic_PM5.SetWindowInt(_ttoi(g_pMainDlg->m_strPMModuleCount) * g_pMainDlg->m_Static_Count);
    else if (nPM_Cheak == 6)
        g_pMainDlg->m_CtrStatic_PM6.SetWindowInt(_ttoi(g_pMainDlg->m_strPMModuleCount) * g_pMainDlg->m_Static_Count);
    
    if(g_pMainDlg->m_nPM_Processing == _ttoi(g_pMainDlg->m_strPMModuleCount))
        SetEvent(g_hEvent_PM_MAX);
    g_pMainDlg->m_nPM_Processing--;
    return 0;
}
//FINAL RESULT (THROUGHPUT)
DWORD WINAPI Thread_Start(LPVOID p)
{
    int nLPM_input_cnt = g_pMainDlg->m_ctrLPM.GetWindowInt();
    int nPM_MAX = _ttoi(g_pMainDlg->m_strPMWaferCount) * _ttoi(g_pMainDlg->m_strPMModuleCount);
    int nLL_MAX = _ttoi(g_pMainDlg->m_strLLWaferCount) * _ttoi(g_pMainDlg->m_strLLRoomCount);
    int i = g_pMainDlg->m_ctrLPM.GetWindowInt();
    

    while (i != 0)
        //while(i<_ttoi(g_pMainDlg->m_strLLRoomCount))
    {
        if (nLPM_input_cnt - i - g_pMainDlg->m_noutput_count >= nPM_MAX + nLL_MAX)
        {
            if (g_pMainDlg->m_nThread_Time_Error > 0)
            {
                if (_ttoi(g_pMainDlg->m_strLLRoomCount) == 1 || _ttoi(g_pMainDlg->m_strLLRoomCount) == 2)
                    WaitForSingleObject(g_hEventLL_Modul_one_Thread4and1, INFINITE);

                CloseHandle(CreateThread(NULL, 0, Thread_4_LL2OUT, 0, 0, 0));
                WaitForSingleObject(g_hEventThread4_wait, INFINITE);

                CloseHandle(CreateThread(NULL, 0, Thread_1_LPM2LL, 0, 0, 0));
                WaitForSingleObject(g_hEventStart, INFINITE);
                g_pMainDlg->m_nThread4_LL++;
                if (g_pMainDlg->m_nThread4_LL == _ttoi(g_pMainDlg->m_strLLRoomCount)+1)
                    g_pMainDlg->m_nThread4_LL = 1;
            }
            
            /*if (g_pMainDlg->m_nThread_Time_Error ==1)
            {
                WaitForSingleObject(g_hEventThread4_wait, INFINITE);
            }*/
            if (g_pMainDlg->m_noutput_count == _ttoi(g_pMainDlg->m_strLLWaferCount))
                g_pMainDlg->m_nThread1_LL = 0;
        }
        
        if (g_pMainDlg->m_Thread3start == 0)
        {
            CloseHandle(CreateThread(NULL, 0, Thread_1_LPM2LL, 0, 0, 0));
            WaitForSingleObject(g_hEventStart, INFINITE);
        }
      
        i = g_pMainDlg->m_ctrLPM.GetWindowInt();



        int nLPM_cnt = g_pMainDlg->m_ctrLPM.GetWindowInt();
        int PM_Count = g_pMainDlg->m_ctrPM1.GetWindowInt() +
            g_pMainDlg->m_ctrPM2.GetWindowInt() +
            g_pMainDlg->m_ctrPM3.GetWindowInt() +
            g_pMainDlg->m_ctrPM4.GetWindowInt() +
            g_pMainDlg->m_ctrPM5.GetWindowInt() +
            g_pMainDlg->m_ctrPM6.GetWindowInt();

        if (PM_Count != nPM_MAX && g_pMainDlg->m_Thread3start == 0)
        {
            if (_ttoi(g_pMainDlg->m_strLLRoomCount) == 1)
                WaitForSingleObject(g_hEventLL_Modul_one_Thread1and2, INFINITE);
        }

        if (g_pMainDlg->m_Thread3start == 0 && (PM_Count == nPM_MAX && g_pMainDlg->m_nWafer_Count == nPM_MAX + g_pMainDlg->m_nLLMAX))
        {
            //for (int i = 0; i < g_pMainDlg->m_nThread2_LL; i++)
            {
                CloseHandle(CreateThread(NULL, 0, Thread_3_PM2LL, 0, 0, 0));
                g_pMainDlg->m_Thread3start++;
                WaitForSingleObject(g_hEventcount, INFINITE);
                //WaitForSingleObject(g_hEventPMtoLL, INFINITE);
            }
        }
    }

    return 0;
}

DWORD WINAPI TotalTime(LPVOID p)
{
    CString strTime;
    int n_H = 0;
    int n_M = 0;
    int n_S = 0;
    while (true)
    {    
        Sleep(1000/g_pMainDlg->m_nSpeed);
        n_S++;
        if (n_S == 60)
        {
            n_S = 0;
            n_M++;
        }
        if (n_M == 60)
        {
            n_M = 0;
            n_H++;
        }
        //g_pMainDlg->m_strCurTime = CTime::GetCurrentTime();
        //g_pMainDlg->m_strDiffTime = g_pMainDlg->m_strCurTime - g_pMainDlg->m_strInitTime;
        strTime.Format(_T("%02d:%02d:%02d"),n_H,n_M,n_S);
        if(n_S%3==0)
            g_pMainDlg->m_ctrlStaticTotalTime.SetWindowText(strTime);
    }
}

void C주성Dlg::OnBnClickedStart()
{
    //if (Thread_Start == NULL)
    {
        
        UpdateData(1);
        g_pMainDlg->InvalidateRect(g_CRtemp, false);
        m_nSpeed = _ttoi(m_strSpeed);
        m_ctrLPM.SetWindowInt(99999999);
        m_nLLMAX = _ttoi(m_strLLWaferCount) * _ttoi(m_strLLRoomCount);
        CloseHandle(CreateThread(NULL, 0, TotalTime, 0, 0, 0));
        CloseHandle(CreateThread(NULL, 0, Thread_Start, 0, 0, 0));     
    }
}

void C주성Dlg::OnClose()
{
    CloseHandle(g_hEventStart);
    CDialogEx::OnClose();
}


void C주성Dlg::OnCbnSelchangeTmArm()
{
    UpdateData(1);
    if (m_strTMCount == _T("4"))
    {

        m_ctrLLWaferCount.ResetContent();
        m_ctrPMWaferCount.ResetContent();

        m_ctrLLWaferCount.AddString(_T("2"));
        m_ctrLLWaferCount.AddString(_T("4"));
        m_ctrLLWaferCount.AddString(_T("6"));

        m_ctrPMWaferCount.AddString(_T("2"));
        m_ctrPMWaferCount.AddString(_T("4"));
        m_ctrPMWaferCount.AddString(_T("6"));

        m_strPMWaferCount = _T("2");
        m_strLLWaferCount = _T("2");
    }
    else
    {
        m_ctrLLWaferCount.ResetContent();
        m_ctrPMWaferCount.ResetContent();

        m_ctrLLWaferCount.AddString(_T("1"));
        m_ctrLLWaferCount.AddString(_T("2"));
        m_ctrLLWaferCount.AddString(_T("3"));
        m_ctrLLWaferCount.AddString(_T("4"));
        m_ctrLLWaferCount.AddString(_T("5"));
        m_ctrLLWaferCount.AddString(_T("6"));

        m_ctrPMWaferCount.AddString(_T("1"));
        m_ctrPMWaferCount.AddString(_T("2"));
        m_ctrPMWaferCount.AddString(_T("3"));
        m_ctrPMWaferCount.AddString(_T("4"));
        m_ctrPMWaferCount.AddString(_T("5"));
        m_ctrPMWaferCount.AddString(_T("6"));
    }
    UpdateData(0);
}


void C주성Dlg::OnCbnSelchangeLlWafer()
{
    UpdateData(1);
    if (m_strTMCount == _T("4"))
    {
        //m_strPMWaferCount = m_strLLWaferCount;
    }
    UpdateData(0);
}


void C주성Dlg::OnCbnSelchangePmWafer()
{
    UpdateData(1);
    if (m_strTMCount == _T("4"))
    {
        //m_strLLWaferCount = m_strPMWaferCount;
    }
    UpdateData(0);
}




void C주성Dlg::OnCbnSelchangeLlRoom()
{
    UpdateData(1);
    if (_ttoi(m_strLLRoomCount) > _ttoi(m_strPMModuleCount))
    {
        MessageBox(_T("LL의 모듈 개수는 PM보다 많을수 없습니다."));
        m_strPMModuleCount = m_strLLRoomCount;
    }
    UpdateData(0);
}


void C주성Dlg::OnCbnSelchangePmModul()
{
    UpdateData(1);
    if (_ttoi(m_strLLRoomCount) > _ttoi(m_strPMModuleCount))
    {
        MessageBox(_T("LL의 모듈 개수는 PM보다 많을수 없습니다."));
        m_strPMModuleCount = m_strLLRoomCount;
    }
    UpdateData(0);
}


void C주성Dlg::OnBnClickedSysInitial()
{
    m_dlgSysInit.DoModal();
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
        strValue.Format(_T("%d"), m_nATM_Pick);
        ::WritePrivateProfileString(_T("EFEM"), _T("Pick"), strValue, strSaveName);
        strValue.Format(_T("%d"), m_nATM_Place);
        ::WritePrivateProfileString(_T("EFEM"), _T("Place"), strValue, strSaveName);
        //strValue.Format(_T("%d"), m_ctrALIGNER);
        //::WritePrivateProfileString(_T("EFEM"), _T("Aligner"), strValue, strSaveName);
        strValue.Format(_T("%d"), m_nATM_ZRotate);
        ::WritePrivateProfileString(_T("EFEM"), _T("Z_Move"), strValue, strSaveName);
        strValue.Format(_T("%d"), m_nATM_Rotate);
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
        strValue.Format(_T("%d"), m_nPM_Processing / 1000);
        ::WritePrivateProfileString(_T("PM"), _T("ProcessTime"), strValue, strSaveName);
        strValue.Format(_T("%d"), m_nPM_Clean_Time / 1000);
        ::WritePrivateProfileString(_T("PM"), _T("CleanTime"), strValue, strSaveName);
        strValue.Format(_T("%d"), m_nPM_Clean_Wafer_Count);
        ::WritePrivateProfileString(_T("PM"), _T("CleanCount"), strValue, strSaveName);
        strValue.Format(_T("%d"), m_nPM_Slot_Valve_Open / 1000);
        ::WritePrivateProfileString(_T("PM"), _T("SlotOpenTime"), strValue, strSaveName);
        strValue.Format(_T("%d"),m_nPM_Slot_Valve_Close / 1000);
        ::WritePrivateProfileString(_T("PM"), _T("SlotCloseTime"), strValue, strSaveName);

    }
}

void C주성Dlg::OnRButtonDown(UINT nFlags, CPoint point)
{
    // TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
    CString A;
    A.Format(_T("%d,%d"), point.x, point.y);
    MessageBox(A);
    CDialogEx::OnRButtonDown(nFlags, point);
}

void C주성Dlg::OnBnClickedSetSpeed()
{
    UpdateData(1);
    g_pMainDlg->m_nSpeed= _ttoi(m_strSpeed);
    g_pSubDlg->m_nEFEMPickTime;
    
    UpdateData(0);
}


void C주성Dlg::OnBnClickedButtonSaveThroughput()
{
   
}

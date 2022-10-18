
// 주성Dlg.h: 헤더 파일
//
#pragma once

#include "CDlg_SYSINIT.h"

class C주성Btn : public CButton
{
public:

	int GetWindowInt() //버튼 UI에 써있는 str -> int 변환 함수
	{
		CString strTmp;
		GetWindowText(strTmp);
		return _ttoi(strTmp);
	}
	void SetWindowInt(int val)//버튼 UI에 써있는 int -> str 변환 함수
	{
		CString strTmp;
		strTmp.Format(_T("%d"), val);
		this->SetWindowText(strTmp);
	}
};

// C주성Dlg 대화 상자
class C주성Dlg : public CDialogEx
{
	// 생성입니다.
public:
	C주성Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAINVIEW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


	// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedStart();

	CDlg_SYSINIT m_dlgSysInit;

	int m_nWafer_Count; //장비에 집어넣은 웨이퍼 현재 개수
	int m_nLLMAX; //LL의 방 개수 x 웨이퍼 개수= LL이 수용할수 있는 최대치
	int m_noutput_count; // output에 들어오는 웨이퍼를 담고있는 변수
	int m_nThread1_LL; //쓰레드 1번에서 사용 하고 어떤 LL을 사용해야 할지 파악하는 변수 
	int m_nThread2_LL; //쓰레드 2번에서 사용 하고 어떤 LL을 사용해야 할지 파악하는 변수 
	int m_nThread3_LL; //쓰레드 3번에서 사용 하고 어떤 LL을 사용해야 할지 파악하는 변수
	int m_nThread3_PM; //쓰레드 3번에서 사용 하고 어떤 PM을 사용해야 할지 파악하는 변수
	int m_nThread4_LL; //쓰레드 4번에서 사용 하고 어떤 LL을 사용해야 할지 파악하는 변수
	int m_nThread_Time_Error; // 쓰레드간 시간이 달라서 충돌 오류를 막기위한 변수
	int m_nLL_Thread;
	int m_nWafer_Process[4] = { 0, };//공정 끝낸 웨이퍼 개수
	//장비 동작 시간
	int m_nSpeed;				//배속
	int m_Thread3start;		//3번 쓰레드 부르는 타이밍
	//ATM 로봇
	int m_nATM_Pick;
	int m_nATM_Place;
	int m_nATM_Rotate;
	int m_nATM_ZRotate;
	//LL
	int m_nLL_Pump;				//진공 상태로 전환
	int m_nLL_Pump_Stable_Time;	//진공 상태 전환 전/후 소요시간
	int m_nLL_Vent;				//대기 상태로 전환
	int m_nLL_Vent_Stable_Time;	//대기 상태 전환 전/후 소요 시간 의미
	int m_nLL_Slot_Valve_Open;	//TM과 연결
	int m_nLL_Slot_Valve_Close;
	int m_nLL_Door_Valve_Open;	//EFEM과 연결
	int m_nLL_Door_Valve_Close;
	//VAC
	int m_nVAC_Pick;
	int m_nVAC_Place;
	int m_nRotate;
	//PM
	int m_nPM_Time;				//프로세스 공정시간
	int m_nPM_Clean_Time;		//클린 시간
	int m_nPM_Clean_Wafer_Count;//프로세스 몇번 진행후 클린 진행할것인가
	int m_nPM_Slot_Valve_Open;
	int m_nPM_Slot_Valve_Close;

	int m_nPM_Thread2 = 0;		//PM 쓰레드 에서 프로그래스바 에서 사용하는 변수 (PM 모듈 구분용) 2번 쓰레드 에서만 사용
	int m_nPM_Thread3 = 0;		//PM 쓰레드 에서 프로그래스바 에서 사용하는 변수 (PM 모듈 구분용) 3번 쓰레드 에서만 사용
	int m_nPM_Processing = 0;	//현재 PM 공정 진행중인 개수
	bool m_bPM_Thread_Check = false;
	//프로그래스바
	CProgressCtrl m_ctrPROGRESS_PM1;
	CProgressCtrl m_ctrPROGRESS_PM2;
	CProgressCtrl m_ctrPROGRESS_PM3;
	CProgressCtrl m_ctrPROGRESS_PM4;
	CProgressCtrl m_ctrPROGRESS_PM5;
	CProgressCtrl m_ctrPROGRESS_PM6;

	CProgressCtrl m_ctrPROGRESS_LL1;
	CProgressCtrl m_ctrPROGRESS_LL2;
	CProgressCtrl m_ctrPROGRESS_LL3;
	CProgressCtrl m_ctrPROGRESS_LL4;

	CString m_strSpeed; // 스피드
	//실제 데이터 이동을 위한 값 변수 모음
	CString m_strLLSlotCnt; //콤보박스 LL 방 개수 값 변수
	CString m_strLLModuleCnt;  //콤보박스 LL 웨이퍼 개수 값 변수
	CString m_strVacArmCnt;      //콤보박스 TM 웨이퍼 개수 값 변수
	CString m_strPMModuleCnt;//콤보박스 PM 모듈 개수 값 변수
	CString m_strPMSlotCnt; //콤보박스 PM 웨이퍼 개수 값 변수


	//UI로 사용자에게 보여지는 버튼 값 UI 변수
	C주성Btn m_ctrEFEM;
	C주성Btn m_ctrALIGNER;
	C주성Btn m_ctrLL1;
	C주성Btn m_ctrLL2;
	C주성Btn m_ctrLL3;
	C주성Btn m_ctrLL4;
	C주성Btn m_ctrTM;
	C주성Btn m_ctrLPM;
	C주성Btn m_ctrPM1;
	C주성Btn m_ctrPM2;
	C주성Btn m_ctrPM3;
	C주성Btn m_ctrPM4;
	C주성Btn m_ctrPM5;
	C주성Btn m_ctrPM6;

	//초기 세팅을 위한 컨트롤 변수 모음

	CComboBox m_ctrSpeed;  //콤보박스 스피드
	afx_msg void OnClose();


	afx_msg void OnBnClickedSysInitial();
	afx_msg void OnBnClickedButtonSaveSystemconfig();
	afx_msg void OnBnClickedButtonSaveThroughput();
	afx_msg void OnBnClickedButtonLoadSystemconfig();
	afx_msg void OnBnClickedButtonLoadThroughput();

	CStatic m_ctrlStaticTotalTime;

	CFont m_font;


	afx_msg void OnBnClickedSetSpeed();
	//각 PM의 웨이퍼 공정 개수
	C주성Btn m_CtrStatic_PM1;
	C주성Btn m_CtrStatic_PM2;
	C주성Btn m_CtrStatic_PM3;
	C주성Btn m_CtrStatic_PM4;
	C주성Btn m_CtrStatic_PM5;
	C주성Btn m_CtrStatic_PM6;
	C주성Btn m_ctrStatic_Speed;
	int m_Static_Count = 0;
	//LPM UI 변수
	C주성Btn m_ctrLPMUI1;
	C주성Btn m_ctrLPMUI2;
	CStatic m_Gui_TM;
	CStatic m_Ctrl_Gui_PM1;
	CStatic m_Ctrl_Gui_PM2;
	CStatic m_Ctrl_Gui_PM3;
	CStatic m_Ctrl_Gui_PM4;
	CStatic m_Ctrl_Gui_PM5;
	CStatic m_Ctrl_Gui_PM6;
	CStatic m_Ctrl_Gui_EFEM;

	//Clean용 더미 웨이퍼 공정시 사용 변수
	int m_nDummy_Wafer_Count;	//들어간 더미 웨이퍼 개수
	bool m_bLL_Dummy;			


	int m_nTotal_Input;			// 웨이퍼 총 INPUT 값

	bool m_bClean_Time_Start;	// Clean 공정 시작/종료 시간 알림
	C주성Btn m_ctrPM_Count1;
	C주성Btn m_ctrPM_Count2;
	C주성Btn m_ctrPM_Count3;
	C주성Btn m_ctrPM_Count4;
	C주성Btn m_ctrPM_Count5;
	C주성Btn m_ctrPM_Count6;
	CStatic m_ctrTotal_Clean_Time;

	bool m_bTime_STOP = false;
	int m_nDummy_Count = 0;
	bool m_bDummy = false;

	//라디오 버튼 모음
	CButton m_ctrRadio_Process1;
	CButton m_ctrRadio_Process2;
	CButton m_ctrRadio_Process3;
	CButton m_ctrRadio_Process4;
	CButton m_ctrRadio_Process5;
	CButton m_ctrRadio_Process6;
	CButton m_ctrRadio_Clean1;
	CButton m_ctrRadio_Clean2;
	CButton m_ctrRadio_Clean3;
	CButton m_ctrRadio_Clean4;
	CButton m_ctrRadio_Clean5;
	CButton m_ctrRadio_Clean6;

	int m_nTotalSec;
	int m_nCleanSec;
	C주성Btn m_ctrOutput;
	C주성Btn m_ctrThrought;
	CStatic m_ctrStaticGreen;
	CStatic m_ctrStaticBlue;
	CStatic m_ctrStaticRed;


	CStatic m_ctrPicture_Back;
	CStatic m_ctrStaticGray;

	//OnPaint	
	CBrush m_brGreen;
	CBrush m_brBlue;
	CBrush m_brRed;
	CBrush m_brGray;	
};

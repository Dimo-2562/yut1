
// yut1View.cpp: Cyut1View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "yut1.h"
#endif

#include "yut1Doc.h"
#include "yut1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cyut1View

IMPLEMENT_DYNCREATE(Cyut1View, CView)

BEGIN_MESSAGE_MAP(Cyut1View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
END_MESSAGE_MAP()

// Cyut1View 생성/소멸

Cyut1View::Cyut1View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

	//배경 좌표 초기화
	background_x1 = 100;
	background_x2 = 1000;
	background_y1 = 50;
	background_y2 = 700;

	//큰 원 좌표 초기화
	bigMovePoint_X[0] = background_x1 + 60;
	bigMovePoint_Y[0] = background_y1 + 60;

	bigMovePoint_X[1] = background_x2 - 60;
	bigMovePoint_Y[1] = background_y1 + 60;

	bigMovePoint_X[2] = background_x1 + 450;
	bigMovePoint_Y[2] = background_y1 + 320;

	bigMovePoint_X[3] = background_x1 + 60;
	bigMovePoint_Y[3] = background_y2 - 60;

	bigMovePoint_X[4] = background_x2 - 60;
	bigMovePoint_Y[4] = background_y2 - 60;
	
	for (int i = 0; i < 4; i++) {
		//위 줄 원 좌표 초기화
		upMovePoint_X[i] = background_x1 + 225 + i * 150;
		upMovePoint_Y[i] = background_y1 + 65;

		//왼쪽 줄 원 좌표 초기화
		leftMovePoint_X[i] = background_x1 + 60;
		leftMovePoint_Y[i] = background_y1 + 175 + i * 100;

		//오른쪽 줄 원 좌표 초기화
		rightMovePoint_X[i] = background_x2 - 60;
		rightMovePoint_Y[i] = background_y1 + 175 + i * 100;

		//아래 줄 원 좌표 초기화
		downMovePoint_X[i] = background_x1 + 225 + i * 150;
		downMovePoint_Y[i] = background_y2 - 65;
	}

	//바깥쪽 원 좌표 초기화
	outerMovePoint_X[0] = background_x1 + 205;
	outerMovePoint_Y[0] = background_y1 + 175;

	outerMovePoint_X[1] = background_x2 - 205;
	outerMovePoint_Y[1] = background_y1 + 175;

	outerMovePoint_X[2] = background_x1 + 205;
	outerMovePoint_Y[2] = background_y2 - 175;

	outerMovePoint_X[3] = background_x2 - 205;
	outerMovePoint_Y[3] = background_y2 - 175;

	//안쪽 원 좌표 초기화
	innerMovePoint_X[0] = background_x1 + 335;
	innerMovePoint_Y[0] = background_y1 + 265;

	innerMovePoint_X[1] = background_x2 - 335;
	innerMovePoint_Y[1] = background_y1 + 265;

	innerMovePoint_X[2] = background_x1 + 335;
	innerMovePoint_Y[2] = background_y2 - 265;

	innerMovePoint_X[3] = background_x2 - 335;
	innerMovePoint_Y[3] = background_y2 - 265;

	//말 위치 초기화
	malFirst_X[0] = 1100;
	malFirst_Y[0] = 450;

	malFirst_X[1] = 1100;
	malFirst_Y[1] = 550;

	malFirst_X[2] = 1200;
	malFirst_Y[2] = 450;

	malFirst_X[3] = 1200;
	malFirst_Y[3] = 550;

	malSecond_X[0] = 1350;
	malSecond_Y[0] = 450;

	malSecond_X[1] = 1350;
	malSecond_Y[1] = 550;

	malSecond_X[2] = 1450;
	malSecond_Y[2] = 450;

	malSecond_X[3] = 1450;
	malSecond_Y[3] = 550;
}

Cyut1View::~Cyut1View()
{
}

BOOL Cyut1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// Cyut1View 그리기

void Cyut1View::OnDraw(CDC* pDC)
{
	Cyut1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CBrush brushBackground(RGB(178, 214, 154)); //윷놀이 판 배경색
	CBrush brushBigMovepoint(RGB(84, 130, 53)); //윷놀이 판 큰 동그라미
	CBrush brushMovepoint(RGB(112, 173, 71)); //윷놀이 판 작은 동그라미
	CBrush brushYutBackground(RGB(255, 221, 156)); //윷판 배경색
	CBrush brushMalBackground(RGB(218, 227, 243)); //윷말 배경색
	CBrush brushMalFirst(RGB(249, 131, 148)); // 빨간말
	CBrush brushMalSecond(RGB(143, 165, 237)); // 파란말
	CBrush* oldBrush;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.

	//윷판 그리기
	oldBrush = pDC->SelectObject(&brushYutBackground);
	pDC->Rectangle(1050, 50, 1500, 350);

	//말판 그리기
	oldBrush = pDC->SelectObject(&brushMalBackground);
	pDC->Rectangle(1050, 400, 1250, 600);
	pDC->Rectangle(1300, 400, 1500, 600);

	//판 그리기
	oldBrush = pDC->SelectObject(&brushBackground);
	pDC->Rectangle(background_x1, background_y1, background_x2, background_y2);

	//큰 움직임 포인트 그리기
	oldBrush = pDC->SelectObject(&brushBigMovepoint);
	for (int i = 0; i < 5; i++) {
		pDC->Ellipse(bigMovePoint_X[i] - 50, bigMovePoint_Y[i] - 50, bigMovePoint_X[i] + 50, bigMovePoint_Y[i] + 50);
	}

	//작은 움직임 포인트 그리기
	oldBrush = pDC->SelectObject(&brushMovepoint);
	for (int i = 0; i < 4; i++) {
		pDC->Ellipse(upMovePoint_X[i] - 35, upMovePoint_Y[i] - 35, upMovePoint_X[i] + 35, upMovePoint_Y[i] + 35); //위 줄
		pDC->Ellipse(leftMovePoint_X[i] - 35, leftMovePoint_Y[i] - 35, leftMovePoint_X[i] + 35, leftMovePoint_Y[i] + 35); //왼쪽 줄
		pDC->Ellipse(rightMovePoint_X[i] - 35, rightMovePoint_Y[i] - 35, rightMovePoint_X[i] + 35, rightMovePoint_Y[i] + 35); //오른쪽 줄
		pDC->Ellipse(downMovePoint_X[i] - 35, downMovePoint_Y[i] - 35, downMovePoint_X[i] + 35, downMovePoint_Y[i] + 35); //아래 줄
		pDC->Ellipse(outerMovePoint_X[i] - 35, outerMovePoint_Y[i] - 35, outerMovePoint_X[i] + 35, outerMovePoint_Y[i] + 35); //바깥쪽 원
		pDC->Ellipse(innerMovePoint_X[i] - 35, innerMovePoint_Y[i] - 35, innerMovePoint_X[i] + 35, innerMovePoint_Y[i] + 35); //안쪽 원
	}

	//윷 그리기
	CBitmap bitmap;
	bitmap.LoadBitmap(IDB_BITMAP1);
	CBrush brushYut(&bitmap);
	pDC->SelectObject(&brushYut);
	for (int i = 0; i < 4; i++) {
		pDC->Rectangle(1100 + 96 * i, 100, 1150 + 96 * i, 290);
	}

	//말 그리기
	oldBrush = pDC->SelectObject(&brushMalFirst);
	for (int i = 0; i < 4; i++) {
		pDC->Ellipse(malFirst_X[i] - 40, malFirst_Y[i] - 40, malFirst_X[i] + 40, malFirst_Y[i] + 40);
	}

	oldBrush = pDC->SelectObject(&brushMalSecond);
	for (int i = 0; i < 4; i++) {
		pDC->Ellipse(malSecond_X[i] - 40, malSecond_Y[i] - 40, malSecond_X[i] + 40, malSecond_Y[i] + 40);
	}
}


// Cyut1View 인쇄

BOOL Cyut1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void Cyut1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void Cyut1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// Cyut1View 진단

#ifdef _DEBUG
void Cyut1View::AssertValid() const
{
	CView::AssertValid();
}

void Cyut1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Cyut1Doc* Cyut1View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Cyut1Doc)));
	return (Cyut1Doc*)m_pDocument;
}
#endif //_DEBUG


// Cyut1View 메시지 처리기


int Cyut1View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	//윷 던지기 버튼 생성
	m_throwButton.Create(_T("윷 던지기"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		CRect(1300, 650, 1500, 720), this, 101);

	

	return 0;
}

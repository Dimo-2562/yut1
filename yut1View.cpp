
// yut1View.cpp: Cyut1View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "math.h"
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
	ON_BN_CLICKED(101, OnButtonClicked)
	ON_WM_CREATE()
	ON_WM_CTLCOLOR()
	ON_WM_DRAWITEM()
END_MESSAGE_MAP()

Map map;
Circle circle[50];
Mal red[4];
Mal blue[4];
Player player1;
Player player2;
Yut yut[4];

// Cyut1View 생성/소멸

Cyut1View::Cyut1View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	map.setPos(100, 1000, 50, 700);

	for (int i = 0; i < 50; i++) {
		circle[i].setPos(0, 0);
	}

	circle[0].setPos(map.x2 - 60, map.y2 - 60);
	for (int i = 0; i < 4; i++)	circle[1 + i].setPos(map.x2 - 60, map.y1 + 175 + (3 - i) * 100);
	circle[5].setPos(map.x2 - 60, map.y1 + 60);
	for (int i = 0; i < 4; i++) circle[6 + i].setPos(map.x1 + 225 + (3 - i) * 150, map.y1 + 65);
	circle[10].setPos(map.x1 + 60, map.y1 + 60);
	for (int i = 0; i < 4; i++) circle[11 + i].setPos(map.x1 + 60, map.y1 + 175 + i * 100);
	circle[15].setPos(map.x1 + 60, map.y2 - 60);
	for (int i = 0; i <4; i++) circle[16 + i].setPos(map.x1 + 225 + i * 150, map.y2 - 65);
	circle[20].setPos(map.x2 - 60, map.y2 - 60);

	circle[30].setPos(map.x2 - 60, map.y1 + 60);

	circle[31].setPos(map.x2 - 205, map.y1 + 175);
	circle[32].setPos(map.x2 - 335, map.y1 + 265);
	circle[33].setPos(map.x1 + 450, map.y1 + 320);
	circle[34].setPos(map.x1 + 335, map.y2 - 265);
	circle[35].setPos(map.x1 + 205, map.y2 - 175);

	circle[36].setPos(map.x1 + 60, map.y2 - 60);

	circle[40].setPos(map.x1 + 60, map.y1 + 60);

	circle[41].setPos(map.x1 + 205, map.y1 + 175);
	circle[42].setPos(map.x1 + 335, map.y1 + 265);
	circle[43].setPos(map.x1 + 450, map.y1 + 320);
	circle[44].setPos(map.x2 - 335, map.y2 - 265);
	circle[45].setPos(map.x2 - 205, map.y2 - 175);

	circle[46].setPos(map.x2 - 60, map.y2 - 60);

	red[0].setInitial(1100, 450, map.x1 - 90, map.y1);
	red[1].setInitial(1100, 550, map.x1 - 90, map.y1 + 70);
	red[2].setInitial(1200, 450, map.x1 - 90, map.y1 + 70 * 2);
	red[3].setInitial(1200, 550, map.x1 - 90, map.y1 + 70 * 3);

	red[0].setPos(1100, 450);
	red[1].setPos(1100, 550);
	red[2].setPos(1200, 450);
	red[3].setPos(1200, 550);

	blue[0].setInitial(1350, 450, map.x1 - 90, map.y1 + 350);
	blue[1].setInitial(1350, 550, map.x1 - 90, map.y1 + 350 + 70);
	blue[2].setInitial(1450, 450, map.x1 - 90, map.y1 + 350 + 70 * 2);
	blue[3].setInitial(1450, 550, map.x1 - 90, map.y1 + 350 + 70 * 3);

	blue[0].setPos(1350, 450);
	blue[1].setPos(1350, 550);
	blue[2].setPos(1450, 450);
	blue[3].setPos(1450, 550);

	for (int i = 0; i < 4; i++) {
		red[i].setID(104 + i);
		red[i].virtualPos = 0;
		red[i].isClicked = false;

		blue[i].setID(108 + i);
		blue[i].virtualPos = 0;
		blue[i].isClicked = false;
	}

	for (int i = 0; i < 4; i++) {
		yut[i].setPos(1100 + 96 * i, 100);
		yut[i].isFront = false;
	}

	player1.setInitial();
	player1.isMyturn = true;

	player2.setInitial();
	player2.throwNum = 0;
}

BOOL Cyut1View::OnCommand(WPARAM wParam, LPARAM lParam)
{
	//isClicked를 true로 변경.
	if ((player1.isMyturn == true) &&(player1.moveCount > 0)
		&& red[0].isClicked == false
		&& red[1].isClicked == false
		&& red[2].isClicked == false
		&& red[3].isClicked == false) {
		if (wParam == red[0].uID)
			red[0].isClicked = true;
		else if (wParam == red[1].uID)
			red[1].isClicked = true;
		else if (wParam == red[2].uID)
			red[2].isClicked = true;
		else if (wParam == red[3].uID)
			red[3].isClicked = true;
	}
	else if (player2.isMyturn == true && (player2.moveCount > 0)
		&& blue[0].isClicked == false
		&& blue[1].isClicked == false
		&& blue[2].isClicked == false
		&& blue[3].isClicked == false) {
		if (wParam == blue[0].uID)
			blue[0].isClicked = true;
		else if (wParam == blue[1].uID)
			blue[1].isClicked = true;
		else if (wParam == blue[2].uID)
			blue[2].isClicked = true;
		else if (wParam == blue[3].uID)
			blue[3].isClicked = true;
	}

	//player1 말 움직이기
	if ((player1.isMyturn == true) && (player1.moveCount > 0)) {
		if (wParam == 1000 && player1.Do > 0) {
			for (int i = 0; i < 4; i++) {
				if (red[i].isClicked == true) {
					red[i].virtualPos += 1;
					red[i].checkPos(red[i].virtualPos);
					for (int j = 0; j < 4; j++) {
						if (red[i].virtualPos == blue[j].virtualPos) {
							blue[j].setPos(blue[j].initialX, blue[j].initialY);
							blue[j].virtualPos = 0;
							player1.throwNum++;
							Wait(1000);
							for (int i = 0; i < 4; i++) {
								yut[i].isFront = false;
							}
							Invalidate();
						}
					}
					red[i].setPos(circle[red[i].virtualPos].x, circle[red[i].virtualPos].y);
					player1.Do--;
					player1.moveCount--;
					red[i].isClicked = false;
				}
			}
		}
		if (wParam == 1001 && player1.Gae > 0) {
			for (int i = 0; i < 4; i++) {
				if (red[i].isClicked == true) {
					red[i].virtualPos += 2;
					red[i].checkPos(red[i].virtualPos);
					for (int j = 0; j < 4; j++) {
						if (red[i].virtualPos == blue[j].virtualPos) {
							blue[j].setPos(blue[j].initialX, blue[j].initialY);
							blue[j].virtualPos = 0;
							player1.throwNum++;
							Wait(1000);
							for (int i = 0; i < 4; i++) {
								yut[i].isFront = false;
							}
							Invalidate();
						}
					}
					red[i].setPos(circle[red[i].virtualPos].x, circle[red[i].virtualPos].y);
					player1.Gae--;
					player1.moveCount--;
					red[i].isClicked = false;
				}
			}
		}
		if (wParam == 1002 && player1.Gul > 0) {
			for (int i = 0; i < 4; i++) {
				if (red[i].isClicked == true) {
					red[i].virtualPos += 3;
					red[i].checkPos(red[i].virtualPos);
					for (int j = 0; j < 4; j++) {
						if (red[i].virtualPos == blue[j].virtualPos) {
							blue[j].setPos(blue[j].initialX, blue[j].initialY);
							blue[j].virtualPos = 0;
							player1.throwNum++;
							Wait(1000);
							for (int i = 0; i < 4; i++) {
								yut[i].isFront = false;
							}
							Invalidate();
						}
					}
					red[i].setPos(circle[red[i].virtualPos].x, circle[red[i].virtualPos].y);
					player1.Gul--;
					player1.moveCount--;
					red[i].isClicked = false;
				}
			}
		}
		if (wParam == 1003 && player1.Yut > 0) {
			for (int i = 0; i < 4; i++) {
				if (red[i].isClicked == true) {
					red[i].virtualPos += 4;
					red[i].checkPos(red[i].virtualPos);
					for (int j = 0; j < 4; j++) {
						if (red[i].virtualPos == blue[j].virtualPos) {
							blue[j].setPos(blue[j].initialX, blue[j].initialY);
							blue[j].virtualPos = 0;
							player1.throwNum++;
							Wait(1000);
							for (int i = 0; i < 4; i++) {
								yut[i].isFront = false;
							}
							Invalidate();
						}
					}
					red[i].setPos(circle[red[i].virtualPos].x, circle[red[i].virtualPos].y);
					player1.Yut--;
					player1.moveCount--;

					red[i].isClicked = false;
				}
			}
		}
		if (wParam == 1004 && player1.Mo > 0) {
			for (int i = 0; i < 4; i++) {
				if (red[i].isClicked == true) {
					red[i].virtualPos += 5;
					red[i].checkPos(red[i].virtualPos);
					for (int j = 0; j < 4; j++) {
						if (red[i].virtualPos == blue[j].virtualPos) {
							blue[j].setPos(blue[j].initialX, blue[j].initialY);
							blue[j].virtualPos = 0;
							player1.throwNum++;
							Wait(1000);
							for (int i = 0; i < 4; i++) {
								yut[i].isFront = false;
							}
							Invalidate();
						}
					}
					red[i].setPos(circle[red[i].virtualPos].x, circle[red[i].virtualPos].y);
					player1.Mo--;
					player1.moveCount--;
					red[i].isClicked = false;
				}
			}
		}
	}
	Invalidate();

	//player2 말 움직이기
	if ((player2.isMyturn == true) && (player2.moveCount > 0)) {
		if (wParam == 1000 && player2.Do > 0) {
			for (int i = 0; i < 4; i++) {
				if (blue[i].isClicked == true) {
					blue[i].virtualPos += 1;
					blue[i].checkPos(blue[i].virtualPos);
					for (int j = 0; j < 4; j++) {
						if (blue[i].virtualPos == red[j].virtualPos) {
							red[j].setPos(red[j].initialX, red[j].initialY);
							red[j].virtualPos = 0;
							player2.throwNum++;
							Wait(1000);
							for (int i = 0; i < 4; i++) {
								yut[i].isFront = false;
							}
							Invalidate();
						}
					}
					blue[i].setPos(circle[blue[i].virtualPos].x, circle[blue[i].virtualPos].y);
					player2.Do--;
					player2.moveCount--;
					blue[i].isClicked = false;
				}
			}
		}
		else if (wParam == 1001 && player2.Gae > 0) {
			for (int i = 0; i < 4; i++) {
				if (blue[i].isClicked == true) {
					blue[i].virtualPos += 2;
					blue[i].checkPos(blue[i].virtualPos);
					for (int j = 0; j < 4; j++) {
						if (blue[i].virtualPos == red[j].virtualPos) {
							red[j].setPos(red[j].initialX, red[j].initialY);
							red[j].virtualPos = 0;
							player2.throwNum++;
							Wait(1000);
							for (int i = 0; i < 4; i++) {
								yut[i].isFront = false;
							}
							Invalidate();
						}
					}
					blue[i].setPos(circle[blue[i].virtualPos].x, circle[blue[i].virtualPos].y);
					player2.Gae--;
					player2.moveCount--;
					blue[i].isClicked = false;
				}
			}
		}
		else if (wParam == 1002 && player2.Gul > 0) {
			for (int i = 0; i < 4; i++) {
				if (blue[i].isClicked == true) {
					blue[i].virtualPos += 3;
					blue[i].checkPos(blue[i].virtualPos);
					for (int j = 0; j < 4; j++) {
						if (blue[i].virtualPos == red[j].virtualPos) {
							red[j].setPos(red[j].initialX, red[j].initialY);
							red[j].virtualPos = 0;
							player2.throwNum++;
							Wait(1000);
							for (int i = 0; i < 4; i++) {
								yut[i].isFront = false;
							}
							Invalidate();
						}
					}
					blue[i].setPos(circle[blue[i].virtualPos].x, circle[blue[i].virtualPos].y);
					player2.Gul--;
					player2.moveCount--;
					blue[i].isClicked = false;
				}
			}
		}
		else if (wParam == 1003 && player2.Yut > 0) {
			for (int i = 0; i < 4; i++) {
				if (blue[i].isClicked == true) {
					blue[i].virtualPos += 4;
					blue[i].checkPos(blue[i].virtualPos);
					for (int j = 0; j < 4; j++) {
						if (blue[i].virtualPos == red[j].virtualPos) {
							red[j].setPos(red[j].initialX, red[j].initialY);
							red[j].virtualPos = 0;
							player2.throwNum++;
							Wait(1000);
							for (int i = 0; i < 4; i++) {
								yut[i].isFront = false;
							}
							Invalidate();
						}
					}
					blue[i].setPos(circle[blue[i].virtualPos].x, circle[blue[i].virtualPos].y);
					player2.Yut--;
					player2.moveCount--;
					blue[i].isClicked = false;
				}
			}
		}
		else if (wParam == 1004 && player2.Mo > 0) {
			for (int i = 0; i < 4; i++) {
				if (blue[i].isClicked == true) {
					blue[i].virtualPos += 5;
					blue[i].checkPos(blue[i].virtualPos);
					for (int j = 0; j < 4; j++) {
						if (blue[i].virtualPos == red[j].virtualPos) {
							red[j].setPos(red[j].initialX, red[j].initialY);
							red[j].virtualPos = 0;
							player2.throwNum++;
							Wait(1000);
							for (int i = 0; i < 4; i++) {
								yut[i].isFront = false;
							}
							Invalidate();
						}
					}
					blue[i].setPos(circle[blue[i].virtualPos].x, circle[blue[i].virtualPos].y);
					player2.Mo--;
					player2.moveCount--;
					blue[i].isClicked = false;
				}
			}
		}
	}
	Invalidate();

	if (player1.isMyturn == true && player1.moveCount == 0 && player1.throwNum == 0
		&& red[0].isClicked == false
		&& red[1].isClicked == false
		&& red[2].isClicked == false
		&& red[3].isClicked == false) {
		player1.isMyturn = false;
		player2.isMyturn = true;
		player2.throwNum++;
		for (int i = 0; i < 4; i++) {
			yut[i].isFront = false;
		}
	}
	else if (player2.isMyturn == true && player2.moveCount == 0 && player2.throwNum == 0
		&& blue[0].isClicked == false
		&& blue[1].isClicked == false
		&& blue[2].isClicked == false
		&& blue[3].isClicked == false) {
		player2.isMyturn = false;
		player1.isMyturn = true;
		player1.throwNum++;
		for (int i = 0; i < 4; i++) {
			yut[i].isFront = false;
		}
	}

	Invalidate();

	return CView::OnCommand(wParam, lParam);
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
	CBrush brushYutFront(RGB(255, 255, 0)); //윷의 앞
	CBrush* oldBrush;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.

	//윷판 그리기
	oldBrush = pDC->SelectObject(&brushYutBackground);
	pDC->Rectangle(1050, 50, 1500, 350);

	//말판 그리기
	oldBrush = pDC->SelectObject(&brushMalBackground);
	pDC->Rectangle(1050, 400, 1250, 600);
	pDC->Rectangle(1300, 400, 1500, 600);

	pDC->Rectangle(map.x1 - 100, map.y1, map.x1 - 20, map.y1 + 300);
	pDC->Rectangle(map.x1 - 100, map.y1+350, map.x1 - 20, map.y1 + 650);

	//판 그리기
	oldBrush = pDC->SelectObject(&brushBackground);
	pDC->Rectangle(map.x1, map.y1, map.x2, map.y2);

	//작은 움직임 포인트 그리기
	oldBrush = pDC->SelectObject(&brushMovepoint);
	for (int i = 0; i < 50; i++) {
		if (circle[i].x != 0 && circle[i].y != 0)
			pDC->Ellipse(circle[i].x - 35, circle[i].y - 35, circle[i].x + 35, circle[i].y + 35);
	}

	//큰 움직임 포인트 그리기
	oldBrush = pDC->SelectObject(&brushBigMovepoint);
	pDC->Ellipse(circle[0].x - 50, circle[0].y - 50, circle[0].x + 50, circle[0].y + 50);
	pDC->Ellipse(circle[5].x - 50, circle[5].y - 50, circle[5].x + 50, circle[5].y + 50);
	pDC->Ellipse(circle[10].x - 50, circle[10].y - 50, circle[10].x + 50, circle[10].y + 50);
	pDC->Ellipse(circle[15].x - 50, circle[15].y - 50, circle[15].x + 50, circle[15].y + 50);
	pDC->Ellipse(circle[33].x - 50, circle[33].y - 50, circle[33].x + 50, circle[33].y + 50);

	//윷 그리기
	CBitmap bitmap;
	bitmap.LoadBitmap(IDB_BITMAP1);
	CBrush brushYutBack(&bitmap);
	
	for (int i = 0; i < 4; i++) {
		if (yut[i].isFront == false)
			pDC->SelectObject(&brushYutBack);
		else
			pDC->SelectObject(&brushYutFront);
		pDC->Rectangle(yut[i].x, yut[i].y, yut[i].x + 50, yut[i].y + 190);
	}

	//말 그리기
	
	for (int i = 0; i < 4; i++) {
		if ((red[i].virtualPos > 20 && red[i].virtualPos < 30) || red[i].virtualPos >= 100) {
			red[i].virtualPos = 100 + i;
			GetDlgItem(red[i].uID)->MoveWindow(red[i].endX, red[i].endY, 60, 60);
		}
		else
			GetDlgItem(red[i].uID)->MoveWindow(red[i].x - 30, red[i].y - 30, 60, 60);

		if ((blue[i].virtualPos > 20 && blue[i].virtualPos < 30) || blue[i].virtualPos >= 200) {
			blue[i].virtualPos = 200 + i;
			GetDlgItem(blue[i].uID)->MoveWindow(blue[i].endX, blue[i].endY, 60, 60);
		}
		else
			GetDlgItem(blue[i].uID)->MoveWindow(blue[i].x - 30, blue[i].y - 30, 60, 60);
	}

	player1.arrived = 0;
	for (int i = 0; i < 4; i++) {
		if (red[i].virtualPos == 100 + i) {
			player1.arrived++;
		}
	}
	if (player1.arrived == 4) {
		AfxMessageBox(_T("Player1 승리!!"));
	}
	player2.arrived = 0;
	for (int i = 0; i < 4; i++) {
		if (blue[i].virtualPos == 200 + i) {
			player2.arrived++;
		}
	}
	if (player2.arrived == 4) {
		AfxMessageBox(_T("Player2 승리!!"));
	}

	
}

// Cyut1View 메시지 처리기


int Cyut1View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	//윷 던지기 버튼 생성
	m_throwButton.Create(_T("윷 던지기"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		CRect(1300, 650, 1500, 720), this, 101);

	m_yutButton[0].Create(_T("도"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		CRect(1070, 300, 1070 + 50, 350), this, 1000);

	m_yutButton[1].Create(_T("개"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		CRect(1160, 300, 1160+50, 350), this, 1001);

	m_yutButton[2].Create(_T("걸"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		CRect(1250, 300, 1300, 350), this, 1002);

	m_yutButton[3].Create(_T("윷"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		CRect(1340, 300, 1340 + 50, 350), this, 1003);

	m_yutButton[4].Create(_T("모"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		CRect(1430, 300, 1480, 350), this, 1004);
	
	m_redTurn.Create(_T("RED"),
		WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE,
		CRect(1070, 650, 1140, 720), this, 102);

	m_blueTurn.Create(_T("BLUE"),
		WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE,
		CRect(1170, 650, 1240, 720), this, 103);

	
	for (int i = 0; i < 4; i++) {
		red[i].button.Create(_T("RED"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_OWNERDRAW,
			CRect(red[i].x - 30, red[i].y - 30, red[i].x + 30, red[i].y + 30), this, red[i].uID);
	}

	for (int i = 0; i < 4; i++) {
		blue[i].button.Create(_T("BLUE"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_OWNERDRAW,
			CRect(blue[i].x - 30, blue[i].y - 30, blue[i].x + 30, blue[i].y + 30), this, blue[i].uID);
	}

	return 0;
}


void Cyut1View::OnButtonClicked() //윷 던지기 버튼을 클릭했을 때
{
	srand((unsigned int)(time(NULL)));

	int startNumber = 0, endNumber = 100;
	int frontCount = 0;

	if (player1.isMyturn == true) { //플레이어 1의 차례이면?
		if (player1.throwNum > 0) {
			player1.throwNum--;

			yut[0].y = 30;
			yut[1].y = 0;
			yut[2].y = 40;
			yut[3].y = 70;
			Invalidate();
			Wait(500);

			for (int i = 0; i < 4; i++)
				yut[i].y = 100;
			

			for (int i = 0; i < 4; i++) {
				int random_number = (rand() % (endNumber - startNumber + 1)) + startNumber;
				if (random_number % 2 == 1) {
					yut[i].isFront = true;
					frontCount++;
				}
			}

			Invalidate();

			switch (frontCount)
			{
			case 1:
				player1.Do++;
				player1.moveCount++;
				break;
			case 2:
				player1.Gae++;
				player1.moveCount++;
				break;
			case 3:
				player1.Gul++;
				player1.moveCount++;
				break;
			case 4:
				player1.Yut++;
				player1.moveCount++;
				player1.throwNum++;
				Wait(1000);
				for (int i = 0; i < 4; i++) {
					yut[i].isFront = false;
				}
				Invalidate();
				break;
			case 0:
				player1.Mo++;
				player1.moveCount++;
				player1.throwNum++;
				for (int i = 0; i < 4; i++) {
					yut[i].isFront = false;
				}
				break;
			}
		}
	}
	else if(player2.isMyturn ==true){
		if (player2.throwNum > 0) {
			player2.throwNum--;

			yut[0].y = 30;
			yut[1].y = 0;
			yut[2].y = 40;
			yut[3].y = 70;
			Invalidate();
			Wait(500);

			for (int i = 0; i < 4; i++)
				yut[i].y = 100;
			Invalidate();

			for (int i = 0; i < 4; i++) {
				int random_number = (rand() % (endNumber - startNumber + 1)) + startNumber;
				if (random_number % 2 == 1) {
					yut[i].isFront = true;
					frontCount++;
				}
			}

			switch (frontCount)
			{
			case 1:
				player2.Do++;
				player2.moveCount++;
				break;
			case 2:
				player2.Gae++;
				player2.moveCount++;
				break;
			case 3:
				player2.Gul++;
				player2.moveCount++;
				break;
			case 4:
				player2.Yut++;
				player2.moveCount++;
				player2.throwNum++;
				Wait(1000);
				for (int i = 0; i < 4; i++) {
					yut[i].isFront = false;
				}
				Invalidate();
				break;
			case 0:
				player2.Mo++;
				player2.moveCount++;
				player2.throwNum++;
				for (int i = 0; i < 4; i++) {
					yut[i].isFront = false;
				}

				break;
			}
		}
	}
	
}

//플레이어의 차례를 색으로 알려주는 코드.
HBRUSH Cyut1View::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CView::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	int nCtlID = pWnd->GetDlgCtrlID(); //컨트롤의 ID가져오기
	switch (nCtlID)
	{
		case 102:
			if (player1.isMyturn == true)
				pDC->SetTextColor(RGB(255, 0, 0));//글자색변경
			break;
		case 103:
			if (player2.isMyturn == true)
				pDC->SetTextColor(RGB(0, 0, 255));
			break;
		default:
			break;
	}

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}



//말 색상 변경 코드
void Cyut1View::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	UINT uStyle = DFCS_BUTTONPUSH;

	ASSERT(lpDrawItemStruct->CtlType == ODT_BUTTON);

	if (lpDrawItemStruct->itemState & ODS_SELECTED)
		uStyle |= DFCS_PUSHED;

	::DrawFrameControl(lpDrawItemStruct->hDC, &lpDrawItemStruct->rcItem,
		DFC_BUTTON, uStyle);

	CDC dc;
	dc.Attach(lpDrawItemStruct->hDC);

	RECT rect;
	rect = lpDrawItemStruct->rcItem;

	if (nIDCtl >= 104 && nIDCtl < 108) {
		for (int i = 0; i < 4; i++) {
			dc.FillSolidRect(&rect, RGB(255, 102, 102));
		}
	}

	if (nIDCtl >= 108 && nIDCtl < 112 ) {
		for (int i = 0; i < 4; i++) {
			dc.FillSolidRect(&rect, RGB(102, 178, 255));
		}
	}
}


void Cyut1View::Wait(DWORD dwMillisecond)
{
	MSG msg;
	DWORD dwStart;
	dwStart = GetTickCount();

	while (GetTickCount() - dwStart < dwMillisecond)
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
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

void Circle::setPos(int x, int y)
{
	this->x = x;
	this->y = y;
}

void Map::setPos(int x1, int x2, int y1, int y2)
{
	this->x1 = x1;
	this->x2 = x2;
	this->y1 = y1;
	this->y2 = y2;
}

void Mal::setPos(int x, int y)
{
	this->x = x;
	this->y = y;
}

void Mal::setInitial(int initialX, int initialY, int endX, int endY)
{
	this->initialX = initialX;
	this->initialY = initialY;
	this->endX = endX;
	this->endY = endY;
}

void Mal::setID(int id)
{
	this->uID = id;
}

void Mal::checkPos(int Pos)
{
	if (Pos == 5)
		Pos = 30;
	else if (Pos >= 36 && Pos <= 40)
		Pos -= 21;
	else if (Pos == 10)
		Pos = 40;
	else if (Pos == 33)
		Pos = 43;
	else if (Pos > 46)
		Pos = 21;

	this->virtualPos = Pos;
}

void Player::setInitial()
{
	this->isMyturn = false;
	this->moveCount = 0;
	this->throwNum = 1;
	Do = 0;
	Gae = 0;
	Gul = 0;
	Yut = 0;
	Mo = 0;
	arrived = 0;
}

void Yut::setPos(int x, int y)
{
	this->x = x;
	this->y = y;
}

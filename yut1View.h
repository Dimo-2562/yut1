
// yut1View.h: Cyut1View 클래스의 인터페이스
//

#pragma once


class Cyut1View : public CView
{
protected: // serialization에서만 만들어집니다.
	Cyut1View() noexcept;
	DECLARE_DYNCREATE(Cyut1View)

// 특성입니다.
public:
	Cyut1Doc* GetDocument() const;
	CButton m_throwButton;
	CButton m_yutButton[5];
	CStatic m_redTurn;
	CStatic m_blueTurn;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~Cyut1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	void OnButtonClicked();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
//	virtual HRESULT accDoDefaultAction(VARIANT varChild);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	void Wait(DWORD dwMillisecond);
};

#ifndef _DEBUG  // yut1View.cpp의 디버그 버전
inline Cyut1Doc* Cyut1View::GetDocument() const
   { return reinterpret_cast<Cyut1Doc*>(m_pDocument); }
#endif

class Mal {
public:
	int virtualPos; //가상의 위치
	int x; //좌표상의 위치 - X
	int y; //좌표상의 위치 - Y
	int initialX;
	int initialY;
	int endX;
	int endY;
	int uID; // uID
	bool isClicked; //클릭되었는가?
	CButton button;

	void setPos(int, int);
	void setInitial(int, int, int, int);
	void setID(int);
	void checkPos(int);
};

class Circle {
public:
	int x;
	int y;
	void setPos(int, int);
};

class Map {
public:
	int x1;
	int x2;
	int y1;
	int y2;
	void setPos(int, int, int, int);
};

class Player {
public:
	bool isMyturn;
	int moveCount;
	int throwNum;
	int Do;
	int Gae;
	int Gul;
	int Yut;
	int Mo;
	int arrived;
	void setInitial();
};

class Yut {
public:
	int x;
	int y;
	bool isFront;
	void setPos(int, int);
};


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
	int background_x1, background_x2, background_y1, background_y2; // 배경 좌표

	int bigMovePoint_X[5];
	int bigMovePoint_Y[5];

	int upMovePoint_X[4], leftMovePoint_X[4], rightMovePoint_X[4], downMovePoint_X[4], innerMovePoint_X[4], outerMovePoint_X[4];
	int upMovePoint_Y[4], leftMovePoint_Y[4], rightMovePoint_Y[4], downMovePoint_Y[4], innerMovePoint_Y[4], outerMovePoint_Y[4];

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
};

#ifndef _DEBUG  // yut1View.cpp의 디버그 버전
inline Cyut1Doc* Cyut1View::GetDocument() const
   { return reinterpret_cast<Cyut1Doc*>(m_pDocument); }
#endif


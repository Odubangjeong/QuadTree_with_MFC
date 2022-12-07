
// quadTree2018161018View.h: CquadTree2018161018View 클래스의 인터페이스
//

#pragma once
#include "qtree.hpp"

class CquadTree2018161018View : public CFormView
{
protected: // serialization에서만 만들어집니다.
	CquadTree2018161018View() noexcept;
	DECLARE_DYNCREATE(CquadTree2018161018View)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_QUADTREE2018161018_FORM };
#endif

// 특성입니다.
public:
	CquadTree2018161018Doc* GetDocument() const;

// 작업입니다.
public:

// 변수
protected:
	int CompressComplete = 0, imageSelected = 0;

	
	// 클래스
	qt_tree tree;

	// 파일 경로
	CString file;
	CString strPathName;

	cv::Mat current_original_img;
	cv::Mat current_modified_img;

	//
	int current_target_deviation;
	int current_min_pixel_size;

	// resoluation
	int current_height;
	int current_width;

	// origin and compressed size (File size)
	unsigned long current_orignal_Bytes;
	unsigned long current_modified_Bytes;
	float current_CompRate;

	// PSNR (dB)
	int current_PSNR;

public:

	cv::Mat m_matImage;
	// Bitmap info: before, after compression
	BITMAPINFO* m_pBitmapInfo;
	BITMAPINFO* m_pBitmapInfo_before;
	BITMAPINFO* m_pBitmapInfo_after;
	void CquadTree2018161018View::DrawImage_before();
	void CquadTree2018161018View::DrawImage_after();
	void CquadTree2018161018View::CreateBitmapInfo_before();
	void CquadTree2018161018View::CreateBitmapInfo_after();
	
	void readyImage();
	void printImage();

//	qt_tree tree;
// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
// 구현입니다.
public:
	virtual ~CquadTree2018161018View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnStnClickedCancel();
	afx_msg void OnBnClickedButtonFilebrowser();
	// 파일 이름.
	CEdit fileName;
	// 표준편차 입력값
	CEdit Edit_SD;
	// 최소블록크기 입력
	CEdit Edit_minblockSize;
	afx_msg void OnBnClickedButtonCompress();
	// 해상도 출력
	CStatic mTextResolution;
	// 원본 크기
	CStatic mTestOriginSize;
	// 원본 이미지
	CStatic mPic_origin;
	// 화질
	CStatic mTextPSNR;
	afx_msg void OnPaint();
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnEnChangeEditFile();
	// 압축 크기
	CStatic mTextModSize;
	// 압축률
	CStatic mTextRate;
};

#ifndef _DEBUG  // quadTree2018161018View.cpp의 디버그 버전
inline CquadTree2018161018Doc* CquadTree2018161018View::GetDocument() const
   { return reinterpret_cast<CquadTree2018161018Doc*>(m_pDocument); }
#endif


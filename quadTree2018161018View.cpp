
// quadTree2018161018View.cpp: CquadTree2018161018View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "quadTree2018161018.h"
#endif

#include "quadTree2018161018Doc.h"
#include "quadTree2018161018View.h"

#include "afxwin.h"

#include "opencv2/opencv.hpp"
#include "qtree.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CquadTree2018161018View

IMPLEMENT_DYNCREATE(CquadTree2018161018View, CFormView)

BEGIN_MESSAGE_MAP(CquadTree2018161018View, CFormView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CFormView::OnFilePrintPreview)
	//ON_BN_CLICKED(IDC_BUTTON1, &CquadTree2018161018View::OnBnClickedButton1)
	ON_STN_CLICKED(IDCANCEL, &CquadTree2018161018View::OnStnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_FileBrowser, &CquadTree2018161018View::OnBnClickedButtonFilebrowser)
	ON_BN_CLICKED(IDC_BUTTON_COMPRESS, &CquadTree2018161018View::OnBnClickedButtonCompress)
	ON_WM_PAINT()
	ON_WM_GETMINMAXINFO()
	ON_EN_CHANGE(IDC_EDIT_File, &CquadTree2018161018View::OnEnChangeEditFile)
END_MESSAGE_MAP()


// CquadTree2018161018View 생성/소멸

CquadTree2018161018View::CquadTree2018161018View() noexcept
	: CFormView(IDD_QUADTREE2018161018_FORM)
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CquadTree2018161018View::~CquadTree2018161018View()
{
}

void CquadTree2018161018View::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_File, fileName);
	DDX_Control(pDX, IDC_Edit_SD, Edit_SD);
	DDX_Control(pDX, IDC_Edit_MINBLOCKSIZE, Edit_minblockSize);
	DDX_Control(pDX, IDC_TEXT_Resolution, mTextResolution);
	DDX_Control(pDX, IDC_TEXT_origin_size, mTestOriginSize);
	DDX_Control(pDX, IDC_PIC_Original, mPic_origin);
	DDX_Control(pDX, IDC_TEXT_PSNR, mTextPSNR);
	DDX_Control(pDX, IDC_TEXT_mod_size, mTextModSize);
	DDX_Control(pDX, IDC_TEXT_Compress_size, mTextRate);
}

BOOL CquadTree2018161018View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CFormView::PreCreateWindow(cs);
}

void CquadTree2018161018View::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();
	GetDlgItem(IDC_Edit_SD)->SetWindowTextA("30");
	GetDlgItem(IDC_Edit_MINBLOCKSIZE)->SetWindowTextA("4");
}


// CquadTree2018161018View 인쇄

BOOL CquadTree2018161018View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CquadTree2018161018View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CquadTree2018161018View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CquadTree2018161018View::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: 여기에 사용자 지정 인쇄 코드를 추가합니다.
}


// CquadTree2018161018View 진단

#ifdef _DEBUG
void CquadTree2018161018View::AssertValid() const
{
	CFormView::AssertValid();
}

void CquadTree2018161018View::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CquadTree2018161018Doc* CquadTree2018161018View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CquadTree2018161018Doc)));
	return (CquadTree2018161018Doc*)m_pDocument;
}
#endif //_DEBUG


// CquadTree2018161018View 메시지 처리기


void CquadTree2018161018View::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}



void CquadTree2018161018View::OnStnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CquadTree2018161018View::OnBnClickedButtonFilebrowser()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//	CWaitCursor wait;
	
//	BROWSEINFO BrInfo;
//	CFileDialog dlg(TRUE, _T("*.dat"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, file, this);

	static TCHAR BASED_CODE szFilter[] = _T("이미지 파일(*.BMP,, *.JPG, *.PNG) | *.BMP;*.JPG;*.PNG;*.bmp;*.jpg;*.png; |모든파일(*.*)|*.*||");

	CFileDialog dlg(TRUE, _T("*.jpg"), _T("image"), OFN_HIDEREADONLY, szFilter);

	if (dlg.DoModal() == IDOK)
	{
		strPathName = dlg.GetPathName();
		file = dlg.GetFileName();

		// SetDlgItemText(IDC_EDIT1, strPathName);

		// 사진선택 옆 파일 주소 출력
		fileName.SetWindowText(strPathName);

		// file size 가져오기
		CFile file;
		file.Open(strPathName, CFile::modeRead);
		current_orignal_Bytes = file.GetLength();

	}
	else return;

		// 해상도 출력, 원본 크기 출력, 원본 이미지 출력
		std::string s((LPCTSTR)strPathName);
		tree.fileopen(s);

		current_width = tree.origin_cols;
		current_height = tree.origin_rows;
		current_original_img = tree.original.clone();

		CString _temp_string;


		// 해상도 출력
		_temp_string.Format("해상도 : %d*%d", current_width, current_height);
		mTextResolution.SetWindowTextA(_temp_string);



		// 데이터 크기
		current_orignal_Bytes = current_width * current_height;
		_temp_string.Format("원본크기\n %d Bytes", current_orignal_Bytes);
		mTestOriginSize.SetWindowTextA(_temp_string);

		CreateBitmapInfo_before();
		DrawImage_before();

		// Flag: 이미지 선택됨
		imageSelected = 1;
		CompressComplete = 0;

		current_target_deviation = GetDlgItemInt(IDC_Edit_SD);
		current_min_pixel_size = GetDlgItemInt(IDC_Edit_MINBLOCKSIZE);
		OnBnClickedButtonCompress();
	
}


void CquadTree2018161018View::DrawImage_before()
{
	CClientDC dc(GetDlgItem(IDC_PIC_Original));

	CRect rect;
	GetDlgItem(IDC_PIC_Original)->GetClientRect(&rect);

	SetStretchBltMode(dc.GetSafeHdc(), COLORONCOLOR);
	StretchDIBits(dc.GetSafeHdc(), 0, 0, rect.Width(), rect.Height(), 0, 0, current_original_img.cols, current_original_img.rows, current_original_img.data, m_pBitmapInfo_before, DIB_RGB_COLORS, SRCCOPY);
}

void CquadTree2018161018View::DrawImage_after()
{
	CClientDC dc(GetDlgItem(IDC_PIC_Modified));

	CRect rect;
	GetDlgItem(IDC_PIC_Modified)->GetClientRect(&rect);

	SetStretchBltMode(dc.GetSafeHdc(), COLORONCOLOR);
	StretchDIBits(dc.GetSafeHdc(), 0, 0, rect.Width(), rect.Height(), 0, 0, current_modified_img.cols, current_modified_img.rows, current_modified_img.data, m_pBitmapInfo_after, DIB_RGB_COLORS, SRCCOPY);
}


void CquadTree2018161018View::CreateBitmapInfo_before()
{
	int bpp = current_original_img.channels() * 8;
	/*
	if (m_pBitmapInfo != NULL)
	{
		delete m_pBitmapInfo;
		m_pBitmapInfo = NULL;
	}
	*/
	if (bpp == 8)
		m_pBitmapInfo_before = (BITMAPINFO*) new BYTE[sizeof(BITMAPINFO) + 255 * sizeof(RGBQUAD)];
	else // 24 or 32bit
		m_pBitmapInfo_before = (BITMAPINFO*) new BYTE[sizeof(BITMAPINFO)];

	m_pBitmapInfo_before->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	m_pBitmapInfo_before->bmiHeader.biPlanes = 1;
	m_pBitmapInfo_before->bmiHeader.biBitCount = bpp;
	m_pBitmapInfo_before->bmiHeader.biCompression = BI_RGB;
	m_pBitmapInfo_before->bmiHeader.biSizeImage = 0;
	m_pBitmapInfo_before->bmiHeader.biXPelsPerMeter = 0;
	m_pBitmapInfo_before->bmiHeader.biYPelsPerMeter = 0;
	m_pBitmapInfo_before->bmiHeader.biClrUsed = 0;
	m_pBitmapInfo_before->bmiHeader.biClrImportant = 0;

	if (bpp == 8)
	{
		for (int i = 0; i < 256; i++)
		{
			m_pBitmapInfo_before->bmiColors[i].rgbBlue = (BYTE)i;
			m_pBitmapInfo_before->bmiColors[i].rgbGreen = (BYTE)i;
			m_pBitmapInfo_before->bmiColors[i].rgbRed = (BYTE)i;
			m_pBitmapInfo_before->bmiColors[i].rgbReserved = 0;
		}
	}

	m_pBitmapInfo_before->bmiHeader.biWidth = current_original_img.cols;
	m_pBitmapInfo_before->bmiHeader.biHeight = -current_original_img.rows;
}

void CquadTree2018161018View::CreateBitmapInfo_after()
{
	int bpp = current_modified_img.channels() * 8;
	/*
	if (m_pBitmapInfo_after != NULL)
	{
		delete m_pBitmapInfo_after;
		m_pBitmapInfo_after = NULL;
	}
	*/
	if (bpp == 8)
		m_pBitmapInfo_after = (BITMAPINFO*) new BYTE[sizeof(BITMAPINFO) + 255 * sizeof(RGBQUAD)];
	else // 24 or 32bit
		m_pBitmapInfo_after = (BITMAPINFO*) new BYTE[sizeof(BITMAPINFO)];

	m_pBitmapInfo_after->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	m_pBitmapInfo_after->bmiHeader.biPlanes = 1;
	m_pBitmapInfo_after->bmiHeader.biBitCount = bpp;
	m_pBitmapInfo_after->bmiHeader.biCompression = BI_RGB;
	m_pBitmapInfo_after->bmiHeader.biSizeImage = 0;
	m_pBitmapInfo_after->bmiHeader.biXPelsPerMeter = 0;
	m_pBitmapInfo_after->bmiHeader.biYPelsPerMeter = 0;
	m_pBitmapInfo_after->bmiHeader.biClrUsed = 0;
	m_pBitmapInfo_after->bmiHeader.biClrImportant = 0;

	if (bpp == 8)
	{
		for (int i = 0; i < 256; i++)
		{
			m_pBitmapInfo_after->bmiColors[i].rgbBlue = (BYTE)i;
			m_pBitmapInfo_after->bmiColors[i].rgbGreen = (BYTE)i;
			m_pBitmapInfo_after->bmiColors[i].rgbRed = (BYTE)i;
			m_pBitmapInfo_after->bmiColors[i].rgbReserved = 0;
		}
	}

	m_pBitmapInfo_after->bmiHeader.biWidth = current_modified_img.cols;
	m_pBitmapInfo_after->bmiHeader.biHeight = -current_modified_img.rows;
}

void CquadTree2018161018View::OnBnClickedButtonCompress()
{
	// TODO: 압축&복원 버튼 눌렀을 시 동작
	// PSNR, 압축률, 크기 출력
	// picture controll에 사진 출력
	CWaitCursor wait;
	BeginWaitCursor();
	std::string s((LPCTSTR)strPathName);
	
	// 높이와 너비
	current_height = tree.origin_cols;
	current_width = tree.origin_rows;

	// 컨트롤에서 값 가져오기
	current_target_deviation = GetDlgItemInt(IDC_Edit_SD);
	current_min_pixel_size = GetDlgItemInt(IDC_Edit_MINBLOCKSIZE);

	// tree 만들기
	tree.make_quadTree(s, current_target_deviation, current_min_pixel_size);
	current_modified_img = tree.modified.clone();
	current_PSNR = tree.PSNR;
	// 이미지 출력
	CreateBitmapInfo_after();
	DrawImage_after();
	// 정보 출력
	CString _temp_PSNR;
	_temp_PSNR.Format("화질 (PSNR dB)\n%d dB", current_PSNR);
	mTextPSNR.SetWindowTextA(_temp_PSNR);

	current_modified_Bytes = tree.fileByte;
	CString compressed;
	compressed.Format("압축 크기\n%d Bytes", current_modified_Bytes);
	mTextModSize.SetWindowTextA(compressed);

	current_CompRate = (current_orignal_Bytes - current_modified_Bytes) * 100 / current_orignal_Bytes;
	CString rate;
	rate.Format("압축률\n%d-%d\n*100/%d\n= %.2f%%", current_orignal_Bytes, current_modified_Bytes, current_orignal_Bytes, current_CompRate);
	mTextRate.SetWindowTextA(rate);

	// 압축 출력 완료, 마우스 잠금 해제
	CompressComplete = 1;
	EndWaitCursor();
	wait.Restore();
}


void CquadTree2018161018View::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CFormView::OnPaint()을(를) 호출하지 마십시오.
//	CreateBitmapInfo_before();
//	DrawImage_before();
	if (imageSelected) {
		DrawImage_before();
	}
	if (CompressComplete) {
		DrawImage_after();
	}

	
}


void CquadTree2018161018View::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CFormView::OnGetMinMaxInfo(lpMMI);
}


void CquadTree2018161018View::OnEnChangeEditFile()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CFormView::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

#include "stdafx.h"
#include "rdoprocess_toolbar.h"
#include "../resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// ----------------------------------------------------------------------------
// ---------- RPToolBar
// ----------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(RPToolBar, CToolBar)
	//{{AFX_MSG_MAP(RPToolBar)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

RPToolBar::RPToolBar():
	CToolBar(),
	color_brush( RGB(0xFF, 0xFF, 0xA0) ),
	color_pen  ( RGB(0xA0, 0xA0, 0xFF) ),
	color_text ( RGB(0xF0, 0xF0, 0xF0) ),
	empty_brush( false ),
	empty_pen( false ),
	empty_text( false )
{
}

RPToolBar::~RPToolBar()
{
}

void RPToolBar::OnPaint()
{
	CToolBar::OnPaint();
	CClientDC dc( this );

	CToolBarCtrl& tb = GetToolBarCtrl();
	CRect  rect;
	CPen   pen;
	CBrush brush;
	if ( !empty_brush && tb.IsButtonEnabled(ID_BTN_FILL_BRUSH) ) {
		pen.CreatePen( PS_SOLID, 1, RGB(0x00, 0x00, 0x00) );
		brush.CreateSolidBrush( color_brush );
	} else {
		pen.CreatePen( PS_SOLID, 1, RGB(0x80, 0x80, 0x80) );
		brush.CreateStockObject( NULL_BRUSH );
	}
	CPen*   old_pen   = dc.SelectObject( &pen );
	CBrush* old_brush = dc.SelectObject( &brush );
	tb.GetRect( ID_BTN_FILL_BRUSH, rect );
	rect.right = rect.left + LOWORD(tb.GetButtonSize());
	rect.right  -= 3;
	rect.bottom -= 2;
	rect.left    = rect.right - 10;
	rect.top     = rect.bottom - 5;
	dc.Rectangle( rect );

	dc.SelectObject( old_pen );
	dc.SelectObject( old_brush );
	pen.DeleteObject();
	brush.DeleteObject();
	if ( !empty_pen && tb.IsButtonEnabled(ID_BTN_FILL_PEN) ) {
		pen.CreatePen( PS_SOLID, 1, RGB(0x00, 0x00, 0x00) );
		brush.CreateSolidBrush( color_pen );
	} else {
		pen.CreatePen( PS_SOLID, 1, RGB(0x80, 0x80, 0x80) );
		brush.CreateStockObject( NULL_BRUSH );
	}
	old_pen   = dc.SelectObject( &pen );
	old_brush = dc.SelectObject( &brush );
	tb.GetRect( ID_BTN_FILL_PEN, rect );
	rect.right = rect.left + LOWORD(tb.GetButtonSize());
	rect.right  -= 3;
	rect.bottom -= 2;
	rect.left    = rect.right - 10;
	rect.top     = rect.bottom - 5;
	dc.Rectangle( rect );

	dc.SelectObject( old_pen );
	dc.SelectObject( old_brush );
	pen.DeleteObject();
	brush.DeleteObject();
	if ( !empty_text && tb.IsButtonEnabled(ID_BTN_FILL_FONT) ) {
		pen.CreatePen( PS_SOLID, 1, RGB(0x00, 0x00, 0x00) );
		brush.CreateSolidBrush( color_text );
	} else {
		pen.CreatePen( PS_SOLID, 1, RGB(0x80, 0x80, 0x80) );
		brush.CreateStockObject( NULL_BRUSH );
	}
	old_pen   = dc.SelectObject( &pen );
	old_brush = dc.SelectObject( &brush );
	tb.GetRect( ID_BTN_FILL_FONT, rect );
	rect.right = rect.left + LOWORD(tb.GetButtonSize());
	rect.right  -= 3;
	rect.bottom -= 2;
	rect.left    = rect.right - 10;
	rect.top     = rect.bottom - 5;
	dc.Rectangle( rect );

	dc.SelectObject( old_pen );
	dc.SelectObject( old_brush );
}
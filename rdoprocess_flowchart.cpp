#include "stdafx.h"
#include "rdoprocess_flowchart.h"
#include "rdoprocess_object.h"
#include "rdoprocess_shape_action.h"
#include "rdoprocess_shape_if.h"
#include "rdoprocess_app.h"
#include "rdoprocess_math.h"
#include "rdoprocess_messages.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// ----------------------------------------------------------------------------
// ---------- RPFlowChartObject
// ----------------------------------------------------------------------------
RPFlowChartObject::RPFlowChartObject( RPObject* _parent, RPChartObject* _chart_parent, RPFlowChart* _flowchart ):
	RPChartObject( _parent, _chart_parent, _flowchart, _T("Flowchart") )
{
	rpapp.msg().connect( this, rp::msg::RP_FLOWSTATE_CHANGED );
}

void RPFlowChartObject::notify( RPObject* from, UINT message, WPARAM wParam, LPARAM lParam )
{
	if ( message == rp::msg::RP_FLOWSTATE_CHANGED ) {
		flowchart->updateFlowState();
		RPProject::FlowState flow_state = static_cast<RPProject::FlowState>(wParam);
		switch ( flow_state ) {
			case RPProject::flow_select   : break;
			case RPProject::flow_connector: break;
			case RPProject::flow_rotate   : break;
		}
	}
}

// ----------------------------------------------------------------------------
// ---------- RPFlowChart
// ----------------------------------------------------------------------------
const int grid_dx_plus = 1;
const int grid_dy_plus = 2;
const int grid_timer_id = 1;

#ifdef TEST_SPEED // =====================================
const int sec_timer_id = 2;
const int base_speed = 10000;
#endif // ================================================

BEGIN_MESSAGE_MAP( RPFlowChart,CWnd )
	//{{AFX_MSG_MAP(RPFlowChart)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	ON_WM_SETCURSOR()
	ON_WM_NCHITTEST()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

RPFlowChart::RPFlowChart():
	CWnd(),
	border_w( 7 ),
	border_h( 7 ),
	paper_border_w( 7 ),
	paper_border_h( 7 ),
	paper_border( 1 ),
	paper_shadow( 2 ),
	pixmap_w_real( 0 ),
	pixmap_h_real( 0 ),
	pixmap_w_show( 0 ),
	pixmap_h_show( 0 ),
	client_width( 0 ),
	client_height( 0 ),
	select_box_size2( 4 ),
	mem_bmp( NULL ),
	saved_dc( 0 ),
	saved_mem_dc( 0 ),
	font_first( NULL ),
	bmp_first( NULL ),
	pen_black( PS_SOLID, 1, RGB(0x00, 0x00, 0x00) ),
	pen_shape_color( PS_SOLID, 1, RGB(0x00, 0x00, 0x00) ),
	pen_selected_line( PS_DOT, 1, RGB(0x00, 0xFF, 0x00) ),
	pen_selected_box( PS_SOLID, 1, RGB(0x00, 0x00, 0x00) ),
	brush_selected_box( RGB(0x00, 0xFF, 0x00) ),
	paper_border_color( RGB(0xC0, 0xC0, 0xC0) ),
	paper_shadow_color( RGB(0x80, 0x80, 0x80) ),
	paper_bg_color( RGB(0xFF, 0xFF, 0xFF) ),
	flowobj( NULL ),
	global_mouse_pos_prev( 0, 0 ),
	one_object( NULL ),
	one_object_pcmd( RPChartObject::pcmd_none )
#ifdef TEST_SPEED // =====================================
	,
	sec_cnt( 0 ),
	sec_timer( 0 ),
	makepixmap_cnt( 0 ),
	makegrid_cnt( 0 ),
	makegridempty_cnt( 0 )
#endif // ================================================
{
	flowobj = new RPFlowChartObject( &rpapp.project(), NULL, this );
}

RPFlowChart::~RPFlowChart()
{
}

BOOL RPFlowChart::PreCreateWindow( CREATESTRUCT& cs )
{
	if ( !CWnd::PreCreateWindow(cs) ) return FALSE;

	cs.style &= ~WS_BORDER;
	cs.style |= WS_HSCROLL | WS_VSCROLL;
	cs.lpszClass = AfxRegisterWndClass( CS_DBLCLKS | CS_OWNDC, ::LoadCursor(NULL, IDC_ARROW) );

	return TRUE;
}

RPShapeAction* shape_action = NULL;
RPShapeIf*     shape_if     = NULL;

BOOL RPFlowChart::Create( LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext )
{
	if ( !CWnd::Create( lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext ) ) return false;

	CDC* dc = GetDC();
	if ( !mem_dc.CreateCompatibleDC( dc ) ) {
		ReleaseDC( dc );
		return false;
	}

	// ��������� ��������� DC ��� �������������� ����� ���������
	saved_dc     = dc->SaveDC();
	saved_mem_dc = mem_dc.SaveDC();
	font_first   = mem_dc.GetCurrentFont();
	bmp_first    = mem_dc.GetCurrentBitmap();
	ReleaseDC( dc );
	if ( !saved_dc || !saved_mem_dc ) return false;

	mem_dc.SetBkMode( TRANSPARENT );

//	updateFont();
	updateScrollBars();

	shape_action = new RPShapeAction( flowobj, this );
	shape_if = new RPShapeIf( flowobj, this );
	shape_if->setPosition( 200, 100 );

#ifdef TEST_SPEED // =====================================
	sec_timer = SetTimer( sec_timer_id, 1000, NULL );
#endif // ================================================

	return true;
}

void RPFlowChart::OnDestroy()
{
#ifdef TEST_SPEED // =====================================
	if ( sec_timer ) {
		KillTimer( sec_timer );
		sec_timer = 0;
	}
#endif // ================================================
//	if ( grid_timer ) {
//		KillTimer( grid_timer );
//		grid_timer = 0;
//	}
	if ( flowobj ) {
		delete flowobj;
		flowobj = NULL;
	}
	CDC* dc = GetDC();
	if ( dc ) {
		dc->RestoreDC( saved_dc );
	}
	ReleaseDC( dc );
	if ( mem_dc.m_hDC ) {
		mem_dc.SelectObject( font_first );
		mem_dc.SelectObject( bmp_first );
		if ( mem_bmp ) {
			mem_bmp->DeleteObject();
			delete mem_bmp;
		}
		mem_dc.RestoreDC( saved_mem_dc );
		mem_dc.DeleteDC();
	}
//	if ( grid_bmp.GetSafeHandle() ) {
//		grid_dc.SelectObject( bmp_first );
//		grid_bmp.DeleteObject();
//	}
	CWnd::OnDestroy();
}

std::list< RPChartObject* >::iterator RPFlowChart::find( const RPChartObject* object )
{
	return std::find( objects.begin(), objects.end(), object );
}

void RPFlowChart::insertShape( RPShape* shape )
{
	if ( find( shape ) == objects.end() ) {
		objects.push_back( shape );
/*
		if ( !connectors_before_create.empty() ) {
			std::list< CBDFlowChartConnector >::iterator it = connectors_before_create.begin();
			while ( it != connectors_before_create.end() ) {
				if ( it->shape_from == new_shape ) {
					it->shape_from = shape;
				} else if ( it->shape_to == new_shape ) {
					it->shape_to = shape;
				}
				connectors.push_back( *it );
				it++;
			}
			connectors_before_create.clear();
		}
*/
	}
	updateDC();
}

void RPFlowChart::deleteShape( RPShape* shape )
{
	std::list< RPChartObject* >::iterator it = find( shape );
	if ( it != objects.end() ) {
		objects.erase( it );

//		if ( movingShape == shape ) {
//			movingShape = NULL;
//			moving_stop();
//		}

		updateScrollBars();
		updateDC();
	}
}

CSize RPFlowChart::getFlowSize( const std::list< RPChartObject* >& list ) const
{
	int max_x = 0;
	int max_y = 0;
	std::list< RPChartObject* >::const_iterator it = list.begin();
	while ( it != list.end() ) {
		rp::rect rect = (*it)->getBoundingRect();
		if ( rect.getMaxX() > max_x ) {
			max_x = rect.getMaxX();
		}
		if ( rect.getMaxY() > max_y ) {
			max_y = rect.getMaxY();
		}
		it++;
	}
	return CSize( max_x, max_y );
}

void RPFlowChart::updateScrollBars()
{
	CSize size = getFlowSize();

	SCROLLINFO si;
	si.cbSize = sizeof( si );
	si.fMask  = SIF_RANGE | SIF_PAGE | SIF_POS;

	int max_x = size.cx + border_w * 2 + paper_border_w * 2 - 1;
	int max_y = size.cy + border_h * 2 + paper_border_h * 2 - 1;
	int scroll_x_pos = flowobj->matrix_transform.dx();
	int scroll_y_pos = flowobj->matrix_transform.dy();
	if ( scroll_x_pos + pixmap_w_show > max_x ) scroll_x_pos = max_x - pixmap_w_show;
	if ( scroll_y_pos + pixmap_h_show > max_y ) scroll_y_pos = max_y - pixmap_h_show;
	if ( scroll_x_pos < 0 ) scroll_x_pos = 0;
	if ( scroll_y_pos < 0 ) scroll_y_pos = 0;
	flowobj->matrix_transform.dx() = scroll_x_pos;
	flowobj->matrix_transform.dy() = scroll_y_pos;

	si.nMin   = 0;
	si.nMax   = max_x;
	si.nPos   = scroll_x_pos;
	si.nPage  = client_width;
	SetScrollInfo( SB_HORZ, &si, TRUE );

	si.nMin   = 0;
	si.nMax   = max_y;
	si.nPos   = scroll_y_pos;
	si.nPage  = client_height;
	SetScrollInfo( SB_VERT, &si, TRUE );
}

void RPFlowChart::updateDC()
{
	InvalidateRect( NULL );
	UpdateWindow();
}

void RPFlowChart::modify()
{
}

void RPFlowChart::OnSize( UINT nType, int cx, int cy )
{
	CWnd::OnSize( nType, cx, cy );
//	grid_pa.resize( 0 );
	makeNewPixmap();
	updateDC();
}

void RPFlowChart::makeNewPixmap()
{
#ifdef TEST_SPEED // =====================================
	makepixmap_cnt++;

	SYSTEMTIME t1;
	SYSTEMTIME t2;
	::GetSystemTime( &t1 );
#endif // ================================================

	int pixmap_w_show_old = pixmap_w_show;
	int pixmap_h_show_old = pixmap_h_show;

#ifdef TEST_SPEED // =====================================
	for ( int cnt = 0; cnt <= base_speed * 10; cnt++ ) {
#endif // ================================================

	CRect client_rect;
	GetClientRect( &client_rect );
	client_width  = client_rect.Width();
	client_height = client_rect.Height();

	int new_pixmap_w_real = client_width - border_w * 2;
	int new_pixmap_h_real = client_height - border_h * 2;
	if ( pixmap_w_real < new_pixmap_w_real || pixmap_h_real < new_pixmap_h_real ) {
		if ( mem_bmp ) {
			mem_dc.SelectObject( bmp_first );
			mem_bmp->DeleteObject();
			delete mem_bmp;
			mem_bmp = NULL;
		}
		pixmap_w_real = new_pixmap_w_real;
		pixmap_h_real = new_pixmap_h_real;
		mem_bmp = new CBitmap();
		CDC* dc = GetDC();
		mem_bmp->CreateCompatibleBitmap( dc, pixmap_w_real, pixmap_h_real );
		ReleaseDC( dc );
		mem_dc.SelectObject( mem_bmp );
	}
	pixmap_w_show = client_width - border_w * 2 - paper_border_w * 2;
	if ( pixmap_w_show > pixmap_w_real ) {
		pixmap_w_show = pixmap_w_real;
	}
	pixmap_h_show = client_height - border_h * 2 - paper_border_h * 2;
	if ( pixmap_h_show > pixmap_h_real ) {
		pixmap_h_show = pixmap_h_real;
	}

	updateScrollBars();

#ifdef TEST_SPEED // =====================================
	}
	::GetSystemTime( &t2 );
	int delay = (t2.wMinute * 1000 * 60 + t2.wSecond * 1000 + t2.wMilliseconds) - (t1.wMinute * 1000 * 60 + t1.wSecond * 1000 + t1.wMilliseconds);
	TRACE( "makepixmap_delay = %d\n", delay );
#endif // ================================================

	if ( pixmap_w_show_old != pixmap_w_show || pixmap_h_show_old != pixmap_h_show ) {
		makeGrid();
	}
}

void RPFlowChart::makeGrid()
{
/*
#ifdef TEST_SPEED // =====================================
	makegridempty_cnt++;
#endif // ================================================

	if ( pixmap_w_show <= paper_border_w * 2 || pixmap_h_show <= paper_border_h * 2 ) {
		grid_cnt_x = 0;
		grid_cnt_y = 0;
		grid_pa.clear();
		return;
	}

#ifdef TEST_SPEED // =====================================
	makegrid_cnt++;
	SYSTEMTIME t1;
	SYSTEMTIME t2;
	::GetSystemTime( &t1 );
	for ( int cnt = 0; cnt <= base_speed * 10; cnt++ ) {
#endif // ================================================

	CSize size = getFlowSize();
	grid_cnt_x = (max(size.cx, scroll_x_pos + pixmap_w_show - paper_border_w * 2) / grid_step) + 1;
	grid_cnt_y = (max(size.cy, scroll_y_pos + pixmap_h_show - paper_border_h * 2) / grid_step) + 1;
	if ( grid_pa.empty() && grid_bmp.m_hObject ) {
		grid_dc.SelectObject( bmp_first );
		grid_bmp.Detach();
		grid_bmp.DeleteObject();
		grid_bmp.m_hObject = NULL;
	}
	CDC* dc = GetDC();
	if ( grid_type == gtPoints ) {
		if ( !grid_bmp.m_hObject ) {
			// brush
			if ( grid_step < 10 ) {
				grid_bmp_width = grid_step * 50;
			} else if ( grid_step < 25 ) {
				grid_bmp_width = grid_step * 25;
			} else {
				grid_bmp_width = grid_step * 10;
			}
			if ( !grid_dc.m_hDC ) {
				grid_dc.CreateCompatibleDC( dc );
			}
			grid_bmp.CreateCompatibleBitmap( dc, grid_bmp_width, grid_bmp_width );
			grid_dc.SelectObject( &grid_bmp );
			grid_dc.FillSolidRect( 0, 0, grid_bmp_width, grid_bmp_width, paper_bg_color );
			for ( int i = 0; i < grid_bmp_width / grid_step; i++ ) {
				for ( int j = 0; j < grid_bmp_width / grid_step; j++ ) {
					grid_dc.SetPixelV( i * grid_step, j * grid_step, grid_color );
				}
			}
		}
		// points array
		grid_pa.resize( grid_cnt_x * grid_cnt_y );
		for ( int i = 0; i < grid_cnt_x; i++ ) {
			for ( int j = 0; j < grid_cnt_y; j++ ) {
				grid_pa[ i + j * grid_cnt_x ]. x = i * grid_step + paper_border_w;
				grid_pa[ i + j * grid_cnt_x ]. y = j * grid_step + paper_border_h;
			}
		}
	} else {
		if ( !grid_bmp.m_hObject ) {
			// brush
			if ( grid_step < 100 ) {
				grid_bmp_width = grid_step * 4;
			} else if ( grid_step < 300 ) {
				grid_bmp_width = grid_step * 2;
			} else {
				grid_bmp_width = grid_step;
			}
			if ( !grid_dc.m_hDC ) {
				grid_dc.CreateCompatibleDC( dc );
			}
			grid_bmp.CreateCompatibleBitmap( dc, grid_bmp_width, grid_bmp_width );
			grid_dc.SelectObject( &grid_bmp );
			grid_dc.FillSolidRect( 0, 0, grid_bmp_width, grid_bmp_width, paper_bg_color );
			CPen pen;
			if ( grid_type == gtSolidLines ) {
				pen.CreatePen( PS_SOLID, 1, grid_color );
			} else {
				pen.CreatePen( PS_DOT, 1, grid_color );
			}
			grid_dc.SelectObject( pen );
			int y1 = 0;
			int y2 = grid_bmp_width;
			for ( int i = 0; i < grid_bmp_width / grid_step; i++ ) {
				int x = i * grid_step;
				grid_dc.MoveTo( x, y1 );
				grid_dc.LineTo( x, y2 );
			}
			int x1 = 0;
			int x2 = grid_bmp_width;
			for ( int j = 0; j < grid_bmp_width / grid_step; j++ ) {
				int y = j * grid_step;
				grid_dc.MoveTo( x1, y );
				grid_dc.LineTo( x2, y );
			}
		}
		// points array
		grid_pa.resize( grid_cnt_x * 2 + grid_cnt_y * 2 );
		int index = 0;
		int y1 = paper_border_h;
		int y2 = pixmap_h_show - paper_border_h;
		for ( int i = 0; i < grid_cnt_x; i++ ) {
			int x = i * grid_step + paper_border_w;
			grid_pa[ index++ ] = CPoint( x, y1 );
			grid_pa[ index++ ] = CPoint( x, y2 );
		}
		int x1 = paper_border_w;
		int x2 = pixmap_w_show - paper_border_w;
		for ( int j = 0; j < grid_cnt_y; j++ ) {
			int y = j * grid_step + paper_border_h;
			grid_pa[ index++ ] = CPoint( x1, y );
			grid_pa[ index++ ] = CPoint( x2, y );
		}
	}
	ReleaseDC( dc );

#ifdef TEST_SPEED // =====================================
	}
	::GetSystemTime( &t2 );
	int delay = (t2.wMinute * 1000 * 60 + t2.wSecond * 1000 + t2.wMilliseconds) - (t1.wMinute * 1000 * 60 + t1.wSecond * 1000 + t1.wMilliseconds);
	TRACE( "makegrid_delay = %d\n", delay );
#endif // ================================================
*/
}

void RPFlowChart::OnPaint() 
{
#ifdef TEST_SPEED // =====================================
	SYSTEMTIME t0;
	SYSTEMTIME t1;
	SYSTEMTIME t2;
	SYSTEMTIME t3;
	SYSTEMTIME t4;
	SYSTEMTIME t5;
	SYSTEMTIME t6;
	SYSTEMTIME t7;
	::GetSystemTime( &t0 );
#endif // ================================================

	CPaintDC dc( this );
	dc.SaveDC();

	CRect client_rect;
	GetClientRect( &client_rect );
	client_width  = client_rect.Width();
	client_height = client_rect.Height();


	if ( client_width < border_w * 2 || client_height < border_h * 2 ) {

#ifdef TEST_SPEED // =====================================
		for ( int cnt1 = 0; cnt1 <= base_speed * 10; cnt1++ ) {
#endif // ================================================

		dc.FillSolidRect( 0, 0, client_width, client_height, paper_border_color );

#ifdef TEST_SPEED // =====================================
		}
		::GetSystemTime( &t1 );
#endif // ================================================

	} else {

#ifdef TEST_SPEED // =====================================
		for ( int cnt1 = 0; cnt1 <= base_speed * 10; cnt1++ ) {
#endif // ================================================

		dc.FillSolidRect( 0, 0, border_w - paper_border, client_height, paper_border_color );
		dc.FillSolidRect( client_width - border_w + paper_border + paper_shadow, 0, border_w - paper_border - paper_shadow, client_height, paper_border_color );
		dc.FillSolidRect( border_w - paper_border, 0, client_width - border_w * 2 + paper_border * 2 + paper_shadow, border_h - paper_border, paper_border_color );
		dc.FillSolidRect( border_w - paper_border, client_height - border_h + paper_border + paper_shadow, client_width - border_w * 2 + paper_border * 2 + paper_shadow, border_h - paper_border - paper_shadow, paper_border_color );
		dc.FillSolidRect( border_w - paper_border, client_height - border_h + paper_border, paper_shadow, paper_shadow, paper_border_color );
		dc.FillSolidRect( client_width - border_w + paper_border, border_h - paper_border, paper_shadow, paper_shadow, paper_border_color );

		if ( client_width > border_w * 2 + paper_border_w * 2 && client_height > border_h * 2 + paper_border_h * 2 ) {
			dc.FillSolidRect( border_w, border_h, paper_border_w, client_height - border_h * 2, paper_bg_color );
			dc.FillSolidRect( border_w + paper_border_w, border_h, client_width - border_w * 2 - paper_border_w, paper_border_h, paper_bg_color );
			dc.FillSolidRect( client_width - border_w - paper_border_w, border_h + paper_border_h, paper_border_w, client_height - border_h * 2 - paper_border_h, paper_bg_color );
			dc.FillSolidRect( border_w + paper_border_w, client_height - border_h - paper_border_h, client_width - border_w * 2 - paper_border_w * 2, paper_border_h, paper_bg_color );
		} else {
			dc.FillSolidRect( border_w, border_h, client_width - border_w * 2, client_height - border_h * 2, paper_bg_color );
		}

#ifdef TEST_SPEED // =====================================
		}
		::GetSystemTime( &t1 );
		for ( int cnt2 = 0; cnt2 <= base_speed * 10; cnt2++ ) {
#endif // ================================================

		const int shadow_border_w = 2;
		const int shadow_border_h = 2;
		dc.FillSolidRect( client_width - border_w + paper_border, border_h + shadow_border_h - paper_border, shadow_border_w, client_height - border_h * 2 + shadow_border_w, paper_shadow_color );
		dc.FillSolidRect( border_w + shadow_border_w - paper_border, client_height - border_h + paper_border, client_width - border_w * 2, shadow_border_h, paper_shadow_color );
		dc.SelectObject( pen_black );
		dc.MoveTo( border_w - 1, border_h - 1 );
		dc.LineTo( client_width - border_w, border_h - 1 );
		dc.LineTo( client_width - border_w, client_height - border_h );
		dc.LineTo( border_w - 1, client_height - border_h );
		dc.LineTo( border_w - 1, border_h - 1 );

#ifdef TEST_SPEED // =====================================
		}
		::GetSystemTime( &t2 );
#endif // ================================================

		if ( pixmap_w_show > 0 && pixmap_h_show > 0 ) {

#ifdef TEST_SPEED // =====================================
			for ( int cnt3 = 0; cnt3 <= base_speed; cnt3++ ) {
#endif // ================================================
/*
			if ( grid_show ) {
				int x_start = scroll_x_pos / grid_bmp_width;
				int y_start = scroll_y_pos / grid_bmp_width;
				int x_stop  = x_start + pixmap_w_show / grid_bmp_width + 1;
				int y_stop  = y_start + pixmap_h_show / grid_bmp_width + 1;
#ifdef TEST_SPEED // =====================================
				if ( cnt3 == 0 ) {
#endif // ================================================
				TRACE( "x_start = %d, y_start = %d, x_stop = %d, y_stop = %d\n", x_start, y_start, x_stop, y_stop );
#ifdef TEST_SPEED // =====================================
				}
#endif // ================================================
				for ( int i = x_start; i <= x_stop; i++ ) {
					for ( int j = y_start; j <= y_stop; j++ ) {
						mem_dc.BitBlt( -scroll_x_pos + paper_border_w + i * grid_bmp_width, -scroll_y_pos + paper_border_h + j * grid_bmp_width, grid_bmp_width, grid_bmp_width, &grid_dc, 0, 0, SRCCOPY );
					}
				}
			}
*/
			mem_dc.FillSolidRect( 0, 0, pixmap_w_show, pixmap_h_show, paper_bg_color );

#ifdef TEST_SPEED // =====================================
			}
			::GetSystemTime( &t3 );

			for ( int cnt4 = 0; cnt4 <= base_speed * 10; cnt4++ ) {
				std::list< RPShape* >::iterator it = objects.begin();
				while ( it != objects.end() ) {
					it++;
				}
			}
			::GetSystemTime( &t4 );
#endif // ================================================

			std::list< RPChartObject* >::iterator it = objects.begin();
			while ( it != objects.end() ) {
				RPChartObject* object = *it;
				object->transformToGlobal();
				it++;
			}

#ifdef TEST_SPEED // =====================================
			for ( int cnt5 = 0; cnt5 <= base_speed; cnt5++ ) {
#endif // ================================================

			it = objects.begin();
			while ( it != objects.end() ) {
				int saved = mem_dc.SaveDC();
				(*it)->draw( mem_dc );
				RPChartObject* obj = *it;
				obj->transformToGlobal();
				static_cast<RPShape*>(obj)->pa_global.extendByPerimetr( obj->main_pen_width / 2.0 );
				obj->draw1( mem_dc );
				mem_dc.RestoreDC( saved );
				it++;
			}

#ifdef TEST_SPEED // =====================================
			}
			::GetSystemTime( &t5 );
#endif // ================================================

#ifdef TEST_SPEED // =====================================
			for ( int cnt6 = 0; cnt6 <= base_speed * 10; cnt6++ ) {
#endif // ================================================
#ifdef TEST_SPEED // =====================================
			}
			::GetSystemTime( &t6 );
#endif // ================================================

			it = objects.begin();
			while ( it != objects.end() ) {
				RPChartObject* object = *it;
/*
				CPoint snap_to_point = shape->getCenter();
				if ( snap_to_point.x > paper_border_w && snap_to_point.y > paper_border_h && snap_to_point.x <= pixmap_w_show - paper_border_w && snap_to_point.y <= pixmap_h_show - paper_border_h ) {
					CPen pen_red( PS_SOLID, 1, RGB(-1,0,0) );
					CBrush brush_white( RGB(-1,-1,-1) );
					mem_dc.SelectObject( pen_red );
					mem_dc.SelectObject( brush_white );
					mem_dc.Ellipse( snap_to_point.x - 2, snap_to_point.y - 2, snap_to_point.x + 2, snap_to_point.y + 2 );
				}
*/
				if ( object->isSelected() ) {
					// ������������� ������ ������
					rp::rect rect = object->getBoundingRect();
					int x0 = rect.p0().x;
					int x1 = rect.p1().x;
					int x2 = rect.p2().x;
					int x3 = rect.p3().x;
					int y0 = rect.p0().y;
					int y1 = rect.p1().y;
					int y2 = rect.p2().y;
					int y3 = rect.p3().y;
					mem_dc.SelectObject( pen_selected_line );
					mem_dc.MoveTo( x0, y0 );
					mem_dc.LineTo( x1, y1 );
					mem_dc.LineTo( x2, y2 );
					mem_dc.LineTo( x3, y3 );
					mem_dc.LineTo( x0, y0 );
					mem_dc.SelectObject( pen_selected_box );
					mem_dc.SelectObject( brush_selected_box );
					int box_size    = select_box_size2 * 2 -1;
					int box_size_2  = select_box_size2;
					if ( rpapp.project().getFlowState() == RPProject::flow_rotate ) {
						int radius = getSensitivity();
						mem_dc.Ellipse( x0 - radius, y0 - radius, x0 + radius, y0 + radius );
						mem_dc.Ellipse( x1 - radius, y1 - radius, x1 + radius, y1 + radius );
						mem_dc.Ellipse( x2 - radius, y2 - radius, x2 + radius, y2 + radius );
						mem_dc.Ellipse( x3 - radius, y3 - radius, x3 + radius, y3 + radius );
					} else {
						mem_dc.Rectangle( x0 - box_size_2, y0 - box_size_2, x0 + box_size_2, y0 + box_size_2 );
						mem_dc.Rectangle( x1 - box_size_2, y1 - box_size_2, x1 + box_size_2, y1 + box_size_2 );
						mem_dc.Rectangle( x2 - box_size_2, y2 - box_size_2, x2 + box_size_2, y2 + box_size_2 );
						mem_dc.Rectangle( x3 - box_size_2, y3 - box_size_2, x3 + box_size_2, y3 + box_size_2 );
					}
					mem_dc.Rectangle( (x0 + x1)/2 - box_size_2, (y0 + y1)/2 - box_size_2, (x0 + x1)/2 + box_size_2, (y0 + y1)/2 + box_size_2 );
					mem_dc.Rectangle( (x1 + x2)/2 - box_size_2, (y1 + y2)/2 - box_size_2, (x1 + x2)/2 + box_size_2, (y1 + y2)/2 + box_size_2 );
					mem_dc.Rectangle( (x2 + x3)/2 - box_size_2, (y2 + y3)/2 - box_size_2, (x2 + x3)/2 + box_size_2, (y2 + y3)/2 + box_size_2 );
					mem_dc.Rectangle( (x3 + x0)/2 - box_size_2, (y3 + y0)/2 - box_size_2, (x3 + x0)/2 + box_size_2, (y3 + y0)/2 + box_size_2 );
					if ( rpapp.project().getFlowState() == RPProject::flow_rotate ) {
						// ����� ��������
						rp::point center = object->getRotateCenter();
						CPen pen_red( PS_SOLID, 1, RGB(0,0,0) );
						CBrush brush_white( RGB(-1,-1,0) );
						int radius = getSensitivity();
						mem_dc.SelectObject( pen_red );
						mem_dc.SelectObject( brush_white );
						mem_dc.Ellipse( center.x - radius, center.y - radius, center.x + radius, center.y + radius );
					}
				}
				it++;
			}

#ifdef TEST_SPEED // =====================================
			for ( int cnt7 = 0; cnt7 <= base_speed * 5; cnt7++ ) {
#endif // ================================================

			dc.BitBlt( border_w + paper_border_w, border_h + paper_border_h, pixmap_w_show, pixmap_h_show, &mem_dc, 0, 0, SRCCOPY );

#ifdef TEST_SPEED // =====================================
			}
			::GetSystemTime( &t7 );
#endif // ================================================
		}
	}
	dc.RestoreDC( -1 );

#ifdef TEST_SPEED // =====================================
	int delay1 = (t1.wMinute * 1000 * 60 + t1.wSecond * 1000 + t1.wMilliseconds) - (t0.wMinute * 1000 * 60 + t0.wSecond * 1000 + t0.wMilliseconds);
	int delay2 = (t2.wMinute * 1000 * 60 + t2.wSecond * 1000 + t2.wMilliseconds) - (t1.wMinute * 1000 * 60 + t1.wSecond * 1000 + t1.wMilliseconds);
	int delay3 = ((t3.wMinute * 1000 * 60 + t3.wSecond * 1000 + t3.wMilliseconds) - (t2.wMinute * 1000 * 60 + t2.wSecond * 1000 + t2.wMilliseconds)) * 10;
	int delay4 = (t4.wMinute * 1000 * 60 + t4.wSecond * 1000 + t4.wMilliseconds) - (t3.wMinute * 1000 * 60 + t3.wSecond * 1000 + t3.wMilliseconds);
	int delay5 = ((t5.wMinute * 1000 * 60 + t5.wSecond * 1000 + t5.wMilliseconds) - (t4.wMinute * 1000 * 60 + t4.wSecond * 1000 + t4.wMilliseconds)) * 10;
	int delay6 = (t6.wMinute * 1000 * 60 + t6.wSecond * 1000 + t6.wMilliseconds) - (t5.wMinute * 1000 * 60 + t5.wSecond * 1000 + t5.wMilliseconds);
	int delay7 = ((t7.wMinute * 1000 * 60 + t7.wSecond * 1000 + t7.wMilliseconds) - (t6.wMinute * 1000 * 60 + t6.wSecond * 1000 + t6.wMilliseconds)) * 2;
	int delay0 = delay1 + delay2 + delay3 + delay4 + delay5 + delay6 + delay7;
	TRACE( "paint_delay = %d: %d, %d, %d, %d, %d, %d, %d\n", delay0, delay1, delay2, delay3, delay4, delay5, delay6, delay7 );
#endif // ================================================

}

void RPFlowChart::OnHScroll( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar )
{
	SCROLLINFO si;
	si.cbSize = sizeof( si );
	switch( nSBCode ) {
		case SB_PAGEUP:
			GetScrollInfo( SB_HORZ, &si, SIF_PAGE );
			flowobj->matrix_transform.dx() += si.nPage;
			break; 

		case SB_PAGEDOWN:
			GetScrollInfo( SB_HORZ, &si, SIF_PAGE );
			flowobj->matrix_transform.dx() -= si.nPage;
			break;

		case SB_LINEUP:
			flowobj->matrix_transform.dx()++;
			break;

		case SB_LINEDOWN:
			flowobj->matrix_transform.dx()--;
			break;

		case SB_THUMBTRACK: {
			GetScrollInfo( SB_HORZ, &si, SIF_TRACKPOS );
			flowobj->matrix_transform.dx() -= si.nTrackPos - flowobj->matrix_transform.dx();
			break;
		}
	}
	CSize size = getFlowSize();
	int width = size.cx - pixmap_w_show + paper_border_w * 2;
	if ( flowobj->matrix_transform.dx() > width ) flowobj->matrix_transform.dx() = width;
	if ( flowobj->matrix_transform.dx() < 0 ) flowobj->matrix_transform.dx() = 0;
	si.fMask = SIF_POS;
	si.nPos  = flowobj->matrix_transform.dx();
	SetScrollInfo( SB_HORZ, &si, TRUE );
	updateDC();
}

void RPFlowChart::OnVScroll( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar )
{
	SCROLLINFO si;
	si.cbSize = sizeof( si );
	switch( nSBCode ) {
		case SB_PAGEUP:
			GetScrollInfo( SB_VERT, &si, SIF_PAGE );
			flowobj->matrix_transform.dy() += si.nPage;
			break; 

		case SB_PAGEDOWN:
			GetScrollInfo( SB_VERT, &si, SIF_PAGE );
			flowobj->matrix_transform.dy() -= si.nPage;
			break;

		case SB_LINEUP:
			flowobj->matrix_transform.dy()++;
			break;

		case SB_LINEDOWN:
			flowobj->matrix_transform.dy()--;
			break;

		case SB_THUMBTRACK: {
			GetScrollInfo( SB_VERT, &si, SIF_TRACKPOS );
			flowobj->matrix_transform.dy() -= si.nTrackPos - flowobj->matrix_transform.dy();
			break;
		}
	}
	CSize size = getFlowSize();
	int height = size.cy - pixmap_h_show + paper_border_h * 2;
	if ( flowobj->matrix_transform.dy() > height ) flowobj->matrix_transform.dy() = height;
	if ( flowobj->matrix_transform.dy() < 0 ) flowobj->matrix_transform.dy() = 0;
	si.fMask = SIF_POS;
	si.nPos  = flowobj->matrix_transform.dy();
	SetScrollInfo( SB_VERT, &si, TRUE );
	updateDC();
}

void RPFlowChart::snapToGrid( RPShape* shape )
{
/*
	if ( shape ) {
		if ( grid_pa.empty() ) return;
		CPoint center;
		if ( grid_mode == gtSnapToPoint ) {
			center = CPoint( shape->getSnapToPoint() );
			center.Offset( shape->getX() + paper_border_w, shape->getY() + paper_border_h );
		} else {
			center = shape->getCenter();
			center += CPoint( shape->getX() + paper_border_w, shape->getY() + paper_border_h );
		}
		int c_x = ((center.x - paper_border_w) / grid_step);
		int c_y = ((center.y - paper_border_h) / grid_step);
		bool makeNewGrid = false;
		const int point_cnt = 4;
		std::vector< CPoint > c_pa;
		c_pa.resize( point_cnt );
		if ( c_x < 0 ) {
			c_x = 0;
		}
		if ( c_y < 0 ) {
			c_y = 0;
		}
		if ( grid_type == gtPoints ) {
			if ( c_x > grid_cnt_x ) {
				c_x = grid_cnt_x;
			}
			if ( c_y > grid_cnt_y ) {
				c_y = grid_cnt_y;
			}
			c_pa[0] = grid_pa[ c_x + c_y * grid_cnt_x ];
			c_pa[1] = grid_pa[ c_x + 1 + c_y * grid_cnt_x ];
			c_pa[2] = grid_pa[ c_x + 1 + (c_y + 1) * grid_cnt_x ];
			c_pa[3] = grid_pa[ c_x + (c_y + 1) * grid_cnt_x ];
		} else {
			int x1 = grid_pa[ c_x * 2 ].x;
			int y1 = grid_pa[ grid_cnt_x * 2 + c_y * 2 ].y;
			int x2 = x1 + grid_step;
			int y2 = y1 + grid_step;
			if ( c_x >= grid_cnt_x - grid_dx_plus || c_y >= grid_cnt_y - grid_dy_plus ) {
				makeNewGrid = true;
			}
			c_pa[0] = CPoint( x1, y1 );
			c_pa[1] = CPoint( x2, y1 );
			c_pa[2] = CPoint( x2, y2 );
			c_pa[3] = CPoint( x1, y2 );
		}
		int dx = 0;
		int dy = 0;
		if ( grid_mode == gtSnapToPoint ) {
			double len1 = RPFlowChart::getDistance( c_pa[1], c_pa[2], center );
			double len2 = RPFlowChart::getDistance( c_pa[3], c_pa[0], center );
			if ( len1 < len2 ) {
				dx = c_pa[1].x - center.x;
			} else {
				dx = c_pa[3].x - center.x;
			}
			len1 = RPFlowChart::getDistance( c_pa[0], c_pa[1], center );
			len2 = RPFlowChart::getDistance( c_pa[2], c_pa[3], center );
			if ( len1 < len2 ) {
				dy = c_pa[1].y - center.y;
			} else {
				dy = c_pa[3].y - center.y;
			}
			if ( abs(dx) > grid_delta ) {
				dx = 0;
			}
			if ( abs(dy) > grid_delta ) {
				dy = 0;
			}
		} else {
			dx = ( c_pa[0].x + (c_pa[1].x - c_pa[0].x)/2 ) - center.x;
			dy = ( c_pa[0].y + (c_pa[3].y - c_pa[0].y)/2 ) - center.y;
		}
		if ( (dx || dy) && grid_mode != gtSnapOff ) {
			shape->move( shape->getX() + dx, shape->getY() + dy );
		}
		if ( dx || dy || makeNewGrid ) {
			if ( makeNewGrid ) {
				grid_pa.resize( 0 );
				makeGrid();
				updateScrollBars();
			}
			updateDC();
		}
	}
*/
}
/*
void RPFlowChart::snapToGridAllShapes()
{
	std::vector< RPShape* >::const_iterator it = objects.begin();
	while ( it != objects.end() ) {
		snapToGrid( *it );
		it++;
	}
}
*/

void RPFlowChart::OnTimer( UINT nIDEvent )
{
#ifdef TEST_SPEED // =====================================
	if ( nIDEvent == sec_timer ) {
		TRACE( "%d. makepixmap = %d, makegrid = %d, makegrid_empty = %d\n", sec_cnt++, makepixmap_cnt, makegrid_cnt, makegridempty_cnt );
		makegrid_cnt      = 0;
		makegridempty_cnt = 0;
		makepixmap_cnt    = 0;
	}
#endif // ================================================
//	if ( nIDEvent == grid_timer ) {
//		if ( grid_mode != gtSnapOff && !grid_objects.empty() ) {
//			std::list< RPShape* >::const_iterator it = grid_objects.begin();
//			while ( it != grid_objects.end() ) {
//				snapToGrid( *it );
//				it++;
//			}
//			grid_objects.clear();
//		}
//	}
	CWnd::OnTimer( nIDEvent );
}

void RPFlowChart::OnLButtonDown( UINT nFlags, CPoint local_mouse_pos )
{
	CWnd::OnLButtonDown( nFlags, local_mouse_pos );
	one_object = NULL;
	RPChartObject::PossibleCommand pcmd = RPChartObject::pcmd_none;
	if ( rpapp.project().getFlowState() == RPProject::flow_select || rpapp.project().getFlowState() == RPProject::flow_rotate ) {
		rp::point global_pos = local_mouse_pos;
		clientToZero( global_pos );
		std::list< RPChartObject* >::const_iterator it = objects.begin();
		while ( it != objects.end() ) {
			RPChartObject* obj = *it;
			// ��������, � �� �������� � ����� �������� �����-���� ������.
			// ��� ����� ����� ��������� ��� ������, ������� �������� ��� ������ ��� ������ ���� �����
			if ( obj->isRotateCenter( global_pos ) ) {
				one_object      = obj;
				one_object_pcmd = RPChartObject::pcmd_rotate_center;
				break;
			}
			// ��������� ������� � ������������
			if ( obj->getBoundingRect().extendByPerimetr( getSensitivity() ).pointInRect( global_pos ) || obj->pointInPolygon( global_pos ) ) {
				obj->transformToGlobal();
				pcmd = obj->getPossibleCommand( global_pos );
				switch ( pcmd ) {
					case RPChartObject::pcmd_rotate_tl    :
					case RPChartObject::pcmd_rotate_tr    : 
					case RPChartObject::pcmd_rotate_bl    :
					case RPChartObject::pcmd_rotate_br    :
					case RPChartObject::pcmd_scale        :
					case RPChartObject::pcmd_move         :
					case RPChartObject::pcmd_scale_l      :
					case RPChartObject::pcmd_scale_r      :
					case RPChartObject::pcmd_scale_t      :
					case RPChartObject::pcmd_scale_b      :
					case RPChartObject::pcmd_scale_tl     :
					case RPChartObject::pcmd_scale_br     :
					case RPChartObject::pcmd_scale_tr     :
					case RPChartObject::pcmd_scale_bl     : one_object = obj; one_object_pcmd = pcmd; break;
				}
			}
			if ( pcmd != RPChartObject::pcmd_none ) break;
			it++;
		}
	}
	// ��������� ���������� ���������� ����� (���������� � ������, � �� 2D ������ ). ���������� � ������ ��������.
	ClientToScreen( &local_mouse_pos );
	global_mouse_pos_prev = local_mouse_pos;
	// ���������� ��������� �����
	SetCapture();
	// ����� ������
	if ( one_object ) {
		if ( !one_object->isSelected() ) one_object->setSelected( true );
		// ������ ��� ����������� �������
		if ( pcmd == RPChartObject::pcmd_move ) {
			moving_objects.clear();
			if ( nFlags & MK_CONTROL ) {
				moving_objects.assign( objects.begin(), objects.end() );
			} else {
				moving_objects.push_back( one_object );
			}
		}
	} else {
		// ������ �� �����, �������� ����
		flowobj->setSelected( true );
	}
}

void RPFlowChart::OnLButtonUp( UINT nFlags, CPoint local_mouse_pos )
{
	CWnd::OnLButtonUp( nFlags, local_mouse_pos );
	// ������ ������ �����
	::ReleaseCapture();
	// ��������� ��� ������
	moving_objects.clear();
	one_object = NULL;
/*
	grid_objects.clear();
	grid_objects.assign( moving_objects.begin(), moving_objects.end() );
//	movingShape = NULL;
	moving_objects.clear();
	if ( !grid_objects.empty() ) {
		if ( grid_timer ) KillTimer( grid_timer );
		grid_timer = SetTimer( grid_timer_id, 100, NULL );
	}
*/
	updateScrollBars();
//	resetPreview();
}

void RPFlowChart::OnMouseMove( UINT nFlags, CPoint local_mouse_pos )
{
	CWnd::OnMouseMove( nFlags, local_mouse_pos );

	// ���������� ��������� ����� � �����
	CPoint global_mouse_pos = local_mouse_pos;
	ClientToScreen( &global_mouse_pos );

	// ���������� ���������� ����� � 2D ������ (�� ������� �����)
	rp::point global_pos = local_mouse_pos;
	clientToZero( global_pos );

	// ���� ������ ���� ������, �� �� ����� ��������� � ���������.
	// ����������� �� ��������� ��������, �������� ��� ������ ��������.
	// ��� �������� �� ����� ���� ����������.
	if ( one_object ) {
		RPChartObject::angle90 a90 = one_object->getAngle90();
		double alpha = one_object->getRotation();
		double dx = global_mouse_pos.x - global_mouse_pos_prev.x;
		double dy = global_mouse_pos.y - global_mouse_pos_prev.y;
		switch ( one_object_pcmd ) {
			case RPChartObject::pcmd_rotate_center: {
				one_object->setRotateCenter( global_pos );
				updateDC();
				break;
			}
			case RPChartObject::pcmd_rotate       :
			case RPChartObject::pcmd_rotate_tl    :
			case RPChartObject::pcmd_rotate_tr    :
			case RPChartObject::pcmd_rotate_bl    :
			case RPChartObject::pcmd_rotate_br    : {
				CPoint point_old = global_mouse_pos_prev;
				CPoint point_new = global_mouse_pos;
				ScreenToClient( &point_old );
				ScreenToClient( &point_new );
				clientToZero( point_old );
				clientToZero( point_new );
				one_object->setRotation( one_object->getRotation() + rp::math::getAlpha( point_old, one_object->getRotateCenter(), point_new ) );
				updateDC();
				break;
			}
			case RPChartObject::pcmd_scale_r      : {
				one_object->backup_push();
				rp::rect rect = one_object->getBoundingRect();
				if ( a90 == RPChartObject::angle90_0 || a90 == RPChartObject::angle90_180 ) {
					double len = rp::math::getLength( rect.p_l(), rect.p_r() );
					one_object->setScaleX( one_object->getScaleX() * (len + dx) / len );
					double _dx = a90 == RPChartObject::angle90_0 ? dx / 2 : -dx / 2;
					one_object->setPostX( one_object->getPostX() + _dx );
					rp::rect rect2 = one_object->getBoundingRect();
					rp::point point( rect.p_l().x - rect2.p_l().x, 0 );
					point = one_object->globalRotate().obr() * point;
					if ( fabs(point.x) > 1e-10 ) {
						one_object->backup_pop();
						dx += point.x;
						if ( dx ) {
							one_object->setScaleX( one_object->getScaleX() * (len + dx) / len );
							double _dx = a90 == RPChartObject::angle90_0 ? dx / 2 : -dx / 2;
							one_object->setPostX( one_object->getPostX() + _dx );
						}
					}
					if ( dx ) {
						one_object->setRotateCenterLocalDelta( dx, 0 );
					}
				}
				if ( a90 == RPChartObject::angle90_90 || a90 == RPChartObject::angle90_270 ) {
					double len = rp::math::getLength( rect.p_t(), rect.p_b() );
					one_object->setScaleY( one_object->getScaleY() * (len + dx) / len );
					dx /= 2;
					dx *= a90 == RPChartObject::angle90_90 ? 1 : -1;
					one_object->setPostY( one_object->getPostY() + dx );
					one_object->setRotateCenterLocalDelta( 0, dx );
				}
				one_object->backup_clear();
				updateDC();
				break;
			}
		}
	}
	// ���������� ������ ��������. ���������� ����� ����� �����.
	if ( one_object_pcmd == RPChartObject::pcmd_move ) {
		int dx = global_mouse_pos.x - global_mouse_pos_prev.x;
		int dy = global_mouse_pos.y - global_mouse_pos_prev.y;
/*
		// ������ ����� �� ������� ����� (����� ������� ����)
		std::list< RPChartObject* >::iterator it = moving_objects.begin();
		while ( it != moving_objects.end() ) {
			RPChartObject* object = *it;
			int delta = object->getX() + dx;
			if ( delta < 0 ) {
				dx -= delta;
			}
			delta = object->getY() + dy;
			if ( delta < 0 ) {
				dy -= delta;
			}
			it++;
		}
*/
		std::list< RPChartObject* >::iterator it = moving_objects.begin();
		while ( it != moving_objects.end() ) {
			(*it)->moving( dx, dy );
			it++;
		}
		updateScrollBars();
		makeGrid();
/*
//		if ( dx > 0 ) {
			CSize size = getFlowSize( movingShapes );
			int max_x = size.cx + border_w + paper_border_w;
			int width = pixmap_w_show + scroll_x_pos;
//			TRACE( "dx = %d, max_x = %d, width = %d\n", dx, max_x, width );
			if ( max_x > width ) {
				SCROLLINFO si;
				si.cbSize = sizeof( si );
				si.fMask  = SIF_RANGE | SIF_PAGE | SIF_POS;

				scroll_x_pos += dx;
				si.nMin   = 0;
				si.nMax   = max_x;
				si.nPos   = scroll_x_pos;
				si.nPage  = client_width;
				SetScrollInfo( SB_HORZ, &si, TRUE );
			}
			makeGrid();
//		}
*/
		updateDC();
	}
	global_mouse_pos_prev = global_mouse_pos;
}

void RPFlowChart::updateFlowState()
{
	updateDC();
}

// ������� ���������� ��� ����������� ����� ��� ����� � ��� �����, �� �� ����������,
// ����� ����� ������������ ��� ����� � ������� ��������
BOOL RPFlowChart::OnSetCursor( CWnd* pWnd, UINT nHitTest, UINT message )
{
	CPoint point;
	::GetCursorPos( &point );
	ScreenToClient( &point );
	clientToZero( point );
	HCURSOR cursor        = NULL;
	RPChartObject* object = NULL;
	one_object_pcmd       = RPChartObject::pcmd_none;
	std::list< RPChartObject* >::const_iterator it = objects.begin();
	while ( it != objects.end() ) {
		RPChartObject* obj = *it;
		if ( obj->isRotateCenter( point ) ) {
			object = obj;
			break;
		}
		if ( obj->getBoundingRect().extendByPerimetr( getSensitivity() ).pointInRect( point ) || obj->pointInPolygon( point ) ) {
			object = obj;
			break;
		}
		it++;
	}
	if ( object ) {
		object->transformToGlobal();
		RPChartObject::PossibleCommand _pcmd = object->getPossibleCommand( point, true );
		if ( object->isSelected() ) {
			switch ( _pcmd ) {
				case RPChartObject::pcmd_none         : break;
				case RPChartObject::pcmd_scale        : cursor = rpapp.cursors[IDC_FLOW_SELECT]; break;
				case RPChartObject::pcmd_move         : one_object_pcmd = _pcmd; cursor = rpapp.cursors[IDC_FLOW_MOVE]; break;
				case RPChartObject::pcmd_rotate       :
				case RPChartObject::pcmd_rotate_tl    :
				case RPChartObject::pcmd_rotate_tr    :
				case RPChartObject::pcmd_rotate_bl    :
				case RPChartObject::pcmd_rotate_br    : cursor = rpapp.cursors[IDC_FLOW_ROTATE_TL]; break;
				case RPChartObject::pcmd_rotate_center: cursor = rpapp.cursors[IDC_FLOW_ROTATE_CENTER]; break;
				case RPChartObject::pcmd_scale_l      :
				case RPChartObject::pcmd_scale_r      : cursor = rpapp.cursors[IDC_FLOW_SCALE_LR]; break;
				case RPChartObject::pcmd_scale_t      :
				case RPChartObject::pcmd_scale_b      : cursor = rpapp.cursors[IDC_FLOW_SCALE_TB]; break;
				case RPChartObject::pcmd_scale_tl     :
				case RPChartObject::pcmd_scale_br     : cursor = rpapp.cursors[IDC_FLOW_SCALE_TLBR]; break;
				case RPChartObject::pcmd_scale_tr     :
				case RPChartObject::pcmd_scale_bl     : cursor = rpapp.cursors[IDC_FLOW_SCALE_TRBL]; break;
			}
		} else {
			switch ( _pcmd ) {
				case RPChartObject::pcmd_move         : one_object_pcmd = _pcmd; cursor = rpapp.cursors[IDC_FLOW_MOVE]; break;
			}
		}
	}
	if ( !cursor ) {
		switch ( rpapp.project().getFlowState() ) {
			case RPProject::flow_select   : cursor = rpapp.cursors[IDC_FLOW_SELECT]; break;
			case RPProject::flow_connector: cursor = rpapp.cursors[IDC_FLOW_CONNECTOR]; break;
			case RPProject::flow_rotate   : cursor = rpapp.cursors[IDC_FLOW_ROTATE]; break;
		}
	}
	if ( cursor ) {
		::SetCursor( cursor );
		return true;
	}
	return false;
}

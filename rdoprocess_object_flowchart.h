#ifndef RDO_PROCESS_OBJECT_FLOWCHART_H
#define RDO_PROCESS_OBJECT_FLOWCHART_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "rdoprocess_object_matrix.h"
#include "rdoprocess_flowchart.h"

// ----------------------------------------------------------------------------
// ---------- RPObjectFlowChart
// ----------------------------------------------------------------------------
class RPObjectFlowChart: public RPObjectMatrix
{
friend class RPFlowChart;

private:
	bool init_ok;
	int border_w;
	int border_h;
	int paper_border_w;
	int paper_border_h;
	int paper_border;
	int paper_shadow;
	int pixmap_w_real;
	int pixmap_h_real;
	int pixmap_w_show;
	int pixmap_h_show;
	int client_width;
	int client_height;
	static const int select_box_size2;

	CPen     pen_black;
	CPen     pen_shape_color;
	CPen     pen_selected_line;
	CPen     pen_selected_box;
	CBrush   brush_selected_box;
	COLORREF paper_border_color;
	COLORREF paper_shadow_color;
	COLORREF paper_bg_color;

	CDC      mem_dc;
	CBitmap* mem_bmp;
	CBitmap* bmp_first;
	CFont*   font_first;
	int      saved_mem_dc;

	CPoint         global_win_pos_current;
	CPoint         global_win_pos_prev;
	RPObjectChart* one_object;

#ifdef TEST_SPEED
	int makepixmap_cnt;
#endif

protected:
	RPFlowChart* flowchart;

	virtual void notify( RPObject* from, UINT message, WPARAM wParam, LPARAM lParam );
	virtual void modify();
	virtual void update();
	virtual bool isFlowChart() const { return true; }
	void makeNewPixmap();

	virtual RPProject::Cursor getCursor( const rp::point& global_chart_pos );
	virtual RPObjectChart* find( const rp::point& global_chart_pos );

	rp::rect getFlowSize( const std::list< RPObjectChart* >& list ) const;

	virtual void onLButtonDown( UINT nFlags, CPoint local_win_pos );
	virtual void onLButtonUp( UINT nFlags, CPoint local_win_pos );
	virtual void onLButtonDblClk( UINT nFlags, CPoint local_win_pos );
	virtual void onRButtonDown( UINT nFlags, CPoint local_win_pos );
	virtual void onRButtonUp( UINT nFlags, CPoint local_win_pos );
	virtual void onMouseMove( UINT nFlags, CPoint local_win_pos );

public:
	RPObjectFlowChart( RPObject* parent, RPFlowChart* flowchart );
	virtual ~RPObjectFlowChart();

	void snapToGrid( RPObjectMatrix* shape );

	static int getSensitivity()               { return select_box_size2 + 1; }
	int getSelectBoxSize2() const             { return select_box_size2;     }
	const CPen& getPenSelectedLine() const    { return pen_selected_line;    }
	const CPen& getPenSelectedBox() const     { return pen_selected_box;     }
	const CBrush& getBrushSelectedBox() const { return brush_selected_box;   }

	rp::point mouse_current() const           {
		CPoint point = global_win_pos_current;
		flowchart->ScreenToClient( &point );
		clientToZero( point );
		return point;
	}
	rp::point mouse_prev() const              {
		CPoint point = global_win_pos_prev;
		flowchart->ScreenToClient( &point );
		clientToZero( point );
		return point;
	}
	rp::point mouse_delta() const             { return rp::point( global_win_pos_current.x - global_win_pos_prev.x, global_win_pos_current.y - global_win_pos_prev.y ); }

	// ��������� ������
	virtual void draw( CDC& dc );
	// �������� ������
	virtual rp::rect getBoundingRect( bool global = true ) const;
	virtual rp::rect getMaxRect();
	// ������� ���� ��������� ������ � ���������� ����������
	virtual void transformToGlobal() {};
	// ��������� �� ����� ������ ������
	virtual bool pointInPolygon( const rp::point& global_chart_pos );
	// ��������� �� ����� � ��������� (������������) ����� ������ (������������� ���������, � �������)
	virtual bool pointInNCArea( const rp::point& global_chart_pos ) { return !pointInPolygon( global_chart_pos ); }

	void clientToZero( CPoint& point ) const {
		point.x -= border_w + paper_border_w;
		point.y -= border_h + paper_border_h;
	}
	void clientToZero( rp::point& point ) const {
		point.x -= border_w + paper_border_w;
		point.y -= border_h + paper_border_h;
	}
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // RDO_PROCESS_OBJECT_FLOWCHART_H

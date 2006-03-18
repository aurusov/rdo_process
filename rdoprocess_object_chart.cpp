#include "stdafx.h"
#include "rdoprocess_object_chart.h"
#include "rdoprocess_object_flowchart.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// ----------------------------------------------------------------------------
// ---------- RPObjectChart
// ----------------------------------------------------------------------------
RPObjectChart::RPObjectChart( RPObject* _parent, const rp::string& _name ):
	RPObject( _parent, _name ),
	main_pen_width( 20 )
{
	LOGBRUSH lb;
	lb.lbStyle = BS_SOLID;
	lb.lbColor = RGB(0x00, 0x00, 0x00);
	lb.lbHatch = 0;
	main_pen.CreatePen( PS_GEOMETRIC | PS_SOLID | PS_ENDCAP_SQUARE | PS_JOIN_MITER, main_pen_width, &lb );
}

RPObjectChart::~RPObjectChart()
{
}

RPObjectFlowChart* RPObjectChart::flowChart() const
{
	RPObjectChart* chart_parent = chartParent();
	RPObjectChart* prev = chart_parent;
	while ( chart_parent ) {
		prev = chart_parent;
		chart_parent = chart_parent->chartParent();
	}
	return static_cast<RPObjectFlowChart*>(prev);
}

void RPObjectChart::modify()
{
	RPObjectChart* flowchart = flowChart();
	if ( flowchart ) {
		flowchart->modify();
	}
}

void RPObjectChart::update()
{
	RPObjectChart* flowchart = flowChart();
	if ( flowchart ) {
		flowchart->update();
	}
}

RPProject::Cursor RPObjectChart::getCursor( const rp::point& global_chart_pos )
{
	std::list< RPObjectChart* > objects;
	getChartObjects( objects );
	std::list< RPObjectChart* >::iterator it = objects.begin();
	while ( it != objects.end() ) {
		RPProject::Cursor cursor = (*it)->getCursor( global_chart_pos );
		if ( cursor != RPProject::cursor_flow_select ) return cursor;
		it++;
	}
	return RPProject::cursor_flow_select;
}

RPObjectChart* RPObjectChart::find( const rp::point& global_chart_pos )
{
	std::list< RPObjectChart* > objects;
	getChartObjects( objects );
	std::list< RPObjectChart* >::iterator it = objects.begin();
	while ( it != objects.end() ) {
		RPObjectChart* obj = (*it)->find( global_chart_pos );
		if ( obj ) return obj;
		it++;
	}
	return (pointInPolygon(global_chart_pos) || pointInNCArea(global_chart_pos)) ? this : NULL;
}

void RPObjectChart::draw( CDC& dc )
{
	// ����� ��������� ��������
	std::list< RPObjectChart* > objects;
	getChartObjects( objects );
	std::list< RPObjectChart* >::iterator it = objects.begin();
	while ( it != objects.end() ) {
		int saved = dc.SaveDC();
		(*it)->draw( dc );
		(*it)->draw1( dc );
		dc.RestoreDC( saved );
		it++;
	}
}

void RPObjectChart::draw_after( CDC& dc )
{
	// ����� ��������� ��������.
	std::list< RPObjectChart* > objects;
	getChartObjects( objects );
	std::list< RPObjectChart* >::iterator it = objects.begin();
	while ( it != objects.end() ) {
		int saved = dc.SaveDC();
		(*it)->draw_after( dc );
		dc.RestoreDC( saved );
		it++;
	}
	if ( isSelected() ) draw_selected( dc );
}

void RPObjectChart::setSelected( bool value )
{
	bool _sel = isSelected();
	RPObject::setSelected( value );
	if ( _sel != value ) {
		update();
	}
}

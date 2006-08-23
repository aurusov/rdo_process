#ifndef RDO_PROCESS_OBJECT_CHART_H
#define RDO_PROCESS_OBJECT_CHART_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "rdoprocess_object.h"
#include "rdoprocess_project.h"
#include <rdoprocess_rect.h>
#include <rdoprocess_point.h>

// ----------------------------------------------------------------------------
// ---------- RPObjectChart
// ----------------------------------------------------------------------------
class RPObjectFlowChart;

class RPObjectChart: public RPObject
{
private:
	CPen main_pen;

protected:
	RPObjectChart* chartParent() const { return !isFlowChart() && parent && parent->isChartObject() ? static_cast<RPObjectChart*>(parent) : NULL; }

	int  main_pen_width;
	CPen main_pen_default;

	virtual void modify();

	virtual RPObjectChart* find( const rp::point& global_chart_pos );

	int getPenWidth() const { return main_pen_width; }

	// ������� ���� ��������� ������ � ���������� ����������
	virtual void transformToGlobal() = 0;

	// ��������� �� ����� ������ ������
	virtual bool pointInPolygon( const rp::point& global_chart_pos ) = 0;
	// ��������� �� ����� � ��������� (������������) ����� ������ (������������� ���������, � �������)
	virtual bool pointInNCArea( const rp::point& global_chart_pos ) = 0;

	// ��������� ������
	virtual void draw_selected( CDC& dc ) {};

public:
	RPObjectChart( RPObject* parent, const rp::string& name = "chart" );
	virtual ~RPObjectChart();

	virtual rp::string getClassName() const { return "RPObjectChart"; }
	virtual void load( rp::RPXMLNode* node );
	virtual rp::RPXMLNode* save( rp::RPXMLNode* parent_node );

	RPObjectFlowChart* flowChart() const;

	virtual bool setName( const rp::string& value ) {
		bool res = RPObject::setName( value );
		if ( res ) update();
		return res;
	}

	const CPen& getDefaultPen() const { return main_pen_default; }
	const CPen& getPen() const        { return main_pen;         }
	void setPen( const CPen& pen );

	virtual void update();

	virtual bool isChartObject() const { return true;  }
	virtual bool isFlowChart() const   { return false; }
	virtual bool isMatrix() const      { return false; }
	virtual bool isShape() const       { return false; }
	virtual bool isConnector() const   { return false; }

	void getChartObjects( std::list< RPObjectChart* >& objects ) const {
		std::list< RPObject* >::const_iterator it = begin();
		while ( it != end() ) {
			if ( (*it)->isChartObject() ) objects.push_back( static_cast<RPObjectChart*>(*it) );
			it++;
		}
	}

	virtual void onLButtonDown( UINT nFlags, CPoint global_chart_pos ) {
		if ( !isSelected() ) setSelected( true );
	};
	virtual void onLButtonUp( UINT nFlags, CPoint global_chart_pos ) {};
	virtual void onLButtonDblClk( UINT nFlags, CPoint global_chart_pos ) {};
	virtual void onRButtonDown( UINT nFlags, CPoint global_chart_pos ) {};
	virtual void onRButtonUp( UINT nFlags, CPoint global_chart_pos ) {};
	virtual void onMouseMove( UINT nFlags, CPoint global_chart_pos ) {};

	// ��������/����� ��������� � ������
	virtual void setSelected( bool value );

	// ��������� �� ����� ������ ������
	bool pointInShape( const rp::point& global_chart_pos ) {
		return pointInPolygon( global_chart_pos ) || pointInNCArea( global_chart_pos );
	}

	virtual RPProject::Cursor getCursor( const rp::point& global_chart_pos );

	// ��������� ������
	virtual void draw( CDC& dc );
	virtual void draw_after( CDC& dc );

	// �������� ������
	virtual rp::rect getBoundingRect( bool global = true ) const = 0;
	virtual rp::rect getMaxRect()                   { return getBoundingRect(); }
	virtual rp::rect getBoundingRectNoRotateOuter() { return getBoundingRect(); }
	virtual rp::rect getBoundingRectNoRotateIner()  { return getBoundingRect(); }

	// ����� ���������� ������� (������ ������ ����������� �������)
	virtual void command_before( const rp::point& global_chart_pos, bool first_click ) {};
	// ��������� ������� ��� ��������
	virtual void command_make( const rp::point& global_chart_pos ) {};

	static rp::string colorToStr( COLORREF color );
	static COLORREF strToColor( const rp::string& color );
};

#endif // RDO_PROCESS_OBJECT_CHART_H

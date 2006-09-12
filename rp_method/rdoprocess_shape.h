#ifndef RDO_PROCESS_SHAPE_H
#define RDO_PROCESS_SHAPE_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "rdoprocess_object_matrix.h"

#include <vector>

// ----------------------------------------------------------------------------
// ---------- RPShape
// ----------------------------------------------------------------------------
class RPConnectorDock;

class RPShape: public RPObjectMatrix
{
protected:
//	CPoint snap_to_point;

	CBrush   bg_brush;
	CFont    text_font;
	COLORREF text_color;
	bool     text_show;

	std::vector< RPConnectorDock* > docks;
	RPConnectorDock* find_dock( const rp::point& global_chart_pos );

	virtual rp::string get_xml_node_name() const { return "shape"; }

	// ���������� ���� �������� (�������� 90 ��������)
	enum angle90 {
		angle90_0 = 0,  //!< ���� �������� ������� alpha > 270 + 45 || alpha <= 45
		angle90_90,     //!< ���� �������� ������� alpha > 45       && alpha <= 90 + 45
		angle90_180,    //!< ���� �������� ������� alpha > 90 + 45  && alpha <= 180 + 45
		angle90_270     //!< ���� �������� ������� alpha > 180 + 45 && alpha <= 270 + 45
	};
	// ���������� ���� �������� (�������� 45 ��������)
	enum angle45 {
		angle45_0 = 0,  //!< ���� �������� ������� alpha > 360 - 22 || alpha <= 22
		angle45_90,     //!< ���� �������� ������� alpha > 90 - 22  && alpha <= 90 + 22
		angle45_180,    //!< ���� �������� ������� alpha > 180 - 22 && alpha <= 180 + 22
		angle45_270,    //!< ���� �������� ������� alpha > 270 - 22 && alpha <= 270 + 22
		angle45_45,     //!< ���� �������� ������� alpha > 45 -  22 && alpha <= 45 + 22
		angle45_135,    //!< ���� �������� ������� alpha > 135 - 22 && alpha <= 135 + 22
		angle45_225,    //!< ���� �������� ������� alpha > 225 - 22 && alpha <= 225 + 22
		angle45_315,    //!< ���� �������� ������� alpha > 315 - 22 && alpha <= 315 + 22
	};
	// ��������� ������� ��� ��������
	enum PossibleCommand {
		pcmd_none = 0,      //!< ��� �������� �� ����� ���� ����������� ������� ��������
		pcmd_move,          //!< ������ ����� ���� ���������
		pcmd_rotate_tl,     //!< ������ ����� ��������� �� ����� ������� ����
		pcmd_rotate_tr,     //!< ������ ����� ��������� �� ������ ������� ����
		pcmd_rotate_bl,     //!< ������ ����� ��������� �� ����� ������ ����
		pcmd_rotate_br,     //!< ������ ����� ��������� �� ����� ������ ����
		pcmd_rotate_center, //!< ����� ���� ������� ����� �������� �������
		pcmd_scale_l,       //!< ������ ����� ���� ������������� �� ����� �������
		pcmd_scale_r,       //!< ������ ����� ���� ������������� �� ������ �������
		pcmd_scale_t,       //!< ������ ����� ���� ������������� �� ����
		pcmd_scale_b,       //!< ������ ����� ���� ������������� �� ���
		pcmd_scale_tl,      //!< ������ ����� ���� ������������� �� ����� ������� ����
		pcmd_scale_tr,      //!< ������ ����� ���� ������������� �� ������ ������� ����
		pcmd_scale_bl,      //!< ������ ����� ���� ������������� �� ����� ������ ����
		pcmd_scale_br,      //!< ������ ����� ���� ������������� �� ������ ������ ����
		pcmd_dock_in,       //!< �������� ������� ��� �������
		pcmd_dock_out,      //!< �������� �������� ��� �������
		pcmd_dock_inout,    //!< �������� ��������������� ��� �������
		pcmd_dock_fly,      //!< ��� ����� ���� ���������
		pcmd_dock_not       //!< ��� ����������
	};
	PossibleCommand pcmd;

	// ��������� ������� ��� ��������
	PossibleCommand getPossibleCommand( const rp::point& global_chart_pos, bool for_cursor = false );

	// ������� ���������� ���� �������� (�������� 90 ��������)
	angle90 getAngle90() const {
		double alpha = getRotationGlobal();
		if ( alpha > 270 + 45 || alpha <= 45       ) return RPShape::angle90_0;
		if ( alpha > 45       && alpha <= 90 + 45  ) return RPShape::angle90_90;
		if ( alpha > 90 + 45  && alpha <= 180 + 45 ) return RPShape::angle90_180;
		if ( alpha > 180 + 45 && alpha <= 270 + 45 ) return RPShape::angle90_270;
		return RPShape::angle90_0;
	}

	// ������� ���������� ���� �������� (�������� 45 ��������)
	angle45 getAngle45() const {
		double alpha = getRotationGlobal();
		if ( alpha > 360 - 22 || alpha <= 22       ) return RPShape::angle45_0;
		if ( alpha > 90 - 22  && alpha <= 90 + 22  ) return RPShape::angle45_90;
		if ( alpha > 180 - 22 && alpha <= 180 + 22 ) return RPShape::angle45_180;
		if ( alpha > 270 - 22 && alpha <= 270 + 22 ) return RPShape::angle45_270;
		if ( alpha > 45 -  22 && alpha <= 45 + 22  ) return RPShape::angle45_45;
		if ( alpha > 135 - 22 && alpha <= 135 + 22 ) return RPShape::angle45_135;
		if ( alpha > 225 - 22 && alpha <= 225 + 22 ) return RPShape::angle45_225;
		if ( alpha > 315 - 22 && alpha <= 315 + 22 ) return RPShape::angle45_315;
		return RPShape::angle45_0;
	}

	static void getScaleDelta( rp::point& delta, RPShape::angle90 a90, RPShape::PossibleCommand pcmd );
	static void getRectDelta( rp::rect& rect_old, rp::rect& rect_new, rp::point& delta, RPShape::angle90 a90, RPShape::PossibleCommand pcmd );

	struct trans {
		trans( rp::matrix& _matrix ): matrix( _matrix ) {};
		rp::point operator()( const rp::point& point ) {
			return matrix * point;
		}
		rp::matrix& matrix;
	};
	rp::polyline pa_src;
	rp::polyline pa_global;

	virtual void drawPolyline( CDC& dc );
	virtual void drawDocks( CDC& dc );

	virtual RPProject::Cursor getCursor( const rp::point& global_chart_pos );

	virtual bool isShape() const { return true; }
	virtual RPObjectChart* find( const rp::point& global_chart_pos );

	virtual void onRButtonDown( UINT nFlags, CPoint global_chart_pos );

public:
	RPShape( RPObject* parent, const rp::string& name = "shape" );
	virtual ~RPShape();

	virtual rp::string getClassName() const { return "RPShape"; }
	virtual void load( rp::RPXMLNode* node );
	virtual rp::RPXMLNode* save( rp::RPXMLNode* parent_node );

	std::list< RPShape* > getNextBlock();

	const std::vector< RPConnectorDock* >& getDocks() const { return docks; }
	int getDockIndex( const RPConnectorDock* dock ) const;
	RPConnectorDock* getDock( unsigned int index ) const    { return index < docks.size() ? docks[index] : NULL; }

	virtual void setPosition( double posx, double posy );

	void setBgBrush( const CBrush& brush );

	const CFont& getTextFont( COLORREF& color ) const {
		color = text_color;
		return text_font;
	}
	void setTextFont( const CFont& font, COLORREF color, bool show );

//	const CPoint& getSnapToPoint() const { return snap_to_point; }

	virtual void draw( CDC& dc );
	virtual void draw_selected( CDC& dc );

	// �������� ������
	virtual rp::rect getBoundingRect( bool global = true ) const;
	virtual rp::rect getMaxRect();
	virtual rp::rect getBoundingRectNoRotateOuter() {
		transformToGlobal();
		return getBoundingRect().getBoundingRect();
	}
	virtual rp::rect getBoundingRectNoRotateIner() {
		transformToGlobal();
		return pa_global.getBoundingRect();
	}

	// ������� ���� ��������� ������ � ���������� ����������
	virtual void transformToGlobal();

	// ��������� �� ����� ������ ������
	virtual bool pointInPolygon( const rp::point& global_chart_pos ) {
		transformToGlobal();
		return pa_global.extendByPerimetr( static_cast<double>(main_pen_width) / 2.0 ).pointInPolygon( global_chart_pos );
	}
	// ��������� �� ����� � ��������� (������������) ����� ������ (������������� ���������, � �������)
	virtual bool pointInNCArea( const rp::point& global_chart_pos );

	// ����� ���������� ������� (������ ������ ����������� �������)
	virtual void command_before( const rp::point& global_chart_pos, bool first_click );
	// ��������� ������� ��� ��������
	virtual void command_make( const rp::point& global_chart_pos );

	virtual bool can_delete() const { return pcmd == pcmd_move; }
};

#endif // RDO_PROCESS_SHAPE_H

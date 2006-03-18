#ifndef RDO_PROCESS_CHART_OBJECT_H
#define RDO_PROCESS_CHART_OBJECT_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "rdoprocess_object.h"
#include "rdoprocess_matrix.h"
#include "rdoprocess_polyline.h"
#include "rdoprocess_rect.h"
#include "rdoprocess_point.h"
#include "rdoprocess_math.h"
#include "rdoprocess_project.h"

// ----------------------------------------------------------------------------
// ---------- RPChartObject
// ----------------------------------------------------------------------------
class RPChartObject: public RPObject
{
friend class RPFlowChartObject;

public:
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
		pcmd_rotate,        //!< ������ ����� ���������
		pcmd_rotate_tl,     //!< ������ ����� ��������� �� ����� ������� ����
		pcmd_rotate_tr,     //!< ������ ����� ��������� �� ������ ������� ����
		pcmd_rotate_bl,     //!< ������ ����� ��������� �� ����� ������ ����
		pcmd_rotate_br,     //!< ������ ����� ��������� �� ����� ������ ����
		pcmd_rotate_center, //!< ����� ���� ������� ����� �������� �������
		pcmd_scale,         //!< ������ ����� ���� �������������
		pcmd_scale_l,       //!< ������ ����� ���� ������������� �� ����� �������
		pcmd_scale_r,       //!< ������ ����� ���� ������������� �� ������ �������
		pcmd_scale_t,       //!< ������ ����� ���� ������������� �� ����
		pcmd_scale_b,       //!< ������ ����� ���� ������������� �� ���
		pcmd_scale_tl,      //!< ������ ����� ���� ������������� �� ����� ������� ����
		pcmd_scale_tr,      //!< ������ ����� ���� ������������� �� ������ ������� ����
		pcmd_scale_bl,      //!< ������ ����� ���� ������������� �� ����� ������ ����
		pcmd_scale_br       //!< ������ ����� ���� ������������� �� ������ ������ ����
	};

private:
	mutable rp::point rotate_center;
	mutable bool      rotate_center_inited;
/*
	class Backup {
	public:
		rp::matrix matrix_transform;
		rp::matrix matrix_rotate;
		rp::matrix matrix_transform_post;
		rp::matrix matrix_scale;
		int        rotation_alpha;
	};
*/
protected:
	RPChartObject*     chartParent() const { return !isFlowChart() && parent && parent->isChartObject() ? static_cast<RPChartObject*>(parent) : NULL; }
	RPFlowChartObject* flowChart() const;
	virtual bool isFlowChart() const { return false; }
	int  main_pen_width;
	CPen main_pen;

	void getChartObjects( std::list< RPChartObject* >& objects ) const {
		std::list< RPObject* >::const_iterator it = begin();
		while ( it != end() ) {
			if ( (*it)->isChartObject() ) objects.push_back( static_cast<RPChartObject*>(*it) );
			it++;
		}
	}

	virtual void modify();
	virtual void update();

	virtual RPProject::Cursor getCursor( const rp::point& global_chart_pos );
	virtual RPChartObject* find( const rp::point& global_chart_pos );

	rp::matrix matrix_transform;
	rp::matrix matrix_rotate;
	rp::matrix matrix_transform_post;
	rp::matrix matrix_scale;
	double rotation_alpha;

//	std::list< Backup > backup;

	rp::matrix selfMatrix() const {
		return matrix_transform * matrix_rotate * matrix_transform_post * matrix_scale;
	}
	rp::matrix globalMatrix( bool self = true ) const {
		if ( self ) {
			return chartParent() ? chartParent()->globalMatrix( false ) * selfMatrix() : selfMatrix();
		} else {
			return chartParent() ? chartParent()->globalMatrix( false ) * matrix_transform * matrix_rotate * matrix_transform_post : matrix_transform * matrix_rotate * matrix_transform_post;
		}
//		return chartParent() ? chartParent()->globalMatrix() * selfMatrix() : selfMatrix();
	}
	rp::matrix flowchartMatrix() const {
		RPChartObject* flowchart = reinterpret_cast<RPChartObject*>(flowChart());
		return flowchart ? flowchart->selfMatrix() : rp::matrix();
	}
	rp::matrix parentMatrix( bool first = true ) const {
		if ( first ) {
			return chartParent() ? chartParent()->parentMatrix( false ) : rp::matrix();
		} else {
			return chartParent() ? chartParent()->parentMatrix( false ) * selfMatrix() : selfMatrix();
		}
	}
	rp::matrix rotateCenterMatrix() const {
		return parentMatrix() * matrix_transform;
	}
	rp::matrix globalRotate() const {
		rp::matrix m_rotate;
		RPChartObject::fillRotateMatrix( m_rotate, rotation_alpha );
		return chartParent() ? chartParent()->globalRotate() * m_rotate : m_rotate;
	}
	static void fillRotateMatrix( rp::matrix& m_rotate, double alpha ) {
		alpha *= rp::math::pi / 180.0;
		double cos_a = cos( alpha );
		double sin_a = sin( alpha );
//		if ( fabs(cos_a) < 1e-10 ) cos_d = 0;
//		if ( fabs(sin_a) < 1e-10 ) sin_d = 0;
		m_rotate.data[0][0] = cos_a;
		m_rotate.data[1][1] = cos_a;
		m_rotate.data[0][1] = sin_a;
		m_rotate.data[1][0] = -sin_a;
	}

	virtual void moving( int dx, int dy );

	virtual void onLButtonDown( UINT nFlags, CPoint global_chart_pos ) {
		if ( !isSelected() ) setSelected( true );
	};
	virtual void onLButtonUp( UINT nFlags, CPoint global_chart_pos ) {};
	virtual void onLButtonDblClk( UINT nFlags, CPoint global_chart_pos ) {};
	virtual void onRButtonDown( UINT nFlags, CPoint global_chart_pos ) {};
	virtual void onRButtonUp( UINT nFlags, CPoint global_chart_pos ) {};
	virtual void onMouseMove( UINT nFlags, CPoint global_chart_pos ) {};

	static void getScaleDelta( rp::point& delta, RPChartObject::angle90 a90, RPChartObject::PossibleCommand pcmd );
	static void getRectDelta( rp::rect& rect_old, rp::rect& rect_new, rp::point& delta, RPChartObject::angle90 a90, RPChartObject::PossibleCommand pcmd );

public:
	RPChartObject( RPObject* parent, const rp::string& name = "object" );
	virtual ~RPChartObject();

	virtual bool isChartObject() const { return true; }

	int getPenWidth() const { return main_pen_width; }

	// �������
	virtual void setPosition( double posx, double posy );
	double getX() const         { return matrix_transform.dx_const();          }
	double getY() const         { return matrix_transform.dy_const();          }
	void setX( double value )   { setPosition( value, matrix_transform.dy() ); }
	void setY( double value )   { setPosition( matrix_transform.dx(), value ); }

	// �������
	virtual void setPositionPost( double posx, double posy );
	double getPostX() const       { return matrix_transform_post.dx_const();              }
	double getPostY() const       { return matrix_transform_post.dy_const();              }
	void setPostX( double value ) { setPositionPost( value, matrix_transform_post.dy() ); }
	void setPostY( double value ) { setPositionPost( matrix_transform_post.dx(), value ); }

	// �������
	virtual void setScale( double sx, double sy );
	double getScaleX() const       { return matrix_scale.sx_const();       }
	double getScaleY() const       { return matrix_scale.sy_const();       }
	void setScaleX( double value ) { setScale( value, matrix_scale.sy() ); }
	void setScaleY( double value ) { setScale( matrix_scale.sx(), value ); }

	// �������
	double RPChartObject::getRotation() const { return rotation_alpha; }
	virtual void setRotation( double alpha );
	// ������� ����� �������� � ���������� �����������
	rp::point getRotateCenter() const {
		if ( !rotate_center_inited ) {
			rotate_center = getBoundingRect( false ).getCenter();
			rotate_center_inited = true;
		}
		return rotateCenterMatrix() * rotate_center;
	}
	// ���������� ����� �������� � ���������� �����������
	void setRotateCenter( const rp::point& global_chart_pos ) { rotate_center = rotateCenterMatrix().obr() * global_chart_pos; }
	// �������� ����� �������� � ��������� �����������
	void setRotateCenterLocalDelta( double dx, double dy );
	// ��������� �� ����� �� ������ �������� ������
	bool isRotateCenter( const rp::point& global_chart_pos ) const;

	// ������� ���������� ���� �������� (�������� 90 ��������)
	angle90 getAngle90() const {
		double alpha = getRotation();
		if ( alpha > 270 + 45 || alpha <= 45       ) return RPChartObject::angle90_0;
		if ( alpha > 45       && alpha <= 90 + 45  ) return RPChartObject::angle90_90;
		if ( alpha > 90 + 45  && alpha <= 180 + 45 ) return RPChartObject::angle90_180;
		if ( alpha > 180 + 45 && alpha <= 270 + 45 ) return RPChartObject::angle90_270;
		return RPChartObject::angle90_0;
	}

	// ������� ���������� ���� �������� (�������� 45 ��������)
	angle45 getAngle45() const {
		double alpha = getRotation();
		if ( alpha > 360 - 22 || alpha <= 22       ) return RPChartObject::angle45_0;
		if ( alpha > 90 - 22  && alpha <= 90 + 22  ) return RPChartObject::angle45_90;
		if ( alpha > 180 - 22 && alpha <= 180 + 22 ) return RPChartObject::angle45_180;
		if ( alpha > 270 - 22 && alpha <= 270 + 22 ) return RPChartObject::angle45_270;
		if ( alpha > 45 -  22 && alpha <= 45 + 22  ) return RPChartObject::angle45_45;
		if ( alpha > 135 - 22 && alpha <= 135 + 22 ) return RPChartObject::angle45_135;
		if ( alpha > 225 - 22 && alpha <= 225 + 22 ) return RPChartObject::angle45_225;
		if ( alpha > 315 - 22 && alpha <= 315 + 22 ) return RPChartObject::angle45_315;
		return RPChartObject::angle45_0;
	}
/*
	// ���� ��� ������ ������
	void backup_push() {
		Backup bkp;
		bkp.matrix_transform      = matrix_transform;
		bkp.matrix_rotate         = matrix_rotate;
		bkp.matrix_transform_post = matrix_transform_post;
		bkp.matrix_scale          = matrix_scale;
		bkp.rotation_alpha        = rotation_alpha;
		backup.push_back( bkp );
	}
	void backup_pop() {
		Backup bkp = backup.back();
		backup.pop_back();
		matrix_transform      = bkp.matrix_transform;
		matrix_rotate         = bkp.matrix_rotate;
		matrix_transform_post = bkp.matrix_transform_post;
		matrix_scale          = bkp.matrix_scale;
		rotation_alpha        = bkp.rotation_alpha;
	}
	void backup_clear() { backup.clear(); }
*/
	// ��������/����� ��������� � ������
	virtual void setSelected( bool value );
	// ��������� ������
	virtual void draw( CDC& dc );
	virtual void draw_after( CDC& dc );
	virtual void draw_selected( CDC& dc ) {};
	virtual void draw1( CDC& dc ) {};

	// �������� ������
	virtual rp::rect getBoundingRect( bool global = true ) const = 0;
	virtual rp::rect getMaxRect()  { return getBoundingRect(); }

	// ����� � ���������� �����������
	rp::point getCenter() const {
		return globalMatrix() * getBoundingRect( false ).getCenter();
	}

	// ������� ���� ��������� ������ � ���������� ����������
	virtual void transformToGlobal() = 0;
	// ��������� �� ����� ������ ������
	virtual bool pointInPolygon( const rp::point& global_chart_pos ) = 0;
	// ��������� �� ����� � ��������� (������������) ����� ������ (������������� ���������, � �������)
	virtual bool pointInNCArea( const rp::point& global_chart_pos ) = 0;
	// ��������� ������� ��� ��������
	virtual PossibleCommand getPossibleCommand( const rp::point& global_chart_pos, bool for_cursor = false ) { return pcmd_none; }
};

#endif // RDO_PROCESS_CHART_OBJECT_H

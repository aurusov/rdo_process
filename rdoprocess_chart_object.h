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

// ----------------------------------------------------------------------------
// ---------- RPChartObject
// ----------------------------------------------------------------------------
class RPChartObject: public RPObject
{
friend class RPFlowChart;

private:
	mutable rp::point rotate_center;
	mutable bool      rotate_center_inited;

protected:
	RPChartObject* chart_parent;
	RPFlowChart* flowchart;
	int  main_pen_width;
	CPen main_pen;

	rp::matrix matrix_transform;
	rp::matrix matrix_rotate;
	rp::matrix matrix_transform_post;
	rp::matrix matrix_scale;
	double rotation_alpha;

	rp::matrix selfMatrix() const {
		return matrix_transform * matrix_rotate * matrix_transform_post * matrix_scale;
	}
	rp::matrix globalMatrix() const {
		return chart_parent ? chart_parent->globalMatrix() * selfMatrix() : selfMatrix();
	}
	rp::matrix parentMatrix( bool self = true ) const {
		if ( self ) {
			return chart_parent ? chart_parent->parentMatrix( false ) : rp::matrix();
		} else {
			return chart_parent ? chart_parent->parentMatrix( false ) * selfMatrix() : selfMatrix();
		}
	}
	rp::matrix rotateCenterMatrix() const {
		return parentMatrix() * matrix_transform;
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

public:
	RPChartObject( RPObject* parent, RPChartObject* chart_parent, RPFlowChart* flowchart, const rp::string& name = "object" );
	virtual ~RPChartObject();

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
	double getScaleX()             { return matrix_scale.sx();             }
	double getScaleY()             { return matrix_scale.sy();             }
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
	void setRotateCenter( const rp::point& point ) { rotate_center = rotateCenterMatrix().obr() * point; }
	// �������� ����� �������� � ��������� �����������
	void setRotateCenterLocalDelta( double dx, double dy );
	// ��������� �� ����� �� ������ �������� ������
	bool isRotateCenter( const CPoint& point ) const;

	// ��������/����� ��������� � ������
	virtual void setSelected( bool value );
	// ��������� ������
	virtual void draw( CDC& dc ) = 0;

	// �������� ������
	virtual rp::rect getBoundingRect( bool global = true ) const = 0;

	// ����� � ���������� �����������
	CPoint getCenter() const {
		return globalMatrix() * getBoundingRect( false ).getCenter();
	}

	// ������� ���� ��������� ������ � ���������� ����������
	virtual void transformToGlobal() = 0;
	// ��������� �� ����� ������ ������
	virtual bool pointInPolygon( const CPoint& point, bool byperimetr = true ) = 0;

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
	virtual PossibleCommand getPossibleCommand( const CPoint& global_pos ) const { return pcmd_none; }
};

#endif // RDO_PROCESS_CHART_OBJECT_H

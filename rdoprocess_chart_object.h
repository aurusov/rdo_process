#ifndef RDO_PROCESS_CHART_OBJECT_H
#define RDO_PROCESS_CHART_OBJECT_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "rdoprocess_object.h"
#include "rdoprocess_matrix.h"
#include "rdoprocess_polyline.h"
#include "rdoprocess_rect.h"

// ----------------------------------------------------------------------------
// ---------- RPChartObject
// ----------------------------------------------------------------------------
class RPChartObject: public RPObject
{
friend class RPFlowChart;

private:
	mutable CPoint rotate_center;
	mutable bool   rotate_center_inited;
CPoint p0;
CPoint p1;
CPoint p2;

protected:
	RPChartObject* chart_parent;
	RPFlowChart* flowchart;
	int  main_pen_width;
	CPen main_pen;

	rp::matrix matrix_transform;
	rp::matrix matrix_rotate;
	rp::matrix matrix_scale;
	double rotation_alpha;

	rp::matrix selfMatrix() const {
		rp::matrix r_center;
		r_center.dx() = -rotate_center.x;
		r_center.dy() = -rotate_center.y;
		return matrix_transform * r_center.obr() * matrix_rotate * r_center * matrix_scale;
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
	rp::matrix rotateCenterMatrix( bool self = true ) const {
		return parentMatrix() * matrix_transform;
//		if ( self ) {
//			return chart_parent ? chart_parent->rotateCenterMatrix( false ) * matrix_transform : matrix_transform;
//		} else {
//			return chart_parent ? chart_parent->rotateCenterMatrix( false ) * selfMatrix() : selfMatrix();
//		}
	}

	virtual void moving( int dx, int dy );

public:
	RPChartObject( RPObject* parent, RPChartObject* chart_parent, RPFlowChart* flowchart, const rp::string& name = "object" );
	virtual ~RPChartObject();

	int getPenWidth() const { return main_pen_width; }

	// �������
	virtual void setPosition( double posx, double posy );
	double getX()               { return matrix_transform.dx();                }
	double getY()               { return matrix_transform.dy();                }
	void setX( double value )   { setPosition( value, matrix_transform.dy() ); }
	void setY( double value )   { setPosition( matrix_transform.dx(), value ); }

	// �������
	virtual void setScale( double sx, double sy ) {
		matrix_scale.sx() = sx;
		matrix_scale.sy() = sy;
	}
	int getScaleX()                { return matrix_scale.sx();             }
	int getScaleY()                { return matrix_scale.sy();             }
	void setScaleX( double value ) { setScale( value, matrix_scale.sy() ); }
	void setScaleY( double value ) { setScale( matrix_scale.sx(), value ); }

	// �������
	double RPChartObject::getRotation() const { return rotation_alpha; }
	virtual void setRotation( double alpha );
	// ����� �������� � ���������� �����������
	CPoint getRotateCenter() const {
		if ( !rotate_center_inited ) {
			rotate_center = getBoundingRect( false ).getCenter();
			rotate_center_inited = true;
		}
		return rotateCenterMatrix() * rotate_center;
	}
	void setRotateCenter( const CPoint& point );
	// ��������� �� ����� �� ������ �������� ������
	bool isRotateCenter( const CPoint& point ) const;

	// ��������/����� ��������� � ������
	virtual void setSelected( bool value );
	// ��������� ������
	virtual void draw( CDC& dc );

	// �������� ������
	virtual rp::rect getBoundingRect( bool global = true ) const = 0;

	// ����� � ���������� �����������
	CPoint getCenter() const {
		return globalMatrix() * getBoundingRect( false ).getCenter();
	}

	// ������� ���� ��������� ������ � ���������� ���������� (�������� ����� meshToGlobal)
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
	virtual PossibleCommand getPossibleCommand( int global_x, int global_y ) const { return pcmd_none; }
};

#endif // RDO_PROCESS_CHART_OBJECT_H

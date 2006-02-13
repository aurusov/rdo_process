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

protected:
	RPChartObject* chart_parent;
	RPFlowChart* flowchart;
	int  main_pen_width;
	CPen main_pen;

	rp::matrix matrix_transform;
	rp::matrix matrix_rotate;
	rp::matrix matrix_scale;
	double rotation_alpha;

	rp::matrix globalMatrix() const;
	rp::matrix parentMatrix() const;

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
	// ����� �������� � ���������� �����������
	CPoint getRotateCenter() const {
		if ( !rotate_center_inited ) {
			rotate_center = getBoundingRect( false ).getCenter();
			rotate_center_inited = true;
		}
		return globalMatrix() * rotate_center;
	}

	// ������� ���� ��������� ������ � ���������� ���������� (�������� ����� meshToGlobal)
	virtual void transformToGlobal() = 0;
	// ��������� �� ����� ������ ������
	virtual bool pointInPolygon( const CPoint& point, bool byperimetr = true ) = 0;
	// ��������� �� ����� �� ������ �������� ������
	bool isRotateCenter( const CPoint& point ) const;

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

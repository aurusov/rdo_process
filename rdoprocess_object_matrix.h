#ifndef RDO_PROCESS_OBJECT_MATRIX_H
#define RDO_PROCESS_OBJECT_MATRIX_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "rdoprocess_object_chart.h"
#include "rdoprocess_math.h"

#include <vector>

// ----------------------------------------------------------------------------
// ---------- RPObjectMatrix
// ----------------------------------------------------------------------------
class RPObjectMatrix: public RPObjectChart
{
private:
	rp::point rotate_center;

public:
	enum m_mask {
		m_tr  = 0x01,
		m_rt  = 0x02,
		m_pt  = 0x04,
		m_sc  = 0x08,
		m_all = 0x0F
	};

protected:
	virtual bool isMatrix() const { return true; }
	RPObjectMatrix* matrixParent() const {
		RPObjectChart* chart_parent = chartParent();
		return chart_parent && chart_parent->isMatrix() ? static_cast<RPObjectMatrix*>(chart_parent) : NULL;
	}

	rp::matrix matrix_transform;
	rp::matrix matrix_rotate;
	rp::matrix matrix_transform_post;
	rp::matrix matrix_scale;
	double rotation_alpha;

	rp::matrix selfMatrix( int mask = m_all ) const {
		if ( mask == m_all ) return matrix_transform * matrix_rotate * matrix_transform_post * matrix_scale;
		rp::matrix m;
		if ( mask & m_tr ) m = matrix_transform;
		if ( mask & m_rt ) m = m * matrix_rotate;
		if ( mask & m_pt ) m = m * matrix_transform_post;
		if ( mask & m_sc ) m = m * matrix_scale;
		return m;
	}
	rp::matrix parentMatrix( int mask = m_all, bool first = true ) const {
		RPObjectMatrix* matrix_parent = matrixParent();
		if ( first ) {
			return matrix_parent ? matrix_parent->parentMatrix( mask, false ) : rp::matrix();
		} else {
			return matrix_parent ? matrix_parent->parentMatrix( mask, false ) * selfMatrix( mask ) : selfMatrix( mask );
		}
	}
	rp::matrix flowchartMatrix() const {
		// ���������� ����������� ����� ������ ������, ���
		// � ���� ������ �� ��������� ����� RPFlowChartObject,
		// � ��������� "rdoprocess_object_flowchart.h" �� �������
		RPObjectMatrix* flowchart = reinterpret_cast<RPObjectMatrix*>(flowChart());
		return flowchart ? flowchart->selfMatrix() : rp::matrix();
	}
	rp::matrix parentRotate( bool first = true ) const {
		RPObjectMatrix* matrix_parent = matrixParent();
		if ( first ) {
			return matrix_parent ? matrix_parent->parentRotate( false ) : rp::matrix();
		} else {
			return globalRotate();
		}
	}
	rp::matrix globalRotate() const {
		rp::matrix m_rotate;
		RPObjectMatrix::fillRotateMatrix( m_rotate, rotation_alpha );
		RPObjectMatrix* matrix_parent = matrixParent();
		return matrix_parent ? matrix_parent->globalRotate() * m_rotate : m_rotate;
	}
	rp::matrix rotateCenterMatrix() const {
		return parentMatrix( m_all & ~m_sc ) * matrix_transform;
	}
	// ������� ����� �������� � ���������� �����������
	rp::point getRotateCenter() const {
		return rotateCenterMatrix() * rotate_center;
	}
	// ���������� ����� �������� � ���������� �����������
	void setRotateCenter( const rp::point& global_chart_pos ) {
		rotate_center = rotateCenterMatrix().obr() * global_chart_pos;
	}
	static void fillRotateMatrix( rp::matrix& m_rotate, double alpha ) {
		alpha *= rp::math::pi / 180.0;
		double cos_a = cos( alpha );
		double sin_a = sin( alpha );
//		if ( fabs(cos_a) < 1e-10 ) cos_a = 0;
//		if ( fabs(sin_a) < 1e-10 ) sin_a = 0;
		m_rotate.data[0][0] = cos_a;
		m_rotate.data[1][1] = cos_a;
		m_rotate.data[0][1] = sin_a;
		m_rotate.data[1][0] = -sin_a;
	}
	// �������� ������
	virtual rp::rect getMaxRect();

/*
	rp::matrix selfMatrix() const {
		return matrix_transform * matrix_rotate * matrix_transform_post * matrix_scale;
	}
	rp::matrix selfMatrix_noScale() const {
		return matrix_transform * matrix_rotate * matrix_transform_post;
	}
	rp::matrix parentMatrix_noScale( bool first = true ) const {
		RPObjectMatrix* matrix_parent = matrixParent();
		if ( first ) {
			return matrix_parent ? matrix_parent->parentMatrix_noScale( false ) : rp::matrix();
		} else {
			return matrix_parent ? matrix_parent->parentMatrix_noScale( false ) * selfMatrix( m_all & ~m_sc ) : selfMatrix( m_all & ~m_sc );
		}
	}
	rp::matrix rotateCenterMatrix() const {
		return parentMatrix_noScale() * matrix_transform;
	}
	rp::matrix globalMatrix( bool first = true ) const {
		RPObjectMatrix* matrix_parent = matrixParent();
		if ( first ) {
			return matrix_parent ? matrix_parent->globalMatrix( false ) * selfMatrix() : selfMatrix();
		} else {
			return matrix_parent ? matrix_parent->globalMatrix( false ) * selfMatrix( m_all & ~m_sc ) : selfMatrix( m_all & ~m_sc );
		}
	}
*/

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
	double getRotation() const { return rotation_alpha; }
	double getRotationGlobal( bool first = true ) const {
		RPObjectMatrix* matrix_parent = matrixParent();
		if ( first ) {
			double alpha = matrix_parent ? matrix_parent->getRotationGlobal() + rotation_alpha : rotation_alpha;
			while ( alpha < 0 )   alpha += 360;
			while ( alpha >= 360 ) alpha -= 360;
			return alpha;
		} else {
			return matrix_parent ? matrix_parent->getRotationGlobal() + rotation_alpha : rotation_alpha;
		}
	}
	virtual void setRotation( double alpha );

	// �������� ����� �������� � ��������� �����������
	void setRotateCenterLocalDelta( double dx, double dy );
	// ��������� �� ����� �� ������ �������� ������
	bool isRotateCenter( const rp::point& global_chart_pos ) const;

	// ����� � ���������� �����������
	rp::point getCenter() const { return globalMatrix() * getBoundingRect( false ).getCenter(); }

public:
	RPObjectMatrix( RPObject* parent, const rp::string& name = "object" );
	virtual ~RPObjectMatrix();

	rp::matrix globalMatrix( int mask_parent = m_all & ~m_sc, int mask_self = m_all ) const {
		RPObjectMatrix* matrix_parent = matrixParent();
		return matrix_parent ? matrix_parent->parentMatrix( mask_parent, false ) * selfMatrix( mask_self ) : selfMatrix( mask_self );
	}

/*
	class Backup {
	public:
		rp::matrix matrix_transform;
		rp::matrix matrix_rotate;
		rp::matrix matrix_transform_post;
		rp::matrix matrix_scale;
		int        rotation_alpha;
	};
	std::list< Backup > backup;

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
};

#endif // RDO_PROCESS_OBJECT_MATRIX_H

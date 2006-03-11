#include "stdafx.h"
#include "rdoprocess_shape.h"
#include "rdoprocess_flowchart.h"
#include "rdoprocess_app.h"
#include "rdoprocess_math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// ----------------------------------------------------------------------------
// ---------- RPShape
// ----------------------------------------------------------------------------
RPShape::RPShape( RPObject* _parent, RPChartObject* _chart_parent, RPFlowChart* _flowchart, const rp::string& _name ):
	RPChartObject( _parent, _chart_parent, _flowchart, _name )
//	snap_to_point( 0, 0 )
{
	flowchart->insertShape( this );
}

RPShape::~RPShape()
{
	flowchart->deleteShape( this );
}

void RPShape::setPosition( int x, int y )
{
	RPChartObject::setPosition( x, y );
	flowchart->snapToGrid( this );
}

void RPShape::transformToGlobal()
{
	if ( pa_global.size() != pa_src.size() ) {
		pa_global.resize( pa_src.size() );
	}
	trans tr( globalMatrix() );
	std::transform( pa_src.begin(), pa_src.end(), pa_global.begin(), tr );
}

rp::rect RPShape::getBoundingRect( bool global ) const
{
	rp::rect bound_rect;
	if ( !pa_src.empty() ) {
		int x_min = pa_src[0].x;
		int y_min = pa_src[0].y;
		int x_max = pa_src[0].x;
		int y_max = pa_src[0].y;
		std::vector< rp::point >::const_iterator it = pa_src.begin() + 1;
		while ( it != pa_src.end() ) {
			if ( x_min > it->x ) x_min = it->x;
			if ( y_min > it->y ) y_min = it->y;
			if ( x_max < it->x ) x_max = it->x;
			if ( y_max < it->y ) y_max = it->y;
			it++;
		}
		rp::rect rect( x_min, y_min, x_max, y_max );
		if ( global ) rect.transform( globalMatrix() );
		bound_rect = rect;
	}
	return bound_rect;
}

void RPShape::drawPolyline( CDC& dc )
{
	if ( pa_global.size() < 2 ) return;
	dc.SelectObject( main_pen );
	dc.BeginPath();
	if ( pa_global.isPolygon() ) {
		dc.Polygon( &pa_global.getWinPolyline()[0], pa_global.size() );
	} else {
		dc.Polyline( &pa_global.getWinPolyline()[0], pa_global.size() );
	}
	dc.EndPath();
	dc.StrokePath();

	rp::matrix gm = globalMatrix();
	CPen pen1( PS_SOLID, 1, RGB(-1,0,0) );
	dc.SelectObject( pen1 );
	dc.MoveTo( gm * CPoint(-70,0) );
	dc.LineTo( gm * CPoint(70,0) );
	CPen pen2( PS_SOLID, 1, RGB(0,-1,0) );
	dc.SelectObject( pen2 );
	dc.MoveTo( gm * CPoint(0,-70) );
	dc.LineTo( gm * CPoint(0,70) );
	dc.DrawText( rp::string::format( "alpha = %f", rotation_alpha ).c_str(), CRect( gm * CPoint(0,70), CSize(100,100)), DT_SINGLELINE );
}

/*
void RPShape::drawConnectorsInput( CDC& dc )
{
	if ( flowChart->getShowConnectorPoint() ) {
		painter.setPen( flowChart->getShapeColor() );
		painter.setBrush( flowChart->getConnectorDockColor() );
		for ( unsigned int i = 0; i < conI.size(); i++ ) {
			painter.drawEllipse( conI.point(i).x() - 3, conI.point(i).y() - 3, 7, 7 );
		}
	}
}

void RPShape::drawConnectorsOutput( CDC& dc )
{
	if ( flowChart->getShowConnectorPoint() ) {
		painter.setPen( flowChart->getShapeColor() );
		painter.setBrush( flowChart->getConnectorDockColor() );
		for ( unsigned int i = 0; i < conO.size(); i++ ) {
			painter.drawEllipse( conO.point(i).x() - 3, conO.point(i).y() - 3, 7, 7 );
		}
	}
}
*/

void RPShape::draw( CDC& dc )
{
	drawPolyline( dc );

/*
	if ( flowChart->getShowShapeName() ) {
		painter.setPen( flowChart->getShapeColor() );
		int name_x = getX() + flowChart->getPaperBorder();
		int name_y = getY() + flowChart->getPaperBorder();
		painter.drawText( name_x, name_y, size.width(), size.height()-1, Qt::AlignHCenter | Qt::AlignVCenter | Qt::SingleLine, name );
	}
	drawConnectorsInput( painter );
	drawConnectorsOutput( painter );
*/
}

void RPShape::draw1( CDC& dc )
{
	CPen pen( PS_SOLID, 1, RGB(-1,0,0) );
	dc.SelectObject( pen );
	dc.BeginPath();
	if ( pa_global.isPolygon() ) {
		dc.Polygon( &pa_global.getWinPolyline()[0], pa_global.size() );
	} else {
//		dc.Polyline( &pa_global.getWinPolyline()[0], pa_global.size() );
	}
	dc.EndPath();
	dc.StrokePath();
}

RPChartObject::PossibleCommand RPShape::getPossibleCommand( const rp::point& global_pos, bool for_cursor )
{
	// �������� �������� �� ����������� ������ ��������. �� �������������� ������ ���������, ������ � ����������� ������ ������.
	if ( isRotateCenter( global_pos ) ) return RPChartObject::pcmd_rotate_center;
	rp::rect rect = getBoundingRect();
	int sensitivity = flowchart->getSensitivity();
	angle90 a90 = getAngle90();
	angle45 a45 = getAngle45();
	double alpha = getRotation();
	// �������� �������� �� ���������� �� ������ ������ ����, �.�. ������, ������ � ����, ����� ����������� �� ����
	if ( rpapp.project().getFlowState() == RPProject::flow_select ) {
		if ( rp::math::getLength( rect.p_tl(), global_pos ) <= sensitivity ) {
			if ( for_cursor ) {
				switch ( a45 ) {
					case angle45_180: return RPChartObject::pcmd_scale_br;
				}
			} else {
				switch ( a90 ) {
					case angle90_180: return RPChartObject::pcmd_scale_br;
				}
			}
		}
		if ( rp::math::getLength( rect.p_tr(), global_pos ) <= sensitivity ) {
			if ( for_cursor ) {
				switch ( a45 ) {
					case angle45_270: return RPChartObject::pcmd_scale_br;
				}
			} else {
				switch ( a90 ) {
					case angle90_270: return RPChartObject::pcmd_scale_br;
				}
			}
		}
		if ( rp::math::getLength( rect.p_bl(), global_pos ) <= sensitivity ) {
			if ( for_cursor ) {
				switch ( a45 ) {
					case angle45_90 : return RPChartObject::pcmd_scale_br;
				}
			} else {
				switch ( a90 ) {
					case angle90_90 : return RPChartObject::pcmd_scale_br;
				}
			}
		}
		if ( rp::math::getLength( rect.p_br(), global_pos ) <= sensitivity ) {
			if ( for_cursor ) {
				switch ( a45 ) {
					case angle45_0  : return RPChartObject::pcmd_scale_br;
				}
			} else {
				switch ( a90 ) {
					case angle90_0  : return RPChartObject::pcmd_scale_br;
				}
			}
		}
		// �������� �������� �� ���������� �� ����� ������ ����, �.�. ������, ������ � �������������� �����, ����� ����������� ������ �� ����, � �� � ����-�����
		if ( rp::math::getLength( rect.p_tl(), global_pos ) <= sensitivity ) {
			if ( for_cursor ) {
				switch ( a45 ) {
					case angle45_90 : return RPChartObject::pcmd_scale_bl;
				}
			} else {
				switch ( a90 ) {
					case angle90_90 : return RPChartObject::pcmd_scale_bl;
				}
			}
		}
		if ( rp::math::getLength( rect.p_tr(), global_pos ) <= sensitivity ) {
			if ( for_cursor ) {
				switch ( a45 ) {
					case angle45_180: return RPChartObject::pcmd_scale_bl;
				}
			} else {
				switch ( a90 ) {
					case angle90_180: return RPChartObject::pcmd_scale_bl;
				}
			}
		}
		if ( rp::math::getLength( rect.p_bl(), global_pos ) <= sensitivity ) {
			if ( for_cursor ) {
				switch ( a45 ) {
					case angle45_0  : return RPChartObject::pcmd_scale_bl;
				}
			} else {
				switch ( a90 ) {
					case angle90_0  : return RPChartObject::pcmd_scale_bl;
				}
			}
		}
		if ( rp::math::getLength( rect.p_br(), global_pos ) <= sensitivity ) {
			if ( for_cursor ) {
				switch ( a45 ) {
					case angle45_270: return RPChartObject::pcmd_scale_bl;
				}
			} else {
				switch ( a90 ) {
					case angle90_270: return RPChartObject::pcmd_scale_bl;
				}
			}
		}
	}
	bool any = rpapp.project().getFlowState() == RPProject::flow_select || rpapp.project().getFlowState() == RPProject::flow_rotate;
	// ����� ����� � ��� ����������� � ��� ��������
	if ( any ) {
		// �������� �������� �� ���������� �� ������ �����, �.�. ������, ������ � �������������� �����, ����� ����������� ���� �� ����, � �� �����
		if ( rp::math::getLength( rect.p_r(), global_pos ) <= sensitivity ) {
			if ( for_cursor ) {
				switch ( a45 ) {
					case angle45_270: return RPChartObject::pcmd_scale_b;
				}
			} else {
				switch ( a90 ) {
					case angle90_270: return RPChartObject::pcmd_scale_b;
				}
			}
		}
		if ( rp::math::getLength( rect.p_l(), global_pos ) <= sensitivity ) {
			if ( for_cursor ) {
				switch ( a45 ) {
					case angle45_90 : return RPChartObject::pcmd_scale_b;
				}
			} else {
				switch ( a90 ) {
					case angle90_90 : return RPChartObject::pcmd_scale_b;
				}
			}
		}
		if ( rp::math::getLength( rect.p_t(), global_pos ) <= sensitivity ) {
			if ( for_cursor ) {
				switch ( a45 ) {
					case angle45_180: return RPChartObject::pcmd_scale_b;
				}
			} else {
				switch ( a90 ) {
					case angle90_180: return RPChartObject::pcmd_scale_b;
				}
			}
		}
		if ( rp::math::getLength( rect.p_b(), global_pos ) <= sensitivity ) {
			if ( for_cursor ) {
				switch ( a45 ) {
					case angle45_0  : return RPChartObject::pcmd_scale_b;
				}
			} else {
				switch ( a90 ) {
					case angle90_0  : return RPChartObject::pcmd_scale_b;
				}
			}
		}
		// �������� �������� �� ���������� �� ������ �����, �.�. ������, ������ � ������������ �����, ����� ����������� ������ �� ����, � �� �����
		if ( rp::math::getLength( rect.p_r(), global_pos ) <= sensitivity ) {
			if ( for_cursor ) {
				switch ( a45 ) {
					case angle45_0  : return RPChartObject::pcmd_scale_r;
				}
			} else {
				switch ( a90 ) {
					case angle90_0  : return RPChartObject::pcmd_scale_r;
				}
			}
		}
		if ( rp::math::getLength( rect.p_l(), global_pos ) <= sensitivity ) {
			if ( for_cursor ) {
				switch ( a45 ) {
					case angle45_180: return RPChartObject::pcmd_scale_r;
				}
			} else {
				switch ( a90 ) {
					case angle90_180: return RPChartObject::pcmd_scale_r;
				}
			}
		}
		if ( rp::math::getLength( rect.p_t(), global_pos ) <= sensitivity ) {
			if ( for_cursor ) {
				switch ( a45 ) {
					case angle45_270: return RPChartObject::pcmd_scale_r;
				}
			} else {
				switch ( a90 ) {
					case angle90_270: return RPChartObject::pcmd_scale_r;
				}
			}
		}
		if ( rp::math::getLength( rect.p_b(), global_pos ) <= sensitivity ) {
			if ( for_cursor ) {
				switch ( a45 ) {
					case angle45_90 : return RPChartObject::pcmd_scale_r;
				}
			} else {
				switch ( a90 ) {
					case angle90_90 : return RPChartObject::pcmd_scale_r;
				}
			}
		}
		// ��� ��������� (������ ����� ���� �����������)
		if ( rp::math::getLength( rect.p_r(), global_pos ) <= sensitivity ) {
			if ( for_cursor ) {
				switch ( a45 ) {
					case angle45_0  : return RPChartObject::pcmd_scale_r;
					case angle45_90 : return RPChartObject::pcmd_scale_t;
					case angle45_180: return RPChartObject::pcmd_scale_l;
					case angle45_270: return RPChartObject::pcmd_scale_b;
					case angle45_45 : return RPChartObject::pcmd_scale_tr;
					case angle45_135: return RPChartObject::pcmd_scale_tl;
					case angle45_225: return RPChartObject::pcmd_scale_bl;
					case angle45_315: return RPChartObject::pcmd_scale_br;
				}
			} else {
				switch ( a90 ) {
					case angle90_0  : return RPChartObject::pcmd_scale_r;
					case angle90_90 : return RPChartObject::pcmd_scale_t;
					case angle90_180: return RPChartObject::pcmd_scale_l;
					case angle90_270: return RPChartObject::pcmd_scale_b;
				}
			}
		}
		if ( rp::math::getLength( rect.p_l(), global_pos ) <= sensitivity ) {
			if ( for_cursor ) {
				switch ( a45 ) {
					case angle45_0  : return RPChartObject::pcmd_scale_l;
					case angle45_90 : return RPChartObject::pcmd_scale_b;
					case angle45_180: return RPChartObject::pcmd_scale_r;
					case angle45_270: return RPChartObject::pcmd_scale_t;
					case angle45_45 : return RPChartObject::pcmd_scale_bl;
					case angle45_135: return RPChartObject::pcmd_scale_br;
					case angle45_225: return RPChartObject::pcmd_scale_tr;
					case angle45_315: return RPChartObject::pcmd_scale_tl;
				}
			} else {
				switch ( a90 ) {
					case angle90_0  : return RPChartObject::pcmd_scale_l;
					case angle90_90 : return RPChartObject::pcmd_scale_b;
					case angle90_180: return RPChartObject::pcmd_scale_r;
					case angle90_270: return RPChartObject::pcmd_scale_t;
				}
			}
		}
		if ( rp::math::getLength( rect.p_t(), global_pos ) <= sensitivity ) {
			if ( for_cursor ) {
				switch ( a45 ) {
					case angle45_0  : return RPChartObject::pcmd_scale_t;
					case angle45_90 : return RPChartObject::pcmd_scale_l;
					case angle45_180: return RPChartObject::pcmd_scale_b;
					case angle45_270: return RPChartObject::pcmd_scale_r;
					case angle45_45 : return RPChartObject::pcmd_scale_tl;
					case angle45_135: return RPChartObject::pcmd_scale_bl;
					case angle45_225: return RPChartObject::pcmd_scale_br;
					case angle45_315: return RPChartObject::pcmd_scale_tr;
				}
			} else {
				switch ( a90 ) {
					case angle90_0  : return RPChartObject::pcmd_scale_t;
					case angle90_90 : return RPChartObject::pcmd_scale_l;
					case angle90_180: return RPChartObject::pcmd_scale_b;
					case angle90_270: return RPChartObject::pcmd_scale_r;
				}
			}
		}
		if ( rp::math::getLength( rect.p_b(), global_pos ) <= sensitivity ) {
			if ( for_cursor ) {
				switch ( a45 ) {
					case angle45_0  : return RPChartObject::pcmd_scale_b;
					case angle45_90 : return RPChartObject::pcmd_scale_r;
					case angle45_180: return RPChartObject::pcmd_scale_t;
					case angle45_270: return RPChartObject::pcmd_scale_l;
					case angle45_45 : return RPChartObject::pcmd_scale_br;
					case angle45_135: return RPChartObject::pcmd_scale_tr;
					case angle45_225: return RPChartObject::pcmd_scale_tl;
					case angle45_315: return RPChartObject::pcmd_scale_bl;
				}
			} else {
				switch ( a90 ) {
					case angle90_0  : return RPChartObject::pcmd_scale_b;
					case angle90_90 : return RPChartObject::pcmd_scale_r;
					case angle90_180: return RPChartObject::pcmd_scale_t;
					case angle90_270: return RPChartObject::pcmd_scale_l;
				}
			}
		}
	}
	if ( rpapp.project().getFlowState() == RPProject::flow_select ) {
		// ������ ��� �����������
		if ( rp::math::getLength( rect.p_tl(), global_pos ) <= sensitivity ) {
			if ( for_cursor ) {
				switch ( a45 ) {
					case angle45_0  : return RPChartObject::pcmd_scale_tl;
					case angle45_90 : return RPChartObject::pcmd_scale_bl;
					case angle45_180: return RPChartObject::pcmd_scale_br;
					case angle45_270: return RPChartObject::pcmd_scale_tr;
					case angle45_45 : return RPChartObject::pcmd_scale_l;
					case angle45_135: return RPChartObject::pcmd_scale_b;
					case angle45_225: return RPChartObject::pcmd_scale_r;
					case angle45_315: return RPChartObject::pcmd_scale_t;
				}
			} else {
				switch ( a90 ) {
					case angle90_0  : return RPChartObject::pcmd_scale_tl;
					case angle90_90 : return RPChartObject::pcmd_scale_bl;
					case angle90_180: return RPChartObject::pcmd_scale_br;
					case angle90_270: return RPChartObject::pcmd_scale_tr;
				}
			}
		}
		if ( rp::math::getLength( rect.p_tr(), global_pos ) <= sensitivity ) {
			if ( for_cursor ) {
				switch ( a45 ) {
					case angle45_0  : return RPChartObject::pcmd_scale_tr;
					case angle45_90 : return RPChartObject::pcmd_scale_tl;
					case angle45_180: return RPChartObject::pcmd_scale_bl;
					case angle45_270: return RPChartObject::pcmd_scale_br;
					case angle45_45 : return RPChartObject::pcmd_scale_t;
					case angle45_135: return RPChartObject::pcmd_scale_l;
					case angle45_225: return RPChartObject::pcmd_scale_b;
					case angle45_315: return RPChartObject::pcmd_scale_r;
				}
			} else {
				switch ( a90 ) {
					case angle90_0  : return RPChartObject::pcmd_scale_tr;
					case angle90_90 : return RPChartObject::pcmd_scale_tl;
					case angle90_180: return RPChartObject::pcmd_scale_bl;
					case angle90_270: return RPChartObject::pcmd_scale_br;
				}
			}
		}
		if ( rp::math::getLength( rect.p_bl(), global_pos ) <= sensitivity ) {
			if ( for_cursor ) {
				switch ( a45 ) {
					case angle45_0  : return RPChartObject::pcmd_scale_bl;
					case angle45_90 : return RPChartObject::pcmd_scale_br;
					case angle45_180: return RPChartObject::pcmd_scale_tr;
					case angle45_270: return RPChartObject::pcmd_scale_tl;
					case angle45_45 : return RPChartObject::pcmd_scale_b;
					case angle45_135: return RPChartObject::pcmd_scale_r;
					case angle45_225: return RPChartObject::pcmd_scale_t;
					case angle45_315: return RPChartObject::pcmd_scale_l;
				}
			} else {
				switch ( a90 ) {
					case angle90_0  : return RPChartObject::pcmd_scale_bl;
					case angle90_90 : return RPChartObject::pcmd_scale_br;
					case angle90_180: return RPChartObject::pcmd_scale_tr;
					case angle90_270: return RPChartObject::pcmd_scale_tl;
				}
			}
		}
		if ( rp::math::getLength( rect.p_br(), global_pos ) <= sensitivity ) {
			if ( for_cursor ) {
				switch ( a45 ) {
					case angle45_0  : return RPChartObject::pcmd_scale_br;
					case angle45_90 : return RPChartObject::pcmd_scale_tr;
					case angle45_180: return RPChartObject::pcmd_scale_tl;
					case angle45_270: return RPChartObject::pcmd_scale_bl;
					case angle45_45 : return RPChartObject::pcmd_scale_r;
					case angle45_135: return RPChartObject::pcmd_scale_t;
					case angle45_225: return RPChartObject::pcmd_scale_l;
					case angle45_315: return RPChartObject::pcmd_scale_b;
				}
			} else {
				switch ( a90 ) {
					case angle90_0  : return RPChartObject::pcmd_scale_br;
					case angle90_90 : return RPChartObject::pcmd_scale_tr;
					case angle90_180: return RPChartObject::pcmd_scale_tl;
					case angle90_270: return RPChartObject::pcmd_scale_bl;
				}
			}
		}
	} else if ( rpapp.project().getFlowState() == RPProject::flow_rotate ) {
		// ������ ��� ��������
		if ( rp::math::getLength( rect.p_tl(), global_pos ) <= sensitivity ) {
			switch ( a90 ) {
				case angle90_0  : return RPChartObject::pcmd_rotate_tl;
				case angle90_90 : return RPChartObject::pcmd_rotate_bl;
				case angle90_180: return RPChartObject::pcmd_rotate_br;
				case angle90_270: return RPChartObject::pcmd_rotate_tr;
			}
		}
		if ( rp::math::getLength( rect.p_tr(), global_pos ) <= sensitivity ) {
			switch ( a90 ) {
				case angle90_0  : return RPChartObject::pcmd_rotate_tr;
				case angle90_90 : return RPChartObject::pcmd_rotate_tl;
				case angle90_180: return RPChartObject::pcmd_rotate_bl;
				case angle90_270: return RPChartObject::pcmd_rotate_br;
			}
		}
		if ( rp::math::getLength( rect.p_bl(), global_pos ) <= sensitivity ) {
			switch ( a90 ) {
				case angle90_0  : return RPChartObject::pcmd_rotate_bl;
				case angle90_90 : return RPChartObject::pcmd_rotate_br;
				case angle90_180: return RPChartObject::pcmd_rotate_tr;
				case angle90_270: return RPChartObject::pcmd_rotate_tl;
			}
		}
		if ( rp::math::getLength( rect.p_br(), global_pos ) <= sensitivity ) {
			switch ( a90 ) {
				case angle90_0  : return RPChartObject::pcmd_rotate_br;
				case angle90_90 : return RPChartObject::pcmd_rotate_tr;
				case angle90_180: return RPChartObject::pcmd_rotate_tl;
				case angle90_270: return RPChartObject::pcmd_rotate_bl;
			}
		}
	}
	// ����� ����� � ��� ����������� � ��� ��������
	if ( any ) {
		if ( pointInPolygon( global_pos ) ) {
			return RPChartObject::pcmd_move;
		}
	}
	return RPChartObject::pcmd_none;
}

void RPShape::onLButtonDown( UINT nFlags, CPoint flowchart_mouse_pos )
{
	RPChartObject::onLButtonDown( nFlags, flowchart_mouse_pos );
	TRACE( "onLButtonDown\n" );
}

void RPShape::onLButtonUp( UINT nFlags, CPoint flowchart_mouse_pos )
{
	TRACE( "onLButtonUp\n" );
}

void RPShape::onLButtonDblClk( UINT nFlags, CPoint flowchart_mouse_pos )
{
	TRACE( "onLButtonDblClk\n" );
}

void RPShape::onRButtonDown( UINT nFlags, CPoint flowchart_mouse_pos )
{
	TRACE( "onRButtonDown\n" );
}

void RPShape::onRButtonUp( UINT nFlags, CPoint flowchart_mouse_pos )
{
	TRACE( "onRButtonUp\n" );
}

void RPShape::onMouseMove( UINT nFlags, CPoint flowchart_mouse_pos )
{
	TRACE( "onMouseMove\n" );
}

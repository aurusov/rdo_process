#ifndef RDO_PROCESS_CTRL_PIXMAP_H
#define RDO_PROCESS_CTRL_PIXMAP_H

#if _MSC_VER > 1000
#pragma once
#endif

#include "rdoprocess_string.h"

// ----------------------------------------------------------------------------
// ---------- RPPixmap
// ----------------------------------------------------------------------------
class RPPixmap
{
protected:
	char**   xpm;
	CBitmap  bmp;
	BITMAP   bmp_info;
	COLORREF transparent;
	struct Pixel {
		unsigned int r;
		unsigned int g;
		unsigned int b;
		Pixel():
			r(0),
			g(0),
			b(0)
		{
		}
		Pixel( unsigned int _r, unsigned int _g, unsigned int _b ):
			r(_r),
			g(_g),
			b(_b)
		{
		}
		Pixel( const Pixel& copy ):
			r(copy.r),
			g(copy.g),
			b(copy.b)
		{
		}
	};

	int char_per_pixel;
	int char_per_r;
	int        getNextInt( rp::string& line ) const;
	rp::string getNextStr( rp::string& line ) const;
	rp::string getNextColor( rp::string& line ) const;
	Pixel      getNextPixel( rp::string& line );

public:
	RPPixmap( char* _xpm[] );
	RPPixmap( HICON icon );
	RPPixmap( unsigned int resource, COLORREF _transparent );
	virtual HBITMAP getBitmap()   { return reinterpret_cast<HBITMAP>(bmp.m_hObject); }
	virtual CBitmap& getCBitmap() { return bmp;                                      }
	virtual int getWidth();
	virtual int getHeight();
	virtual HICON getIcon();
	virtual void Draw( HDC hdc, int x, int y, int cx = 0 );
	COLORREF getTransparent() const { return transparent; }
};

#endif // RDO_PROCESS_CTRL_PIXMAP_H

#ifndef RDO_PROCESS_GLOBAL_H
#define RDO_PROCESS_GLOBAL_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include <locale>

namespace rp {

class string: public std::string
{
protected:
	//! ��������� (���������), ������� ������������ ��� �������� ������� � ������ �������
	struct toLower {
		//! �����������
		/*! \param loc - ������. ����� �� ������������ ������ ������� ��� �������.
\n������:\code
toLower tr( std::locale("rus") );
		\endcode
		*/
		toLower( std::locale loc ): m_loc(loc) {};
		char operator()(char c) {
			return std::tolower( c, m_loc );
		}
		std::locale m_loc;
	};
	//! ��������� (���������), ������� ������������ ��� �������� ������� � ������� �������
	struct toUpper {
		toUpper( std::locale loc ): m_loc(loc) {};
		char operator()(char c) {
			return std::toupper( c, m_loc );
		}
		std::locale m_loc;
	};

public:
	//! ����������� ��-���������, ������� ������ ������.
	string(): std::basic_string< char >() {};
	//! ������� ������ �� ���������.
	string( const char* str ): std::basic_string< char >( str ) {};
	//! ����������� �����.
	string( const std::string& str ): std::basic_string< char >( str ) {};

	int      toint() const    { return atoi( c_str() ); }
	long int tolong() const   { return atol( c_str() ); }
	float    tofloat() const  { return atof( c_str() ); }
	double   todouble() const { return strtod( c_str(), NULL ); }

	//! ��������� ����� ����� � �������.
	/*! \param value - ����� ����� ��� �������� � ������.
		\return ��������� ������������� ������ �����.
		\par ������:
		\code
rp::string str = rp::string::fromint( 20 );
		\endcode
		\sa fromdouble()
	*/
	static rp::string fromint( int value ) {
		char buffer[20];
		_itoa( value, buffer, 10 );
		return rp::string( buffer );
	}

	//! ��������� ������������ ����� � �������.
	/*! \param value - ������������ ����� ��� �������� � ������.
		\return ��������� ������������� ������������� �����.
		\par ������:
		\code
rp::string str = rp::string::fromdouble( 20.2 );
		\endcode
		\sa fromint()
	*/
	static rp::string fromdouble( double value ) {
		char buffer[40];
		_gcvt( value, 10, buffer );
		rp::string str( buffer );
		if ( str[str.length()-1] == '.' ) {
			str += '0';
		} else if ( str[str.length()-1] == ',' ) {
			str[str.length()-1] = '.';
			str += '0';
		}
		return str;
	}

	//! ��������� ��� ������� ������ � ��������.
	/*! \return ����� ������, ��� ������� ������� ��������, �������� �������� ��� ���������.
		\sa toupper()
	*/
	rp::string tolower() {
		rp::string str( *this );
		toLower tr( std::locale("rus") );
		std::transform( str.begin(), str.end(), str.begin(), tr );
		return str;
	}
	//! ��������� ��� ������� ������ � ���������.
	/*! \return ����� ������, ��� ������� ������� ���������, �������� �������� ��� ���������.
		\sa tolower()
	*/
	rp::string toupper() {
		rp::string str( *this );
		toUpper tr( std::locale("rus") );
		std::transform( str.begin(), str.end(), str.begin(), tr );
		return str;
	}

};

rp::string format( const char* str, ... );
rp::string format( unsigned int resource, ... );


}

#endif // RDO_PROCESS_GLOBAL_H

#ifndef RDO_PROCESS_MESSAGES_H
#define RDO_PROCESS_MESSAGES_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "rdoprocess_object.h"

// ----------------------------------------------------------------------------
// ---------- RPMessages
// ----------------------------------------------------------------------------
class RPApp;

namespace rp {

class msg: public RPObject
{
friend class RPApp;

protected:
	msg();
	virtual ~msg();

	typedef std::multimap< UINT, RPObject* > Connected;
	Connected connected;

	virtual void notify( RPObject* from, UINT message, WPARAM wParam, LPARAM lParam );

	void sendMessage( RPObject* from, UINT message, WPARAM wParam = 0, LPARAM lParam = 0 );

public:
	void connect( RPObject* to, UINT message );
	void disconnect( RPObject* to );
	void disconnect( RPObject* to, UINT message );

	static const UINT RP_OBJ_BEFOREDELETE;
	static const UINT RP_OBJ_NAMECHANGED;
	static const UINT RP_OBJ_SELCHANGED;
	static const UINT RP_FLOWSTATE_CHANGED;

/*
	��������� ���������:
	RP_OBJ_BEFOREDELETE:
		from    - ��������� ������,
		wParam  - �� ������������,
		lParam  - �� ������������
	RP_OBJ_NAMECHANGED:
		from    - ������, � �������� ��������� ���,
		wParam  - �� ������������,
		lParam  - �� ������������
	RP_OBJ_SELCHANGED:
		from    - ������, � �������� ���������� ���������,
		wParam  - ����� �������� (true/false),
		lParam  - �� ������������
	RP_FLOWSTATE_CHANGED:
		from    - ��������� �� ������,
		wParam  - ����� ��������� �������,
		lParam  - �� ������������
*/

};

}

#endif // RDO_PROCESS_MESSAGES_H

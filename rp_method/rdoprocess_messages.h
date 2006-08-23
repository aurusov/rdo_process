#ifndef RDO_PROCESS_MESSAGES_H
#define RDO_PROCESS_MESSAGES_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "rdoprocess_object.h"

// ----------------------------------------------------------------------------
// ---------- RPMessages
// ----------------------------------------------------------------------------
class RPProject;

namespace rp {

class msg: public RPObject
{
friend class RPProject;

public:
	enum Messages {
		RP_OBJ_BEFOREDELETE = 0,   // from - ��������� ������                        / param �� ������������
		RP_OBJ_NAMECHANGED,        // from - ������, � �������� ��������� ���        / param �� ������������
		RP_OBJ_SELCHANGED,         // from - ������, � �������� ���������� ��������� / param = bool*
		RP_FLOWSTATE_CHANGED       // from - ��������� �� ������                     / param = RPProject::FlowState*
	};

protected:
	msg();
	virtual ~msg();

	typedef std::multimap< UINT, RPObject* > Connected;
	Connected connected;

	virtual void notify( RPObject* from, UINT message, void* param = NULL );

	void sendMessage( RPObject* from, UINT message, void* param = NULL );

public:
	virtual rp::string getClassName() const { return "msg"; }

	void connect( RPObject* to, UINT message );
	void disconnect( RPObject* to );
	void disconnect( RPObject* to, UINT message );
};

} // namespace rp

#endif // RDO_PROCESS_MESSAGES_H

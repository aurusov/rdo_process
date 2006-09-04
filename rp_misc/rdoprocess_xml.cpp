#include "stdafx.h"
#include "rdoprocess_xml.h"
#include <comdef.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace rp {

// ----------------------------------------------------------------------------
// ---------- RPXMLNode
// ----------------------------------------------------------------------------
RPXMLNode::~RPXMLNode()
{
	std::list< MSXML2::IXMLDOMAttribute* >::const_iterator iattr_it = iattrs.begin();
	while ( iattr_it != iattrs.end() ) {
		(*iattr_it)->Release();
		iattr_it++;
	}
	std::list< RPXMLNode* >::const_iterator child_it = childs.begin();
	while ( child_it != childs.end() ) {
		delete *child_it;
		child_it++;
	}
	if ( inode ) inode->Release();
}

rp::string RPXMLNode::getName() const
{
	return node_name;
}

RPXMLNode* RPXMLNode::find( const rp::string& _node_name ) const
{
	std::list< RPXMLNode* >::const_iterator child_it = childs.begin();
	while ( child_it != childs.end() ) {
		if ( (*child_it)->node_name == _node_name ) return *child_it;
		child_it++;
	}
	return NULL;
}

RPXMLNode* RPXMLNode::find( MSXML2::IXMLDOMNode* _inode ) const
{
	std::list< RPXMLNode* >::const_iterator child_it = childs.begin();
	while ( child_it != childs.end() ) {
		if ( (*child_it)->inode == _inode ) return *child_it;
		child_it++;
	}
	return NULL;
}

MSXML2::IXMLDOMNode* RPXMLNode::getFirstINode() const
{
	MSXML2::IXMLDOMNode* ifirst = NULL;
	if ( inode->get_firstChild( &ifirst ) != S_OK ) {
		if ( !ifirst ) return NULL;
		ifirst->Release();
		throw rp::RPXMLException( rp::format("������ ������ ������� ������� ��� %s", node_name.c_str()) );
	}
	return ifirst;
}

rp::string RPXMLNode::getNameByINode( MSXML2::IXMLDOMNode* inode )
{
	BSTR bstr = NULL;
	if ( inode->get_nodeName( &bstr ) != S_OK ) {
		if ( bstr ) ::SysFreeString( bstr );
		throw rp::RPXMLException( rp::format("������ ��������� �����") );
	}
	rp::string name = static_cast<const char*>(_bstr_t(bstr));
	if ( bstr ) ::SysFreeString( bstr );
	return name;
}

rp::RPXMLNode* RPXMLNode::findFirstChild( const rp::string& name )
{
	// ������� ��������, � ��� �� ��� � ����� ��������
	rp::RPXMLNode* found = find( name );
	if ( found ) return found;
	// � ������ �������� �� �����, ������ � xml-���������
	// ������� ������� �������
	MSXML2::IXMLDOMNode* ichild = getFirstINode();
	while ( true ) {
		// �������� ���
		if ( name == RPXMLNode::getNameByINode( ichild ) ) {
			RPXMLNode* child = new RPXMLNode( ichild );
			child->node_name = name;
			childs.push_back( child );
			return child;
		}
		// �������� � ���������� �������
		MSXML2::IXMLDOMNode* ichild_next = NULL;
		if ( ichild->get_nextSibling( &ichild_next ) != S_OK ) {
			return NULL;
		}
		ichild = ichild_next;
	}
	return NULL;
}

rp::RPXMLNode* RPXMLNode::nextChild( RPXMLNode* after )
{
	MSXML2::IXMLDOMNode* ichild = NULL;
	if ( !after ) {
		ichild = getFirstINode();
	} else {
		if ( after->inode->get_nextSibling( &ichild ) != S_OK ) {
			return NULL;
		}
	}
	if ( ichild ) {
		RPXMLNode* child = new RPXMLNode( ichild );
		child->node_name = RPXMLNode::getNameByINode( ichild );
		childs.push_back( child );
		return child;
	} else {
		return NULL;
	}
}

rp::string RPXMLNode::getAttribute( const rp::string& attribute )
{
	MSXML2::IXMLDOMNamedNodeMap* imap = NULL;
	if ( inode->get_attributes( &imap ) != S_OK ) {
		if ( imap ) imap->Release();
		throw rp::RPXMLException( rp::format("������ ��������� ������ ��������� ������� %s", node_name.c_str()) );
	}
	MSXML2::IXMLDOMNode* iattr = NULL;
	_bstr_t bstr( attribute.c_str() );
	if ( imap->getNamedItem( bstr.copy(), &iattr ) != S_OK ) {
//	if ( imap->getNamedItem( bstr.GetBSTR(), &iattr ) != S_OK ) {
		if ( imap ) imap->Release();
		if ( iattr ) iattr->Release();
		throw rp::RPXMLException( rp::format("�� ������ ������� %s ������� %s", attribute.c_str(), node_name.c_str()) );
	}
	VARIANT value;
	if ( iattr->get_nodeValue( &value ) != S_OK ) {
		if ( imap ) imap->Release();
		if ( iattr ) iattr->Release();
		throw rp::RPXMLException( rp::format("������ ��������� �������� �������� %s ������� %s", attribute.c_str(), node_name.c_str()) );
	}
	if ( imap ) imap->Release();
	if ( iattr ) iattr->Release();
	return static_cast<char*>(_bstr_t(value));
}

void RPXMLNode::insertChild( RPXMLNode* child )
{
	MSXML2::IXMLDOMNode* node_2 = NULL;
	HRESULT hr = inode->appendChild( child->inode, &node_2 ) != S_OK;
	if ( hr != S_OK ) {
		if ( node_2 ) node_2->Release();
		throw rp::RPXMLException( rp::format("������ ���������� ������� %s � %s", child->node_name.c_str(), node_name.c_str()) );
	}
}

rp::RPXMLNode* RPXMLNode::makeChild( const rp::string& name )
{
	MSXML2::IXMLDOMElement* elem = NULL;
	if ( xml->idocument->createElement( _bstr_t(name.c_str()), &elem ) != S_OK ) {
		if ( elem ) elem->Release();
		throw rp::RPXMLException( rp::format("������ �������� ������� %s", name.c_str()) );
	}
	RPXMLNode* child = new RPXMLNode( elem );
	child->node_name = name;
	childs.push_back( child );
	insertChild( child );
	return child;
}

void RPXMLNode::insertAttribute( const rp::string& name, const rp::string& value )
{
	MSXML2::IXMLDOMAttribute* iattr = NULL;
	if ( xml->idocument->createAttribute( _bstr_t(name.c_str()), &iattr ) != S_OK ) {
		if ( iattr ) iattr->Release();
		throw rp::RPXMLException( rp::format("������ �������� �������� %s ������� %s", name.c_str(), node_name.c_str()) );
	}
	if ( iattr->put_value( _variant_t(value.c_str()) ) != S_OK ) {
		if ( iattr ) iattr->Release();
		throw rp::RPXMLException( rp::format("������ ���������� �������� %s �������� %s ������� %s", value.c_str(), name.c_str(), node_name.c_str()) );
	}
	MSXML2::IXMLDOMAttribute* iattr_2 = NULL;
	if ( static_cast<MSXML2::IXMLDOMElement*>(inode)->setAttributeNode( iattr, &iattr_2 ) != S_OK ) {
		if ( iattr   ) iattr->Release();
		if ( iattr_2 ) iattr_2->Release();
		throw rp::RPXMLException( rp::format("������ ���������� �������� %s ������� %s", name.c_str(), node_name.c_str()) );
	}
	iattrs.push_back( iattr );
}

void RPXMLNode::insertAttribute( const rp::string& name, int value )
{
	insertAttribute( name, rp::string::fromint(value) );
}

void RPXMLNode::insertAttribute( const rp::string& name, double value )
{
	insertAttribute( name, rp::string::fromdouble(value) );
}

// ----------------------------------------------------------------------------
// ---------- RPXML
// ----------------------------------------------------------------------------
RPXML* xml = NULL;

RPXML::RPXML():
	idocument( NULL )
{
    if ( ::CoCreateInstance( __uuidof(MSXML2::DOMDocument30), NULL, CLSCTX_INPROC_SERVER, __uuidof(MSXML2::IXMLDOMDocument), reinterpret_cast<void**>(&idocument) ) != S_OK ) {
		throw rp::RPXMLException( "������ �������� xml-���������" );
    }
	xml = this;
    document.inode = idocument;
	idocument->put_async( VARIANT_FALSE );
	idocument->put_validateOnParse( VARIANT_FALSE );
	idocument->put_resolveExternals( VARIANT_FALSE );
	idocument->put_preserveWhiteSpace( VARIANT_FALSE );
//	insertHeader( "RDOProcess", "version 1.2" );
}

RPXML::~RPXML()
{
	xml = NULL;
}

RPXMLNode* RPXML::open( const rp::string& fname )
{
	VARIANT_BOOL status;
	if ( idocument->load( _variant_t(fname.c_str()), &status ) != S_OK ) {
		throw rp::RPXMLException( rp::format("������ �������� ����� %s", fname.c_str()) );
	}
	RPXMLNode* project_node = document.findFirstChild( "project" );
	if ( project_node ) {
		return project_node;
	} else {
		throw rp::RPXMLException( "�� ������� �������� �������" );
	}
	return NULL;
}

void RPXML::save( const rp::string& fname )
{
	if ( idocument->save( _variant_t(fname.c_str()) ) != S_OK ) {
		throw rp::RPXMLException( rp::format("������ ������ ����� %s", fname.c_str()) );
	}
}

void RPXML::insertHeader( const rp::string& attribute, const rp::string& value )
{
	MSXML2::IXMLDOMProcessingInstruction* pi = NULL;
	if ( idocument->createProcessingInstruction( _bstr_t(attribute.c_str()), _bstr_t(value.c_str()), &pi ) != S_OK ) {
		if ( pi ) pi->Release();
		throw rp::RPXMLException( rp::format("������ ���������� ��������� %s", attribute.c_str()) );
	}
	RPXMLNode node( pi );
	document.insertChild( &node );
}

} // namespace rp

//====== Copyright � Sandern Corporation, All rights reserved. ===========//
//
// Purpose: 
//
// $Workfile:     $
// $Date:         $
//
//-----------------------------------------------------------------------------
// $Log: $
//
// $NoKeywords: $
//=============================================================================//
#if !defined( SRC_PYTHON_SERVER_CLASS_H )
#define SRC_PYTHON_SERVER_CLASS_H
#ifdef _WIN32
#pragma once
#endif

#ifndef ENABLE_PYTHON
	#define IMPLEMENT_PYCLIENTCLASS_SYSTEM( name, network_name )
	#define DECLARE_PYSERVERCLASS( name )
	#define IMPLEMENT_PYSERVERCLASS( name, networkType )
	#define DECLARE_PYCLASS( name )
#else

#include "server_class.h"
#include "dt_send.h"
#include "src_python_class_shared.h"

extern boost::python::object _entities;

class NetworkedClass;
class CBasePlayer;

#define IMPLEMENT_PYSERVERCLASS_SYSTEM( name, network_name ) PyServerClass name(#network_name);	

class PyServerClass : public ServerClass
{
public:
	PyServerClass(char *pNetworkName);

	void SetupServerClass( int iType );

public:
	SendProp *m_pSendProps;
	PyServerClass *m_pPyNext;
	bool m_bFree;
	int m_iType;
	NetworkedClass *m_pNetworkedClass;
};

// NetworkedClass is exposed to python and deals with getting a server/client class and cleaning up
class NetworkedClass
{
public:
	NetworkedClass( const char *pNetworkName, boost::python::object cls_type );
	~NetworkedClass();

	void SetupServerClass();

public:
	boost::python::object m_PyClass;
	const char *m_pNetworkName;

	PyServerClass *m_pServerClass;
};

void FullClientUpdatePyNetworkCls( CBasePlayer *pPlayer );
void FullClientUpdatePyNetworkClsByFilter( IRecipientFilter &filter );
void FullClientUpdatePyNetworkClsByEdict( edict_t *pEdict );

typedef struct EntityInfoOnHold {
	CBaseEntity *ent;
	edict_t *edict;
} EntityInfoOnHold;

void SetupNetworkTables();
void SetupNetworkTablesOnHold();
void AddSetupNetworkTablesOnHoldEnt( EntityInfoOnHold info );
bool SetupNetworkTablesRelease();
void PyResetAllNetworkTables();

// Implement a python class. For python/c++ handle conversion
#define DECLARE_PYCLASS( name )																		\
	public:																							\
	boost::python::object CreatePyHandle( void ) const												\
	{																								\
		return CreatePyHandleHelper(this, #name "HANDLE");											\
	}

// Implement a networkable python class. Used to determine the right recv/send tables
#define DECLARE_PYSERVERCLASS( name )																\
	DECLARE_PYCLASS( name )																			\
	public:																							\
	static int GetPyNetworkType();

#define IMPLEMENT_PYSERVERCLASS( name, networkType )												\
	int name::GetPyNetworkType() { return networkType; }

#endif // ENABLE_PYTHON

#endif // SRC_PYTHON_SERVER_CLASS_H
#ifndef _INCLUDED_WARS_EXTENSION_H
#define _INCLUDED_WARS_EXTENSION_H
#ifdef _WIN32
#pragma once
#endif

#include "wars/iwars_extension.h"
#include "tier3/tier3dm.h"

#include "steam/steam_api.h"

class IEngineVGui;

class CWarsExtension : public CTier3AppSystem< IWarsExtension > 
{
	typedef CTier3AppSystem< IWarsExtension > BaseClass;
public:
	CWarsExtension() : m_bPaused(false) {}
	// Methods of IAppSystem
	virtual bool Connect( CreateInterfaceFn factory );
	virtual void Disconnect();
	virtual void *QueryInterface( const char *pInterfaceName );
	virtual InitReturnVal_t Init();
	
	// IWarsExtension
	// Wars Editor function implementations
	void ClearData();
	virtual void QueueClientCommand( KeyValues *pCommand );
	virtual void QueueServerCommand( KeyValues *pCommand );
	virtual KeyValues *PopClientCommandQueue();
	virtual KeyValues *PopServerCommandQueue();

	// Receiving Steam P2P messages
	virtual void ReceiveSteamP2PMessages( ISteamNetworking *pSteamNetworking );
	virtual WarsMessageData_t *ServerMessageHead();
	virtual bool NextServerMessage();
	virtual WarsMessageData_t *InsertServerMessage();
	virtual WarsMessageData_t *ClientMessageHead();
	virtual bool NextClientMessage();
	virtual WarsMessageData_t *InsertClientMessage();

	// Hack to tell client we are paused (engine->IsPaused is broken...)
	virtual void SetPaused( bool bPaused ) { m_bPaused = bPaused; }
	virtual bool IsPaused() { return m_bPaused; }

private:
	// Wars Editor commands
	CUtlVector<KeyValues *> m_hQueuedClientCommands;
	CUtlVector<KeyValues *> m_hQueuedServerCommands;

	// Steam P2P messages
	CUtlVector<WarsMessageData_t> m_hQueuedClientP2PMessages;
	CUtlVector<WarsMessageData_t> m_hQueuedServerP2PMessages;

	// Paused?
	bool m_bPaused;
};

#endif // _INCLUDED_WARS_EXTENSION_H

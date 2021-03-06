//====== Copyright � Sandern Corporation, All rights reserved. ===========//
//
// Purpose: MiniMap.h: interface for the CMiniMap class.
//
// $NoKeywords: $
//=============================================================================//

#if !defined HL2WARS_BASEMINIMAP_H
#define HL2WARS_BASEMINIMAP_H
#ifdef _WIN32
#pragma once
#endif

#include <vgui_controls/Panel.h>
#include "GameEventListener.h"

struct EntityObject
{
	EntityObject( CBaseEntity *pEnt, CHudTexture *pIcon, int iHalfWide = 1, int iHalfTall = 1, bool bTestShowInFOW = true, bool bFlashOnAttacked = false, int iLayer = 0 )
	{
		m_hEntity = pEnt;
		m_pIcon = pIcon;
		m_iHalfWide = iHalfWide;
		m_iHalfTall = iHalfTall;
		m_bTestShowInFOW = bTestShowInFOW;
		m_bFlashOnAttacked = bFlashOnAttacked;
		m_fFlashTimeOut = -1;
		m_iLayer = iLayer;
	}

	EHANDLE m_hEntity;
	CHudTexture *m_pIcon;
	int m_iHalfWide;
	int m_iHalfTall;
	float m_fFlashTimeOut;
	bool m_bTestShowInFOW;
	bool m_bFlashOnAttacked; // Units only
	int m_iLayer;
};

class CBaseMinimap :  public vgui::Panel, public CGameEventListener
{
	DECLARE_CLASS_SIMPLE( CBaseMinimap, vgui::Panel );

public:	
	// Init
	CBaseMinimap(Panel *parent, const char *panelName, bool registerlisteners=true);

	// FireEvent is called by EventManager if event just occured
	// KeyValue memory will be freed by manager if not needed anymore
	virtual void FireGameEvent( IGameEvent *event );

	// General
	virtual void			SetMap(const char * map);
	void					InsertEntityObject( CBaseEntity *ent, CHudTexture *icon=NULL, int iHalfWide = 1, int iHalfTall = 1, 
												bool testshowinfow = true, bool bFlashOnAttacked = false, int layer = 0 );
	bool					RemoveEntityObject( CBaseEntity *ent );
	void					RemoveAllEntityObjects( bool unitsonly = false );	
	void					FlashEntity( CBaseEntity *ent, float duration );

	// Draw
	void					DrawEntityObjects();
	void					DrawPlayerView();

	// Convert
	float					GetViewAngle( void ); // The angle that determines the viewport twist from map texture to panel drawing.
	Vector2D				WorldToMap( const Vector &worldpos );
	Vector2D				MapToPanel( const Vector2D &mappos );
	Vector					MapToWorld( const Vector2D &offset );
	Vector2D				PanelToMap( const Vector2D &panelpos );

public:		// Public settings for python
	Vector		maporigin;
	float		mapscale;
	bool		rotatemap;	

	float		zoom;
	float		fullzoom;
	Vector2D	vieworigin;
	Vector2D	mapcenter;

	float		baserotation;
	float		viewangle;
	bool		followangle;

	static int	OVERVIEW_MAP_SIZE;

	Color		playerviewcolor;

private:
	CUtlVector<EntityObject> m_EntityObjects;
};

#endif // HL2WARS_BASEMINIMAP_H
//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//

#include "cbase.h"

#include "decals.h"
#include "effect_dispatch_data.h"
#include "model_types.h"
#include "gamestringpool.h"
#include "ammodef.h"
#include "takedamageinfo.h"
#include "shot_manipulator.h"
#include "ai_debug_shared.h"
#include "mapentities_shared.h"
#include "debugoverlay_shared.h"
#include "coordsize.h"
#include "AI_Criteria.h"

#ifdef CLIENT_DLL
	#include "c_te_effect_dispatch.h"
#else
	#include "te_effect_dispatch.h"
	#include "soundent.h"
	#include "iservervehicle.h"
	#include "player_pickup.h"
	#include "waterbullet.h"
	#include "func_break.h"

	#include "GameStats.h"
	#include "globalstate.h"
	#include "world.h"

#endif

#ifdef HL2_EPISODIC
ConVar hl2_episodic( "hl2_episodic", "1", FCVAR_REPLICATED );
#else
ConVar hl2_episodic( "hl2_episodic", "0", FCVAR_REPLICATED );
#endif//HL2_EPISODIC



#include "rumble_shared.h"

#include "fowmgr.h"

#ifdef ENABLE_PYTHON
	#include "srcpy.h"
#endif // ENABLE_PYTHON

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

#ifdef GAME_DLL
	ConVar ent_debugkeys( "ent_debugkeys", "" );
	extern bool ParseKeyvalue( void *pObject, typedescription_t *pFields, int iNumFields, const char *szKeyName, const char *szValue );
	extern bool ExtractKeyvalue( void *pObject, typedescription_t *pFields, int iNumFields, const char *szKeyName, char *szValue, int iMaxLen );
#endif

bool CBaseEntity::m_bAllowPrecache = false;
bool CBaseEntity::sm_bAccurateTriggerBboxChecks = true;	// set to false for legacy behavior in ep1


ConVar	ai_shot_bias_min( "ai_shot_bias_min", "-1.0", FCVAR_REPLICATED );
ConVar	ai_shot_bias_max( "ai_shot_bias_max", "1.0", FCVAR_REPLICATED );
ConVar	ai_debug_shoot_positions( "ai_debug_shoot_positions", "0", FCVAR_REPLICATED | FCVAR_CHEAT );

DEFINE_LOGGING_CHANNEL_NO_TAGS( LOG_DEVELOPER_VERBOSE, "DeveloperVerbose" );

//-----------------------------------------------------------------------------
// Purpose: Spawn some blood particles
//-----------------------------------------------------------------------------
void SpawnBlood(Vector vecSpot, const Vector &vecDir, int bloodColor, float flDamage)
{
	UTIL_BloodDrips( vecSpot, vecDir, bloodColor, (int)flDamage );
}

#if !defined( NO_ENTITY_PREDICTION )
//-----------------------------------------------------------------------------
// The player drives simulation of this entity
//-----------------------------------------------------------------------------
void CBaseEntity::SetPlayerSimulated( CBasePlayer *pOwner )
{
	m_bIsPlayerSimulated = true;
	pOwner->AddToPlayerSimulationList( this );
	m_hPlayerSimulationOwner = pOwner;
}

void CBaseEntity::UnsetPlayerSimulated( void )
{
	if ( m_hPlayerSimulationOwner != NULL )
	{
		m_hPlayerSimulationOwner->RemoveFromPlayerSimulationList( this );
	}
	m_hPlayerSimulationOwner = NULL;
	m_bIsPlayerSimulated = false;
}
#endif

// position of eyes
Vector CBaseEntity::EyePosition( void )
{ 
	return GetAbsOrigin() + m_vecViewOffset; 
}

const QAngle &CBaseEntity::EyeAngles( void )
{
	return GetAbsAngles();
}

const QAngle &CBaseEntity::LocalEyeAngles( void )
{
	return GetLocalAngles();
}

// position of ears
Vector CBaseEntity::EarPosition( void )
{ 
	return EyePosition( ); 
}

void CBaseEntity::SetViewOffset( const Vector& v ) 
{ 
	m_vecViewOffset = v; 
}

const Vector& CBaseEntity::GetViewOffset() const 
{ 
	return m_vecViewOffset; 
}


//-----------------------------------------------------------------------------
// center point of entity
//-----------------------------------------------------------------------------
const Vector &CBaseEntity::WorldSpaceCenter( ) const 
{
	return CollisionProp()->WorldSpaceCenter();
}

#if !defined( CLIENT_DLL )
#define CHANGE_FLAGS(flags,newFlags) { unsigned int old = flags; flags = (newFlags); gEntList.ReportEntityFlagsChanged( this, old, flags ); }
#else
#define CHANGE_FLAGS(flags,newFlags) (flags = (newFlags))
#endif

void CBaseEntity::AddFlag( int flags )
{
	CHANGE_FLAGS( m_fFlags, m_fFlags | flags );
}

void CBaseEntity::RemoveFlag( int flagsToRemove )
{
	CHANGE_FLAGS( m_fFlags, m_fFlags & ~flagsToRemove );
}

void CBaseEntity::ClearFlags( void )
{
	CHANGE_FLAGS( m_fFlags, 0 );
}

void CBaseEntity::ToggleFlag( int flagToToggle )
{
	CHANGE_FLAGS( m_fFlags, m_fFlags ^ flagToToggle );
}

void CBaseEntity::SetEffects( int nEffects )
{
	if ( nEffects != m_fEffects )
	{
#if !defined( CLIENT_DLL )
#ifdef HL2_EPISODIC
		// Hack for now, to avoid player emitting radius with his flashlight
		if ( !IsPlayer() )
		{
			if ( (nEffects & (EF_BRIGHTLIGHT|EF_DIMLIGHT)) && !(m_fEffects & (EF_BRIGHTLIGHT|EF_DIMLIGHT)) )
			{
				AddEntityToDarknessCheck( this );
			}
			else if ( !(nEffects & (EF_BRIGHTLIGHT|EF_DIMLIGHT)) && (m_fEffects & (EF_BRIGHTLIGHT|EF_DIMLIGHT)) )
			{
				RemoveEntityFromDarknessCheck( this );
			}
		}
#endif // HL2_EPISODIC
#endif // !CLIENT_DLL

		m_fEffects = nEffects;

#if !defined( CLIENT_DLL )
		if ( nEffects & ( EF_NOINTERP ) )
		{
			gEntList.AddPostClientMessageEntity( this );
		}
#endif

		if ( ( nEffects & EF_NOINTERP ) && IsPlayer() )
		{
			((CBasePlayer *)this)->IncrementEFNoInterpParity();
		}

#ifndef CLIENT_DLL
		DispatchUpdateTransmitState();
#else
		UpdateVisibility();
#endif
	}
}

void CBaseEntity::AddEffects( int nEffects ) 
{ 
#if !defined( CLIENT_DLL )
#ifdef HL2_EPISODIC
	if ( (nEffects & (EF_BRIGHTLIGHT|EF_DIMLIGHT)) && !(m_fEffects & (EF_BRIGHTLIGHT|EF_DIMLIGHT)) )
	{
		// Hack for now, to avoid player emitting radius with his flashlight
		if ( !IsPlayer() )
		{
			AddEntityToDarknessCheck( this );
		}
	}
#endif // HL2_EPISODIC
#endif // !CLIENT_DLL

	m_fEffects |= nEffects; 
#if !defined( CLIENT_DLL )
	if ( nEffects & ( EF_NOINTERP ) )
	{
		gEntList.AddPostClientMessageEntity( this );
	}
#else
	if ( m_fEffects & (EF_DIMLIGHT|EF_DIMLIGHT) )
	{
		AddToEntityList(ENTITY_LIST_PRERENDER);
	}
#endif


	if ( nEffects & EF_NODRAW)
	{
#ifndef CLIENT_DLL
		DispatchUpdateTransmitState();
#else
		UpdateVisibility();
#endif
	}
}

void CBaseEntity::SetBlocksLOS( bool bBlocksLOS )
{
	if ( bBlocksLOS )
	{
		RemoveEFlags( EFL_DONTBLOCKLOS );
	}
	else
	{
		AddEFlags( EFL_DONTBLOCKLOS );
	}
}

bool CBaseEntity::BlocksLOS( void ) 
{ 
	return !IsEFlagSet(EFL_DONTBLOCKLOS); 
}

void CBaseEntity::SetAIWalkable( bool bBlocksLOS )
{
	if ( bBlocksLOS )
	{
		RemoveEFlags( EFL_DONTWALKON );
	}
	else
	{
		AddEFlags( EFL_DONTWALKON );
	}
}

bool CBaseEntity::IsAIWalkable( void ) 
{ 
	return !IsEFlagSet(EFL_DONTWALKON);
}


//-----------------------------------------------------------------------------
// Purpose: Handles keys and outputs from the BSP.
// Input  : mapData - Text block of keys and values from the BSP.
//-----------------------------------------------------------------------------
void CBaseEntity::ParseMapData( CEntityMapData *mapData )
{
	char keyName[MAPKEY_MAXLENGTH];
	char value[MAPKEY_MAXLENGTH];

	#ifdef _DEBUG
	#ifdef GAME_DLL
	ValidateDataDescription();
	#endif // GAME_DLL
	#endif // _DEBUG

	// loop through all keys in the data block and pass the info back into the object
	if ( mapData->GetFirstKey(keyName, value) )
	{
		do 
		{
			KeyValue( keyName, value );
		} 
		while ( mapData->GetNextKey(keyName, value) );
	}

	OnParseMapDataFinished();
}

//-----------------------------------------------------------------------------
// Parse data from a map file
//-----------------------------------------------------------------------------
bool CBaseEntity::KeyValue( const char *szKeyName, const char *szValue ) 
{
	//!! temp hack, until worldcraft is fixed
	// strip the # tokens from (duplicate) key names
	char *s = (char *)strchr( szKeyName, '#' );
	if ( s )
	{
		*s = '\0';
	}

	if ( FStrEq( szKeyName, "rendercolor" ) || FStrEq( szKeyName, "rendercolor32" ))
	{
		color32 tmp;
		V_StringToColor32( &tmp, szValue );
		SetRenderColor( tmp.r, tmp.g, tmp.b );
		SetRenderAlpha( tmp.a );
		return true;
	}

	if ( FStrEq( szKeyName, "renderamt" ) )
	{
		SetRenderAlpha( Q_atoi( szValue ) );
		return true;
	}

	if ( FStrEq( szKeyName, "disableshadows" ))
	{
		int val = atoi( szValue );
		if (val)
		{
			AddEffects( EF_NOSHADOW );
		}
		return true;
	}

	if ( FStrEq( szKeyName, "mins" ))
	{
		Vector mins;
		UTIL_StringToVector( mins.Base(), szValue );
		CollisionProp()->SetCollisionBounds( mins, CollisionProp()->OBBMaxs() );
		return true;
	}

	if ( FStrEq( szKeyName, "maxs" ))
	{
		Vector maxs;
		UTIL_StringToVector( maxs.Base(), szValue );
		CollisionProp()->SetCollisionBounds( CollisionProp()->OBBMins(), maxs );
		return true;
	}

	if ( FStrEq( szKeyName, "disablereceiveshadows" ))
	{
		int val = atoi( szValue );
		if (val)
		{
			AddEffects( EF_NORECEIVESHADOW );
		}
		return true;
	}

	if ( FStrEq( szKeyName, "nodamageforces" ))
	{
		int val = atoi( szValue );
		if (val)
		{
			AddEFlags( EFL_NO_DAMAGE_FORCES );
		}
		return true;
	}

	// Fix up single angles
	if( FStrEq( szKeyName, "angle" ) )
	{
		static char szBuf[64];

		float y = atof( szValue );
		if (y >= 0)
		{
			Q_snprintf( szBuf,sizeof(szBuf), "%f %f %f", GetLocalAngles()[0], y, GetLocalAngles()[2] );
		}
		else if ((int)y == -1)
		{
			Q_strncpy( szBuf, "-90 0 0", sizeof(szBuf) );
		}
		else
		{
			Q_strncpy( szBuf, "90 0 0", sizeof(szBuf) );
		}

		// Do this so inherited classes looking for 'angles' don't have to bother with 'angle'
		return KeyValue( szKeyName, szBuf );
	}

	// NOTE: Have to do these separate because they set two values instead of one
	if( FStrEq( szKeyName, "angles" ) )
	{
		QAngle angles;
		UTIL_StringToVector( angles.Base(), szValue );

		// If you're hitting this assert, it's probably because you're
		// calling SetLocalAngles from within a KeyValues method.. use SetAbsAngles instead!
		Assert( (GetMoveParent() == NULL) && !IsEFlagSet( EFL_DIRTY_ABSTRANSFORM ) );
		SetAbsAngles( angles );
		return true;
	}

	if( FStrEq( szKeyName, "origin" ) )
	{
		Vector vecOrigin;
		UTIL_StringToVector( vecOrigin.Base(), szValue );

		// If you're hitting this assert, it's probably because you're
		// calling SetLocalOrigin from within a KeyValues method.. use SetAbsOrigin instead!
		Assert( (GetMoveParent() == NULL) && !IsEFlagSet( EFL_DIRTY_ABSTRANSFORM ) );
		SetAbsOrigin( vecOrigin );
		return true;
	}

#ifdef GAME_DLL	
	
	if ( FStrEq( szKeyName, "targetname" ) )
	{
		m_iName = AllocPooledString( szValue );
		return true;
	}

#ifdef HL2WARS_DLL
	if ( FStrEq( szKeyName, "ownernumber" ) )
	{
		SetOwnerNumber( atoi(szValue) );
		return true;
	}
#endif // HL2WARS_DLL

	// loop through the data description, and try and place the keys in
	if ( !*ent_debugkeys.GetString() )
	{
		for ( datamap_t *dmap = GetDataDescMap(); dmap != NULL; dmap = dmap->baseMap )
		{
			if ( ::ParseKeyvalue(this, dmap->dataDesc, dmap->dataNumFields, szKeyName, szValue) )
				return true;
		}
	}
	else
	{
		// debug version - can be used to see what keys have been parsed in
		bool printKeyHits = false;
		const char *debugName = "";

		if ( *ent_debugkeys.GetString() && !Q_stricmp(ent_debugkeys.GetString(), STRING(m_iClassname)) )
		{
			// Msg( "-- found entity of type %s\n", STRING(m_iClassname) );
			printKeyHits = true;
			debugName = STRING(m_iClassname);
		}

		// loop through the data description, and try and place the keys in
		for ( datamap_t *dmap = GetDataDescMap(); dmap != NULL; dmap = dmap->baseMap )
		{
			if ( !printKeyHits && *ent_debugkeys.GetString() && !Q_stricmp(dmap->dataClassName, ent_debugkeys.GetString()) )
			{
				// Msg( "-- found class of type %s\n", dmap->dataClassName );
				printKeyHits = true;
				debugName = dmap->dataClassName;
			}

			if ( ::ParseKeyvalue(this, dmap->dataDesc, dmap->dataNumFields, szKeyName, szValue) )
			{
				if ( printKeyHits )
					Msg( "(%s) key: %-16s value: %s\n", debugName, szKeyName, szValue );
				
				return true;
			}
		}

		if ( printKeyHits )
			Msg( "!! (%s) key not handled: \"%s\" \"%s\"\n", STRING(m_iClassname), szKeyName, szValue );
	}
#else

	// HACK: Read dxlevels for client-side entities
	if ( FStrEq( szKeyName, "mincpulevel" ))
	{
		m_nMinCPULevel = atoi( szValue );
		return true;
	}
	if ( FStrEq( szKeyName, "maxcpulevel" ))
	{
		m_nMaxCPULevel = atoi( szValue );
		return true;
	}
	if ( FStrEq( szKeyName, "mingpulevel" ))
	{
		m_nMinGPULevel = atoi( szValue );
		return true;
	}
	if ( FStrEq( szKeyName, "maxgpulevel" ))
	{
		m_nMaxGPULevel = atoi( szValue );
		return true;
	}

#endif
// =======================================
// PySource Additions
// =======================================
#ifdef ENABLE_PYTHON
	// Check Python keyvalues map
	if( m_pyInstance.ptr() != Py_None )
	{
		boost::python::object keyvaluemap;
		try
		{
			keyvaluemap = m_pyInstance.attr("keyvaluemap");
		} 
		catch( boost::python::error_already_set & )
		{
			Warning("Python entity has no keyvaluesmap!\n");
			PyErr_Clear();
		}

		try
		{
			boost::python::object field = keyvaluemap.attr("get")(szKeyName, boost::python::object());
			if( field.ptr() != Py_None )
			{
				field.attr("Set")(m_pyInstance, szValue);
				return true;
			}
		} 
		catch( boost::python::error_already_set & )
		{
			Warning("Python entity has an invalid keyvalues map!\n");
			PyErr_Print();
		}
	}
#endif // ENABLE_PYTHON
// =======================================
// END PySource Additions
// =======================================

	// key hasn't been handled
	return false;
}

bool CBaseEntity::KeyValue( const char *szKeyName, float flValue ) 
{
	char	string[256];

	Q_snprintf(string,sizeof(string), "%f", flValue );

	return KeyValue( szKeyName, string );
}

bool CBaseEntity::KeyValue( const char *szKeyName, int nValue ) 
{
	char	string[256];

	Q_snprintf(string,sizeof(string), "%d", nValue );

	return KeyValue( szKeyName, string );
}

bool CBaseEntity::KeyValue( const char *szKeyName, const Vector &vecValue ) 
{
	char	string[256];

	Q_snprintf(string,sizeof(string), "%f %f %f", vecValue.x, vecValue.y, vecValue.z );

	return KeyValue( szKeyName, string );
}

//-----------------------------------------------------------------------------
// Purpose: 
// Input  :
// Output :
//-----------------------------------------------------------------------------

bool CBaseEntity::GetKeyValue( const char *szKeyName, char *szValue, int iMaxLen )
{
	if ( FStrEq( szKeyName, "rendercolor" ) || FStrEq( szKeyName, "rendercolor32" ))
	{
		color24 tmp = GetRenderColor();
		unsigned char a = GetRenderAlpha();
		Q_snprintf( szValue, iMaxLen, "%d %d %d %d", tmp.r, tmp.g, tmp.b, a );
		return true;
	}
	
	if ( FStrEq( szKeyName, "renderamt" ) )
	{
		unsigned char a = GetRenderAlpha();
		Q_snprintf( szValue, iMaxLen, "%d", a );
		return true;
	}

	if ( FStrEq( szKeyName, "disableshadows" ))
	{
		Q_snprintf( szValue, iMaxLen, "%d", IsEffectActive( EF_NOSHADOW ) );
		return true;
	}

	if ( FStrEq( szKeyName, "mins" ))
	{
		Assert( 0 );
		return false;
	}

	if ( FStrEq( szKeyName, "maxs" ))
	{
		Assert( 0 );
		return false;
	}

	if ( FStrEq( szKeyName, "disablereceiveshadows" ))
	{
		Q_snprintf( szValue, iMaxLen, "%d", IsEffectActive( EF_NORECEIVESHADOW ) );
		return true;
	}

	if ( FStrEq( szKeyName, "nodamageforces" ))
	{
		Q_snprintf( szValue, iMaxLen, "%d", IsEffectActive( EFL_NO_DAMAGE_FORCES ) );
		return true;
	}

	// Fix up single angles
	if( FStrEq( szKeyName, "angle" ) )
	{
		return false;
	}

	// NOTE: Have to do these separate because they set two values instead of one
	if( FStrEq( szKeyName, "angles" ) )
	{
		QAngle angles = GetAbsAngles();

		Q_snprintf( szValue, iMaxLen, "%f %f %f", angles.x, angles.y, angles.z );
		return true;
	}

	if( FStrEq( szKeyName, "origin" ) )
	{
		Vector vecOrigin = GetAbsOrigin();
		Q_snprintf( szValue, iMaxLen, "%f %f %f", vecOrigin.x, vecOrigin.y, vecOrigin.z );
		return true;
	}

#ifdef GAME_DLL	
	
	if ( FStrEq( szKeyName, "targetname" ) )
	{
		Q_snprintf( szValue, iMaxLen, "%s", STRING( GetEntityName() ) );
		return true;
	}

	if ( FStrEq( szKeyName, "classname" ) )
	{
		Q_snprintf( szValue, iMaxLen, "%s", GetClassname() );
		return true;
	}

	for ( datamap_t *dmap = GetDataDescMap(); dmap != NULL; dmap = dmap->baseMap )
	{
		if ( ::ExtractKeyvalue( this, dmap->dataDesc, dmap->dataNumFields, szKeyName, szValue, iMaxLen ) )
			return true;
	}
#endif

	return false;
}

//-----------------------------------------------------------------------------
// Purpose: 
// Input  : collisionGroup - 
// Output : Returns true on success, false on failure.
//-----------------------------------------------------------------------------
bool CBaseEntity::ShouldCollide( int collisionGroup, int contentsMask ) const
{
	if ( m_CollisionGroup == COLLISION_GROUP_DEBRIS )
	{
		if ( ! (contentsMask & CONTENTS_DEBRIS) )
			return false;
	}
	return true;
}


//-----------------------------------------------------------------------------
// Purpose: 
// Input  : seed - 
//-----------------------------------------------------------------------------
void CBaseEntity::SetPredictionRandomSeed( const CUserCmd *cmd )
{
	if ( !cmd )
	{
		m_nPredictionRandomSeed = -1;
		return;
	}

	m_nPredictionRandomSeed = ( cmd->random_seed );
}


//------------------------------------------------------------------------------
// Purpose : Base implimentation for entity handling decals
//------------------------------------------------------------------------------
void CBaseEntity::DecalTrace( trace_t *pTrace, char const *decalName )
{
	int index = decalsystem->GetDecalIndexForName( decalName );
	if ( index < 0 )
		return;

	Assert( pTrace->m_pEnt );

	CBroadcastRecipientFilter filter;
	te->Decal( filter, 0.0, &pTrace->endpos, &pTrace->startpos,
		pTrace->GetEntityIndex(), pTrace->hitbox, index );
}

//-----------------------------------------------------------------------------
// Purpose: Base handling for impacts against entities
//-----------------------------------------------------------------------------
void CBaseEntity::ImpactTrace( trace_t *pTrace, int iDamageType, char *pCustomImpactName )
{
	VPROF( "CBaseEntity::ImpactTrace" );
	Assert( pTrace->m_pEnt );

	CBaseEntity *pEntity = pTrace->m_pEnt;
 
	// Build the impact data
	CEffectData data;
	data.m_vOrigin = pTrace->endpos;
	data.m_vStart = pTrace->startpos;
	data.m_nSurfaceProp = pTrace->surface.surfaceProps;
	if ( data.m_nSurfaceProp < 0 )
	{
		data.m_nSurfaceProp = 0;
	}
	data.m_nDamageType = iDamageType;
	data.m_nHitBox = pTrace->hitbox;
#ifdef CLIENT_DLL
	data.m_hEntity = ClientEntityList().EntIndexToHandle( pEntity->entindex() );
#else
	data.m_nEntIndex = pEntity->entindex();
#endif

	// Send it on its way
	if ( !pCustomImpactName )
	{
		DispatchEffect( "Impact", data );
	}
	else
	{
		DispatchEffect( pCustomImpactName, data );
	}
}

//-----------------------------------------------------------------------------
// Purpose: returns the damage decal to use, given a damage type
// Input  : bitsDamageType - the damage type
// Output : the index of the damage decal to use
//-----------------------------------------------------------------------------
char const *CBaseEntity::DamageDecal( int bitsDamageType, int gameMaterial )
{
	if ( m_nRenderMode == kRenderTransAlpha )
		return "";

	if ( m_nRenderMode != kRenderNormal && gameMaterial == 'G' )
		return "BulletProof";

	if ( bitsDamageType == DMG_SLASH )
		return "ManhackCut";

	// This will get translated at a lower layer based on game material
	return "Impact.Concrete";
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
int	CBaseEntity::GetIndexForThinkContext( const char *pszContext )
{
	for ( int i = 0; i < m_aThinkFunctions.Count(); i++ )
	{
		if ( !Q_strncmp( STRING( m_aThinkFunctions[i].m_iszContext ), pszContext, MAX_CONTEXT_LENGTH ) )
			return i;
	}

	return NO_THINK_CONTEXT;
}

//-----------------------------------------------------------------------------
// Purpose: Get a fresh think context for this entity
//-----------------------------------------------------------------------------
int CBaseEntity::RegisterThinkContext( const char *szContext )
{
	int iIndex = GetIndexForThinkContext( szContext );
	if ( iIndex != NO_THINK_CONTEXT )
		return iIndex;

	// Make a new think func
	thinkfunc_t sNewFunc;
#ifdef ENABLE_PYTHON
	Q_memset( &sNewFunc, 0, sizeof( sNewFunc ) - sizeof( bp::object ) );	//  m_pyThink is last in struct. DON'T SET TO NULL!
#else
	Q_memset( &sNewFunc, 0, sizeof( sNewFunc ) );
#endif // ENABLE_PYTHON
	sNewFunc.m_pfnThink = NULL;
	sNewFunc.m_nNextThinkTick = 0;
	sNewFunc.m_iszContext = AllocPooledString(szContext);

	// Insert it into our list
	return m_aThinkFunctions.AddToTail( sNewFunc );
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
BASEPTR	CBaseEntity::ThinkSet( BASEPTR func, float thinkTime, const char *szContext )
{
#if !defined( CLIENT_DLL )
#ifdef _DEBUG
#ifdef GNUC
	COMPILE_TIME_ASSERT( sizeof(func) == 8 );
#else
	COMPILE_TIME_ASSERT( sizeof(func) == 4 );
#endif
#endif
#endif

	// Old system?
	if ( !szContext )
	{
		m_pfnThink = func;
#ifdef ENABLE_PYTHON
		m_pyThink = boost::python::object();
#endif // ENABLE_PYTHON
#if !defined( CLIENT_DLL )
#ifdef _DEBUG
		FunctionCheck( *(reinterpret_cast<void **>(&m_pfnThink)), "BaseThinkFunc" ); 
#endif
#endif
		return m_pfnThink;
	}

	// Find the think function in our list, and if we couldn't find it, register it
	int iIndex = GetIndexForThinkContext( szContext );
	if ( iIndex == NO_THINK_CONTEXT )
	{
		iIndex = RegisterThinkContext( szContext );
	}

	m_aThinkFunctions[ iIndex ].m_pfnThink = func;
#ifdef ENABLE_PYTHON
	m_aThinkFunctions[ iIndex ].m_pyThink = boost::python::object();
#endif // ENABLE_PYTHON
#if !defined( CLIENT_DLL )
#ifdef _DEBUG
	FunctionCheck( *(reinterpret_cast<void **>(&m_aThinkFunctions[ iIndex ].m_pfnThink)), szContext ); 
#endif
#endif

	if ( thinkTime != 0 )
	{
		int thinkTick = ( thinkTime == TICK_NEVER_THINK ) ? TICK_NEVER_THINK : TIME_TO_TICKS( thinkTime );
		m_aThinkFunctions[ iIndex ].m_nNextThinkTick = thinkTick;
		CheckHasThinkFunction( thinkTick == TICK_NEVER_THINK ? false : true );
	}
	return func;
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CBaseEntity::SetNextThink( float thinkTime, const char *szContext )
{
	int thinkTick = ( thinkTime == TICK_NEVER_THINK ) ? TICK_NEVER_THINK : TIME_TO_TICKS( thinkTime );

	// Are we currently in a think function with a context?
	int iIndex = 0;
	if ( !szContext )
	{
#ifdef _DEBUG
		if ( m_iCurrentThinkContext != NO_THINK_CONTEXT )
		{
			Msg( "Warning: Setting base think function within think context %s\n", STRING(m_aThinkFunctions[m_iCurrentThinkContext].m_iszContext) );
		}
#endif

		// Old system
		m_nNextThinkTick = thinkTick;
		CheckHasThinkFunction( thinkTick == TICK_NEVER_THINK ? false : true );
		return;
	}
	else
	{
		// Find the think function in our list, and if we couldn't find it, register it
		iIndex = GetIndexForThinkContext( szContext );
		if ( iIndex == NO_THINK_CONTEXT )
		{
			iIndex = RegisterThinkContext( szContext );
		}
	}

	// Old system
	m_aThinkFunctions[ iIndex ].m_nNextThinkTick = thinkTick;
	CheckHasThinkFunction( thinkTick == TICK_NEVER_THINK ? false : true );
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
float CBaseEntity::GetNextThink( const char *szContext )
{
	// Are we currently in a think function with a context?
	int iIndex = 0;
	if ( !szContext )
	{
#ifdef _DEBUG
		if ( m_iCurrentThinkContext != NO_THINK_CONTEXT )
		{
			Msg( "Warning: Getting base nextthink time within think context %s\n", STRING(m_aThinkFunctions[m_iCurrentThinkContext].m_iszContext) );
		}
#endif

		if ( m_nNextThinkTick == TICK_NEVER_THINK )
			return TICK_NEVER_THINK;

		// Old system
		return TICK_INTERVAL * (m_nNextThinkTick );
	}
	else
	{
		// Find the think function in our list
		iIndex = GetIndexForThinkContext( szContext );
	}

	if ( iIndex == m_aThinkFunctions.InvalidIndex() )
		return TICK_NEVER_THINK;

	if ( m_aThinkFunctions[ iIndex ].m_nNextThinkTick == TICK_NEVER_THINK )
	{
		return TICK_NEVER_THINK;
	}
	return TICK_INTERVAL * (m_aThinkFunctions[ iIndex ].m_nNextThinkTick );
}

int	CBaseEntity::GetNextThinkTick( const char *szContext /*= NULL*/ )
{
	// Are we currently in a think function with a context?
	int iIndex = 0;
	if ( !szContext )
	{
#ifdef _DEBUG
		if ( m_iCurrentThinkContext != NO_THINK_CONTEXT )
		{
			Msg( "Warning: Getting base nextthink time within think context %s\n", STRING(m_aThinkFunctions[m_iCurrentThinkContext].m_iszContext) );
		}
#endif

		if ( m_nNextThinkTick == TICK_NEVER_THINK )
			return TICK_NEVER_THINK;

		// Old system
		return m_nNextThinkTick;
	}
	else
	{
		// Find the think function in our list
		iIndex = GetIndexForThinkContext( szContext );

		// Looking up an invalid think context!
		Assert( iIndex != -1 );
	}

	if ( ( iIndex == -1 ) || ( m_aThinkFunctions[ iIndex ].m_nNextThinkTick == TICK_NEVER_THINK ) )
	{
		return TICK_NEVER_THINK;
	}

	return m_aThinkFunctions[ iIndex ].m_nNextThinkTick;
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
float CBaseEntity::GetLastThink( const char *szContext )
{
	// Are we currently in a think function with a context?
	int iIndex = 0;
	if ( !szContext )
	{
#ifdef _DEBUG
		if ( m_iCurrentThinkContext != NO_THINK_CONTEXT )
		{
			Msg( "Warning: Getting base lastthink time within think context %s\n", STRING(m_aThinkFunctions[m_iCurrentThinkContext].m_iszContext) );
		}
#endif
		// Old system
		return m_nLastThinkTick * TICK_INTERVAL;
	}
	else
	{
		// Find the think function in our list
		iIndex = GetIndexForThinkContext( szContext );
	}

	return m_aThinkFunctions[ iIndex ].m_nLastThinkTick * TICK_INTERVAL;
}
	
int CBaseEntity::GetLastThinkTick( const char *szContext /*= NULL*/ )
{
	// Are we currently in a think function with a context?
	int iIndex = 0;
	if ( !szContext )
	{
#ifdef _DEBUG
		if ( m_iCurrentThinkContext != NO_THINK_CONTEXT )
		{
			Msg( "Warning: Getting base lastthink time within think context %s\n", STRING(m_aThinkFunctions[m_iCurrentThinkContext].m_iszContext) );
		}
#endif
		// Old system
		return m_nLastThinkTick;
	}
	else
	{
		// Find the think function in our list
		iIndex = GetIndexForThinkContext( szContext );
	}

	return m_aThinkFunctions[ iIndex ].m_nLastThinkTick;
}

bool CBaseEntity::WillThink()
{
	if ( m_nNextThinkTick > 0 )
		return true;

	for ( int i = 0; i < m_aThinkFunctions.Count(); i++ )
	{
		if ( m_aThinkFunctions[i].m_nNextThinkTick > 0 )
			return true;
	}

	return false;
}

#if !defined( CLIENT_DLL )

// Rebase all the current ticks in the think functions as delta ticks or from delta ticks to absolute ticks
void CBaseEntity::RebaseThinkTicks( bool bMakeDeltas )
{
	int nCurTick = TIME_TO_TICKS( gpGlobals->curtime );
	for ( int i = 0; i < m_aThinkFunctions.Count(); i++ )
	{
		if ( m_aThinkFunctions[i].m_nNextThinkTick > 0 )
		{
			if ( bMakeDeltas )
			{
				// Turn into a delta value
				m_aThinkFunctions[i].m_nNextThinkTick = m_aThinkFunctions[i].m_nNextThinkTick - nCurTick;
				m_aThinkFunctions[i].m_nLastThinkTick = m_aThinkFunctions[i].m_nLastThinkTick - nCurTick;
			}
			else
			{
				// Change a delta to an absolute tick value
				m_aThinkFunctions[i].m_nNextThinkTick = m_aThinkFunctions[i].m_nNextThinkTick + nCurTick;
				m_aThinkFunctions[i].m_nLastThinkTick = m_aThinkFunctions[i].m_nLastThinkTick + nCurTick;
			}
		}
	}
}

#endif // !CLIENT_DLL

// returns the first tick the entity will run any think function
// returns TICK_NEVER_THINK if no think functions are scheduled
int CBaseEntity::GetFirstThinkTick()
{
	int minTick = TICK_NEVER_THINK;
	if ( m_nNextThinkTick > 0 )
	{
		minTick = m_nNextThinkTick;
	}

	for ( int i = 0; i < m_aThinkFunctions.Count(); i++ )
	{
		int next = m_aThinkFunctions[i].m_nNextThinkTick;
		if ( next > 0 )
		{
			if ( next < minTick || minTick == TICK_NEVER_THINK )
			{
				minTick = next;
			}
		}
	}
	return minTick;
}

// NOTE: pass in the isThinking hint so we have to search the think functions less
void CBaseEntity::CheckHasThinkFunction( bool isThinking )
{
	if ( IsEFlagSet( EFL_NO_THINK_FUNCTION ) && isThinking )
	{
		RemoveEFlags( EFL_NO_THINK_FUNCTION );
	}
	else if ( !isThinking && !IsEFlagSet( EFL_NO_THINK_FUNCTION ) && !WillThink() )
	{
		AddEFlags( EFL_NO_THINK_FUNCTION );
	}
#if !defined( CLIENT_DLL )
	SimThink_EntityChanged( this );
#endif
}

bool CBaseEntity::WillSimulateGamePhysics()
{
	// players always simulate game physics
	if ( !IsPlayer() )
	{
		MoveType_t movetype = GetMoveType();
		
		if ( movetype == MOVETYPE_NONE || movetype == MOVETYPE_VPHYSICS )
			return false;

#if !defined( CLIENT_DLL )
		// MOVETYPE_PUSH not supported on the client
		if ( movetype == MOVETYPE_PUSH && GetMoveDoneTime() <= 0 )
			return false;
#endif
	}

	return true;
}

void CBaseEntity::CheckHasGamePhysicsSimulation()
{
	bool isSimulating = WillSimulateGamePhysics();
	if ( isSimulating != IsEFlagSet(EFL_NO_GAME_PHYSICS_SIMULATION) )
		return;
	if ( isSimulating )
	{
		RemoveEFlags( EFL_NO_GAME_PHYSICS_SIMULATION );
	}
	else
	{
		AddEFlags( EFL_NO_GAME_PHYSICS_SIMULATION );
	}
#if !defined( CLIENT_DLL )
	SimThink_EntityChanged( this );
#endif
}

//-----------------------------------------------------------------------------
// Sets/Gets the next think based on context index
//-----------------------------------------------------------------------------
void CBaseEntity::SetNextThink( int nContextIndex, float thinkTime )
{
	int thinkTick = ( thinkTime == TICK_NEVER_THINK ) ? TICK_NEVER_THINK : TIME_TO_TICKS( thinkTime );

	if (nContextIndex < 0)
	{
		SetNextThink( thinkTime );
	}
	else
	{
		m_aThinkFunctions[nContextIndex].m_nNextThinkTick = thinkTick;
	}
	CheckHasThinkFunction( thinkTick == TICK_NEVER_THINK ? false : true );
}

void CBaseEntity::SetLastThink( int nContextIndex, float thinkTime )
{
	int thinkTick = ( thinkTime == TICK_NEVER_THINK ) ? TICK_NEVER_THINK : TIME_TO_TICKS( thinkTime );

	if (nContextIndex < 0)
	{
		m_nLastThinkTick = thinkTick;
	}
	else
	{
		m_aThinkFunctions[nContextIndex].m_nLastThinkTick = thinkTick;
	}
}

float CBaseEntity::GetNextThink( int nContextIndex ) const
{
	if (nContextIndex < 0)
		return m_nNextThinkTick * TICK_INTERVAL;

	return m_aThinkFunctions[nContextIndex].m_nNextThinkTick * TICK_INTERVAL; 
}

int	CBaseEntity::GetNextThinkTick( int nContextIndex ) const
{
	if (nContextIndex < 0)
		return m_nNextThinkTick;

	return m_aThinkFunctions[nContextIndex].m_nNextThinkTick; 
}


//-----------------------------------------------------------------------------
// Purpose: My physics object has been updated, react or extract data
//-----------------------------------------------------------------------------
void CBaseEntity::VPhysicsUpdate( IPhysicsObject *pPhysics )
{
	switch( GetMoveType() )
	{
	case MOVETYPE_VPHYSICS:
		{
			if ( GetMoveParent() )
			{
				Log_Warning( LOG_DEVELOPER_VERBOSE, "Updating physics on object in hierarchy %s!\n", GetClassname());
				return;
			}
			Vector origin;
			QAngle angles;

			pPhysics->GetPosition( &origin, &angles );

			if ( !IsFinite( angles.x ) || !IsFinite( angles.y ) || !IsFinite( angles.x ) )
			{
				Msg( "Infinite angles from vphysics! (entity %s)\n", GetDebugName() );
				angles = vec3_angle;
			}
#ifndef CLIENT_DLL 
			Vector prevOrigin = GetAbsOrigin();
#endif

			for ( int i = 0; i < 3; ++i )
			{
				angles[ i ] = AngleNormalize( angles[ i ] );
			}

#ifndef CLIENT_DLL 
			NetworkQuantize( origin, angles );
#endif

			if ( origin.IsValid() )
			{
				SetAbsOrigin( origin );
			}
			else
			{
				Msg( "Infinite origin from vphysics! (entity %s)\n", GetDebugName() );
			}
			SetAbsAngles( angles );

			// Interactive debris converts back to debris when it comes to rest
			if ( pPhysics->IsAsleep() && GetCollisionGroup() == COLLISION_GROUP_INTERACTIVE_DEBRIS )
			{
				SetCollisionGroup( COLLISION_GROUP_DEBRIS );
			}

#ifndef CLIENT_DLL 
			PhysicsTouchTriggers( &prevOrigin );
			PhysicsRelinkChildren(gpGlobals->frametime);
#endif
		}
	break;

	case MOVETYPE_STEP:
		break;

	case MOVETYPE_PUSH:
#ifndef CLIENT_DLL
		VPhysicsUpdatePusher( pPhysics );
#endif
	break;
	}
}

//-----------------------------------------------------------------------------
// Purpose: Init this object's physics as a static
//-----------------------------------------------------------------------------
IPhysicsObject *CBaseEntity::VPhysicsInitStatic( void )
{
	if ( !VPhysicsInitSetup() )
		return NULL;

#ifndef CLIENT_DLL
	// If this entity has a move parent, it needs to be shadow, not static
	if ( GetMoveParent() )
	{
		// must be SOLID_VPHYSICS if in hierarchy to solve collisions correctly
		if ( GetSolid() == SOLID_BSP && GetRootMoveParent()->GetSolid() != SOLID_BSP )
		{
			SetSolid( SOLID_VPHYSICS );
		}

		return VPhysicsInitShadow( false, false );
	}
#endif

	// No physics
	if ( GetSolid() == SOLID_NONE )
		return NULL;

	// create a static physics objct
	IPhysicsObject *pPhysicsObject = NULL;
	if ( GetSolid() == SOLID_BBOX )
	{
		pPhysicsObject = PhysModelCreateBox( this, WorldAlignMins(), WorldAlignMaxs(), GetAbsOrigin(), true );
	}
	else
	{
		pPhysicsObject = PhysModelCreateUnmoveable( this, GetModelIndex(), GetAbsOrigin(), GetAbsAngles() );
	}
	VPhysicsSetObject( pPhysicsObject );
	return pPhysicsObject;
}

//-----------------------------------------------------------------------------
// Purpose: 
// Input  : *pPhysics - 
//-----------------------------------------------------------------------------
void CBaseEntity::VPhysicsSetObject( IPhysicsObject *pPhysics )
{
	if ( m_pPhysicsObject && pPhysics )
	{
		Warning( "Overwriting physics object for %s\n", GetClassname() );
	}
	m_pPhysicsObject = pPhysics;
#ifndef CLIENT_DLL
	RemoveSolidFlags(FSOLID_NOT_MOVEABLE);
#endif
	if ( m_pPhysicsObject )
	{
#ifndef CLIENT_DLL
		if ( m_pPhysicsObject->IsStatic() )
		{
			AddSolidFlags(FSOLID_NOT_MOVEABLE);
		}
#endif
	}
	if ( pPhysics && !m_pPhysicsObject )
	{
		CollisionRulesChanged();
	}
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CBaseEntity::VPhysicsDestroyObject( void )
{
	if ( m_pPhysicsObject )
	{
#ifndef CLIENT_DLL
		PhysRemoveShadow( this );
#endif
		PhysDestroyObject( m_pPhysicsObject, this );
		m_pPhysicsObject = NULL;

#ifdef ENABLE_PYTHON
		if( m_pyPhysObj.ptr() != Py_None )
		{
			try {
				PyPhysicsObject *pPyPhysObj = bp::extract<PyPhysicsObject *>(m_pyPhysObj);
				pPyPhysObj->SetInvalid();
			} catch(boost::python::error_already_set &) {
				PyErr_Print();
				PyErr_Clear();
			}
			m_pyPhysObj = bp::object();
		}
#endif // ENABLE_PYTHON
	}
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
bool CBaseEntity::VPhysicsInitSetup()
{
#ifndef CLIENT_DLL
	// don't support logical ents
	if ( !edict() || IsMarkedForDeletion() )
		return false;
#endif

	// If this entity already has a physics object, then it should have been deleted prior to making this call.
	Assert(!m_pPhysicsObject);
	VPhysicsDestroyObject();

	// make sure absorigin / absangles are correct
	return true;
}

//-----------------------------------------------------------------------------
// Purpose: This creates a normal vphysics simulated object
//			physics alone determines where it goes (gravity, friction, etc)
//			and the entity receives updates from vphysics.  SetAbsOrigin(), etc do not affect the object!
//-----------------------------------------------------------------------------
IPhysicsObject *CBaseEntity::VPhysicsInitNormal( SolidType_t solidType, int nSolidFlags, bool createAsleep, solid_t *pSolid )
{
	if ( !VPhysicsInitSetup() )
		return NULL;

	// NOTE: This has to occur before PhysModelCreate because that call will
	// call back into ShouldCollide(), which uses solidtype for rules.
	SetSolid( solidType );
	SetSolidFlags( nSolidFlags );

	// No physics
	if ( solidType == SOLID_NONE )
	{
		return NULL;
	}

	// create a normal physics object
	IPhysicsObject *pPhysicsObject = PhysModelCreate( this, GetModelIndex(), GetAbsOrigin(), GetAbsAngles(), pSolid );
	if ( pPhysicsObject )
	{
		VPhysicsSetObject( pPhysicsObject );
		SetMoveType( MOVETYPE_VPHYSICS );

		if ( !createAsleep )
		{
			pPhysicsObject->Wake();
		}
	}

	return pPhysicsObject;
}

// This creates a vphysics object with a shadow controller that follows the AI
IPhysicsObject *CBaseEntity::VPhysicsInitShadow( bool allowPhysicsMovement, bool allowPhysicsRotation, solid_t *pSolid )
{
	if ( !VPhysicsInitSetup() )
		return NULL;

	// No physics
	if ( GetSolid() == SOLID_NONE )
		return NULL;

	const Vector &origin = GetAbsOrigin();
	QAngle angles = GetAbsAngles();
	IPhysicsObject *pPhysicsObject = NULL;

	if ( GetSolid() == SOLID_BBOX )
	{
		// adjust these so the game tracing epsilons match the physics minimum separation distance
		// this will shrink the vphysics version of the model by the difference in epsilons
		float radius = 0.25f - DIST_EPSILON;
		Vector mins = WorldAlignMins() + Vector(radius, radius, radius);
		Vector maxs = WorldAlignMaxs() - Vector(radius, radius, radius);
		pPhysicsObject = PhysModelCreateBox( this, mins, maxs, origin, false );
		angles = vec3_angle;
	}
	else if ( GetSolid() == SOLID_OBB )
	{
		pPhysicsObject = PhysModelCreateOBB( this, CollisionProp()->OBBMins(), CollisionProp()->OBBMaxs(), origin, angles, false );
	}
	else
	{
		pPhysicsObject = PhysModelCreate( this, GetModelIndex(), origin, angles, pSolid );
	}
	if ( !pPhysicsObject )
		return NULL;

	VPhysicsSetObject( pPhysicsObject );
	// UNDONE: Tune these speeds!!!
	pPhysicsObject->SetShadow( 1e4, 1e4, allowPhysicsMovement, allowPhysicsRotation );
	pPhysicsObject->UpdateShadow( origin, angles, false, 0 );
	return pPhysicsObject;
}


//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
bool CBaseEntity::CreateVPhysics()
{
	return false;
}

bool CBaseEntity::IsStandable() const
{
	if (GetSolidFlags() & FSOLID_NOT_STANDABLE) 
		return false;

	if ( GetSolid() == SOLID_BSP || GetSolid() == SOLID_VPHYSICS || GetSolid() == SOLID_BBOX )
		return true;

	return IsBSPModel( ); 
}

bool CBaseEntity::IsBSPModel() const
{
	if ( GetSolid() == SOLID_BSP )
		return true;
	
	const model_t *model = modelinfo->GetModel( GetModelIndex() );

	if ( GetSolid() == SOLID_VPHYSICS && modelinfo->GetModelType( model ) == mod_brush )
		return true;

	return false;
}


//-----------------------------------------------------------------------------
// Invalidates the abs state of all children
//-----------------------------------------------------------------------------
void CBaseEntity::InvalidatePhysicsRecursive( int nChangeFlags )
{
	// Main entry point for dirty flag setting for the 90% case
	// 1) If the origin changes, then we have to update abstransform, Shadow projection, PVS, KD-tree, 
	//    client-leaf system.
	// 2) If the angles change, then we have to update abstransform, Shadow projection,
	//    shadow render-to-texture, client-leaf system, and surrounding bounds. 
	//	  Children have to additionally update absvelocity, KD-tree, and PVS.
	//	  If the surrounding bounds actually update, when we also need to update the KD-tree and the PVS.
	// 3) If it's due to attachment, then all children who are attached to an attachment point
	//    are assumed to have dirty origin + angles.

	// Other stuff:
	// 1) Marking the surrounding bounds dirty will automatically mark KD tree + PVS dirty.
	
	int nDirtyFlags = 0;

	if ( nChangeFlags & VELOCITY_CHANGED )
	{
		nDirtyFlags |= EFL_DIRTY_ABSVELOCITY;
	}

	bool bSurroundDirty = false;
	if ( nChangeFlags & POSITION_CHANGED )
	{
		nDirtyFlags |= EFL_DIRTY_ABSTRANSFORM;

#ifndef CLIENT_DLL
		NetworkProp()->MarkPVSInformationDirty();
#endif

		// NOTE: This will also mark shadow projection + client leaf dirty
		if ( entindex() != 0 )
		{
			CollisionProp()->MarkPartitionHandleDirty();
		}
	}

	// NOTE: This has to be done after velocity + position are changed
	// because we change the nChangeFlags for the child entities
	if ( nChangeFlags & ANGLES_CHANGED )
	{
		nDirtyFlags |= EFL_DIRTY_ABSTRANSFORM;
		if ( CollisionProp()->DoesRotationInvalidateSurroundingBox() )
		{
			// NOTE: This will handle the KD-tree, surrounding bounds, PVS
			// render-to-texture shadow, shadow projection, and client leaf dirty
			CollisionProp()->MarkSurroundingBoundsDirty();
			bSurroundDirty = true;
		}

		// This is going to be used for all children: children
		// have position + velocity changed
		nChangeFlags |= POSITION_CHANGED | VELOCITY_CHANGED;
	}

	if ( nChangeFlags & SEQUENCE_CHANGED )
	{
		if ( !bSurroundDirty )
		{
			if ( CollisionProp()->DoesSequenceChangeInvalidateSurroundingBox() )
			{
				// NOTE: This will handle the KD-tree, surrounding bounds, PVS
				// render-to-texture shadow, shadow projection, and client leaf dirty
				CollisionProp()->MarkSurroundingBoundsDirty();
				bSurroundDirty = true;
			}
		}

		// Children sequences do not change as a result of parent sequence changes
		nChangeFlags &= ~SEQUENCE_CHANGED;
	}

#ifdef CLIENT_DLL
	if ( !bSurroundDirty && (nChangeFlags & (POSITION_CHANGED|ANGLES_CHANGED|BOUNDS_CHANGED)) )
	{
		if ( entindex() != 0 )
		{
			MarkRenderHandleDirty();
			g_pClientShadowMgr->AddToDirtyShadowList( this );
			g_pClientShadowMgr->MarkRenderToTextureShadowDirty( GetShadowHandle() );
		}
	}
#endif

	AddEFlags( nDirtyFlags );

	// Set flags for children
	bool bOnlyDueToAttachment = false;
	if ( nChangeFlags & ( ANIMATION_CHANGED | BOUNDS_CHANGED ) )
	{
#ifdef CLIENT_DLL
		if ( ( nChangeFlags & BOUNDS_CHANGED ) == 0 )
		{
			g_pClientShadowMgr->MarkRenderToTextureShadowDirty( GetShadowHandle() );
		}
#endif

		// Only set this flag if the only thing that changed us was the animation.
		// If position or something else changed us, then we must tell all children.
		if ( !( nChangeFlags & (POSITION_CHANGED | VELOCITY_CHANGED | ANGLES_CHANGED) ) )
		{
			bOnlyDueToAttachment = true;
		}

		nChangeFlags = POSITION_CHANGED | ANGLES_CHANGED | VELOCITY_CHANGED;
	}

	for (CBaseEntity *pChild = FirstMoveChild(); pChild; pChild = pChild->NextMovePeer())
	{
		// If this is due to the parent animating, only invalidate children that are parented to an attachment
		// Entities that are following also access attachments points on parents and must be invalidated.
		if ( bOnlyDueToAttachment )
		{
#ifdef CLIENT_DLL
			if ( (pChild->GetParentAttachment() == 0) && !pChild->IsFollowingEntity() )
				continue;
#else
			if ( pChild->GetParentAttachment() == 0 )
				continue;
#endif
		}
		pChild->InvalidatePhysicsRecursive( nChangeFlags );
	}

	// Clear out cached bones
	if ( nChangeFlags & (POSITION_CHANGED | ANGLES_CHANGED | ANIMATION_CHANGED) )
	{
		CBaseAnimating *pAnim = GetBaseAnimating();
		if ( pAnim )
			pAnim->InvalidateBoneCache();		
	}
}



//-----------------------------------------------------------------------------
// Returns the highest parent of an entity
//-----------------------------------------------------------------------------
CBaseEntity *CBaseEntity::GetRootMoveParent()
{
	CBaseEntity *pEntity = this;
	CBaseEntity *pParent = this->GetMoveParent();
	while ( pParent )
	{
		pEntity = pParent;
		pParent = pEntity->GetMoveParent();
	}

	return pEntity;
}

//-----------------------------------------------------------------------------
// Purpose: static method
// Output : Returns true on success, false on failure.
//-----------------------------------------------------------------------------
bool CBaseEntity::IsPrecacheAllowed()
{
	return m_bAllowPrecache;
}

//-----------------------------------------------------------------------------
// Purpose: static method
// Input  : allow - 
//-----------------------------------------------------------------------------
void CBaseEntity::SetAllowPrecache( bool allow )
{
	m_bAllowPrecache = allow;
}

/*
================
FireBullets

Go to the trouble of combining multiple pellets into a single damage call.
================
*/

#if defined( GAME_DLL )
class CBulletsTraceFilter : public CTraceFilterSimpleList
{
public:
	CBulletsTraceFilter( int collisionGroup ) : CTraceFilterSimpleList( collisionGroup ) {}

	bool ShouldHitEntity( IHandleEntity *pHandleEntity, int contentsMask )
	{
		if ( m_PassEntities.Count() )
		{
			CBaseEntity *pEntity = EntityFromEntityHandle( pHandleEntity );
			CBaseEntity *pPassEntity = EntityFromEntityHandle( m_PassEntities[0] );
			if ( pEntity && pPassEntity && pEntity->GetOwnerEntity() == pPassEntity && 
				pPassEntity->IsSolidFlagSet(FSOLID_NOT_SOLID) && pPassEntity->IsSolidFlagSet( FSOLID_CUSTOMBOXTEST ) && 
				pPassEntity->IsSolidFlagSet( FSOLID_CUSTOMRAYTEST ) )
			{
				// It's a bone follower of the entity to ignore (toml 8/3/2007)
				return false;
			}
		}
		return CTraceFilterSimpleList::ShouldHitEntity( pHandleEntity, contentsMask );
	}

};
#else
typedef CTraceFilterSimpleList CBulletsTraceFilter;
#endif

void CBaseEntity::FireBullets( const FireBulletsInfo_t &info )
{
	static int	tracerCount;
	trace_t		tr;
	CAmmoDef*	pAmmoDef	= GetAmmoDef();
	int			nDamageType	= pAmmoDef->DamageType(info.m_iAmmoType);
	int			nAmmoFlags	= pAmmoDef->Flags(info.m_iAmmoType);
	
	bool bDoServerEffects = true;

#if defined( GAME_DLL )
	if( IsPlayer() )
	{
		CBasePlayer *pPlayer = dynamic_cast<CBasePlayer*>(this);

		int rumbleEffect = pPlayer->GetActiveWeapon()->GetRumbleEffect();

		if( rumbleEffect != RUMBLE_INVALID )
		{
			if( rumbleEffect == RUMBLE_SHOTGUN_SINGLE )
			{
				if( info.m_iShots == 12 )
				{
					// Upgrade to double barrel rumble effect
					rumbleEffect = RUMBLE_SHOTGUN_DOUBLE;
				}
			}

			pPlayer->RumbleEffect( rumbleEffect, 0, RUMBLE_FLAG_RESTART );
		}
	}
#endif// GAME_DLL

	float flPlayerDamage = info.m_flPlayerDamage;
	if ( flPlayerDamage == 0.0f )
	{
		if ( nAmmoFlags & AMMO_INTERPRET_PLRDAMAGE_AS_DAMAGE_TO_PLAYER )
		{
			flPlayerDamage = pAmmoDef->PlrDamage( info.m_iAmmoType );
		}
	}

	// the default attacker is ourselves
	CBaseEntity *pAttacker = info.m_pAttacker ? info.m_pAttacker : this;

	// Make sure we don't have a dangling damage target from a recursive call
	if ( g_MultiDamage.GetTarget() != NULL )
	{
		ApplyMultiDamage();
	}
	  
	ClearMultiDamage();
	g_MultiDamage.SetDamageType( nDamageType | DMG_NEVERGIB );

	Vector vecDir;
	Vector vecEnd;
	
	// Skip multiple entities when tracing
	CBulletsTraceFilter traceFilter( COLLISION_GROUP_NONE );
	traceFilter.SetPassEntity( this ); // Standard pass entity for THIS so that it can be easily removed from the list after passing through a portal
	traceFilter.AddEntityToIgnore( info.m_pAdditionalIgnoreEnt );

#if defined( HL2_EPISODIC ) && defined( GAME_DLL )
	// FIXME: We need to emulate this same behavior on the client as well -- jdw
	// Also ignore a vehicle we're a passenger in
	if ( MyCombatCharacterPointer() != NULL && MyCombatCharacterPointer()->IsInAVehicle() )
	{
		traceFilter.AddEntityToIgnore( MyCombatCharacterPointer()->GetVehicleEntity() );
	}
#endif // SERVER_DLL

	bool bUnderwaterBullets = ShouldDrawUnderwaterBulletBubbles();
	bool bStartedInWater = false;
	if ( bUnderwaterBullets )
	{
		bStartedInWater = ( enginetrace->GetPointContents( info.m_vecSrc, MASK_WATER ) & (CONTENTS_WATER|CONTENTS_SLIME) ) != 0;
	}

	// Prediction is only usable on players
	int iSeed = 0;
	if ( IsPlayer() )
	{
		iSeed = CBaseEntity::GetPredictionRandomSeed() & 255;
	}

	//-----------------------------------------------------
	// Set up our shot manipulator.
	//-----------------------------------------------------
	CShotManipulator Manipulator( info.m_vecDirShooting );

	bool bDoImpacts = false;
	bool bDoTracers = false;
	
	float flCumulativeDamage = 0.0f;

	for (int iShot = 0; iShot < info.m_iShots; iShot++)
	{
		bool bHitWater = false;
		bool bHitGlass = false;

		// Prediction is only usable on players
		if ( IsPlayer() )
		{
			RandomSeed( iSeed );	// init random system with this seed
		}

		// If we're firing multiple shots, and the first shot has to be bang on target, ignore spread
		if ( iShot == 0 && info.m_iShots > 1 && (info.m_nFlags & FIRE_BULLETS_FIRST_SHOT_ACCURATE) )
		{
			vecDir = Manipulator.GetShotDirection();
		}
		else
		{

			// Don't run the biasing code for the player at the moment.
			vecDir = Manipulator.ApplySpread( info.m_vecSpread );
		}

		vecEnd = info.m_vecSrc + vecDir * info.m_flDistance;




		if( IsPlayer() && info.m_iShots > 1 && iShot % 2 )
		{
			// Half of the shotgun pellets are hulls that make it easier to hit targets with the shotgun.

			AI_TraceHull( info.m_vecSrc, vecEnd, Vector( -3, -3, -3 ), Vector( 3, 3, 3 ), MASK_SHOT, &traceFilter, &tr );

		}
		else
		{

			AI_TraceLine(info.m_vecSrc, vecEnd, MASK_SHOT, &traceFilter, &tr);

		}

		// Tracker 70354/63250:  ywb 8/2/07
		// Fixes bug where trace from turret with attachment point outside of Vcollide
		//  starts solid so doesn't hit anything else in the world and the final coord 
		//  is outside of the MAX_COORD_FLOAT range.  This cause trying to send the end pos
		//  of the tracer down to the client with an origin which is out-of-range for networking
		if ( tr.startsolid )
		{
			tr.endpos = tr.startpos;
			tr.fraction = 0.0f;
		}



#ifdef GAME_DLL
		if ( ai_debug_shoot_positions.GetBool() )
			NDebugOverlay::Line(info.m_vecSrc, vecEnd, 255, 255, 255, false, .1 );
#endif

		if ( bStartedInWater )
		{
#ifdef GAME_DLL
			Vector vBubbleStart = info.m_vecSrc;
			Vector vBubbleEnd = tr.endpos;



			CreateBubbleTrailTracer( vBubbleStart, vBubbleEnd, vecDir );
			


#endif //#ifdef GAME_DLL
			bHitWater = true;
		}

		// Now hit all triggers along the ray that respond to shots...
		// Clip the ray to the first collided solid returned from traceline
		CTakeDamageInfo triggerInfo( pAttacker, pAttacker, info.m_flDamage, nDamageType );
		CalculateBulletDamageForce( &triggerInfo, info.m_iAmmoType, vecDir, tr.endpos );
		triggerInfo.ScaleDamageForce( info.m_flDamageForceScale );
		triggerInfo.SetAmmoType( info.m_iAmmoType );
#ifdef GAME_DLL
		TraceAttackToTriggers( triggerInfo, tr.startpos, tr.endpos, vecDir );
#endif

		// Make sure given a valid bullet type
		if (info.m_iAmmoType == -1)
		{
			DevMsg("ERROR: Undefined ammo type!\n");
			return;
		}

		Vector vecTracerDest = tr.endpos;

		// do damage, paint decals
		if (tr.fraction != 1.0)
		{
#ifdef GAME_DLL
			UpdateShotStatistics( tr );

#ifndef HL2WARS_DLL
			// For shots that don't need persistance
			int soundEntChannel = ( info.m_nFlags&FIRE_BULLETS_TEMPORARY_DANGER_SOUND ) ? SOUNDENT_CHANNEL_BULLET_IMPACT : SOUNDENT_CHANNEL_UNSPECIFIED;

			CSoundEnt::InsertSound( SOUND_BULLET_IMPACT, tr.endpos, 200, 0.5, this, soundEntChannel );
#endif // HL2WARS_DLL
#endif

			// See if the bullet ended up underwater + started out of the water
			if ( !bHitWater && ( enginetrace->GetPointContents( tr.endpos, MASK_WATER ) & (CONTENTS_WATER|CONTENTS_SLIME) ) )
			{
				bHitWater = HandleShotImpactingWater( info, vecEnd, &traceFilter, &vecTracerDest );
			}

			float flActualDamage = info.m_flDamage;

			// If we hit a player, and we have player damage specified, use that instead
			// Adrian: Make sure to use the currect value if we hit a vehicle the player is currently driving.
			if ( flPlayerDamage != 0.0f )
			{
				if ( tr.m_pEnt->IsPlayer() )
				{
					flActualDamage = flPlayerDamage;
				}
#ifdef GAME_DLL
				else if ( tr.m_pEnt->GetServerVehicle() )
				{
					if ( tr.m_pEnt->GetServerVehicle()->GetPassenger() && tr.m_pEnt->GetServerVehicle()->GetPassenger()->IsPlayer() )
					{
						flActualDamage = flPlayerDamage;
					}
				}
#endif
			}

			int nActualDamageType = nDamageType;
			if ( flActualDamage == 0.0 )
			{
				flActualDamage = g_pGameRules->GetAmmoDamage( pAttacker, tr.m_pEnt, info.m_iAmmoType );
			}
			else
			{
				nActualDamageType = nDamageType | ((flActualDamage > 16) ? DMG_ALWAYSGIB : DMG_NEVERGIB );
			}

			if ( !bHitWater || ((info.m_nFlags & FIRE_BULLETS_DONT_HIT_UNDERWATER) == 0) )
			{
				// Damage specified by function parameter
				CTakeDamageInfo dmgInfo( this, pAttacker, flActualDamage, nActualDamageType );
				CalculateBulletDamageForce( &dmgInfo, info.m_iAmmoType, vecDir, tr.endpos );
				dmgInfo.ScaleDamageForce( info.m_flDamageForceScale );
				dmgInfo.SetAmmoType( info.m_iAmmoType );
				tr.m_pEnt->DispatchTraceAttack( dmgInfo, vecDir, &tr );
			
				if ( ToBaseCombatCharacter( tr.m_pEnt ) )
				{
					flCumulativeDamage += dmgInfo.GetDamage();
				}

				if ( bStartedInWater || !bHitWater || (info.m_nFlags & FIRE_BULLETS_ALLOW_WATER_SURFACE_IMPACTS) )
				{
					if ( bDoServerEffects == true )
					{
						DoImpactEffect( tr, nDamageType );
					}
					else
					{
						bDoImpacts = true;
					}
				}
				else
				{
					// We may not impact, but we DO need to affect ragdolls on the client
					CEffectData data;
					data.m_vStart = tr.startpos;
					data.m_vOrigin = tr.endpos;
					data.m_nDamageType = nDamageType;
					
					DispatchEffect( "RagdollImpact", data );
				}
	
#ifdef GAME_DLL
				if ( nAmmoFlags & AMMO_FORCE_DROP_IF_CARRIED )
				{
					// Make sure if the player is holding this, he drops it
					Pickup_ForcePlayerToDropThisObject( tr.m_pEnt );		
				}
#endif
			}
		}

		// See if we hit glass
		if ( tr.m_pEnt != NULL )
		{
#ifdef GAME_DLL
			surfacedata_t *psurf = physprops->GetSurfaceData( tr.surface.surfaceProps );
			if ( ( psurf != NULL ) && ( psurf->game.material == CHAR_TEX_GLASS ) && ( tr.m_pEnt->ClassMatches( "func_breakable" ) ) )
			{
				// Query the func_breakable for whether it wants to allow for bullet penetration
				if ( tr.m_pEnt->HasSpawnFlags( SF_BREAK_NO_BULLET_PENETRATION ) == false )
				{
					bHitGlass = true;
				}
			}
#endif
		}

		if ( ( info.m_iTracerFreq != 0 ) && ( tracerCount++ % info.m_iTracerFreq ) == 0 && ( bHitGlass == false ) )
		{
			if ( bDoServerEffects == true )
			{
				Vector vecTracerSrc = vec3_origin;
				ComputeTracerStartPosition( info.m_vecSrc, &vecTracerSrc );

				trace_t Tracer;
				Tracer = tr;
				Tracer.endpos = vecTracerDest;



				MakeTracer( vecTracerSrc, Tracer, pAmmoDef->TracerType(info.m_iAmmoType) );


			}
			else
			{
				bDoTracers = true;
			}
		}

		//NOTENOTE: We could expand this to a more general solution for various material penetration types (wood, thin metal, etc)

		// See if we should pass through glass
#ifdef GAME_DLL
		if ( bHitGlass )
		{
			HandleShotImpactingGlass( info, tr, vecDir, &traceFilter );
		}
#endif

		iSeed++;
	}

#ifdef GAME_DLL
	ApplyMultiDamage();

	if ( IsPlayer() && flCumulativeDamage > 0.0f )
	{
		CBasePlayer *pPlayer = static_cast< CBasePlayer * >( this );
		CTakeDamageInfo dmgInfo( this, pAttacker, flCumulativeDamage, nDamageType );
		gamestats->Event_WeaponHit( pPlayer, info.m_bPrimaryAttack, pPlayer->GetActiveWeapon()->GetClassname(), dmgInfo );
	}
#endif
}


//-----------------------------------------------------------------------------
// Should we draw bubbles underwater?
//-----------------------------------------------------------------------------
bool CBaseEntity::ShouldDrawUnderwaterBulletBubbles()
{
#if defined( HL2_DLL ) && defined( GAME_DLL )
	CBaseEntity *pPlayer = ( gpGlobals->maxClients == 1 ) ? UTIL_GetLocalPlayer() : NULL;
	return pPlayer && (pPlayer->GetWaterLevel() == 3);
#else
	return false;
#endif
}


//-----------------------------------------------------------------------------
// Handle shot entering water
//-----------------------------------------------------------------------------
bool CBaseEntity::HandleShotImpactingWater( const FireBulletsInfo_t &info, 
	const Vector &vecEnd, ITraceFilter *pTraceFilter, Vector *pVecTracerDest )
{
	trace_t	waterTrace;

	// Trace again with water enabled
	AI_TraceLine( info.m_vecSrc, vecEnd, (MASK_SHOT|CONTENTS_WATER|CONTENTS_SLIME), pTraceFilter, &waterTrace );
	
	// See if this is the point we entered
	if ( ( enginetrace->GetPointContents( waterTrace.endpos - Vector(0,0,0.1f), MASK_WATER ) & (CONTENTS_WATER|CONTENTS_SLIME) ) == 0 )
		return false;

	if ( ShouldDrawWaterImpacts() )
	{
		int	nMinSplashSize = GetAmmoDef()->MinSplashSize(info.m_iAmmoType);
		int	nMaxSplashSize = GetAmmoDef()->MaxSplashSize(info.m_iAmmoType);

		CEffectData	data;
 		data.m_vOrigin = waterTrace.endpos;
		data.m_vNormal = waterTrace.plane.normal;
		data.m_flScale = random->RandomFloat( nMinSplashSize, nMaxSplashSize );
		if ( waterTrace.contents & CONTENTS_SLIME )
		{
			data.m_fFlags |= FX_WATER_IN_SLIME;
		}
		DispatchEffect( "gunshotsplash", data );
	}

#ifdef GAME_DLL
	if ( ShouldDrawUnderwaterBulletBubbles() )
	{
		CWaterBullet *pWaterBullet = ( CWaterBullet * )CreateEntityByName( "waterbullet" );
		if ( pWaterBullet )
		{
			pWaterBullet->Spawn( waterTrace.endpos, info.m_vecDirShooting );
					 
			CEffectData tracerData;
			tracerData.m_vStart = waterTrace.endpos;
			tracerData.m_vOrigin = waterTrace.endpos + info.m_vecDirShooting * 400.0f;
			tracerData.m_fFlags = TRACER_TYPE_WATERBULLET;
			DispatchEffect( "TracerSound", tracerData );
		}
	}
#endif

	*pVecTracerDest = waterTrace.endpos;
	return true;
}


ITraceFilter* CBaseEntity::GetBeamTraceFilter( void )
{
	return NULL;
}


void CBaseEntity::DispatchTraceAttack( const CTakeDamageInfo &info, const Vector &vecDir, trace_t *ptr )
{
#ifdef GAME_DLL
	// Make sure our damage filter allows the damage.
	if ( !PassesDamageFilter( info ))
	{
		return;
	}
#endif

	TraceAttack( info, vecDir, ptr );
}

void CBaseEntity::TraceAttack( const CTakeDamageInfo &info, const Vector &vecDir, trace_t *ptr )
{
	Vector vecOrigin = ptr->endpos - vecDir * 4;

	if ( m_takedamage )
	{
		AddMultiDamage( info, this );

		int blood = BloodColor();
		
		if ( blood != DONT_BLEED )
		{
			SpawnBlood( vecOrigin, vecDir, blood, info.GetDamage() );// a little surface blood.
			TraceBleed( info.GetDamage(), vecDir, ptr, info.GetDamageType() );
		}
	}
}


//-----------------------------------------------------------------------------
// Allows the shooter to change the impact effect of his bullets
//-----------------------------------------------------------------------------
void CBaseEntity::DoImpactEffect( trace_t &tr, int nDamageType )
{
	// give shooter a chance to do a custom impact.
	UTIL_ImpactTrace( &tr, nDamageType );
} 


//-----------------------------------------------------------------------------
// Computes the tracer start position
//-----------------------------------------------------------------------------
void CBaseEntity::ComputeTracerStartPosition( const Vector &vecShotSrc, Vector *pVecTracerStart )
{
#if 0
	if ( g_pGameRules->IsMultiplayer() )
	{
		// NOTE: we do this because in MakeTracer, we force it to use the attachment position
		// in multiplayer, so the results from this function should never actually get used.
		pVecTracerStart->Init( 999, 999, 999 );
		return;
	}
#endif // 0
	
	if ( IsPlayer() )
	{
		// adjust tracer position for player
		Vector forward, right;
		CBasePlayer *pPlayer = ToBasePlayer( this );
		pPlayer->EyeVectors( &forward, &right, NULL );
		*pVecTracerStart = vecShotSrc + Vector ( 0 , 0 , -4 ) + right * 2 + forward * 16;
	}
	else
	{
		*pVecTracerStart = vecShotSrc;

		CBaseCombatCharacter *pBCC = MyCombatCharacterPointer();
		if ( pBCC != NULL )
		{
			CBaseCombatWeapon *pWeapon = pBCC->GetActiveWeapon();

			if ( pWeapon != NULL )
			{
				Vector vecMuzzle;
				QAngle vecMuzzleAngles;

				if ( pWeapon->GetAttachment( 1, vecMuzzle, vecMuzzleAngles ) )
				{
					*pVecTracerStart = vecMuzzle;
				}
			}
		}
	}
}


//-----------------------------------------------------------------------------
// Purpose: Virtual function allows entities to handle tracer presentation
//			as they see fit.
//
// Input  : vecTracerSrc - the point at which to start the tracer (not always the
//			same spot as the traceline!
//
//			tr - the entire trace result for the shot.
//
// Output :
//-----------------------------------------------------------------------------
void CBaseEntity::MakeTracer( const Vector &vecTracerSrc, const trace_t &tr, int iTracerType )
{
	const char *pszTracerName = GetTracerType();

	Vector vNewSrc = vecTracerSrc;

	int iAttachment = GetTracerAttachment();

	switch ( iTracerType )
	{
	case TRACER_LINE:
		UTIL_Tracer( vNewSrc, tr.endpos, entindex(), iAttachment, 0.0f, false, pszTracerName );
		break;

	case TRACER_LINE_AND_WHIZ:
		UTIL_Tracer( vNewSrc, tr.endpos, entindex(), iAttachment, 0.0f, true, pszTracerName );
		break;
	}
}

//-----------------------------------------------------------------------------
// Default tracer attachment
//-----------------------------------------------------------------------------
int CBaseEntity::GetTracerAttachment( void )
{
	int iAttachment = TRACER_DONT_USE_ATTACHMENT;

	if ( g_pGameRules->IsMultiplayer() )
	{
		iAttachment = 1;
	}

	return iAttachment;
}


int CBaseEntity::BloodColor()
{
	return DONT_BLEED; 
}


void CBaseEntity::TraceBleed( float flDamage, const Vector &vecDir, trace_t *ptr, int bitsDamageType )
{
	if ((BloodColor() == DONT_BLEED) || (BloodColor() == BLOOD_COLOR_MECH))
	{
		return;
	}

	if (flDamage == 0)
		return;

	if (! (bitsDamageType & (DMG_CRUSH | DMG_BULLET | DMG_SLASH | DMG_BLAST | DMG_CLUB | DMG_AIRBOAT)))
		return;

	// make blood decal on the wall!
	trace_t Bloodtr;
	Vector vecTraceDir;
	float flNoise;
	int cCount;
	int i;

#ifdef GAME_DLL
	if ( !IsAlive() )
	{
		// dealing with a dead npc.
		if ( GetMaxHealth() <= 0 )
		{
			// no blood decal for a npc that has already decalled its limit.
			return;
		}
		else
		{
			m_iMaxHealth -= 1;
		}
	}
#endif

	if (flDamage < 10)
	{
		flNoise = 0.1;
		cCount = 1;
	}
	else if (flDamage < 25)
	{
		flNoise = 0.2;
		cCount = 2;
	}
	else
	{
		flNoise = 0.3;
		cCount = 4;
	}

	float flTraceDist = (bitsDamageType & DMG_AIRBOAT) ? 384 : 172;
	for ( i = 0 ; i < cCount ; i++ )
	{
		vecTraceDir = vecDir * -1;// trace in the opposite direction the shot came from (the direction the shot is going)

		vecTraceDir.x += random->RandomFloat( -flNoise, flNoise );
		vecTraceDir.y += random->RandomFloat( -flNoise, flNoise );
		vecTraceDir.z += random->RandomFloat( -flNoise, flNoise );

		// Don't bleed on grates.
		AI_TraceLine( ptr->endpos, ptr->endpos + vecTraceDir * -flTraceDist, MASK_SOLID_BRUSHONLY & ~CONTENTS_GRATE, this, COLLISION_GROUP_NONE, &Bloodtr);

		if ( Bloodtr.fraction != 1.0 )
		{
			UTIL_BloodDecalTrace( &Bloodtr, BloodColor() );
		}
	}
}


const char* CBaseEntity::GetTracerType()
{
	return NULL;
}


//-----------------------------------------------------------------------------
// These methods encapsulate MOVETYPE_FOLLOW, which became obsolete
//-----------------------------------------------------------------------------
void CBaseEntity::FollowEntity( CBaseEntity *pBaseEntity, bool bBoneMerge )
{
	if (pBaseEntity)
	{
		SetParent( pBaseEntity );
		SetMoveType( MOVETYPE_NONE );
		
		if ( bBoneMerge )
			AddEffects( EF_BONEMERGE );

		AddSolidFlags( FSOLID_NOT_SOLID );
		SetLocalOrigin( vec3_origin );
		SetLocalAngles( vec3_angle );
	}
	else
	{
		StopFollowingEntity();
	}
}

void CBaseEntity::SetEffectEntity( CBaseEntity *pEffectEnt )
{
	if ( m_hEffectEntity.Get() != pEffectEnt )
	{
		m_hEffectEntity = pEffectEnt;
	}
}


void CBaseEntity::ApplyLocalVelocityImpulse( const Vector &vecImpulse )
{
	// NOTE: Don't have to use GetVelocity here because local values
	// are always guaranteed to be correct, unlike abs values which may 
	// require recomputation
	if (vecImpulse != vec3_origin )
	{
		if ( GetMoveType() == MOVETYPE_VPHYSICS )
		{
			IPhysicsObject *ppPhysObjs[ VPHYSICS_MAX_OBJECT_LIST_COUNT ];
			int nNumPhysObjs = VPhysicsGetObjectList( ppPhysObjs, VPHYSICS_MAX_OBJECT_LIST_COUNT );
			for ( int i = 0; i < nNumPhysObjs; i++ )
			{
				Vector worldVel;
				ppPhysObjs[ i ]->LocalToWorld( &worldVel, vecImpulse );
				ppPhysObjs[ i ]->AddVelocity(  &worldVel, NULL );
			}
		}
		else
		{
			InvalidatePhysicsRecursive( VELOCITY_CHANGED );
			m_vecVelocity += vecImpulse;
		}
	}
}

void CBaseEntity::ApplyAbsVelocityImpulse( const Vector &vecImpulse )
{
	if (vecImpulse != vec3_origin )
	{
		if ( GetMoveType() == MOVETYPE_VPHYSICS )
		{
			IPhysicsObject *ppPhysObjs[ VPHYSICS_MAX_OBJECT_LIST_COUNT ];
			int nNumPhysObjs = VPhysicsGetObjectList( ppPhysObjs, VPHYSICS_MAX_OBJECT_LIST_COUNT );
			for ( int i = 0; i < nNumPhysObjs; i++ )
			{
				ppPhysObjs[ i ]->AddVelocity( &vecImpulse, NULL );
			}
		}
		else
		{
			// NOTE: Have to use GetAbsVelocity here to ensure it's the correct value
			Vector vecResult;
			VectorAdd( GetAbsVelocity(), vecImpulse, vecResult );
			SetAbsVelocity( vecResult );
		}
	}
}

void CBaseEntity::ApplyLocalAngularVelocityImpulse( const AngularImpulse &angImpulse )
{
	if (angImpulse != vec3_origin )
	{
		if ( GetMoveType() == MOVETYPE_VPHYSICS )
		{
			IPhysicsObject *ppPhysObjs[ VPHYSICS_MAX_OBJECT_LIST_COUNT ];
			int nNumPhysObjs = VPhysicsGetObjectList( ppPhysObjs, VPHYSICS_MAX_OBJECT_LIST_COUNT );
			for ( int i = 0; i < nNumPhysObjs; i++ )
			{
				ppPhysObjs[ i ]->AddVelocity( NULL, &angImpulse );
			}
		}
		else
		{
			QAngle vecResult;
			AngularImpulseToQAngle( angImpulse, vecResult );
			VectorAdd( GetLocalAngularVelocity(), vecResult, vecResult );
			SetLocalAngularVelocity( vecResult );
		}
	}
}

void CBaseEntity::SetCollisionGroup( int collisionGroup )
{
	if ( (int)m_CollisionGroup != collisionGroup )
	{
		m_CollisionGroup = collisionGroup;
		CollisionRulesChanged();
	}
}


void CBaseEntity::CollisionRulesChanged()
{
	// ivp maintains state based on recent return values from the collision filter, so anything
	// that can change the state that a collision filter will return (like m_Solid) needs to call RecheckCollisionFilter.
	if ( VPhysicsGetObject() )
	{
		extern bool PhysIsInCallback();
		if ( PhysIsInCallback() )
		{
			Warning("Changing collision rules within a callback is likely to cause crashes!\n");
			Assert(0);
		}
		IPhysicsObject *pList[VPHYSICS_MAX_OBJECT_LIST_COUNT];
		int count = VPhysicsGetObjectList( pList, ARRAYSIZE(pList) );
		for ( int i = 0; i < count; i++ )
		{
			if ( pList[i] != NULL ) //this really shouldn't happen, but it does >_<
				pList[i]->RecheckCollisionFilter();
		}
	}
}

int CBaseEntity::GetWaterType() const
{
	int out = 0;
	if ( m_nWaterType & 1 )
		out |= CONTENTS_WATER;
	if ( m_nWaterType & 2 )
		out |= CONTENTS_SLIME;
	return out;
}

void CBaseEntity::SetWaterType( int nType )
{
	m_nWaterType = 0;
	if ( nType & CONTENTS_WATER )
		m_nWaterType |= 1;
	if ( nType & CONTENTS_SLIME )
		m_nWaterType |= 2;
}

ConVar	sv_alternateticks( "sv_alternateticks", ( IsX360() ) ? "1" : "0", FCVAR_SPONLY, "If set, server only simulates entities on even numbered ticks.\n" );

//-----------------------------------------------------------------------------
// Purpose: 
// Output : Returns true on success, false on failure.
//-----------------------------------------------------------------------------
bool CBaseEntity::IsSimulatingOnAlternateTicks()
{


	if ( gpGlobals->maxClients != 1 )
	{
		return false;
	}

	return sv_alternateticks.GetBool();
}

#ifdef CLIENT_DLL
//-----------------------------------------------------------------------------
// Purpose: 
// Input  :  - 
// Output : Returns true on success, false on failure.
//-----------------------------------------------------------------------------
bool CBaseEntity::IsToolRecording() const
{
#ifndef NO_TOOLFRAMEWORK
	return m_bToolRecording;
#else
	return false;
#endif
}
#endif

#if defined( CLIENT_DLL ) 
#define FAST_TRIGGER_TOUCH
extern void TouchTriggerPlayerMovement( C_BaseEntity *pEntity );
#endif

void CBaseEntity::PhysicsTouchTriggers( const Vector *pPrevAbsOrigin )
{
#if defined( CLIENT_DLL )
#if defined( FAST_TRIGGER_TOUCH )
	{
		Assert( !pPrevAbsOrigin );
		TouchTriggerPlayerMovement( this );
		return;
	}
#endif // FAST_TRIGGER_TOUCH
	IClientEntity *pEntity = this;
#else
	edict_t *pEntity = edict();
#endif

	if ( pEntity && !IsWorld() )
	{
		Assert(CollisionProp());
		bool isTriggerCheckSolids = IsSolidFlagSet( FSOLID_TRIGGER );
		bool isSolidCheckTriggers = IsSolid() && !isTriggerCheckSolids;		// NOTE: Moving triggers (items, ammo etc) are not 
		// checked against other triggers ot reduce the number of touchlinks created
		if ( !(isSolidCheckTriggers || isTriggerCheckSolids) )
			return;

		if ( GetSolid() == SOLID_BSP ) 
		{
			if ( !GetModel() && Q_strlen( STRING( GetModelName() ) ) == 0 ) 
			{
				Warning( "Inserted %s with no model\n", GetClassname() );
				return;
			}
		}

		SetCheckUntouch( true );
		if ( isSolidCheckTriggers )
		{
			engine->SolidMoved( pEntity, CollisionProp(), pPrevAbsOrigin, sm_bAccurateTriggerBboxChecks );
		}
		if ( isTriggerCheckSolids )
		{
			engine->TriggerMoved( pEntity, sm_bAccurateTriggerBboxChecks );
		}
	}
}


//-----------------------------------------------------------------------------
// Purpose: 
// Input  : set - 
//-----------------------------------------------------------------------------
void CBaseEntity::ModifyOrAppendCriteria( AI_CriteriaSet& set )
{
	// TODO
	// Append chapter/day?

	set.AppendCriteria( "randomnum", UTIL_VarArgs("%d", RandomInt(0,100)) );
	
	// Append our classname and game name
	set.AppendCriteria( "classname", GetClassname() );

	const char *pEntityName = "";

#ifdef CLIENT_DLL
	pEntityName = GetEntityName();
#else
	pEntityName = GetEntityNameAsCStr();
#endif

	set.AppendCriteria( "name", pEntityName );

	// Append our health
	set.AppendCriteria( "health", UTIL_VarArgs( "%i", GetHealth() ) );

	float healthfrac = 0.0f;
	if ( GetMaxHealth() > 0 )
	{
		healthfrac = (float)GetHealth() / (float)GetMaxHealth();
	}

	set.AppendCriteria( "healthfrac", UTIL_VarArgs( "%.3f", healthfrac ) );

	// Go through all the global states and append them

#ifdef GAME_DLL
	for ( int i = 0; i < GlobalEntity_GetNumGlobals(); i++ ) 
	{
		const char *szGlobalName = GlobalEntity_GetName(i);
		int iGlobalState = (int)GlobalEntity_GetStateByIndex(i);
		set.AppendCriteria( szGlobalName, UTIL_VarArgs( "%i", iGlobalState ) );
	}

	// Append map name
	set.AppendCriteria( "map", gpGlobals->mapname.ToCStr() );

	// Append anything from I/O or keyvalues pairs
	AppendContextToCriteria( set );

	if( hl2_episodic.GetBool() )
	{
		set.AppendCriteria( "episodic", "1" );
	}

	// Append anything from world I/O/keyvalues with "world" as prefix
	CWorld *world = assert_cast< CWorld * >( CBaseEntity::Instance( INDEXENT( 0 ) ) );
	if ( world )
	{
		world->AppendContextToCriteria( set, "world" );
	}
#endif
}

//-----------------------------------------------------------------------------
// Returns the health fraction
//-----------------------------------------------------------------------------
float CBaseEntity::HealthFraction() const
{
	if (GetMaxHealth() == 0)
		return 1.0f;

	float flFraction = (float)GetHealth() / (float)GetMaxHealth();
	flFraction = clamp( flFraction, 0.0f, 1.0f );
	return flFraction;
}

//------------------------------------------------------------------------------
// HL2Wars additions
void CBaseEntity::OnChangeOwnerNumberInternal( int old_owner_number )
{
	OnChangeOwnerNumber(old_owner_number);

#ifndef CLIENT_DLL
	if( GetCollisionGroup() >= WARS_COLLISION_GROUP_UNIT_START && GetCollisionGroup() <= WARS_COLLISION_GROUP_UNIT_END )
		SetCollisionGroup(CalculateOwnerCollisionGroup());
	else if( GetCollisionGroup() >= WARS_COLLISION_GROUP_IGNORE_UNIT_START && GetCollisionGroup() <= WARS_COLLISION_GROUP_IGNORE_UNIT_END )
		SetCollisionGroup(CalculateIgnoreOwnerCollisionGroup());
#endif // CLIENT_DLL

#ifdef CLIENT_DLL
	// NOTE: Use the old flags here. Flags might get changed in OnDataChanged, so don't want to use the new flags yet.
	//		 When the flags get changed it will be inserted in the right list anyway or removed.
	if( m_nOldFOWFlags & FOWFLAG_UPDATER ) 
#else
	if( m_nFOWFlags & FOWFLAG_UPDATER ) 
#endif // CLIENT_DLL
	{
		FogOfWarMgr()->RemoveFogUpdater( old_owner_number, this );
		FogOfWarMgr()->AddFogUpdater( m_iOwnerNumber, this );
	}

#ifdef CLIENT_DLL
	m_bCheckTeamColor = true; // Team color might be changing, so recheck
	UpdateVisibility();
#else
	DispatchUpdateTransmitState();
#endif // CLIENT_DLL
}

#ifndef CLIENT_DLL
extern int GetAllChildren( CBaseEntity *pParent, CUtlVector<CBaseEntity *> &list );
//------------------------------------------------------------------------------
// Purpose:
//------------------------------------------------------------------------------
void CBaseEntity::AddFOWFlags( int flags )
{
	int nOldFlags = m_nFOWFlags;

	m_nFOWFlagsIntern |= flags;

	m_nFOWFlags = m_nFOWFlagsIntern;
	if( GetParent() )
		m_nFOWFlags |= (GetParent()->GetFOWFlags() & FOWFLAG_PARENTMASK);

	if( !(nOldFlags & FOWFLAG_UPDATER) && (m_nFOWFlags & FOWFLAG_UPDATER) )
		FogOfWarMgr()->AddFogUpdater( m_iOwnerNumber, this );

	if( (!(nOldFlags & FOWFLAG_HIDDEN) && (m_nFOWFlags & FOWFLAG_HIDDEN)) || 
			(!(nOldFlags & FOWFLAG_NOTRANSMIT) && (m_nFOWFlags & FOWFLAG_NOTRANSMIT)) )
		FogOfWarMgr()->AddFogEntity(this);

	if( m_nFOWFlags & FOWFLAG_INITTRANSMIT )
	{
		for( int i = 0; i < MAX_PLAYERS; i++ )
			FogOfWarMgr()->MarkEntityUnKnown( i, entindex() );
	}

	// Tell all children to recalculate the fow flags
	CUtlVector<CBaseEntity *> childrenList;
	GetAllChildren( this, childrenList );
	if ( childrenList.Count() )
	{
		for ( int i = childrenList.Count()-1; i >= 0; --i )
		{
			childrenList[i]->RecalculateFOWFlags();
		}
	}

	DispatchUpdateTransmitState();
}

//------------------------------------------------------------------------------
// Purpose:
//------------------------------------------------------------------------------
void CBaseEntity::RemoveFOWFlags( int flags )
{
	int nOldFlags = m_nFOWFlags;

	m_nFOWFlagsIntern &= ~flags;

	m_nFOWFlags = m_nFOWFlagsIntern;
	if( GetParent() )
		m_nFOWFlags |= (GetParent()->GetFOWFlags() & FOWFLAG_PARENTMASK);

	if( (nOldFlags & FOWFLAG_UPDATER) && !(m_nFOWFlags & FOWFLAG_UPDATER) )
		FogOfWarMgr()->RemoveFogUpdater( m_iOwnerNumber, this );

	if( ((nOldFlags & FOWFLAG_HIDDEN) && !(m_nFOWFlags & FOWFLAG_HIDDEN)) ||
			((nOldFlags & FOWFLAG_NOTRANSMIT) && !(m_nFOWFlags & FOWFLAG_NOTRANSMIT)) )
		FogOfWarMgr()->RemoveFogEntity(this);

	// Tell all children to recalculate the fow flags
	CUtlVector<CBaseEntity *> childrenList;
	GetAllChildren( this, childrenList );
	if ( childrenList.Count() )
	{
		for ( int i = childrenList.Count()-1; i >= 0; --i )
		{
			childrenList[i]->RecalculateFOWFlags();
		}
	}

	DispatchUpdateTransmitState();
}

void CBaseEntity::RecalculateFOWFlags()
{
	int nOldFlags = m_nFOWFlags;

	m_nFOWFlags = m_nFOWFlagsIntern;
	if( GetParent() )
		m_nFOWFlags |= (GetParent()->GetFOWFlags() & FOWFLAG_PARENTMASK);

	if( (nOldFlags & FOWFLAG_UPDATER) && !(m_nFOWFlags & FOWFLAG_UPDATER) )
		FogOfWarMgr()->RemoveFogUpdater( m_iOwnerNumber, this );
	else if( !(nOldFlags & FOWFLAG_UPDATER) && (m_nFOWFlags & FOWFLAG_UPDATER) )
		FogOfWarMgr()->AddFogUpdater( m_iOwnerNumber, this );

	if( (!(nOldFlags & FOWFLAG_HIDDEN) && (m_nFOWFlags & FOWFLAG_HIDDEN)) || 
			(!(nOldFlags & FOWFLAG_NOTRANSMIT) && (m_nFOWFlags & FOWFLAG_NOTRANSMIT)) )
		FogOfWarMgr()->AddFogEntity(this);
	else if( ((nOldFlags & FOWFLAG_HIDDEN) && !(m_nFOWFlags & FOWFLAG_HIDDEN)) ||
			((nOldFlags & FOWFLAG_NOTRANSMIT) && !(m_nFOWFlags & FOWFLAG_NOTRANSMIT)) )
		FogOfWarMgr()->RemoveFogEntity(this);

	// Tell all children to recalculate the fow flags
	CUtlVector<CBaseEntity *> childrenList;
	GetAllChildren( this, childrenList );
	if ( childrenList.Count() )
	{
		for ( int i = childrenList.Count()-1; i >= 0; --i )
		{
			childrenList[i]->RecalculateFOWFlags();
		}
	}

	DispatchUpdateTransmitState();
}
#endif // CLIENT_DLL

#ifdef ENABLE_PYTHON
//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CBaseEntity::SetPyTouch( bp::object touch_method )
{
	// Can't set touch if m_pyInstance is None
	if( m_pyInstance.ptr() == Py_None )
	{
		Warning("SetPyTouch: Can't set touch after entity removal!\n");
		return;
	}

	m_pyTouchMethod = touch_method;
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CBaseEntity::SetPyThink( bp::object func, float thinkTime, const char *szContext )
{
	// Can't think if m_pyInstance is None
	if( m_pyInstance.ptr() == Py_None )
	{
		Warning("SetPyThink: Can't set think after entity removal!\n");
		return;
	}

	// Context think?
	if( !szContext )
	{
		if( func.ptr() == Py_None )
		{
			SetThink(NULL);
			m_pyThink = func;
		}
		else {
			SetThink( &CBaseEntity::PyThink );
			m_pyThink = func;
			int thinkTick = ( thinkTime == TICK_NEVER_THINK ) ? TICK_NEVER_THINK : TIME_TO_TICKS( thinkTime );
			if ( thinkTick != 0 )
			{
				m_nNextThinkTick = thinkTick;
				CheckHasThinkFunction( thinkTick == TICK_NEVER_THINK ? false : true );
			}
		}
		return;
	}

	// Find the think function in our list, and if we couldn't find it, register it
	int iIndex = GetIndexForThinkContext( szContext );
	if ( iIndex == NO_THINK_CONTEXT )
	{
		iIndex = RegisterThinkContext( szContext );
	}

	m_aThinkFunctions[ iIndex ].m_pyThink = func;

	if ( thinkTime != 0 )
	{
		int thinkTick = ( thinkTime == TICK_NEVER_THINK ) ? TICK_NEVER_THINK : TIME_TO_TICKS( thinkTime );
		m_aThinkFunctions[ iIndex ].m_nNextThinkTick = thinkTick;
		CheckHasThinkFunction( thinkTick == TICK_NEVER_THINK ? false : true );
	}
}

//-----------------------------------------------------------------------------
// Purpose: 
//----------------------------------------------------------------------------
void CBaseEntity::PyThink()
{
	try	{
		m_pyThink();
	} catch(boost::python::error_already_set &) {
#ifndef CLIENT_DLL
		//if( !ValidatePyInstance() )
		//	return;
#endif // CLIENT_DLL
		PyErr_Print();
		PyErr_Clear();
	}
}


// Functions which return *IPhysicsObject need to be wrapped in python
//-----------------------------------------------------------------------------
// Purpose: 
//----------------------------------------------------------------------------
void CBaseEntity::PyVPhysicsSetObject( bp::object physref )
{
	PyPhysicsObject *pPyPhysObj;

	// Clear old
	if( m_pyPhysObj.ptr() != Py_None )
	{
		pPyPhysObj = bp::extract<PyPhysicsObject *>(m_pyPhysObj);
		pPyPhysObj->SetEntity(NULL);
		m_pyPhysObj = bp::object();
	}

	// Set New
	if( physref.ptr() != Py_None )
	{
		pPyPhysObj = bp::extract<PyPhysicsObject *>(physref);
		if( !pPyPhysObj || !pPyPhysObj->IsValid() ) 
		{
			PyErr_SetString(PyExc_ValueError, "Invalid physics object" );
			throw boost::python::error_already_set();
			return;
		}

		if( pPyPhysObj->HasEntity() )
		{
			PyErr_SetString(PyExc_ValueError, "Physics object is already bound to an entity" );
			throw boost::python::error_already_set();
			return;
		}

		pPyPhysObj->SetEntity( this );
		VPhysicsSetObject( pPyPhysObj->GetVPhysicsObject() );
		m_pyPhysObj = physref;
	}
	else
	{
		VPhysicsSetObject( NULL );
	}
}

//-----------------------------------------------------------------------------
// Purpose: 
//----------------------------------------------------------------------------
bp::object CBaseEntity::PyVPhysicsGetObject( void ) 
{ 
	if( VPhysicsGetObject() && m_pyPhysObj.ptr() == Py_None )
	{
		m_pyPhysObj = PyCreatePhysicsObject(this);
	}
	return m_pyPhysObj;
}

//-----------------------------------------------------------------------------
// Purpose: 
//----------------------------------------------------------------------------
bp::object CBaseEntity::PyVPhysicsInitStatic( void ) 
{ 
	// Passing in origin and angles with NAN's will cause a crash in the physics dll...
	if( !GetAbsOrigin().IsValid() || !GetAbsAngles().IsValid() )
	{
		char buf[256];
		Q_snprintf(buf, 256, "invalid origin(%f %f %f) or angles(%f %f %f)!", GetAbsOrigin().x, GetAbsOrigin().y, GetAbsOrigin().z, GetAbsAngles().x, GetAbsAngles().y, GetAbsAngles().z);
		PyErr_SetString(PyExc_ValueError, buf );
		throw boost::python::error_already_set(); 
		return bp::object();
	}
	VPhysicsInitStatic(); 
	return PyVPhysicsGetObject(); 
}

//-----------------------------------------------------------------------------
// Purpose: 
//----------------------------------------------------------------------------
bp::object CBaseEntity::PyVPhysicsInitNormal( SolidType_t solidType, int nSolidFlags, bool createAsleep, solid_t *pSolid ) 
{ 
	// Passing in origin and angles with NAN's will cause a crash in the physics dll...
	if( !GetAbsOrigin().IsValid() || !GetAbsAngles().IsValid() )
	{
		char buf[256];
		Q_snprintf(buf, 256, "invalid origin(%f %f %f) or angles(%f %f %f)!", GetAbsOrigin().x, GetAbsOrigin().y, GetAbsOrigin().z, GetAbsAngles().x, GetAbsAngles().y, GetAbsAngles().z);
		PyErr_SetString(PyExc_ValueError, buf );
		throw boost::python::error_already_set(); 
		return bp::object();
	}
	VPhysicsInitNormal(solidType, nSolidFlags, createAsleep, pSolid); 
	return PyVPhysicsGetObject(); 
}

//-----------------------------------------------------------------------------
// Purpose: 
//----------------------------------------------------------------------------

bp::object CBaseEntity::PyVPhysicsInitShadow( bool allowPhysicsMovement, bool allowPhysicsRotation, solid_t *pSolid ) 
{ 
	// Passing in origin and angles with NAN's will cause a crash in the physics dll...
	if( !GetAbsOrigin().IsValid() || !GetAbsAngles().IsValid() )
	{
		char buf[256];
		Q_snprintf(buf, 256, "invalid origin(%f %f %f) or angles(%f %f %f)!", GetAbsOrigin().x, GetAbsOrigin().y, GetAbsOrigin().z, GetAbsAngles().x, GetAbsAngles().y, GetAbsAngles().z);
		PyErr_SetString(PyExc_ValueError, buf );
		throw boost::python::error_already_set(); 
		return bp::object();
	}
	VPhysicsInitShadow(allowPhysicsMovement, allowPhysicsRotation, pSolid); 
	return PyVPhysicsGetObject(); 
}
#endif // ENABLE_PYTHON

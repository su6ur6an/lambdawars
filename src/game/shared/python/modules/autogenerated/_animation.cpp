// This file has been generated by Py++.

#include "cbase.h"

#ifdef CLIENT_DLL

#include "boost/python.hpp"

#include "bone_setup.h"

#include "eventlist.h"

#include "animation.h"

#include "ai_activity.h"

#include "activitylist.h"

#include "npcevent.h"

#include "srcpy_animation.h"

#include "srcpy.h"

#include "tier0/memdbgon.h"

namespace bp = boost::python;

BOOST_PYTHON_MODULE(_animation){
    bp::docstring_options doc_options( true, true, false );

    bp::enum_< Animevent>("Animevent")
        .value("AE_INVALID", AE_INVALID)
        .value("AE_EMPTY", AE_EMPTY)
        .value("AE_NPC_LEFTFOOT", AE_NPC_LEFTFOOT)
        .value("AE_NPC_RIGHTFOOT", AE_NPC_RIGHTFOOT)
        .value("AE_NPC_BODYDROP_LIGHT", AE_NPC_BODYDROP_LIGHT)
        .value("AE_NPC_BODYDROP_HEAVY", AE_NPC_BODYDROP_HEAVY)
        .value("AE_NPC_SWISHSOUND", AE_NPC_SWISHSOUND)
        .value("AE_NPC_180TURN", AE_NPC_180TURN)
        .value("AE_NPC_ITEM_PICKUP", AE_NPC_ITEM_PICKUP)
        .value("AE_NPC_WEAPON_DROP", AE_NPC_WEAPON_DROP)
        .value("AE_NPC_WEAPON_SET_SEQUENCE_NAME", AE_NPC_WEAPON_SET_SEQUENCE_NAME)
        .value("AE_NPC_WEAPON_SET_SEQUENCE_NUMBER", AE_NPC_WEAPON_SET_SEQUENCE_NUMBER)
        .value("AE_NPC_WEAPON_SET_ACTIVITY", AE_NPC_WEAPON_SET_ACTIVITY)
        .value("AE_NPC_HOLSTER", AE_NPC_HOLSTER)
        .value("AE_NPC_DRAW", AE_NPC_DRAW)
        .value("AE_NPC_WEAPON_FIRE", AE_NPC_WEAPON_FIRE)
        .value("AE_CL_PLAYSOUND", AE_CL_PLAYSOUND)
        .value("AE_SV_PLAYSOUND", AE_SV_PLAYSOUND)
        .value("AE_CL_STOPSOUND", AE_CL_STOPSOUND)
        .value("AE_START_SCRIPTED_EFFECT", AE_START_SCRIPTED_EFFECT)
        .value("AE_STOP_SCRIPTED_EFFECT", AE_STOP_SCRIPTED_EFFECT)
        .value("AE_CLIENT_EFFECT_ATTACH", AE_CLIENT_EFFECT_ATTACH)
        .value("AE_MUZZLEFLASH", AE_MUZZLEFLASH)
        .value("AE_NPC_MUZZLEFLASH", AE_NPC_MUZZLEFLASH)
        .value("AE_THUMPER_THUMP", AE_THUMPER_THUMP)
        .value("AE_AMMOCRATE_PICKUP_AMMO", AE_AMMOCRATE_PICKUP_AMMO)
        .value("AE_NPC_RAGDOLL", AE_NPC_RAGDOLL)
        .value("AE_NPC_ADDGESTURE", AE_NPC_ADDGESTURE)
        .value("AE_NPC_RESTARTGESTURE", AE_NPC_RESTARTGESTURE)
        .value("AE_NPC_ATTACK_BROADCAST", AE_NPC_ATTACK_BROADCAST)
        .value("AE_NPC_HURT_INTERACTION_PARTNER", AE_NPC_HURT_INTERACTION_PARTNER)
        .value("AE_NPC_SET_INTERACTION_CANTDIE", AE_NPC_SET_INTERACTION_CANTDIE)
        .value("AE_SV_DUSTTRAIL", AE_SV_DUSTTRAIL)
        .value("AE_CL_CREATE_PARTICLE_EFFECT", AE_CL_CREATE_PARTICLE_EFFECT)
        .value("AE_CL_STOP_PARTICLE_EFFECT", AE_CL_STOP_PARTICLE_EFFECT)
        .value("AE_CL_ADD_PARTICLE_EFFECT_CP", AE_CL_ADD_PARTICLE_EFFECT_CP)
        .value("AE_CL_CREATE_PARTICLE_BRASS", AE_CL_CREATE_PARTICLE_BRASS)
        .value("AE_RAGDOLL", AE_RAGDOLL)
        .value("AE_CL_ENABLE_BODYGROUP", AE_CL_ENABLE_BODYGROUP)
        .value("AE_CL_DISABLE_BODYGROUP", AE_CL_DISABLE_BODYGROUP)
        .value("AE_CL_BODYGROUP_SET_VALUE", AE_CL_BODYGROUP_SET_VALUE)
        .value("AE_CL_BODYGROUP_SET_VALUE_CMODEL_WPN", AE_CL_BODYGROUP_SET_VALUE_CMODEL_WPN)
        .value("AE_WPN_PRIMARYATTACK", AE_WPN_PRIMARYATTACK)
        .value("AE_WPN_INCREMENTAMMO", AE_WPN_INCREMENTAMMO)
        .value("AE_WPN_HIDE", AE_WPN_HIDE)
        .value("AE_WPN_UNHIDE", AE_WPN_UNHIDE)
        .value("AE_WPN_PLAYWPNSOUND", AE_WPN_PLAYWPNSOUND)
        .value("AE_ASW_FOOTSTEP", AE_ASW_FOOTSTEP)
        .value("AE_MARINE_FOOTSTEP", AE_MARINE_FOOTSTEP)
        .value("AE_MARINE_RELOAD_SOUND_A", AE_MARINE_RELOAD_SOUND_A)
        .value("AE_MARINE_RELOAD_SOUND_B", AE_MARINE_RELOAD_SOUND_B)
        .value("AE_MARINE_RELOAD_SOUND_C", AE_MARINE_RELOAD_SOUND_C)
        .value("AE_REMOVE_CLIENT_AIM", AE_REMOVE_CLIENT_AIM)
        .value("AE_MELEE_DAMAGE", AE_MELEE_DAMAGE)
        .value("AE_MELEE_START_COLLISION_DAMAGE", AE_MELEE_START_COLLISION_DAMAGE)
        .value("AE_MELEE_STOP_COLLISION_DAMAGE", AE_MELEE_STOP_COLLISION_DAMAGE)
        .value("AE_SCREEN_SHAKE", AE_SCREEN_SHAKE)
        .value("AE_START_DETECTING_COMBO", AE_START_DETECTING_COMBO)
        .value("AE_STOP_DETECTING_COMBO", AE_STOP_DETECTING_COMBO)
        .value("AE_COMBO_TRANSITION", AE_COMBO_TRANSITION)
        .value("AE_ALLOW_MOVEMENT", AE_ALLOW_MOVEMENT)
        .value("AE_SKILL_EVENT", AE_SKILL_EVENT)
        .value("AE_TUG_INCAP", AE_TUG_INCAP)
        .value("LAST_SHARED_ANIMEVENT", LAST_SHARED_ANIMEVENT)
        .export_values()
        ;

    { //::ActivityList_IndexForName
    
        typedef int ( *ActivityList_IndexForName_function_type )( char const * );
        
        bp::def( 
            "ActivityList_IndexForName"
            , ActivityList_IndexForName_function_type( &::ActivityList_IndexForName )
            , ( bp::arg("pszActivityName") ) );
    
    }

    { //::ActivityList_NameForIndex
    
        typedef char const * ( *ActivityList_NameForIndex_function_type )( int );
        
        bp::def( 
            "ActivityList_NameForIndex"
            , ActivityList_NameForIndex_function_type( &::ActivityList_NameForIndex )
            , ( bp::arg("iActivityIndex") ) );
    
    }

    { //::ActivityList_RegisterPrivateActivity
    
        typedef ::Activity ( *ActivityList_RegisterPrivateActivity_function_type )( char const * );
        
        bp::def( 
            "ActivityList_RegisterPrivateActivity"
            , ActivityList_RegisterPrivateActivity_function_type( &::ActivityList_RegisterPrivateActivity )
            , ( bp::arg("pszActivityName") ) );
    
    }

    { //::BuildAllAnimationEventIndexes
    
        typedef void ( *BuildAllAnimationEventIndexes_function_type )( ::CStudioHdr * );
        
        bp::def( 
            "BuildAllAnimationEventIndexes"
            , BuildAllAnimationEventIndexes_function_type( &::BuildAllAnimationEventIndexes )
            , ( bp::arg("pstudiohdr") ) );
    
    }

    { //::EventList_IndexForName
    
        typedef int ( *EventList_IndexForName_function_type )( char const * );
        
        bp::def( 
            "EventList_IndexForName"
            , EventList_IndexForName_function_type( &::EventList_IndexForName )
            , ( bp::arg("pszEventName") ) );
    
    }

    { //::EventList_NameForIndex
    
        typedef char const * ( *EventList_NameForIndex_function_type )( int );
        
        bp::def( 
            "EventList_NameForIndex"
            , EventList_NameForIndex_function_type( &::EventList_NameForIndex )
            , ( bp::arg("iEventIndex") ) );
    
    }

    { //::EventList_RegisterPrivateEvent
    
        typedef ::Animevent ( *EventList_RegisterPrivateEvent_function_type )( char const * );
        
        bp::def( 
            "EventList_RegisterPrivateEvent"
            , EventList_RegisterPrivateEvent_function_type( &::EventList_RegisterPrivateEvent )
            , ( bp::arg("pszEventName") ) );
    
    }

    { //::GetAnimationEvent
    
        typedef int ( *GetAnimationEvent_function_type )( ::CStudioHdr *,int,::animevent_t *,float,float,int );
        
        bp::def( 
            "GetAnimationEvent"
            , GetAnimationEvent_function_type( &::GetAnimationEvent )
            , ( bp::arg("pstudiohdr"), bp::arg("sequence"), bp::arg("pNPCEvent"), bp::arg("flStart"), bp::arg("flEnd"), bp::arg("index") ) );
    
    }

    { //::GetSequenceActivityName
    
        typedef char const * ( *GetSequenceActivityName_function_type )( ::CStudioHdr *,int );
        
        bp::def( 
            "GetSequenceActivityName"
            , GetSequenceActivityName_function_type( &::GetSequenceActivityName )
            , ( bp::arg("pstudiohdr"), bp::arg("iSequence") ) );
    
    }

    { //::GetSequenceFlags
    
        typedef int ( *GetSequenceFlags_function_type )( ::CStudioHdr *,int );
        
        bp::def( 
            "GetSequenceFlags"
            , GetSequenceFlags_function_type( &::GetSequenceFlags )
            , ( bp::arg("pstudiohdr"), bp::arg("sequence") ) );
    
    }

    { //::GetSequenceName
    
        typedef char const * ( *GetSequenceName_function_type )( ::CStudioHdr *,int );
        
        bp::def( 
            "GetSequenceName"
            , GetSequenceName_function_type( &::GetSequenceName )
            , ( bp::arg("pstudiohdr"), bp::arg("sequence") ) );
    
    }

    { //::HasAnimationEventOfType
    
        typedef bool ( *HasAnimationEventOfType_function_type )( ::CStudioHdr *,int,int );
        
        bp::def( 
            "HasAnimationEventOfType"
            , HasAnimationEventOfType_function_type( &::HasAnimationEventOfType )
            , ( bp::arg("pstudiohdr"), bp::arg("sequence"), bp::arg("type") ) );
    
    }

    { //::IndexModelSequences
    
        typedef void ( *IndexModelSequences_function_type )( ::CStudioHdr * );
        
        bp::def( 
            "IndexModelSequences"
            , IndexModelSequences_function_type( &::IndexModelSequences )
            , ( bp::arg("pstudiohdr") ) );
    
    }

    { //::LookupActivity
    
        typedef int ( *LookupActivity_function_type )( ::CStudioHdr *,char const * );
        
        bp::def( 
            "LookupActivity"
            , LookupActivity_function_type( &::LookupActivity )
            , ( bp::arg("pstudiohdr"), bp::arg("label") ) );
    
    }

    { //::LookupSequence
    
        typedef int ( *LookupSequence_function_type )( ::CStudioHdr *,char const * );
        
        bp::def( 
            "LookupSequence"
            , LookupSequence_function_type( &::LookupSequence )
            , ( bp::arg("pstudiohdr"), bp::arg("label") ) );
    
    }

    { //::Py_Studio_GetMass
    
        typedef float ( *Studio_GetMass_function_type )( ::CStudioHdr * );
        
        bp::def( 
            "Studio_GetMass"
            , Studio_GetMass_function_type( &::Py_Studio_GetMass )
            , ( bp::arg("pstudiohdr") ) );
    
    }

    { //::ResetActivityIndexes
    
        typedef void ( *ResetActivityIndexes_function_type )( ::CStudioHdr * );
        
        bp::def( 
            "ResetActivityIndexes"
            , ResetActivityIndexes_function_type( &::ResetActivityIndexes )
            , ( bp::arg("pstudiohdr") ) );
    
    }

    { //::ResetEventIndexes
    
        typedef void ( *ResetEventIndexes_function_type )( ::CStudioHdr * );
        
        bp::def( 
            "ResetEventIndexes"
            , ResetEventIndexes_function_type( &::ResetEventIndexes )
            , ( bp::arg("pstudiohdr") ) );
    
    }

    { //::VerifySequenceIndex
    
        typedef void ( *VerifySequenceIndex_function_type )( ::CStudioHdr * );
        
        bp::def( 
            "VerifySequenceIndex"
            , VerifySequenceIndex_function_type( &::VerifySequenceIndex )
            , ( bp::arg("pstudiohdr") ) );
    
    }
}

#else

#include "boost/python.hpp"

#include "bone_setup.h"

#include "eventlist.h"

#include "animation.h"

#include "ai_activity.h"

#include "activitylist.h"

#include "npcevent.h"

#include "srcpy_animation.h"

#include "srcpy.h"

#include "tier0/memdbgon.h"

namespace bp = boost::python;

BOOST_PYTHON_MODULE(_animation){
    bp::docstring_options doc_options( true, true, false );

    bp::enum_< Animevent>("Animevent")
        .value("AE_INVALID", AE_INVALID)
        .value("AE_EMPTY", AE_EMPTY)
        .value("AE_NPC_LEFTFOOT", AE_NPC_LEFTFOOT)
        .value("AE_NPC_RIGHTFOOT", AE_NPC_RIGHTFOOT)
        .value("AE_NPC_BODYDROP_LIGHT", AE_NPC_BODYDROP_LIGHT)
        .value("AE_NPC_BODYDROP_HEAVY", AE_NPC_BODYDROP_HEAVY)
        .value("AE_NPC_SWISHSOUND", AE_NPC_SWISHSOUND)
        .value("AE_NPC_180TURN", AE_NPC_180TURN)
        .value("AE_NPC_ITEM_PICKUP", AE_NPC_ITEM_PICKUP)
        .value("AE_NPC_WEAPON_DROP", AE_NPC_WEAPON_DROP)
        .value("AE_NPC_WEAPON_SET_SEQUENCE_NAME", AE_NPC_WEAPON_SET_SEQUENCE_NAME)
        .value("AE_NPC_WEAPON_SET_SEQUENCE_NUMBER", AE_NPC_WEAPON_SET_SEQUENCE_NUMBER)
        .value("AE_NPC_WEAPON_SET_ACTIVITY", AE_NPC_WEAPON_SET_ACTIVITY)
        .value("AE_NPC_HOLSTER", AE_NPC_HOLSTER)
        .value("AE_NPC_DRAW", AE_NPC_DRAW)
        .value("AE_NPC_WEAPON_FIRE", AE_NPC_WEAPON_FIRE)
        .value("AE_CL_PLAYSOUND", AE_CL_PLAYSOUND)
        .value("AE_SV_PLAYSOUND", AE_SV_PLAYSOUND)
        .value("AE_CL_STOPSOUND", AE_CL_STOPSOUND)
        .value("AE_START_SCRIPTED_EFFECT", AE_START_SCRIPTED_EFFECT)
        .value("AE_STOP_SCRIPTED_EFFECT", AE_STOP_SCRIPTED_EFFECT)
        .value("AE_CLIENT_EFFECT_ATTACH", AE_CLIENT_EFFECT_ATTACH)
        .value("AE_MUZZLEFLASH", AE_MUZZLEFLASH)
        .value("AE_NPC_MUZZLEFLASH", AE_NPC_MUZZLEFLASH)
        .value("AE_THUMPER_THUMP", AE_THUMPER_THUMP)
        .value("AE_AMMOCRATE_PICKUP_AMMO", AE_AMMOCRATE_PICKUP_AMMO)
        .value("AE_NPC_RAGDOLL", AE_NPC_RAGDOLL)
        .value("AE_NPC_ADDGESTURE", AE_NPC_ADDGESTURE)
        .value("AE_NPC_RESTARTGESTURE", AE_NPC_RESTARTGESTURE)
        .value("AE_NPC_ATTACK_BROADCAST", AE_NPC_ATTACK_BROADCAST)
        .value("AE_NPC_HURT_INTERACTION_PARTNER", AE_NPC_HURT_INTERACTION_PARTNER)
        .value("AE_NPC_SET_INTERACTION_CANTDIE", AE_NPC_SET_INTERACTION_CANTDIE)
        .value("AE_SV_DUSTTRAIL", AE_SV_DUSTTRAIL)
        .value("AE_CL_CREATE_PARTICLE_EFFECT", AE_CL_CREATE_PARTICLE_EFFECT)
        .value("AE_CL_STOP_PARTICLE_EFFECT", AE_CL_STOP_PARTICLE_EFFECT)
        .value("AE_CL_ADD_PARTICLE_EFFECT_CP", AE_CL_ADD_PARTICLE_EFFECT_CP)
        .value("AE_CL_CREATE_PARTICLE_BRASS", AE_CL_CREATE_PARTICLE_BRASS)
        .value("AE_RAGDOLL", AE_RAGDOLL)
        .value("AE_CL_ENABLE_BODYGROUP", AE_CL_ENABLE_BODYGROUP)
        .value("AE_CL_DISABLE_BODYGROUP", AE_CL_DISABLE_BODYGROUP)
        .value("AE_CL_BODYGROUP_SET_VALUE", AE_CL_BODYGROUP_SET_VALUE)
        .value("AE_CL_BODYGROUP_SET_VALUE_CMODEL_WPN", AE_CL_BODYGROUP_SET_VALUE_CMODEL_WPN)
        .value("AE_WPN_PRIMARYATTACK", AE_WPN_PRIMARYATTACK)
        .value("AE_WPN_INCREMENTAMMO", AE_WPN_INCREMENTAMMO)
        .value("AE_WPN_HIDE", AE_WPN_HIDE)
        .value("AE_WPN_UNHIDE", AE_WPN_UNHIDE)
        .value("AE_WPN_PLAYWPNSOUND", AE_WPN_PLAYWPNSOUND)
        .value("AE_ASW_FOOTSTEP", AE_ASW_FOOTSTEP)
        .value("AE_MARINE_FOOTSTEP", AE_MARINE_FOOTSTEP)
        .value("AE_MARINE_RELOAD_SOUND_A", AE_MARINE_RELOAD_SOUND_A)
        .value("AE_MARINE_RELOAD_SOUND_B", AE_MARINE_RELOAD_SOUND_B)
        .value("AE_MARINE_RELOAD_SOUND_C", AE_MARINE_RELOAD_SOUND_C)
        .value("AE_REMOVE_CLIENT_AIM", AE_REMOVE_CLIENT_AIM)
        .value("AE_MELEE_DAMAGE", AE_MELEE_DAMAGE)
        .value("AE_MELEE_START_COLLISION_DAMAGE", AE_MELEE_START_COLLISION_DAMAGE)
        .value("AE_MELEE_STOP_COLLISION_DAMAGE", AE_MELEE_STOP_COLLISION_DAMAGE)
        .value("AE_SCREEN_SHAKE", AE_SCREEN_SHAKE)
        .value("AE_START_DETECTING_COMBO", AE_START_DETECTING_COMBO)
        .value("AE_STOP_DETECTING_COMBO", AE_STOP_DETECTING_COMBO)
        .value("AE_COMBO_TRANSITION", AE_COMBO_TRANSITION)
        .value("AE_ALLOW_MOVEMENT", AE_ALLOW_MOVEMENT)
        .value("AE_SKILL_EVENT", AE_SKILL_EVENT)
        .value("AE_TUG_INCAP", AE_TUG_INCAP)
        .value("LAST_SHARED_ANIMEVENT", LAST_SHARED_ANIMEVENT)
        .export_values()
        ;

    { //::ActivityList_IndexForName
    
        typedef int ( *ActivityList_IndexForName_function_type )( char const * );
        
        bp::def( 
            "ActivityList_IndexForName"
            , ActivityList_IndexForName_function_type( &::ActivityList_IndexForName )
            , ( bp::arg("pszActivityName") ) );
    
    }

    { //::ActivityList_NameForIndex
    
        typedef char const * ( *ActivityList_NameForIndex_function_type )( int );
        
        bp::def( 
            "ActivityList_NameForIndex"
            , ActivityList_NameForIndex_function_type( &::ActivityList_NameForIndex )
            , ( bp::arg("iActivityIndex") ) );
    
    }

    { //::ActivityList_RegisterPrivateActivity
    
        typedef ::Activity ( *ActivityList_RegisterPrivateActivity_function_type )( char const * );
        
        bp::def( 
            "ActivityList_RegisterPrivateActivity"
            , ActivityList_RegisterPrivateActivity_function_type( &::ActivityList_RegisterPrivateActivity )
            , ( bp::arg("pszActivityName") ) );
    
    }

    { //::BuildAllAnimationEventIndexes
    
        typedef void ( *BuildAllAnimationEventIndexes_function_type )( ::CStudioHdr * );
        
        bp::def( 
            "BuildAllAnimationEventIndexes"
            , BuildAllAnimationEventIndexes_function_type( &::BuildAllAnimationEventIndexes )
            , ( bp::arg("pstudiohdr") ) );
    
    }

    { //::EventList_IndexForName
    
        typedef int ( *EventList_IndexForName_function_type )( char const * );
        
        bp::def( 
            "EventList_IndexForName"
            , EventList_IndexForName_function_type( &::EventList_IndexForName )
            , ( bp::arg("pszEventName") ) );
    
    }

    { //::EventList_NameForIndex
    
        typedef char const * ( *EventList_NameForIndex_function_type )( int );
        
        bp::def( 
            "EventList_NameForIndex"
            , EventList_NameForIndex_function_type( &::EventList_NameForIndex )
            , ( bp::arg("iEventIndex") ) );
    
    }

    { //::EventList_RegisterPrivateEvent
    
        typedef ::Animevent ( *EventList_RegisterPrivateEvent_function_type )( char const * );
        
        bp::def( 
            "EventList_RegisterPrivateEvent"
            , EventList_RegisterPrivateEvent_function_type( &::EventList_RegisterPrivateEvent )
            , ( bp::arg("pszEventName") ) );
    
    }

    { //::GetAnimationEvent
    
        typedef int ( *GetAnimationEvent_function_type )( ::CStudioHdr *,int,::animevent_t *,float,float,int );
        
        bp::def( 
            "GetAnimationEvent"
            , GetAnimationEvent_function_type( &::GetAnimationEvent )
            , ( bp::arg("pstudiohdr"), bp::arg("sequence"), bp::arg("pNPCEvent"), bp::arg("flStart"), bp::arg("flEnd"), bp::arg("index") ) );
    
    }

    { //::GetSequenceActivityName
    
        typedef char const * ( *GetSequenceActivityName_function_type )( ::CStudioHdr *,int );
        
        bp::def( 
            "GetSequenceActivityName"
            , GetSequenceActivityName_function_type( &::GetSequenceActivityName )
            , ( bp::arg("pstudiohdr"), bp::arg("iSequence") ) );
    
    }

    { //::GetSequenceFlags
    
        typedef int ( *GetSequenceFlags_function_type )( ::CStudioHdr *,int );
        
        bp::def( 
            "GetSequenceFlags"
            , GetSequenceFlags_function_type( &::GetSequenceFlags )
            , ( bp::arg("pstudiohdr"), bp::arg("sequence") ) );
    
    }

    { //::GetSequenceName
    
        typedef char const * ( *GetSequenceName_function_type )( ::CStudioHdr *,int );
        
        bp::def( 
            "GetSequenceName"
            , GetSequenceName_function_type( &::GetSequenceName )
            , ( bp::arg("pstudiohdr"), bp::arg("sequence") ) );
    
    }

    { //::HasAnimationEventOfType
    
        typedef bool ( *HasAnimationEventOfType_function_type )( ::CStudioHdr *,int,int );
        
        bp::def( 
            "HasAnimationEventOfType"
            , HasAnimationEventOfType_function_type( &::HasAnimationEventOfType )
            , ( bp::arg("pstudiohdr"), bp::arg("sequence"), bp::arg("type") ) );
    
    }

    { //::IndexModelSequences
    
        typedef void ( *IndexModelSequences_function_type )( ::CStudioHdr * );
        
        bp::def( 
            "IndexModelSequences"
            , IndexModelSequences_function_type( &::IndexModelSequences )
            , ( bp::arg("pstudiohdr") ) );
    
    }

    { //::LookupActivity
    
        typedef int ( *LookupActivity_function_type )( ::CStudioHdr *,char const * );
        
        bp::def( 
            "LookupActivity"
            , LookupActivity_function_type( &::LookupActivity )
            , ( bp::arg("pstudiohdr"), bp::arg("label") ) );
    
    }

    { //::LookupSequence
    
        typedef int ( *LookupSequence_function_type )( ::CStudioHdr *,char const * );
        
        bp::def( 
            "LookupSequence"
            , LookupSequence_function_type( &::LookupSequence )
            , ( bp::arg("pstudiohdr"), bp::arg("label") ) );
    
    }

    { //::Py_Studio_GetMass
    
        typedef float ( *Studio_GetMass_function_type )( ::CStudioHdr * );
        
        bp::def( 
            "Studio_GetMass"
            , Studio_GetMass_function_type( &::Py_Studio_GetMass )
            , ( bp::arg("pstudiohdr") ) );
    
    }

    { //::ResetActivityIndexes
    
        typedef void ( *ResetActivityIndexes_function_type )( ::CStudioHdr * );
        
        bp::def( 
            "ResetActivityIndexes"
            , ResetActivityIndexes_function_type( &::ResetActivityIndexes )
            , ( bp::arg("pstudiohdr") ) );
    
    }

    { //::ResetEventIndexes
    
        typedef void ( *ResetEventIndexes_function_type )( ::CStudioHdr * );
        
        bp::def( 
            "ResetEventIndexes"
            , ResetEventIndexes_function_type( &::ResetEventIndexes )
            , ( bp::arg("pstudiohdr") ) );
    
    }

    { //::VerifySequenceIndex
    
        typedef void ( *VerifySequenceIndex_function_type )( ::CStudioHdr * );
        
        bp::def( 
            "VerifySequenceIndex"
            , VerifySequenceIndex_function_type( &::VerifySequenceIndex )
            , ( bp::arg("pstudiohdr") ) );
    
    }
}

#endif // CLIENT_DLL



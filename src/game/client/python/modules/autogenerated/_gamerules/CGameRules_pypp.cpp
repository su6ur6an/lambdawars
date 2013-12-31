// This file has been generated by Py++.

#include "cbase.h"
// This file has been generated by Py++.

#include "cbase.h"
#include "gamerules.h"
#include "multiplay_gamerules.h"
#include "singleplay_gamerules.h"
#include "teamplay_gamerules.h"
#include "srcpy_gamerules.h"
#include "ammodef.h"
#include "takedamageinfo.h"
#include "hl2wars_gamerules.h"
#include "srcpy.h"
#include "tier0/memdbgon.h"
#include "CGameRules_pypp.hpp"

namespace bp = boost::python;

struct C_GameRules_wrapper : C_GameRules, bp::wrapper< C_GameRules > {

    C_GameRules_wrapper( )
    : C_GameRules( )
      , bp::wrapper< C_GameRules >(){
        // null constructor
    
    }

    virtual void ClientCommandKeyValues( ::edict_t * pEntity, ::KeyValues * pKeyValues ) {
        PY_OVERRIDE_CHECK( C_GameRules, ClientCommandKeyValues )
        PY_OVERRIDE_LOG( _gamerules, C_GameRules, ClientCommandKeyValues )
        bp::override func_ClientCommandKeyValues = this->get_override( "ClientCommandKeyValues" );
        if( func_ClientCommandKeyValues.ptr() != Py_None )
            try {
                func_ClientCommandKeyValues( boost::python::ptr(pEntity), boost::python::ptr(pKeyValues) );
            } catch(bp::error_already_set &) {
                PyErr_Print();
                this->C_GameRules::ClientCommandKeyValues( pEntity, pKeyValues );
            }
        else
            this->C_GameRules::ClientCommandKeyValues( pEntity, pKeyValues );
    }
    
    void default_ClientCommandKeyValues( ::edict_t * pEntity, ::KeyValues * pKeyValues ) {
        C_GameRules::ClientCommandKeyValues( pEntity, pKeyValues );
    }

    virtual int Damage_GetNoPhysicsForce(  ){
        bp::override func_Damage_GetNoPhysicsForce = this->get_override( "Damage_GetNoPhysicsForce" );
        try {
            return func_Damage_GetNoPhysicsForce(  );
        } catch(bp::error_already_set &) {
            throw boost::python::error_already_set();
        }
    }

    virtual int Damage_GetShouldGibCorpse(  ){
        bp::override func_Damage_GetShouldGibCorpse = this->get_override( "Damage_GetShouldGibCorpse" );
        try {
            return func_Damage_GetShouldGibCorpse(  );
        } catch(bp::error_already_set &) {
            throw boost::python::error_already_set();
        }
    }

    virtual int Damage_GetShouldNotBleed(  ){
        bp::override func_Damage_GetShouldNotBleed = this->get_override( "Damage_GetShouldNotBleed" );
        try {
            return func_Damage_GetShouldNotBleed(  );
        } catch(bp::error_already_set &) {
            throw boost::python::error_already_set();
        }
    }

    virtual int Damage_GetShowOnHud(  ){
        bp::override func_Damage_GetShowOnHud = this->get_override( "Damage_GetShowOnHud" );
        try {
            return func_Damage_GetShowOnHud(  );
        } catch(bp::error_already_set &) {
            throw boost::python::error_already_set();
        }
    }

    virtual int Damage_GetTimeBased(  ){
        bp::override func_Damage_GetTimeBased = this->get_override( "Damage_GetTimeBased" );
        try {
            return func_Damage_GetTimeBased(  );
        } catch(bp::error_already_set &) {
            throw boost::python::error_already_set();
        }
    }

    virtual bool Damage_IsTimeBased( int iDmgType ){
        bp::override func_Damage_IsTimeBased = this->get_override( "Damage_IsTimeBased" );
        try {
            return func_Damage_IsTimeBased( iDmgType );
        } catch(bp::error_already_set &) {
            throw boost::python::error_already_set();
        }
    }

    virtual bool Damage_NoPhysicsForce( int iDmgType ){
        bp::override func_Damage_NoPhysicsForce = this->get_override( "Damage_NoPhysicsForce" );
        try {
            return func_Damage_NoPhysicsForce( iDmgType );
        } catch(bp::error_already_set &) {
            throw boost::python::error_already_set();
        }
    }

    virtual bool Damage_ShouldGibCorpse( int iDmgType ){
        bp::override func_Damage_ShouldGibCorpse = this->get_override( "Damage_ShouldGibCorpse" );
        try {
            return func_Damage_ShouldGibCorpse( iDmgType );
        } catch(bp::error_already_set &) {
            throw boost::python::error_already_set();
        }
    }

    virtual bool Damage_ShouldNotBleed( int iDmgType ){
        bp::override func_Damage_ShouldNotBleed = this->get_override( "Damage_ShouldNotBleed" );
        try {
            return func_Damage_ShouldNotBleed( iDmgType );
        } catch(bp::error_already_set &) {
            throw boost::python::error_already_set();
        }
    }

    virtual bool Damage_ShowOnHUD( int iDmgType ){
        bp::override func_Damage_ShowOnHUD = this->get_override( "Damage_ShowOnHUD" );
        try {
            return func_Damage_ShowOnHUD( iDmgType );
        } catch(bp::error_already_set &) {
            throw boost::python::error_already_set();
        }
    }

    virtual int DefaultFOV(  ) {
        PY_OVERRIDE_CHECK( C_GameRules, DefaultFOV )
        PY_OVERRIDE_LOG( _gamerules, C_GameRules, DefaultFOV )
        bp::override func_DefaultFOV = this->get_override( "DefaultFOV" );
        if( func_DefaultFOV.ptr() != Py_None )
            try {
                return func_DefaultFOV(  );
            } catch(bp::error_already_set &) {
                PyErr_Print();
                return this->C_GameRules::DefaultFOV(  );
            }
        else
            return this->C_GameRules::DefaultFOV(  );
    }
    
    int default_DefaultFOV(  ) {
        return C_GameRules::DefaultFOV( );
    }

    virtual bool ForceSplitScreenPlayersOnToSameTeam(  ) {
        PY_OVERRIDE_CHECK( C_GameRules, ForceSplitScreenPlayersOnToSameTeam )
        PY_OVERRIDE_LOG( _gamerules, C_GameRules, ForceSplitScreenPlayersOnToSameTeam )
        bp::override func_ForceSplitScreenPlayersOnToSameTeam = this->get_override( "ForceSplitScreenPlayersOnToSameTeam" );
        if( func_ForceSplitScreenPlayersOnToSameTeam.ptr() != Py_None )
            try {
                return func_ForceSplitScreenPlayersOnToSameTeam(  );
            } catch(bp::error_already_set &) {
                PyErr_Print();
                return this->C_GameRules::ForceSplitScreenPlayersOnToSameTeam(  );
            }
        else
            return this->C_GameRules::ForceSplitScreenPlayersOnToSameTeam(  );
    }
    
    bool default_ForceSplitScreenPlayersOnToSameTeam(  ) {
        return C_GameRules::ForceSplitScreenPlayersOnToSameTeam( );
    }

    virtual float GetDamageMultiplier(  ) {
        PY_OVERRIDE_CHECK( C_GameRules, GetDamageMultiplier )
        PY_OVERRIDE_LOG( _gamerules, C_GameRules, GetDamageMultiplier )
        bp::override func_GetDamageMultiplier = this->get_override( "GetDamageMultiplier" );
        if( func_GetDamageMultiplier.ptr() != Py_None )
            try {
                return func_GetDamageMultiplier(  );
            } catch(bp::error_already_set &) {
                PyErr_Print();
                return this->C_GameRules::GetDamageMultiplier(  );
            }
        else
            return this->C_GameRules::GetDamageMultiplier(  );
    }
    
    float default_GetDamageMultiplier(  ) {
        return C_GameRules::GetDamageMultiplier( );
    }

    virtual int GetGameType(  ) {
        PY_OVERRIDE_CHECK( C_GameRules, GetGameType )
        PY_OVERRIDE_LOG( _gamerules, C_GameRules, GetGameType )
        bp::override func_GetGameType = this->get_override( "GetGameType" );
        if( func_GetGameType.ptr() != Py_None )
            try {
                return func_GetGameType(  );
            } catch(bp::error_already_set &) {
                PyErr_Print();
                return this->C_GameRules::GetGameType(  );
            }
        else
            return this->C_GameRules::GetGameType(  );
    }
    
    int default_GetGameType(  ) {
        return C_GameRules::GetGameType( );
    }

    virtual char const * GetGameTypeName(  ) {
        PY_OVERRIDE_CHECK( C_GameRules, GetGameTypeName )
        PY_OVERRIDE_LOG( _gamerules, C_GameRules, GetGameTypeName )
        bp::override func_GetGameTypeName = this->get_override( "GetGameTypeName" );
        if( func_GetGameTypeName.ptr() != Py_None )
            try {
                return func_GetGameTypeName(  );
            } catch(bp::error_already_set &) {
                PyErr_Print();
                return this->C_GameRules::GetGameTypeName(  );
            }
        else
            return this->C_GameRules::GetGameTypeName(  );
    }
    
    char const * default_GetGameTypeName(  ) {
        return C_GameRules::GetGameTypeName( );
    }

    virtual int GetMaxHumanPlayers(  ) const  {
        PY_OVERRIDE_CHECK( C_GameRules, GetMaxHumanPlayers )
        PY_OVERRIDE_LOG( _gamerules, C_GameRules, GetMaxHumanPlayers )
        bp::override func_GetMaxHumanPlayers = this->get_override( "GetMaxHumanPlayers" );
        if( func_GetMaxHumanPlayers.ptr() != Py_None )
            try {
                return func_GetMaxHumanPlayers(  );
            } catch(bp::error_already_set &) {
                PyErr_Print();
                return this->C_GameRules::GetMaxHumanPlayers(  );
            }
        else
            return this->C_GameRules::GetMaxHumanPlayers(  );
    }
    
    int default_GetMaxHumanPlayers(  ) const  {
        return C_GameRules::GetMaxHumanPlayers( );
    }

    virtual ::C_BaseCombatWeapon * GetNextBestWeapon( ::C_BaseCombatCharacter * pPlayer, ::C_BaseCombatWeapon * pCurrentWeapon ) {
        PY_OVERRIDE_CHECK( C_GameRules, GetNextBestWeapon )
        PY_OVERRIDE_LOG( _gamerules, C_GameRules, GetNextBestWeapon )
        bp::override func_GetNextBestWeapon = this->get_override( "GetNextBestWeapon" );
        if( func_GetNextBestWeapon.ptr() != Py_None )
            try {
                return func_GetNextBestWeapon( pPlayer ? pPlayer->GetPyHandle() : boost::python::object(), pCurrentWeapon ? pCurrentWeapon->GetPyHandle() : boost::python::object() );
            } catch(bp::error_already_set &) {
                PyErr_Print();
                return this->C_GameRules::GetNextBestWeapon( pPlayer, pCurrentWeapon );
            }
        else
            return this->C_GameRules::GetNextBestWeapon( pPlayer, pCurrentWeapon );
    }
    
    ::C_BaseCombatWeapon * default_GetNextBestWeapon( ::C_BaseCombatCharacter * pPlayer, ::C_BaseCombatWeapon * pCurrentWeapon ) {
        return C_GameRules::GetNextBestWeapon( pPlayer, pCurrentWeapon );
    }

    virtual bool InRoundRestart(  ) {
        PY_OVERRIDE_CHECK( C_GameRules, InRoundRestart )
        PY_OVERRIDE_LOG( _gamerules, C_GameRules, InRoundRestart )
        bp::override func_InRoundRestart = this->get_override( "InRoundRestart" );
        if( func_InRoundRestart.ptr() != Py_None )
            try {
                return func_InRoundRestart(  );
            } catch(bp::error_already_set &) {
                PyErr_Print();
                return this->C_GameRules::InRoundRestart(  );
            }
        else
            return this->C_GameRules::InRoundRestart(  );
    }
    
    bool default_InRoundRestart(  ) {
        return C_GameRules::InRoundRestart( );
    }

    virtual bool Init(  ) {
        PY_OVERRIDE_CHECK( C_GameRules, Init )
        PY_OVERRIDE_LOG( _gamerules, C_GameRules, Init )
        bp::override func_Init = this->get_override( "Init" );
        if( func_Init.ptr() != Py_None )
            try {
                return func_Init(  );
            } catch(bp::error_already_set &) {
                PyErr_Print();
                return this->C_GameRules::Init(  );
            }
        else
            return this->C_GameRules::Init(  );
    }
    
    bool default_Init(  ) {
        return C_GameRules::Init( );
    }

    virtual void InitGamerules(  ) {
        PY_OVERRIDE_CHECK( C_GameRules, InitGamerules )
        PY_OVERRIDE_LOG( _gamerules, C_GameRules, InitGamerules )
        bp::override func_InitGamerules = this->get_override( "InitGamerules" );
        if( func_InitGamerules.ptr() != Py_None )
            try {
                func_InitGamerules(  );
            } catch(bp::error_already_set &) {
                PyErr_Print();
                this->C_GameRules::InitGamerules(  );
            }
        else
            this->C_GameRules::InitGamerules(  );
    }
    
    void default_InitGamerules(  ) {
        C_GameRules::InitGamerules( );
    }

    virtual bool IsBonusChallengeTimeBased(  ) {
        PY_OVERRIDE_CHECK( C_GameRules, IsBonusChallengeTimeBased )
        PY_OVERRIDE_LOG( _gamerules, C_GameRules, IsBonusChallengeTimeBased )
        bp::override func_IsBonusChallengeTimeBased = this->get_override( "IsBonusChallengeTimeBased" );
        if( func_IsBonusChallengeTimeBased.ptr() != Py_None )
            try {
                return func_IsBonusChallengeTimeBased(  );
            } catch(bp::error_already_set &) {
                PyErr_Print();
                return this->C_GameRules::IsBonusChallengeTimeBased(  );
            }
        else
            return this->C_GameRules::IsBonusChallengeTimeBased(  );
    }
    
    bool default_IsBonusChallengeTimeBased(  ) {
        return C_GameRules::IsBonusChallengeTimeBased( );
    }

    virtual bool IsMultiplayer(  ){
        bp::override func_IsMultiplayer = this->get_override( "IsMultiplayer" );
        try {
            return func_IsMultiplayer(  );
        } catch(bp::error_already_set &) {
            throw boost::python::error_already_set();
        }
    }

    virtual bool IsTopDown(  ) {
        PY_OVERRIDE_CHECK( C_GameRules, IsTopDown )
        PY_OVERRIDE_LOG( _gamerules, C_GameRules, IsTopDown )
        bp::override func_IsTopDown = this->get_override( "IsTopDown" );
        if( func_IsTopDown.ptr() != Py_None )
            try {
                return func_IsTopDown(  );
            } catch(bp::error_already_set &) {
                PyErr_Print();
                return this->C_GameRules::IsTopDown(  );
            }
        else
            return this->C_GameRules::IsTopDown(  );
    }
    
    bool default_IsTopDown(  ) {
        return C_GameRules::IsTopDown( );
    }

    virtual char const * Name(  ) {
        PY_OVERRIDE_CHECK( C_GameRules, Name )
        PY_OVERRIDE_LOG( _gamerules, C_GameRules, Name )
        bp::override func_Name = this->get_override( "Name" );
        if( func_Name.ptr() != Py_None )
            try {
                return func_Name(  );
            } catch(bp::error_already_set &) {
                PyErr_Print();
                return this->C_GameRules::Name(  );
            }
        else
            return this->C_GameRules::Name(  );
    }
    
    char const * default_Name(  ) {
        return C_GameRules::Name( );
    }

    virtual void OnNavMeshLoad(  ) {
        PY_OVERRIDE_CHECK( C_GameRules, OnNavMeshLoad )
        PY_OVERRIDE_LOG( _gamerules, C_GameRules, OnNavMeshLoad )
        bp::override func_OnNavMeshLoad = this->get_override( "OnNavMeshLoad" );
        if( func_OnNavMeshLoad.ptr() != Py_None )
            try {
                func_OnNavMeshLoad(  );
            } catch(bp::error_already_set &) {
                PyErr_Print();
                this->C_GameRules::OnNavMeshLoad(  );
            }
        else
            this->C_GameRules::OnNavMeshLoad(  );
    }
    
    void default_OnNavMeshLoad(  ) {
        C_GameRules::OnNavMeshLoad( );
    }

    virtual void RegisterScriptFunctions(  ) {
        PY_OVERRIDE_CHECK( C_GameRules, RegisterScriptFunctions )
        PY_OVERRIDE_LOG( _gamerules, C_GameRules, RegisterScriptFunctions )
        bp::override func_RegisterScriptFunctions = this->get_override( "RegisterScriptFunctions" );
        if( func_RegisterScriptFunctions.ptr() != Py_None )
            try {
                func_RegisterScriptFunctions(  );
            } catch(bp::error_already_set &) {
                PyErr_Print();
                this->C_GameRules::RegisterScriptFunctions(  );
            }
        else
            this->C_GameRules::RegisterScriptFunctions(  );
    }
    
    void default_RegisterScriptFunctions(  ) {
        C_GameRules::RegisterScriptFunctions( );
    }

    virtual void ShutdownGamerules(  ) {
        PY_OVERRIDE_CHECK( C_GameRules, ShutdownGamerules )
        PY_OVERRIDE_LOG( _gamerules, C_GameRules, ShutdownGamerules )
        bp::override func_ShutdownGamerules = this->get_override( "ShutdownGamerules" );
        if( func_ShutdownGamerules.ptr() != Py_None )
            try {
                func_ShutdownGamerules(  );
            } catch(bp::error_already_set &) {
                PyErr_Print();
                this->C_GameRules::ShutdownGamerules(  );
            }
        else
            this->C_GameRules::ShutdownGamerules(  );
    }
    
    void default_ShutdownGamerules(  ) {
        C_GameRules::ShutdownGamerules( );
    }

    virtual bool SwitchToNextBestWeapon( ::C_BaseCombatCharacter * pPlayer, ::C_BaseCombatWeapon * pCurrentWeapon ) {
        PY_OVERRIDE_CHECK( C_GameRules, SwitchToNextBestWeapon )
        PY_OVERRIDE_LOG( _gamerules, C_GameRules, SwitchToNextBestWeapon )
        bp::override func_SwitchToNextBestWeapon = this->get_override( "SwitchToNextBestWeapon" );
        if( func_SwitchToNextBestWeapon.ptr() != Py_None )
            try {
                return func_SwitchToNextBestWeapon( pPlayer ? pPlayer->GetPyHandle() : boost::python::object(), pCurrentWeapon ? pCurrentWeapon->GetPyHandle() : boost::python::object() );
            } catch(bp::error_already_set &) {
                PyErr_Print();
                return this->C_GameRules::SwitchToNextBestWeapon( pPlayer, pCurrentWeapon );
            }
        else
            return this->C_GameRules::SwitchToNextBestWeapon( pPlayer, pCurrentWeapon );
    }
    
    bool default_SwitchToNextBestWeapon( ::C_BaseCombatCharacter * pPlayer, ::C_BaseCombatWeapon * pCurrentWeapon ) {
        return C_GameRules::SwitchToNextBestWeapon( pPlayer, pCurrentWeapon );
    }

};

void register_CGameRules_class(){

    bp::class_< C_GameRules_wrapper, boost::noncopyable >( "CGameRules", bp::no_init )    
        .def( bp::init< >() )    
        .def( 
            "ClientCommandKeyValues"
            , (void ( ::C_GameRules::* )( ::edict_t *,::KeyValues * ) )(&::C_GameRules::ClientCommandKeyValues)
            , (void ( C_GameRules_wrapper::* )( ::edict_t *,::KeyValues * ) )(&C_GameRules_wrapper::default_ClientCommandKeyValues)
            , ( bp::arg("pEntity"), bp::arg("pKeyValues") ) )    
        .def( 
            "Damage_GetNoPhysicsForce"
            , bp::pure_virtual( (int ( ::C_GameRules::* )(  ) )(&::C_GameRules::Damage_GetNoPhysicsForce) ) )    
        .def( 
            "Damage_GetShouldGibCorpse"
            , bp::pure_virtual( (int ( ::C_GameRules::* )(  ) )(&::C_GameRules::Damage_GetShouldGibCorpse) ) )    
        .def( 
            "Damage_GetShouldNotBleed"
            , bp::pure_virtual( (int ( ::C_GameRules::* )(  ) )(&::C_GameRules::Damage_GetShouldNotBleed) ) )    
        .def( 
            "Damage_GetShowOnHud"
            , bp::pure_virtual( (int ( ::C_GameRules::* )(  ) )(&::C_GameRules::Damage_GetShowOnHud) ) )    
        .def( 
            "Damage_GetTimeBased"
            , bp::pure_virtual( (int ( ::C_GameRules::* )(  ) )(&::C_GameRules::Damage_GetTimeBased) ) )    
        .def( 
            "Damage_IsTimeBased"
            , bp::pure_virtual( (bool ( ::C_GameRules::* )( int ) )(&::C_GameRules::Damage_IsTimeBased) )
            , ( bp::arg("iDmgType") ) )    
        .def( 
            "Damage_NoPhysicsForce"
            , bp::pure_virtual( (bool ( ::C_GameRules::* )( int ) )(&::C_GameRules::Damage_NoPhysicsForce) )
            , ( bp::arg("iDmgType") ) )    
        .def( 
            "Damage_ShouldGibCorpse"
            , bp::pure_virtual( (bool ( ::C_GameRules::* )( int ) )(&::C_GameRules::Damage_ShouldGibCorpse) )
            , ( bp::arg("iDmgType") ) )    
        .def( 
            "Damage_ShouldNotBleed"
            , bp::pure_virtual( (bool ( ::C_GameRules::* )( int ) )(&::C_GameRules::Damage_ShouldNotBleed) )
            , ( bp::arg("iDmgType") ) )    
        .def( 
            "Damage_ShowOnHUD"
            , bp::pure_virtual( (bool ( ::C_GameRules::* )( int ) )(&::C_GameRules::Damage_ShowOnHUD) )
            , ( bp::arg("iDmgType") ) )    
        .def( 
            "DefaultFOV"
            , (int ( ::C_GameRules::* )(  ) )(&::C_GameRules::DefaultFOV)
            , (int ( C_GameRules_wrapper::* )(  ) )(&C_GameRules_wrapper::default_DefaultFOV) )    
        .def( 
            "ForceSplitScreenPlayersOnToSameTeam"
            , (bool ( ::C_GameRules::* )(  ) )(&::C_GameRules::ForceSplitScreenPlayersOnToSameTeam)
            , (bool ( C_GameRules_wrapper::* )(  ) )(&C_GameRules_wrapper::default_ForceSplitScreenPlayersOnToSameTeam) )    
        .def( 
            "GetAmmoDamage"
            , (float ( ::C_GameRules::* )( ::C_BaseEntity *,::C_BaseEntity *,int ) )( &::C_GameRules::GetAmmoDamage )
            , ( bp::arg("pAttacker"), bp::arg("pVictim"), bp::arg("nAmmoType") ) )    
        .def( 
            "GetDamageMultiplier"
            , (float ( ::C_GameRules::* )(  ) )(&::C_GameRules::GetDamageMultiplier)
            , (float ( C_GameRules_wrapper::* )(  ) )(&C_GameRules_wrapper::default_GetDamageMultiplier) )    
        .def( 
            "GetGameType"
            , (int ( ::C_GameRules::* )(  ) )(&::C_GameRules::GetGameType)
            , (int ( C_GameRules_wrapper::* )(  ) )(&C_GameRules_wrapper::default_GetGameType) )    
        .def( 
            "GetGameTypeName"
            , (char const * ( ::C_GameRules::* )(  ) )(&::C_GameRules::GetGameTypeName)
            , (char const * ( C_GameRules_wrapper::* )(  ) )(&C_GameRules_wrapper::default_GetGameTypeName) )    
        .def( 
            "GetMaxHumanPlayers"
            , (int ( ::C_GameRules::* )(  ) const)(&::C_GameRules::GetMaxHumanPlayers)
            , (int ( C_GameRules_wrapper::* )(  ) const)(&C_GameRules_wrapper::default_GetMaxHumanPlayers) )    
        .def( 
            "GetNextBestWeapon"
            , (::C_BaseCombatWeapon * ( ::C_GameRules::* )( ::C_BaseCombatCharacter *,::C_BaseCombatWeapon * ) )(&::C_GameRules::GetNextBestWeapon)
            , (::C_BaseCombatWeapon * ( C_GameRules_wrapper::* )( ::C_BaseCombatCharacter *,::C_BaseCombatWeapon * ) )(&C_GameRules_wrapper::default_GetNextBestWeapon)
            , ( bp::arg("pPlayer"), bp::arg("pCurrentWeapon") )
            , bp::return_value_policy< bp::return_by_value >() )    
        .def( 
            "GetTopDownMovementAxis"
            , (::QAngle const & ( ::C_GameRules::* )(  ) )(&::C_GameRules::GetTopDownMovementAxis)
            , bp::return_value_policy< bp::copy_const_reference >() )    
        .def( 
            "InRoundRestart"
            , (bool ( ::C_GameRules::* )(  ) )(&::C_GameRules::InRoundRestart)
            , (bool ( C_GameRules_wrapper::* )(  ) )(&C_GameRules_wrapper::default_InRoundRestart) )    
        .def( 
            "Init"
            , (bool ( ::C_GameRules::* )(  ) )(&::C_GameRules::Init)
            , (bool ( C_GameRules_wrapper::* )(  ) )(&C_GameRules_wrapper::default_Init) )    
        .def( 
            "InitGamerules"
            , (void ( ::C_GameRules::* )(  ) )(&::C_GameRules::InitGamerules)
            , (void ( C_GameRules_wrapper::* )(  ) )(&C_GameRules_wrapper::default_InitGamerules) )    
        .def( 
            "IsBonusChallengeTimeBased"
            , (bool ( ::C_GameRules::* )(  ) )(&::C_GameRules::IsBonusChallengeTimeBased)
            , (bool ( C_GameRules_wrapper::* )(  ) )(&C_GameRules_wrapper::default_IsBonusChallengeTimeBased) )    
        .def( 
            "IsMultiplayer"
            , bp::pure_virtual( (bool ( ::C_GameRules::* )(  ) )(&::C_GameRules::IsMultiplayer) ) )    
        .def( 
            "IsTopDown"
            , (bool ( ::C_GameRules::* )(  ) )(&::C_GameRules::IsTopDown)
            , (bool ( C_GameRules_wrapper::* )(  ) )(&C_GameRules_wrapper::default_IsTopDown) )    
        .def( 
            "Name"
            , (char const * ( ::C_GameRules::* )(  ) )(&::C_GameRules::Name)
            , (char const * ( C_GameRules_wrapper::* )(  ) )(&C_GameRules_wrapper::default_Name) )    
        .def( 
            "NetworkStateChanged"
            , (void ( ::C_GameRules::* )(  ) )( &::C_GameRules::NetworkStateChanged ) )    
        .def( 
            "NetworkStateChanged"
            , (void ( ::C_GameRules::* )( void * ) )( &::C_GameRules::NetworkStateChanged )
            , ( bp::arg("pVar") ) )    
        .def( 
            "OnNavMeshLoad"
            , (void ( ::C_GameRules::* )(  ) )(&::C_GameRules::OnNavMeshLoad)
            , (void ( C_GameRules_wrapper::* )(  ) )(&C_GameRules_wrapper::default_OnNavMeshLoad) )    
        .def( 
            "RegisterScriptFunctions"
            , (void ( ::C_GameRules::* )(  ) )(&::C_GameRules::RegisterScriptFunctions)
            , (void ( C_GameRules_wrapper::* )(  ) )(&C_GameRules_wrapper::default_RegisterScriptFunctions) )    
        .def( 
            "ShouldCollide"
            , (bool ( ::C_GameRules::* )( int,int ) )( &::C_GameRules::ShouldCollide )
            , ( bp::arg("collisionGroup0"), bp::arg("collisionGroup1") ) )    
        .def( 
            "ShutdownGamerules"
            , (void ( ::C_GameRules::* )(  ) )(&::C_GameRules::ShutdownGamerules)
            , (void ( C_GameRules_wrapper::* )(  ) )(&C_GameRules_wrapper::default_ShutdownGamerules) )    
        .def( 
            "SwitchToNextBestWeapon"
            , (bool ( ::C_GameRules::* )( ::C_BaseCombatCharacter *,::C_BaseCombatWeapon * ) )(&::C_GameRules::SwitchToNextBestWeapon)
            , (bool ( C_GameRules_wrapper::* )( ::C_BaseCombatCharacter *,::C_BaseCombatWeapon * ) )(&C_GameRules_wrapper::default_SwitchToNextBestWeapon)
            , ( bp::arg("pPlayer"), bp::arg("pCurrentWeapon") ) );

}

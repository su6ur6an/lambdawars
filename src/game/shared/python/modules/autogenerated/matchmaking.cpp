// This file has been generated by Py++.

#include "cbase.h"
#ifdef CLIENT_DLL
#include "cbase.h"

#include "srcpy_matchmaking.h"

#include "wars_matchmaking.h"

#include "srcpy.h"

#include "tier0/memdbgon.h"

namespace bp = boost::python;

struct PyMatchEventsSink_wrapper : PyMatchEventsSink, bp::wrapper< PyMatchEventsSink > {

    PyMatchEventsSink_wrapper(PyMatchEventsSink const & arg )
    : PyMatchEventsSink( arg )
      , bp::wrapper< PyMatchEventsSink >(){
        // copy constructor
        
    }

    PyMatchEventsSink_wrapper()
    : PyMatchEventsSink()
      , bp::wrapper< PyMatchEventsSink >(){
        // null constructor
        
    }

    virtual void OnEvent( ::KeyValues * pEvent ) {
        PY_OVERRIDE_CHECK( PyMatchEventsSink, OnEvent )
        PY_OVERRIDE_LOG( matchmaking, PyMatchEventsSink, OnEvent )
        bp::override func_OnEvent = this->get_override( "OnEvent" );
        if( func_OnEvent.ptr() != Py_None )
            try {
                func_OnEvent( boost::python::ptr(pEvent) );
            } catch(bp::error_already_set &) {
                PyErr_Print();
                this->PyMatchEventsSink::OnEvent( pEvent );
            }
        else
            this->PyMatchEventsSink::OnEvent( pEvent );
    }
    
    void default_OnEvent( ::KeyValues * pEvent ) {
        PyMatchEventsSink::OnEvent( pEvent );
    }

};

BOOST_PYTHON_MODULE(matchmaking){
    bp::docstring_options doc_options( true, true, false );

    bp::class_< PyMatchEventsSink_wrapper >( "MatchEventsSink" )    
        .def( 
            "OnEvent"
            , (void ( ::PyMatchEventsSink::* )( ::KeyValues * ) )(&::PyMatchEventsSink::OnEvent)
            , (void ( PyMatchEventsSink_wrapper::* )( ::KeyValues * ) )(&PyMatchEventsSink_wrapper::default_OnEvent)
            , ( bp::arg("pEvent") ) );

    bp::class_< PyMatchEventsSubscription >( "matcheventssubscription" )    
        .def( 
            "BroadcastEvent"
            , (void (*)( ::KeyValues * ))( &::PyMatchEventsSubscription::BroadcastEvent )
            , ( bp::arg("pEvent") ) )    
        .def( 
            "GetEventData"
            , (::KeyValues * (*)( char const * ))( &::PyMatchEventsSubscription::GetEventData )
            , ( bp::arg("szEventDataKey") )
            , bp::return_value_policy< bp::return_by_value >() )    
        .def( 
            "RegisterEventData"
            , (void (*)( ::KeyValues * ))( &::PyMatchEventsSubscription::RegisterEventData )
            , ( bp::arg("pEventData") ) )    
        .def( 
            "Subscribe"
            , (void (*)( ::PyMatchEventsSink * ))( &::PyMatchEventsSubscription::Subscribe )
            , ( bp::arg("sink") ) )    
        .def( 
            "Unsubscribe"
            , (void (*)( ::PyMatchEventsSink * ))( &::PyMatchEventsSubscription::Unsubscribe )
            , ( bp::arg("sink") ) )    
        .staticmethod( "BroadcastEvent" )    
        .staticmethod( "GetEventData" )    
        .staticmethod( "RegisterEventData" )    
        .staticmethod( "Subscribe" )    
        .staticmethod( "Unsubscribe" );

    bp::class_< PyMatchSearchResult >( "MatchSearchResult", bp::init< >() )    
        .def( 
            "GetGameDetails"
            , (::KeyValues * ( ::PyMatchSearchResult::* )(  ) )( &::PyMatchSearchResult::GetGameDetails )
            , bp::return_value_policy< bp::return_by_value >() )    
        .def( 
            "GetOnlineId"
            , (::boost::python::api::object ( ::PyMatchSearchResult::* )(  ) )( &::PyMatchSearchResult::GetOnlineId ) )    
        .def( 
            "IsJoinable"
            , (bool ( ::PyMatchSearchResult::* )(  ) )( &::PyMatchSearchResult::IsJoinable ) )    
        .def( 
            "IsValid"
            , (bool ( ::PyMatchSearchResult::* )(  ) )( &::PyMatchSearchResult::IsValid ) )    
        .def( 
            "Join"
            , (void ( ::PyMatchSearchResult::* )(  ) )( &::PyMatchSearchResult::Join ) )    
        .def( 
            "SetMatchResultInternal"
            , (void ( ::PyMatchSearchResult::* )( ::IMatchSearchResult *,::boost::python::api::object ) )( &::PyMatchSearchResult::SetMatchResultInternal )
            , ( bp::arg("pMatchResult"), bp::arg("weakref") ) );

    bp::class_< PyMatchSession >( "matchsession" )    
        .def( 
            "Command"
            , (void (*)( ::KeyValues * ))( &::PyMatchSession::Command )
            , ( bp::arg("pCommand") ) )    
        .def( 
            "GetSessionSettings"
            , (::KeyValues * (*)(  ))( &::PyMatchSession::GetSessionSettings )
            , bp::return_value_policy< bp::return_by_value >() )    
        .def( 
            "GetSessionSystemData"
            , (::KeyValues * (*)(  ))( &::PyMatchSession::GetSessionSystemData )
            , bp::return_value_policy< bp::return_by_value >() )    
        .def( 
            "UpdateSessionSettings"
            , (void (*)( ::KeyValues * ))( &::PyMatchSession::UpdateSessionSettings )
            , ( bp::arg("pSettings") ) )    
        .staticmethod( "Command" )    
        .staticmethod( "GetSessionSettings" )    
        .staticmethod( "GetSessionSystemData" )    
        .staticmethod( "UpdateSessionSettings" );

    bp::class_< PyMatchSystem >( "matchsystem" )    
        .def( 
            "CreateGameSearchManager"
            , (::boost::python::api::object (*)( ::KeyValues * ))( &::PyMatchSystem::CreateGameSearchManager )
            , ( bp::arg("pSettings") ) )    
        .staticmethod( "CreateGameSearchManager" );

    bp::class_< PySearchManager >( "SearchManager", bp::init< >() )    
        .def( 
            "Destroy"
            , (void ( ::PySearchManager::* )(  ) )( &::PySearchManager::Destroy ) )    
        .def( 
            "EnableResultsUpdate"
            , (void ( ::PySearchManager::* )( bool,::KeyValues * ) )( &::PySearchManager::EnableResultsUpdate )
            , ( bp::arg("bEnable"), bp::arg("pSearchParams")=bp::object() ) )    
        .def( 
            "GetNumResults"
            , (int ( ::PySearchManager::* )(  ) )( &::PySearchManager::GetNumResults ) )    
        .def( 
            "GetResultByIndex"
            , (::boost::python::api::object ( ::PySearchManager::* )( int ) )( &::PySearchManager::GetResultByIndex )
            , ( bp::arg("iResultIdx") ) )    
        .def( 
            "GetResultByOnlineId"
            , (::boost::python::api::object ( ::PySearchManager::* )( ::boost::python::api::object ) )( &::PySearchManager::GetResultByOnlineId )
            , ( bp::arg("xuidResultOnline") ) )    
        .def( 
            "IsValid"
            , (bool ( ::PySearchManager::* )(  ) )( &::PySearchManager::IsValid ) );

    bp::class_< PySteamMatchmaking >( "steammatchmaking" )    
        .def( 
            "AddRequestLobbyListDistanceFilter"
            , (void (*)( ::ELobbyDistanceFilter ))( &::PySteamMatchmaking::AddRequestLobbyListDistanceFilter )
            , ( bp::arg("eLobbyDistanceFilter") ) )    
        .staticmethod( "AddRequestLobbyListDistanceFilter" );

    { //::PyMKCloseSession
    
        typedef void ( *CloseSession_function_type )(  );
        
        bp::def( 
            "CloseSession"
            , CloseSession_function_type( &::PyMKCloseSession ) );
    
    }

    { //::PyMKCreateSession
    
        typedef void ( *CreateSession_function_type )( ::KeyValues * );
        
        bp::def( 
            "CreateSession"
            , CreateSession_function_type( &::PyMKCreateSession )
            , ( bp::arg("pSettings") ) );
    
    }

    { //::PyMKIsSessionActive
    
        typedef bool ( *IsSessionActive_function_type )(  );
        
        bp::def( 
            "IsSessionActive"
            , IsSessionActive_function_type( &::PyMKIsSessionActive ) );
    
    }

    { //::PyMKMatchSession
    
        typedef void ( *MatchSession_function_type )( ::KeyValues * );
        
        bp::def( 
            "MatchSession"
            , MatchSession_function_type( &::PyMKMatchSession )
            , ( bp::arg("pSettings") ) );
    
    }

    { //::WarsRequestGameServer
    
        typedef void ( *WarsRequestGameServer_function_type )( ::CSteamID,::CSteamID,::KeyValues * );
        
        bp::def( 
            "WarsRequestGameServer"
            , WarsRequestGameServer_function_type( &::WarsRequestGameServer )
            , ( bp::arg("serverSteamId"), bp::arg("lobbySteamId"), bp::arg("pGameData") ) );
    
    }
}
#else
#include "cbase.h"

#include "srcpy_matchmaking.h"

#include "wars_matchmaking.h"

#include "srcpy.h"

#include "tier0/memdbgon.h"

namespace bp = boost::python;

struct PyMatchEventsSink_wrapper : PyMatchEventsSink, bp::wrapper< PyMatchEventsSink > {

    PyMatchEventsSink_wrapper(PyMatchEventsSink const & arg )
    : PyMatchEventsSink( arg )
      , bp::wrapper< PyMatchEventsSink >(){
        // copy constructor
        
    }

    PyMatchEventsSink_wrapper()
    : PyMatchEventsSink()
      , bp::wrapper< PyMatchEventsSink >(){
        // null constructor
        
    }

    virtual void OnEvent( ::KeyValues * pEvent ) {
        PY_OVERRIDE_CHECK( PyMatchEventsSink, OnEvent )
        PY_OVERRIDE_LOG( matchmaking, PyMatchEventsSink, OnEvent )
        bp::override func_OnEvent = this->get_override( "OnEvent" );
        if( func_OnEvent.ptr() != Py_None )
            try {
                func_OnEvent( boost::python::ptr(pEvent) );
            } catch(bp::error_already_set &) {
                PyErr_Print();
                this->PyMatchEventsSink::OnEvent( pEvent );
            }
        else
            this->PyMatchEventsSink::OnEvent( pEvent );
    }
    
    void default_OnEvent( ::KeyValues * pEvent ) {
        PyMatchEventsSink::OnEvent( pEvent );
    }

};

BOOST_PYTHON_MODULE(matchmaking){
    bp::docstring_options doc_options( true, true, false );

    bp::class_< PyMatchEventsSink_wrapper >( "MatchEventsSink" )    
        .def( 
            "OnEvent"
            , (void ( ::PyMatchEventsSink::* )( ::KeyValues * ) )(&::PyMatchEventsSink::OnEvent)
            , (void ( PyMatchEventsSink_wrapper::* )( ::KeyValues * ) )(&PyMatchEventsSink_wrapper::default_OnEvent)
            , ( bp::arg("pEvent") ) );

    bp::class_< PyMatchEventsSubscription >( "matcheventssubscription" )    
        .def( 
            "BroadcastEvent"
            , (void (*)( ::KeyValues * ))( &::PyMatchEventsSubscription::BroadcastEvent )
            , ( bp::arg("pEvent") ) )    
        .def( 
            "GetEventData"
            , (::KeyValues * (*)( char const * ))( &::PyMatchEventsSubscription::GetEventData )
            , ( bp::arg("szEventDataKey") )
            , bp::return_value_policy< bp::return_by_value >() )    
        .def( 
            "RegisterEventData"
            , (void (*)( ::KeyValues * ))( &::PyMatchEventsSubscription::RegisterEventData )
            , ( bp::arg("pEventData") ) )    
        .def( 
            "Subscribe"
            , (void (*)( ::PyMatchEventsSink * ))( &::PyMatchEventsSubscription::Subscribe )
            , ( bp::arg("sink") ) )    
        .def( 
            "Unsubscribe"
            , (void (*)( ::PyMatchEventsSink * ))( &::PyMatchEventsSubscription::Unsubscribe )
            , ( bp::arg("sink") ) )    
        .staticmethod( "BroadcastEvent" )    
        .staticmethod( "GetEventData" )    
        .staticmethod( "RegisterEventData" )    
        .staticmethod( "Subscribe" )    
        .staticmethod( "Unsubscribe" );

    bp::class_< PyMatchSearchResult >( "MatchSearchResult", bp::init< >() )    
        .def( 
            "GetGameDetails"
            , (::KeyValues * ( ::PyMatchSearchResult::* )(  ) )( &::PyMatchSearchResult::GetGameDetails )
            , bp::return_value_policy< bp::return_by_value >() )    
        .def( 
            "GetOnlineId"
            , (::boost::python::api::object ( ::PyMatchSearchResult::* )(  ) )( &::PyMatchSearchResult::GetOnlineId ) )    
        .def( 
            "IsJoinable"
            , (bool ( ::PyMatchSearchResult::* )(  ) )( &::PyMatchSearchResult::IsJoinable ) )    
        .def( 
            "IsValid"
            , (bool ( ::PyMatchSearchResult::* )(  ) )( &::PyMatchSearchResult::IsValid ) )    
        .def( 
            "Join"
            , (void ( ::PyMatchSearchResult::* )(  ) )( &::PyMatchSearchResult::Join ) )    
        .def( 
            "SetMatchResultInternal"
            , (void ( ::PyMatchSearchResult::* )( ::IMatchSearchResult *,::boost::python::api::object ) )( &::PyMatchSearchResult::SetMatchResultInternal )
            , ( bp::arg("pMatchResult"), bp::arg("weakref") ) );

    bp::class_< PyMatchSession >( "matchsession" )    
        .def( 
            "Command"
            , (void (*)( ::KeyValues * ))( &::PyMatchSession::Command )
            , ( bp::arg("pCommand") ) )    
        .def( 
            "GetSessionSettings"
            , (::KeyValues * (*)(  ))( &::PyMatchSession::GetSessionSettings )
            , bp::return_value_policy< bp::return_by_value >() )    
        .def( 
            "GetSessionSystemData"
            , (::KeyValues * (*)(  ))( &::PyMatchSession::GetSessionSystemData )
            , bp::return_value_policy< bp::return_by_value >() )    
        .def( 
            "UpdateSessionSettings"
            , (void (*)( ::KeyValues * ))( &::PyMatchSession::UpdateSessionSettings )
            , ( bp::arg("pSettings") ) )    
        .staticmethod( "Command" )    
        .staticmethod( "GetSessionSettings" )    
        .staticmethod( "GetSessionSystemData" )    
        .staticmethod( "UpdateSessionSettings" );

    bp::class_< PyMatchSystem >( "matchsystem" )    
        .def( 
            "CreateGameSearchManager"
            , (::boost::python::api::object (*)( ::KeyValues * ))( &::PyMatchSystem::CreateGameSearchManager )
            , ( bp::arg("pSettings") ) )    
        .staticmethod( "CreateGameSearchManager" );

    bp::class_< PySearchManager >( "SearchManager", bp::init< >() )    
        .def( 
            "Destroy"
            , (void ( ::PySearchManager::* )(  ) )( &::PySearchManager::Destroy ) )    
        .def( 
            "EnableResultsUpdate"
            , (void ( ::PySearchManager::* )( bool,::KeyValues * ) )( &::PySearchManager::EnableResultsUpdate )
            , ( bp::arg("bEnable"), bp::arg("pSearchParams")=bp::object() ) )    
        .def( 
            "GetNumResults"
            , (int ( ::PySearchManager::* )(  ) )( &::PySearchManager::GetNumResults ) )    
        .def( 
            "GetResultByIndex"
            , (::boost::python::api::object ( ::PySearchManager::* )( int ) )( &::PySearchManager::GetResultByIndex )
            , ( bp::arg("iResultIdx") ) )    
        .def( 
            "GetResultByOnlineId"
            , (::boost::python::api::object ( ::PySearchManager::* )( ::boost::python::api::object ) )( &::PySearchManager::GetResultByOnlineId )
            , ( bp::arg("xuidResultOnline") ) )    
        .def( 
            "IsValid"
            , (bool ( ::PySearchManager::* )(  ) )( &::PySearchManager::IsValid ) );

    bp::class_< PySteamMatchmaking >( "steammatchmaking" )    
        .def( 
            "AddRequestLobbyListDistanceFilter"
            , (void (*)( ::ELobbyDistanceFilter ))( &::PySteamMatchmaking::AddRequestLobbyListDistanceFilter )
            , ( bp::arg("eLobbyDistanceFilter") ) )    
        .staticmethod( "AddRequestLobbyListDistanceFilter" );

    { //::PyMKCloseSession
    
        typedef void ( *CloseSession_function_type )(  );
        
        bp::def( 
            "CloseSession"
            , CloseSession_function_type( &::PyMKCloseSession ) );
    
    }

    { //::PyMKCreateSession
    
        typedef void ( *CreateSession_function_type )( ::KeyValues * );
        
        bp::def( 
            "CreateSession"
            , CreateSession_function_type( &::PyMKCreateSession )
            , ( bp::arg("pSettings") ) );
    
    }

    { //::PyMKIsSessionActive
    
        typedef bool ( *IsSessionActive_function_type )(  );
        
        bp::def( 
            "IsSessionActive"
            , IsSessionActive_function_type( &::PyMKIsSessionActive ) );
    
    }

    { //::PyMKMatchSession
    
        typedef void ( *MatchSession_function_type )( ::KeyValues * );
        
        bp::def( 
            "MatchSession"
            , MatchSession_function_type( &::PyMKMatchSession )
            , ( bp::arg("pSettings") ) );
    
    }

    { //::WarsRequestGameServer
    
        typedef void ( *WarsRequestGameServer_function_type )( ::CSteamID,::CSteamID,::KeyValues * );
        
        bp::def( 
            "WarsRequestGameServer"
            , WarsRequestGameServer_function_type( &::WarsRequestGameServer )
            , ( bp::arg("serverSteamId"), bp::arg("lobbySteamId"), bp::arg("pGameData") ) );
    
    }
}
#endif


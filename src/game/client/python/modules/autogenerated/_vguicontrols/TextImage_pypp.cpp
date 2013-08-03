// This file has been generated by Py++.

#include "cbase.h"
#include "boost/python.hpp"
#include "__convenience.pypp.hpp"
#include "__call_policies.pypp.hpp"
#include "videocfg/videocfg.h"
#include "cbase.h"
#include "vgui_controls/Panel.h"
#include "vgui_controls/AnimationController.h"
#include "vgui_controls/EditablePanel.h"
#include "vgui_controls/AnalogBar.h"
#include "vgui_controls/Image.h"
#include "vgui_controls/TextImage.h"
#include "vgui_controls/ScrollBar.h"
#include "vgui_controls/ScrollBarSlider.h"
#include "vgui_controls/Menu.h"
#include "vgui_controls/MenuButton.h"
#include "vgui_controls/Frame.h"
#include "vgui_controls/TextEntry.h"
#include "vgui_controls/RichText.h"
#include "vgui_controls/Tooltip.h"
#include "vgui/IBorder.h"
#include "vgui_bitmapimage.h"
#include "vgui_avatarimage.h"
#include "srcpy_vgui.h"
#include "hl2wars/hl2wars_baseminimap.h"
#include "hl2wars/vgui_video_general.h"
#include "srcpy.h"
#include "tier0/memdbgon.h"
#include "TextImage_pypp.hpp"

namespace bp = boost::python;

struct TextImage_wrapper : vgui::TextImage, bp::wrapper< vgui::TextImage > {

    TextImage_wrapper(char const * text )
    : vgui::TextImage( text )
      , bp::wrapper< vgui::TextImage >(){
        // constructor
    
    }

    TextImage_wrapper(wchar_t const * wszText )
    : vgui::TextImage( wszText )
      , bp::wrapper< vgui::TextImage >(){
        // constructor
    
    }

    static boost::python::tuple GetContentSize( ::vgui::TextImage & inst ){
        int wide2;
        int tall2;
        inst.GetContentSize(wide2, tall2);
        return bp::make_tuple( wide2, tall2 );
    }

    static boost::python::object GetDrawWidth( ::vgui::TextImage & inst ){
        int width2;
        inst.GetDrawWidth(width2);
        return bp::object( width2 );
    }

    void DrawFilledRect( int x0, int y0, int x1, int y1 ){
        vgui::Image::DrawFilledRect( x0, y0, x1, y1 );
    }

    void DrawLine( int x0, int y0, int x1, int y1 ){
        vgui::Image::DrawLine( x0, y0, x1, y1 );
    }

    void DrawOutlinedRect( int x0, int y0, int x1, int y1 ){
        vgui::Image::DrawOutlinedRect( x0, y0, x1, y1 );
    }

    void DrawPolyLine( int * px, int * py, int numPoints ){
        vgui::Image::DrawPolyLine( px, py, numPoints );
    }

    void DrawPrintChar( wchar_t ch ){
        vgui::Image::DrawPrintChar( ch );
    }

    void DrawPrintChar( int x, int y, wchar_t ch ){
        vgui::Image::DrawPrintChar( x, y, ch );
    }

    void DrawPrintText( wchar_t const * str, int strlen ){
        vgui::Image::DrawPrintText( str, strlen );
    }

    void DrawPrintText( int x, int y, wchar_t const * str, int strlen ){
        vgui::Image::DrawPrintText( x, y, str, strlen );
    }

    void DrawSetColor( ::Color color ){
        vgui::Image::DrawSetColor( color );
    }

    void DrawSetColor( int r, int g, int b, int a ){
        vgui::Image::DrawSetColor( r, g, b, a );
    }

    void DrawSetTextColor( ::Color color ){
        vgui::Image::DrawSetTextColor( color );
    }

    void DrawSetTextColor( int r, int g, int b, int a ){
        vgui::Image::DrawSetTextColor( r, g, b, a );
    }

    void DrawSetTextFont( ::vgui::HFont font ){
        vgui::Image::DrawSetTextFont( font );
    }

    void DrawSetTextPos( int x, int y ){
        vgui::Image::DrawSetTextPos( x, y );
    }

    void DrawSetTexture( int id ){
        vgui::Image::DrawSetTexture( id );
    }

    void DrawTexturedRect( int x0, int y0, int x1, int y1 ){
        vgui::Image::DrawTexturedRect( x0, y0, x1, y1 );
    }

    virtual bool Evict(  ) {
        #if defined(_WIN32)
        #if defined(_DEBUG)
        Assert( SrcPySystem()->IsPythonRunning() );
        Assert( GetCurrentThreadId() == g_hPythonThreadID );
        #elif defined(PY_CHECKTHREADID)
        if( GetCurrentThreadId() != g_hPythonThreadID )
            Error( "Evict: Client? %d. Thread ID is not the same as in which the python interpreter is initialized! %d != %d. Tell a developer.\n", CBaseEntity::IsClient(), g_hPythonThreadID, GetCurrentThreadId() );
        #endif // _DEBUG/PY_CHECKTHREADID
        #endif // _WIN32
        #if defined(_DEBUG) || defined(PY_CHECK_LOG_OVERRIDES)
        if( py_log_overrides.GetBool() )
            Msg("Calling Evict(  ) of Class: vgui::Image\n");
        #endif // _DEBUG/PY_CHECK_LOG_OVERRIDES
        bp::override func_Evict = this->get_override( "Evict" );
        if( func_Evict.ptr() != Py_None )
            try {
                return func_Evict(  );
            } catch(bp::error_already_set &) {
                PyErr_Print();
                return this->vgui::Image::Evict(  );
            }
        else
            return this->vgui::Image::Evict(  );
    }
    
    bool default_Evict(  ) {
        return vgui::Image::Evict( );
    }

    virtual ::vgui::HTexture GetID(  ) {
        #if defined(_WIN32)
        #if defined(_DEBUG)
        Assert( SrcPySystem()->IsPythonRunning() );
        Assert( GetCurrentThreadId() == g_hPythonThreadID );
        #elif defined(PY_CHECKTHREADID)
        if( GetCurrentThreadId() != g_hPythonThreadID )
            Error( "GetID: Client? %d. Thread ID is not the same as in which the python interpreter is initialized! %d != %d. Tell a developer.\n", CBaseEntity::IsClient(), g_hPythonThreadID, GetCurrentThreadId() );
        #endif // _DEBUG/PY_CHECKTHREADID
        #endif // _WIN32
        #if defined(_DEBUG) || defined(PY_CHECK_LOG_OVERRIDES)
        if( py_log_overrides.GetBool() )
            Msg("Calling GetID(  ) of Class: vgui::Image\n");
        #endif // _DEBUG/PY_CHECK_LOG_OVERRIDES
        bp::override func_GetID = this->get_override( "GetID" );
        if( func_GetID.ptr() != Py_None )
            try {
                return func_GetID(  );
            } catch(bp::error_already_set &) {
                PyErr_Print();
                return this->vgui::Image::GetID(  );
            }
        else
            return this->vgui::Image::GetID(  );
    }
    
    ::vgui::HTexture default_GetID(  ) {
        return vgui::Image::GetID( );
    }

    virtual int GetNumFrames(  ) {
        #if defined(_WIN32)
        #if defined(_DEBUG)
        Assert( SrcPySystem()->IsPythonRunning() );
        Assert( GetCurrentThreadId() == g_hPythonThreadID );
        #elif defined(PY_CHECKTHREADID)
        if( GetCurrentThreadId() != g_hPythonThreadID )
            Error( "GetNumFrames: Client? %d. Thread ID is not the same as in which the python interpreter is initialized! %d != %d. Tell a developer.\n", CBaseEntity::IsClient(), g_hPythonThreadID, GetCurrentThreadId() );
        #endif // _DEBUG/PY_CHECKTHREADID
        #endif // _WIN32
        #if defined(_DEBUG) || defined(PY_CHECK_LOG_OVERRIDES)
        if( py_log_overrides.GetBool() )
            Msg("Calling GetNumFrames(  ) of Class: vgui::Image\n");
        #endif // _DEBUG/PY_CHECK_LOG_OVERRIDES
        bp::override func_GetNumFrames = this->get_override( "GetNumFrames" );
        if( func_GetNumFrames.ptr() != Py_None )
            try {
                return func_GetNumFrames(  );
            } catch(bp::error_already_set &) {
                PyErr_Print();
                return this->vgui::Image::GetNumFrames(  );
            }
        else
            return this->vgui::Image::GetNumFrames(  );
    }
    
    int default_GetNumFrames(  ) {
        return vgui::Image::GetNumFrames( );
    }

    virtual void GetPos( int & x, int & y ) {
        namespace bpl = boost::python;
        bpl::override func_GetPos = this->get_override( "GetPos" );
        if( func_GetPos.ptr() != Py_None ) {
            bpl::object py_result = bpl::call<bpl::object>( func_GetPos.ptr() );
            x = boost::python::extract< int >( pyplus_conv::get_out_argument( py_result, "x" ) );
            y = boost::python::extract< int >( pyplus_conv::get_out_argument( py_result, "y" ) );
        }
        else{
            vgui::Image::GetPos( x, y );
        }
    }
    
    static boost::python::tuple default_GetPos( ::vgui::Image & inst ){
        int x2;
        int y2;
        if( dynamic_cast< TextImage_wrapper * >( boost::addressof( inst ) ) ){
            inst.::vgui::Image::GetPos(x2, y2);
        }
        else{
            inst.GetPos(x2, y2);
        }
        return bp::make_tuple( x2, y2 );
    }

    virtual void GetSize( int & wide, int & tall ) {
        namespace bpl = boost::python;
        bpl::override func_GetSize = this->get_override( "GetSize" );
        if( func_GetSize.ptr() != Py_None ) {
            bpl::object py_result = bpl::call<bpl::object>( func_GetSize.ptr() );
            wide = boost::python::extract< int >( pyplus_conv::get_out_argument( py_result, "wide" ) );
            tall = boost::python::extract< int >( pyplus_conv::get_out_argument( py_result, "tall" ) );
        }
        else{
            vgui::Image::GetSize( wide, tall );
        }
    }
    
    static boost::python::tuple default_GetSize( ::vgui::Image & inst ){
        int wide2;
        int tall2;
        if( dynamic_cast< TextImage_wrapper * >( boost::addressof( inst ) ) ){
            inst.::vgui::Image::GetSize(wide2, tall2);
        }
        else{
            inst.GetSize(wide2, tall2);
        }
        return bp::make_tuple( wide2, tall2 );
    }

    virtual int GetTall(  ) {
        #if defined(_WIN32)
        #if defined(_DEBUG)
        Assert( SrcPySystem()->IsPythonRunning() );
        Assert( GetCurrentThreadId() == g_hPythonThreadID );
        #elif defined(PY_CHECKTHREADID)
        if( GetCurrentThreadId() != g_hPythonThreadID )
            Error( "GetTall: Client? %d. Thread ID is not the same as in which the python interpreter is initialized! %d != %d. Tell a developer.\n", CBaseEntity::IsClient(), g_hPythonThreadID, GetCurrentThreadId() );
        #endif // _DEBUG/PY_CHECKTHREADID
        #endif // _WIN32
        #if defined(_DEBUG) || defined(PY_CHECK_LOG_OVERRIDES)
        if( py_log_overrides.GetBool() )
            Msg("Calling GetTall(  ) of Class: vgui::Image\n");
        #endif // _DEBUG/PY_CHECK_LOG_OVERRIDES
        bp::override func_GetTall = this->get_override( "GetTall" );
        if( func_GetTall.ptr() != Py_None )
            try {
                return func_GetTall(  );
            } catch(bp::error_already_set &) {
                PyErr_Print();
                return this->vgui::Image::GetTall(  );
            }
        else
            return this->vgui::Image::GetTall(  );
    }
    
    int default_GetTall(  ) {
        return vgui::Image::GetTall( );
    }

    virtual int GetWide(  ) {
        #if defined(_WIN32)
        #if defined(_DEBUG)
        Assert( SrcPySystem()->IsPythonRunning() );
        Assert( GetCurrentThreadId() == g_hPythonThreadID );
        #elif defined(PY_CHECKTHREADID)
        if( GetCurrentThreadId() != g_hPythonThreadID )
            Error( "GetWide: Client? %d. Thread ID is not the same as in which the python interpreter is initialized! %d != %d. Tell a developer.\n", CBaseEntity::IsClient(), g_hPythonThreadID, GetCurrentThreadId() );
        #endif // _DEBUG/PY_CHECKTHREADID
        #endif // _WIN32
        #if defined(_DEBUG) || defined(PY_CHECK_LOG_OVERRIDES)
        if( py_log_overrides.GetBool() )
            Msg("Calling GetWide(  ) of Class: vgui::Image\n");
        #endif // _DEBUG/PY_CHECK_LOG_OVERRIDES
        bp::override func_GetWide = this->get_override( "GetWide" );
        if( func_GetWide.ptr() != Py_None )
            try {
                return func_GetWide(  );
            } catch(bp::error_already_set &) {
                PyErr_Print();
                return this->vgui::Image::GetWide(  );
            }
        else
            return this->vgui::Image::GetWide(  );
    }
    
    int default_GetWide(  ) {
        return vgui::Image::GetWide( );
    }

    virtual void SetFrame( int nFrame ) {
        #if defined(_WIN32)
        #if defined(_DEBUG)
        Assert( SrcPySystem()->IsPythonRunning() );
        Assert( GetCurrentThreadId() == g_hPythonThreadID );
        #elif defined(PY_CHECKTHREADID)
        if( GetCurrentThreadId() != g_hPythonThreadID )
            Error( "SetFrame: Client? %d. Thread ID is not the same as in which the python interpreter is initialized! %d != %d. Tell a developer.\n", CBaseEntity::IsClient(), g_hPythonThreadID, GetCurrentThreadId() );
        #endif // _DEBUG/PY_CHECKTHREADID
        #endif // _WIN32
        #if defined(_DEBUG) || defined(PY_CHECK_LOG_OVERRIDES)
        if( py_log_overrides.GetBool() )
            Msg("Calling SetFrame( nFrame ) of Class: vgui::Image\n");
        #endif // _DEBUG/PY_CHECK_LOG_OVERRIDES
        bp::override func_SetFrame = this->get_override( "SetFrame" );
        if( func_SetFrame.ptr() != Py_None )
            try {
                func_SetFrame( nFrame );
            } catch(bp::error_already_set &) {
                PyErr_Print();
                this->vgui::Image::SetFrame( nFrame );
            }
        else
            this->vgui::Image::SetFrame( nFrame );
    }
    
    void default_SetFrame( int nFrame ) {
        vgui::Image::SetFrame( nFrame );
    }

    virtual void SetRotation( int iRotation ) {
        #if defined(_WIN32)
        #if defined(_DEBUG)
        Assert( SrcPySystem()->IsPythonRunning() );
        Assert( GetCurrentThreadId() == g_hPythonThreadID );
        #elif defined(PY_CHECKTHREADID)
        if( GetCurrentThreadId() != g_hPythonThreadID )
            Error( "SetRotation: Client? %d. Thread ID is not the same as in which the python interpreter is initialized! %d != %d. Tell a developer.\n", CBaseEntity::IsClient(), g_hPythonThreadID, GetCurrentThreadId() );
        #endif // _DEBUG/PY_CHECKTHREADID
        #endif // _WIN32
        #if defined(_DEBUG) || defined(PY_CHECK_LOG_OVERRIDES)
        if( py_log_overrides.GetBool() )
            Msg("Calling SetRotation( iRotation ) of Class: vgui::Image\n");
        #endif // _DEBUG/PY_CHECK_LOG_OVERRIDES
        bp::override func_SetRotation = this->get_override( "SetRotation" );
        if( func_SetRotation.ptr() != Py_None )
            try {
                func_SetRotation( iRotation );
            } catch(bp::error_already_set &) {
                PyErr_Print();
                this->vgui::Image::SetRotation( iRotation );
            }
        else
            this->vgui::Image::SetRotation( iRotation );
    }
    
    void default_SetRotation( int iRotation ) {
        vgui::Image::SetRotation( iRotation );
    }

    boost::python::object GetText() {
        char buf[1025];
        TextImage::GetText(buf, 1025);
        return boost::python::object(buf);
    }

};

void register_TextImage_class(){

    { //::vgui::TextImage
        typedef bp::class_< TextImage_wrapper, bp::bases< vgui::Image >, boost::noncopyable > TextImage_exposer_t;
        TextImage_exposer_t TextImage_exposer = TextImage_exposer_t( "TextImage", bp::init< char const * >(( bp::arg("text") )) );
        bp::scope TextImage_scope( TextImage_exposer );
        bp::implicitly_convertible< char const *, vgui::TextImage >();
        TextImage_exposer.def( bp::init< wchar_t const * >(( bp::arg("wszText") )) );
        bp::implicitly_convertible< wchar_t const *, vgui::TextImage >();
        { //::vgui::TextImage::GetContentSize
        
            typedef boost::python::tuple ( *GetContentSize_function_type )( ::vgui::TextImage & );
            
            TextImage_exposer.def( 
                "GetContentSize"
                , GetContentSize_function_type( &TextImage_wrapper::GetContentSize )
                , ( bp::arg("inst") ) );
        
        }
        { //::vgui::TextImage::GetDrawWidth
        
            typedef boost::python::object ( *GetDrawWidth_function_type )( ::vgui::TextImage & );
            
            TextImage_exposer.def( 
                "GetDrawWidth"
                , GetDrawWidth_function_type( &TextImage_wrapper::GetDrawWidth )
                , ( bp::arg("inst") ) );
        
        }
        { //::vgui::TextImage::GetFont
        
            typedef ::vgui::HFont ( ::vgui::TextImage::*GetFont_function_type )(  ) ;
            
            TextImage_exposer.def( 
                "GetFont"
                , GetFont_function_type( &::vgui::TextImage::GetFont ) );
        
        }
        { //::vgui::TextImage::GetUText
        
            typedef wchar_t const * ( ::vgui::TextImage::*GetUText_function_type )(  ) ;
            
            TextImage_exposer.def( 
                "GetUText"
                , GetUText_function_type( &::vgui::TextImage::GetUText )
                , bp::return_value_policy< bp::return_by_value >() );
        
        }
        { //::vgui::TextImage::GetUnlocalizedText
        
            typedef void ( ::vgui::TextImage::*GetUnlocalizedText_function_type )( char *,int ) ;
            
            TextImage_exposer.def( 
                "GetUnlocalizedText"
                , GetUnlocalizedText_function_type( &::vgui::TextImage::GetUnlocalizedText )
                , ( bp::arg("buffer"), bp::arg("bufferSize") ) );
        
        }
        { //::vgui::TextImage::GetUnlocalizedTextSymbol
        
            typedef ::vgui::StringIndex_t ( ::vgui::TextImage::*GetUnlocalizedTextSymbol_function_type )(  ) ;
            
            TextImage_exposer.def( 
                "GetUnlocalizedTextSymbol"
                , GetUnlocalizedTextSymbol_function_type( &::vgui::TextImage::GetUnlocalizedTextSymbol ) );
        
        }
        { //::vgui::TextImage::Paint
        
            typedef void ( ::vgui::TextImage::*Paint_function_type )(  ) ;
            
            TextImage_exposer.def( 
                "Paint"
                , Paint_function_type( &::vgui::TextImage::Paint ) );
        
        }
        { //::vgui::TextImage::RecalculateCenterWrapIndents
        
            typedef void ( ::vgui::TextImage::*RecalculateCenterWrapIndents_function_type )(  ) ;
            
            TextImage_exposer.def( 
                "RecalculateCenterWrapIndents"
                , RecalculateCenterWrapIndents_function_type( &::vgui::TextImage::RecalculateCenterWrapIndents ) );
        
        }
        { //::vgui::TextImage::RecalculateNewLinePositions
        
            typedef void ( ::vgui::TextImage::*RecalculateNewLinePositions_function_type )(  ) ;
            
            TextImage_exposer.def( 
                "RecalculateNewLinePositions"
                , RecalculateNewLinePositions_function_type( &::vgui::TextImage::RecalculateNewLinePositions ) );
        
        }
        { //::vgui::TextImage::ResizeImageToContent
        
            typedef void ( ::vgui::TextImage::*ResizeImageToContent_function_type )(  ) ;
            
            TextImage_exposer.def( 
                "ResizeImageToContent"
                , ResizeImageToContent_function_type( &::vgui::TextImage::ResizeImageToContent ) );
        
        }
        { //::vgui::TextImage::ResizeImageToContentMaxWidth
        
            typedef void ( ::vgui::TextImage::*ResizeImageToContentMaxWidth_function_type )( int ) ;
            
            TextImage_exposer.def( 
                "ResizeImageToContentMaxWidth"
                , ResizeImageToContentMaxWidth_function_type( &::vgui::TextImage::ResizeImageToContentMaxWidth )
                , ( bp::arg("nMaxWidth") ) );
        
        }
        { //::vgui::TextImage::SetAllCaps
        
            typedef void ( ::vgui::TextImage::*SetAllCaps_function_type )( bool ) ;
            
            TextImage_exposer.def( 
                "SetAllCaps"
                , SetAllCaps_function_type( &::vgui::TextImage::SetAllCaps )
                , ( bp::arg("bAllCaps") ) );
        
        }
        { //::vgui::TextImage::SetBounds
        
            typedef void ( ::vgui::TextImage::*SetBounds_function_type )( int,int,int,int ) ;
            
            TextImage_exposer.def( 
                "SetBounds"
                , SetBounds_function_type( &::vgui::TextImage::SetBounds )
                , ( bp::arg("x"), bp::arg("y"), bp::arg("w"), bp::arg("h") ) );
        
        }
        { //::vgui::TextImage::SetCenterWrap
        
            typedef void ( ::vgui::TextImage::*SetCenterWrap_function_type )( bool ) ;
            
            TextImage_exposer.def( 
                "SetCenterWrap"
                , SetCenterWrap_function_type( &::vgui::TextImage::SetCenterWrap )
                , ( bp::arg("bWrap") ) );
        
        }
        { //::vgui::TextImage::SetDrawWidth
        
            typedef void ( ::vgui::TextImage::*SetDrawWidth_function_type )( int ) ;
            
            TextImage_exposer.def( 
                "SetDrawWidth"
                , SetDrawWidth_function_type( &::vgui::TextImage::SetDrawWidth )
                , ( bp::arg("width") ) );
        
        }
        { //::vgui::TextImage::SetFont
        
            typedef void ( ::vgui::TextImage::*SetFont_function_type )( ::vgui::HFont ) ;
            
            TextImage_exposer.def( 
                "SetFont"
                , SetFont_function_type( &::vgui::TextImage::SetFont )
                , ( bp::arg("font") ) );
        
        }
        { //::vgui::TextImage::SetSize
        
            typedef void ( ::vgui::TextImage::*SetSize_function_type )( int,int ) ;
            
            TextImage_exposer.def( 
                "SetSize"
                , SetSize_function_type( &::vgui::TextImage::SetSize )
                , ( bp::arg("wide"), bp::arg("tall") ) );
        
        }
        { //::vgui::TextImage::SetText
        
            typedef void ( ::vgui::TextImage::*SetText_function_type )( char const * ) ;
            
            TextImage_exposer.def( 
                "SetText"
                , SetText_function_type( &::vgui::TextImage::SetText )
                , ( bp::arg("text") ) );
        
        }
        { //::vgui::TextImage::SetUseFallbackFont
        
            typedef void ( ::vgui::TextImage::*SetUseFallbackFont_function_type )( bool,::vgui::HFont ) ;
            
            TextImage_exposer.def( 
                "SetUseFallbackFont"
                , SetUseFallbackFont_function_type( &::vgui::TextImage::SetUseFallbackFont )
                , ( bp::arg("bState"), bp::arg("hFallback") ) );
        
        }
        { //::vgui::TextImage::SetWrap
        
            typedef void ( ::vgui::TextImage::*SetWrap_function_type )( bool ) ;
            
            TextImage_exposer.def( 
                "SetWrap"
                , SetWrap_function_type( &::vgui::TextImage::SetWrap )
                , ( bp::arg("bWrap") ) );
        
        }
        { //::vgui::Image::DrawFilledRect
        
            typedef void ( TextImage_wrapper::*DrawFilledRect_function_type )( int,int,int,int ) ;
            
            TextImage_exposer.def( 
                "DrawFilledRect"
                , DrawFilledRect_function_type( &TextImage_wrapper::DrawFilledRect )
                , ( bp::arg("x0"), bp::arg("y0"), bp::arg("x1"), bp::arg("y1") ) );
        
        }
        { //::vgui::Image::DrawLine
        
            typedef void ( TextImage_wrapper::*DrawLine_function_type )( int,int,int,int ) ;
            
            TextImage_exposer.def( 
                "DrawLine"
                , DrawLine_function_type( &TextImage_wrapper::DrawLine )
                , ( bp::arg("x0"), bp::arg("y0"), bp::arg("x1"), bp::arg("y1") ) );
        
        }
        { //::vgui::Image::DrawOutlinedRect
        
            typedef void ( TextImage_wrapper::*DrawOutlinedRect_function_type )( int,int,int,int ) ;
            
            TextImage_exposer.def( 
                "DrawOutlinedRect"
                , DrawOutlinedRect_function_type( &TextImage_wrapper::DrawOutlinedRect )
                , ( bp::arg("x0"), bp::arg("y0"), bp::arg("x1"), bp::arg("y1") ) );
        
        }
        { //::vgui::Image::DrawPolyLine
        
            typedef void ( TextImage_wrapper::*DrawPolyLine_function_type )( int *,int *,int ) ;
            
            TextImage_exposer.def( 
                "DrawPolyLine"
                , DrawPolyLine_function_type( &TextImage_wrapper::DrawPolyLine )
                , ( bp::arg("px"), bp::arg("py"), bp::arg("numPoints") ) );
        
        }
        { //::vgui::Image::DrawPrintChar
        
            typedef void ( TextImage_wrapper::*DrawPrintChar_function_type )( wchar_t ) ;
            
            TextImage_exposer.def( 
                "DrawPrintChar"
                , DrawPrintChar_function_type( &TextImage_wrapper::DrawPrintChar )
                , ( bp::arg("ch") ) );
        
        }
        { //::vgui::Image::DrawPrintChar
        
            typedef void ( TextImage_wrapper::*DrawPrintChar_function_type )( int,int,wchar_t ) ;
            
            TextImage_exposer.def( 
                "DrawPrintChar"
                , DrawPrintChar_function_type( &TextImage_wrapper::DrawPrintChar )
                , ( bp::arg("x"), bp::arg("y"), bp::arg("ch") ) );
        
        }
        { //::vgui::Image::DrawPrintText
        
            typedef void ( TextImage_wrapper::*DrawPrintText_function_type )( wchar_t const *,int ) ;
            
            TextImage_exposer.def( 
                "DrawPrintText"
                , DrawPrintText_function_type( &TextImage_wrapper::DrawPrintText )
                , ( bp::arg("str"), bp::arg("strlen") ) );
        
        }
        { //::vgui::Image::DrawPrintText
        
            typedef void ( TextImage_wrapper::*DrawPrintText_function_type )( int,int,wchar_t const *,int ) ;
            
            TextImage_exposer.def( 
                "DrawPrintText"
                , DrawPrintText_function_type( &TextImage_wrapper::DrawPrintText )
                , ( bp::arg("x"), bp::arg("y"), bp::arg("str"), bp::arg("strlen") ) );
        
        }
        { //::vgui::Image::DrawSetColor
        
            typedef void ( TextImage_wrapper::*DrawSetColor_function_type )( ::Color ) ;
            
            TextImage_exposer.def( 
                "DrawSetColor"
                , DrawSetColor_function_type( &TextImage_wrapper::DrawSetColor )
                , ( bp::arg("color") ) );
        
        }
        { //::vgui::Image::DrawSetColor
        
            typedef void ( TextImage_wrapper::*DrawSetColor_function_type )( int,int,int,int ) ;
            
            TextImage_exposer.def( 
                "DrawSetColor"
                , DrawSetColor_function_type( &TextImage_wrapper::DrawSetColor )
                , ( bp::arg("r"), bp::arg("g"), bp::arg("b"), bp::arg("a") ) );
        
        }
        { //::vgui::Image::DrawSetTextColor
        
            typedef void ( TextImage_wrapper::*DrawSetTextColor_function_type )( ::Color ) ;
            
            TextImage_exposer.def( 
                "DrawSetTextColor"
                , DrawSetTextColor_function_type( &TextImage_wrapper::DrawSetTextColor )
                , ( bp::arg("color") ) );
        
        }
        { //::vgui::Image::DrawSetTextColor
        
            typedef void ( TextImage_wrapper::*DrawSetTextColor_function_type )( int,int,int,int ) ;
            
            TextImage_exposer.def( 
                "DrawSetTextColor"
                , DrawSetTextColor_function_type( &TextImage_wrapper::DrawSetTextColor )
                , ( bp::arg("r"), bp::arg("g"), bp::arg("b"), bp::arg("a") ) );
        
        }
        { //::vgui::Image::DrawSetTextFont
        
            typedef void ( TextImage_wrapper::*DrawSetTextFont_function_type )( ::vgui::HFont ) ;
            
            TextImage_exposer.def( 
                "DrawSetTextFont"
                , DrawSetTextFont_function_type( &TextImage_wrapper::DrawSetTextFont )
                , ( bp::arg("font") ) );
        
        }
        { //::vgui::Image::DrawSetTextPos
        
            typedef void ( TextImage_wrapper::*DrawSetTextPos_function_type )( int,int ) ;
            
            TextImage_exposer.def( 
                "DrawSetTextPos"
                , DrawSetTextPos_function_type( &TextImage_wrapper::DrawSetTextPos )
                , ( bp::arg("x"), bp::arg("y") ) );
        
        }
        { //::vgui::Image::DrawSetTexture
        
            typedef void ( TextImage_wrapper::*DrawSetTexture_function_type )( int ) ;
            
            TextImage_exposer.def( 
                "DrawSetTexture"
                , DrawSetTexture_function_type( &TextImage_wrapper::DrawSetTexture )
                , ( bp::arg("id") ) );
        
        }
        { //::vgui::Image::DrawTexturedRect
        
            typedef void ( TextImage_wrapper::*DrawTexturedRect_function_type )( int,int,int,int ) ;
            
            TextImage_exposer.def( 
                "DrawTexturedRect"
                , DrawTexturedRect_function_type( &TextImage_wrapper::DrawTexturedRect )
                , ( bp::arg("x0"), bp::arg("y0"), bp::arg("x1"), bp::arg("y1") ) );
        
        }
        { //::vgui::Image::Evict
        
            typedef bool ( ::vgui::Image::*Evict_function_type )(  ) ;
            typedef bool ( TextImage_wrapper::*default_Evict_function_type )(  ) ;
            
            TextImage_exposer.def( 
                "Evict"
                , Evict_function_type(&::vgui::Image::Evict)
                , default_Evict_function_type(&TextImage_wrapper::default_Evict) );
        
        }
        { //::vgui::Image::GetID
        
            typedef ::vgui::HTexture ( ::vgui::Image::*GetID_function_type )(  ) ;
            typedef ::vgui::HTexture ( TextImage_wrapper::*default_GetID_function_type )(  ) ;
            
            TextImage_exposer.def( 
                "GetID"
                , GetID_function_type(&::vgui::Image::GetID)
                , default_GetID_function_type(&TextImage_wrapper::default_GetID) );
        
        }
        { //::vgui::Image::GetNumFrames
        
            typedef int ( ::vgui::Image::*GetNumFrames_function_type )(  ) ;
            typedef int ( TextImage_wrapper::*default_GetNumFrames_function_type )(  ) ;
            
            TextImage_exposer.def( 
                "GetNumFrames"
                , GetNumFrames_function_type(&::vgui::Image::GetNumFrames)
                , default_GetNumFrames_function_type(&TextImage_wrapper::default_GetNumFrames) );
        
        }
        { //::vgui::Image::GetPos
        
            typedef boost::python::tuple ( *default_GetPos_function_type )( ::vgui::Image & );
            
            TextImage_exposer.def( 
                "GetPos"
                , default_GetPos_function_type( &TextImage_wrapper::default_GetPos )
                , ( bp::arg("inst") ) );
        
        }
        { //::vgui::Image::GetSize
        
            typedef boost::python::tuple ( *default_GetSize_function_type )( ::vgui::Image & );
            
            TextImage_exposer.def( 
                "GetSize"
                , default_GetSize_function_type( &TextImage_wrapper::default_GetSize )
                , ( bp::arg("inst") ) );
        
        }
        { //::vgui::Image::GetTall
        
            typedef int ( ::vgui::Image::*GetTall_function_type )(  ) ;
            typedef int ( TextImage_wrapper::*default_GetTall_function_type )(  ) ;
            
            TextImage_exposer.def( 
                "GetTall"
                , GetTall_function_type(&::vgui::Image::GetTall)
                , default_GetTall_function_type(&TextImage_wrapper::default_GetTall) );
        
        }
        { //::vgui::Image::GetWide
        
            typedef int ( ::vgui::Image::*GetWide_function_type )(  ) ;
            typedef int ( TextImage_wrapper::*default_GetWide_function_type )(  ) ;
            
            TextImage_exposer.def( 
                "GetWide"
                , GetWide_function_type(&::vgui::Image::GetWide)
                , default_GetWide_function_type(&TextImage_wrapper::default_GetWide) );
        
        }
        { //::vgui::Image::SetFrame
        
            typedef void ( ::vgui::Image::*SetFrame_function_type )( int ) ;
            typedef void ( TextImage_wrapper::*default_SetFrame_function_type )( int ) ;
            
            TextImage_exposer.def( 
                "SetFrame"
                , SetFrame_function_type(&::vgui::Image::SetFrame)
                , default_SetFrame_function_type(&TextImage_wrapper::default_SetFrame)
                , ( bp::arg("nFrame") ) );
        
        }
        { //::vgui::Image::SetRotation
        
            typedef void ( ::vgui::Image::*SetRotation_function_type )( int ) ;
            typedef void ( TextImage_wrapper::*default_SetRotation_function_type )( int ) ;
            
            TextImage_exposer.def( 
                "SetRotation"
                , SetRotation_function_type(&::vgui::Image::SetRotation)
                , default_SetRotation_function_type(&TextImage_wrapper::default_SetRotation)
                , ( bp::arg("iRotation") ) );
        
        }
        TextImage_exposer.def( 
            "GetText"
            , (boost::python::object ( TextImage_wrapper::* )())( &TextImage_wrapper::GetText ) );
    }

}

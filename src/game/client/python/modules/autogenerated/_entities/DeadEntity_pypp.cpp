// This file has been generated by Py++.

#include "cbase.h"
// This file has been generated by Py++.

#include "boost/python.hpp"
#include "videocfg/videocfg.h"
#include "cbase.h"
#include "takedamageinfo.h"
#include "c_baseanimating.h"
#include "c_baseanimatingoverlay.h"
#include "c_baseflex.h"
#include "c_basecombatcharacter.h"
#include "basegrenade_shared.h"
#include "c_baseplayer.h"
#include "c_hl2wars_player.h"
#include "unit_base_shared.h"
#include "wars_func_unit.h"
#include "c_playerresource.h"
#include "sprite.h"
#include "SpriteTrail.h"
#include "c_smoke_trail.h"
#include "c_wars_weapon.h"
#include "c_basetoggle.h"
#include "c_triggers.h"
#include "shared_classnames.h"
#include "npcevent.h"
#include "studio.h"
#include "srcpy_entities.h"
#include "isaverestore.h"
#include "saverestore.h"
#include "mapentities_shared.h"
#include "vcollide_parse.h"
#include "hl2wars_player_shared.h"
#include "imouse.h"
#include "props_shared.h"
#include "beam_shared.h"
#include "basecombatweapon_shared.h"
#include "wars_mapboundary.h"
#include "srcpy_converters_ents.h"
#include "srcpy.h"
#include "tier0/memdbgon.h"
#include "DeadEntity_pypp.hpp"

namespace bp = boost::python;

void register_DeadEntity_class(){

    bp::class_< DeadEntity >( "DeadEntity" )    
        .def( 
            "__nonzero__"
            , (bool ( ::DeadEntity::* )(  ) )( &::DeadEntity::NonZero ) );

}


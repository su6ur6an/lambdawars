// This file has been generated by Py++.

#include "cbase.h"
// This file has been generated by Py++.

#include "boost/python.hpp"
#include "cbase.h"
#include "mathlib/vmatrix.h"
#include "utlvector.h"
#include "shareddefs.h"
#include "util.h"
#include "takedamageinfo.h"
#include "baseanimating.h"
#include "BaseAnimatingOverlay.h"
#include "baseflex.h"
#include "basecombatcharacter.h"
#include "basegrenade_shared.h"
#include "player.h"
#include "hl2wars_player.h"
#include "unit_base_shared.h"
#include "unit_sense.h"
#include "wars_func_unit.h"
#include "soundent.h"
#include "gib.h"
#include "Sprite.h"
#include "SpriteTrail.h"
#include "smoke_trail.h"
#include "entityoutput.h"
#include "props.h"
#include "modelentities.h"
#include "triggers.h"
#include "wars_weapon.h"
#include "spark.h"
#include "physics_prop_ragdoll.h"
#include "filters.h"
#include "EntityFlame.h"
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
#include "_entities__entities_enumerations_pypp.hpp"

namespace bp = boost::python;

void register__entities_enumerations(){

    bp::enum_< Disposition_t>("Disposition_t")
        .value("D_ER", D_ER)
        .value("D_HT", D_HT)
        .value("D_FR", D_FR)
        .value("D_LI", D_LI)
        .value("D_NU", D_NU)
        .value("D_ERROR", D_ERROR)
        .value("D_HATE", D_HATE)
        .value("D_FEAR", D_FEAR)
        .value("D_LIKE", D_LIKE)
        .value("D_NEUTRAL", D_NEUTRAL)
        .export_values()
        ;

    bp::enum_< GibType_e>("GibType_e")
        .value("GIB_HUMAN", GIB_HUMAN)
        .value("GIB_ALIEN", GIB_ALIEN)
        .export_values()
        ;

    bp::enum_< LocalFlexController_t>("LocalFlexController_t")
        .value("DUMMY_FLEX_CONTROLLER", DUMMY_FLEX_CONTROLLER)
        .export_values()
        ;

    bp::enum_< WeaponSound_t>("WeaponSound")
        .value("EMPTY", EMPTY)
        .value("SINGLE", SINGLE)
        .value("SINGLE_NPC", SINGLE_NPC)
        .value("WPN_DOUBLE", WPN_DOUBLE)
        .value("DOUBLE_NPC", DOUBLE_NPC)
        .value("BURST", BURST)
        .value("RELOAD", RELOAD)
        .value("RELOAD_NPC", RELOAD_NPC)
        .value("MELEE_MISS", MELEE_MISS)
        .value("MELEE_HIT", MELEE_HIT)
        .value("MELEE_HIT_WORLD", MELEE_HIT_WORLD)
        .value("SPECIAL1", SPECIAL1)
        .value("SPECIAL2", SPECIAL2)
        .value("SPECIAL3", SPECIAL3)
        .value("TAUNT", TAUNT)
        .value("FAST_RELOAD", FAST_RELOAD)
        .value("NUM_SHOOT_SOUND_TYPES", NUM_SHOOT_SOUND_TYPES)
        .export_values()
        ;

}


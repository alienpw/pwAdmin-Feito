#include "config.h"

#include <fstream>
#include <cassert>
#include <sstream>
#include <iostream>
#include <limits>
#include <regex>
#include <map>
#include <cctype>
#include <stdio.h>
#include <string>
#include <QString>
#include <QDir>
#include <QFileInfo>
#include <QDebug>

// raw enums
enum ID_SPACE {
    ID_SPACE_ESSENCE	= 0,
    ID_SPACE_ADDON		= 1,
    ID_SPACE_TALK		= 2,
    ID_SPACE_FACE		= 3,
    ID_SPACE_RECIPE		= 4,
    ID_SPACE_CONFIG		= 5,
};

enum DATA_TYPE {
    DT_INVALID					= 0,
    DT_EQUIPMENT_ADDON			,
    DT_WEAPON_MAJOR_TYPE		,
    DT_WEAPON_SUB_TYPE			,
    DT_WEAPON_ESSENCE			,

    DT_ARMOR_MAJOR_TYPE			,
    DT_ARMOR_SUB_TYPE			,
    DT_ARMOR_ESSENCE			,
    DT_DECORATION_MAJOR_TYPE	,
    DT_DECORATION_SUB_TYPE		,

    DT_DECORATION_ESSENCE		= 10,
    DT_MEDICINE_MAJOR_TYPE		,
    DT_MEDICINE_SUB_TYPE		,
    DT_MEDICINE_ESSENCE			,
    DT_MATERIAL_MAJOR_TYPE		,

    DT_MATERIAL_SUB_TYPE		,
    DT_MATERIAL_ESSENCE			,
    DT_DAMAGERUNE_SUB_TYPE		,
    DT_DAMAGERUNE_ESSENCE		,
    DT_ARMORRUNE_SUB_TYPE		,

    DT_ARMORRUNE_ESSENCE		= 20,
    DT_SKILLTOME_SUB_TYPE		,
    DT_SKILLTOME_ESSENCE		,
    DT_FLYSWORD_ESSENCE			,
    DT_WINGMANWING_ESSENCE		,

    DT_TOWNSCROLL_ESSENCE		,
    DT_UNIONSCROLL_ESSENCE		,
    DT_REVIVESCROLL_ESSENCE		,
    DT_ELEMENT_ESSENCE			,
    DT_TASKMATTER_ESSENCE		,

    DT_TOSSMATTER_ESSENCE		= 30,
    DT_PROJECTILE_TYPE			,
    DT_PROJECTILE_ESSENCE		,
    DT_QUIVER_SUB_TYPE			,
    DT_QUIVER_ESSENCE			,

    DT_STONE_SUB_TYPE			,
    DT_STONE_ESSENCE			,
    DT_MONSTER_ADDON			,
    DT_MONSTER_TYPE				,
    DT_MONSTER_ESSENCE			,

    DT_NPC_TALK_SERVICE			= 40,
    DT_NPC_SELL_SERVICE			,
    DT_NPC_BUY_SERVICE			,
    DT_NPC_REPAIR_SERVICE		,
    DT_NPC_INSTALL_SERVICE		,

    DT_NPC_UNINSTALL_SERVICE	,
    DT_NPC_TASK_IN_SERVICE		,
    DT_NPC_TASK_OUT_SERVICE		,
    DT_NPC_TASK_MATTER_SERVICE	,
    DT_NPC_SKILL_SERVICE		,

    DT_NPC_HEAL_SERVICE			= 50,
    DT_NPC_TRANSMIT_SERVICE		,
    DT_NPC_TRANSPORT_SERVICE	,
    DT_NPC_PROXY_SERVICE		,
    DT_NPC_STORAGE_SERVICE		,

    DT_NPC_MAKE_SERVICE			,
    DT_NPC_DECOMPOSE_SERVICE	,
    DT_NPC_TYPE					,
    DT_NPC_ESSENCE				,
    DT_TALK_PROC				,

    DT_FACE_TEXTURE_ESSENCE		= 60,
    DT_FACE_SHAPE_ESSENCE		,
    DT_FACE_EMOTION_TYPE		,
    DT_FACE_EXPRESSION_ESSENCE	,
    DT_FACE_HAIR_ESSENCE		,

    DT_FACE_MOUSTACHE_ESSENCE	,
    DT_COLORPICKER_ESSENCE		,
    DT_CUSTOMIZEDATA_ESSENCE	,
    DT_RECIPE_MAJOR_TYPE		,
    DT_RECIPE_SUB_TYPE			,

    DT_RECIPE_ESSENCE			= 70,
    DT_ENEMY_FACTION_CONFIG		,
    DT_CHARRACTER_CLASS_CONFIG	,
    DT_PARAM_ADJUST_CONFIG		,
    DT_PLAYER_ACTION_INFO_CONFIG,

    DT_TASKDICE_ESSENCE			= 75,
    DT_TASKNORMALMATTER_ESSENCE	,
    DT_FACE_FALING_ESSENCE		,
    DT_PLAYER_LEVELEXP_CONFIG	,
    DT_MINE_TYPE,

    DT_MINE_ESSENCE				= 80,
    DT_NPC_IDENTIFY_SERVICE		,
    DT_FASHION_MAJOR_TYPE		,
    DT_FASHION_SUB_TYPE			,
    DT_FASHION_ESSENCE			,

    DT_FACETICKET_MAJOR_TYPE	= 85,
    DT_FACETICKET_SUB_TYPE,
    DT_FACETICKET_ESSENCE,
    DT_FACEPILL_MAJOR_TYPE,
    DT_FACEPILL_SUB_TYPE,

    DT_FACEPILL_ESSENCE			= 90,
    DT_SUITE_ESSENCE,
    DT_GM_GENERATOR_TYPE,
    DT_GM_GENERATOR_ESSENCE,
    DT_PET_TYPE,

    DT_PET_ESSENCE				= 95,
    DT_PET_EGG_ESSENCE,
    DT_PET_FOOD_ESSENCE,
    DT_PET_FACETICKET_ESSENCE,
    DT_FIREWORKS_ESSENCE,

    DT_WAR_TANKCALLIN_ESSENCE	= 100,
    DT_NPC_WAR_TOWERBUILD_SERVICE,
    DT_PLAYER_SECONDLEVEL_CONFIG,
    DT_NPC_RESETPROP_SERVICE,
    DT_NPC_PETNAME_SERVICE,

    DT_NPC_PETLEARNSKILL_SERVICE  = 105,
    DT_NPC_PETFORGETSKILL_SERVICE,
    DT_SKILLMATTER_ESSENCE,
    DT_REFINE_TICKET_ESSENCE,
    DT_DESTROYING_ESSENCE,

    DT_NPC_EQUIPBIND_SERVICE	  = 110,
    DT_NPC_EQUIPDESTROY_SERVICE,
    DT_NPC_EQUIPUNDESTROY_SERVICE,
    DT_BIBLE_ESSENCE,
    DT_SPEAKER_ESSENCE,

    DT_AUTOHP_ESSENCE			  = 115,
    DT_AUTOMP_ESSENCE,
    DT_DOUBLE_EXP_ESSENCE,
    DT_TRANSMITSCROLL_ESSENCE,
    DT_DYE_TICKET_ESSENCE,

    DT_GOBLIN_ESSENCE			= 120,
    DT_GOBLIN_EQUIP_TYPE,
    DT_GOBLIN_EQUIP_ESSENCE,
    DT_GOBLIN_EXPPILL_ESSENCE,
    DT_SELL_CERTIFICATE_ESSENCE,

    DT_TARGET_ITEM_ESSENCE		= 125,
    DT_LOOK_INFO_ESSENCE,
    DT_UPGRADE_PRODUCTION_CONFIG,
    DT_ACC_STORAGE_BLACKLIST_CONFIG,
    DT_FACE_HAIR_TEXTURE_MAP,

    DT_MULTI_EXP_CONFIG         = 130,
    DT_INC_SKILL_ABILITY_ESSENCE,
    DT_GOD_EVIL_CONVERT_CONFIG,
    DT_WEDDING_CONFIG,
    DT_WEDDING_BOOKCARD_ESSENCE,

    DT_WEDDING_INVITECARD_ESSENCE	=	135,
    DT_SHARPENER_ESSENCE,
    DT_FACE_THIRDEYE_ESSENCE,
    DT_FACTION_FORTRESS_CONFIG,
    DT_FACTION_BUILDING_SUB_TYPE,

    DT_FACTION_BUILDING_ESSENCE	=	140,
    DT_FACTION_MATERIAL_ESSENCE,
    DT_CONGREGATE_ESSENCE,
    DT_ENGRAVE_MAJOR_TYPE,
    DT_ENGRAVE_SUB_TYPE,

    DT_ENGRAVE_ESSENCE	= 145,
    DT_NPC_ENGRAVE_SERVICE,
    DT_NPC_RANDPROP_SERVICE,
    DT_RANDPROP_TYPE,
    DT_RANDPROP_ESSENCE,

    DT_WIKI_TABOO_CONFIG = 150,
    DT_FORCE_CONFIG,
    DT_FORCE_TOKEN_ESSENCE,
    DT_NPC_FORCE_SERVICE,
    DT_PLAYER_DEATH_DROP_CONFIG,

    DT_DYNSKILLEQUIP_ESSENCE = 155,
    DT_CONSUME_POINTS_CONFIG,
    DT_ONLINE_AWARDS_CONFIG,
    DT_COUNTRY_CONFIG,
    DT_GM_ACTIVITY_CONFIG,

    DT_FASHION_WEAPON_CONFIG = 160,
    DT_PET_EVOLVE_CONFIG,
    DT_PET_EVOLVED_SKILL_CONFIG,
    DT_MONEY_CONVERTIBLE_ESSENCE,
    DT_STONE_CHANGE_RECIPE_TYPE,

    DT_STONE_CHANGE_RECIPE = 165,
    DT_MERIDIAN_CONFIG,
    DT_PET_EVOLVED_SKILL_RAND_CONFIG,
    DT_AUTOTASK_DISPLAY_CONFIG,
    DT_TOUCH_SHOP_CONFIG,

    DT_TITLE_CONFIG,
    DT_COMPLEX_TITLE_CONFIG,
    DT_MONSTER_SPIRIT_ESSENCE,
    DT_PLAYER_SPIRIT_CONFIG,
    DT_PLAYER_REINCARNATION_CONFIG,

    DT_HISTORY_STAGE_CONFIG,
    DT_HISTORY_ADVANCE_CONFIG,
    DT_AUTOTEAM_CONFIG,
    DT_PLAYER_REALM_CONFIG,
    DT_CHARIOT_CONFIG,

    DT_CHARIOT_WAR_CONFIG,
    DT_POKER_LEVELEXP_CONFIG,
    DT_POKER_SUITE_ESSENCE,
    DT_POKER_DICE_ESSENCE,
    DT_POKER_SUB_TYPE,

    DT_POKER_ESSENCE,
    DT_TOKEN_SHOP_CONFIG,
    DT_SHOP_TOKEN_ESSENCE,
    DT_GT_CONFIG,
    DT_RAND_SHOP_CONFIG,

    DT_PROFIT_TIME_CONFIG,
    DT_FACTION_PVP_CONFIG,
    DT_UNIVERSAL_TOKEN_ESSENCE,
    DT_TASK_LIST_CONFIG,
    DT_TASK_DICE_BY_WEIGHT_CONFIG,

    DT_FASHION_SUITE_ESSENCE,
    DT_FASHION_BEST_COLOR_CONFIG,
    DT_SIGN_AWARD_CONFIG,
    DT_ASTROLABE_ESSENCE,
    DT_ASTROLABE_RANDOM_ADDON_ESSENCE,

    DT_ASTROLABE_INC_INNER_POINT_VALUE_ESSENCE,
    DT_ASTROLABE_INC_EXP_ESSENCE,
    DT_ITEM_PACKAGE_BY_PROFESSION_ESSENCE,
    DT_ASTROLABE_LEVELEXP_CONFIG,
    DT_ASTROLABE_ADDON_RANDOM_CONFIG,

    DT_ASTROLABE_APPEARANCE_CONFIG,
    DT_EQUIP_MAKE_HOLE_CONFIG,
    DT_SOLO_TOWER_CHALLENGE_LEVEL_CONFIG,
    DT_SOLO_TOWER_CHALLENGE_AWARD_PAGE_CONFIG,
    DT_SOLO_TOWER_CHALLENGE_AWARD_LIST_CONFIG,

    DT_SOLO_TOWER_CHALLENGE_SCORE_COST_CONFIG,
    DT_MNFACTION_WAR_CONFIG,
    DT_NPC_CROSS_SERVER_SERVICE,
    DT_FIREWORKS2_ESSENCE,
    DT_FIX_POSITION_TRANSMIT_ESSENCE,

    DT_MAX,

};

elements::space_id dt_to_space(elements::data_type dt) {
    static const std::map<DATA_TYPE, ID_SPACE> _ {
                                                 { DT_EQUIPMENT_ADDON, ID_SPACE_ADDON },
                                                 { DT_WEAPON_MAJOR_TYPE, ID_SPACE_ESSENCE },
                                                 { DT_WEAPON_SUB_TYPE, ID_SPACE_ESSENCE },
                                                 { DT_WEAPON_ESSENCE, ID_SPACE_ESSENCE },
                                                 { DT_ARMOR_MAJOR_TYPE, ID_SPACE_ESSENCE },
                                                 { DT_ARMOR_SUB_TYPE, ID_SPACE_ESSENCE },
                                                 { DT_ARMOR_ESSENCE, ID_SPACE_ESSENCE },
                                                 { DT_DECORATION_MAJOR_TYPE, ID_SPACE_ESSENCE },
                                                 { DT_DECORATION_SUB_TYPE, ID_SPACE_ESSENCE },
                                                 { DT_DECORATION_ESSENCE, ID_SPACE_ESSENCE },
                                                 { DT_MEDICINE_MAJOR_TYPE, ID_SPACE_ESSENCE },
                                                 { DT_MEDICINE_SUB_TYPE, ID_SPACE_ESSENCE },
                                                 { DT_MEDICINE_ESSENCE, ID_SPACE_ESSENCE },
                                                 { DT_MATERIAL_MAJOR_TYPE, ID_SPACE_ESSENCE },
                                                 { DT_MATERIAL_SUB_TYPE, ID_SPACE_ESSENCE },
                                                 { DT_MATERIAL_ESSENCE, ID_SPACE_ESSENCE },
                                                 { DT_DAMAGERUNE_SUB_TYPE, ID_SPACE_ESSENCE },
                                                 { DT_DAMAGERUNE_ESSENCE, ID_SPACE_ESSENCE },
                                                 { DT_ARMORRUNE_SUB_TYPE, ID_SPACE_ESSENCE },
                                                 { DT_ARMORRUNE_ESSENCE, ID_SPACE_ESSENCE },
                                                 { DT_SKILLTOME_SUB_TYPE, ID_SPACE_ESSENCE },
                                                 { DT_SKILLTOME_ESSENCE, ID_SPACE_ESSENCE },
                                                 { DT_SHOP_TOKEN_ESSENCE, ID_SPACE_ESSENCE },
                                                 { DT_UNIVERSAL_TOKEN_ESSENCE, ID_SPACE_ESSENCE },
                                                 { DT_FASHION_SUITE_ESSENCE, ID_SPACE_ESSENCE },
                                                 { DT_ASTROLABE_ESSENCE, ID_SPACE_ESSENCE },
                                                 { DT_ASTROLABE_RANDOM_ADDON_ESSENCE, ID_SPACE_ESSENCE },
                                                 { DT_ASTROLABE_INC_INNER_POINT_VALUE_ESSENCE, ID_SPACE_ESSENCE },
                                                 { DT_ASTROLABE_INC_EXP_ESSENCE, ID_SPACE_ESSENCE },
                                                 { DT_ITEM_PACKAGE_BY_PROFESSION_ESSENCE, ID_SPACE_ESSENCE },
                                                 { DT_FACTION_BUILDING_SUB_TYPE, ID_SPACE_ESSENCE },
                                                 { DT_FACTION_BUILDING_ESSENCE, ID_SPACE_ESSENCE },
                                                 { DT_FACTION_MATERIAL_ESSENCE, ID_SPACE_ESSENCE },
                                                 { DT_FLYSWORD_ESSENCE, ID_SPACE_ESSENCE },
                                                 { DT_WINGMANWING_ESSENCE, ID_SPACE_ESSENCE },
                                                 { DT_TOWNSCROLL_ESSENCE, ID_SPACE_ESSENCE },
                                                 { DT_TRANSMITSCROLL_ESSENCE, ID_SPACE_ESSENCE },
                                                 { DT_UNIONSCROLL_ESSENCE, ID_SPACE_ESSENCE },
                                                 { DT_REVIVESCROLL_ESSENCE, ID_SPACE_ESSENCE },
                                                 { DT_ELEMENT_ESSENCE, ID_SPACE_ESSENCE },
                                                 { DT_TASKMATTER_ESSENCE, ID_SPACE_ESSENCE },
                                                 { DT_TOSSMATTER_ESSENCE, ID_SPACE_ESSENCE },
                                                 { DT_PROJECTILE_TYPE, ID_SPACE_ESSENCE },
                                                 { DT_PROJECTILE_ESSENCE, ID_SPACE_ESSENCE },
                                                 { DT_QUIVER_SUB_TYPE, ID_SPACE_ESSENCE },
                                                 { DT_QUIVER_ESSENCE, ID_SPACE_ESSENCE },
                                                 { DT_STONE_SUB_TYPE, ID_SPACE_ESSENCE },
                                                 { DT_STONE_ESSENCE, ID_SPACE_ESSENCE },
                                                 { DT_MONSTER_ADDON, ID_SPACE_ADDON },
                                                 { DT_MONSTER_TYPE, ID_SPACE_ESSENCE },
                                                 { DT_MONSTER_ESSENCE, ID_SPACE_ESSENCE },
                                                 { DT_NPC_TALK_SERVICE, ID_SPACE_ESSENCE },
                                                 { DT_NPC_SELL_SERVICE, ID_SPACE_ESSENCE },
                                                 { DT_NPC_BUY_SERVICE, ID_SPACE_ESSENCE },
                                                 { DT_NPC_REPAIR_SERVICE, ID_SPACE_ESSENCE },
                                                 { DT_NPC_INSTALL_SERVICE, ID_SPACE_ESSENCE },
                                                 { DT_NPC_UNINSTALL_SERVICE, ID_SPACE_ESSENCE },
                                                 { DT_NPC_TASK_IN_SERVICE, ID_SPACE_ESSENCE },
                                                 { DT_NPC_TASK_OUT_SERVICE, ID_SPACE_ESSENCE },
                                                 { DT_NPC_TASK_MATTER_SERVICE, ID_SPACE_ESSENCE },
                                                 { DT_NPC_SKILL_SERVICE, ID_SPACE_ESSENCE },
                                                 { DT_NPC_HEAL_SERVICE, ID_SPACE_ESSENCE },
                                                 { DT_NPC_TRANSMIT_SERVICE, ID_SPACE_ESSENCE },
                                                 { DT_NPC_TRANSPORT_SERVICE, ID_SPACE_ESSENCE },
                                                 { DT_NPC_PROXY_SERVICE, ID_SPACE_ESSENCE },
                                                 { DT_NPC_STORAGE_SERVICE, ID_SPACE_ESSENCE },
                                                 { DT_NPC_MAKE_SERVICE, ID_SPACE_ESSENCE },
                                                 { DT_NPC_DECOMPOSE_SERVICE, ID_SPACE_ESSENCE },
                                                 { DT_NPC_TYPE, ID_SPACE_ESSENCE },
                                                 { DT_NPC_ESSENCE, ID_SPACE_ESSENCE },
                                                 { DT_TALK_PROC, ID_SPACE_TALK },
                                                 { DT_FACE_TEXTURE_ESSENCE, ID_SPACE_FACE },
                                                 { DT_FACE_SHAPE_ESSENCE, ID_SPACE_FACE },
                                                 { DT_FACE_EMOTION_TYPE, ID_SPACE_FACE },
                                                 { DT_FACE_EXPRESSION_ESSENCE, ID_SPACE_FACE },
                                                 { DT_FACE_HAIR_ESSENCE, ID_SPACE_FACE },
                                                 { DT_FACE_MOUSTACHE_ESSENCE, ID_SPACE_FACE },
                                                 { DT_COLORPICKER_ESSENCE, ID_SPACE_FACE },
                                                 { DT_CUSTOMIZEDATA_ESSENCE, ID_SPACE_FACE },
                                                 { DT_RECIPE_MAJOR_TYPE, ID_SPACE_RECIPE },
                                                 { DT_RECIPE_SUB_TYPE, ID_SPACE_RECIPE },
                                                 { DT_RECIPE_ESSENCE, ID_SPACE_RECIPE },
                                                 { DT_ENGRAVE_MAJOR_TYPE, ID_SPACE_RECIPE },
                                                 { DT_ENGRAVE_SUB_TYPE, ID_SPACE_RECIPE },
                                                 { DT_ENGRAVE_ESSENCE, ID_SPACE_RECIPE },
                                                 { DT_RANDPROP_TYPE, ID_SPACE_RECIPE },
                                                 { DT_RANDPROP_ESSENCE, ID_SPACE_RECIPE },
                                                 { DT_STONE_CHANGE_RECIPE_TYPE, ID_SPACE_RECIPE },
                                                 { DT_STONE_CHANGE_RECIPE, ID_SPACE_RECIPE },
                                                 { DT_ENEMY_FACTION_CONFIG, ID_SPACE_CONFIG },
                                                 { DT_CHARRACTER_CLASS_CONFIG, ID_SPACE_CONFIG },
                                                 { DT_PARAM_ADJUST_CONFIG, ID_SPACE_CONFIG },
                                                 { DT_PLAYER_ACTION_INFO_CONFIG, ID_SPACE_CONFIG },
                                                 { DT_UPGRADE_PRODUCTION_CONFIG, ID_SPACE_CONFIG },
                                                 { DT_ACC_STORAGE_BLACKLIST_CONFIG, ID_SPACE_CONFIG },
                                                 { DT_PLAYER_DEATH_DROP_CONFIG, ID_SPACE_CONFIG },
                                                 { DT_CONSUME_POINTS_CONFIG, ID_SPACE_CONFIG },
                                                 { DT_ONLINE_AWARDS_CONFIG, ID_SPACE_CONFIG },
                                                 { DT_PET_EVOLVE_CONFIG, ID_SPACE_CONFIG },
                                                 { DT_PET_EVOLVED_SKILL_CONFIG, ID_SPACE_CONFIG },
                                                 { DT_PET_EVOLVED_SKILL_RAND_CONFIG, ID_SPACE_CONFIG },
                                                 { DT_AUTOTASK_DISPLAY_CONFIG, ID_SPACE_CONFIG },
                                                 { DT_PLAYER_SPIRIT_CONFIG, ID_SPACE_CONFIG },
                                                 { DT_HISTORY_STAGE_CONFIG, ID_SPACE_CONFIG },
                                                 { DT_HISTORY_ADVANCE_CONFIG, ID_SPACE_CONFIG },
                                                 { DT_AUTOTEAM_CONFIG, ID_SPACE_CONFIG },
                                                 { DT_CHARIOT_CONFIG, ID_SPACE_CONFIG },
                                                 { DT_CHARIOT_WAR_CONFIG, ID_SPACE_CONFIG },
                                                 { DT_POKER_LEVELEXP_CONFIG, ID_SPACE_CONFIG },
                                                 { DT_GT_CONFIG, ID_SPACE_CONFIG },
                                                 { DT_MERIDIAN_CONFIG, ID_SPACE_CONFIG },
                                                 { DT_MONEY_CONVERTIBLE_ESSENCE, ID_SPACE_ESSENCE },
                                                 { DT_FASHION_WEAPON_CONFIG, ID_SPACE_CONFIG },
                                                 { DT_MULTI_EXP_CONFIG, ID_SPACE_CONFIG },
                                                 { DT_WEDDING_CONFIG, ID_SPACE_CONFIG },
                                                 { DT_GOD_EVIL_CONVERT_CONFIG, ID_SPACE_CONFIG },
                                                 { DT_WIKI_TABOO_CONFIG, ID_SPACE_CONFIG },
                                                 { DT_TASKDICE_ESSENCE, ID_SPACE_ESSENCE },
                                                 { DT_POKER_DICE_ESSENCE, ID_SPACE_ESSENCE },
                                                 { DT_TASKNORMALMATTER_ESSENCE, ID_SPACE_ESSENCE },
                                                 { DT_FACE_FALING_ESSENCE, ID_SPACE_FACE },
                                                 { DT_FACE_THIRDEYE_ESSENCE, ID_SPACE_FACE },
                                                 { DT_PLAYER_LEVELEXP_CONFIG, ID_SPACE_CONFIG },
                                                 { DT_ASTROLABE_LEVELEXP_CONFIG, ID_SPACE_CONFIG },
                                                 { DT_ASTROLABE_ADDON_RANDOM_CONFIG, ID_SPACE_CONFIG },
                                                 { DT_ASTROLABE_APPEARANCE_CONFIG, ID_SPACE_CONFIG },
                                                 { DT_EQUIP_MAKE_HOLE_CONFIG, ID_SPACE_CONFIG },
                                                 { DT_SOLO_TOWER_CHALLENGE_LEVEL_CONFIG, ID_SPACE_CONFIG },
                                                 { DT_SOLO_TOWER_CHALLENGE_AWARD_PAGE_CONFIG, ID_SPACE_CONFIG },
                                                 { DT_SOLO_TOWER_CHALLENGE_AWARD_LIST_CONFIG, ID_SPACE_CONFIG },
                                                 { DT_SOLO_TOWER_CHALLENGE_SCORE_COST_CONFIG, ID_SPACE_CONFIG },
                                                 { DT_MNFACTION_WAR_CONFIG, ID_SPACE_CONFIG },
                                                 { DT_FACTION_FORTRESS_CONFIG, ID_SPACE_CONFIG },
                                                 { DT_FORCE_CONFIG, ID_SPACE_CONFIG },
                                                 { DT_COUNTRY_CONFIG, ID_SPACE_CONFIG },
                                                 { DT_GM_ACTIVITY_CONFIG, ID_SPACE_CONFIG },
                                                 { DT_TOUCH_SHOP_CONFIG, ID_SPACE_CONFIG },
                                                 { DT_TOKEN_SHOP_CONFIG, ID_SPACE_CONFIG },
                                                 { DT_RAND_SHOP_CONFIG, ID_SPACE_CONFIG },
                                                 { DT_PROFIT_TIME_CONFIG, ID_SPACE_CONFIG },
                                                 { DT_FACTION_PVP_CONFIG, ID_SPACE_CONFIG },
                                                 { DT_TASK_LIST_CONFIG, ID_SPACE_CONFIG },
                                                 { DT_TASK_DICE_BY_WEIGHT_CONFIG, ID_SPACE_CONFIG },
                                                 { DT_FASHION_BEST_COLOR_CONFIG, ID_SPACE_CONFIG },
                                                 { DT_SIGN_AWARD_CONFIG, ID_SPACE_CONFIG },
                                                 { DT_TITLE_CONFIG, ID_SPACE_CONFIG },
                                                 { DT_COMPLEX_TITLE_CONFIG, ID_SPACE_CONFIG },
                                                 { DT_MINE_TYPE, ID_SPACE_ESSENCE },
                                                 { DT_MINE_ESSENCE, ID_SPACE_ESSENCE },
                                                 { DT_NPC_IDENTIFY_SERVICE, ID_SPACE_ESSENCE },
                                                 { DT_FASHION_MAJOR_TYPE, ID_SPACE_ESSENCE },
                                                 { DT_FASHION_SUB_TYPE, ID_SPACE_ESSENCE },
                                                 { DT_FASHION_ESSENCE, ID_SPACE_ESSENCE },
                                                 { DT_POKER_SUB_TYPE, ID_SPACE_ESSENCE },
                                                 { DT_POKER_ESSENCE, ID_SPACE_ESSENCE },
                                                 { DT_FACETICKET_MAJOR_TYPE, ID_SPACE_ESSENCE },
                                                 { DT_FACETICKET_SUB_TYPE, ID_SPACE_ESSENCE },
                                                 { DT_FACETICKET_ESSENCE, ID_SPACE_ESSENCE },
                                                 { DT_FACEPILL_MAJOR_TYPE, ID_SPACE_ESSENCE },
                                                 { DT_FACEPILL_SUB_TYPE, ID_SPACE_ESSENCE },
                                                 { DT_FACEPILL_ESSENCE, ID_SPACE_ESSENCE },
                                                 { DT_SUITE_ESSENCE, ID_SPACE_ESSENCE },
                                                 { DT_POKER_SUITE_ESSENCE, ID_SPACE_ESSENCE },
                                                 { DT_GM_GENERATOR_TYPE, ID_SPACE_ESSENCE },
                                                 { DT_GM_GENERATOR_ESSENCE, ID_SPACE_ESSENCE },
                                                 { DT_PET_TYPE, ID_SPACE_ESSENCE },
                                                 { DT_PET_ESSENCE, ID_SPACE_ESSENCE },
                                                 { DT_PET_EGG_ESSENCE, ID_SPACE_ESSENCE },
                                                 { DT_PET_FOOD_ESSENCE, ID_SPACE_ESSENCE },
                                                 { DT_PET_FACETICKET_ESSENCE, ID_SPACE_ESSENCE },
                                                 { DT_FIREWORKS_ESSENCE, ID_SPACE_ESSENCE },
                                                 { DT_FIREWORKS2_ESSENCE, ID_SPACE_ESSENCE },
                                                 { DT_FIX_POSITION_TRANSMIT_ESSENCE, ID_SPACE_ESSENCE },
                                                 { DT_GOBLIN_ESSENCE, ID_SPACE_ESSENCE },
                                                 { DT_GOBLIN_EQUIP_TYPE, ID_SPACE_ESSENCE },
                                                 { DT_GOBLIN_EQUIP_ESSENCE, ID_SPACE_ESSENCE },
                                                 { DT_GOBLIN_EXPPILL_ESSENCE, ID_SPACE_ESSENCE },
                                                 { DT_SELL_CERTIFICATE_ESSENCE, ID_SPACE_ESSENCE },
                                                 { DT_TARGET_ITEM_ESSENCE, ID_SPACE_ESSENCE },
                                                 { DT_LOOK_INFO_ESSENCE, ID_SPACE_ESSENCE },
                                                 { DT_WAR_TANKCALLIN_ESSENCE, ID_SPACE_ESSENCE },
                                                 { DT_NPC_WAR_TOWERBUILD_SERVICE, ID_SPACE_ESSENCE },
                                                 { DT_PLAYER_SECONDLEVEL_CONFIG, ID_SPACE_CONFIG },
                                                 { DT_PLAYER_REINCARNATION_CONFIG, ID_SPACE_CONFIG },
                                                 { DT_PLAYER_REALM_CONFIG, ID_SPACE_CONFIG },
                                                 { DT_NPC_RESETPROP_SERVICE, ID_SPACE_ESSENCE },
                                                 { DT_NPC_PETNAME_SERVICE, ID_SPACE_ESSENCE },
                                                 { DT_NPC_PETLEARNSKILL_SERVICE, ID_SPACE_ESSENCE },
                                                 { DT_NPC_PETFORGETSKILL_SERVICE, ID_SPACE_ESSENCE },
                                                 { DT_SKILLMATTER_ESSENCE, ID_SPACE_ESSENCE },
                                                 { DT_DYNSKILLEQUIP_ESSENCE, ID_SPACE_ESSENCE },
                                                 { DT_INC_SKILL_ABILITY_ESSENCE, ID_SPACE_ESSENCE },
                                                 { DT_WEDDING_BOOKCARD_ESSENCE, ID_SPACE_ESSENCE },
                                                 { DT_WEDDING_INVITECARD_ESSENCE, ID_SPACE_ESSENCE },
                                                 { DT_SHARPENER_ESSENCE, ID_SPACE_ESSENCE },
                                                 { DT_CONGREGATE_ESSENCE, ID_SPACE_ESSENCE },
                                                 { DT_MONSTER_SPIRIT_ESSENCE, ID_SPACE_ESSENCE },
                                                 { DT_DESTROYING_ESSENCE, ID_SPACE_ESSENCE },
                                                 { DT_DOUBLE_EXP_ESSENCE, ID_SPACE_ESSENCE },
                                                 { DT_DYE_TICKET_ESSENCE, ID_SPACE_ESSENCE },
                                                 { DT_REFINE_TICKET_ESSENCE, ID_SPACE_ESSENCE },
                                                 { DT_NPC_EQUIPBIND_SERVICE, ID_SPACE_ESSENCE },
                                                 { DT_NPC_EQUIPDESTROY_SERVICE, ID_SPACE_ESSENCE },
                                                 { DT_NPC_EQUIPUNDESTROY_SERVICE, ID_SPACE_ESSENCE },
                                                 { DT_NPC_ENGRAVE_SERVICE, ID_SPACE_ESSENCE },
                                                 { DT_NPC_RANDPROP_SERVICE, ID_SPACE_ESSENCE },
                                                 { DT_NPC_FORCE_SERVICE, ID_SPACE_ESSENCE },
                                                 { DT_NPC_CROSS_SERVER_SERVICE, ID_SPACE_ESSENCE },
                                                 { DT_BIBLE_ESSENCE, ID_SPACE_ESSENCE },
                                                 { DT_SPEAKER_ESSENCE, ID_SPACE_ESSENCE },
                                                 { DT_AUTOHP_ESSENCE, ID_SPACE_ESSENCE },
                                                 { DT_AUTOMP_ESSENCE, ID_SPACE_ESSENCE },
                                                 { DT_FORCE_TOKEN_ESSENCE, ID_SPACE_ESSENCE },
                                                 { DT_FACE_HAIR_TEXTURE_MAP, ID_SPACE_FACE },
                                                 };

    auto it = _.find(static_cast<DATA_TYPE>(dt)) ;
    if (it != _.end()) {
        return static_cast<elements::space_id>(it->second);
    }
    else {
        // default
        return elements::space_id::essence;
    }
}

bool starts_with(const std::string& full, const std::string& prefix) {
    if (full.length() >= prefix.length()) {
        return (0 == full.compare(0, prefix.length(), prefix));
    } else {
        return false;
    }
}

namespace elements {

meta_type meta_type::parse(const std::string& str) {
    if (str == "int32") {
        return fundamental_meta_type<int32_t>{};
    }
    else if (str == "int64") {
        return fundamental_meta_type<int64_t>{};
    }
    else if (str == "float") {
        return fundamental_meta_type<float>{};
    }
    else if (str == "byte:AUTO") {
        return raw_meta_type{};
    }
    else if (starts_with(str, "string:")) {
        return string_meta_type<char>(std::stoi(str.substr(7)));
    }
    else if (starts_with(str, "wstring:")) {
        return string_meta_type<char16_t>(std::stoi(str.substr(8)));
    }
    else {
        throw std::runtime_error("unknown type in cfg: " + str);
    }
}

std::shared_ptr<list_config> list_config::parse(std::istream& is) {
    /*
        001 - EQUIPMENT_ADDON
        0
        ID;Name;num_params;param1;param2;param3
        int32;wstring:64;int32;int32;int32;int32
     */
    auto config = std::make_shared<list_config>();

    auto read_line = [](std::istream& is, std::string& out, char delim = '\n') -> std::istream& {
        auto& result = std::getline(is, out, delim);
        if (result) {
            while (!out.empty() && std::isspace(out.back())) {
                out.pop_back();
            }
        }
        return result;
    };

    read_line(is >> std::ws, config->caption, '\r');

    std::string offset, field_names, field_types;

    is >> std::ws >> offset;
    read_line(is >> std::ws, field_names);
    read_line(is >> std::ws, field_types);

    static const std::map<std::string, std::size_t> known_offsets {
        { "AUTO", static_cast<std::size_t>(-1) },
        { "0", 0 },
        { "4", 4 }
    };

    auto it = known_offsets.find(offset);
    if (it == known_offsets.end()) {
        throw std::runtime_error("unknown offset: " + offset + " (list " + config->caption + ")");
    }
    config->offset = it->second;

    std::istringstream sfield_names{ field_names }, sfield_types{ field_types };
    std::string field_name, field_type;
    while (read_line(sfield_names, field_name, ';') && read_line(sfield_types, field_type, ';')) {
        config->fields.emplace_back(std::move(field_name), meta_type::parse(field_type));
    }

    static constexpr auto STRING_OUTPUT_LIMIT = 128;
    auto make_short_str = [](std::string s) {
        if (s.length() >= STRING_OUTPUT_LIMIT) {
            s.resize(STRING_OUTPUT_LIMIT);
            s.append("... (truncated)");
        }
        return s;
    };

    if (!sfield_names.eof()) {
        QString str;
        str.sprintf("elements::list_config::load: cannot parse all field names from '%s' (list: %s)", make_short_str(field_names).c_str(), config->caption.c_str());
        throw std::runtime_error(str.toStdString());
    }

    if (!sfield_types.eof()) {
        QString str;
        str.sprintf("elements::list_config::load: cannot parse all field types from '%s' (list: %s)", make_short_str(field_names).c_str(), config->caption.c_str());
        throw std::runtime_error(str.toStdString());
    }

    int idt = -1;
    char sdt[256]{};
    if (sscanf(config->caption.c_str(), "%d - %255s", &idt, sdt) != 2) {
        QString str;
        str.sprintf("elements::list_config::load: cannot parse data_type from caption (list: %s)", config->caption.c_str());
        throw std::runtime_error(str.toStdString());
    }
    config->dt = static_cast<data_type>(idt);
    config->sdt = sdt;
    config->space = dt_to_space(config->dt);

    return config;
}

config::ptr config::load(const std::string& path, uint16_t version) {
    try {
        std::ifstream ifs;
        //ifs.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        ifs.open(path);

        size_t list_count{}, unknown{};
        ifs >> list_count >> unknown;

        //assert(unknown == 58);

        auto pconfig = std::make_shared<elements::config>();

        pconfig->_file_path = path;
        pconfig->_version = version;
        for (std::size_t i = 0; i < list_count; i++) {
            auto list = list_config::parse(ifs);

            std::size_t list_index = static_cast<std::size_t>(list->dt) - 1;
            if (list_index > 10'000) {
                throw std::runtime_error(QString("unexpected dt: %1").arg(static_cast<int>(list->dt)).toStdString());
            }

            pconfig->_list_names[list->sdt] = list->dt;
            if (pconfig->_lists.size() <= list_index) {
                pconfig->_lists.resize(list_index + 1);
            }
            pconfig->_lists[list_index] = std::move(list);
        }

        for (std::size_t i = 0; i < pconfig->_lists.size(); i++) {
            if (!pconfig->_lists[i]) {
                auto dt = i + 1;
                throw std::runtime_error(QString("missing list %1:03d").arg(dt).toStdString());
            }
        }

        return pconfig;
    }
    catch (std::exception& e) {
        throw std::runtime_error(QString("elements::config::load: cannot parse '%1' (%2)").arg(QString::fromStdString(path)).arg(e.what()).toStdString());
    }
}

std::vector<config::ptr> config::load_folder(std::string folder) {
    static const std::regex re{ R"re(PW_(\d\.\d.\d)_v(\d*)\.cfg)re" };

    std::vector<elements::config::ptr> out;
    QDir directory(folder.c_str());

    // Obter a lista de arquivos no diretório
    QFileInfoList fileList = directory.entryInfoList();
    for (QFileInfo &fileInfo : fileList)
    {
        if (!fileInfo.isFile()) continue;
        auto name = fileInfo.fileName().toStdString();
        std::smatch match;
        if (std::regex_search(name, match, re) && match.size() == 3) {
            auto version = std::stoi(match[2]);
            if (0 <= version && version <= std::numeric_limits<uint16_t>::max()) {
                try {
                    out.emplace_back(elements::config::load(fileInfo.fileName().toStdString(), static_cast<uint16_t>(version)));
                }
                catch (std::exception& e) {
                    std::cerr << e.what() << std::endl;
                }
            }
        }
    }

    return out;
}

data_type config::get_dt_by_name(const std::string& name) const {
    auto it = _list_names.find(name);
    if (it == _list_names.end()) {
        QString str;
        str.sprintf("no data_type with name '%s' in config v%d (path: '%s')", name.c_str(), _version, _file_path.c_str());
        throw std::invalid_argument(str.toStdString());
    }
    return it->second;
}

}

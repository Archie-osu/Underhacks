#include "Menu.hpp"

const char* nMenu::szRooms[]{  //All the rooms - ToDo: Find this in memory so I don't have to index this.
	  "room_start"
	, "room_introstory"
	, "room_introimage"
	, "room_intromenu"
	, "room_area1"
	, "room_area1_2"
	, "room_ruins1"
	, "room_ruins2"
	, "room_ruins3"
	, "room_ruins4"
	, "room_ruins5"
	, "room_ruins6"
	, "room_ruins7"
	, "room_ruins7A"
	, "room_ruins8"
	, "room_ruins9"
	, "room_ruins10"
	, "room_ruins11"
	, "room_ruins12A"
	, "room_ruins12"
	, "room_ruins12B"
	, "room_ruins13"
	, "room_ruins14"
	, "room_ruins15A"
	, "room_ruins15B"
	, "room_ruins15C"
	, "room_ruins15D"
	, "room_ruins15E"
	, "room_ruins16"
	, "room_ruins17"
	, "room_ruins18OLD"
	, "room_ruins19"
	, "room_torhouse1"
	, "room_torhouse2"
	, "room_torhouse3"
	, "room_torielroom"
	, "room_asrielroom"
	, "room_kitchen"
	, "room_basement1"
	, "room_basement2"
	, "room_basement3"
	, "room_basement4"
	, "room_basement5"
	, "room_ruinsexit"
	, "room_tundra1"
	, "room_tundra2"
	, "room_tundra3"
	, "room_tundra3A"
	, "room_tundra4"
	, "room_tundra5"
	, "room_tundra6"
	, "room_tundra6A"
	, "room_tundra7"
	, "room_tundra8"
	, "room_tundra8A"
	, "room_tundra9"
	, "room_tundra_spaghetti"
	, "room_tundra_snowpuzz"
	, "room_tundra_xoxosmall"
	, "room_tundra_randoblock"
	, "room_tundra_lesserdog"
	, "room_tundra_icehole"
	, "room_tundra_iceentrance"
	, "room_tundra_iceexit_new"
	, "room_tundra_iceexit"
	, "room_ruinsexit"
	, "room_tundra_poffzone"
	, "room_tundra_dangerbridge"
	, "room_tundra_town"
	, "room_tundra_town2"
	, "room_tundra_dock"
	, "room_tundra_inn"
	, "room_tundra_inn_2f"
	, "room_tundra_grillby"
	, "room_tundra_library"
	, "room_tundra_garage"
	, "room_tundra_sanshouse"
	, "room_tundra_paproom"
	, "room_tundra_sansroom"
	, "(DC) room_tundra_sansroom_dark"
	, "room_tundra_sansbasement"
	, "room_fogroom"
	, "room_water1"
	, "room_water2"
	, "room_water3"
	, "room_water3A"
	, "room_water4"
	, "room_water_bridgepuzz1"
	, "room_water5"
	, "room_water5A"
	, "room_water6"
	, "room_water7"
	, "room_water8"
	, "room_water9"
	, "room_water_savepoint1"
	, "room_water11"
	, "room_water_nicecream"
	, "room_water12"
	, "room_water_shoe"
	, "room_water_bird"
	, "room_water_onionsan"
	, "room_water14"
	, "room_water_piano"
	, "room_water_dogroom"
	, "room_water_statue"
	, "room_water_prewaterfall"
	, "room_water_waterfall"
	, "room_water_waterfall2"
	, "room_water_waterfall3"
	, "room_water_waterfall4"
	, "room_water_preundyne"
	, "room_water_undynebridge"
	, "room_water_undynebridgeend"
	, "room_water_trashzone1"
	, "room_water_trashsavepoint"
	, "room_water_trashzone2"
	, "room_water_friendlyhub"
	, "room_water_undyneyard"
	, "room_water_undynehouse"
	, "room_water_blookyard"
	, "room_water_blookhouse"
	, "room_water_hapstablook"
	, "room_water_farm"
	, "room_water_prebird"
	, "room_water_shop"
	, "room_water_dock"
	, "room_water15"
	, "room_water16"
	, "rum_temi_vilage"
	, "room_water1"
	, "room_water2"
	, "room_water3"
	, "room_water3A"
	, "room_water4"
	, "room_water_bridgepuzz1"
	, "room_water5"
	, "room_water5A"
	, "room_water6"
	, "room_water7"
	, "room_water8"
	, "room_water9"
	, "room_water_savepoint1"
	, "room_water11"
	, "room_water_nicecream"
	, "room_water12"
	, "room_water_shoe"
	, "room_water_bird"
	, "room_water_onionsan"
	, "room_water14"
	, "room_water_piano"
	, "room_water_dogroom"
	, "room_water_statue"
	, "room_water_prewaterfall"
	, "room_water_waterfall"
	, "room_water_waterfall2"
	, "room_water_waterfall3"
	, "room_water_waterfall4"
	, "room_water_preundyne"
	, "room_water_undynebridge"
	, "room_water_undynebridgeend"
	, "room_water_trashzone1"
	, "room_water_trashsavepoint"
	, "room_water_trashzone2"
	, "room_water_friendlyhub"
	, "room_water_undyneyard"
	, "room_water_undynehouse"
	, "room_water_blookyard"
	, "room_water_blookhouse"
	, "room_water_hapstablook"
	, "room_water_farm"
	, "room_water_prebird"
	, "room_water_shop"
	, "room_water_dock"
	, "room_water15"
	, "room_water16"
	, "rum_temii_vilage"
	, "room_water17"
	, "room_water18"
	, "room_water19"
	, "room_water20"
	, "room_water21"
	, "room_water_undynefinal"
	, "room_water_undynefinal2"
	, "room_water_undynefinal3"
	, "room_fire1"
	, "room_fire2"
	, "room_fire_prelab"
	, "room_fire_dock"
	, "room_fire_lab1"
	, "room_fire_lab2"
	, "room_fire3"
	, "room_fire5"
	, "room_fire6"
	, "room_fire6A"
	, "room_fire_lasers1"
	, "room_fire7"
	, "room_fire8"
	, "room_fire_shootguy_2"
	, "room_fire9"
	, "room_fire_shootguy_1"
	, "room_fire_turn"
	, "room_fire_cookingshow"
	, "room_fire_savepoint1"
	, "room_fire_elevator_r1"
	, "room_fire_elevator_r2"
	, "room_water_undynebridge"
	, "room_water_undynebridgeend"
	, "room_fire_hotdog"
	, "room_fire_walkandbranch"
	, "room_fire_sorry"
	, "room_fire_apron"
	, "room_fire10"
	, "room_fire_rpuzzle"
	, "room_fire_mewmew2"
	, "room_fire_boysnightout"
	, "room_fire_newsreport"
	, "room_fire_coreview2"
	, "room_fire_elevator_l2"
	, "room_fire_elevator_l3"
	, "room_fire_spidershop"
	, "room_fire_walkandbranch2"
	, "room_fire_conveyorlaser"
	, "room_fire_shootguy_3"
	, "room_fire_preshootguy4"
	, "room_fire_shootguy_4"
	, "room_fire_savepoint2"
	, "room_fire_spider"
	, "room_fire_pacing"
	, "room_fire_operatest"
	, "room_fire_multitile"
	, "room_fire_hotelfront_1"
	, "room_fire_hotelfront_2"
	, "room_fire_hotellobby"
	, "room_fire_restaurant"
	, "room_fire_hoteldoors"
	, "room_fire_hotelbed"
	, "room_fire_elevator_r3"
	, "room_fire_precore"
	, "room_fire_core1"
	, "room_fire_core2"
	, "room_fire_core3"
	, "room_fire_core4"
	, "room_fire_core5"
	, "room_fire_core_freebattle"
	, "room_fire_core_laserfun"
	, "room_fire_core_branch"
	, "room_fire_core_bottomleft"
	, "room_fire_core_left"
	, "room_fire_core_topleft"
	, "room_fire_core_top"
	, "room_fire_core_topright"
	, "room_fire_core_right"
	, "room_fire_core_bottomright"
	, "room_fire_core_center"
	, "room_fire_shootguy_5"
	, "room_fire_core_treasureleft"
	, "room_fire_core_treasureright"
	, "room_fire_core_warrior"
	, "room_fire_core_bridge"
	, "room_fire_core_premett"
	, "room_fire_core_metttest"
	, "room_fire_core_final"
	, "room_fire_elevator"
	, "room_fire_elevator_l1"
	, "room_fire_finalelevator"
	, "room_castle_elevatorout"
	, "room_castle_precastle"
	, "room_castle_hook"
	, "room_castle_front"
	, "room_asghouse1"
	, "room_asghouse2"
	, "room_asghouse3"
	, "room_asgoreroom"
	, "room_asrielroom_final"
	, "room_kitchen_final"
	, "room_basement1_final"
	, "room_basement2_final"
	, "room_basement3_final"
	, "room_basement4_final"
	, "room_lastruins_corridor"
	, "room_sanscorridor"
	, "room_castle_finalshoehorn"
	, "room_castle_coffins1"
	, "room_castle_coffins2"
	, "room_castle_throneroom"
	, "room_castle_prebarrier"
	, "room_castle_barrier"
	, "room_castle_exit"
	, "room_undertale_end"
	, "room_castle_trueexit"
	, "room_outsideworld"
	, "room_fire_labelevator"
	, "room_fire_finalelevator"
	, "room_truelab_elevatorinside"
	, "room_truelab_elevator"
	, "room_truelab_hall1"
	, "room_truelab_hub"
	, "room_truelab_hall2"
	, "room_truelab_operatingroom"
	, "room_truelab_redlever"
	, "room_truelab_prebed"
	, "room_truelab_bedroom"
	, "room_truelab_mirror"
	, "room_truelab_bluelever"
	, "room_truelab_hall3"
	, "room_truelab_shower"
	, "room_truelab_determination"
	, "room_truelab_tv"
	, "room_truelab_cooler"
	, "room_truelab_greenlever"
	, "room_truelab_fan"
	, "room_truelab_castle_elevator"
	, "room_truelab_prepower"
	, "room_truelab_power"
	, "(DC) room_gaster"
	, "(DC) room_icecave1"
	, "(DC) room_ice_dog"
	, "(DC) room2"
	, "(DC) room_water_fakehallway"
	, "(DC) room_mysteryman"
	, "(DC) room_soundtest"
	, "(DC) TESTROOM"
	, "(DC) room_water_redacted"
	, "(DC) room_water13"
	, "(DC) room_overworld"
	, "(DC) room_overworld3"
	, "(DC) bullettest"
	, "(DC) room_water16A"
	, "(DC) room_end_castroll"
	, "(DC) room_end_highway"
	, "(DC) room_end_beach"
	, "(DC) room_end_metta"
	, "(DC) room_end_school"
	, "(DC) room_end_mtebott"
	, "(DC) room_creditsdodger"
	, "(DC) room_end_myroom"
	, "(DC) room_end_theend"
	, "(DC) room_spritecheck"
	, "(DC) room_joyconfig"
	, "(DC) room_controltest"
	, "(DC) room_f_start"
	, "(DC) room_f_intro"
	, "(DC) room_f_menu"
	, "(DC) room_floweyx (crashes)"
	, "(DC) room_f_phrase (crashes)"
	, "(DC) room_fire4"
	, "(DC) room_fire10_old"
	, "(DC) room_fire10A_old"
	, "(DC) room_tundra_placeholder"
	, "(DC) room_ruins12B_old"
	, "(DC) room_tundra_rollsnow"
	, "(DC) room_water7_older"
	, "(DC) room_meetundyne_old"
	, "(DC) room_water_mushroom"
	, "(DC) room_monsteralign_test"
	, "(DC) room_battle"
	, "(DC) room_floweybattle"
	, "(DC) room_fastbattle"
	, "(DC) room_storybattle"
	, "(DC) room_gameover"
	, "(DC) room_shop1"
	, "(DC) room_shop2"
	, "(DC) room_shop3"
	, "(DC) room_shop4"
	, "(DC) room_shop5"
	, "(DC) room_riverman_transition"
	, "(DC) room_papdate"
	, "(DC) room_adate"
	, "(DC) room_flowey_endchoice"
	, "(DC) room_flowey_regret"
	, "(DC) room_empty"
	, "(DC) room_emptywhite"
	, "(DC) room_emptyblack"
	, "(DC) room_nothingness"
	, "(DC) room_undertale"
	, "(DC) room_of_dog"
	, "(DC) room_quizholder"
	, "(DC) room_friendtest"
	, "(DC) room_bringitinguys"
	, "(DC) room_asrielappears"
	, "(DC) room_goodbyeasriel"
	, "(DC) room_asrielmemory"
	, "(DC) room_asrieltest"
	, "(DC) room_afinaltest"
};

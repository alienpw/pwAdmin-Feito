#ifndef ADDONS_H
#define ADDONS_H

#include "QString"
#include "QList"

struct ItemAddon
{
    int id;
    QString desc;

    ItemAddon(int _id, QString _desc)
    {
        this->id = _id;
        this->desc = _desc;
    }
};
/*
QList<ItemAddon> GetAllAddonsList()
{
    QList<ItemAddon> addons;
    addons.append(ItemAddon(216,"IA_EA_ESS<offsetof(armor_essence,defense)>"));
    addons.append(ItemAddon(217,"IA_EA_ESS<offsetof(armor_essence,defense)>"));
    addons.append(ItemAddon(218,"IA_EA_ESS<offsetof(armor_essence,defense)>"));
    addons.append(ItemAddon(219,"IA_EA_ESS<offsetof(armor_essence,defense)>"));
    addons.append(ItemAddon(220,"IA_EA_ESS<offsetof(armor_essence,defense)>"));

    addons.append(ItemAddon(221,"enhance_defense_scale_addon"));
    addons.append(ItemAddon(222,"enhance_defense_scale_addon"));
    addons.append(ItemAddon(223,"enhance_defense_scale_addon"));
    addons.append(ItemAddon(224,"enhance_defense_scale_addon"));
    addons.append(ItemAddon(225,"enhance_defense_scale_addon"));

    addons.append(ItemAddon(226,"item_armor_enhance_resistance<0>"));
    addons.append(ItemAddon(227,"item_armor_enhance_resistance<0>"));
    addons.append(ItemAddon(228,"item_armor_enhance_resistance<0>"));
    addons.append(ItemAddon(229,"item_armor_enhance_resistance<0>"));
    addons.append(ItemAddon(230,"item_armor_enhance_resistance<0>"));

    addons.append(ItemAddon(231,"item_armor_scale_enhance_resistance<0>"));
    addons.append(ItemAddon(232,"item_armor_scale_enhance_resistance<0>"));
    addons.append(ItemAddon(233,"item_armor_scale_enhance_resistance<0>"));
    addons.append(ItemAddon(234,"item_armor_scale_enhance_resistance<0>"));
    addons.append(ItemAddon(235,"item_armor_scale_enhance_resistance<0>"));

    addons.append(ItemAddon(236,"item_armor_enhance_resistance<1>"));
    addons.append(ItemAddon(237,"item_armor_enhance_resistance<1>"));
    addons.append(ItemAddon(238,"item_armor_enhance_resistance<1>"));
    addons.append(ItemAddon(239,"item_armor_enhance_resistance<1>"));
    addons.append(ItemAddon(240,"item_armor_enhance_resistance<1>"));

    addons.append(ItemAddon(424,"item_armor_scale_enhance_resistance<1>"));
    addons.append(ItemAddon(425,"item_armor_scale_enhance_resistance<1>"));
    addons.append(ItemAddon(426,"item_armor_scale_enhance_resistance<1>"));
    addons.append(ItemAddon(427,"item_armor_scale_enhance_resistance<1>"));
    addons.append(ItemAddon(428,"item_armor_scale_enhance_resistance<1>"));

    addons.append(ItemAddon(429,"item_armor_enhance_resistance<2>"));
    addons.append(ItemAddon(430,"item_armor_enhance_resistance<2>"));
    addons.append(ItemAddon(431,"item_armor_enhance_resistance<2>"));
    addons.append(ItemAddon(432,"item_armor_enhance_resistance<2>"));
    addons.append(ItemAddon(433,"item_armor_enhance_resistance<2>"));

    addons.append(ItemAddon(241,"item_armor_scale_enhance_resistance<2>"));
    addons.append(ItemAddon(242,"item_armor_scale_enhance_resistance<2>"));
    addons.append(ItemAddon(243,"item_armor_scale_enhance_resistance<2>"));
    addons.append(ItemAddon(244,"item_armor_scale_enhance_resistance<2>"));
    addons.append(ItemAddon(245,"item_armor_scale_enhance_resistance<2>"));

    addons.append(ItemAddon(246,"item_armor_enhance_resistance<3>"));
    addons.append(ItemAddon(247,"item_armor_enhance_resistance<3>"));
    addons.append(ItemAddon(248,"item_armor_enhance_resistance<3>"));
    addons.append(ItemAddon(249,"item_armor_enhance_resistance<3>"));
    addons.append(ItemAddon(250,"item_armor_enhance_resistance<3>"));

    addons.append(ItemAddon(251,"item_armor_scale_enhance_resistance<3>"));
    addons.append(ItemAddon(252,"item_armor_scale_enhance_resistance<3>"));
    addons.append(ItemAddon(253,"item_armor_scale_enhance_resistance<3>"));
    addons.append(ItemAddon(254,"item_armor_scale_enhance_resistance<3>"));
    addons.append(ItemAddon(255,"item_armor_scale_enhance_resistance<3>"));

    addons.append(ItemAddon(256,"item_armor_enhance_resistance<4>"));
    addons.append(ItemAddon(257,"item_armor_enhance_resistance<4>"));
    addons.append(ItemAddon(258,"item_armor_enhance_resistance<4>"));
    addons.append(ItemAddon(259,"item_armor_enhance_resistance<4>"));
    addons.append(ItemAddon(260,"item_armor_enhance_resistance<4>"));

    addons.append(ItemAddon(261,"item_armor_scale_enhance_resistance<4>"));
    addons.append(ItemAddon(262,"item_armor_scale_enhance_resistance<4>"));
    addons.append(ItemAddon(263,"item_armor_scale_enhance_resistance<4>"));
    addons.append(ItemAddon(264,"item_armor_scale_enhance_resistance<4>"));
    addons.append(ItemAddon(265,"item_armor_scale_enhance_resistance<4>"));

    addons.append(ItemAddon(266,"IA_EA_ESS<offsetof(armor_essence,hp_enhance)>"));
    addons.append(ItemAddon(267,"IA_EA_ESS<offsetof(armor_essence,hp_enhance)>"));
    addons.append(ItemAddon(268,"IA_EA_ESS<offsetof(armor_essence,hp_enhance)>"));
    addons.append(ItemAddon(269,"IA_EA_ESS<offsetof(armor_essence,hp_enhance)>"));
    addons.append(ItemAddon(270,"IA_EA_ESS<offsetof(armor_essence,hp_enhance)>"));

    addons.append(ItemAddon(271,"IA_EA_ESS_SCALE<offsetof(armor_essence,hp_enhance)>"));
    addons.append(ItemAddon(272,"IA_EA_ESS_SCALE<offsetof(armor_essence,hp_enhance)>"));
    addons.append(ItemAddon(273,"IA_EA_ESS_SCALE<offsetof(armor_essence,hp_enhance)>"));
    addons.append(ItemAddon(274,"IA_EA_ESS_SCALE<offsetof(armor_essence,hp_enhance)>"));
    addons.append(ItemAddon(275,"IA_EA_ESS_SCALE<offsetof(armor_essence,hp_enhance)>"));

    addons.append(ItemAddon(276,"IA_EA_ESS<offsetof(armor_essence,mp_enhance)>"));
    addons.append(ItemAddon(277,"IA_EA_ESS<offsetof(armor_essence,mp_enhance)>"));
    addons.append(ItemAddon(278,"IA_EA_ESS<offsetof(armor_essence,mp_enhance)>"));
    addons.append(ItemAddon(279,"IA_EA_ESS<offsetof(armor_essence,mp_enhance)>"));
    addons.append(ItemAddon(280,"IA_EA_ESS<offsetof(armor_essence,mp_enhance)>"));

    addons.append(ItemAddon(281,"IA_EA_ESS_SCALE<offsetof(armor_essence,mp_enhance)>"));
    addons.append(ItemAddon(282,"IA_EA_ESS_SCALE<offsetof(armor_essence,mp_enhance)>"));
    addons.append(ItemAddon(283,"IA_EA_ESS_SCALE<offsetof(armor_essence,mp_enhance)>"));
    addons.append(ItemAddon(284,"IA_EA_ESS_SCALE<offsetof(armor_essence,mp_enhance)>"));
    addons.append(ItemAddon(285,"IA_EA_ESS_SCALE<offsetof(armor_essence,mp_enhance)>"));

    addons.append(ItemAddon(286,"enhance_speed_addon"));
    addons.append(ItemAddon(287,"enhance_speed_addon"));
    addons.append(ItemAddon(288,"enhance_speed_addon"));
    addons.append(ItemAddon(289,"enhance_speed_addon"));
    addons.append(ItemAddon(290,"enhance_speed_addon"));

    addons.append(ItemAddon(291,"enhance_armor_scale_addon"));
    addons.append(ItemAddon(292,"enhance_armor_scale_addon"));
    addons.append(ItemAddon(293,"enhance_armor_scale_addon"));
    addons.append(ItemAddon(294,"enhance_armor_scale_addon"));
    addons.append(ItemAddon(295,"enhance_armor_scale_addon"));

    addons.append(ItemAddon(296,"enhance_durability_addon"));
    addons.append(ItemAddon(297,"enhance_durability_addon"));
    addons.append(ItemAddon(298,"enhance_durability_addon"));
    addons.append(ItemAddon(299,"enhance_durability_addon"));
    addons.append(ItemAddon(300,"enhance_durability_addon"));

    addons.append(ItemAddon(301,"reduce_require_addon"));
    addons.append(ItemAddon(302,"reduce_require_addon"));
    addons.append(ItemAddon(303,"reduce_require_addon"));
    addons.append(ItemAddon(304,"reduce_require_addon"));
    addons.append(ItemAddon(305,"reduce_require_addon"));

    addons.append(ItemAddon(306,"item_armor_enhance_all_resistance"));
    addons.append(ItemAddon(307,"item_armor_enhance_all_resistance"));
    addons.append(ItemAddon(308,"item_armor_enhance_all_resistance"));
    addons.append(ItemAddon(309,"item_armor_enhance_all_resistance"));
    addons.append(ItemAddon(310,"item_armor_enhance_all_resistance"));

    addons.append(ItemAddon(311,"enhance_damage_reduce_addon"));
    addons.append(ItemAddon(312,"enhance_damage_reduce_addon"));
    addons.append(ItemAddon(313,"enhance_damage_reduce_addon"));
    addons.append(ItemAddon(314,"enhance_damage_reduce_addon"));
    addons.append(ItemAddon(315,"enhance_damage_reduce_addon"));

    addons.append(ItemAddon(316,"item_armor_specific_addon"));
    addons.append(ItemAddon(317,"item_armor_specific_addon"));
    addons.append(ItemAddon(318,"item_armor_specific_addon"));
    addons.append(ItemAddon(319,"item_armor_specific_addon"));
    addons.append(ItemAddon(320,"item_armor_specific_addon"));

    addons.append(ItemAddon(321,"enhance_hpgen_addon"));
    addons.append(ItemAddon(322,"enhance_hpgen_addon"));
    addons.append(ItemAddon(323,"enhance_hpgen_addon"));
    addons.append(ItemAddon(324,"enhance_hpgen_addon"));
    addons.append(ItemAddon(325,"enhance_hpgen_addon"));

    addons.append(ItemAddon(326,"enhance_mpgen_addon"));
    addons.append(ItemAddon(327,"enhance_mpgen_addon"));
    addons.append(ItemAddon(328,"enhance_mpgen_addon"));
    addons.append(ItemAddon(329,"enhance_mpgen_addon"));
    addons.append(ItemAddon(330,"enhance_mpgen_addon"));

    addons.append(ItemAddon(336,"item_addon_random"));

    addons.append(ItemAddon(331,"enhance_attack_speed_addon"));
    addons.append(ItemAddon(337,"enhance_attack_speed_addon"));
    addons.append(ItemAddon(338,"enhance_attack_speed_addon"));
    addons.append(ItemAddon(339,"enhance_attack_speed_addon"));

    addons.append(ItemAddon(332,"reduce_cast_time_addon"));
    addons.append(ItemAddon(333,"reduce_cast_time_addon"));
    addons.append(ItemAddon(334,"reduce_cast_time_addon"));
    addons.append(ItemAddon(335,"reduce_cast_time_addon"));

    addons.append(ItemAddon(341,"IA_ED_ESS<offsetof(decoration_essence,damage)>"));
    addons.append(ItemAddon(342,"IA_ED_ESS<offsetof(decoration_essence,damage)>"));
    addons.append(ItemAddon(343,"IA_ED_ESS<offsetof(decoration_essence,damage)>"));

    addons.append(ItemAddon(344,"item_decoration_scale_enhance_damage"));

    addons.append(ItemAddon(345,"item_decoration_specific_damage_addon"));
    addons.append(ItemAddon(346,"item_decoration_specific_damage_addon"));
    addons.append(ItemAddon(347,"item_decoration_specific_damage_addon"));

    addons.append(ItemAddon(348,"IA_ED_ESS<offsetof(decoration_essence,magic_damage)>"));
    addons.append(ItemAddon(349,"IA_ED_ESS<offsetof(decoration_essence,magic_damage)>"));
    addons.append(ItemAddon(350,"IA_ED_ESS<offsetof(decoration_essence,magic_damage)>"));

    addons.append(ItemAddon(351,"item_decoration_scale_enhance_magic_damage"));

    addons.append(ItemAddon(352,"item_decoration_specific_magic_damage_addon"));
    addons.append(ItemAddon(353,"item_decoration_specific_magic_damage_addon"));
    addons.append(ItemAddon(354,"item_decoration_specific_magic_damage_addon"));

    addons.append(ItemAddon(355,"enhance_attack_speed_addon"));//$$$$$$$$$$$$ 魔法咏唱时间减少，未实现

    addons.append(ItemAddon(356,"enhance_crit_rate"));
    addons.append(ItemAddon(357,"enhance_crit_rate"));
    addons.append(ItemAddon(358,"enhance_crit_rate"));

    addons.append(ItemAddon(359,"IA_ED_ESS<offsetof(decoration_essence,defense)>"));
    addons.append(ItemAddon(360,"IA_ED_ESS<offsetof(decoration_essence,defense)>"));
    addons.append(ItemAddon(361,"IA_ED_ESS<offsetof(decoration_essence,defense)>"));

    addons.append(ItemAddon(362,"enhance_damage_reduce_addon"));
    addons.append(ItemAddon(363,"enhance_damage_reduce_addon"));
    addons.append(ItemAddon(364,"enhance_damage_reduce_addon"));

    addons.append(ItemAddon(365,"item_decoration_enchance_resistance<0>"));
    addons.append(ItemAddon(366,"item_decoration_enchance_resistance<0>"));
    addons.append(ItemAddon(367,"item_decoration_enchance_resistance<0>"));
    addons.append(ItemAddon(368,"item_decoration_enchance_resistance<1>"));
    addons.append(ItemAddon(369,"item_decoration_enchance_resistance<1>"));
    addons.append(ItemAddon(370,"item_decoration_enchance_resistance<1>"));
    addons.append(ItemAddon(371,"item_decoration_enchance_resistance<2>"));
    addons.append(ItemAddon(372,"item_decoration_enchance_resistance<2>"));
    addons.append(ItemAddon(373,"item_decoration_enchance_resistance<2>"));
    addons.append(ItemAddon(374,"item_decoration_enchance_resistance<3>"));
    addons.append(ItemAddon(375,"item_decoration_enchance_resistance<3>"));
    addons.append(ItemAddon(376,"item_decoration_enchance_resistance<3>"));
    addons.append(ItemAddon(377,"item_decoration_enchance_resistance<4>"));
    addons.append(ItemAddon(378,"item_decoration_enchance_resistance<4>"));
    addons.append(ItemAddon(379,"item_decoration_enchance_resistance<4>"));

    addons.append(ItemAddon(380,"item_decoration_enhance_all_resistance"));
    addons.append(ItemAddon(381,"item_decoration_enhance_all_resistance"));
    addons.append(ItemAddon(382,"item_decoration_enhance_all_resistance"));


    addons.append(ItemAddon(383,"enhance_hpgen_addon"));
    addons.append(ItemAddon(384,"enhance_mpgen_addon"));

    addons.append(ItemAddon(385,"empty_addon"));//$$$$$$$$$$$$$ 组队属性没有想好
    addons.append(ItemAddon(386,"empty_addon"));//$$$$$$$$$$$$$ 组队属性没有想好

    addons.append(ItemAddon(387,"enhance_hp_scale_addon"));
    addons.append(ItemAddon(388,"enhance_mp_scale_addon"));

    addons.append(ItemAddon(389,"enhance_attack_scale_addon"));
    addons.append(ItemAddon(390,"enhance_attack_scale_addon"));
    addons.append(ItemAddon(391,"enhance_attack_scale_addon"));

    addons.append(ItemAddon(392,"enhance_armor_scale_addon_single"));
    addons.append(ItemAddon(393,"enhance_armor_scale_addon_single"));
    addons.append(ItemAddon(394,"enhance_armor_scale_addon_single"));

    addons.append(ItemAddon(403,"empty_addon"));//$$$$$$$$$$$$$ 组队属性没有想好

    addons.append(ItemAddon(404,"enhance_exp_addon"));
    addons.append(ItemAddon(405,"enhance_exp_addon"));
    addons.append(ItemAddon(406,"enhance_exp_addon"));

    addons.append(ItemAddon(407,"enhance_durability_addon"));
    addons.append(ItemAddon(408,"enhance_durability_addon"));
    addons.append(ItemAddon(409,"enhance_durability_addon"));

    addons.append(ItemAddon(410,"item_addon_random"));


    addons.append(ItemAddon(411,"enhance_weapon_damage_addon"));
    addons.append(ItemAddon(413,"enhance_weapon_damage_addon"));
    addons.append(ItemAddon(415,"enhance_weapon_damage_addon"));

    addons.append(ItemAddon(412,"enhance_weapon_max_damage_addon"));
    addons.append(ItemAddon(414,"enhance_weapon_max_damage_addon"));
    addons.append(ItemAddon(416,"enhance_weapon_max_damage_addon"));

    addons.append(ItemAddon(417,"enhance_damage_scale_addon"));
    addons.append(ItemAddon(418,"enhance_damage_scale_addon"));
    addons.append(ItemAddon(419,"enhance_damage_scale_addon"));

    addons.append(ItemAddon(420,"enhance_weapon_speed_addon"));
    addons.append(ItemAddon(421,"enhance_weapon_speed_addon"));

    addons.append(ItemAddon(422,"enhance_weapon_magic_addon"));
    addons.append(ItemAddon(434,"enhance_weapon_magic_addon"));
    addons.append(ItemAddon(436,"enhance_weapon_magic_addon"));

    addons.append(ItemAddon(423,"enhance_weapon_max_magic_addon"));
    addons.append(ItemAddon(435,"enhance_weapon_max_magic_addon"));
    addons.append(ItemAddon(437,"enhance_weapon_max_magic_addon"));

    addons.append(ItemAddon(438,"enhance_magic_scale_addon"));
    addons.append(ItemAddon(439,"enhance_magic_scale_addon"));
    addons.append(ItemAddon(440,"enhance_magic_scale_addon"));

    addons.append(ItemAddon(441,"reduce_cast_time_addon"));
    addons.append(ItemAddon(442,"reduce_cast_time_addon"));
    addons.append(ItemAddon(443,"reduce_cast_time_addon"));
    addons.append(ItemAddon(444,"reduce_cast_time_addon"));

    addons.append(ItemAddon(445,"item_skill_addon"));
    addons.append(ItemAddon(446,"item_skill_addon"));
    addons.append(ItemAddon(447,"item_skill_addon"));
    addons.append(ItemAddon(448,"item_skill_addon"));
    addons.append(ItemAddon(449,"item_skill_addon"));
    addons.append(ItemAddon(450,"item_skill_addon"));
    addons.append(ItemAddon(451,"item_skill_addon"));
    addons.append(ItemAddon(452,"item_skill_addon"));
    addons.append(ItemAddon(453,"item_skill_addon"));
    addons.append(ItemAddon(454,"item_skill_addon"));
    addons.append(ItemAddon(455,"item_skill_addon"));
    addons.append(ItemAddon(456,"item_skill_addon"));
    addons.append(ItemAddon(457,"item_skill_addon"));
    addons.append(ItemAddon(458,"item_skill_addon"));
    addons.append(ItemAddon(459,"item_skill_addon"));
    addons.append(ItemAddon(460,"item_skill_addon"));
    addons.append(ItemAddon(461,"item_skill_addon"));

    addons.append(ItemAddon(462,"enhance_attack_scale_addon"));
    addons.append(ItemAddon(463,"enhance_attack_scale_addon"));
    addons.append(ItemAddon(464,"enhance_attack_scale_addon"));

    addons.append(ItemAddon(465,"enhance_durability_addon"));
    addons.append(ItemAddon(467,"enhance_durability_addon"));
    addons.append(ItemAddon(469,"enhance_durability_addon"));

    addons.append(ItemAddon(466,"reduce_require_addon"));
    addons.append(ItemAddon(468,"reduce_require_addon"));
    addons.append(ItemAddon(470,"reduce_require_addon"));

    addons.append(ItemAddon(471,"enhance_weapon_attack_range"));

    addons.append(ItemAddon(472,"item_addon_random"));

    addons.append(ItemAddon(473,"enhance_crit_rate"));
    addons.append(ItemAddon(474,"enhance_crit_rate"));
    addons.append(ItemAddon(475,"enhance_crit_rate"));

    addons.append(ItemAddon(476,"enhance_damage_addon"));
    addons.append(ItemAddon(477,"enhance_defense_addon_1arg"));
    addons.append(ItemAddon(478,"enhance_damage_addon"));
    addons.append(ItemAddon(479,"enhance_defense_addon_1arg"));
    addons.append(ItemAddon(481,"enhance_damage_addon"));
    addons.append(ItemAddon(482,"enhance_defense_addon_1arg"));
    addons.append(ItemAddon(553,"enhance_damage_addon"));
    addons.append(ItemAddon(557,"enhance_defense_addon_1arg"));
    addons.append(ItemAddon(554,"enhance_damage_addon"));
    addons.append(ItemAddon(558,"enhance_defense_addon_1arg"));
    addons.append(ItemAddon(555,"enhance_damage_addon"));
    addons.append(ItemAddon(559,"enhance_defense_addon_1arg"));
    addons.append(ItemAddon(556,"enhance_damage_addon"));
    addons.append(ItemAddon(560,"enhance_defense_addon_1arg"));
    addons.append(ItemAddon(1144,"enhance_damage_addon"));
    addons.append(ItemAddon(1145,"enhance_defense_addon_1arg"));
    addons.append(ItemAddon(1146,"enhance_damage_addon"));
    addons.append(ItemAddon(1147,"enhance_defense_addon_1arg"));
    addons.append(ItemAddon(1148,"enhance_damage_addon"));
    addons.append(ItemAddon(1149,"enhance_defense_addon_1arg"));
    addons.append(ItemAddon(1150,"enhance_damage_addon"));
    addons.append(ItemAddon(1151,"enhance_defense_addon_1arg"));
    addons.append(ItemAddon(1152,"enhance_damage_addon"));
    addons.append(ItemAddon(1153,"enhance_defense_addon_1arg"));

    addons.append(ItemAddon(483,"enhance_magic_damage_addon"));
    addons.append(ItemAddon(484,"enhance_all_resistance_addon"));
    addons.append(ItemAddon(485,"enhance_magic_damage_addon"));
    addons.append(ItemAddon(486,"enhance_all_resistance_addon"));
    addons.append(ItemAddon(488,"enhance_magic_damage_addon"));
    addons.append(ItemAddon(489,"enhance_all_resistance_addon"));

    addons.append(ItemAddon(561,"enhance_magic_damage_addon"));
    addons.append(ItemAddon(565,"enhance_all_resistance_addon"));
    addons.append(ItemAddon(562,"enhance_magic_damage_addon"));
    addons.append(ItemAddon(566,"enhance_all_resistance_addon"));
    addons.append(ItemAddon(563,"enhance_magic_damage_addon"));
    addons.append(ItemAddon(567,"enhance_all_resistance_addon"));
    addons.append(ItemAddon(564,"enhance_magic_damage_addon"));
    addons.append(ItemAddon(568,"enhance_all_resistance_addon"));
    addons.append(ItemAddon(1154,"enhance_magic_damage_addon"));
    addons.append(ItemAddon(1155,"enhance_all_resistance_addon"));
    addons.append(ItemAddon(1156,"enhance_magic_damage_addon"));
    addons.append(ItemAddon(1157,"enhance_all_resistance_addon"));
    addons.append(ItemAddon(1158,"enhance_magic_damage_addon"));
    addons.append(ItemAddon(1159,"enhance_all_resistance_addon"));
    addons.append(ItemAddon(1160,"enhance_magic_damage_addon"));
    addons.append(ItemAddon(1161,"enhance_all_resistance_addon"));
    addons.append(ItemAddon(1162,"enhance_magic_damage_addon"));
    addons.append(ItemAddon(1163,"enhance_all_resistance_addon"));

    addons.append(ItemAddon(490,"enhance_attack_addon"));
    addons.append(ItemAddon(491,"enhance_armor_addon"));
    addons.append(ItemAddon(492,"enhance_attack_addon"));
    addons.append(ItemAddon(493,"enhance_armor_addon"));
    addons.append(ItemAddon(494,"enhance_attack_addon"));
    addons.append(ItemAddon(495,"enhance_armor_addon"));
    addons.append(ItemAddon(569,"enhance_attack_addon"));
    addons.append(ItemAddon(573,"enhance_armor_addon"));
    addons.append(ItemAddon(570,"enhance_attack_addon"));
    addons.append(ItemAddon(574,"enhance_armor_addon"));
    addons.append(ItemAddon(571,"enhance_attack_addon"));
    addons.append(ItemAddon(575,"enhance_armor_addon"));
    addons.append(ItemAddon(572,"enhance_attack_addon"));
    addons.append(ItemAddon(576,"enhance_armor_addon"));
    addons.append(ItemAddon(1164,"enhance_attack_addon"));
    addons.append(ItemAddon(1165,"enhance_armor_addon"));
    addons.append(ItemAddon(1166,"enhance_attack_addon"));
    addons.append(ItemAddon(1167,"enhance_armor_addon"));
    addons.append(ItemAddon(1168,"enhance_attack_addon"));
    addons.append(ItemAddon(1169,"enhance_armor_addon"));
    addons.append(ItemAddon(1170,"enhance_attack_addon"));
    addons.append(ItemAddon(1171,"enhance_armor_addon"));
    addons.append(ItemAddon(1172,"enhance_attack_addon"));
    addons.append(ItemAddon(1173,"enhance_armor_addon"));

    addons.append(ItemAddon(497,"enhance_hp_addon"));
    addons.append(ItemAddon(498,"enhance_hp_addon"));
    addons.append(ItemAddon(499,"enhance_hp_addon"));
    addons.append(ItemAddon(577,"enhance_hp_addon"));
    addons.append(ItemAddon(578,"enhance_hp_addon"));
    addons.append(ItemAddon(579,"enhance_hp_addon"));
    addons.append(ItemAddon(580,"enhance_hp_addon"));
    addons.append(ItemAddon(1174,"enhance_hp_addon"));
    addons.append(ItemAddon(1175,"enhance_hp_addon"));
    addons.append(ItemAddon(1176,"enhance_hp_addon"));
    addons.append(ItemAddon(1177,"enhance_hp_addon"));
    addons.append(ItemAddon(1178,"enhance_hp_addon"));

    addons.append(ItemAddon(500,"enhance_mp_addon"));
    addons.append(ItemAddon(501,"enhance_mp_addon"));
    addons.append(ItemAddon(502,"enhance_mp_addon"));
    addons.append(ItemAddon(581,"enhance_mp_addon"));
    addons.append(ItemAddon(582,"enhance_mp_addon"));
    addons.append(ItemAddon(583,"enhance_mp_addon"));
    addons.append(ItemAddon(584,"enhance_mp_addon"));
    addons.append(ItemAddon(1179,"enhance_mp_addon"));
    addons.append(ItemAddon(1180,"enhance_mp_addon"));
    addons.append(ItemAddon(1181,"enhance_mp_addon"));
    addons.append(ItemAddon(1182,"enhance_mp_addon"));
    addons.append(ItemAddon(1183,"enhance_mp_addon"));

    #define IDMRA(x,y) item_decoration_magic_resistance_addon<x,y>
    addons.append(ItemAddon(512,"IDMRA(0,3)"));
    addons.append(ItemAddon(513,"IDMRA(1,0)"));
    addons.append(ItemAddon(514,"IDMRA(2,4)"));
    addons.append(ItemAddon(515,"IDMRA(3,2)"));
    addons.append(ItemAddon(516,"IDMRA(4,1)"));
    addons.append(ItemAddon(517,"IDMRA(0,3)"));
    addons.append(ItemAddon(518,"IDMRA(1,0)"));
    addons.append(ItemAddon(519,"IDMRA(2,4)"));
    addons.append(ItemAddon(520,"IDMRA(3,2)"));
    addons.append(ItemAddon(521,"IDMRA(4,1)"));
    addons.append(ItemAddon(522,"IDMRA(0,3)"));
    addons.append(ItemAddon(523,"IDMRA(1,0)"));
    addons.append(ItemAddon(524,"IDMRA(2,4)"));
    addons.append(ItemAddon(525,"IDMRA(3,2)"));
    addons.append(ItemAddon(526,"IDMRA(4,1)"));

    #define IAERA(x,y) item_armor_enhance_resistance_addon<x,y>
    addons.append(ItemAddon(528,"IAERA(0,3)"));
    addons.append(ItemAddon(527,"IAERA(0,3)"));
    addons.append(ItemAddon(529,"IAERA(0,3)"));
    addons.append(ItemAddon(530,"IAERA(0,3)"));
    addons.append(ItemAddon(531,"IAERA(0,3)"));

    addons.append(ItemAddon(532,"IAERA(1,0)"));
    addons.append(ItemAddon(533,"IAERA(1,0)"));
    addons.append(ItemAddon(534,"IAERA(1,0)"));
    addons.append(ItemAddon(535,"IAERA(1,0)"));
    addons.append(ItemAddon(536,"IAERA(1,0)"));

    addons.append(ItemAddon(537,"IAERA(2,4)"));
    addons.append(ItemAddon(538,"IAERA(2,4)"));
    addons.append(ItemAddon(539,"IAERA(2,4)"));
    addons.append(ItemAddon(540,"IAERA(2,4)"));
    addons.append(ItemAddon(541,"IAERA(2,4)"));

    addons.append(ItemAddon(542,"IAERA(3,2)"));
    addons.append(ItemAddon(543,"IAERA(3,2)"));
    addons.append(ItemAddon(544,"IAERA(3,2)"));
    addons.append(ItemAddon(545,"IAERA(3,2)"));
    addons.append(ItemAddon(546,"IAERA(3,2)"));

    addons.append(ItemAddon(547,"IAERA(4,1)"));
    addons.append(ItemAddon(548,"IAERA(4,1)"));
    addons.append(ItemAddon(549,"IAERA(4,1)"));
    addons.append(ItemAddon(550,"IAERA(4,1)"));
    addons.append(ItemAddon(551,"IAERA(4,1)"));

    addons.append(ItemAddon(590,"IA_EA_ESS<offsetof(armor_essence,defense)>"));
    addons.append(ItemAddon(598,"IA_EA_ESS<offsetof(armor_essence,defense)>"));
    addons.append(ItemAddon(599,"IA_EA_ESS<offsetof(armor_essence,defense)>"));
    addons.append(ItemAddon(600,"IA_EA_ESS<offsetof(armor_essence,defense)>"));
    addons.append(ItemAddon(601,"IA_EA_ESS<offsetof(armor_essence,defense)>"));

    #define IAERA2(x,y) item_armor_enhance_resistance_addon_2<x,y>
    addons.append(ItemAddon(592,"IAERA2(0,3)"));
    addons.append(ItemAddon(602,"IAERA2(0,3)"));
    addons.append(ItemAddon(603,"IAERA2(0,3)"));
    addons.append(ItemAddon(604,"IAERA2(0,3)"));
    addons.append(ItemAddon(605,"IAERA2(0,3)"));

    addons.append(ItemAddon(606,"IAERA2(1,0)"));
    addons.append(ItemAddon(607,"IAERA2(1,0)"));
    addons.append(ItemAddon(608,"IAERA2(1,0)"));
    addons.append(ItemAddon(609,"IAERA2(1,0)"));
    addons.append(ItemAddon(610,"IAERA2(1,0)"));

    addons.append(ItemAddon(611,"IAERA2(2,4)"));
    addons.append(ItemAddon(612,"IAERA2(2,4)"));
    addons.append(ItemAddon(613,"IAERA2(2,4)"));
    addons.append(ItemAddon(614,"IAERA2(2,4)"));
    addons.append(ItemAddon(615,"IAERA2(2,4)"));

    addons.append(ItemAddon(617,"IAERA2(3,2)"));
    addons.append(ItemAddon(616,"IAERA2(3,2)"));
    addons.append(ItemAddon(618,"IAERA2(3,2)"));
    addons.append(ItemAddon(619,"IAERA2(3,2)"));
    addons.append(ItemAddon(620,"IAERA2(3,2)"));

    addons.append(ItemAddon(621,"IAERA2(4,1)"));
    addons.append(ItemAddon(622,"IAERA2(4,1)"));
    addons.append(ItemAddon(623,"IAERA2(4,1)"));
    addons.append(ItemAddon(624,"IAERA2(4,1)"));
    addons.append(ItemAddon(625,"IAERA2(4,1)"));

    addons.append(ItemAddon(626,"IA_EA_ESS<offsetof(armor_essence,hp_enhance)>"));
    addons.append(ItemAddon(627,"IA_EA_ESS<offsetof(armor_essence,hp_enhance)>"));
    addons.append(ItemAddon(628,"IA_EA_ESS<offsetof(armor_essence,hp_enhance)>"));
    addons.append(ItemAddon(629,"IA_EA_ESS<offsetof(armor_essence,hp_enhance)>"));
    addons.append(ItemAddon(630,"IA_EA_ESS<offsetof(armor_essence,hp_enhance)>"));

    addons.append(ItemAddon(631,"IA_EA_ESS<offsetof(armor_essence,mp_enhance)>"));
    addons.append(ItemAddon(632,"IA_EA_ESS<offsetof(armor_essence,mp_enhance)>"));
    addons.append(ItemAddon(633,"IA_EA_ESS<offsetof(armor_essence,mp_enhance)>"));
    addons.append(ItemAddon(634,"IA_EA_ESS<offsetof(armor_essence,mp_enhance)>"));
    addons.append(ItemAddon(635,"IA_EA_ESS<offsetof(armor_essence,mp_enhance)>"));

    addons.append(ItemAddon(636,"enhance_speed_addon_point"));
    addons.append(ItemAddon(637,"enhance_speed_addon_point"));
    addons.append(ItemAddon(638,"enhance_speed_addon_point"));
    addons.append(ItemAddon(639,"enhance_speed_addon_point"));
    addons.append(ItemAddon(640,"enhance_speed_addon_point"));

    addons.append(ItemAddon(641,"enhance_armor_range_addon"));
    addons.append(ItemAddon(642,"enhance_armor_range_addon"));
    addons.append(ItemAddon(643,"enhance_armor_range_addon"));
    addons.append(ItemAddon(644,"enhance_armor_range_addon"));
    addons.append(ItemAddon(645,"enhance_armor_range_addon"));

    addons.append(ItemAddon(586,"IA_ED_ESS<offsetof(decoration_essence,damage)>"));
    addons.append(ItemAddon(587,"item_decoration_specific_damage_addon"));
    addons.append(ItemAddon(588,"IA_ED_ESS<offsetof(decoration_essence,magic_damage)>"));
    addons.append(ItemAddon(589,"item_decoration_specific_magic_damage_addon"));

    addons.append(ItemAddon(594,"reduce_cast_time_addon"));
    addons.append(ItemAddon(595,"reduce_cast_time_addon"));

    addons.append(ItemAddon(585,"enhance_crit_rate"));
    addons.append(ItemAddon(591,"enhance_crit_rate"));

    addons.append(ItemAddon(593,"IA_ED_ESS<offsetof(decoration_essence,armor)>"));
    addons.append(ItemAddon(596,"IA_ED_ESS<offsetof(decoration_essence,armor)>"));
    addons.append(ItemAddon(597,"IA_ED_ESS<offsetof(decoration_essence,armor)>"));

    //addons.append(ItemAddon(512,"enhance_str_addon2"));

    addons.append(ItemAddon(652 ,"IA_EA_ESS<offsetof(armor_essence,defense)>"));
    addons.append(ItemAddon(653 ,"IA_EA_ESS<offsetof(armor_essence,defense)>"));
    addons.append(ItemAddon(654 ,"IA_EA_ESS<offsetof(armor_essence,defense)>"));
    addons.append(ItemAddon(655 ,"IA_EA_ESS<offsetof(armor_essence,defense)>"));
    addons.append(ItemAddon(656 ,"IA_EA_ESS<offsetof(armor_essence,defense)>"));
    addons.append(ItemAddon(657 ,"IA_EA_ESS<offsetof(armor_essence,defense)>"));
    addons.append(ItemAddon(658 ,"IA_EA_ESS<offsetof(armor_essence,defense)>"));
    addons.append(ItemAddon(659 ,"IA_EA_ESS<offsetof(armor_essence,defense)>"));
    addons.append(ItemAddon(660 ,"IA_EA_ESS<offsetof(armor_essence,defense)>"));
    addons.append(ItemAddon(661 ,"IA_EA_ESS<offsetof(armor_essence,defense)>"));
    addons.append(ItemAddon(1058,"IA_EA_ESS<offsetof(armor_essence,defense)>"));
    addons.append(ItemAddon(1057,"IA_EA_ESS<offsetof(armor_essence,defense)>"));
    addons.append(ItemAddon(1056,"IA_EA_ESS<offsetof(armor_essence,defense)>"));
    addons.append(ItemAddon(1055,"IA_EA_ESS<offsetof(armor_essence,defense)>"));


    addons.append(ItemAddon(662 ,"IA_EA_ESS<offsetof(armor_essence,armor)>"));
    addons.append(ItemAddon(663 ,"IA_EA_ESS<offsetof(armor_essence,armor)>"));
    addons.append(ItemAddon(664 ,"IA_EA_ESS<offsetof(armor_essence,armor)>"));
    addons.append(ItemAddon(665 ,"IA_EA_ESS<offsetof(armor_essence,armor)>"));
    addons.append(ItemAddon(666 ,"IA_EA_ESS<offsetof(armor_essence,armor)>"));
    addons.append(ItemAddon(667 ,"IA_EA_ESS<offsetof(armor_essence,armor)>"));
    addons.append(ItemAddon(668 ,"IA_EA_ESS<offsetof(armor_essence,armor)>"));
    addons.append(ItemAddon(669 ,"IA_EA_ESS<offsetof(armor_essence,armor)>"));
    addons.append(ItemAddon(670 ,"IA_EA_ESS<offsetof(armor_essence,armor)>"));
    addons.append(ItemAddon(671 ,"IA_EA_ESS<offsetof(armor_essence,armor)>"));
    addons.append(ItemAddon(1062,"IA_EA_ESS<offsetof(armor_essence,armor)>"));
    addons.append(ItemAddon(1061,"IA_EA_ESS<offsetof(armor_essence,armor)>"));
    addons.append(ItemAddon(1060,"IA_EA_ESS<offsetof(armor_essence,armor)>"));
    addons.append(ItemAddon(1059,"IA_EA_ESS<offsetof(armor_essence,armor)>"));

    #define IAERA3(x,y) item_armor_enhance_resistance_addon_3<x,y>
    addons.append(ItemAddon(676 ,"IAERA3(0,3)"));
    addons.append(ItemAddon(677 ,"IAERA3(0,3)"));
    addons.append(ItemAddon(678 ,"IAERA3(0,3)"));
    addons.append(ItemAddon(679 ,"IAERA3(0,3)"));
    addons.append(ItemAddon(680 ,"IAERA3(0,3)"));
    addons.append(ItemAddon(681 ,"IAERA3(0,3)"));
    addons.append(ItemAddon(682 ,"IAERA3(0,3)"));
    addons.append(ItemAddon(683 ,"IAERA3(0,3)"));
    addons.append(ItemAddon(684 ,"IAERA3(0,3)"));
    addons.append(ItemAddon(685 ,"IAERA3(0,3)"));
    addons.append(ItemAddon(686 ,"IAERA3(0,3)"));
    addons.append(ItemAddon(1066,"IAERA3(0,3)"));
    addons.append(ItemAddon(1065,"IAERA3(0,3)"));
    addons.append(ItemAddon(1064,"IAERA3(0,3)"));
    addons.append(ItemAddon(1063,"IAERA3(0,3)"));

    addons.append(ItemAddon(693 ,"IAERA3(1,0)"));
    addons.append(ItemAddon(694 ,"IAERA3(1,0)"));
    addons.append(ItemAddon(695 ,"IAERA3(1,0)"));
    addons.append(ItemAddon(696 ,"IAERA3(1,0)"));
    addons.append(ItemAddon(698 ,"IAERA3(1,0)"));
    addons.append(ItemAddon(699 ,"IAERA3(1,0)"));
    addons.append(ItemAddon(700 ,"IAERA3(1,0)"));
    addons.append(ItemAddon(701 ,"IAERA3(1,0)"));
    addons.append(ItemAddon(707 ,"IAERA3(1,0)"));
    addons.append(ItemAddon(708 ,"IAERA3(1,0)"));
    addons.append(ItemAddon(709 ,"IAERA3(1,0)"));
    addons.append(ItemAddon(1070,"IAERA3(1,0)"));
    addons.append(ItemAddon(1069,"IAERA3(1,0)"));
    addons.append(ItemAddon(1068,"IAERA3(1,0)"));
    addons.append(ItemAddon(1067,"IAERA3(1,0)"));

    addons.append(ItemAddon(710 ,"IAERA3(2,4)"));
    addons.append(ItemAddon(711 ,"IAERA3(2,4)"));
    addons.append(ItemAddon(712 ,"IAERA3(2,4)"));
    addons.append(ItemAddon(713 ,"IAERA3(2,4)"));
    addons.append(ItemAddon(714 ,"IAERA3(2,4)"));
    addons.append(ItemAddon(715 ,"IAERA3(2,4)"));
    addons.append(ItemAddon(716 ,"IAERA3(2,4)"));
    addons.append(ItemAddon(717 ,"IAERA3(2,4)"));
    addons.append(ItemAddon(718 ,"IAERA3(2,4)"));
    addons.append(ItemAddon(719 ,"IAERA3(2,4)"));
    addons.append(ItemAddon(720 ,"IAERA3(2,4)"));
    addons.append(ItemAddon(1074,"IAERA3(2,4)"));
    addons.append(ItemAddon(1073,"IAERA3(2,4)"));
    addons.append(ItemAddon(1072,"IAERA3(2,4)"));
    addons.append(ItemAddon(1071,"IAERA3(2,4)"));

    addons.append(ItemAddon(722 ,"IAERA3(3,2)"));
    addons.append(ItemAddon(723 ,"IAERA3(3,2)"));
    addons.append(ItemAddon(724 ,"IAERA3(3,2)"));
    addons.append(ItemAddon(725 ,"IAERA3(3,2)"));
    addons.append(ItemAddon(726 ,"IAERA3(3,2)"));
    addons.append(ItemAddon(727 ,"IAERA3(3,2)"));
    addons.append(ItemAddon(728 ,"IAERA3(3,2)"));
    addons.append(ItemAddon(729 ,"IAERA3(3,2)"));
    addons.append(ItemAddon(730 ,"IAERA3(3,2)"));
    addons.append(ItemAddon(731 ,"IAERA3(3,2)"));
    addons.append(ItemAddon(732 ,"IAERA3(3,2)"));
    addons.append(ItemAddon(1078,"IAERA3(3,2)"));
    addons.append(ItemAddon(1077,"IAERA3(3,2)"));
    addons.append(ItemAddon(1076,"IAERA3(3,2)"));
    addons.append(ItemAddon(1075,"IAERA3(3,2)"));

    addons.append(ItemAddon(733 ,"IAERA3(4,1)"));
    addons.append(ItemAddon(734 ,"IAERA3(4,1)"));
    addons.append(ItemAddon(735 ,"IAERA3(4,1)"));
    addons.append(ItemAddon(736 ,"IAERA3(4,1)"));
    addons.append(ItemAddon(737 ,"IAERA3(4,1)"));
    addons.append(ItemAddon(738 ,"IAERA3(4,1)"));
    addons.append(ItemAddon(739 ,"IAERA3(4,1)"));
    addons.append(ItemAddon(741 ,"IAERA3(4,1)"));
    addons.append(ItemAddon(742 ,"IAERA3(4,1)"));
    addons.append(ItemAddon(743 ,"IAERA3(4,1)"));
    addons.append(ItemAddon(744 ,"IAERA3(4,1)"));
    addons.append(ItemAddon(1082,"IAERA3(4,1)"));
    addons.append(ItemAddon(1081,"IAERA3(4,1)"));
    addons.append(ItemAddon(1080,"IAERA3(4,1)"));
    addons.append(ItemAddon(1079,"IAERA3(4,1)"));

    addons.append(ItemAddon(1124,"enhance_str_addon"));
    addons.append(ItemAddon(1125,"enhance_str_addon"));
    addons.append(ItemAddon(1126,"enhance_str_addon"));
    addons.append(ItemAddon(1127,"enhance_str_addon"));
    addons.append(ItemAddon(1128,"enhance_str_addon"));
    addons.append(ItemAddon(1104,"enhance_str_addon"));
    addons.append(ItemAddon(1105,"enhance_str_addon"));
    addons.append(ItemAddon(1106,"enhance_str_addon"));
    addons.append(ItemAddon(1107,"enhance_str_addon"));
    addons.append(ItemAddon(1108,"enhance_str_addon"));
    addons.append(ItemAddon(1098,"enhance_str_addon"));
    addons.append(ItemAddon(1084,"enhance_str_addon"));
    addons.append(ItemAddon(1085,"enhance_str_addon"));
    addons.append(ItemAddon(1086,"enhance_str_addon"));
    addons.append(ItemAddon(1087,"enhance_str_addon"));

    addons.append(ItemAddon(1088,"enhance_agi_addon"));
    addons.append(ItemAddon(1089,"enhance_agi_addon"));
    addons.append(ItemAddon(1090,"enhance_agi_addon"));
    addons.append(ItemAddon(1091,"enhance_agi_addon"));
    addons.append(ItemAddon(1092,"enhance_agi_addon"));
    addons.append(ItemAddon(1129,"enhance_agi_addon"));
    addons.append(ItemAddon(1130,"enhance_agi_addon"));
    addons.append(ItemAddon(1131,"enhance_agi_addon"));
    addons.append(ItemAddon(1132,"enhance_agi_addon"));
    addons.append(ItemAddon(1133,"enhance_agi_addon"));
    addons.append(ItemAddon(1109,"enhance_agi_addon"));
    addons.append(ItemAddon(1110,"enhance_agi_addon"));
    addons.append(ItemAddon(1111,"enhance_agi_addon"));
    addons.append(ItemAddon(1112,"enhance_agi_addon"));
    addons.append(ItemAddon(1113,"enhance_agi_addon"));

    addons.append(ItemAddon(1114,"enhance_eng_addon"));
    addons.append(ItemAddon(1115,"enhance_eng_addon"));
    addons.append(ItemAddon(1116,"enhance_eng_addon"));
    addons.append(ItemAddon(1117,"enhance_eng_addon"));
    addons.append(ItemAddon(1118,"enhance_eng_addon"));
    addons.append(ItemAddon(1134,"enhance_eng_addon"));
    addons.append(ItemAddon(1135,"enhance_eng_addon"));
    addons.append(ItemAddon(1136,"enhance_eng_addon"));
    addons.append(ItemAddon(1137,"enhance_eng_addon"));
    addons.append(ItemAddon(1138,"enhance_eng_addon"));
    addons.append(ItemAddon(1093,"enhance_eng_addon"));
    addons.append(ItemAddon(1094,"enhance_eng_addon"));
    addons.append(ItemAddon(1095,"enhance_eng_addon"));
    addons.append(ItemAddon(1096,"enhance_eng_addon"));
    addons.append(ItemAddon(1097,"enhance_eng_addon"));

    addons.append(ItemAddon(1099,"enhance_vit_addon"));
    addons.append(ItemAddon(1100,"enhance_vit_addon"));
    addons.append(ItemAddon(1101,"enhance_vit_addon"));
    addons.append(ItemAddon(1102,"enhance_vit_addon"));
    addons.append(ItemAddon(1103,"enhance_vit_addon"));
    addons.append(ItemAddon(1139,"enhance_vit_addon"));
    addons.append(ItemAddon(1140,"enhance_vit_addon"));
    addons.append(ItemAddon(1141,"enhance_vit_addon"));
    addons.append(ItemAddon(1142,"enhance_vit_addon"));
    addons.append(ItemAddon(1143,"enhance_vit_addon"));
    addons.append(ItemAddon(1119,"enhance_vit_addon"));
    addons.append(ItemAddon(1120,"enhance_vit_addon"));
    addons.append(ItemAddon(1121,"enhance_vit_addon"));
    addons.append(ItemAddon(1122,"enhance_vit_addon"));
    addons.append(ItemAddon(1123,"enhance_vit_addon"));

    addons.append(ItemAddon(753 ,"enhance_weapon_damage_addon"));
    addons.append(ItemAddon(754 ,"enhance_weapon_damage_addon"));
    addons.append(ItemAddon(756 ,"enhance_weapon_damage_addon"));
    addons.append(ItemAddon(755 ,"enhance_weapon_damage_addon"));
    addons.append(ItemAddon(757 ,"enhance_weapon_damage_addon"));
    addons.append(ItemAddon(758 ,"enhance_weapon_damage_addon"));
    addons.append(ItemAddon(759 ,"enhance_weapon_damage_addon"));
    addons.append(ItemAddon(760 ,"enhance_weapon_damage_addon"));
    addons.append(ItemAddon(761 ,"enhance_weapon_damage_addon"));
    addons.append(ItemAddon(762 ,"enhance_weapon_damage_addon"));
    addons.append(ItemAddon(763 ,"enhance_weapon_damage_addon"));
    addons.append(ItemAddon(784 ,"enhance_weapon_damage_addon"));
    addons.append(ItemAddon(785 ,"enhance_weapon_damage_addon"));
    addons.append(ItemAddon(786 ,"enhance_weapon_damage_addon"));
    addons.append(ItemAddon(787 ,"enhance_weapon_damage_addon"));
    addons.append(ItemAddon(788 ,"enhance_weapon_damage_addon"));
    addons.append(ItemAddon(789 ,"enhance_weapon_damage_addon"));
    addons.append(ItemAddon(790 ,"enhance_weapon_damage_addon"));
    addons.append(ItemAddon(791 ,"enhance_weapon_damage_addon"));
    addons.append(ItemAddon(792 ,"enhance_weapon_damage_addon"));
    addons.append(ItemAddon(793 ,"enhance_weapon_damage_addon"));
    addons.append(ItemAddon(794 ,"enhance_weapon_damage_addon"));
    addons.append(ItemAddon(994 ,"enhance_weapon_damage_addon"));
    addons.append(ItemAddon(995 ,"enhance_weapon_damage_addon"));
    addons.append(ItemAddon(996 ,"enhance_weapon_damage_addon"));
    addons.append(ItemAddon(997 ,"enhance_weapon_damage_addon"));
    addons.append(ItemAddon(1009,"enhance_weapon_damage_addon"));
    addons.append(ItemAddon(1008,"enhance_weapon_damage_addon"));
    addons.append(ItemAddon(1007,"enhance_weapon_damage_addon"));
    addons.append(ItemAddon(1006,"enhance_weapon_damage_addon"));

    addons.append(ItemAddon(795 ,"enhance_weapon_max_damage_addon"));
    addons.append(ItemAddon(796 ,"enhance_weapon_max_damage_addon"));
    addons.append(ItemAddon(797 ,"enhance_weapon_max_damage_addon"));
    addons.append(ItemAddon(798 ,"enhance_weapon_max_damage_addon"));
    addons.append(ItemAddon(799 ,"enhance_weapon_max_damage_addon"));
    addons.append(ItemAddon(800 ,"enhance_weapon_max_damage_addon"));
    addons.append(ItemAddon(801 ,"enhance_weapon_max_damage_addon"));
    addons.append(ItemAddon(802 ,"enhance_weapon_max_damage_addon"));
    addons.append(ItemAddon(803 ,"enhance_weapon_max_damage_addon"));
    addons.append(ItemAddon(804 ,"enhance_weapon_max_damage_addon"));
    addons.append(ItemAddon(805 ,"enhance_weapon_max_damage_addon"));
    addons.append(ItemAddon(1001,"enhance_weapon_max_damage_addon"));
    addons.append(ItemAddon(1000,"enhance_weapon_max_damage_addon"));
    addons.append(ItemAddon(999 ,"enhance_weapon_max_damage_addon"));
    addons.append(ItemAddon(998 ,"enhance_weapon_max_damage_addon"));
    addons.append(ItemAddon(764 ,"enhance_weapon_max_damage_addon"));
    addons.append(ItemAddon(765 ,"enhance_weapon_max_damage_addon"));
    addons.append(ItemAddon(766 ,"enhance_weapon_max_damage_addon"));
    addons.append(ItemAddon(767 ,"enhance_weapon_max_damage_addon"));
    addons.append(ItemAddon(768 ,"enhance_weapon_max_damage_addon"));
    addons.append(ItemAddon(769 ,"enhance_weapon_max_damage_addon"));
    addons.append(ItemAddon(770 ,"enhance_weapon_max_damage_addon"));
    addons.append(ItemAddon(771 ,"enhance_weapon_max_damage_addon"));
    addons.append(ItemAddon(772 ,"enhance_weapon_max_damage_addon"));
    addons.append(ItemAddon(773 ,"enhance_weapon_max_damage_addon"));
    addons.append(ItemAddon(774 ,"enhance_weapon_max_damage_addon"));
    addons.append(ItemAddon(1003,"enhance_weapon_max_damage_addon"));
    addons.append(ItemAddon(1004,"enhance_weapon_max_damage_addon"));
    addons.append(ItemAddon(1005,"enhance_weapon_max_damage_addon"));
    addons.append(ItemAddon(1002,"enhance_weapon_max_damage_addon"));

    //typedef EPSA_EQ_addon<EQ_PERCENT+offsetof(equip_item::scale_data,damage),DOUBLE_PERCENT> scale_enhance_damage2;
    addons.append(ItemAddon(775,"scale_enhance_damage2"));

    addons.append(ItemAddon(809,"enhance_weapon_magic_addon"));
    addons.append(ItemAddon(810,"enhance_weapon_magic_addon"));
    addons.append(ItemAddon(811,"enhance_weapon_magic_addon"));
    addons.append(ItemAddon(813,"enhance_weapon_magic_addon"));
    addons.append(ItemAddon(814,"enhance_weapon_magic_addon"));
    addons.append(ItemAddon(815,"enhance_weapon_magic_addon"));
    addons.append(ItemAddon(816,"enhance_weapon_magic_addon"));
    addons.append(ItemAddon(817,"enhance_weapon_magic_addon"));
    addons.append(ItemAddon(818,"enhance_weapon_magic_addon"));
    addons.append(ItemAddon(820,"enhance_weapon_magic_addon"));
    addons.append(ItemAddon(821,"enhance_weapon_magic_addon"));
    addons.append(ItemAddon(990,"enhance_weapon_magic_addon"));
    addons.append(ItemAddon(991,"enhance_weapon_magic_addon"));
    addons.append(ItemAddon(992,"enhance_weapon_magic_addon"));
    addons.append(ItemAddon(993,"enhance_weapon_magic_addon"));

    addons.append(ItemAddon(822,"enhance_weapon_max_magic_addon"));
    addons.append(ItemAddon(823,"enhance_weapon_max_magic_addon"));
    addons.append(ItemAddon(824,"enhance_weapon_max_magic_addon"));
    addons.append(ItemAddon(825,"enhance_weapon_max_magic_addon"));
    addons.append(ItemAddon(826,"enhance_weapon_max_magic_addon"));
    addons.append(ItemAddon(827,"enhance_weapon_max_magic_addon"));
    addons.append(ItemAddon(828,"enhance_weapon_max_magic_addon"));
    addons.append(ItemAddon(829,"enhance_weapon_max_magic_addon"));
    addons.append(ItemAddon(830,"enhance_weapon_max_magic_addon"));
    addons.append(ItemAddon(831,"enhance_weapon_max_magic_addon"));
    addons.append(ItemAddon(832,"enhance_weapon_max_magic_addon"));
    addons.append(ItemAddon(989,"enhance_weapon_max_magic_addon"));
    addons.append(ItemAddon(988,"enhance_weapon_max_magic_addon"));
    addons.append(ItemAddon(987,"enhance_weapon_max_magic_addon"));
    addons.append(ItemAddon(986,"enhance_weapon_max_magic_addon"));

    //typedef EPSA_EQ_addon<EQ_PERCENT+offsetof(equip_item::scale_data,magic_damage),DOUBLE_PERCENT> scale_enhance_magic_damage2;
    addons.append(ItemAddon(835,"scale_enhance_magic_damage2"));

    addons.append(ItemAddon(848 ,"IA_ED_ESS<offsetof(decoration_essence,damage)>"));
    addons.append(ItemAddon(849 ,"IA_ED_ESS<offsetof(decoration_essence,damage)>"));
    addons.append(ItemAddon(850 ,"IA_ED_ESS<offsetof(decoration_essence,damage)>"));
    addons.append(ItemAddon(852 ,"IA_ED_ESS<offsetof(decoration_essence,damage)>"));
    addons.append(ItemAddon(857 ,"IA_ED_ESS<offsetof(decoration_essence,damage)>"));
    addons.append(ItemAddon(858 ,"IA_ED_ESS<offsetof(decoration_essence,damage)>"));
    addons.append(ItemAddon(859 ,"IA_ED_ESS<offsetof(decoration_essence,damage)>"));
    addons.append(ItemAddon(860 ,"IA_ED_ESS<offsetof(decoration_essence,damage)>"));
    addons.append(ItemAddon(855 ,"IA_ED_ESS<offsetof(decoration_essence,damage)>"));
    addons.append(ItemAddon(1011,"IA_ED_ESS<offsetof(decoration_essence,damage)>"));
    addons.append(ItemAddon(1010,"IA_ED_ESS<offsetof(decoration_essence,damage)>"));
    addons.append(ItemAddon(1012,"IA_ED_ESS<offsetof(decoration_essence,damage)>"));
    addons.append(ItemAddon(1013,"IA_ED_ESS<offsetof(decoration_essence,damage)>"));

    addons.append(ItemAddon(885 ,"IA_ED_ESS<offsetof(decoration_essence,magic_damage)>"));
    addons.append(ItemAddon(886 ,"IA_ED_ESS<offsetof(decoration_essence,magic_damage)>"));
    addons.append(ItemAddon(887 ,"IA_ED_ESS<offsetof(decoration_essence,magic_damage)>"));
    addons.append(ItemAddon(889 ,"IA_ED_ESS<offsetof(decoration_essence,magic_damage)>"));
    addons.append(ItemAddon(890 ,"IA_ED_ESS<offsetof(decoration_essence,magic_damage)>"));
    addons.append(ItemAddon(891 ,"IA_ED_ESS<offsetof(decoration_essence,magic_damage)>"));
    addons.append(ItemAddon(892 ,"IA_ED_ESS<offsetof(decoration_essence,magic_damage)>"));
    addons.append(ItemAddon(893 ,"IA_ED_ESS<offsetof(decoration_essence,magic_damage)>"));
    addons.append(ItemAddon(895 ,"IA_ED_ESS<offsetof(decoration_essence,magic_damage)>"));
    addons.append(ItemAddon(1018,"IA_ED_ESS<offsetof(decoration_essence,magic_damage)>"));
    addons.append(ItemAddon(1019,"IA_ED_ESS<offsetof(decoration_essence,magic_damage)>"));
    addons.append(ItemAddon(1020,"IA_ED_ESS<offsetof(decoration_essence,magic_damage)>"));
    addons.append(ItemAddon(1022,"IA_ED_ESS<offsetof(decoration_essence,magic_damage)>"));

    addons.append(ItemAddon(862  ,"item_decoration_specific_damage_addon"));
    addons.append(ItemAddon(863  ,"item_decoration_specific_damage_addon"));
    addons.append(ItemAddon(864  ,"item_decoration_specific_damage_addon"));
    addons.append(ItemAddon(865  ,"item_decoration_specific_damage_addon"));
    addons.append(ItemAddon(867  ,"item_decoration_specific_damage_addon"));
    addons.append(ItemAddon(868  ,"item_decoration_specific_damage_addon"));
    addons.append(ItemAddon(869  ,"item_decoration_specific_damage_addon"));
    addons.append(ItemAddon(870  ,"item_decoration_specific_damage_addon"));
    addons.append(ItemAddon(871  ,"item_decoration_specific_damage_addon"));
    addons.append(ItemAddon(1014 ,"item_decoration_specific_damage_addon"));
    addons.append(ItemAddon(1015 ,"item_decoration_specific_damage_addon"));
    addons.append(ItemAddon(1016 ,"item_decoration_specific_damage_addon"));
    addons.append(ItemAddon(1017 ,"item_decoration_specific_damage_addon"));

    addons.append(ItemAddon(896 ,"item_decoration_specific_magic_damage_addon"));
    addons.append(ItemAddon(897 ,"item_decoration_specific_magic_damage_addon"));
    addons.append(ItemAddon(898 ,"item_decoration_specific_magic_damage_addon"));
    addons.append(ItemAddon(899 ,"item_decoration_specific_magic_damage_addon"));
    addons.append(ItemAddon(900 ,"item_decoration_specific_magic_damage_addon"));
    addons.append(ItemAddon(901 ,"item_decoration_specific_magic_damage_addon"));
    addons.append(ItemAddon(902 ,"item_decoration_specific_magic_damage_addon"));
    addons.append(ItemAddon(903 ,"item_decoration_specific_magic_damage_addon"));
    addons.append(ItemAddon(905 ,"item_decoration_specific_magic_damage_addon"));
    addons.append(ItemAddon(1026,"item_decoration_specific_magic_damage_addon"));
    addons.append(ItemAddon(1025,"item_decoration_specific_magic_damage_addon"));
    addons.append(ItemAddon(1024,"item_decoration_specific_magic_damage_addon"));
    addons.append(ItemAddon(1023,"item_decoration_specific_magic_damage_addon"));

    addons.append(ItemAddon(909 ,"IA_ED_ESS<offsetof(decoration_essence,defense)>"));
    addons.append(ItemAddon(910 ,"IA_ED_ESS<offsetof(decoration_essence,defense)>"));
    addons.append(ItemAddon(911 ,"IA_ED_ESS<offsetof(decoration_essence,defense)>"));
    addons.append(ItemAddon(912 ,"IA_ED_ESS<offsetof(decoration_essence,defense)>"));
    addons.append(ItemAddon(913 ,"IA_ED_ESS<offsetof(decoration_essence,defense)>"));
    addons.append(ItemAddon(914 ,"IA_ED_ESS<offsetof(decoration_essence,defense)>"));
    addons.append(ItemAddon(915 ,"IA_ED_ESS<offsetof(decoration_essence,defense)>"));
    addons.append(ItemAddon(916 ,"IA_ED_ESS<offsetof(decoration_essence,defense)>"));
    addons.append(ItemAddon(917 ,"IA_ED_ESS<offsetof(decoration_essence,defense)>"));
    addons.append(ItemAddon(918 ,"IA_ED_ESS<offsetof(decoration_essence,defense)>"));
    addons.append(ItemAddon(919 ,"IA_ED_ESS<offsetof(decoration_essence,defense)>"));
    addons.append(ItemAddon(1027,"IA_ED_ESS<offsetof(decoration_essence,defense)>"));
    addons.append(ItemAddon(1028,"IA_ED_ESS<offsetof(decoration_essence,defense)>"));
    addons.append(ItemAddon(1029,"IA_ED_ESS<offsetof(decoration_essence,defense)>"));
    addons.append(ItemAddon(1030,"IA_ED_ESS<offsetof(decoration_essence,defense)>"));

    addons.append(ItemAddon(920 ,"IA_ED_ESS<offsetof(decoration_essence,armor)>"));
    addons.append(ItemAddon(921 ,"IA_ED_ESS<offsetof(decoration_essence,armor)>"));
    addons.append(ItemAddon(922 ,"IA_ED_ESS<offsetof(decoration_essence,armor)>"));
    addons.append(ItemAddon(923 ,"IA_ED_ESS<offsetof(decoration_essence,armor)>"));
    addons.append(ItemAddon(924 ,"IA_ED_ESS<offsetof(decoration_essence,armor)>"));
    addons.append(ItemAddon(925 ,"IA_ED_ESS<offsetof(decoration_essence,armor)>"));
    addons.append(ItemAddon(926 ,"IA_ED_ESS<offsetof(decoration_essence,armor)>"));
    addons.append(ItemAddon(927 ,"IA_ED_ESS<offsetof(decoration_essence,armor)>"));
    addons.append(ItemAddon(928 ,"IA_ED_ESS<offsetof(decoration_essence,armor)>"));
    addons.append(ItemAddon(929 ,"IA_ED_ESS<offsetof(decoration_essence,armor)>"));
    addons.append(ItemAddon(930 ,"IA_ED_ESS<offsetof(decoration_essence,armor)>"));
    addons.append(ItemAddon(1031,"IA_ED_ESS<offsetof(decoration_essence,armor)>"));
    addons.append(ItemAddon(1032,"IA_ED_ESS<offsetof(decoration_essence,armor)>"));
    addons.append(ItemAddon(1033,"IA_ED_ESS<offsetof(decoration_essence,armor)>"));
    addons.append(ItemAddon(1034,"IA_ED_ESS<offsetof(decoration_essence,armor)>"));

    addons.append(ItemAddon(931 ,"IDMRA(0,3)"));
    addons.append(ItemAddon(932 ,"IDMRA(0,3)"));
    addons.append(ItemAddon(933 ,"IDMRA(0,3)"));
    addons.append(ItemAddon(934 ,"IDMRA(0,3)"));
    addons.append(ItemAddon(935 ,"IDMRA(0,3)"));
    addons.append(ItemAddon(936 ,"IDMRA(0,3)"));
    addons.append(ItemAddon(937 ,"IDMRA(0,3)"));
    addons.append(ItemAddon(938 ,"IDMRA(0,3)"));
    addons.append(ItemAddon(939 ,"IDMRA(0,3)"));
    addons.append(ItemAddon(940 ,"IDMRA(0,3)"));
    addons.append(ItemAddon(941 ,"IDMRA(0,3)"));
    addons.append(ItemAddon(1038,"IDMRA(0,3)"));
    addons.append(ItemAddon(1037,"IDMRA(0,3)"));
    addons.append(ItemAddon(1036,"IDMRA(0,3)"));
    addons.append(ItemAddon(1035,"IDMRA(0,3)"));

    addons.append(ItemAddon(942 ,"IDMRA(1,0)"));
    addons.append(ItemAddon(943 ,"IDMRA(1,0)"));
    addons.append(ItemAddon(944 ,"IDMRA(1,0)"));
    addons.append(ItemAddon(945 ,"IDMRA(1,0)"));
    addons.append(ItemAddon(946 ,"IDMRA(1,0)"));
    addons.append(ItemAddon(947 ,"IDMRA(1,0)"));
    addons.append(ItemAddon(948 ,"IDMRA(1,0)"));
    addons.append(ItemAddon(949 ,"IDMRA(1,0)"));
    addons.append(ItemAddon(950 ,"IDMRA(1,0)"));
    addons.append(ItemAddon(951 ,"IDMRA(1,0)"));
    addons.append(ItemAddon(952 ,"IDMRA(1,0)"));
    addons.append(ItemAddon(1042,"IDMRA(1,0)"));
    addons.append(ItemAddon(1041,"IDMRA(1,0)"));
    addons.append(ItemAddon(1040,"IDMRA(1,0)"));
    addons.append(ItemAddon(1039,"IDMRA(1,0)"));

    addons.append(ItemAddon(964 ,"IDMRA(2,4)"));
    addons.append(ItemAddon(965 ,"IDMRA(2,4)"));
    addons.append(ItemAddon(966 ,"IDMRA(2,4)"));
    addons.append(ItemAddon(967 ,"IDMRA(2,4)"));
    addons.append(ItemAddon(968 ,"IDMRA(2,4)"));
    addons.append(ItemAddon(969 ,"IDMRA(2,4)"));
    addons.append(ItemAddon(970 ,"IDMRA(2,4)"));
    addons.append(ItemAddon(971 ,"IDMRA(2,4)"));
    addons.append(ItemAddon(972 ,"IDMRA(2,4)"));
    addons.append(ItemAddon(973 ,"IDMRA(2,4)"));
    addons.append(ItemAddon(974 ,"IDMRA(2,4)"));
    addons.append(ItemAddon(1050,"IDMRA(2,4)"));
    addons.append(ItemAddon(1049,"IDMRA(2,4)"));
    addons.append(ItemAddon(1048,"IDMRA(2,4)"));
    addons.append(ItemAddon(1047,"IDMRA(2,4)"));

    addons.append(ItemAddon(975 ,"IDMRA(3,2)"));
    addons.append(ItemAddon(976 ,"IDMRA(3,2)"));
    addons.append(ItemAddon(977 ,"IDMRA(3,2)"));
    addons.append(ItemAddon(978 ,"IDMRA(3,2)"));
    addons.append(ItemAddon(979 ,"IDMRA(3,2)"));
    addons.append(ItemAddon(980 ,"IDMRA(3,2)"));
    addons.append(ItemAddon(981 ,"IDMRA(3,2)"));
    addons.append(ItemAddon(982 ,"IDMRA(3,2)"));
    addons.append(ItemAddon(983 ,"IDMRA(3,2)"));
    addons.append(ItemAddon(984 ,"IDMRA(3,2)"));
    addons.append(ItemAddon(985 ,"IDMRA(3,2)"));
    addons.append(ItemAddon(1054,"IDMRA(3,2)"));
    addons.append(ItemAddon(1053,"IDMRA(3,2)"));
    addons.append(ItemAddon(1052,"IDMRA(3,2)"));
    addons.append(ItemAddon(1051,"IDMRA(3,2)"));

    addons.append(ItemAddon(953 ,"IDMRA(4,1)"));
    addons.append(ItemAddon(954 ,"IDMRA(4,1)"));
    addons.append(ItemAddon(956 ,"IDMRA(4,1)"));
    addons.append(ItemAddon(955 ,"IDMRA(4,1)"));
    addons.append(ItemAddon(957 ,"IDMRA(4,1)"));
    addons.append(ItemAddon(958 ,"IDMRA(4,1)"));
    addons.append(ItemAddon(959 ,"IDMRA(4,1)"));
    addons.append(ItemAddon(960 ,"IDMRA(4,1)"));
    addons.append(ItemAddon(961 ,"IDMRA(4,1)"));
    addons.append(ItemAddon(962 ,"IDMRA(4,1)"));
    addons.append(ItemAddon(963 ,"IDMRA(4,1)"));
    addons.append(ItemAddon(1046,"IDMRA(4,1)"));
    addons.append(ItemAddon(1045,"IDMRA(4,1)"));
    addons.append(ItemAddon(1044,"IDMRA(4,1)"));
    addons.append(ItemAddon(1043,"IDMRA(4,1)"));

    #define  STONE_MAGIC_RES_ADDON(x) EPSA_addon<int, POINT_OFF+offsetof(enhanced_param,resistance) + sizeof(int) * (x), POINT>
    #define  STONE_MAGIC_DMG_ADDON(x) EPSA_addon<int, POINT_OFF+offsetof(enhanced_param,addon_damage) + sizeof(int) * (x), POINT>

    addons.append(ItemAddon(672 ,"STONE_MAGIC_DMG_ADDON(0)"));
    addons.append(ItemAddon(673 ,"STONE_MAGIC_RES_ADDON(0)"));
    addons.append(ItemAddon(674 ,"STONE_MAGIC_DMG_ADDON(0)"));
    addons.append(ItemAddon(675 ,"STONE_MAGIC_RES_ADDON(0)"));
    addons.append(ItemAddon(687 ,"STONE_MAGIC_DMG_ADDON(0)"));
    addons.append(ItemAddon(688 ,"STONE_MAGIC_RES_ADDON(0)"));
    addons.append(ItemAddon(689 ,"STONE_MAGIC_DMG_ADDON(0)"));
    addons.append(ItemAddon(690 ,"STONE_MAGIC_RES_ADDON(0)"));
    addons.append(ItemAddon(691 ,"STONE_MAGIC_DMG_ADDON(0)"));
    addons.append(ItemAddon(692 ,"STONE_MAGIC_RES_ADDON(0)"));
    addons.append(ItemAddon(778 ,"STONE_MAGIC_DMG_ADDON(0)"));
    addons.append(ItemAddon(779 ,"STONE_MAGIC_RES_ADDON(0)"));
    addons.append(ItemAddon(776 ,"STONE_MAGIC_DMG_ADDON(0)"));
    addons.append(ItemAddon(777 ,"STONE_MAGIC_RES_ADDON(0)"));
    addons.append(ItemAddon(1184,"STONE_MAGIC_DMG_ADDON(0)"));
    addons.append(ItemAddon(1185,"STONE_MAGIC_RES_ADDON(0)"));
    addons.append(ItemAddon(1186,"STONE_MAGIC_DMG_ADDON(0)"));
    addons.append(ItemAddon(1187,"STONE_MAGIC_RES_ADDON(0)"));
    addons.append(ItemAddon(1188,"STONE_MAGIC_DMG_ADDON(0)"));
    addons.append(ItemAddon(1189,"STONE_MAGIC_RES_ADDON(0)"));
    addons.append(ItemAddon(1190,"STONE_MAGIC_DMG_ADDON(0)"));
    addons.append(ItemAddon(1191,"STONE_MAGIC_RES_ADDON(0)"));
    addons.append(ItemAddon(1192,"STONE_MAGIC_DMG_ADDON(0)"));
    addons.append(ItemAddon(1193,"STONE_MAGIC_RES_ADDON(0)"));

    addons.append(ItemAddon(706 ,"STONE_MAGIC_DMG_ADDON(1)"));
    addons.append(ItemAddon(721 ,"STONE_MAGIC_RES_ADDON(1)"));
    addons.append(ItemAddon(740 ,"STONE_MAGIC_DMG_ADDON(1)"));
    addons.append(ItemAddon(745 ,"STONE_MAGIC_RES_ADDON(1)"));
    addons.append(ItemAddon(746 ,"STONE_MAGIC_DMG_ADDON(1)"));
    addons.append(ItemAddon(747 ,"STONE_MAGIC_RES_ADDON(1)"));
    addons.append(ItemAddon(748 ,"STONE_MAGIC_DMG_ADDON(1)"));
    addons.append(ItemAddon(749 ,"STONE_MAGIC_RES_ADDON(1)"));
    addons.append(ItemAddon(750 ,"STONE_MAGIC_DMG_ADDON(1)"));
    addons.append(ItemAddon(751 ,"STONE_MAGIC_RES_ADDON(1)"));
    addons.append(ItemAddon(780 ,"STONE_MAGIC_DMG_ADDON(1)"));
    addons.append(ItemAddon(781 ,"STONE_MAGIC_RES_ADDON(1)"));
    addons.append(ItemAddon(782 ,"STONE_MAGIC_DMG_ADDON(1)"));
    addons.append(ItemAddon(783 ,"STONE_MAGIC_RES_ADDON(1)"));
    addons.append(ItemAddon(1194,"STONE_MAGIC_DMG_ADDON(1)"));
    addons.append(ItemAddon(1195,"STONE_MAGIC_RES_ADDON(1)"));
    addons.append(ItemAddon(1196,"STONE_MAGIC_DMG_ADDON(1)"));
    addons.append(ItemAddon(1197,"STONE_MAGIC_RES_ADDON(1)"));
    addons.append(ItemAddon(1198,"STONE_MAGIC_DMG_ADDON(1)"));
    addons.append(ItemAddon(1199,"STONE_MAGIC_RES_ADDON(1)"));
    addons.append(ItemAddon(1200,"STONE_MAGIC_DMG_ADDON(1)"));
    addons.append(ItemAddon(1201,"STONE_MAGIC_RES_ADDON(1)"));
    addons.append(ItemAddon(1202,"STONE_MAGIC_DMG_ADDON(1)"));
    addons.append(ItemAddon(1203,"STONE_MAGIC_RES_ADDON(1)"));

    addons.append(ItemAddon(812 ,"STONE_MAGIC_DMG_ADDON(2)"));
    addons.append(ItemAddon(808 ,"STONE_MAGIC_RES_ADDON(2)"));
    addons.append(ItemAddon(819 ,"STONE_MAGIC_DMG_ADDON(2)"));
    addons.append(ItemAddon(833 ,"STONE_MAGIC_RES_ADDON(2)"));
    addons.append(ItemAddon(834 ,"STONE_MAGIC_DMG_ADDON(2)"));
    addons.append(ItemAddon(836 ,"STONE_MAGIC_RES_ADDON(2)"));
    addons.append(ItemAddon(837 ,"STONE_MAGIC_DMG_ADDON(2)"));
    addons.append(ItemAddon(838 ,"STONE_MAGIC_RES_ADDON(2)"));
    addons.append(ItemAddon(839 ,"STONE_MAGIC_DMG_ADDON(2)"));
    addons.append(ItemAddon(840 ,"STONE_MAGIC_RES_ADDON(2)"));
    addons.append(ItemAddon(841 ,"STONE_MAGIC_DMG_ADDON(2)"));
    addons.append(ItemAddon(842 ,"STONE_MAGIC_RES_ADDON(2)"));
    addons.append(ItemAddon(843 ,"STONE_MAGIC_DMG_ADDON(2)"));
    addons.append(ItemAddon(844 ,"STONE_MAGIC_RES_ADDON(2)"));
    addons.append(ItemAddon(1204,"STONE_MAGIC_DMG_ADDON(2)"));
    addons.append(ItemAddon(1205,"STONE_MAGIC_RES_ADDON(2)"));
    addons.append(ItemAddon(1206,"STONE_MAGIC_DMG_ADDON(2)"));
    addons.append(ItemAddon(1207,"STONE_MAGIC_RES_ADDON(2)"));
    addons.append(ItemAddon(1208,"STONE_MAGIC_DMG_ADDON(2)"));
    addons.append(ItemAddon(1209,"STONE_MAGIC_RES_ADDON(2)"));
    addons.append(ItemAddon(1210,"STONE_MAGIC_DMG_ADDON(2)"));
    addons.append(ItemAddon(1211,"STONE_MAGIC_RES_ADDON(2)"));
    addons.append(ItemAddon(1212,"STONE_MAGIC_DMG_ADDON(2)"));
    addons.append(ItemAddon(1213,"STONE_MAGIC_RES_ADDON(2)"));

    addons.append(ItemAddon(845 ,"STONE_MAGIC_DMG_ADDON(3)"));
    addons.append(ItemAddon(846 ,"STONE_MAGIC_RES_ADDON(3)"));
    addons.append(ItemAddon(847 ,"STONE_MAGIC_DMG_ADDON(3)"));
    addons.append(ItemAddon(851 ,"STONE_MAGIC_RES_ADDON(3)"));
    addons.append(ItemAddon(853 ,"STONE_MAGIC_DMG_ADDON(3)"));
    addons.append(ItemAddon(854 ,"STONE_MAGIC_RES_ADDON(3)"));
    addons.append(ItemAddon(856 ,"STONE_MAGIC_DMG_ADDON(3)"));
    addons.append(ItemAddon(861 ,"STONE_MAGIC_RES_ADDON(3)"));
    addons.append(ItemAddon(866 ,"STONE_MAGIC_DMG_ADDON(3)"));
    addons.append(ItemAddon(872 ,"STONE_MAGIC_RES_ADDON(3)"));
    addons.append(ItemAddon(873 ,"STONE_MAGIC_DMG_ADDON(3)"));
    addons.append(ItemAddon(874 ,"STONE_MAGIC_RES_ADDON(3)"));
    addons.append(ItemAddon(875 ,"STONE_MAGIC_DMG_ADDON(3)"));
    addons.append(ItemAddon(876 ,"STONE_MAGIC_RES_ADDON(3)"));
    addons.append(ItemAddon(1214,"STONE_MAGIC_DMG_ADDON(3)"));
    addons.append(ItemAddon(1215,"STONE_MAGIC_RES_ADDON(3)"));
    addons.append(ItemAddon(1216,"STONE_MAGIC_DMG_ADDON(3)"));
    addons.append(ItemAddon(1217,"STONE_MAGIC_RES_ADDON(3)"));
    addons.append(ItemAddon(1218,"STONE_MAGIC_DMG_ADDON(3)"));
    addons.append(ItemAddon(1219,"STONE_MAGIC_RES_ADDON(3)"));
    addons.append(ItemAddon(1220,"STONE_MAGIC_DMG_ADDON(3)"));
    addons.append(ItemAddon(1221,"STONE_MAGIC_RES_ADDON(3)"));
    addons.append(ItemAddon(1222,"STONE_MAGIC_DMG_ADDON(3)"));
    addons.append(ItemAddon(1223,"STONE_MAGIC_RES_ADDON(3)"));

    addons.append(ItemAddon(877 ,"STONE_MAGIC_DMG_ADDON(4)"));
    addons.append(ItemAddon(878 ,"STONE_MAGIC_RES_ADDON(4)"));
    addons.append(ItemAddon(879 ,"STONE_MAGIC_DMG_ADDON(4)"));
    addons.append(ItemAddon(880 ,"STONE_MAGIC_RES_ADDON(4)"));
    addons.append(ItemAddon(881 ,"STONE_MAGIC_DMG_ADDON(4)"));
    addons.append(ItemAddon(882 ,"STONE_MAGIC_RES_ADDON(4)"));
    addons.append(ItemAddon(883 ,"STONE_MAGIC_DMG_ADDON(4)"));
    addons.append(ItemAddon(884 ,"STONE_MAGIC_RES_ADDON(4)"));
    addons.append(ItemAddon(888 ,"STONE_MAGIC_DMG_ADDON(4)"));
    addons.append(ItemAddon(894 ,"STONE_MAGIC_RES_ADDON(4)"));
    addons.append(ItemAddon(904 ,"STONE_MAGIC_DMG_ADDON(4)"));
    addons.append(ItemAddon(906 ,"STONE_MAGIC_RES_ADDON(4)"));
    addons.append(ItemAddon(907 ,"STONE_MAGIC_DMG_ADDON(4)"));
    addons.append(ItemAddon(908 ,"STONE_MAGIC_RES_ADDON(4)"));
    addons.append(ItemAddon(1224,"STONE_MAGIC_DMG_ADDON(4)"));
    addons.append(ItemAddon(1225,"STONE_MAGIC_RES_ADDON(4)"));
    addons.append(ItemAddon(1226,"STONE_MAGIC_DMG_ADDON(4)"));
    addons.append(ItemAddon(1227,"STONE_MAGIC_RES_ADDON(4)"));
    addons.append(ItemAddon(1228,"STONE_MAGIC_DMG_ADDON(4)"));
    addons.append(ItemAddon(1229,"STONE_MAGIC_RES_ADDON(4)"));
    addons.append(ItemAddon(1230,"STONE_MAGIC_DMG_ADDON(4)"));
    addons.append(ItemAddon(1231,"STONE_MAGIC_RES_ADDON(4)"));
    addons.append(ItemAddon(1232,"STONE_MAGIC_DMG_ADDON(4)"));
    addons.append(ItemAddon(1233,"STONE_MAGIC_RES_ADDON(4)"));

    addons.append(ItemAddon(1234,"enhance_mp_addon_2"));
    addons.append(ItemAddon(1235,"enhance_mp_addon_2"));
    addons.append(ItemAddon(1236,"enhance_mp_addon_2"));
    addons.append(ItemAddon(1237,"enhance_mp_addon_2"));
    addons.append(ItemAddon(1238,"enhance_mp_addon_2"));

    addons.append(ItemAddon(1239,"enhance_hp_addon_2"));
    addons.append(ItemAddon(1240,"enhance_hp_addon_2"));
    addons.append(ItemAddon(1241,"enhance_hp_addon_2"));
    addons.append(ItemAddon(1242,"enhance_hp_addon_2"));
    addons.append(ItemAddon(1243,"enhance_hp_addon_2"));

    addons.append(ItemAddon(1244,"enhance_defense_addon"));
    addons.append(ItemAddon(1245,"enhance_defense_addon"));
    addons.append(ItemAddon(1246,"enhance_defense_addon"));
    addons.append(ItemAddon(1247,"enhance_defense_addon"));
    addons.append(ItemAddon(1248,"enhance_defense_addon"));
    addons.append(ItemAddon(1249,"enhance_defense_addon"));
    addons.append(ItemAddon(1250,"enhance_defense_addon"));
    addons.append(ItemAddon(1251,"enhance_defense_addon"));
    addons.append(ItemAddon(1252,"enhance_defense_addon"));
    addons.append(ItemAddon(1253,"enhance_defense_addon"));
    addons.append(ItemAddon(1254,"enhance_defense_addon"));
    addons.append(ItemAddon(1255,"enhance_defense_addon"));
    addons.append(ItemAddon(1256,"enhance_defense_addon"));
    addons.append(ItemAddon(1257,"enhance_defense_addon"));

    addons.append(ItemAddon(1258,"enhance_armor_range_addon"));
    addons.append(ItemAddon(1259,"enhance_armor_range_addon"));
    addons.append(ItemAddon(1260,"enhance_armor_range_addon"));
    addons.append(ItemAddon(1261,"enhance_armor_range_addon"));
    addons.append(ItemAddon(1262,"enhance_armor_range_addon"));
    addons.append(ItemAddon(1263,"enhance_armor_range_addon"));
    addons.append(ItemAddon(1264,"enhance_armor_range_addon"));
    addons.append(ItemAddon(1265,"enhance_armor_range_addon"));
    addons.append(ItemAddon(1266,"enhance_armor_range_addon"));
    addons.append(ItemAddon(1267,"enhance_armor_range_addon"));
    addons.append(ItemAddon(1268,"enhance_armor_range_addon"));
    addons.append(ItemAddon(1269,"enhance_armor_range_addon"));
    addons.append(ItemAddon(1270,"enhance_armor_range_addon"));
    addons.append(ItemAddon(1271,"enhance_armor_range_addon"));

    addons.append(ItemAddon(1272,"enhance_damage_reduce_addon"));
    addons.append(ItemAddon(1273,"enhance_damage_reduce_addon"));
    addons.append(ItemAddon(1274,"enhance_damage_reduce_addon"));

    addons.append(ItemAddon(1275,"item_skill_addon"));
    addons.append(ItemAddon(1276,"item_skill_addon"));
    addons.append(ItemAddon(1277,"item_skill_addon"));
    addons.append(ItemAddon(1278,"item_skill_addon"));
    addons.append(ItemAddon(1279,"item_skill_addon"));
    addons.append(ItemAddon(1280,"item_skill_addon"));
    addons.append(ItemAddon(1281,"item_skill_addon"));
    addons.append(ItemAddon(1282,"item_skill_addon"));
    addons.append(ItemAddon(1283,"item_skill_addon"));
    addons.append(ItemAddon(1284,"item_skill_addon"));
    addons.append(ItemAddon(1285,"item_skill_addon"));
    addons.append(ItemAddon(1286,"item_skill_addon"));
    addons.append(ItemAddon(1287,"item_skill_addon"));
    addons.append(ItemAddon(1288,"item_skill_addon"));
    addons.append(ItemAddon(1289,"item_skill_addon"));
    addons.append(ItemAddon(1290,"item_skill_addon"));
    addons.append(ItemAddon(1291,"item_skill_addon"));
    addons.append(ItemAddon(1292,"item_skill_addon"));
    addons.append(ItemAddon(1293,"item_skill_addon"));
    addons.append(ItemAddon(1294,"item_skill_addon"));
    addons.append(ItemAddon(1295,"item_skill_addon"));
    addons.append(ItemAddon(1296,"item_skill_addon"));
    addons.append(ItemAddon(1297,"item_skill_addon"));
    addons.append(ItemAddon(1298,"item_skill_addon"));
    addons.append(ItemAddon(1299,"item_skill_addon"));
    addons.append(ItemAddon(1300,"item_skill_addon"));
    addons.append(ItemAddon(1301,"item_skill_addon"));
    addons.append(ItemAddon(1302,"item_skill_addon"));
    addons.append(ItemAddon(1303,"item_skill_addon"));
    addons.append(ItemAddon(1304,"item_skill_addon"));
    addons.append(ItemAddon(1305,"item_skill_addon"));
    addons.append(ItemAddon(1306,"item_skill_addon"));
    addons.append(ItemAddon(1307,"item_skill_addon"));
    addons.append(ItemAddon(1308,"item_skill_addon"));
    addons.append(ItemAddon(1309,"item_skill_addon"));
    addons.append(ItemAddon(1310,"item_skill_addon"));

    addons.append(ItemAddon(1311,"enhance_attack_addon_2"));
    addons.append(ItemAddon(1312,"enhance_attack_addon_2"));
    addons.append(ItemAddon(1313,"enhance_attack_addon_2"));
    addons.append(ItemAddon(1314,"enhance_attack_addon_2"));
    addons.append(ItemAddon(1315,"enhance_attack_addon_2"));
    addons.append(ItemAddon(1316,"enhance_attack_addon_2"));
    addons.append(ItemAddon(1317,"enhance_attack_addon_2"));
    addons.append(ItemAddon(1318,"enhance_attack_addon_2"));
    addons.append(ItemAddon(1319,"enhance_attack_addon_2"));
    addons.append(ItemAddon(1320,"enhance_attack_addon_2"));
    addons.append(ItemAddon(1321,"enhance_attack_addon_2"));
    addons.append(ItemAddon(1322,"enhance_attack_addon_2"));
    addons.append(ItemAddon(1323,"enhance_attack_addon_2"));
    addons.append(ItemAddon(1324,"enhance_attack_addon_2"));

    addons.append(ItemAddon(1325,"enhance_mp_addon_2"));
    addons.append(ItemAddon(1326,"enhance_mp_addon_2"));
    addons.append(ItemAddon(1327,"enhance_mp_addon_2"));
    addons.append(ItemAddon(1328,"enhance_mp_addon_2"));
    addons.append(ItemAddon(1329,"enhance_mp_addon_2"));
    addons.append(ItemAddon(1330,"enhance_mp_addon_2"));
    addons.append(ItemAddon(1331,"enhance_mp_addon_2"));
    addons.append(ItemAddon(1332,"enhance_mp_addon_2"));
    addons.append(ItemAddon(1333,"enhance_mp_addon_2"));
    addons.append(ItemAddon(1334,"enhance_mp_addon_2"));

    addons.append(ItemAddon(1335,"enhance_hp_addon_2"));
    addons.append(ItemAddon(1336,"enhance_hp_addon_2"));
    addons.append(ItemAddon(1337,"enhance_hp_addon_2"));
    addons.append(ItemAddon(1338,"enhance_hp_addon_2"));
    addons.append(ItemAddon(1339,"enhance_hp_addon_2"));
    addons.append(ItemAddon(1340,"enhance_hp_addon_2"));
    addons.append(ItemAddon(1341,"enhance_hp_addon_2"));
    addons.append(ItemAddon(1342,"enhance_hp_addon_2"));
    addons.append(ItemAddon(1343,"enhance_hp_addon_2"));
    addons.append(ItemAddon(1344,"enhance_hp_addon_2"));

    addons.append(ItemAddon(1401,"enhance_weapon_damage_addon"));
    addons.append(ItemAddon(1402,"enhance_weapon_damage_addon"));
    addons.append(ItemAddon(1403,"enhance_weapon_damage_addon"));
    addons.append(ItemAddon(1404,"enhance_weapon_damage_addon"));
    addons.append(ItemAddon(1405,"enhance_weapon_damage_addon"));

    addons.append(ItemAddon(1406,"enhance_attack_addon_2"));
    addons.append(ItemAddon(1407,"enhance_attack_addon_2"));
    addons.append(ItemAddon(1408,"enhance_attack_addon_2"));

    addons.append(ItemAddon(1409,"enhance_armor_range_addon"));
    addons.append(ItemAddon(1410,"enhance_armor_range_addon"));

    addons.append(ItemAddon(1411,"enhance_hp_addon_2"));
    addons.append(ItemAddon(1412,"enhance_hp_addon_2"));
    addons.append(ItemAddon(1413,"enhance_hp_addon_2"));
    addons.append(ItemAddon(1414,"enhance_hp_addon_2"));
    addons.append(ItemAddon(1415,"enhance_hp_addon_2"));
    addons.append(ItemAddon(1416,"enhance_hp_addon_2"));

    addons.append(ItemAddon(1417,"reduce_cast_time_addon"));

    addons.append(ItemAddon(1418,"enhance_agi_addon"));

    addons.append(ItemAddon(1419,"enhance_eng_addon"));

    addons.append(ItemAddon(1420,"enhance_defense_addon"));

    addons.append(ItemAddon(1421,"enhance_crit_rate"));

    addons.append(ItemAddon(1422,"enhance_weapon_attack_range"));

    addons.append(ItemAddon(1345,"IA_EA_ESS<offsetof(armor_essence,hp_enhance)>"));
    addons.append(ItemAddon(1346,"IA_EA_ESS<offsetof(armor_essence,hp_enhance)>"));
    addons.append(ItemAddon(1347,"IA_EA_ESS<offsetof(armor_essence,hp_enhance)>"));
    addons.append(ItemAddon(1348,"IA_EA_ESS<offsetof(armor_essence,hp_enhance)>"));
    addons.append(ItemAddon(1349,"IA_EA_ESS<offsetof(armor_essence,hp_enhance)>"));

    addons.append(ItemAddon(1350,"IA_EA_ESS<offsetof(armor_essence,mp_enhance)>"));
    addons.append(ItemAddon(1351,"IA_EA_ESS<offsetof(armor_essence,mp_enhance)>"));
    addons.append(ItemAddon(1352,"IA_EA_ESS<offsetof(armor_essence,mp_enhance)>"));
    addons.append(ItemAddon(1353,"IA_EA_ESS<offsetof(armor_essence,mp_enhance)>"));
    addons.append(ItemAddon(1354,"IA_EA_ESS<offsetof(armor_essence,mp_enhance)>"));

    addons.append(ItemAddon(1355,"enhance_mp_addon_2"));
    addons.append(ItemAddon(1356,"enhance_mp_addon_2"));
    addons.append(ItemAddon(1357,"enhance_mp_addon_2"));
    addons.append(ItemAddon(1358,"enhance_mp_addon_2"));
    addons.append(ItemAddon(1359,"enhance_mp_addon_2"));
    addons.append(ItemAddon(1360,"enhance_mp_addon_2"));
    addons.append(ItemAddon(1361,"enhance_mp_addon_2"));
    addons.append(ItemAddon(1362,"enhance_mp_addon_2"));
    addons.append(ItemAddon(1363,"enhance_mp_addon_2"));
    addons.append(ItemAddon(1364,"enhance_mp_addon_2"));
    addons.append(ItemAddon(1365,"enhance_mp_addon_2"));
    addons.append(ItemAddon(1366,"enhance_mp_addon_2"));
    addons.append(ItemAddon(1367,"enhance_mp_addon_2"));
    addons.append(ItemAddon(1368,"enhance_mp_addon_2"));
    addons.append(ItemAddon(1369,"enhance_mp_addon_2"));

    addons.append(ItemAddon(1370,"enhance_hp_addon_2"));
    addons.append(ItemAddon(1371,"enhance_hp_addon_2"));
    addons.append(ItemAddon(1372,"enhance_hp_addon_2"));
    addons.append(ItemAddon(1373,"enhance_hp_addon_2"));
    addons.append(ItemAddon(1374,"enhance_hp_addon_2"));
    addons.append(ItemAddon(1375,"enhance_hp_addon_2"));
    addons.append(ItemAddon(1376,"enhance_hp_addon_2"));
    addons.append(ItemAddon(1377,"enhance_hp_addon_2"));
    addons.append(ItemAddon(1378,"enhance_hp_addon_2"));
    addons.append(ItemAddon(1379,"enhance_hp_addon_2"));
    addons.append(ItemAddon(1380,"enhance_hp_addon_2"));
    addons.append(ItemAddon(1381,"enhance_hp_addon_2"));
    addons.append(ItemAddon(1382,"enhance_hp_addon_2"));
    addons.append(ItemAddon(1383,"enhance_hp_addon_2"));
    addons.append(ItemAddon(1384,"enhance_hp_addon_2"));

    addons.append(ItemAddon(1385,"enhance_attack_addon_2"));
    addons.append(ItemAddon(1386,"enhance_attack_addon_2"));
    addons.append(ItemAddon(1387,"enhance_attack_addon_2"));
    addons.append(ItemAddon(1388,"enhance_attack_addon_2"));
    addons.append(ItemAddon(1389,"enhance_attack_addon_2"));
    addons.append(ItemAddon(1390,"enhance_attack_addon_2"));
    addons.append(ItemAddon(1391,"enhance_attack_addon_2"));
    addons.append(ItemAddon(1392,"enhance_attack_addon_2"));
    addons.append(ItemAddon(1393,"enhance_attack_addon_2"));
    addons.append(ItemAddon(1395,"enhance_attack_addon_2"));
    addons.append(ItemAddon(1396,"enhance_attack_addon_2"));
    addons.append(ItemAddon(1397,"enhance_attack_addon_2"));
    addons.append(ItemAddon(1398,"enhance_attack_addon_2"));
    addons.append(ItemAddon(1399,"enhance_attack_addon_2"));

    addons.append(ItemAddon(1423,"enhance_weapon_magic_addon"));
    addons.append(ItemAddon(1424,"enhance_weapon_magic_addon"));
    addons.append(ItemAddon(1425,"enhance_weapon_magic_addon"));
    addons.append(ItemAddon(1426,"enhance_weapon_magic_addon"));
    addons.append(ItemAddon(1427,"enhance_weapon_magic_addon"));

    addons.append(ItemAddon(1429,"enhance_str_addon"));
    addons.append(ItemAddon(1430,"enhance_str_addon"));
    addons.append(ItemAddon(1431,"enhance_str_addon"));
    addons.append(ItemAddon(1432,"enhance_str_addon"));
    addons.append(ItemAddon(1433,"enhance_str_addon"));
    addons.append(ItemAddon(1470,"enhance_str_addon"));
    addons.append(ItemAddon(1471,"enhance_str_addon"));
    addons.append(ItemAddon(1472,"enhance_str_addon"));
    addons.append(ItemAddon(1473,"enhance_str_addon"));
    addons.append(ItemAddon(1474,"enhance_str_addon"));
    addons.append(ItemAddon(1450,"enhance_str_addon"));
    addons.append(ItemAddon(1451,"enhance_str_addon"));
    addons.append(ItemAddon(1452,"enhance_str_addon"));
    addons.append(ItemAddon(1453,"enhance_str_addon"));
    addons.append(ItemAddon(1454,"enhance_str_addon"));

    addons.append(ItemAddon(1434,"enhance_agi_addon"));
    addons.append(ItemAddon(1435,"enhance_agi_addon"));
    addons.append(ItemAddon(1436,"enhance_agi_addon"));
    addons.append(ItemAddon(1437,"enhance_agi_addon"));
    addons.append(ItemAddon(1438,"enhance_agi_addon"));
    addons.append(ItemAddon(1475,"enhance_agi_addon"));
    addons.append(ItemAddon(1476,"enhance_agi_addon"));
    addons.append(ItemAddon(1477,"enhance_agi_addon"));
    addons.append(ItemAddon(1478,"enhance_agi_addon"));
    addons.append(ItemAddon(1479,"enhance_agi_addon"));
    addons.append(ItemAddon(1455,"enhance_agi_addon"));
    addons.append(ItemAddon(1456,"enhance_agi_addon"));
    addons.append(ItemAddon(1457,"enhance_agi_addon"));
    addons.append(ItemAddon(1458,"enhance_agi_addon"));
    addons.append(ItemAddon(1459,"enhance_agi_addon"));

    addons.append(ItemAddon(1444,"enhance_vit_addon"));
    addons.append(ItemAddon(1445,"enhance_vit_addon"));
    addons.append(ItemAddon(1446,"enhance_vit_addon"));
    addons.append(ItemAddon(1447,"enhance_vit_addon"));
    addons.append(ItemAddon(1448,"enhance_vit_addon"));
    addons.append(ItemAddon(1485,"enhance_vit_addon"));
    addons.append(ItemAddon(1486,"enhance_vit_addon"));
    addons.append(ItemAddon(1487,"enhance_vit_addon"));
    addons.append(ItemAddon(1488,"enhance_vit_addon"));
    addons.append(ItemAddon(1489,"enhance_vit_addon"));
    addons.append(ItemAddon(1465,"enhance_vit_addon"));
    addons.append(ItemAddon(1466,"enhance_vit_addon"));
    addons.append(ItemAddon(1467,"enhance_vit_addon"));
    addons.append(ItemAddon(1468,"enhance_vit_addon"));
    addons.append(ItemAddon(1469,"enhance_vit_addon"));

    addons.append(ItemAddon(1460,"enhance_eng_addon"));
    addons.append(ItemAddon(1461,"enhance_eng_addon"));
    addons.append(ItemAddon(1462,"enhance_eng_addon"));
    addons.append(ItemAddon(1463,"enhance_eng_addon"));
    addons.append(ItemAddon(1464,"enhance_eng_addon"));
    addons.append(ItemAddon(1480,"enhance_eng_addon"));
    addons.append(ItemAddon(1481,"enhance_eng_addon"));
    addons.append(ItemAddon(1482,"enhance_eng_addon"));
    addons.append(ItemAddon(1483,"enhance_eng_addon"));
    addons.append(ItemAddon(1484,"enhance_eng_addon"));
    addons.append(ItemAddon(1439,"enhance_eng_addon"));
    addons.append(ItemAddon(1440,"enhance_eng_addon"));
    addons.append(ItemAddon(1441,"enhance_eng_addon"));
    addons.append(ItemAddon(1442,"enhance_eng_addon"));
    addons.append(ItemAddon(1443,"enhance_eng_addon"));

    addons.append(ItemAddon(1428,"reduce_cast_time_addon"));
    addons.append(ItemAddon(1449,"reduce_cast_time_addon"));

    addons.append(ItemAddon(1490,"enhance_str_addon"));
    addons.append(ItemAddon(1491,"enhance_vit_addon"));

    addons.append(ItemAddon(1492,"enhance_str_addon"));
    addons.append(ItemAddon(1493,"enhance_vit_addon"));
    addons.append(ItemAddon(1494,"enhance_agi_addon"));
    addons.append(ItemAddon(1495,"enhance_eng_addon"));

    addons.append(ItemAddon(1496,"refine_magic_damage"));
    addons.append(ItemAddon(1497,"refine_damage"));
    addons.append(ItemAddon(1498,"refine_damage"));
    addons.append(ItemAddon(1499,"refine_damage"));

    addons.append(ItemAddon(1500,"refine_max_hp"));
    addons.append(ItemAddon(1501,"refine_max_hp"));
    addons.append(ItemAddon(1502,"refine_max_hp"));

    addons.append(ItemAddon(1503,"refine_defense"));
    addons.append(ItemAddon(1504,"refine_resistance"));
    addons.append(ItemAddon(1505,"refine_armor"));

    addons.append(ItemAddon(1510,"enhance_crit_rate"));
    addons.append(ItemAddon(1511,"reduce_cast_time_addon"));
    addons.append(ItemAddon(1512,"enhance_attack_scale_addon"));

    addons.append(ItemAddon(1513,"enhance_str_addon"));
    addons.append(ItemAddon(1514,"enhance_agi_addon"));
    addons.append(ItemAddon(1515,"enhance_vit_addon"));
    addons.append(ItemAddon(1516,"enhance_eng_addon"));
    addons.append(ItemAddon(1517,"enhance_crit_rate"));
    addons.append(ItemAddon(1518,"reduce_cast_time_addon"));

    addons.append(ItemAddon(1519,"item_armor_enhance_resistance<0>"));
    addons.append(ItemAddon(1520,"item_armor_enhance_resistance<0>"));
    addons.append(ItemAddon(1521,"item_armor_enhance_resistance<0>"));
    addons.append(ItemAddon(1524,"item_armor_enhance_resistance<0>"));
    addons.append(ItemAddon(1527,"item_armor_enhance_resistance<0>"));
    addons.append(ItemAddon(1528,"item_armor_enhance_resistance<0>"));
    addons.append(ItemAddon(1530,"item_armor_enhance_resistance<0>"));
    addons.append(ItemAddon(1531,"item_armor_enhance_resistance<0>"));
    addons.append(ItemAddon(1534,"item_armor_enhance_resistance<0>"));
    addons.append(ItemAddon(1535,"item_armor_enhance_resistance<0>"));
    addons.append(ItemAddon(1537,"item_armor_enhance_resistance<0>"));
    addons.append(ItemAddon(1539,"item_armor_enhance_resistance<0>"));
    addons.append(ItemAddon(1541,"item_armor_enhance_resistance<0>"));
    addons.append(ItemAddon(1542,"item_armor_enhance_resistance<0>"));
    addons.append(ItemAddon(1544,"item_armor_enhance_resistance<0>"));

    addons.append(ItemAddon(1546,"item_armor_enhance_resistance<1>"));
    addons.append(ItemAddon(1549,"item_armor_enhance_resistance<1>"));
    addons.append(ItemAddon(1550,"item_armor_enhance_resistance<1>"));
    addons.append(ItemAddon(1552,"item_armor_enhance_resistance<1>"));
    addons.append(ItemAddon(1553,"item_armor_enhance_resistance<1>"));
    addons.append(ItemAddon(1555,"item_armor_enhance_resistance<1>"));
    addons.append(ItemAddon(1556,"item_armor_enhance_resistance<1>"));
    addons.append(ItemAddon(1558,"item_armor_enhance_resistance<1>"));
    addons.append(ItemAddon(1559,"item_armor_enhance_resistance<1>"));
    addons.append(ItemAddon(1561,"item_armor_enhance_resistance<1>"));
    addons.append(ItemAddon(1562,"item_armor_enhance_resistance<1>"));
    addons.append(ItemAddon(1564,"item_armor_enhance_resistance<1>"));
    addons.append(ItemAddon(1566,"item_armor_enhance_resistance<1>"));
    addons.append(ItemAddon(1567,"item_armor_enhance_resistance<1>"));
    addons.append(ItemAddon(1568,"item_armor_enhance_resistance<1>"));


    addons.append(ItemAddon(1570,"item_armor_enhance_resistance<2>"));
    addons.append(ItemAddon(1572,"item_armor_enhance_resistance<2>"));
    addons.append(ItemAddon(1573,"item_armor_enhance_resistance<2>"));
    addons.append(ItemAddon(1575,"item_armor_enhance_resistance<2>"));
    addons.append(ItemAddon(1577,"item_armor_enhance_resistance<2>"));
    addons.append(ItemAddon(1578,"item_armor_enhance_resistance<2>"));
    addons.append(ItemAddon(1580,"item_armor_enhance_resistance<2>"));
    addons.append(ItemAddon(1581,"item_armor_enhance_resistance<2>"));
    addons.append(ItemAddon(1583,"item_armor_enhance_resistance<2>"));
    addons.append(ItemAddon(1585,"item_armor_enhance_resistance<2>"));
    addons.append(ItemAddon(1586,"item_armor_enhance_resistance<2>"));
    addons.append(ItemAddon(1587,"item_armor_enhance_resistance<2>"));
    addons.append(ItemAddon(1589,"item_armor_enhance_resistance<2>"));
    addons.append(ItemAddon(1591,"item_armor_enhance_resistance<2>"));
    addons.append(ItemAddon(1592,"item_armor_enhance_resistance<2>"));

    addons.append(ItemAddon(1594,"item_armor_enhance_resistance<3>"));
    addons.append(ItemAddon(1596,"item_armor_enhance_resistance<3>"));
    addons.append(ItemAddon(1597,"item_armor_enhance_resistance<3>"));
    addons.append(ItemAddon(1599,"item_armor_enhance_resistance<3>"));
    addons.append(ItemAddon(1601,"item_armor_enhance_resistance<3>"));
    addons.append(ItemAddon(1602,"item_armor_enhance_resistance<3>"));
    addons.append(ItemAddon(1604,"item_armor_enhance_resistance<3>"));
    addons.append(ItemAddon(1606,"item_armor_enhance_resistance<3>"));
    addons.append(ItemAddon(1607,"item_armor_enhance_resistance<3>"));
    addons.append(ItemAddon(1609,"item_armor_enhance_resistance<3>"));
    addons.append(ItemAddon(1612,"item_armor_enhance_resistance<3>"));
    addons.append(ItemAddon(1613,"item_armor_enhance_resistance<3>"));
    addons.append(ItemAddon(1614,"item_armor_enhance_resistance<3>"));
    addons.append(ItemAddon(1617,"item_armor_enhance_resistance<3>"));
    addons.append(ItemAddon(1618,"item_armor_enhance_resistance<3>"));

    addons.append(ItemAddon(1620,"item_armor_enhance_resistance<4>"));
    addons.append(ItemAddon(1622,"item_armor_enhance_resistance<4>"));
    addons.append(ItemAddon(1624,"item_armor_enhance_resistance<4>"));
    addons.append(ItemAddon(1625,"item_armor_enhance_resistance<4>"));
    addons.append(ItemAddon(1627,"item_armor_enhance_resistance<4>"));
    addons.append(ItemAddon(1629,"item_armor_enhance_resistance<4>"));
    addons.append(ItemAddon(1631,"item_armor_enhance_resistance<4>"));
    addons.append(ItemAddon(1632,"item_armor_enhance_resistance<4>"));
    addons.append(ItemAddon(1638,"item_armor_enhance_resistance<4>"));
    addons.append(ItemAddon(1640,"item_armor_enhance_resistance<4>"));
    addons.append(ItemAddon(1642,"item_armor_enhance_resistance<4>"));
    addons.append(ItemAddon(1643,"item_armor_enhance_resistance<4>"));
    addons.append(ItemAddon(1645,"item_armor_enhance_resistance<4>"));
    addons.append(ItemAddon(1647,"item_armor_enhance_resistance<4>"));
    addons.append(ItemAddon(1649,"item_armor_enhance_resistance<4>"));

    addons.append(ItemAddon(1523,"item_decoration_enchance_resistance<0>"));
    addons.append(ItemAddon(1525,"item_decoration_enchance_resistance<0>"));
    addons.append(ItemAddon(1526,"item_decoration_enchance_resistance<0>"));
    addons.append(ItemAddon(1529,"item_decoration_enchance_resistance<0>"));
    addons.append(ItemAddon(1532,"item_decoration_enchance_resistance<0>"));
    addons.append(ItemAddon(1533,"item_decoration_enchance_resistance<0>"));
    addons.append(ItemAddon(1536,"item_decoration_enchance_resistance<0>"));
    addons.append(ItemAddon(1538,"item_decoration_enchance_resistance<0>"));
    addons.append(ItemAddon(1540,"item_decoration_enchance_resistance<0>"));
    addons.append(ItemAddon(1545,"item_decoration_enchance_resistance<0>"));
    addons.append(ItemAddon(1547,"item_decoration_enchance_resistance<0>"));
    addons.append(ItemAddon(1687,"item_decoration_enchance_resistance<0>"));
    addons.append(ItemAddon(1551,"item_decoration_enchance_resistance<0>"));
    addons.append(ItemAddon(1554,"item_decoration_enchance_resistance<0>"));
    addons.append(ItemAddon(1557,"item_decoration_enchance_resistance<0>"));
    addons.append(ItemAddon(1560,"item_decoration_enchance_resistance<0>"));
    addons.append(ItemAddon(1563,"item_decoration_enchance_resistance<0>"));
    addons.append(ItemAddon(1565,"item_decoration_enchance_resistance<0>"));

    addons.append(ItemAddon(1569,"item_decoration_enchance_resistance<1>"));
    addons.append(ItemAddon(1571,"item_decoration_enchance_resistance<1>"));
    addons.append(ItemAddon(1574,"item_decoration_enchance_resistance<1>"));
    addons.append(ItemAddon(1576,"item_decoration_enchance_resistance<1>"));
    addons.append(ItemAddon(1579,"item_decoration_enchance_resistance<1>"));
    addons.append(ItemAddon(1582,"item_decoration_enchance_resistance<1>"));
    addons.append(ItemAddon(1584,"item_decoration_enchance_resistance<1>"));
    addons.append(ItemAddon(1588,"item_decoration_enchance_resistance<1>"));
    addons.append(ItemAddon(1590,"item_decoration_enchance_resistance<1>"));
    addons.append(ItemAddon(1593,"item_decoration_enchance_resistance<1>"));
    addons.append(ItemAddon(1595,"item_decoration_enchance_resistance<1>"));
    addons.append(ItemAddon(1598,"item_decoration_enchance_resistance<1>"));
    addons.append(ItemAddon(1600,"item_decoration_enchance_resistance<1>"));
    addons.append(ItemAddon(1603,"item_decoration_enchance_resistance<1>"));
    addons.append(ItemAddon(1605,"item_decoration_enchance_resistance<1>"));
    addons.append(ItemAddon(1608,"item_decoration_enchance_resistance<1>"));
    addons.append(ItemAddon(1610,"item_decoration_enchance_resistance<1>"));
    addons.append(ItemAddon(1611,"item_decoration_enchance_resistance<1>"));

    addons.append(ItemAddon(1616,"item_decoration_enchance_resistance<2>"));
    addons.append(ItemAddon(1619,"item_decoration_enchance_resistance<2>"));
    addons.append(ItemAddon(1621,"item_decoration_enchance_resistance<2>"));
    addons.append(ItemAddon(1623,"item_decoration_enchance_resistance<2>"));
    addons.append(ItemAddon(1626,"item_decoration_enchance_resistance<2>"));
    addons.append(ItemAddon(1628,"item_decoration_enchance_resistance<2>"));
    addons.append(ItemAddon(1630,"item_decoration_enchance_resistance<2>"));
    addons.append(ItemAddon(1633,"item_decoration_enchance_resistance<2>"));
    addons.append(ItemAddon(1634,"item_decoration_enchance_resistance<2>"));
    addons.append(ItemAddon(1635,"item_decoration_enchance_resistance<2>"));
    addons.append(ItemAddon(1636,"item_decoration_enchance_resistance<2>"));
    addons.append(ItemAddon(1637,"item_decoration_enchance_resistance<2>"));
    addons.append(ItemAddon(1639,"item_decoration_enchance_resistance<2>"));
    addons.append(ItemAddon(1641,"item_decoration_enchance_resistance<2>"));
    addons.append(ItemAddon(1644,"item_decoration_enchance_resistance<2>"));
    addons.append(ItemAddon(1646,"item_decoration_enchance_resistance<2>"));
    addons.append(ItemAddon(1648,"item_decoration_enchance_resistance<2>"));
    addons.append(ItemAddon(1650,"item_decoration_enchance_resistance<2>"));

    addons.append(ItemAddon(1651,"item_decoration_enchance_resistance<3>"));
    addons.append(ItemAddon(1652,"item_decoration_enchance_resistance<3>"));
    addons.append(ItemAddon(1653,"item_decoration_enchance_resistance<3>"));
    addons.append(ItemAddon(1654,"item_decoration_enchance_resistance<3>"));
    addons.append(ItemAddon(1655,"item_decoration_enchance_resistance<3>"));
    addons.append(ItemAddon(1656,"item_decoration_enchance_resistance<3>"));
    addons.append(ItemAddon(1657,"item_decoration_enchance_resistance<3>"));
    addons.append(ItemAddon(1658,"item_decoration_enchance_resistance<3>"));
    addons.append(ItemAddon(1659,"item_decoration_enchance_resistance<3>"));
    addons.append(ItemAddon(1660,"item_decoration_enchance_resistance<3>"));
    addons.append(ItemAddon(1661,"item_decoration_enchance_resistance<3>"));
    addons.append(ItemAddon(1662,"item_decoration_enchance_resistance<3>"));
    addons.append(ItemAddon(1663,"item_decoration_enchance_resistance<3>"));
    addons.append(ItemAddon(1664,"item_decoration_enchance_resistance<3>"));
    addons.append(ItemAddon(1665,"item_decoration_enchance_resistance<3>"));
    addons.append(ItemAddon(1666,"item_decoration_enchance_resistance<3>"));
    addons.append(ItemAddon(1667,"item_decoration_enchance_resistance<3>"));
    addons.append(ItemAddon(1668,"item_decoration_enchance_resistance<3>"));

    addons.append(ItemAddon(1669,"item_decoration_enchance_resistance<4>"));
    addons.append(ItemAddon(1670,"item_decoration_enchance_resistance<4>"));
    addons.append(ItemAddon(1671,"item_decoration_enchance_resistance<4>"));
    addons.append(ItemAddon(1672,"item_decoration_enchance_resistance<4>"));
    addons.append(ItemAddon(1673,"item_decoration_enchance_resistance<4>"));
    addons.append(ItemAddon(1674,"item_decoration_enchance_resistance<4>"));
    addons.append(ItemAddon(1675,"item_decoration_enchance_resistance<4>"));
    addons.append(ItemAddon(1676,"item_decoration_enchance_resistance<4>"));
    addons.append(ItemAddon(1677,"item_decoration_enchance_resistance<4>"));
    addons.append(ItemAddon(1678,"item_decoration_enchance_resistance<4>"));
    addons.append(ItemAddon(1679,"item_decoration_enchance_resistance<4>"));
    addons.append(ItemAddon(1680,"item_decoration_enchance_resistance<4>"));
    addons.append(ItemAddon(1681,"item_decoration_enchance_resistance<4>"));
    addons.append(ItemAddon(1682,"item_decoration_enchance_resistance<4>"));
    addons.append(ItemAddon(1683,"item_decoration_enchance_resistance<4>"));
    addons.append(ItemAddon(1684,"item_decoration_enchance_resistance<4>"));
    addons.append(ItemAddon(1685,"item_decoration_enchance_resistance<4>"));
    addons.append(ItemAddon(1686,"item_decoration_enchance_resistance<4>"));

    addons.append(ItemAddon(1688,"enhance_hp_scale_addon"));
    addons.append(ItemAddon(1689,"enhance_mp_scale_addon"));

    addons.append(ItemAddon(1690,"enhance_hpgen_addon"));
    addons.append(ItemAddon(1691,"enhance_mpgen_addon"));

    addons.append(ItemAddon(1692,"refine_damage"));
    addons.append(ItemAddon(1693,"refine_damage"));
    addons.append(ItemAddon(1694,"refine_damage"));
    addons.append(ItemAddon(1695,"refine_damage"));
    addons.append(ItemAddon(1696,"refine_damage"));
    addons.append(ItemAddon(1697,"refine_damage"));
    addons.append(ItemAddon(1698,"refine_damage"));
    addons.append(ItemAddon(1701,"refine_damage"));
    addons.append(ItemAddon(1699,"refine_damage"));
    addons.append(ItemAddon(1700,"refine_damage"));
    addons.append(ItemAddon(1702,"refine_damage"));
    addons.append(ItemAddon(1703,"refine_damage"));
    addons.append(ItemAddon(1704,"refine_damage"));
    addons.append(ItemAddon(1705,"refine_damage"));
    addons.append(ItemAddon(1706,"refine_damage"));
    addons.append(ItemAddon(1707,"refine_damage"));
    addons.append(ItemAddon(1708,"refine_damage"));
    addons.append(ItemAddon(1709,"refine_damage"));
    addons.append(ItemAddon(1710,"refine_damage"));
    addons.append(ItemAddon(1711,"refine_damage"));
    addons.append(ItemAddon(1712,"refine_damage"));
    addons.append(ItemAddon(1713,"refine_damage"));
    addons.append(ItemAddon(1714,"refine_damage"));
    addons.append(ItemAddon(1715,"refine_damage"));
    addons.append(ItemAddon(1716,"refine_damage"));
    addons.append(ItemAddon(1717,"refine_damage"));
    addons.append(ItemAddon(1718,"refine_damage"));
    addons.append(ItemAddon(1719,"refine_damage"));
    addons.append(ItemAddon(1720,"refine_damage"));
    addons.append(ItemAddon(1721,"refine_damage"));
    addons.append(ItemAddon(1722,"refine_damage"));
    addons.append(ItemAddon(1723,"refine_damage"));
    addons.append(ItemAddon(1724,"refine_damage"));
    addons.append(ItemAddon(1725,"refine_damage"));
    addons.append(ItemAddon(1726,"refine_damage"));
    addons.append(ItemAddon(1727,"refine_damage"));
    addons.append(ItemAddon(1728,"refine_damage"));
    addons.append(ItemAddon(1729,"refine_damage"));
    addons.append(ItemAddon(1730,"refine_damage"));
    addons.append(ItemAddon(1731,"refine_damage"));
    addons.append(ItemAddon(1732,"refine_damage"));
    addons.append(ItemAddon(1733,"refine_damage"));
    addons.append(ItemAddon(1734,"refine_damage"));
    addons.append(ItemAddon(1735,"refine_damage"));
    addons.append(ItemAddon(1736,"refine_damage"));
    addons.append(ItemAddon(1737,"refine_damage"));
    addons.append(ItemAddon(1738,"refine_damage"));
    addons.append(ItemAddon(1739,"refine_damage"));
    addons.append(ItemAddon(1740,"refine_damage"));
    addons.append(ItemAddon(1741,"refine_damage"));
    addons.append(ItemAddon(1742,"refine_damage"));
    addons.append(ItemAddon(1743,"refine_damage"));
    addons.append(ItemAddon(1744,"refine_damage"));
    addons.append(ItemAddon(1745,"refine_damage"));
    addons.append(ItemAddon(1746,"refine_damage"));
    addons.append(ItemAddon(1747,"refine_damage"));
    addons.append(ItemAddon(1748,"refine_damage"));
    addons.append(ItemAddon(1749,"refine_damage"));
    addons.append(ItemAddon(1750,"refine_damage"));
    addons.append(ItemAddon(1751,"refine_damage"));

    addons.append(ItemAddon(1752,"refine_magic_damage"));
    addons.append(ItemAddon(1753,"refine_magic_damage"));
    addons.append(ItemAddon(1754,"refine_magic_damage"));
    addons.append(ItemAddon(1755,"refine_magic_damage"));
    addons.append(ItemAddon(1756,"refine_magic_damage"));
    addons.append(ItemAddon(1757,"refine_magic_damage"));
    addons.append(ItemAddon(1758,"refine_magic_damage"));
    addons.append(ItemAddon(1759,"refine_magic_damage"));
    addons.append(ItemAddon(1760,"refine_magic_damage"));
    addons.append(ItemAddon(1761,"refine_magic_damage"));
    addons.append(ItemAddon(1762,"refine_magic_damage"));
    addons.append(ItemAddon(1763,"refine_magic_damage"));
    addons.append(ItemAddon(1764,"refine_magic_damage"));
    addons.append(ItemAddon(1765,"refine_magic_damage"));
    addons.append(ItemAddon(1766,"refine_magic_damage"));
    addons.append(ItemAddon(1767,"refine_magic_damage"));
    addons.append(ItemAddon(1768,"refine_magic_damage"));
    addons.append(ItemAddon(1769,"refine_magic_damage"));
    addons.append(ItemAddon(1770,"refine_magic_damage"));
    addons.append(ItemAddon(1771,"refine_magic_damage"));

    addons.append(ItemAddon(1772,"refine_max_hp"));
    addons.append(ItemAddon(1773,"refine_max_hp"));
    addons.append(ItemAddon(1774,"refine_max_hp"));
    addons.append(ItemAddon(1775,"refine_max_hp"));
    addons.append(ItemAddon(1776,"refine_max_hp"));
    addons.append(ItemAddon(1777,"refine_max_hp"));
    addons.append(ItemAddon(1778,"refine_max_hp"));
    addons.append(ItemAddon(1779,"refine_max_hp"));
    addons.append(ItemAddon(1780,"refine_max_hp"));
    addons.append(ItemAddon(1781,"refine_max_hp"));
    addons.append(ItemAddon(1782,"refine_max_hp"));
    addons.append(ItemAddon(1783,"refine_max_hp"));
    addons.append(ItemAddon(1784,"refine_max_hp"));
    addons.append(ItemAddon(1785,"refine_max_hp"));
    addons.append(ItemAddon(1786,"refine_max_hp"));
    addons.append(ItemAddon(1787,"refine_max_hp"));
    addons.append(ItemAddon(1788,"refine_max_hp"));
    addons.append(ItemAddon(1789,"refine_max_hp"));
    addons.append(ItemAddon(1790,"refine_max_hp"));
    addons.append(ItemAddon(1791,"refine_max_hp"));
    addons.append(ItemAddon(1792,"refine_max_hp"));
    addons.append(ItemAddon(1793,"refine_max_hp"));
    addons.append(ItemAddon(1794,"refine_max_hp"));
    addons.append(ItemAddon(1795,"refine_max_hp"));
    addons.append(ItemAddon(1796,"refine_max_hp"));
    addons.append(ItemAddon(1797,"refine_max_hp"));
    addons.append(ItemAddon(1798,"refine_max_hp"));
    addons.append(ItemAddon(1799,"refine_max_hp"));
    addons.append(ItemAddon(1800,"refine_max_hp"));
    addons.append(ItemAddon(1801,"refine_max_hp"));
    addons.append(ItemAddon(1802,"refine_max_hp"));
    addons.append(ItemAddon(1803,"refine_max_hp"));
    addons.append(ItemAddon(1804,"refine_max_hp"));
    addons.append(ItemAddon(1805,"refine_max_hp"));
    addons.append(ItemAddon(1806,"refine_max_hp"));
    addons.append(ItemAddon(1807,"refine_max_hp"));
    addons.append(ItemAddon(1808,"refine_max_hp"));
    addons.append(ItemAddon(1809,"refine_max_hp"));
    addons.append(ItemAddon(1810,"refine_max_hp"));
    addons.append(ItemAddon(1811,"refine_max_hp"));
    addons.append(ItemAddon(1812,"refine_max_hp"));
    addons.append(ItemAddon(1813,"refine_max_hp"));
    addons.append(ItemAddon(1814,"refine_max_hp"));
    addons.append(ItemAddon(1815,"refine_max_hp"));
    addons.append(ItemAddon(1816,"refine_max_hp"));
    addons.append(ItemAddon(1817,"refine_max_hp"));
    addons.append(ItemAddon(1818,"refine_max_hp"));
    addons.append(ItemAddon(1819,"refine_max_hp"));
    addons.append(ItemAddon(1820,"refine_max_hp"));
    addons.append(ItemAddon(1821,"refine_max_hp"));
    addons.append(ItemAddon(1822,"refine_max_hp"));
    addons.append(ItemAddon(1823,"refine_max_hp"));
    addons.append(ItemAddon(1824,"refine_max_hp"));
    addons.append(ItemAddon(1825,"refine_max_hp"));
    addons.append(ItemAddon(1826,"refine_max_hp"));
    addons.append(ItemAddon(1827,"refine_max_hp"));
    addons.append(ItemAddon(1828,"refine_max_hp"));
    addons.append(ItemAddon(1829,"refine_max_hp"));
    addons.append(ItemAddon(1830,"refine_max_hp"));

    addons.append(ItemAddon(1832,"refine_defense"));
    addons.append(ItemAddon(1833,"refine_defense"));
    addons.append(ItemAddon(1834,"refine_defense"));
    addons.append(ItemAddon(1835,"refine_defense"));
    addons.append(ItemAddon(1836,"refine_defense"));
    addons.append(ItemAddon(1837,"refine_defense"));
    addons.append(ItemAddon(1838,"refine_defense"));
    addons.append(ItemAddon(1839,"refine_defense"));
    addons.append(ItemAddon(1840,"refine_defense"));
    addons.append(ItemAddon(1841,"refine_defense"));
    addons.append(ItemAddon(1842,"refine_defense"));
    addons.append(ItemAddon(1843,"refine_defense"));
    addons.append(ItemAddon(1844,"refine_defense"));
    addons.append(ItemAddon(1845,"refine_defense"));
    addons.append(ItemAddon(1846,"refine_defense"));
    addons.append(ItemAddon(1847,"refine_defense"));
    addons.append(ItemAddon(1848,"refine_defense"));
    addons.append(ItemAddon(1849,"refine_defense"));
    addons.append(ItemAddon(1850,"refine_defense"));
    addons.append(ItemAddon(1851,"refine_defense"));

    addons.append(ItemAddon(1852,"refine_resistance"));
    addons.append(ItemAddon(1853,"refine_resistance"));
    addons.append(ItemAddon(1854,"refine_resistance"));
    addons.append(ItemAddon(1855,"refine_resistance"));
    addons.append(ItemAddon(1856,"refine_resistance"));
    addons.append(ItemAddon(1857,"refine_resistance"));
    addons.append(ItemAddon(1858,"refine_resistance"));
    addons.append(ItemAddon(1859,"refine_resistance"));
    addons.append(ItemAddon(1860,"refine_resistance"));
    addons.append(ItemAddon(1861,"refine_resistance"));
    addons.append(ItemAddon(1862,"refine_resistance"));
    addons.append(ItemAddon(1863,"refine_resistance"));
    addons.append(ItemAddon(1864,"refine_resistance"));
    addons.append(ItemAddon(1865,"refine_resistance"));
    addons.append(ItemAddon(1866,"refine_resistance"));
    addons.append(ItemAddon(1867,"refine_resistance"));
    addons.append(ItemAddon(1868,"refine_resistance"));
    addons.append(ItemAddon(1869,"refine_resistance"));
    addons.append(ItemAddon(1870,"refine_resistance"));
    addons.append(ItemAddon(1871,"refine_resistance"));

    addons.append(ItemAddon(1872 ,"refine_armor"));
    addons.append(ItemAddon(1873 ,"refine_armor"));
    addons.append(ItemAddon(1874 ,"refine_armor"));
    addons.append(ItemAddon(1875 ,"refine_armor"));
    addons.append(ItemAddon(1876 ,"refine_armor"));
    addons.append(ItemAddon(1877 ,"refine_armor"));
    addons.append(ItemAddon(1878 ,"refine_armor"));
    addons.append(ItemAddon(1879 ,"refine_armor"));
    addons.append(ItemAddon(1880 ,"refine_armor"));
    addons.append(ItemAddon(1881 ,"refine_armor"));
    addons.append(ItemAddon(1882 ,"refine_armor"));
    addons.append(ItemAddon(1883 ,"refine_armor"));
    addons.append(ItemAddon(1884 ,"refine_armor"));
    addons.append(ItemAddon(1885 ,"refine_armor"));
    addons.append(ItemAddon(1886 ,"refine_armor"));
    addons.append(ItemAddon(1887 ,"refine_armor"));
    addons.append(ItemAddon(1888 ,"refine_armor"));
    addons.append(ItemAddon(1889 ,"refine_armor"));
    addons.append(ItemAddon(1890 ,"refine_armor"));
    addons.append(ItemAddon(1891 ,"refine_armor"));


    addons.append(ItemAddon(1912,"enhance_str_addon"));
    addons.append(ItemAddon(1913,"enhance_str_addon"));
    addons.append(ItemAddon(1914,"enhance_str_addon"));
    addons.append(ItemAddon(1915,"enhance_str_addon"));
    addons.append(ItemAddon(1916,"enhance_str_addon"));
    addons.append(ItemAddon(1917,"enhance_str_addon"));

    addons.append(ItemAddon(1918,"enhance_agi_addon"));
    addons.append(ItemAddon(1919,"enhance_agi_addon"));
    addons.append(ItemAddon(1920,"enhance_agi_addon"));
    addons.append(ItemAddon(1921,"enhance_agi_addon"));
    addons.append(ItemAddon(1922,"enhance_agi_addon"));
    addons.append(ItemAddon(1923,"enhance_agi_addon"));

    addons.append(ItemAddon(1924,"enhance_vit_addon"));
    addons.append(ItemAddon(1925,"enhance_vit_addon"));
    addons.append(ItemAddon(1926,"enhance_vit_addon"));
    addons.append(ItemAddon(1927,"enhance_vit_addon"));
    addons.append(ItemAddon(1928,"enhance_vit_addon"));
    addons.append(ItemAddon(1929,"enhance_vit_addon"));

    addons.append(ItemAddon(1930,"enhance_eng_addon"));
    addons.append(ItemAddon(1931,"enhance_eng_addon"));
    addons.append(ItemAddon(1932,"enhance_eng_addon"));
    addons.append(ItemAddon(1933,"enhance_eng_addon"));
    addons.append(ItemAddon(1934,"enhance_eng_addon"));
    addons.append(ItemAddon(1935,"enhance_eng_addon"));


    addons.append(ItemAddon(1936,"enhance_str_addon"));
    addons.append(ItemAddon(1937,"enhance_str_addon"));
    addons.append(ItemAddon(1938,"enhance_str_addon"));
    addons.append(ItemAddon(1939,"enhance_str_addon"));
    addons.append(ItemAddon(1940,"enhance_str_addon"));
    addons.append(ItemAddon(1941,"enhance_str_addon"));
    addons.append(ItemAddon(1942,"enhance_str_addon"));
    addons.append(ItemAddon(1943,"enhance_str_addon"));
    addons.append(ItemAddon(1944,"enhance_str_addon"));


    addons.append(ItemAddon(1945,"enhance_agi_addon"));
    addons.append(ItemAddon(1946,"enhance_agi_addon"));
    addons.append(ItemAddon(1947,"enhance_agi_addon"));
    addons.append(ItemAddon(1948,"enhance_agi_addon"));
    addons.append(ItemAddon(1949,"enhance_agi_addon"));
    addons.append(ItemAddon(1950,"enhance_agi_addon"));
    addons.append(ItemAddon(1951,"enhance_agi_addon"));
    addons.append(ItemAddon(1952,"enhance_agi_addon"));
    addons.append(ItemAddon(1953,"enhance_agi_addon"));


    addons.append(ItemAddon(1954,"enhance_vit_addon"));
    addons.append(ItemAddon(1955,"enhance_vit_addon"));
    addons.append(ItemAddon(1956,"enhance_vit_addon"));
    addons.append(ItemAddon(1957,"enhance_vit_addon"));
    addons.append(ItemAddon(1958,"enhance_vit_addon"));
    addons.append(ItemAddon(1959,"enhance_vit_addon"));
    addons.append(ItemAddon(1960,"enhance_vit_addon"));
    addons.append(ItemAddon(1961,"enhance_vit_addon"));
    addons.append(ItemAddon(1962,"enhance_vit_addon"));

    addons.append(ItemAddon(1963,"enhance_eng_addon"));
    addons.append(ItemAddon(1964,"enhance_eng_addon"));
    addons.append(ItemAddon(1965,"enhance_eng_addon"));
    addons.append(ItemAddon(1966,"enhance_eng_addon"));
    addons.append(ItemAddon(1967,"enhance_eng_addon"));
    addons.append(ItemAddon(1968,"enhance_eng_addon"));
    addons.append(ItemAddon(1969,"enhance_eng_addon"));
    addons.append(ItemAddon(1970,"enhance_eng_addon"));
    addons.append(ItemAddon(1971,"enhance_eng_addon"));

    addons.append(ItemAddon(1972,"enhance_speed_addon_point"));
    addons.append(ItemAddon(1973,"enhance_speed_addon_point"));
    addons.append(ItemAddon(1974,"enhance_speed_addon_point"));
    addons.append(ItemAddon(1975,"enhance_speed_addon_point"));
    addons.append(ItemAddon(1976,"enhance_speed_addon_point"));

    addons.append(ItemAddon(1977,"enhance_crit_rate"));
    addons.append(ItemAddon(1978,"enhance_crit_rate"));
    addons.append(ItemAddon(1979,"enhance_crit_rate"));
    addons.append(ItemAddon(1980,"enhance_crit_rate"));
    addons.append(ItemAddon(1981,"enhance_crit_rate"));

    addons.append(ItemAddon(1982,"enhance_damage_reduce_addon"));
    addons.append(ItemAddon(1983,"enhance_damage_reduce_addon"));
    addons.append(ItemAddon(1984,"enhance_damage_reduce_addon"));
    addons.append(ItemAddon(1985,"enhance_damage_reduce_addon"));
    addons.append(ItemAddon(1986,"enhance_damage_reduce_addon"));

    addons.append(ItemAddon(1987,"enhance_hpgen_addon"));
    addons.append(ItemAddon(1988,"enhance_hpgen_addon"));
    addons.append(ItemAddon(1989,"enhance_hpgen_addon"));
    addons.append(ItemAddon(1990,"enhance_hpgen_addon"));
    addons.append(ItemAddon(1991,"enhance_hpgen_addon"));

    addons.append(ItemAddon(1992,"enhance_mpgen_addon"));
    addons.append(ItemAddon(1993,"enhance_mpgen_addon"));
    addons.append(ItemAddon(1994,"enhance_mpgen_addon"));
    addons.append(ItemAddon(1995,"enhance_mpgen_addon"));
    addons.append(ItemAddon(1996,"enhance_mpgen_addon"));

    addons.append(ItemAddon(1997,"enhance_hp_addon_2"));
    addons.append(ItemAddon(1998,"enhance_hp_addon_2"));
    addons.append(ItemAddon(1999,"enhance_hp_addon_2"));
    addons.append(ItemAddon(2000,"enhance_hp_addon_2"));
    addons.append(ItemAddon(2001,"enhance_hp_addon_2"));

    addons.append(ItemAddon(2002,"enhance_mp_addon_2"));
    addons.append(ItemAddon(2003,"enhance_mp_addon_2"));
    addons.append(ItemAddon(2004,"enhance_mp_addon_2"));
    addons.append(ItemAddon(2005,"enhance_mp_addon_2"));
    addons.append(ItemAddon(2006,"enhance_mp_addon_2"));

    addons.append(ItemAddon(2007,"reduce_cast_time_addon"));
    addons.append(ItemAddon(2008,"reduce_cast_time_addon"));
    addons.append(ItemAddon(2009,"reduce_cast_time_addon"));
    addons.append(ItemAddon(2010,"reduce_cast_time_addon"));
    addons.append(ItemAddon(2011,"reduce_cast_time_addon"));

    addons.append(ItemAddon(2012,"enhance_attack_speed_addon"));
    addons.append(ItemAddon(2013,"enhance_attack_speed_addon"));
    addons.append(ItemAddon(2014,"enhance_attack_speed_addon"));

    addons.append(ItemAddon(2015,"enhance_exp_addon"));
    addons.append(ItemAddon(2016,"enhance_exp_addon"));
    addons.append(ItemAddon(2017,"enhance_exp_addon"));
    addons.append(ItemAddon(2018,"enhance_exp_addon"));
    addons.append(ItemAddon(2019,"enhance_exp_addon"));

    addons.append(ItemAddon(2020,"enhance_damage_addon"));
    addons.append(ItemAddon(2021,"enhance_crit_rate"));
    addons.append(ItemAddon(2024,"enhance_crit_rate"));
    addons.append(ItemAddon(2025,"enhance_crit_rate"));
    addons.append(ItemAddon(2027,"enhance_crit_rate"));
    addons.append(ItemAddon(2028,"enhance_crit_rate"));

    addons.append(ItemAddon(2022,"enhance_max_damage_addon"));
    addons.append(ItemAddon(2023,"enhance_max_magic_addon"));

    addons.append(ItemAddon(2029,"enhance_attack_degree"));
    addons.append(ItemAddon(2030,"enhance_attack_degree"));
    addons.append(ItemAddon(2031,"enhance_attack_degree"));
    addons.append(ItemAddon(2032,"enhance_attack_degree"));
    addons.append(ItemAddon(2033,"enhance_attack_degree"));
    addons.append(ItemAddon(2034,"enhance_attack_degree"));
    addons.append(ItemAddon(2035,"enhance_attack_degree"));
    addons.append(ItemAddon(2036,"enhance_attack_degree"));
    addons.append(ItemAddon(2037,"enhance_attack_degree"));
    addons.append(ItemAddon(2038,"enhance_attack_degree"));

    addons.append(ItemAddon(2039,"enhance_defend_degree"));
    addons.append(ItemAddon(2040,"enhance_defend_degree"));
    addons.append(ItemAddon(2041,"enhance_defend_degree"));
    addons.append(ItemAddon(2042,"enhance_defend_degree"));
    addons.append(ItemAddon(2043,"enhance_defend_degree"));
    addons.append(ItemAddon(2044,"enhance_defend_degree"));
    addons.append(ItemAddon(2045,"enhance_defend_degree"));
    addons.append(ItemAddon(2046,"enhance_defend_degree"));
    addons.append(ItemAddon(2047,"enhance_defend_degree"));
    addons.append(ItemAddon(2048,"enhance_defend_degree"));
    addons.append(ItemAddon(2049,"enhance_defend_degree"));
    addons.append(ItemAddon(2050,"enhance_defend_degree"));
    addons.append(ItemAddon(2051,"enhance_defend_degree"));

    addons.append(ItemAddon(2052,"enhance_defend_degree"));
    addons.append(ItemAddon(2053,"enhance_defend_degree"));
    addons.append(ItemAddon(2054,"enhance_defend_degree"));
    addons.append(ItemAddon(2055,"enhance_defend_degree"));
    addons.append(ItemAddon(2056,"enhance_defend_degree"));
    addons.append(ItemAddon(2057,"enhance_defend_degree"));
    addons.append(ItemAddon(2058,"enhance_defend_degree"));
    addons.append(ItemAddon(2059,"enhance_defend_degree"));
    addons.append(ItemAddon(2060,"enhance_defend_degree"));
    addons.append(ItemAddon(2061,"enhance_defend_degree"));
    addons.append(ItemAddon(2062,"enhance_defend_degree"));
    addons.append(ItemAddon(2063,"enhance_defend_degree"));
    addons.append(ItemAddon(2064,"enhance_defend_degree"));

    addons.append(ItemAddon(2065,"enhance_attack_degree"));
    addons.append(ItemAddon(2066,"enhance_attack_degree"));
    addons.append(ItemAddon(2067,"enhance_attack_degree"));
    addons.append(ItemAddon(2068,"enhance_attack_degree"));
    addons.append(ItemAddon(2069,"enhance_attack_degree"));
    addons.append(ItemAddon(2070,"enhance_attack_degree"));
    addons.append(ItemAddon(2071,"enhance_attack_degree"));
    addons.append(ItemAddon(2072,"enhance_attack_degree"));
    addons.append(ItemAddon(2073,"enhance_attack_degree"));
    addons.append(ItemAddon(2074,"enhance_attack_degree"));

    addons.append(ItemAddon(2075,"enhance_attack_degree"));
    addons.append(ItemAddon(2076,"enhance_attack_degree"));
    addons.append(ItemAddon(2077,"enhance_attack_degree"));
    addons.append(ItemAddon(2078,"enhance_attack_degree"));
    addons.append(ItemAddon(2079,"enhance_attack_degree"));
    addons.append(ItemAddon(2080,"enhance_attack_degree"));
    addons.append(ItemAddon(2081,"enhance_attack_degree"));
    addons.append(ItemAddon(2082,"enhance_attack_degree"));
    addons.append(ItemAddon(2083,"enhance_attack_degree"));
    addons.append(ItemAddon(2084,"enhance_attack_degree"));

    addons.append(ItemAddon(2085,"enhance_defend_degree"));
    addons.append(ItemAddon(2086,"enhance_defend_degree"));
    addons.append(ItemAddon(2087,"enhance_defend_degree"));
    addons.append(ItemAddon(2088,"enhance_defend_degree"));
    addons.append(ItemAddon(2089,"enhance_defend_degree"));
    addons.append(ItemAddon(2090,"enhance_defend_degree"));
    addons.append(ItemAddon(2091,"enhance_defend_degree"));
    addons.append(ItemAddon(2092,"enhance_defend_degree"));
    addons.append(ItemAddon(2093,"enhance_defend_degree"));
    addons.append(ItemAddon(2094,"enhance_defend_degree"));
    addons.append(ItemAddon(2095,"enhance_defend_degree"));
    addons.append(ItemAddon(2096,"enhance_defend_degree"));
    addons.append(ItemAddon(2097,"enhance_defend_degree"));

    addons.append(ItemAddon(2098,"enhance_attack_degree"));
    addons.append(ItemAddon(2099,"enhance_attack_degree"));
    addons.append(ItemAddon(2100,"enhance_attack_degree"));
    addons.append(ItemAddon(2101,"enhance_attack_degree"));

    addons.append(ItemAddon(2102,"enhance_damage_reduce_addon"));
    addons.append(ItemAddon(2103,"enhance_damage_reduce_addon"));
    addons.append(ItemAddon(2104,"enhance_damage_reduce_addon"));
    addons.append(ItemAddon(2105,"enhance_damage_reduce_addon"));
    addons.append(ItemAddon(2106,"enhance_damage_reduce_addon"));
    addons.append(ItemAddon(2107,"enhance_damage_reduce_addon"));
    addons.append(ItemAddon(2108,"enhance_damage_reduce_addon"));

    addons.append(ItemAddon(2109,"item_armor_enhance_all_resistance"));
    addons.append(ItemAddon(2110,"item_armor_enhance_all_resistance"));
    addons.append(ItemAddon(2111,"item_armor_enhance_all_resistance"));
    addons.append(ItemAddon(2112,"item_armor_enhance_all_resistance"));
    addons.append(ItemAddon(2113,"item_armor_enhance_all_resistance"));
    addons.append(ItemAddon(2114,"item_armor_enhance_all_resistance"));
    addons.append(ItemAddon(2115,"item_armor_enhance_all_resistance"));
    addons.append(ItemAddon(2116,"item_armor_enhance_all_resistance"));

    addons.append(ItemAddon(2117,"enhance_mp_addon_2"));
    addons.append(ItemAddon(2118,"enhance_mp_addon_2"));
    addons.append(ItemAddon(2119,"enhance_mp_addon_2"));
    addons.append(ItemAddon(2120,"enhance_mp_addon_2"));
    addons.append(ItemAddon(2121,"enhance_mp_addon_2"));
    addons.append(ItemAddon(2122,"enhance_mp_addon_2"));
    addons.append(ItemAddon(2123,"enhance_mp_addon_2"));
    addons.append(ItemAddon(2124,"enhance_mp_addon_2"));
    addons.append(ItemAddon(2125,"enhance_mp_addon_2"));

    addons.append(ItemAddon(2126,"enhance_hp_addon_2"));
    addons.append(ItemAddon(2127,"enhance_hp_addon_2"));
    addons.append(ItemAddon(2128,"enhance_hp_addon_2"));
    addons.append(ItemAddon(2129,"enhance_hp_addon_2"));
    addons.append(ItemAddon(2130,"enhance_hp_addon_2"));
    addons.append(ItemAddon(2131,"enhance_hp_addon_2"));
    addons.append(ItemAddon(2132,"enhance_hp_addon_2"));

    addons.append(ItemAddon(2133,"enhance_hp_scale_addon"));
    addons.append(ItemAddon(2134,"enhance_hp_scale_addon"));
    addons.append(ItemAddon(2135,"enhance_hp_scale_addon"));
    addons.append(ItemAddon(2136,"enhance_hp_scale_addon"));
    addons.append(ItemAddon(2137,"enhance_hp_scale_addon"));
    addons.append(ItemAddon(2138,"enhance_hp_scale_addon"));
    addons.append(ItemAddon(2139,"enhance_hp_scale_addon"));
    addons.append(ItemAddon(2140,"enhance_hp_scale_addon"));
    addons.append(ItemAddon(2141,"enhance_hp_scale_addon"));

    addons.append(ItemAddon(2142,"enhance_attack_degree"));
    addons.append(ItemAddon(2143,"enhance_attack_degree"));

    addons.append(ItemAddon(2144,"enhance_defend_degree"));
    addons.append(ItemAddon(2145,"enhance_defend_degree"));

    addons.append(ItemAddon(2146,"enhance_vit_addon"));
    addons.append(ItemAddon(2147,"enhance_crit_rate"));
    addons.append(ItemAddon(2148,"reduce_cast_time_addon"));


    addons.append(ItemAddon(2149,"enhance_attack_degree"));
    addons.append(ItemAddon(2150,"enhance_attack_degree"));
    addons.append(ItemAddon(2151,"enhance_attack_degree"));

    addons.append(ItemAddon(2154,"enhance_defend_degree"));
    addons.append(ItemAddon(2155,"enhance_defend_degree"));
    addons.append(ItemAddon(2156,"enhance_defend_degree"));
    addons.append(ItemAddon(2157,"enhance_defend_degree"));

    addons.append(ItemAddon(2167,"enhance_defense_scale_addon_2"));
    addons.append(ItemAddon(2168,"enhance_defense_scale_addon_2"));
    addons.append(ItemAddon(2169,"enhance_defense_scale_addon_2"));
    addons.append(ItemAddon(2170,"enhance_defense_scale_addon_2"));
    addons.append(ItemAddon(2171,"enhance_defense_scale_addon_2"));
    addons.append(ItemAddon(2172,"enhance_defense_scale_addon_2"));
    addons.append(ItemAddon(2173,"enhance_defense_scale_addon_2"));
    addons.append(ItemAddon(2174,"enhance_defense_scale_addon_2"));
    addons.append(ItemAddon(2175,"enhance_defense_scale_addon_2"));

    addons.append(ItemAddon(2176,"enhance_resistance3_scale_addon"));
    addons.append(ItemAddon(2177,"enhance_resistance3_scale_addon"));
    addons.append(ItemAddon(2178,"enhance_resistance3_scale_addon"));
    addons.append(ItemAddon(2179,"enhance_resistance3_scale_addon"));
    addons.append(ItemAddon(2180,"enhance_resistance3_scale_addon"));
    addons.append(ItemAddon(2181,"enhance_resistance3_scale_addon"));
    addons.append(ItemAddon(2182,"enhance_resistance3_scale_addon"));
    addons.append(ItemAddon(2183,"enhance_resistance3_scale_addon"));
    addons.append(ItemAddon(2184,"enhance_resistance3_scale_addon"));

    addons.append(ItemAddon(2185,"enhance_resistance1_scale_addon"));
    addons.append(ItemAddon(2186,"enhance_resistance1_scale_addon"));
    addons.append(ItemAddon(2187,"enhance_resistance1_scale_addon"));
    addons.append(ItemAddon(2188,"enhance_resistance1_scale_addon"));
    addons.append(ItemAddon(2189,"enhance_resistance1_scale_addon"));
    addons.append(ItemAddon(2190,"enhance_resistance1_scale_addon"));
    addons.append(ItemAddon(2191,"enhance_resistance1_scale_addon"));
    addons.append(ItemAddon(2192,"enhance_resistance1_scale_addon"));
    addons.append(ItemAddon(2193,"enhance_resistance1_scale_addon"));

    addons.append(ItemAddon(2194,"enhance_resistance0_scale_addon"));
    addons.append(ItemAddon(2195,"enhance_resistance0_scale_addon"));
    addons.append(ItemAddon(2196,"enhance_resistance0_scale_addon"));
    addons.append(ItemAddon(2197,"enhance_resistance0_scale_addon"));
    addons.append(ItemAddon(2198,"enhance_resistance0_scale_addon"));
    addons.append(ItemAddon(2199,"enhance_resistance0_scale_addon"));
    addons.append(ItemAddon(2200,"enhance_resistance0_scale_addon"));
    addons.append(ItemAddon(2201,"enhance_resistance0_scale_addon"));
    addons.append(ItemAddon(2202,"enhance_resistance0_scale_addon"));

    addons.append(ItemAddon(2203,"enhance_resistance4_scale_addon"));
    addons.append(ItemAddon(2204,"enhance_resistance4_scale_addon"));
    addons.append(ItemAddon(2205,"enhance_resistance4_scale_addon"));
    addons.append(ItemAddon(2206,"enhance_resistance4_scale_addon"));
    addons.append(ItemAddon(2207,"enhance_resistance4_scale_addon"));
    addons.append(ItemAddon(2208,"enhance_resistance4_scale_addon"));
    addons.append(ItemAddon(2209,"enhance_resistance4_scale_addon"));
    addons.append(ItemAddon(2210,"enhance_resistance4_scale_addon"));
    addons.append(ItemAddon(2211,"enhance_resistance4_scale_addon"));

    addons.append(ItemAddon(2212,"enhance_resistance2_scale_addon"));
    addons.append(ItemAddon(2213,"enhance_resistance2_scale_addon"));
    addons.append(ItemAddon(2214,"enhance_resistance2_scale_addon"));
    addons.append(ItemAddon(2215,"enhance_resistance2_scale_addon"));
    addons.append(ItemAddon(2216,"enhance_resistance2_scale_addon"));
    addons.append(ItemAddon(2217,"enhance_resistance2_scale_addon"));
    addons.append(ItemAddon(2218,"enhance_resistance2_scale_addon"));
    addons.append(ItemAddon(2219,"enhance_resistance2_scale_addon"));
    addons.append(ItemAddon(2220,"enhance_resistance2_scale_addon"));

    addons.append(ItemAddon(2221,"enhance_damage_scale_addon_2"));
    addons.append(ItemAddon(2222,"enhance_damage_scale_addon_2"));
    addons.append(ItemAddon(2223,"enhance_damage_scale_addon_2"));
    addons.append(ItemAddon(2224,"enhance_damage_scale_addon_2"));
    addons.append(ItemAddon(2225,"enhance_damage_scale_addon_2"));
    addons.append(ItemAddon(2226,"enhance_damage_scale_addon_2"));
    addons.append(ItemAddon(2227,"enhance_damage_scale_addon_2"));
    addons.append(ItemAddon(2228,"enhance_damage_scale_addon_2"));
    addons.append(ItemAddon(2229,"enhance_damage_scale_addon_2"));

    addons.append(ItemAddon(2230,"enhance_magic_damage_scale_addon"));
    addons.append(ItemAddon(2231,"enhance_magic_damage_scale_addon"));
    addons.append(ItemAddon(2232,"enhance_magic_damage_scale_addon"));
    addons.append(ItemAddon(2233,"enhance_magic_damage_scale_addon"));
    addons.append(ItemAddon(2234,"enhance_magic_damage_scale_addon"));
    addons.append(ItemAddon(2235,"enhance_magic_damage_scale_addon"));
    addons.append(ItemAddon(2236,"enhance_magic_damage_scale_addon"));
    addons.append(ItemAddon(2237,"enhance_magic_damage_scale_addon"));
    addons.append(ItemAddon(2238,"enhance_magic_damage_scale_addon"));

    addons.append(ItemAddon(2239,"enhance_all_resistance_scale_addon"));
    addons.append(ItemAddon(2240,"enhance_all_resistance_scale_addon"));
    addons.append(ItemAddon(2241,"enhance_all_resistance_scale_addon"));
    addons.append(ItemAddon(2242,"enhance_all_resistance_scale_addon"));
    addons.append(ItemAddon(2243,"enhance_all_resistance_scale_addon"));
    addons.append(ItemAddon(2244,"enhance_all_resistance_scale_addon"));
    addons.append(ItemAddon(2245,"enhance_all_resistance_scale_addon"));
    addons.append(ItemAddon(2246,"enhance_all_resistance_scale_addon"));
    addons.append(ItemAddon(2247,"enhance_all_resistance_scale_addon"));

    addons.append(ItemAddon(2248,"enhance_damage_scale_addon_2"));
    addons.append(ItemAddon(2249,"enhance_damage_scale_addon_2"));
    addons.append(ItemAddon(2250,"enhance_damage_scale_addon_2"));
    addons.append(ItemAddon(2251,"enhance_damage_scale_addon_2"));
    addons.append(ItemAddon(2252,"enhance_damage_scale_addon_2"));
    addons.append(ItemAddon(2253,"enhance_damage_scale_addon_2"));
    addons.append(ItemAddon(2254,"enhance_damage_scale_addon_2"));
    addons.append(ItemAddon(2255,"enhance_damage_scale_addon_2"));
    addons.append(ItemAddon(2256,"enhance_damage_scale_addon_2"));

    addons.append(ItemAddon(2257,"enhance_magic_damage_scale_addon"));
    addons.append(ItemAddon(2258,"enhance_magic_damage_scale_addon"));
    addons.append(ItemAddon(2259,"enhance_magic_damage_scale_addon"));
    addons.append(ItemAddon(2260,"enhance_magic_damage_scale_addon"));
    addons.append(ItemAddon(2261,"enhance_magic_damage_scale_addon"));
    addons.append(ItemAddon(2262,"enhance_magic_damage_scale_addon"));
    addons.append(ItemAddon(2265,"enhance_magic_damage_scale_addon"));
    addons.append(ItemAddon(2266,"enhance_magic_damage_scale_addon"));
    addons.append(ItemAddon(2267,"enhance_magic_damage_scale_addon"));

    addons.append(ItemAddon(2270,"enhance_eng_addon"));
    addons.append(ItemAddon(2271,"enhance_agi_addon"));
    addons.append(ItemAddon(2272,"enhance_str_addon"));
    addons.append(ItemAddon(2273,"enhance_vit_addon"));
    addons.append(ItemAddon(2275,"item_skill_addon"));
    addons.append(ItemAddon(2276,"item_skill_addon"));
    addons.append(ItemAddon(2277,"item_skill_addon"));
    addons.append(ItemAddon(2278,"item_skill_addon"));
    addons.append(ItemAddon(2279,"item_skill_addon"));
    addons.append(ItemAddon(2280,"item_skill_addon"));
    addons.append(ItemAddon(2281,"item_skill_addon"));
    addons.append(ItemAddon(2282,"item_skill_addon"));
    addons.append(ItemAddon(2283,"item_skill_addon"));

    addons.append(ItemAddon(2472,"item_skill_addon"));
    addons.append(ItemAddon(2473,"item_skill_addon"));
    addons.append(ItemAddon(2474,"item_skill_addon"));
    addons.append(ItemAddon(2475,"item_skill_addon"));

    addons.append(ItemAddon(2477,"item_rebound_skill_addon"));
    addons.append(ItemAddon(2479,"item_rebound_skill_addon"));


    addons.append(ItemAddon(2299,"enhance_all_resistance_scale_addon"));
    addons.append(ItemAddon(2300,"enhance_all_resistance_scale_addon"));
    addons.append(ItemAddon(2301,"enhance_all_resistance_scale_addon"));
    addons.append(ItemAddon(2302,"enhance_all_resistance_scale_addon"));
    addons.append(ItemAddon(2303,"enhance_all_resistance_scale_addon"));
    addons.append(ItemAddon(2304,"enhance_all_resistance_scale_addon"));
    addons.append(ItemAddon(2305,"enhance_all_resistance_scale_addon"));
    addons.append(ItemAddon(2306,"enhance_all_resistance_scale_addon"));
    addons.append(ItemAddon(2307,"enhance_all_resistance_scale_addon"));
    addons.append(ItemAddon(2308,"enhance_all_resistance_scale_addon"));
    addons.append(ItemAddon(2309,"enhance_defend_degree"));
    addons.append(ItemAddon(2310,"enhance_defend_degree"));
    addons.append(ItemAddon(2311,"query_other_property_addon"));
    addons.append(ItemAddon(2362,"enhance_soulpower_addon"));

    addons.append(ItemAddon(2447,"enhance_damage_addon"));
    addons.append(ItemAddon(2448,"enhance_defense_addon_1arg"));
    addons.append(ItemAddon(2449,"enhance_damage_addon"));
    addons.append(ItemAddon(2450,"enhance_defense_addon_1arg"));
    addons.append(ItemAddon(2451,"enhance_damage_addon"));
    addons.append(ItemAddon(2452,"enhance_defense_addon_1arg"));
    addons.append(ItemAddon(2453,"enhance_magic_damage_addon"));
    addons.append(ItemAddon(2454,"enhance_all_resistance_addon"));
    addons.append(ItemAddon(2455,"enhance_magic_damage_addon"));
    addons.append(ItemAddon(2456,"enhance_all_resistance_addon"));
    addons.append(ItemAddon(2457,"enhance_attack_addon"));
    addons.append(ItemAddon(2458,"enhance_armor_addon"));
    addons.append(ItemAddon(2459,"enhance_attack_addon"));
    addons.append(ItemAddon(2460,"enhance_armor_addon"));
    addons.append(ItemAddon(2461,"enhance_attack_addon"));
    addons.append(ItemAddon(2462,"enhance_armor_addon"));
    addons.append(ItemAddon(2463,"enhance_hp_addon"));
    addons.append(ItemAddon(2464,"enhance_hp_addon"));
    addons.append(ItemAddon(2465,"enhance_vit_addon"));
    addons.append(ItemAddon(2466,"enhance_magic_damage_addon"));
    addons.append(ItemAddon(2467,"enhance_all_resistance_addon"));
    addons.append(ItemAddon(2482,"item_skill_addon"));

    addons.append(ItemAddon(2483,"enhance_magic_damage_reduce3_addon"));
    addons.append(ItemAddon(2484,"enhance_magic_damage_reduce3_addon"));
    addons.append(ItemAddon(2485,"enhance_magic_damage_reduce3_addon"));
    addons.append(ItemAddon(2486,"enhance_magic_damage_reduce3_addon"));
    addons.append(ItemAddon(2487,"enhance_magic_damage_reduce0_addon"));
    addons.append(ItemAddon(2488,"enhance_magic_damage_reduce0_addon"));
    addons.append(ItemAddon(2489,"enhance_magic_damage_reduce0_addon"));
    addons.append(ItemAddon(2490,"enhance_magic_damage_reduce0_addon"));
    addons.append(ItemAddon(2491,"enhance_magic_damage_reduce1_addon"));
    addons.append(ItemAddon(2492,"enhance_magic_damage_reduce1_addon"));
    addons.append(ItemAddon(2493,"enhance_magic_damage_reduce1_addon"));
    addons.append(ItemAddon(2494,"enhance_magic_damage_reduce1_addon"));
    addons.append(ItemAddon(2495,"enhance_magic_damage_reduce2_addon"));
    addons.append(ItemAddon(2496,"enhance_magic_damage_reduce2_addon"));
    addons.append(ItemAddon(2497,"enhance_magic_damage_reduce2_addon"));
    addons.append(ItemAddon(2498,"enhance_magic_damage_reduce2_addon"));
    addons.append(ItemAddon(2499,"enhance_magic_damage_reduce4_addon"));
    addons.append(ItemAddon(2500,"enhance_magic_damage_reduce4_addon"));
    addons.append(ItemAddon(2501,"enhance_magic_damage_reduce4_addon"));
    addons.append(ItemAddon(2502,"enhance_magic_damage_reduce4_addon"));
    addons.append(ItemAddon(2503,"enhance_all_magic_damage_reduce_addon"));
    addons.append(ItemAddon(2504,"enhance_all_magic_damage_reduce_addon"));
    addons.append(ItemAddon(2505,"enhance_all_magic_damage_reduce_addon"));

    addons.append(ItemAddon(2506,"enhance_resistance1_addon"));
    addons.append(ItemAddon(2507,"enhance_resistance1_addon"));
    addons.append(ItemAddon(2508,"enhance_resistance1_addon"));
    addons.append(ItemAddon(2509,"enhance_resistance1_addon"));
    addons.append(ItemAddon(2510,"enhance_resistance1_addon"));
    addons.append(ItemAddon(2511,"enhance_resistance1_addon"));
    addons.append(ItemAddon(2512,"enhance_resistance2_addon"));
    addons.append(ItemAddon(2513,"enhance_resistance2_addon"));
    addons.append(ItemAddon(2514,"enhance_resistance2_addon"));
    addons.append(ItemAddon(2515,"enhance_resistance2_addon"));
    addons.append(ItemAddon(2516,"enhance_resistance2_addon"));
    addons.append(ItemAddon(2517,"enhance_resistance2_addon"));
    addons.append(ItemAddon(2518,"enhance_resistance0_addon"));
    addons.append(ItemAddon(2519,"enhance_resistance0_addon"));
    addons.append(ItemAddon(2520,"enhance_resistance0_addon"));
    addons.append(ItemAddon(2521,"enhance_resistance0_addon"));
    addons.append(ItemAddon(2522,"enhance_resistance0_addon"));
    addons.append(ItemAddon(2523,"enhance_resistance0_addon"));
    addons.append(ItemAddon(2524,"enhance_resistance4_addon"));
    addons.append(ItemAddon(2525,"enhance_resistance4_addon"));
    addons.append(ItemAddon(2526,"enhance_resistance4_addon"));
    addons.append(ItemAddon(2527,"enhance_resistance4_addon"));
    addons.append(ItemAddon(2528,"enhance_resistance4_addon"));
    addons.append(ItemAddon(2529,"enhance_resistance4_addon"));
    addons.append(ItemAddon(2530,"enhance_resistance3_addon"));
    addons.append(ItemAddon(2531,"enhance_resistance3_addon"));
    addons.append(ItemAddon(2532,"enhance_resistance3_addon"));
    addons.append(ItemAddon(2533,"enhance_resistance3_addon"));
    addons.append(ItemAddon(2534,"enhance_resistance3_addon"));
    addons.append(ItemAddon(2535,"enhance_resistance3_addon"));

    addons.append(ItemAddon(2536,"enhance_attack_addon"));
    addons.append(ItemAddon(2537,"enhance_attack_addon"));
    addons.append(ItemAddon(2538,"enhance_attack_addon"));
    addons.append(ItemAddon(2539,"enhance_attack_addon"));
    addons.append(ItemAddon(2540,"enhance_attack_addon"));
    addons.append(ItemAddon(2541,"enhance_attack_addon"));
    addons.append(ItemAddon(2542,"enhance_attack_addon"));
    addons.append(ItemAddon(2543,"enhance_armor_addon_2"));
    addons.append(ItemAddon(2544,"enhance_armor_addon_2"));
    addons.append(ItemAddon(2545,"enhance_armor_addon_2"));
    addons.append(ItemAddon(2546,"enhance_armor_addon_2"));
    addons.append(ItemAddon(2547,"enhance_armor_addon_2"));
    addons.append(ItemAddon(2548,"enhance_armor_addon_2"));
    addons.append(ItemAddon(2549,"enhance_armor_addon_2"));
    addons.append(ItemAddon(2550,"enhance_mp_addon"));
    addons.append(ItemAddon(2551,"enhance_mp_addon"));
    addons.append(ItemAddon(2552,"enhance_mp_addon"));
    addons.append(ItemAddon(2553,"enhance_mp_addon"));
    addons.append(ItemAddon(2554,"enhance_mp_addon"));
    addons.append(ItemAddon(2555,"enhance_mp_addon"));
    addons.append(ItemAddon(2556,"enhance_mp_addon"));
    addons.append(ItemAddon(2557,"enhance_mp_addon"));
    addons.append(ItemAddon(2558,"enhance_vit_addon"));
    addons.append(ItemAddon(2559,"enhance_vit_addon"));
    addons.append(ItemAddon(2560,"enhance_vit_addon"));
    addons.append(ItemAddon(2561,"enhance_vit_addon"));
    addons.append(ItemAddon(2562,"enhance_vit_addon"));
    addons.append(ItemAddon(2563,"enhance_vit_addon"));
    addons.append(ItemAddon(2564,"enhance_vit_addon"));
    addons.append(ItemAddon(2565,"enhance_vit_addon"));
    addons.append(ItemAddon(2566,"enhance_vit_addon"));
    addons.append(ItemAddon(2567,"enhance_str_addon"));
    addons.append(ItemAddon(2568,"enhance_str_addon"));
    addons.append(ItemAddon(2569,"enhance_str_addon"));
    addons.append(ItemAddon(2570,"enhance_str_addon"));
    addons.append(ItemAddon(2571,"enhance_str_addon"));
    addons.append(ItemAddon(2572,"enhance_str_addon"));
    addons.append(ItemAddon(2573,"enhance_str_addon"));
    addons.append(ItemAddon(2574,"enhance_str_addon"));
    addons.append(ItemAddon(2575,"enhance_str_addon"));
    addons.append(ItemAddon(2576,"enhance_agi_addon"));
    addons.append(ItemAddon(2577,"enhance_agi_addon"));
    addons.append(ItemAddon(2578,"enhance_agi_addon"));
    addons.append(ItemAddon(2579,"enhance_agi_addon"));
    addons.append(ItemAddon(2580,"enhance_agi_addon"));
    addons.append(ItemAddon(2581,"enhance_agi_addon"));
    addons.append(ItemAddon(2582,"enhance_agi_addon"));
    addons.append(ItemAddon(2583,"enhance_agi_addon"));
    addons.append(ItemAddon(2584,"enhance_agi_addon"));
    addons.append(ItemAddon(2585,"enhance_eng_addon"));
    addons.append(ItemAddon(2586,"enhance_eng_addon"));
    addons.append(ItemAddon(2587,"enhance_eng_addon"));
    addons.append(ItemAddon(2588,"enhance_eng_addon"));
    addons.append(ItemAddon(2589,"enhance_eng_addon"));
    addons.append(ItemAddon(2590,"enhance_eng_addon"));
    addons.append(ItemAddon(2591,"enhance_eng_addon"));
    addons.append(ItemAddon(2592,"enhance_eng_addon"));
    addons.append(ItemAddon(2593,"enhance_eng_addon"));
    addons.append(ItemAddon(2594,"enhance_hp_addon"));
    addons.append(ItemAddon(2595,"enhance_hp_addon"));
    addons.append(ItemAddon(2596,"enhance_hp_addon"));
    addons.append(ItemAddon(2597,"enhance_hp_addon"));
    addons.append(ItemAddon(2598,"enhance_hp_addon"));
    addons.append(ItemAddon(2599,"enhance_hp_addon"));
    addons.append(ItemAddon(2600,"enhance_hp_addon"));
    addons.append(ItemAddon(2601,"enhance_hp_addon"));
    addons.append(ItemAddon(2602,"enhance_hp_addon"));
    addons.append(ItemAddon(2603,"enhance_hp_addon"));
    addons.append(ItemAddon(2604,"enhance_hp_addon"));
    addons.append(ItemAddon(2605,"enhance_hp_addon"));
    addons.append(ItemAddon(2606,"enhance_hp_addon"));
    addons.append(ItemAddon(2607,"enhance_hp_addon"));
    addons.append(ItemAddon(2608,"enhance_hp_addon"));
    addons.append(ItemAddon(2609,"enhance_hp_addon"));
    addons.append(ItemAddon(2610,"enhance_hp_addon"));
    addons.append(ItemAddon(2611,"enhance_hp_addon"));
    addons.append(ItemAddon(2612,"enhance_hp_addon"));
    addons.append(ItemAddon(2613,"enhance_hp_addon"));
    addons.append(ItemAddon(2614,"enhance_hp_addon"));
    addons.append(ItemAddon(2615,"enhance_hp_addon"));
    addons.append(ItemAddon(2616,"enhance_defense_addon_2"));
    addons.append(ItemAddon(2617,"enhance_defense_addon_2"));
    addons.append(ItemAddon(2618,"enhance_defense_addon_2"));
    addons.append(ItemAddon(2619,"enhance_defense_addon_2"));
    addons.append(ItemAddon(2620,"enhance_defense_addon_2"));
    addons.append(ItemAddon(2621,"enhance_defense_addon_2"));
    addons.append(ItemAddon(2622,"enhance_defense_addon_2"));
    addons.append(ItemAddon(2623,"enhance_defense_addon_2"));
    addons.append(ItemAddon(2624,"enhance_defense_addon_2"));
    addons.append(ItemAddon(2625,"enhance_defense_addon_2"));
    addons.append(ItemAddon(2626,"enhance_defense_addon_2"));
    addons.append(ItemAddon(2627,"enhance_defense_addon_2"));
    addons.append(ItemAddon(2628,"enhance_defense_addon_2"));
    addons.append(ItemAddon(2629,"enhance_defense_addon_2"));
    addons.append(ItemAddon(2630,"enhance_defense_addon_2"));
    addons.append(ItemAddon(2631,"enhance_defense_addon_2"));
    addons.append(ItemAddon(2632,"enhance_defense_addon_2"));
    addons.append(ItemAddon(2633,"enhance_all_resistance_addon"));
    addons.append(ItemAddon(2634,"enhance_all_resistance_addon"));
    addons.append(ItemAddon(2635,"enhance_all_resistance_addon"));
    addons.append(ItemAddon(2636,"enhance_all_resistance_addon"));
    addons.append(ItemAddon(2637,"enhance_all_resistance_addon"));
    addons.append(ItemAddon(2638,"enhance_all_resistance_addon"));
    addons.append(ItemAddon(2639,"enhance_all_resistance_addon"));
    addons.append(ItemAddon(2640,"enhance_all_resistance_addon"));
    addons.append(ItemAddon(2641,"enhance_all_resistance_addon"));
    addons.append(ItemAddon(2642,"enhance_all_resistance_addon"));
    addons.append(ItemAddon(2643,"enhance_all_resistance_addon"));
    addons.append(ItemAddon(2644,"enhance_all_resistance_addon"));
    addons.append(ItemAddon(2645,"enhance_all_resistance_addon"));
    addons.append(ItemAddon(2646,"enhance_all_resistance_addon"));
    addons.append(ItemAddon(2647,"enhance_all_resistance_addon"));
    addons.append(ItemAddon(2648,"enhance_all_resistance_addon"));
    addons.append(ItemAddon(2649,"enhance_all_resistance_addon"));
    addons.append(ItemAddon(2650,"enhance_damage_addon_2"));
    addons.append(ItemAddon(2651,"enhance_damage_addon_2"));
    addons.append(ItemAddon(2652,"enhance_damage_addon_2"));
    addons.append(ItemAddon(2653,"enhance_damage_addon_2"));
    addons.append(ItemAddon(2654,"enhance_damage_addon_2"));
    addons.append(ItemAddon(2655,"enhance_damage_addon_2"));
    addons.append(ItemAddon(2656,"enhance_damage_addon_2"));
    addons.append(ItemAddon(2657,"enhance_damage_addon_2"));
    addons.append(ItemAddon(2658,"enhance_damage_addon_2"));
    addons.append(ItemAddon(2659,"enhance_damage_addon_2"));
    addons.append(ItemAddon(2660,"enhance_damage_addon_2"));
    addons.append(ItemAddon(2661,"enhance_damage_addon_2"));
    addons.append(ItemAddon(2662,"enhance_damage_addon_2"));
    addons.append(ItemAddon(2663,"enhance_damage_addon_2"));
    addons.append(ItemAddon(2664,"enhance_damage_addon_2"));
    addons.append(ItemAddon(2665,"enhance_damage_addon_2"));
    addons.append(ItemAddon(2666,"enhance_damage_addon_2"));
    addons.append(ItemAddon(2667,"enhance_damage_addon_2"));
    addons.append(ItemAddon(2668,"enhance_magic_damage_addon_2"));
    addons.append(ItemAddon(2669,"enhance_magic_damage_addon_2"));
    addons.append(ItemAddon(2670,"enhance_magic_damage_addon_2"));
    addons.append(ItemAddon(2671,"enhance_magic_damage_addon_2"));
    addons.append(ItemAddon(2672,"enhance_magic_damage_addon_2"));
    addons.append(ItemAddon(2673,"enhance_magic_damage_addon_2"));
    addons.append(ItemAddon(2674,"enhance_magic_damage_addon_2"));
    addons.append(ItemAddon(2675,"enhance_magic_damage_addon_2"));
    addons.append(ItemAddon(2676,"enhance_magic_damage_addon_2"));
    addons.append(ItemAddon(2677,"enhance_magic_damage_addon_2"));
    addons.append(ItemAddon(2678,"enhance_magic_damage_addon_2"));
    addons.append(ItemAddon(2679,"enhance_magic_damage_addon_2"));
    addons.append(ItemAddon(2680,"enhance_magic_damage_addon_2"));
    addons.append(ItemAddon(2681,"enhance_magic_damage_addon_2"));
    addons.append(ItemAddon(2682,"enhance_magic_damage_addon_2"));
    addons.append(ItemAddon(2683,"enhance_magic_damage_addon_2"));
    addons.append(ItemAddon(2684,"enhance_magic_damage_addon_2"));
    addons.append(ItemAddon(2685,"enhance_magic_damage_addon_2"));
    addons.append(ItemAddon(2686,"enhance_magic_damage_reduce0_addon"));
    addons.append(ItemAddon(2687,"enhance_magic_damage_reduce0_addon"));
    addons.append(ItemAddon(2688,"enhance_magic_damage_reduce0_addon"));
    addons.append(ItemAddon(2689,"enhance_magic_damage_reduce1_addon"));
    addons.append(ItemAddon(2690,"enhance_magic_damage_reduce1_addon"));
    addons.append(ItemAddon(2691,"enhance_magic_damage_reduce1_addon"));
    addons.append(ItemAddon(2692,"enhance_magic_damage_reduce2_addon"));
    addons.append(ItemAddon(2693,"enhance_magic_damage_reduce2_addon"));
    addons.append(ItemAddon(2694,"enhance_magic_damage_reduce2_addon"));
    addons.append(ItemAddon(2695,"enhance_magic_damage_reduce3_addon"));
    addons.append(ItemAddon(2696,"enhance_magic_damage_reduce3_addon"));
    addons.append(ItemAddon(2697,"enhance_magic_damage_reduce3_addon"));
    addons.append(ItemAddon(2698,"enhance_magic_damage_reduce4_addon"));
    addons.append(ItemAddon(2699,"enhance_magic_damage_reduce4_addon"));
    addons.append(ItemAddon(2700,"enhance_magic_damage_reduce4_addon"));
    addons.append(ItemAddon(2701,"enhance_crit_rate"));
    addons.append(ItemAddon(2702,"enhance_attack_degree"));
    addons.append(ItemAddon(2703,"enhance_attack_degree"));
    addons.append(ItemAddon(2704,"enhance_defend_degree"));
    addons.append(ItemAddon(2705,"enhance_defend_degree"));
    addons.append(ItemAddon(2706,"enhance_damage_reduce_addon"));
    addons.append(ItemAddon(2707,"enhance_damage_reduce_addon"));
    addons.append(ItemAddon(2708,"enhance_all_magic_damage_reduce_addon"));
    addons.append(ItemAddon(2709,"enhance_all_magic_damage_reduce_addon"));

    addons.append(ItemAddon(2710,"item_skill_addon"));
    addons.append(ItemAddon(2711,"item_skill_addon"));
    addons.append(ItemAddon(2712,"item_skill_addon"));
    addons.append(ItemAddon(2713,"item_skill_addon"));
    addons.append(ItemAddon(2714,"item_skill_addon"));
    addons.append(ItemAddon(2715,"item_rebound_skill_addon"));
    addons.append(ItemAddon(2716,"item_rebound_skill_addon"));

    addons.append(ItemAddon(2717,"enhance_eng_addon"));
    addons.append(ItemAddon(2718,"enhance_str_addon"));
    addons.append(ItemAddon(2719,"enhance_agi_addon"));
    addons.append(ItemAddon(2720,"enhance_vit_addon"));
    addons.append(ItemAddon(2721,"enhance_attack_degree_2arg"));
    addons.append(ItemAddon(2722,"enhance_attack_degree_2arg"));
    addons.append(ItemAddon(2723,"enhance_defend_degree_2arg"));
    addons.append(ItemAddon(2724,"enhance_defend_degree_2arg"));
    addons.append(ItemAddon(2725,"enhance_crit_rate_2arg"));
    addons.append(ItemAddon(2726,"enhance_crit_rate_2arg"));
    addons.append(ItemAddon(2727,"enhance_damage_addon_2arg"));
    addons.append(ItemAddon(2728,"enhance_magic_damage_addon_2arg"));
    addons.append(ItemAddon(2729,"enhance_hp_addon_2"));
    addons.append(ItemAddon(2730,"enhance_mp_addon_2"));
    addons.append(ItemAddon(2731,"enhance_attack_scale_addon_2arg"));
    addons.append(ItemAddon(2732,"enhance_defense_addon_2_2arg"));
    addons.append(ItemAddon(2733,"enhance_all_resistance_addon_2arg"));
    addons.append(ItemAddon(2734,"enhance_damage_reduce_addon_2arg"));
    addons.append(ItemAddon(2735,"enhance_all_magic_damage_reduce_addon_2arg"));
    addons.append(ItemAddon(2736,"reduce_cast_time_addon_2arg"));
    addons.append(ItemAddon(2737,"reduce_cast_time_addon_2arg"));
    addons.append(ItemAddon(2738,"reduce_require_addon"));
    addons.append(ItemAddon(2739,"enhance_attack_range_addon_2arg"));

    addons.append(ItemAddon(2740,"enhance_hp_addon_2"));
    addons.append(ItemAddon(2741,"enhance_hp_addon_2"));
    addons.append(ItemAddon(2742,"enhance_mp_addon_2"));
    addons.append(ItemAddon(2743,"enhance_mpgen_addon_2arg"));
    addons.append(ItemAddon(2744,"enhance_eng_addon"));
    addons.append(ItemAddon(2745,"enhance_str_addon"));
    addons.append(ItemAddon(2746,"enhance_agi_addon"));
    addons.append(ItemAddon(2747,"enhance_vit_addon"));
    addons.append(ItemAddon(2748,"enhance_defense_scale_addon_2_2arg"));
    addons.append(ItemAddon(2749,"enhance_all_resistance_scale_addon_2arg"));
    addons.append(ItemAddon(2750,"enhance_hpgen_addon_2arg"));
    addons.append(ItemAddon(2751,"enhance_armor_addon_2_2arg"));
    addons.append(ItemAddon(2752,"reduce_cast_time_addon_2arg"));
    addons.append(ItemAddon(2753,"reduce_cast_time_addon_2arg"));
    addons.append(ItemAddon(2754,"enhance_crit_rate_2arg"));
    addons.append(ItemAddon(2755,"enhance_all_resistance_addon_2arg"));
    addons.append(ItemAddon(2756,"enhance_defense_addon_2_2arg"));
    addons.append(ItemAddon(2757,"enhance_damage_reduce_addon_2arg"));
    addons.append(ItemAddon(2758,"enhance_all_magic_damage_reduce_addon_2arg"));

    addons.append(ItemAddon(2839,"enhance_exp_addon"));
    addons.append(ItemAddon(2840,"enhance_exp_addon"));
    addons.append(ItemAddon(2841,"enhance_exp_addon"));
    addons.append(ItemAddon(2842,"enhance_hp_scale_addon"));

    addons.append(ItemAddon(2843,"enhance_penetration"));
    addons.append(ItemAddon(2844,"enhance_penetration"));
    addons.append(ItemAddon(2845,"enhance_penetration"));
    addons.append(ItemAddon(2846,"enhance_penetration"));
    addons.append(ItemAddon(2847,"enhance_penetration"));
    addons.append(ItemAddon(2848,"enhance_penetration"));
    addons.append(ItemAddon(2849,"enhance_penetration"));
    addons.append(ItemAddon(2850,"enhance_resilience"));
    addons.append(ItemAddon(2851,"enhance_resilience"));
    addons.append(ItemAddon(2852,"enhance_resilience"));
    addons.append(ItemAddon(2853,"enhance_resilience"));
    addons.append(ItemAddon(2854,"enhance_resilience"));
    addons.append(ItemAddon(2855,"enhance_resilience"));
    addons.append(ItemAddon(2856,"enhance_resilience"));
    addons.append(ItemAddon(2857,"enhance_resilience"));
    addons.append(ItemAddon(2858,"enhance_resilience"));
    addons.append(ItemAddon(2859,"enhance_resilience"));

    addons.append(ItemAddon(2881,"enhance_penetration"));
    addons.append(ItemAddon(2882,"enhance_magic_damage_addon"));
    addons.append(ItemAddon(2883,"enhance_all_resistance_addon"));
    addons.append(ItemAddon(2884,"enhance_damage_addon"));
    addons.append(ItemAddon(2885,"enhance_defense_addon_1arg"));
    addons.append(ItemAddon(2886,"enhance_hp_addon"));

    addons.append(ItemAddon(2887,"enhance_resilience"));
    addons.append(ItemAddon(2888,"enhance_resilience"));
    addons.append(ItemAddon(2889,"enhance_penetration"));
    addons.append(ItemAddon(2890,"enhance_penetration"));

    //typedef EPSA_addon<int, POINT_OFF+offsetof(enhanced_param,max_hp),DOUBLE_POINT> enhance_hp_addon_2;
    //typedef EPSA_addon<int, POINT_OFF+offsetof(enhanced_param,max_mp),DOUBLE_POINT> enhance_mp_addon_2;
    /*
    #define SET_ADDON_MACRO(value, type)  set_equip_addon<value,type>
    addons.append(ItemAddon(1506,"SET_ADDON_MACRO(2,enhance_crit_rate)"));
    addons.append(ItemAddon(1507,"SET_ADDON_MACRO(3,enhance_str_addon)"));
    addons.append(ItemAddon(1508,"SET_ADDON_MACRO(4,item_skill_addon)"));

    #define SET_ADDON_MACRO(value, type)  set_equip_addon<value,type>
    addons.append(ItemAddon(1895,"SET_ADDON_MACRO(2,enhance_str_addon)"));
    addons.append(ItemAddon(1896,"SET_ADDON_MACRO(4,enhance_damage_reduce_addon)"));

    addons.append(ItemAddon(1897,"SET_ADDON_MACRO(2,enhance_agi_addon)"));
    addons.append(ItemAddon(1898,"SET_ADDON_MACRO(4,enhance_damage_reduce_addon)"));

    addons.append(ItemAddon(1899,"SET_ADDON_MACRO(2,enhance_eng_addon)"));
    addons.append(ItemAddon(1900,"SET_ADDON_MACRO(4,enhance_damage_reduce_addon)"));

    addons.append(ItemAddon(1901,"SET_ADDON_MACRO(2,enhance_attack_speed_addon)"));
    addons.append(ItemAddon(1902,"SET_ADDON_MACRO(4,enhance_vit_addon)"));
    addons.append(ItemAddon(1903,"SET_ADDON_MACRO(6,enhance_crit_rate)"));

    addons.append(ItemAddon(1904,"SET_ADDON_MACRO(2,enhance_attack_speed_addon)"));
    addons.append(ItemAddon(1905,"SET_ADDON_MACRO(4,enhance_vit_addon)"));
    addons.append(ItemAddon(1906,"SET_ADDON_MACRO(6,enhance_crit_rate)"));

    addons.append(ItemAddon(1907,"SET_ADDON_MACRO(2,reduce_cast_time_addon)"));
    addons.append(ItemAddon(1908,"SET_ADDON_MACRO(4,enhance_vit_addon)"));
    addons.append(ItemAddon(1909,"SET_ADDON_MACRO(6,enhance_crit_rate)"));

    addons.append(ItemAddon(2268,"SET_ADDON_MACRO(2,enhance_attack_degree)"));
    addons.append(ItemAddon(2269,"SET_ADDON_MACRO(5,enhance_defend_degree)"));
    addons.append(ItemAddon(2274,"SET_ADDON_MACRO(6,enhance_defend_degree)"));

    addons.append(ItemAddon(2284,"SET_ADDON_MACRO(2,enhance_attack_degree)"));
    addons.append(ItemAddon(2285,"SET_ADDON_MACRO(5,enhance_defend_degree)"));
    addons.append(ItemAddon(2286,"SET_ADDON_MACRO(6,enhance_defend_degree)"));

    addons.append(ItemAddon(2287,"SET_ADDON_MACRO(2,enhance_attack_degree)"));
    addons.append(ItemAddon(2288,"SET_ADDON_MACRO(5,enhance_defend_degree)"));
    addons.append(ItemAddon(2289,"SET_ADDON_MACRO(6,enhance_defend_degree)"));

    addons.append(ItemAddon(2290,"SET_ADDON_MACRO(2,enhance_attack_degree)"));
    addons.append(ItemAddon(2291,"SET_ADDON_MACRO(5,enhance_defend_degree)"));
    addons.append(ItemAddon(2292,"SET_ADDON_MACRO(6,enhance_defend_degree)"));

    addons.append(ItemAddon(2293,"SET_ADDON_MACRO(2,enhance_attack_degree)"));
    addons.append(ItemAddon(2294,"SET_ADDON_MACRO(5,enhance_defend_degree)"));
    addons.append(ItemAddon(2295,"SET_ADDON_MACRO(6,enhance_defend_degree)"));

    addons.append(ItemAddon(2296,"SET_ADDON_MACRO(2,enhance_attack_degree)"));
    addons.append(ItemAddon(2297,"SET_ADDON_MACRO(5,enhance_defend_degree)"));
    addons.append(ItemAddon(2298,"SET_ADDON_MACRO(6,enhance_defend_degree)"));

    addons.append(ItemAddon(2312,"SET_ADDON_MACRO(2,enhance_defend_degree)"));
    addons.append(ItemAddon(2313,"SET_ADDON_MACRO(3,enhance_crit_rate)"));
    addons.append(ItemAddon(2314,"SET_ADDON_MACRO(4,enhance_attack_degree)"));
    addons.append(ItemAddon(2315,"SET_ADDON_MACRO(5,enhance_defend_degree)"));
    addons.append(ItemAddon(2316,"SET_ADDON_MACRO(6,enhance_attack_degree)"));
    addons.append(ItemAddon(2317,"SET_ADDON_MACRO(2,enhance_defend_degree)"));
    addons.append(ItemAddon(2318,"SET_ADDON_MACRO(3,enhance_crit_rate)"));
    addons.append(ItemAddon(2319,"SET_ADDON_MACRO(4,enhance_attack_degree)"));
    addons.append(ItemAddon(2320,"SET_ADDON_MACRO(5,enhance_defend_degree)"));
    addons.append(ItemAddon(2321,"SET_ADDON_MACRO(6,enhance_attack_degree)"));
    addons.append(ItemAddon(2322,"SET_ADDON_MACRO(2,enhance_defend_degree)"));
    addons.append(ItemAddon(2323,"SET_ADDON_MACRO(3,enhance_crit_rate)"));
    addons.append(ItemAddon(2324,"SET_ADDON_MACRO(4,enhance_attack_degree)"));
    addons.append(ItemAddon(2325,"SET_ADDON_MACRO(5,enhance_defend_degree)"));
    addons.append(ItemAddon(2326,"SET_ADDON_MACRO(6,enhance_attack_degree)"));
    addons.append(ItemAddon(2327,"SET_ADDON_MACRO(2,enhance_defend_degree)"));
    addons.append(ItemAddon(2328,"SET_ADDON_MACRO(3,enhance_crit_rate)"));
    addons.append(ItemAddon(2329,"SET_ADDON_MACRO(4,enhance_attack_degree)"));
    addons.append(ItemAddon(2330,"SET_ADDON_MACRO(5,enhance_defend_degree)"));
    addons.append(ItemAddon(2331,"SET_ADDON_MACRO(6,enhance_attack_degree)"));
    addons.append(ItemAddon(2332,"SET_ADDON_MACRO(2,enhance_defend_degree)"));
    addons.append(ItemAddon(2333,"SET_ADDON_MACRO(3,enhance_crit_rate)"));
    addons.append(ItemAddon(2334,"SET_ADDON_MACRO(4,enhance_attack_degree)"));
    addons.append(ItemAddon(2335,"SET_ADDON_MACRO(5,enhance_defend_degree)"));
    addons.append(ItemAddon(2336,"SET_ADDON_MACRO(6,enhance_attack_degree)"));
    addons.append(ItemAddon(2337,"SET_ADDON_MACRO(2,enhance_defend_degree)"));
    addons.append(ItemAddon(2338,"SET_ADDON_MACRO(3,enhance_crit_rate)"));
    addons.append(ItemAddon(2339,"SET_ADDON_MACRO(4,enhance_attack_degree)"));
    addons.append(ItemAddon(2340,"SET_ADDON_MACRO(5,enhance_defend_degree)"));
    addons.append(ItemAddon(2341,"SET_ADDON_MACRO(6,enhance_attack_degree)"));
    addons.append(ItemAddon(2342,"SET_ADDON_MACRO(2,enhance_defend_degree)"));
    addons.append(ItemAddon(2343,"SET_ADDON_MACRO(3,enhance_crit_rate)"));
    addons.append(ItemAddon(2344,"SET_ADDON_MACRO(4,enhance_attack_degree)"));
    addons.append(ItemAddon(2345,"SET_ADDON_MACRO(5,enhance_defend_degree)"));
    addons.append(ItemAddon(2346,"SET_ADDON_MACRO(6,enhance_attack_degree)"));
    addons.append(ItemAddon(2347,"SET_ADDON_MACRO(2,enhance_defend_degree)"));
    addons.append(ItemAddon(2348,"SET_ADDON_MACRO(3,enhance_crit_rate)"));
    addons.append(ItemAddon(2349,"SET_ADDON_MACRO(4,enhance_attack_degree)"));
    addons.append(ItemAddon(2350,"SET_ADDON_MACRO(5,enhance_defend_degree)"));
    addons.append(ItemAddon(2351,"SET_ADDON_MACRO(6,enhance_attack_degree)"));
    addons.append(ItemAddon(2352,"SET_ADDON_MACRO(2,enhance_defend_degree)"));
    addons.append(ItemAddon(2353,"SET_ADDON_MACRO(3,enhance_crit_rate)"));
    addons.append(ItemAddon(2354,"SET_ADDON_MACRO(4,enhance_attack_degree)"));
    addons.append(ItemAddon(2355,"SET_ADDON_MACRO(5,enhance_defend_degree)"));
    addons.append(ItemAddon(2356,"SET_ADDON_MACRO(6,enhance_attack_degree)"));
    addons.append(ItemAddon(2357,"SET_ADDON_MACRO(2,enhance_defend_degree)"));
    addons.append(ItemAddon(2358,"SET_ADDON_MACRO(3,enhance_crit_rate)"));
    addons.append(ItemAddon(2359,"SET_ADDON_MACRO(4,enhance_attack_degree)"));
    addons.append(ItemAddon(2360,"SET_ADDON_MACRO(5,enhance_defend_degree)"));
    addons.append(ItemAddon(2361,"SET_ADDON_MACRO(6,enhance_attack_degree)"));
    addons.append(ItemAddon(2435,"SET_ADDON_MACRO(2,enhance_defense_addon_2)"));
    addons.append(ItemAddon(2436,"SET_ADDON_MACRO(3,enhance_all_resistance_addon)"));
    addons.append(ItemAddon(2437,"SET_ADDON_MACRO(4,enhance_mp_addon)"));
    addons.append(ItemAddon(2438,"SET_ADDON_MACRO(5,enhance_hp_addon)"));
    addons.append(ItemAddon(2439,"SET_ADDON_MACRO(2,enhance_defense_addon_2)"));
    addons.append(ItemAddon(2440,"SET_ADDON_MACRO(3,enhance_all_resistance_addon)"));
    addons.append(ItemAddon(2441,"SET_ADDON_MACRO(4,enhance_mp_addon)"));
    addons.append(ItemAddon(2442,"SET_ADDON_MACRO(5,enhance_hp_addon)"));
    addons.append(ItemAddon(2443,"SET_ADDON_MACRO(2,enhance_defense_addon_2)"));
    addons.append(ItemAddon(2444,"SET_ADDON_MACRO(3,enhance_all_resistance_addon)"));
    addons.append(ItemAddon(2445,"SET_ADDON_MACRO(4,enhance_mp_addon)"));
    addons.append(ItemAddon(2446,"SET_ADDON_MACRO(5,enhance_hp_addon)"));

    addons.append(ItemAddon(2468,"SET_ADDON_MACRO(2,enhance_hp_addon)"));
    addons.append(ItemAddon(2469,"SET_ADDON_MACRO(2,enhance_defense_addon_2)"));
    addons.append(ItemAddon(2470,"SET_ADDON_MACRO(2,enhance_attack_addon)"));
    addons.append(ItemAddon(2471,"SET_ADDON_MACRO(2,enhance_speed_addon_point)"));

    addons.append(ItemAddon(2759,"SET_ADDON_MACRO(2,enhance_defend_degree)"));
    addons.append(ItemAddon(2760,"SET_ADDON_MACRO(3,enhance_crit_rate)"));
    addons.append(ItemAddon(2761,"SET_ADDON_MACRO(4,enhance_attack_degree)"));
    addons.append(ItemAddon(2762,"SET_ADDON_MACRO(5,enhance_defend_degree)"));
    addons.append(ItemAddon(2763,"SET_ADDON_MACRO(6,enhance_attack_degree)"));
    addons.append(ItemAddon(2764,"SET_ADDON_MACRO(2,enhance_defend_degree)"));
    addons.append(ItemAddon(2765,"SET_ADDON_MACRO(3,enhance_crit_rate)"));
    addons.append(ItemAddon(2766,"SET_ADDON_MACRO(4,enhance_attack_degree)"));
    addons.append(ItemAddon(2767,"SET_ADDON_MACRO(5,enhance_defend_degree)"));
    addons.append(ItemAddon(2768,"SET_ADDON_MACRO(6,enhance_attack_degree)"));
    addons.append(ItemAddon(2769,"SET_ADDON_MACRO(2,enhance_defend_degree)"));
    addons.append(ItemAddon(2770,"SET_ADDON_MACRO(3,enhance_crit_rate)"));
    addons.append(ItemAddon(2771,"SET_ADDON_MACRO(4,enhance_attack_degree)"));
    addons.append(ItemAddon(2772,"SET_ADDON_MACRO(5,enhance_defend_degree)"));
    addons.append(ItemAddon(2773,"SET_ADDON_MACRO(6,enhance_attack_degree)"));
    addons.append(ItemAddon(2774,"SET_ADDON_MACRO(2,enhance_defend_degree)"));
    addons.append(ItemAddon(2775,"SET_ADDON_MACRO(3,enhance_crit_rate)"));
    addons.append(ItemAddon(2776,"SET_ADDON_MACRO(4,enhance_attack_degree)"));
    addons.append(ItemAddon(2777,"SET_ADDON_MACRO(5,enhance_defend_degree)"));
    addons.append(ItemAddon(2778,"SET_ADDON_MACRO(6,enhance_attack_degree)"));
    addons.append(ItemAddon(2779,"SET_ADDON_MACRO(2,enhance_defend_degree)"));
    addons.append(ItemAddon(2780,"SET_ADDON_MACRO(3,enhance_crit_rate)"));
    addons.append(ItemAddon(2781,"SET_ADDON_MACRO(4,enhance_attack_degree)"));
    addons.append(ItemAddon(2782,"SET_ADDON_MACRO(5,enhance_defend_degree)"));
    addons.append(ItemAddon(2783,"SET_ADDON_MACRO(6,enhance_attack_degree)"));
    addons.append(ItemAddon(2784,"SET_ADDON_MACRO(2,enhance_defend_degree)"));
    addons.append(ItemAddon(2785,"SET_ADDON_MACRO(3,enhance_crit_rate)"));
    addons.append(ItemAddon(2786,"SET_ADDON_MACRO(4,enhance_attack_degree)"));
    addons.append(ItemAddon(2787,"SET_ADDON_MACRO(5,enhance_defend_degree)"));
    addons.append(ItemAddon(2788,"SET_ADDON_MACRO(6,enhance_attack_degree)"));
    addons.append(ItemAddon(2789,"SET_ADDON_MACRO(2,enhance_defend_degree)"));
    addons.append(ItemAddon(2790,"SET_ADDON_MACRO(3,enhance_crit_rate)"));
    addons.append(ItemAddon(2791,"SET_ADDON_MACRO(4,enhance_attack_degree)"));
    addons.append(ItemAddon(2792,"SET_ADDON_MACRO(5,enhance_defend_degree)"));
    addons.append(ItemAddon(2793,"SET_ADDON_MACRO(6,enhance_attack_degree)"));
    addons.append(ItemAddon(2794,"SET_ADDON_MACRO(2,enhance_defend_degree)"));
    addons.append(ItemAddon(2795,"SET_ADDON_MACRO(3,enhance_crit_rate)"));
    addons.append(ItemAddon(2796,"SET_ADDON_MACRO(4,enhance_attack_degree)"));
    addons.append(ItemAddon(2797,"SET_ADDON_MACRO(5,enhance_defend_degree)"));
    addons.append(ItemAddon(2798,"SET_ADDON_MACRO(6,enhance_attack_degree)"));
    addons.append(ItemAddon(2799,"SET_ADDON_MACRO(2,enhance_defend_degree)"));
    addons.append(ItemAddon(2800,"SET_ADDON_MACRO(3,enhance_crit_rate)"));
    addons.append(ItemAddon(2801,"SET_ADDON_MACRO(4,enhance_attack_degree)"));
    addons.append(ItemAddon(2802,"SET_ADDON_MACRO(5,enhance_defend_degree)"));
    addons.append(ItemAddon(2803,"SET_ADDON_MACRO(6,enhance_attack_degree)"));
    addons.append(ItemAddon(2804,"SET_ADDON_MACRO(2,enhance_defend_degree)"));
    addons.append(ItemAddon(2805,"SET_ADDON_MACRO(3,enhance_crit_rate)"));
    addons.append(ItemAddon(2806,"SET_ADDON_MACRO(4,enhance_attack_degree)"));
    addons.append(ItemAddon(2807,"SET_ADDON_MACRO(5,enhance_defend_degree)"));
    addons.append(ItemAddon(2808,"SET_ADDON_MACRO(6,enhance_attack_degree)"));
    addons.append(ItemAddon(2809,"SET_ADDON_MACRO(2,enhance_hp_addon)"));
    addons.append(ItemAddon(2810,"SET_ADDON_MACRO(3,enhance_all_magic_damage_reduce_addon)"));
    addons.append(ItemAddon(2811,"SET_ADDON_MACRO(4,enhance_attack_degree)"));
    addons.append(ItemAddon(2812,"SET_ADDON_MACRO(2,enhance_hp_addon)"));
    addons.append(ItemAddon(2813,"SET_ADDON_MACRO(3,enhance_crit_rate)"));
    addons.append(ItemAddon(2814,"SET_ADDON_MACRO(4,enhance_attack_degree)"));
    addons.append(ItemAddon(2815,"SET_ADDON_MACRO(2,enhance_hp_addon)"));
    addons.append(ItemAddon(2816,"SET_ADDON_MACRO(3,enhance_attack_speed_addon)"));
    addons.append(ItemAddon(2817,"SET_ADDON_MACRO(4,enhance_attack_degree)"));
    addons.append(ItemAddon(2818,"SET_ADDON_MACRO(2,enhance_hp_addon)"));
    addons.append(ItemAddon(2819,"SET_ADDON_MACRO(3,enhance_attack_speed_addon)"));
    addons.append(ItemAddon(2820,"SET_ADDON_MACRO(4,enhance_attack_degree)"));
    addons.append(ItemAddon(2821,"SET_ADDON_MACRO(2,enhance_hp_addon)"));
    addons.append(ItemAddon(2822,"SET_ADDON_MACRO(3,enhance_crit_rate)"));
    addons.append(ItemAddon(2823,"SET_ADDON_MACRO(4,enhance_attack_degree)"));
    addons.append(ItemAddon(2824,"SET_ADDON_MACRO(2,enhance_hp_addon)"));
    addons.append(ItemAddon(2825,"SET_ADDON_MACRO(3,reduce_cast_time_addon)"));
    addons.append(ItemAddon(2826,"SET_ADDON_MACRO(4,enhance_attack_degree)"));
    addons.append(ItemAddon(2827,"SET_ADDON_MACRO(2,enhance_hp_addon)"));
    addons.append(ItemAddon(2828,"SET_ADDON_MACRO(3,enhance_defend_degree)"));
    addons.append(ItemAddon(2829,"SET_ADDON_MACRO(4,enhance_attack_degree)"));
    addons.append(ItemAddon(2830,"SET_ADDON_MACRO(2,enhance_hp_addon)"));
    addons.append(ItemAddon(2831,"SET_ADDON_MACRO(3,enhance_damage_reduce_addon)"));
    addons.append(ItemAddon(2832,"SET_ADDON_MACRO(4,enhance_attack_degree)"));
    addons.append(ItemAddon(2833,"SET_ADDON_MACRO(2,enhance_hp_addon)"));
    addons.append(ItemAddon(2834,"SET_ADDON_MACRO(3,enhance_soulpower_addon)"));
    addons.append(ItemAddon(2835,"SET_ADDON_MACRO(4,enhance_attack_degree)"));
    addons.append(ItemAddon(2836,"SET_ADDON_MACRO(2,enhance_hp_addon)"));
    addons.append(ItemAddon(2837,"SET_ADDON_MACRO(3,enhance_crit_rate)"));
    addons.append(ItemAddon(2838,"SET_ADDON_MACRO(4,enhance_attack_degree)"));
    addons.append(ItemAddon(2860,"SET_ADDON_MACRO(3,enhance_resilience)"));
    addons.append(ItemAddon(2861,"SET_ADDON_MACRO(5,enhance_penetration)"));
    addons.append(ItemAddon(2862,"SET_ADDON_MACRO(3,enhance_resilience)"));
    addons.append(ItemAddon(2863,"SET_ADDON_MACRO(5,enhance_penetration)"));
    addons.append(ItemAddon(2864,"SET_ADDON_MACRO(3,enhance_resilience)"));
    addons.append(ItemAddon(2865,"SET_ADDON_MACRO(5,enhance_penetration)"));
    addons.append(ItemAddon(2866,"SET_ADDON_MACRO(3,enhance_resilience)"));
    addons.append(ItemAddon(2867,"SET_ADDON_MACRO(5,enhance_penetration)"));
    addons.append(ItemAddon(2868,"SET_ADDON_MACRO(3,enhance_resilience)"));
    addons.append(ItemAddon(2869,"SET_ADDON_MACRO(5,enhance_penetration)"));
    addons.append(ItemAddon(2870,"SET_ADDON_MACRO(3,enhance_resilience)"));
    addons.append(ItemAddon(2871,"SET_ADDON_MACRO(5,enhance_penetration)"));
    addons.append(ItemAddon(2872,"SET_ADDON_MACRO(3,enhance_resilience)"));
    addons.append(ItemAddon(2873,"SET_ADDON_MACRO(4,enhance_penetration)"));
    addons.append(ItemAddon(2874,"SET_ADDON_MACRO(3,enhance_resilience)"));
    addons.append(ItemAddon(2875,"SET_ADDON_MACRO(4,enhance_penetration)"));
    addons.append(ItemAddon(2876,"SET_ADDON_MACRO(3,enhance_resilience)"));
    addons.append(ItemAddon(2877,"SET_ADDON_MACRO(4,enhance_penetration)"));
    addons.append(ItemAddon(2878,"SET_ADDON_MACRO(5,reduce_cast_time_addon)"));
    addons.append(ItemAddon(2879,"SET_ADDON_MACRO(5,enhance_attack_speed_addon)"));
    addons.append(ItemAddon(2880,"SET_ADDON_MACRO(5,enhance_attack_speed_addon)"));

    addons.append(ItemAddon(2891,"SET_ADDON_MACRO(2,enhance_hp_addon)"));
    addons.append(ItemAddon(2892,"SET_ADDON_MACRO(5,enhance_defend_degree)"));
    addons.append(ItemAddon(2893,"SET_ADDON_MACRO(6,enhance_attack_degree)"));
    addons.append(ItemAddon(2894,"SET_ADDON_MACRO(2,enhance_hp_addon)"));
    addons.append(ItemAddon(2895,"SET_ADDON_MACRO(5,enhance_defend_degree)"));
    addons.append(ItemAddon(2896,"SET_ADDON_MACRO(6,enhance_attack_degree)"));
    addons.append(ItemAddon(2897,"SET_ADDON_MACRO(2,enhance_hp_addon)"));
    addons.append(ItemAddon(2898,"SET_ADDON_MACRO(5,enhance_defend_degree)"));
    addons.append(ItemAddon(2899,"SET_ADDON_MACRO(6,enhance_attack_degree)"));
    addons.append(ItemAddon(2900,"SET_ADDON_MACRO(2,reduce_cast_time_addon)"));
    addons.append(ItemAddon(2901,"SET_ADDON_MACRO(3,enhance_eng_addon)"));
    addons.append(ItemAddon(2902,"SET_ADDON_MACRO(4,enhance_defend_degree)"));
    addons.append(ItemAddon(2903,"SET_ADDON_MACRO(5,enhance_attack_degree)"));
    addons.append(ItemAddon(2904,"SET_ADDON_MACRO(2,enhance_crit_rate)"));
    addons.append(ItemAddon(2905,"SET_ADDON_MACRO(3,enhance_agi_addon)"));
    addons.append(ItemAddon(2906,"SET_ADDON_MACRO(4,enhance_defend_degree)"));
    addons.append(ItemAddon(2907,"SET_ADDON_MACRO(5,enhance_attack_degree)"));
    addons.append(ItemAddon(2908,"SET_ADDON_MACRO(2,enhance_crit_rate)"));
    addons.append(ItemAddon(2909,"SET_ADDON_MACRO(3,enhance_str_addon)"));
    addons.append(ItemAddon(2910,"SET_ADDON_MACRO(4,enhance_defend_degree)"));
    addons.append(ItemAddon(2911,"SET_ADDON_MACRO(5,enhance_attack_degree)"));

    #define TEMPORARY_ADDON_MACRO(type) temporary_addon_template<type>
    addons.append(ItemAddon(2363,"TEMPORARY_ADDON_MACRO(enhance_damage_addon)"));
    addons.append(ItemAddon(2364,"TEMPORARY_ADDON_MACRO(enhance_magic_damage_addon)"));
    addons.append(ItemAddon(2365,"TEMPORARY_ADDON_MACRO(enhance_hp_addon_2)"));
    addons.append(ItemAddon(2366,"TEMPORARY_ADDON_MACRO(enhance_str_addon)"));
    addons.append(ItemAddon(2367,"TEMPORARY_ADDON_MACRO(enhance_agi_addon)"));
    addons.append(ItemAddon(2368,"TEMPORARY_ADDON_MACRO(enhance_eng_addon)"));
    addons.append(ItemAddon(2369,"TEMPORARY_ADDON_MACRO(enhance_damage_addon)"));
    addons.append(ItemAddon(2370,"TEMPORARY_ADDON_MACRO(enhance_max_damage_addon)"));
    addons.append(ItemAddon(2371,"TEMPORARY_ADDON_MACRO(enhance_magic_damage_addon)"));
    addons.append(ItemAddon(2372,"TEMPORARY_ADDON_MACRO(enhance_max_magic_addon)"));
    addons.append(ItemAddon(2373,"TEMPORARY_ADDON_MACRO(enhance_hp_addon_2)"));
    addons.append(ItemAddon(2374,"TEMPORARY_ADDON_MACRO(enhance_str_addon)"));
    addons.append(ItemAddon(2375,"TEMPORARY_ADDON_MACRO(enhance_agi_addon)"));
    addons.append(ItemAddon(2376,"TEMPORARY_ADDON_MACRO(enhance_eng_addon)"));
    addons.append(ItemAddon(2377,"TEMPORARY_ADDON_MACRO(enhance_damage_addon)"));
    addons.append(ItemAddon(2378,"TEMPORARY_ADDON_MACRO(enhance_max_damage_addon)"));
    addons.append(ItemAddon(2379,"TEMPORARY_ADDON_MACRO(enhance_magic_damage_addon)"));
    addons.append(ItemAddon(2380,"TEMPORARY_ADDON_MACRO(enhance_max_magic_addon)"));
    addons.append(ItemAddon(2381,"TEMPORARY_ADDON_MACRO(enhance_hp_addon_2)"));
    addons.append(ItemAddon(2382,"TEMPORARY_ADDON_MACRO(enhance_defense_addon)"));
    addons.append(ItemAddon(2383,"TEMPORARY_ADDON_MACRO(enhance_str_addon)"));
    addons.append(ItemAddon(2384,"TEMPORARY_ADDON_MACRO(enhance_agi_addon)"));
    addons.append(ItemAddon(2385,"TEMPORARY_ADDON_MACRO(enhance_eng_addon)"));
    addons.append(ItemAddon(2386,"TEMPORARY_ADDON_MACRO(enhance_damage_addon)"));
    addons.append(ItemAddon(2387,"TEMPORARY_ADDON_MACRO(enhance_max_damage_addon)"));
    addons.append(ItemAddon(2388,"TEMPORARY_ADDON_MACRO(enhance_magic_damage_addon)"));
    addons.append(ItemAddon(2389,"TEMPORARY_ADDON_MACRO(enhance_max_magic_addon)"));
    addons.append(ItemAddon(2390,"TEMPORARY_ADDON_MACRO(enhance_defense_addon)"));
    addons.append(ItemAddon(2391,"TEMPORARY_ADDON_MACRO(enhance_attack_addon_2)"));
    addons.append(ItemAddon(2392,"TEMPORARY_ADDON_MACRO(enhance_str_addon)"));
    addons.append(ItemAddon(2393,"TEMPORARY_ADDON_MACRO(enhance_agi_addon)"));
    addons.append(ItemAddon(2394,"TEMPORARY_ADDON_MACRO(enhance_eng_addon)"));
    addons.append(ItemAddon(2395,"TEMPORARY_ADDON_MACRO(enhance_damage_addon)"));
    addons.append(ItemAddon(2396,"TEMPORARY_ADDON_MACRO(enhance_max_damage_addon)"));
    addons.append(ItemAddon(2397,"TEMPORARY_ADDON_MACRO(enhance_magic_damage_addon)"));
    addons.append(ItemAddon(2398,"TEMPORARY_ADDON_MACRO(enhance_max_magic_addon)"));
    addons.append(ItemAddon(2399,"TEMPORARY_ADDON_MACRO(enhance_hp_addon_2)"));
    addons.append(ItemAddon(2400,"TEMPORARY_ADDON_MACRO(enhance_defense_addon)"));
    addons.append(ItemAddon(2401,"TEMPORARY_ADDON_MACRO(enhance_attack_addon_2)"));
    addons.append(ItemAddon(2402,"TEMPORARY_ADDON_MACRO(enhance_crit_rate)"));
    addons.append(ItemAddon(2403,"TEMPORARY_ADDON_MACRO(enhance_attack_degree)"));
    addons.append(ItemAddon(2404,"TEMPORARY_ADDON_MACRO(enhance_defend_degree)"));
    addons.append(ItemAddon(2405,"TEMPORARY_ADDON_MACRO(enhance_agi_addon)"));
    addons.append(ItemAddon(2406,"TEMPORARY_ADDON_MACRO(enhance_eng_addon)"));
    addons.append(ItemAddon(2407,"TEMPORARY_ADDON_MACRO(enhance_damage_addon)"));
    addons.append(ItemAddon(2408,"TEMPORARY_ADDON_MACRO(enhance_max_damage_addon)"));
    addons.append(ItemAddon(2409,"TEMPORARY_ADDON_MACRO(enhance_magic_damage_addon)"));
    addons.append(ItemAddon(2410,"TEMPORARY_ADDON_MACRO(enhance_max_magic_addon)"));
    addons.append(ItemAddon(2411,"TEMPORARY_ADDON_MACRO(enhance_hp_addon_2)"));
    addons.append(ItemAddon(2412,"TEMPORARY_ADDON_MACRO(enhance_defense_addon)"));
    addons.append(ItemAddon(2413,"TEMPORARY_ADDON_MACRO(enhance_attack_addon_2)"));
    addons.append(ItemAddon(2414,"TEMPORARY_ADDON_MACRO(reduce_cast_time_addon)"));
    addons.append(ItemAddon(2415,"TEMPORARY_ADDON_MACRO(enhance_attack_degree)"));
    addons.append(ItemAddon(2416,"TEMPORARY_ADDON_MACRO(enhance_defend_degree)"));
    addons.append(ItemAddon(2417,"TEMPORARY_ADDON_MACRO(enhance_str_addon)"));
    addons.append(ItemAddon(2418,"TEMPORARY_ADDON_MACRO(enhance_agi_addon)"));
    addons.append(ItemAddon(2419,"TEMPORARY_ADDON_MACRO(enhance_eng_addon)"));
    addons.append(ItemAddon(2420,"TEMPORARY_ADDON_MACRO(enhance_damage_addon)"));
    addons.append(ItemAddon(2421,"TEMPORARY_ADDON_MACRO(enhance_max_damage_addon)"));
     addons.append(ItemAddon(2422,"TEMPORARY_ADDON_MACRO(enhance_magic_damage_addon)"));
    addons.append(ItemAddon(2423,"TEMPORARY_ADDON_MACRO(enhance_max_magic_addon)"));
    addons.append(ItemAddon(2424,"TEMPORARY_ADDON_MACRO(enhance_hp_addon_2)"));
    addons.append(ItemAddon(2425,"TEMPORARY_ADDON_MACRO(enhance_defense_addon)"));
    addons.append(ItemAddon(2426,"TEMPORARY_ADDON_MACRO(enhance_attack_addon_2)"));
    addons.append(ItemAddon(2427,"TEMPORARY_ADDON_MACRO(enhance_crit_rate)"));
    addons.append(ItemAddon(2428,"TEMPORARY_ADDON_MACRO(enhance_attack_degree)"));
    addons.append(ItemAddon(2429,"TEMPORARY_ADDON_MACRO(enhance_defend_degree)"));
    addons.append(ItemAddon(2430,"TEMPORARY_ADDON_MACRO(enhance_str_addon)"));
    addons.append(ItemAddon(2431,"TEMPORARY_ADDON_MACRO(enhance_agi_addon)"));
    addons.append(ItemAddon(2432,"TEMPORARY_ADDON_MACRO(enhance_eng_addon)"));
    addons.append(ItemAddon(2433,"TEMPORARY_ADDON_MACRO(enhance_str_addon)"));
    addons.append(ItemAddon(2434,"TEMPORARY_ADDON_MACRO(enhance_hp_addon_2)"));

    addons.append(ItemAddon(2912,"enhance_attack_degree_2arg"));
    addons.append(ItemAddon(2913,"reduce_cast_time_addon_2arg"));
    addons.append(ItemAddon(2914,"reduce_cast_time_addon"));
    addons.append(ItemAddon(2915,"enhance_crit_rate"));
    addons.append(ItemAddon(2916,"enhance_damage_reduce_addon"));
    addons.append(ItemAddon(2917,"enhance_str_addon_1arg"));
    addons.append(ItemAddon(2918,"enhance_agi_addon_1arg"));
    addons.append(ItemAddon(2919,"enhance_eng_addon_1arg"));
    addons.append(ItemAddon(2920,"enhance_vit_addon_1arg"));
    addons.append(ItemAddon(2921,"enhance_all_magic_damage_reduce_addon"));
    addons.append(ItemAddon(2922,"enhance_soulpower_addon"));
    addons.append(ItemAddon(2923,"refine_defense_resistance"));
    addons.append(ItemAddon(2974,"enhance_attack_degree"));
    addons.append(ItemAddon(2975,"enhance_attack_degree"));
    addons.append(ItemAddon(2976,"enhance_attack_degree"));
    addons.append(ItemAddon(2977,"enhance_attack_degree"));
    addons.append(ItemAddon(2978,"enhance_attack_degree"));
    addons.append(ItemAddon(2979,"enhance_defend_degree"));
    addons.append(ItemAddon(2980,"enhance_defend_degree"));
    addons.append(ItemAddon(2983,"enhance_hp_addon"));
    addons.append(ItemAddon(2984,"enhance_mp_addon"));
    addons.append(ItemAddon(2985,"enhance_str_addon_1arg"));
    addons.append(ItemAddon(2986,"enhance_agi_addon_1arg"));
    addons.append(ItemAddon(2987,"enhance_eng_addon_1arg"));

    addons.append(ItemAddon(2924,"SET_ADDON_MACRO(2,enhance_defend_degree)"));
    addons.append(ItemAddon(2925,"SET_ADDON_MACRO(3,enhance_crit_rate)"));
    addons.append(ItemAddon(2926,"SET_ADDON_MACRO(4,enhance_defend_degree)"));
    addons.append(ItemAddon(2927,"SET_ADDON_MACRO(5,reduce_cast_time_addon)"));
    addons.append(ItemAddon(2928,"SET_ADDON_MACRO(6,enhance_attack_degree)"));

    addons.append(ItemAddon(2929,"SET_ADDON_MACRO(2,enhance_defend_degree)"));
    addons.append(ItemAddon(2930,"SET_ADDON_MACRO(3,enhance_crit_rate)"));
    addons.append(ItemAddon(2931,"SET_ADDON_MACRO(4,enhance_defend_degree)"));
    addons.append(ItemAddon(2932,"SET_ADDON_MACRO(5,reduce_cast_time_addon)"));
    addons.append(ItemAddon(2933,"SET_ADDON_MACRO(6,enhance_attack_degree)"));

    addons.append(ItemAddon(2934,"SET_ADDON_MACRO(2,enhance_defend_degree)"));
    addons.append(ItemAddon(2935,"SET_ADDON_MACRO(3,enhance_crit_rate)"));
    addons.append(ItemAddon(2936,"SET_ADDON_MACRO(4,enhance_defend_degree)"));
    addons.append(ItemAddon(2937,"SET_ADDON_MACRO(5,reduce_cast_time_addon)"));
    addons.append(ItemAddon(2938,"SET_ADDON_MACRO(6,enhance_attack_degree)"));

    addons.append(ItemAddon(2939,"SET_ADDON_MACRO(2,enhance_defend_degree)"));
    addons.append(ItemAddon(2940,"SET_ADDON_MACRO(3,enhance_crit_rate)"));
    addons.append(ItemAddon(2941,"SET_ADDON_MACRO(4,enhance_defend_degree)"));
    addons.append(ItemAddon(2942,"SET_ADDON_MACRO(5,reduce_cast_time_addon)"));
    addons.append(ItemAddon(2943,"SET_ADDON_MACRO(6,enhance_attack_degree)"));

    addons.append(ItemAddon(2944,"SET_ADDON_MACRO(2,enhance_defend_degree)"));
    addons.append(ItemAddon(2945,"SET_ADDON_MACRO(3,enhance_crit_rate)"));
    addons.append(ItemAddon(2946,"SET_ADDON_MACRO(4,enhance_defend_degree)"));
    addons.append(ItemAddon(2947,"SET_ADDON_MACRO(5,reduce_cast_time_addon)"));
    addons.append(ItemAddon(2948,"SET_ADDON_MACRO(6,enhance_attack_degree)"));

    addons.append(ItemAddon(2949,"SET_ADDON_MACRO(2,enhance_defend_degree)"));
    addons.append(ItemAddon(2950,"SET_ADDON_MACRO(3,enhance_crit_rate)"));
    addons.append(ItemAddon(2951,"SET_ADDON_MACRO(4,enhance_defend_degree)"));
    addons.append(ItemAddon(2952,"SET_ADDON_MACRO(5,enhance_attack_speed_addon)"));
    addons.append(ItemAddon(2953,"SET_ADDON_MACRO(6,enhance_attack_degree)"));

    addons.append(ItemAddon(2954,"SET_ADDON_MACRO(2,enhance_defend_degree)"));
    addons.append(ItemAddon(2955,"SET_ADDON_MACRO(3,enhance_crit_rate)"));
    addons.append(ItemAddon(2956,"SET_ADDON_MACRO(4,enhance_defend_degree)"));
    addons.append(ItemAddon(2957,"SET_ADDON_MACRO(5,enhance_attack_speed_addon)"));
    addons.append(ItemAddon(2958,"SET_ADDON_MACRO(6,enhance_attack_degree)"));

    addons.append(ItemAddon(2959,"SET_ADDON_MACRO(2,enhance_defend_degree)"));
    addons.append(ItemAddon(2960,"SET_ADDON_MACRO(3,enhance_crit_rate)"));
    addons.append(ItemAddon(2961,"SET_ADDON_MACRO(4,enhance_defend_degree)"));
    addons.append(ItemAddon(2962,"SET_ADDON_MACRO(5,enhance_attack_speed_addon)"));
    addons.append(ItemAddon(2963,"SET_ADDON_MACRO(6,enhance_attack_degree)"));

    addons.append(ItemAddon(2964,"SET_ADDON_MACRO(2,enhance_defend_degree)"));
    addons.append(ItemAddon(2965,"SET_ADDON_MACRO(3,enhance_crit_rate)"));
    addons.append(ItemAddon(2966,"SET_ADDON_MACRO(4,enhance_defend_degree)"));
    addons.append(ItemAddon(2967,"SET_ADDON_MACRO(5,enhance_attack_speed_addon)"));
    addons.append(ItemAddon(2968,"SET_ADDON_MACRO(6,enhance_attack_degree)"));

    addons.append(ItemAddon(2969,"SET_ADDON_MACRO(2,enhance_defend_degree)"));
    addons.append(ItemAddon(2970,"SET_ADDON_MACRO(3,enhance_crit_rate)"));
    addons.append(ItemAddon(2971,"SET_ADDON_MACRO(4,enhance_defend_degree)"));
    addons.append(ItemAddon(2972,"SET_ADDON_MACRO(5,enhance_attack_speed_addon)"));
    addons.append(ItemAddon(2973,"SET_ADDON_MACRO(6,enhance_attack_degree)"));

    addons.append(ItemAddon(2981,"SET_ADDON_MACRO(2,enhance_attack_degree)"));
    addons.append(ItemAddon(2982,"SET_ADDON_MACRO(2,enhance_penetration)"));


    addons.append(ItemAddon(2988,"enhance_vit_addon"));
    addons.append(ItemAddon(2989,"enhance_hp_addon"));
    addons.append(ItemAddon(2990,"enhance_hp_addon"));
    addons.append(ItemAddon(2991,"enhance_hp_addon"));
    addons.append(ItemAddon(2992,"enhance_magic_damage_addon_2"));
    addons.append(ItemAddon(2993,"enhance_magic_damage_addon_2"));
    addons.append(ItemAddon(2994,"enhance_magic_damage_addon_2"));
    addons.append(ItemAddon(2995,"enhance_damage_addon_2"));
    addons.append(ItemAddon(2996,"enhance_damage_addon_2"));
    addons.append(ItemAddon(2997,"enhance_damage_addon_2"));
    addons.append(ItemAddon(2998,"enhance_all_resistance_addon"));
    addons.append(ItemAddon(2999,"enhance_all_resistance_addon"));
    addons.append(ItemAddon(3000,"enhance_all_resistance_addon"));
    addons.append(ItemAddon(3001,"enhance_defense_addon_1arg"));
    addons.append(ItemAddon(3002,"enhance_defense_addon_1arg"));
    addons.append(ItemAddon(3003,"enhance_defense_addon_1arg"));

    addons.append(ItemAddon(3004,"TEMPORARY_ADDON_MACRO(enhance_damage_addon)"));
    addons.append(ItemAddon(3005,"TEMPORARY_ADDON_MACRO(enhance_magic_damage_addon)"));
    addons.append(ItemAddon(3006,"TEMPORARY_ADDON_MACRO(enhance_hp_addon_2)"));
    addons.append(ItemAddon(3007,"enhance_penetration"));

    addons.append(ItemAddon(3008,"enhance_defend_degree"));
    addons.append(ItemAddon(3009,"enhance_attack_degree"));
    addons.append(ItemAddon(3010,"enhance_str_addon_1arg"));
    addons.append(ItemAddon(3011,"enhance_str_addon"));
    addons.append(ItemAddon(3012,"enhance_eng_addon_1arg"));
    addons.append(ItemAddon(3013,"enhance_eng_addon"));
    addons.append(ItemAddon(3014,"enhance_agi_addon_1arg"));
    addons.append(ItemAddon(3015,"enhance_agi_addon"));
    addons.append(ItemAddon(3016,"enhance_vit_addon_1arg"));
    addons.append(ItemAddon(3017,"enhance_vit_addon"));
    addons.append(ItemAddon(3018,"enhance_hp_addon_2"));
    addons.append(ItemAddon(3019,"enhance_hp_addon"));
    addons.append(ItemAddon(3020,"enhance_crit_rate"));
    addons.append(ItemAddon(3021,"enhance_penetration"));
    addons.append(ItemAddon(3022,"enhance_resilience"));
    addons.append(ItemAddon(3023,"enhance_penetration"));
    addons.append(ItemAddon(3024,"enhance_resilience"));
    addons.append(ItemAddon(3025,"enhance_max_damage_addon_2_2arg"));
    addons.append(ItemAddon(3026,"enhance_max_damage_addon_2"));
    addons.append(ItemAddon(3027,"enhance_max_magic_addon_2_2arg"));
    addons.append(ItemAddon(3028,"enhance_max_magic_addon_2"));
    addons.append(ItemAddon(3029,"enhance_attack_addon"));
    addons.append(ItemAddon(3030,"enhance_armor_addon_2"));
    addons.append(ItemAddon(3031,"enhance_defense_addon_2_2arg"));
    addons.append(ItemAddon(3032,"enhance_defense_addon_2"));
    addons.append(ItemAddon(3033,"enhance_all_resistance_addon_2arg"));
    addons.append(ItemAddon(3034,"enhance_all_resistance_addon"));
    addons.append(ItemAddon(3035,"enhance_damage_addon_2_2arg"));
    addons.append(ItemAddon(3036,"enhance_damage_addon_2"));
    addons.append(ItemAddon(3037,"enhance_magic_damage_addon_2_2arg"));
    addons.append(ItemAddon(3038,"enhance_magic_damage_addon_2"));
    addons.append(ItemAddon(3039,"enhance_damage_addon_2_2arg"));
    addons.append(ItemAddon(3040,"enhance_damage_addon_2"));
    addons.append(ItemAddon(3041,"enhance_magic_damage_addon_2_2arg"));
    addons.append(ItemAddon(3042,"enhance_magic_damage_addon_2"));
    addons.append(ItemAddon(3043,"enhance_vigour"));
    addons.append(ItemAddon(3044,"enhance_vigour"));
    addons.append(ItemAddon(3045,"TEMPORARY_ADDON_MACRO(enhance_all_resistance_addon_2arg)"));
    addons.append(ItemAddon(3046,"TEMPORARY_ADDON_MACRO(enhance_all_resistance_addon_2arg)"));
    addons.append(ItemAddon(3047,"TEMPORARY_ADDON_MACRO(enhance_all_resistance_addon_2arg)"));
    addons.append(ItemAddon(3048,"TEMPORARY_ADDON_MACRO(enhance_all_resistance_addon_2arg)"));
    addons.append(ItemAddon(3049,"TEMPORARY_ADDON_MACRO(enhance_all_resistance_addon_2arg)"));
    addons.append(ItemAddon(3050,"enhance_hp_addon_2"));
    addons.append(ItemAddon(3051,"enhance_hp_addon_2"));
    addons.append(ItemAddon(3052,"enhance_mp_addon_2"));
    addons.append(ItemAddon(3053,"enhance_mpgen_addon_2arg"));
    addons.append(ItemAddon(3054,"enhance_eng_addon"));
    addons.append(ItemAddon(3055,"enhance_str_addon"));
    addons.append(ItemAddon(3056,"enhance_agi_addon"));
    addons.append(ItemAddon(3057,"enhance_vit_addon"));
    addons.append(ItemAddon(3058,"enhance_defense_scale_addon_2_2arg"));
    addons.append(ItemAddon(3059,"enhance_all_resistance_scale_addon_2arg"));
    addons.append(ItemAddon(3060,"enhance_hpgen_addon_2arg"));
    addons.append(ItemAddon(3061,"enhance_armor_addon_2_2arg"));
    addons.append(ItemAddon(3062,"reduce_cast_time_addon_2arg"));
    addons.append(ItemAddon(3063,"enhance_all_resistance_addon_2arg"));
    addons.append(ItemAddon(3064,"enhance_defense_addon_2_2arg"));
    addons.append(ItemAddon(3065,"enhance_all_resistance_addon_2arg"));
    addons.append(ItemAddon(3066,"enhance_all_resistance_addon_2arg"));
    addons.append(ItemAddon(3067,"enhance_all_resistance_addon_2arg"));
    addons.append(ItemAddon(3068,"enhance_hp_addon_2"));
    addons.append(ItemAddon(3069,"enhance_hp_addon_2"));
    addons.append(ItemAddon(3070,"enhance_hp_addon_2"));
    addons.append(ItemAddon(3071,"enhance_eng_addon"));
    addons.append(ItemAddon(3072,"enhance_str_addon"));
    addons.append(ItemAddon(3073,"enhance_agi_addon"));
    addons.append(ItemAddon(3074,"enhance_vit_addon"));
    addons.append(ItemAddon(3075,"enhance_attack_degree_2arg"));
    addons.append(ItemAddon(3076,"enhance_attack_degree_2arg"));
    addons.append(ItemAddon(3077,"enhance_defend_degree_2arg"));
    addons.append(ItemAddon(3078,"enhance_defend_degree_2arg"));
    addons.append(ItemAddon(3079,"enhance_damage_addon_2arg"));
    addons.append(ItemAddon(3080,"enhance_magic_damage_addon_2arg"));
    addons.append(ItemAddon(3081,"enhance_hp_addon_2"));
    addons.append(ItemAddon(3082,"enhance_mp_addon_2"));
    addons.append(ItemAddon(3083,"enhance_attack_scale_addon_2arg"));
    addons.append(ItemAddon(3084,"enhance_defense_addon_2_2arg"));
    addons.append(ItemAddon(3085,"enhance_all_resistance_addon_2arg"));
    addons.append(ItemAddon(3086,"enhance_damage_reduce_addon_2arg"));
    addons.append(ItemAddon(3087,"enhance_all_magic_damage_reduce_addon_2arg"));
    addons.append(ItemAddon(3088,"reduce_cast_time_addon_2arg"));
    addons.append(ItemAddon(3089,"SET_ADDON_MACRO(3,enhance_all_magic_damage_reduce_addon)"));
    addons.append(ItemAddon(3090,"SET_ADDON_MACRO(3,reduce_cast_time_addon)"));
    addons.append(ItemAddon(3091,"SET_ADDON_MACRO(3,enhance_defend_degree)"));
    addons.append(ItemAddon(3092,"SET_ADDON_MACRO(3,enhance_damage_reduce_addon)"));
    addons.append(ItemAddon(3093,"SET_ADDON_MACRO(3,enhance_soulpower_addon)"));
    addons.append(ItemAddon(3094,"SET_ADDON_MACRO(2,enhance_eng_addon_1arg)"));
    addons.append(ItemAddon(3095,"SET_ADDON_MACRO(2,enhance_agi_addon_1arg)"));
    addons.append(ItemAddon(3096,"SET_ADDON_MACRO(2,enhance_str_addon_1arg)"));
    addons.append(ItemAddon(3097,"SET_ADDON_MACRO(2,enhance_eng_addon_1arg)"));
    addons.append(ItemAddon(3098,"SET_ADDON_MACRO(2,enhance_agi_addon_1arg)"));
    addons.append(ItemAddon(3099,"SET_ADDON_MACRO(2,enhance_str_addon_1arg)"));
    addons.append(ItemAddon(3100,"SET_ADDON_MACRO(2,enhance_eng_addon_1arg)"));
    addons.append(ItemAddon(3101,"SET_ADDON_MACRO(2,enhance_agi_addon_1arg)"));
    addons.append(ItemAddon(3102,"SET_ADDON_MACRO(2,enhance_str_addon_1arg)"));
    addons.append(ItemAddon(3103,"SET_ADDON_MACRO(4,enhance_damage_reduce_addon)"));
    addons.append(ItemAddon(3104,"SET_ADDON_MACRO(4,enhance_damage_reduce_addon)"));
    addons.append(ItemAddon(3105,"SET_ADDON_MACRO(3,enhance_resilience)"));
    addons.append(ItemAddon(3106,"SET_ADDON_MACRO(3,enhance_resilience)"));
    addons.append(ItemAddon(3107,"SET_ADDON_MACRO(5,enhance_penetration)"));
    addons.append(ItemAddon(3108,"SET_ADDON_MACRO(5,enhance_penetration)"));
    addons.append(ItemAddon(3109,"enhance_penetration"));
    addons.append(ItemAddon(3110,"enhance_attack_degree"));
    addons.append(ItemAddon(3111,"reduce_cast_time_addon"));
    addons.append(ItemAddon(3112,"SET_ADDON_MACRO(3,enhance_resilience)"));
    addons.append(ItemAddon(3113,"SET_ADDON_MACRO(4,enhance_penetration)"));
    addons.append(ItemAddon(3114,"SET_ADDON_MACRO(5,enhance_attack_speed_addon)"));
    addons.append(ItemAddon(3115,"SET_ADDON_MACRO(6,enhance_hp_addon)"));
    addons.append(ItemAddon(3116,"SET_ADDON_MACRO(3,enhance_resilience)"));
    addons.append(ItemAddon(3117,"SET_ADDON_MACRO(4,enhance_penetration)"));
    addons.append(ItemAddon(3118,"SET_ADDON_MACRO(5,enhance_attack_speed_addon)"));
    addons.append(ItemAddon(3119,"SET_ADDON_MACRO(6,enhance_hp_addon)"));
    addons.append(ItemAddon(3120,"SET_ADDON_MACRO(3,enhance_resilience)"));
    addons.append(ItemAddon(3121,"SET_ADDON_MACRO(4,enhance_penetration)"));
    addons.append(ItemAddon(3122,"SET_ADDON_MACRO(5,reduce_cast_time_addon)"));
    addons.append(ItemAddon(3123,"SET_ADDON_MACRO(6,enhance_hp_addon)"));
    addons.append(ItemAddon(3124,"SET_ADDON_MACRO(6,enhance_resilience)"));
    addons.append(ItemAddon(3125,"SET_ADDON_MACRO(6,enhance_resilience)"));
    addons.append(ItemAddon(3126,"SET_ADDON_MACRO(6,enhance_resilience)"));
    addons.append(ItemAddon(3127,"SET_ADDON_MACRO(8,enhance_penetration)"));
    addons.append(ItemAddon(3128,"SET_ADDON_MACRO(8,enhance_penetration)"));
    addons.append(ItemAddon(3129,"SET_ADDON_MACRO(8,enhance_penetration)"));
    addons.append(ItemAddon(3130,"enhance_penetration"));
    addons.append(ItemAddon(3131,"enhance_penetration"));
    addons.append(ItemAddon(3132,"enhance_penetration"));
    addons.append(ItemAddon(3133,"TEMPORARY_ADDON_MACRO(enhance_mount_speed_addon)"));
    addons.append(ItemAddon(3134,"TEMPORARY_ADDON_MACRO(enhance_mount_speed_addon)"));
    addons.append(ItemAddon(3135,"TEMPORARY_ADDON_MACRO(enhance_mount_speed_addon)"));
    return addons;
}*/
#endif // ADDONS_H

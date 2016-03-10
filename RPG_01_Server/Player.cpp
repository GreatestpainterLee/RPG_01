#include "Player.h"

void Player::ConvertPack2Player(const GamePackage_Player& pack_player,Player& player)
{
	player.SetID(pack_player.userid());
	player.SetSpeed(pack_player.speed());
	player.SetDirection(pack_player.direction());
	player.SetDestPointX(pack_player.destpointx());
	player.SetDestPointY(pack_player.destpointy());
	player.SetCurrentPointX(pack_player.currentpointx());
	player.SetCurrentPointY(pack_player.currentpointy());
	player.SetMsgCode(pack_player.msgcode());
	player.SetBloodValue(pack_player.bloodvalue());
	player.SetMaxBloodValue(pack_player.maxbloodvalue());
	player.SetMagicValue(pack_player.magicvalue());
	player.SetMaxMagicValue(pack_player.maxmagicvalue());
	player.SetEmpiricalValue(pack_player.empiricalvalue());
	player.SetMaxEmpiricalValue(pack_player.maxempiricalvalue());
	player.SetLevel(pack_player.level());
	player.SetDamageValue(pack_player.damagevalue());
	//player.SetCurrentSkill(pack_player.skill());
}

void Player::ConvertPlayer2Pack(Player& player,GamePackage_Player& pack_player)
{
	pack_player.set_userid(player.GetID());
	pack_player.set_speed(player.GetSpeed());
	pack_player.set_direction(player.GetDirection());
	pack_player.set_destpointx(player.GetDestPointX());
	pack_player.set_destpointy(player.GetDestPointY());
	pack_player.set_currentpointx(player.GetCurrentPointX());
	pack_player.set_currentpointy(player.GetCurrentPointY());
	pack_player.set_msgcode(player.GetMsgCode());
	pack_player.set_bloodvalue(player.GetBloodValue());
	pack_player.set_maxbloodvalue(player.GetMaxBloodValue());
	pack_player.set_magicvalue(player.GetMagicValue());
	pack_player.set_maxmagicvalue(player.GetMaxMagicValue());
	pack_player.set_empiricalvalue(player.GetEmpiricalValue());
	pack_player.set_maxempiricalvalue(player.GetMaxEmpiricalValue());
	pack_player.set_level(player.GetLevel());
	pack_player.set_damagevalue(player.GetDamageValue());
	//pack_player.set_skill(player.GetCurrentSkill());
}
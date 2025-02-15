#pragma once

#include "pch.hpp"

#include "components/children.hpp"
#include "components/collider.hpp"
#include "components/modifiers.hpp"

namespace common::entities
{

	/**
	 * @brief Check initAttributes for the default values
	 */
	enum Stat : int
	{
		NoneStat = 0,
		Health = 1,
		MaxHealth = 2,
		Speed = 3,
		Damage = 4,
		MinDamage = 5,
		MaxDamage = 6,
		Trigger = 7,
		BaseAttackSpeed = 8,
		Radius = 9
	};
	constexpr std::size_t ATTRIBUTES_SIZE = 9;
	using Attributes = components::children<ATTRIBUTES_SIZE>;

	static std::unordered_map<std::string, Stat> const mapStat = {
		{"Health", Stat::Health},		{"MaxHealth", Stat::MaxHealth}, {"Speed", Stat::Speed},		{"Damage", Stat::Damage},
		{"MinDamage", Stat::MinDamage}, {"MaxDamage", Stat::MaxDamage}, {"Trigger", Stat::Trigger}, {"BaseAttackSpeed", Stat::BaseAttackSpeed},
		{"Radius", Stat::Radius}};

	Stat getStat(std::string stat);
	Scope getScope(std::string scope);
	entt::entity createAttribute(entt::registry &registry, entt::entity unit, Stat stat, float initialValue);
	void initAttributes(entt::registry &registry, entt::entity entity);
	entt::entity createModifier(entt::registry &registry, entt::entity parent, entities::Scope scope, float value);
}  // namespace common::entities
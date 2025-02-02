#pragma once

#include "pch.hpp"

#include "components/children.hpp"
#include "components/modifiers.hpp"

namespace common::entities
{
	constexpr std::size_t ATTRIBUTES_SIZE = 6;
	using Attributes = common::components::children<ATTRIBUTES_SIZE>;

	enum Stat : int
	{
		NoneStat = 0,
		Health = 1,
		MaxHealth = 2,
		Speed = 3,
		Damage = 4,
		MinDamage = 5,
		MaxDamage = 6,
	};
	static std::unordered_map<std::string, Stat> const mapStat = {{"Health", Stat::Health}, {"MaxHealth", Stat::MaxHealth}, {"Speed", Stat::Speed},
																  {"Damage", Stat::Damage}, {"MinDamage", Stat::MinDamage}, {"MaxDamage", Stat::MaxDamage}};

	Stat getStat(std::string stat);
	Scope getScope(std::string scope);
	entt::entity createAttribute(entt::registry &registry, Stat stat, float initialValue);
	entt::entity createModifier(entt::registry &registry, common::entities::Scope scope, float value);
	entt::entity addModifier(entt::registry &registry, entt::entity attribute, common::entities::Scope scope, float value);
}  // namespace common::entities
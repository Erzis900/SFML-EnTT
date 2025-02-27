#pragma once

#include "pch.hpp"

#include "components/children.hpp"
#include "components/collider.hpp"
#include "components/modifiers.hpp"
#include "entities/attribute.hpp"

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
		Radius = 9,
		HealthRegen = 10,
		Range = 11
	};
	constexpr std::size_t ATTRIBUTES_SIZE = 11;
	using Attributes = components::children<ATTRIBUTES_SIZE>;

	static std::unordered_map<std::string, Stat> const mapStat = {
		{"health", Stat::Health},		 {"max-health", Stat::MaxHealth}, {"health-regen", Stat::HealthRegen},
		{"speed", Stat::Speed},			 {"damage", Stat::Damage},		  {"min-damage", Stat::MinDamage},
		{"max-damage", Stat::MaxDamage}, {"trigger", Stat::Trigger},	  {"base-attack-speed", Stat::BaseAttackSpeed},
		{"radius", Stat::Radius},		 {"range", Stat::Range}};

	struct Modifier
	{
		common::entities::Stat attribute;
		common::entities::Scope scope;
		float value;
	};

	Stat getStat(std::string stat);
	Scope getScope(std::string scope);
	entt::entity createAttribute(entt::registry &registry, entt::entity unit, Stat stat, float initialValue);
	void initAttributes(entt::registry &registry, entt::entity entity);
	entt::entity createModifier(entt::registry &registry, entt::entity parent, entities::Scope scope, float value);
	void applyModifiers(entt::registry &registry, entt::entity entity, common::entities::Attributes &attributes, std::vector<Modifier> &modifiers);
	void removeModifiers(entt::registry &registry, entt::entity source, common::entities::Attributes &attributes, std::vector<Modifier> &modifiers);
}  // namespace common::entities
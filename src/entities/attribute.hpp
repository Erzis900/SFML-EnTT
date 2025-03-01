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
		Health = 0,
		MaxHealth = 1,
		Speed = 2,
		Damage = 3,
		MinDamage = 4,
		MaxDamage = 5,
		Range = 6,
		BaseAttackSpeed = 7,
		Radius = 8,
		HealthRegen = 9,
		Place = 10,
		Group = 11,
		Travel = 12,
		Moment = 13,
		Trigger = 14,
		Area = 15,
		Kind = 16,
	};
	constexpr std::size_t ATTRIBUTES_SIZE = 17;	 // 1 + max(Stat)
	using Attributes = components::children<ATTRIBUTES_SIZE>;

	static std::unordered_map<std::string, Stat> const mapStat = {
		{"health", Stat::Health},
		{"max-health", Stat::MaxHealth},
		{"health-regen", Stat::HealthRegen},
		{"speed", Stat::Speed},
		{"damage", Stat::Damage},
		{"min-damage", Stat::MinDamage},
		{"max-damage", Stat::MaxDamage},
		{"base-attack-speed", Stat::BaseAttackSpeed},
		{"radius", Stat::Radius},
		{"range", Stat::Range},
		{"place", Stat::Place},
		{"group", Stat::Group},
		{"travel", Stat::Travel},
		{"moment", Stat::Moment},
		{"trigger", Stat::Trigger},
		{"area", Stat::Area},
		{"kind", Stat::Kind},
	};

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
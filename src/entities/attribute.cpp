#include "attribute.hpp"

#include "components/attribute.hpp"
#include "components/health.hpp"
#include "components/maxHealth.hpp"
#include "components/recalculate.hpp"
#include "components/relationship.hpp"
#include "components/speed.hpp"

namespace common::entities
{
	entt::entity createAttribute(entt::registry &registry, entt::entity unit, common::entities::Stat stat, float initialValue)
	{
		auto entity = registry.create();
		auto &relationship = registry.emplace<common::components::relationship>(entity);
		registry.emplace<common::components::attribute>(entity, initialValue, initialValue);
		switch (stat)
		{
		case common::entities::Stat::Health:
			registry.emplace<common::components::health>(unit, initialValue);
			break;
		case common::entities::Stat::MaxHealth:
			registry.emplace<common::components::maxHealth>(unit, initialValue);
			break;
		case common::entities::Stat::Speed:
			registry.emplace<common::components::speed>(unit, initialValue);
			break;
		default:
			break;
		}
		return entity;
	}
	entt::entity createModifier(entt::registry &registry, entt::entity parent, common::entities::Scope scope, float value)
	{
		auto modifierEntity = registry.create();
		auto &relationship = registry.emplace<common::components::relationship>(modifierEntity);
		relationship.source = parent;
		registry.emplace<common::components::modifier>(modifierEntity, value, scope);

		return modifierEntity;
	}
	Stat getStat(std::string stat)
	{
		auto it = mapStat.find(stat);
		if (it != mapStat.end())
		{
			return it->second;
		}
		else
		{
			return Stat::NoneStat;
		}
	}
	Scope getScope(std::string scope)
	{
		auto it = mapScope.find(scope);
		if (it != mapScope.end())
		{
			return it->second;
		}
		else
		{
			return Scope::NoneScope;
		}
	}
}  // namespace common::entities

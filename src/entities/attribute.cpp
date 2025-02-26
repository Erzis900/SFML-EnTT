#include "attribute.hpp"

#include "components/attribute.hpp"
#include "components/health.hpp"
#include "components/healthRegen.hpp"
#include "components/maxHealth.hpp"
#include "components/recalculate.hpp"
#include "components/relationship.hpp"
#include "components/speed.hpp"

namespace common::entities
{
	entt::entity createAttribute(entt::registry &registry, entt::entity unit, Stat stat, float initialValue)
	{
		auto entity = registry.create();
		auto &relationship = registry.emplace<components::relationship>(entity);
		registry.emplace<components::attribute>(entity, initialValue, initialValue);
		switch (stat)
		{
		case Stat::Health:
			registry.emplace<components::health>(unit, initialValue);
			break;
		case Stat::MaxHealth:
			registry.emplace<components::maxHealth>(unit, initialValue);
			break;
		case Stat::HealthRegen:
			registry.emplace<components::healthRegen>(unit, initialValue);
			break;
		case Stat::Speed:
			registry.emplace<components::speed>(unit, initialValue);
			break;
		case Stat::Radius:
			registry.emplace<components::collider>(unit, initialValue);
			break;
		default:
			break;
		}
		return entity;
	}

	/**
	 * @brief Check headers for the attributes that are initialized
	 */
	void initAttributes(entt::registry &registry, entt::entity entity)
	{
		registry.emplace<Attributes>(entity, Attributes{});

		auto &attributes = registry.get<Attributes>(entity).entities;
		attributes[Stat::Health] = createAttribute(registry, entity, Stat::Health, 50.f);
		attributes[Stat::MaxHealth] = createAttribute(registry, entity, Stat::MaxHealth, 50.f);
		attributes[Stat::HealthRegen] = createAttribute(registry, entity, Stat::HealthRegen, 0.2f);
		attributes[Stat::Speed] = createAttribute(registry, entity, Stat::Speed, 180.f);
		attributes[Stat::Damage] = createAttribute(registry, entity, Stat::Damage, 10.f);
		attributes[Stat::MinDamage] = createAttribute(registry, entity, Stat::MinDamage, 0.f);
		attributes[Stat::MaxDamage] = createAttribute(registry, entity, Stat::MaxDamage, 5.f);
		attributes[Stat::Trigger] = createAttribute(registry, entity, Stat::Trigger, 0.f);
		attributes[Stat::BaseAttackSpeed] = createAttribute(registry, entity, Stat::BaseAttackSpeed, 0.f);
		attributes[Stat::Radius] = createAttribute(registry, entity, Stat::Radius, 50.f);
	}

	entt::entity createModifier(entt::registry &registry, entt::entity target, entities::Scope scope, float value)
	{
		auto modifierEntity = registry.create();
		auto &relationship = registry.emplace<components::relationship>(modifierEntity);
		relationship.source = target;
		registry.emplace<components::modifier>(modifierEntity, value, scope);

		return modifierEntity;
	}

	void applyModifiers(entt::registry &registry, entt::entity target, common::entities::Attributes &attributes, std::vector<Modifier> &modifiers)
	{
		for (auto modifier : modifiers)
		{
			auto modifierEntity = common::entities::createModifier(registry, target, modifier.scope, modifier.value);

			auto &relationship = registry.get<common::components::relationship>(attributes.entities[modifier.attribute]);
			if (relationship.first_child == entt::null)
			{
				relationship.first_child = modifierEntity;
			}
			else
			{
				auto lastModifier = relationship.first_child;
				while (registry.get<common::components::relationship>(lastModifier).next != entt::null)
				{
					lastModifier = registry.get<common::components::relationship>(lastModifier).next;
				}
				registry.get<common::components::relationship>(lastModifier).next = modifierEntity;
				registry.get<common::components::relationship>(modifierEntity).prev = lastModifier;
			}
			registry.emplace_or_replace<common::components::recalculate>(attributes.entities[modifier.attribute], true);
		}
	}

	void removeModifiers(entt::registry &registry, entt::entity source, common::entities::Attributes &attributes, std::vector<Modifier> &modifiers)
	{
		for (auto modifier : modifiers)
		{
			auto &relationship = registry.get<common::components::relationship>(attributes.entities[modifier.attribute]);
			auto modifierEntity = relationship.first_child;
			while (modifierEntity != entt::null)
			{
				if (registry.get<common::components::relationship>(modifierEntity).source == source)
				{
					auto &mod = registry.get<common::components::modifier>(modifierEntity);
					auto &modifierRelationship = registry.get<common::components::relationship>(modifierEntity);
					if (modifierRelationship.prev != entt::null)
					{
						registry.get<common::components::relationship>(modifierRelationship.prev).next = modifierRelationship.next;
					}
					if (modifierRelationship.next != entt::null)
					{
						registry.get<common::components::relationship>(modifierRelationship.next).prev = modifierRelationship.prev;
					}
					if (relationship.first_child == modifierEntity)
					{
						relationship.first_child = modifierRelationship.next;
					}
					registry.destroy(modifierEntity);
					modifierEntity = modifierRelationship.next;
				}
				else
				{
					modifierEntity = registry.get<common::components::relationship>(modifierEntity).next;
				}
			}
			registry.emplace_or_replace<common::components::recalculate>(attributes.entities[modifier.attribute], true);
		}
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

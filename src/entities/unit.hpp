#include "external/entt.hpp"
#include <SFML/Graphics.hpp>
#include "config.hpp"

void createUnit(entt::registry &registry, entt::entity entity, sf::Vector2f pos, sf::Vector2f dir, float speed, float health, float maxHealth);
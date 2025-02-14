#include "renderAnimation.hpp"
#include "../components/color.hpp"
#include "../components/timer.hpp"
#include "components/position.hpp"
#include "components/source.hpp"

namespace features::animation::renderers
{
	void renderAnimations(entt::registry &registry, sf::RenderWindow &window, features::animation::AnimationLoader &animationLoader)
	{
		auto view = registry.view<features::animation::components::timer, common::components::position, common::components::source,
								  features::animation::components::Color>();
		for (auto [entity, timer, position, source, color] : view.each())
		{
			float time = timer.value / animationLoader.getTotalTime();
			sf::Sprite sprite = animationLoader.getSprite(time, color);

			auto pos = registry.get<common::components::position>(source.entity);
			sprite.setPosition({pos.x, pos.y});

			// std::cout << pos.x << std::endl;

			window.draw(sprite);
		}
	}
}  // namespace features::animation::renderers
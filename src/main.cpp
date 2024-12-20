#include <SFML/Graphics.hpp>
#include "../inc/entt.hpp"
struct position
{
    float x;
    float y;
};

struct velocity
{
    float dx;
    float dy;
};

void update(entt::registry &registry)
{
    auto view = registry.view<const position, velocity>();

    // use a callback
    view.each([](const auto &pos, auto &vel) { /* ... */ });

    // use an extended callback
    view.each([](const auto entity, const auto &pos, auto &vel) { /* ... */ });

    // use a range-for
    for (auto [entity, pos, vel] : view.each())
    {
        // ...
        registry.replace<position>(entity, pos.x + vel.dx, pos.y + vel.dx);
    }

    // use forward iterators and get only the components of interest
    for (auto entity : view)
    {
        auto &vel = view.get<velocity>(entity);
        // ...
    }
}
sf::CircleShape CreateO(position pos)
{
    // Radius: 50px
    sf::CircleShape o(50);
    o.setFillColor(sf::Color::White);
    o.setOutlineThickness(1);
    o.setOutlineColor(sf::Color::White);
    o.setPosition(pos.x, pos.y);
    return o;
}
int main()
{
    auto window = sf::RenderWindow({1920u, 1080u}, "CMake SFML Project");
    window.setFramerateLimit(144);
    entt::registry registry;

    for (auto i = 0u; i < 10u; ++i)
    {
        const auto entity = registry.create();
        registry.emplace<position>(entity, i * 134.f, i * 140.f);
        if (i % 2 == 0)
        {
            registry.emplace<velocity>(entity, i * .1f, i * .1f);
        }
    }

    update(registry);
    while (window.isOpen())
    {
        for (auto event = sf::Event(); window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear();
        update(registry);
        const auto &cregistry = registry;
        auto view = registry.view<position, velocity>();

        for (auto entity : view)
        {
            auto [pos, vel] = view.get(entity);
            window.draw(CreateO(pos));
        }
        window.display();
    }
}

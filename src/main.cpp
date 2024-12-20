#include <SFML/Graphics.hpp>
#include "../inc/entt.hpp"
#include <random>
#include <iostream>

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
        // registry.replace<position>(entity, pos.x + vel.dx, pos.y + vel.dx);
    }

    // use forward iterators and get only the components of interest
    for (auto entity : view)
    {
        auto &vel = view.get<velocity>(entity);
        // ...
    }

    sf::Vector2f dir = {0.f, 0.f};

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        dir.y = -1.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        dir.y = 1.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        dir.x = -1.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        dir.x = 1.f;
    }
    // Normalize the velocity vector
    float magnitude = std::sqrt(dir.x * dir.x + dir.y * dir.y);
    if (magnitude > 0)
    {
        dir.x /= magnitude;
        dir.y /= magnitude;
    }

    for (auto [entity, pos, vel] : view.each())
    {
        std::cout << dir.x << " " << dir.y << std::endl;
        registry.replace<position>(entity, pos.x + vel.dx * dir.x, pos.y + vel.dy * dir.y);

        if (-20 > pos.x || pos.x > 1200)
        {
            registry.replace<velocity>(entity, -vel.dx, vel.dy);
        }
        if (-20 > pos.y || pos.y > 800)
        {
            registry.replace<velocity>(entity, vel.dx, -vel.dy);
        }
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

    for (auto i = 0u; i < 3u; ++i)
    {
        const auto entity = registry.create();
        registry.emplace<position>(entity, i * 30.f, i * 150.f);
        registry.emplace<velocity>(entity, 2.f, 2.f);
    }

    while (window.isOpen())
    {
        for (auto event = sf::Event(); window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
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

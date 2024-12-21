#include "entt/entt.hpp"

namespace components

{

    struct source

    {

        source(entt::entity entity) : entity(entity) {}

        entt::entity entity;
    };

}

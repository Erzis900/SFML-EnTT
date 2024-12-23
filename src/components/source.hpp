#include "external/entt.hpp"

namespace common::components

{

    struct source

    {

        source(entt::entity entity) : entity(entity) {}

        entt::entity entity;
    };

}

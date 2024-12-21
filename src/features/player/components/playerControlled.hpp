#ifndef FEATURES_PLAYER_COMPONENTS_PLAYERCONTROLLED_HPP
#define FEATURES_PLAYER_COMPONENTS_PLAYERCONTROLLED_HPP

namespace features::player::components
{
    struct playerControlled
    {
        bool isControlled;
        playerControlled(bool controlled) : isControlled(controlled) {}
    };

}

#endif // FEATURES_PLAYER_COMPONENTS_PLAYERCONTROLLED_HPP

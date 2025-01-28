#pragma once

#include "pch.hpp"

namespace common::components {
    constexpr std::size_t FACTION_SIZE = 16;
    using FactionMask = std::bitset<FACTION_SIZE>;

    constexpr FactionMask FOES_MASK = FactionMask(0b0000000000000001);
    constexpr FactionMask ALLY_MASK = FactionMask(0b0000000000000010);

    struct faction {
        FactionMask affiliation;
        FactionMask allies;
        FactionMask foes;
    };
}  // namespace common::components

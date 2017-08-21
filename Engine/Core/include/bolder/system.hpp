#pragma once

namespace bolder {

/**
 * @brief Interface of Sub-Systems of the game engine
 */
class System {
public:
    System() {}
    virtual ~System() {}

    System(System& rhs) = delete;
    System& operator==(System& rhs) = delete;
};

}

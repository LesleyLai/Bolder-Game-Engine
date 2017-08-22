#pragma once

namespace bolder {

namespace event {
    class Channel;
}

/**
 * @brief Interface of Sub-Systems of the game engine
 */
class System {
public:
    System(event::Channel& channel);
    virtual ~System();

    System(System& rhs) = delete;
    System& operator==(System& rhs) = delete;

protected:
    /// Gets the event channel used by this system
    event::Channel& channel() const;

private:
    event::Channel& channel_;
};

}

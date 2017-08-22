#include "system.hpp"

namespace bolder {

System::System(event::Channel& channel) : channel_{channel}
{

}

System::~System() {}


event::Channel& System::channel() const
{
    return channel_;
}

}


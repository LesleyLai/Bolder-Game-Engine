#include <cstdint>
#include <cassert>
#include <stdexcept>
#include <iomanip>

#include "doctest.h"

using ID = std::uint32_t;

class World;

class Entity {
public:
    ID index() const {
        return index_;
    }

    friend std::ostream& operator<<(std::ostream& os, const Entity& entity);

private:
    friend class World;

    Entity(ID index, const World* world)
        : index_{index},
          world_{world} {
    }

    const ID index_;
    const World* world_;
};

class World {
public:
    /// Creates an entity and return that entity
    Entity create_entity();

    /// Distory entity with a certain id
    void destory_entity(ID id);

private:
    ID count_ = 0;
};

inline bool operator==(Entity lhs, Entity rhs) {
    return lhs.index() == rhs.index();
}

inline bool operator!=(Entity lhs, Entity rhs) {
    return lhs.index() != rhs.index();
}


std::ostream& operator<<(std::ostream& os, const Entity& entity) {
    os << "Entity " << "0x" << std::hex << std::setfill('0') <<
          std::setw(sizeof(ID) * 2) << entity.index();
    return os;
}


Entity World::create_entity()
{
    assert(count_ != (ID{0} - 1));
    return Entity {count_++, this};
}

void World::destory_entity(ID id)
{
    if (id >= count_) {
        throw std::runtime_error{"Trying to delete not exist entities\n"};
    }

    // Todo: destory all the components
}

SCENARIO("World class") {
    World world;
    const auto entity0 = world.create_entity();
    const auto entity1 = world.create_entity();

    SUBCASE("Create entity from factory") {
        REQUIRE_EQ(entity0.index(), 0);
        REQUIRE_EQ(entity1.index(), 1);
    }

    SUBCASE("Cannot destory entity that have ID larger then created entities") {
        REQUIRE_THROWS_AS(world.destory_entity(2), std::runtime_error);
    }

    SUBCASE("Compare entity: ==") {
        REQUIRE_EQ(entity0, entity0);
        REQUIRE_NE(entity0, entity1);
    }

}

#include "doctest.h"

#include "bolder/graphics/image.hpp"
#include "bolder/vector.hpp"
#include "bolder/angle.hpp"

namespace bolder { namespace graphics {

struct Transform2 {
    math::Vec2 position;
    math::Vec2 scale;
    math::Radian rotation;
};

struct Sprite {
    Sprite(const Image& image) {

    }

};

}} // namespace bolder::graphics

using namespace bolder::graphics;

TEST_CASE("Create sprite") {
    Sprite(Image{});
}

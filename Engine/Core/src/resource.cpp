#include <unordered_map>
#include <cstdint>

#include "resource.hpp"

namespace bolder { namespace resource {

class Graphics_resources;

enum class Type {
    Texture,
    Shader_program,
};

using Handle = std::uint16_t;

/**
 * @brief The resource::Package class packes all kind of resources.
 * @todo Serialization of the whole class
 */
class Package {
    //void make_texture(Handle handle, const Image& image);

private:
    Graphics_resources* graphics_resources_;
};

}} // namespace bolder::resource

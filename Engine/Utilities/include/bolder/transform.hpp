#include "matrix.hpp"

namespace bolder { namespace math {
/// Returns an orthographics projection matrix
Mat4 orthographic(float left,   float right,
                  float bottom, float top,
                  float z_near,   float z_far);

}}

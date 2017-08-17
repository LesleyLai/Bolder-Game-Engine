#include "transform.hpp"

namespace bolder { namespace math {

/**
 * @brief Returns an orthographics projection matrix
 *
 * The returned matrix, when used as a Camera's projection matrix, creates a
 * view showing the area between left, right, top and bottom, with z_near and
 * z_far as the near and far depth clipping planes.
 */
Mat4 orthographic(float left,   float right,
                  float bottom, float top,
                  float z_near,   float z_far) {
    Mat4 result(1);
    result[0][0] = 2 / (right - left);
    result[1][1] = 2 / (top - bottom);
    result[2][2] = -2 / (z_far - z_near);
    result[3][0] = -(right + left) / (right - left);
    result[3][1] = -(top + bottom) / (top - bottom);
    result[3][2] = -(z_far + z_near) / (z_far - z_near);
    return result;
}

}}

#pragma once

#include <string>

namespace bolder { namespace file_util {

/** @addtogroup utilities
 * @{
 */

/// Returns a string of whole content of a file
std::string load(const char* filename);

/** @}*/

}} // namespace bolder::utility


#pragma once

#include "bolder/integer.hpp"

namespace bolder { namespace resource {

template<typename Handle, typename T, int capacity = 4096>
class Handle_manager;

/**
 * @class Handle
 * @ingroup resource_group
 * @brief Handle refer to internal data.
 * @tparam N Bits for index, remaining bits are for generation
 *
 * Handle refer to some data that owned by a system directly via Handle_manager.
 * Internally, handles are indices of data inside Handle_manager.
 *
 * Handle also store generation of data in which the index was created.
 * Generations are also stored for every data inside Handle_manager, where they
 * are monotonically increasing counters that get incremented each time their
 * corresponding data items are deleted. Thus, the Handle_manager knows whether
 * a handle is still valid.
 *
 * This struct template is a generic handle implementation. To define a handle
 * type, simply define a typedef:
 * @code{.cpp}
 * using Vertex_buffer_handle = Handle<12>;
 * @endcode
 *
 * @see Handle_manager about how to manage underlying resource using handles.
 */
template <size_t N>
struct Handle {
    static_assert(N < 32, "Bits for index cannot be equal to or greater than"
                          " the bit for the whole handle.");

    static constexpr auto index_bits = N;
    static constexpr auto generation_bits = 32 - N;

    const uint32 index : index_bits;
    const uint32 generation : generation_bits;

private:
    template<typename Handle, typename T, int capacity>
    friend class Handle_manager;

    // Prevent outside code from creating handles
    Handle(uint32 index, uint32 generation)
        : index{index}, generation{generation}
    {}
};

}} // namespace bolder::resource

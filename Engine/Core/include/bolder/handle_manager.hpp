#pragma once

#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <limits>

#include "bolder/handle.hpp"
#include "bolder/resource_error.hpp"

namespace bolder { namespace resource {

namespace detail {
template<typename Handle>
struct Handle_entry {
    uint32 next_free_index : Handle::index_bits;
    uint32 generation : Handle::generation_bits;
};
}

template<typename Handle, typename T, int capacity>
class Handle_manager {
    static constexpr auto max_capacity = 1u << Handle::index_bits;
    static_assert(capacity <= max_capacity,
                  "capacity bigger then max value of handle index");
public:
    using value_type = T;
    using size_type = size_t;

    Handle_manager() {
        size_t next = 1;
        std::generate(handles_.begin(), handles_.end(), [&next]() {
            detail::Handle_entry<Handle> entry {next, 0};
            ++next;
            return entry;
        });
    }

    Handle add(value_type value);

    void remove(Handle handle);

    /**
     * @brief Gets underlying variable that a handle refer to.
     * @param handle
     * @return A pointer to underlying variable that a handle refer to;
     * nullptr if the handle is no longer valid.
     */
    const value_type* operator[](Handle handle) {
        const auto index = handle.index;
        if (handle.generation != handles_[index].generation) {
            return nullptr;
        }

        return &elems_[index];
    }

    size_type size() const;

private:
    std::bitset<capacity> actives_;
    std::array<detail::Handle_entry<Handle>, capacity> handles_;
    std::array<T, capacity> elems_;
    size_type size_ = 0;
    size_type first_free_entry_ = 0;
};

template<typename Handle, typename T, int capacity>
Handle Handle_manager<Handle, T, capacity>::add(T elem) {
    if (size_ == capacity) {
        throw Resource_error{Handle_error_type::out_of_space};
    }

    const auto index = first_free_entry_;
    const auto generation = handles_[index].generation;
    first_free_entry_ = handles_[index].next_free_index;
    actives_[index] = elem;
    elems_[index] = elem;
    ++size_;
    return Handle{index, generation};
}

template<typename Handle, typename T, int capacity>
void Handle_manager<Handle, T, capacity>::remove(Handle handle) {
    const auto index = handle.index;
    if (actives_[index] == false) {
        throw Resource_error{Handle_error_type::null_entry};
    } else if (handles_[index].generation != handle.generation) {
        throw Resource_error{Handle_error_type::invalid_handle};
    }

    handles_[index].next_free_index = first_free_entry_;
    first_free_entry_ = index;

    actives_[index] = false;
    ++handles_[index].generation;
    --size_;
}

template<typename Handle, typename T, int capacity>
typename Handle_manager<Handle, T, capacity>::size_type
Handle_manager<Handle, T, capacity>::size() const {
    return size_;
}

}} // namespace bolder::resource

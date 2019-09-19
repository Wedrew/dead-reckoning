//!**********************************************************
//! @file   queue_family_indices.hpp
//!
//! @author Andrew Pagan <apagan289@gmail.com>
//!
//! @date   June 2019
//!
//! @brief  QueueFamilyIndices definition
//!
//! Copyright 2019-2020 Harmonics Inc
//! All rights reserved.
//!***********************************************************/

#ifndef QUEUE_FAMILY_INDICES_HPP
#define QUEUE_FAMILY_INDICES_HPP

#define VULKAN_ENABLE_LUNARG_VALIDATION
#include "vulkan/vulkan.h"

namespace Zero {

struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;

    bool isComplete() {
        return graphicsFamily.has_value() and presentFamily.has_value();
    }
};

}

#endif
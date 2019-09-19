//!**********************************************************
//! @file   swap_chain_support_details.cpp
//!
//! @author Andrew Pagan <apagan289@gmail.com>
//!
//! @date   June 2019
//!
//! @brief  Defines all renderer operations including
//!         validation layers, graphics pipeline, 
//!         framebuffers, commmand buffers, etc...
//!
//! Copyright 2019-2020 Harmonics Inc
//! All rights reserved.
//!***********************************************************/

#ifndef SWAP_CHAIN_SUPPORT_DETAILS_HPP
#define SWAP_CHAIN_SUPPORT_DETAILS_HPP

#define VULKAN_ENABLE_LUNARG_VALIDATION
#include "vulkan/vulkan.h"

namespace Zero {

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

}

#endif
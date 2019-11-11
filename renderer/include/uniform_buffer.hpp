//!**********************************************************
//! @file   uniform_buffer.hpp
//!
//! @author Andrew Pagan <apagan289@gmail.com>
//!
//! @date   June 2019
//!
//! @brief  UniformBufferObject definition
//!
//! Copyright 2019-2020 Harmonics Inc
//! All rights reserved.
//!***********************************************************/

#ifndef UNIFORM_BUFFER_HPP
#define UNIFORM_BUFFER_HPP

#include "glm/glm.hpp"

namespace Zero {

struct UniformBuffer {
    alignas(16) glm::mat4 model;
    alignas(16) glm::mat4 view;
    alignas(16) glm::mat4 proj;
};

}

#endif
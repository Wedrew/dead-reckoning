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
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 proj;
};

}

#endif
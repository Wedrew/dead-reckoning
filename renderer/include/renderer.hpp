//!**********************************************************
//! @file   renderer.cpp
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

#ifndef RENDERER_HPP
#define RENDERER_HPP

#define VULKAN_ENABLE_LUNARG_VALIDATION
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define STB_IMAGE_IMPLEMENTATION

#include <string>
#include <optional>
#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "vulkan/vulkan.h"
#include "GLFW/glfw3.h"
#include "utils/utils.hpp"
#include "assets_manager/assets_manager.hpp"
#include "window_manager/window_details.hpp"
#include "queue_family_indices.hpp"
#include "swap_chain_support_details.hpp"

namespace Zero {

struct Vertex {
    glm::vec2 pos;
    glm::vec3 color;

    static VkVertexInputBindingDescription getBindingDescription() {
        VkVertexInputBindingDescription bindingDescription = {};
        bindingDescription.binding = 0;
        bindingDescription.stride = sizeof(Vertex);
        bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

        return bindingDescription;
    }

    static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions() {
        std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions = {};
        attributeDescriptions[0].binding = 0;
        attributeDescriptions[0].location = 0;
        attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
        attributeDescriptions[0].offset = offsetof(Vertex, pos);

        attributeDescriptions[1].binding = 0;
        attributeDescriptions[1].location = 1;
        attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[1].offset = offsetof(Vertex, color);

        return attributeDescriptions;
    }
};
const std::vector<Vertex> vertices = {
    {{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
    {{0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
    {{0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
    {{-0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}}
};

const std::vector<uint16_t> indices = {
    0, 1, 2, 2, 3, 0
};


class Renderer {

public:
    Renderer(std::string title);
    ~Renderer();

protected:
    std::string title;
    std::vector<char const*> const validationLayers = {"VK_LAYER_KHRONOS_validation"};
    std::vector<char const*> const deviceExtensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};
    bool static const enableValidationLayers;

    void drawFrame();
    void waitDeviceIdle();
    void updateButtonsPressed();
    void initVulkan(GLFWwindow *window);
    void uninitializeRenderer(GLFWwindow *window);
    void setMonitor(MonitorDetails *monitor) {currentMonitor = monitor;};
    void setFrameBufferResize(bool wasResized) {frameBufferResized = wasResized;};
    static void frameBufferResizeCallback(GLFWwindow* window, int width, int height);

private:
    int const maxFramesInFlight = 2;
    bool frameBufferResized = false;
    size_t currentFrame = 0;

    GLFWwindow *_window;
    VkDevice device;
    VkQueue graphicsQueue;
    VkQueue presentQueue;
    VkInstance instance;
    VkDebugUtilsMessengerEXT debugMessenger;
    VkSurfaceKHR surface;
    VkSwapchainKHR swapChain;
    VkFormat swapChainImageFormat;
    VkExtent2D swapChainExtent;
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkPhysicalDeviceProperties deviceProperties;
    VkPipelineLayout pipelineLayout;
    VkPipeline graphicsPipeline;
    VkRenderPass renderPass;
    VkCommandPool commandPool;
    VkBuffer vertexBuffer;
    VkDeviceMemory vertexBufferMemory;
    VkBuffer indexBuffer;
    VkDeviceMemory indexBufferMemory;
    VkDescriptorSetLayout descriptorSetLayout;
    VkDescriptorPool descriptorPool;
    MonitorDetails *currentMonitor;
    std::string rendererType = type(this);
    std::string engineName = "Over Zero";
    std::shared_ptr<spdlog::logger> rendererLogger = createSpdLogger(rendererType, spdlog::level::debug);
    std::vector<VkImage> swapChainImages;
    std::vector<VkImageView> swapChainImageViews;
    std::vector<VkFramebuffer> swapChainFramebuffers;
    std::vector<VkCommandBuffer> commandBuffers;
    std::vector<VkSemaphore> imageAvailableSemaphores;
    std::vector<VkSemaphore> renderFinishedSemaphores;
    std::vector<VkFence> inFlightFences;
    std::vector<VkPipelineShaderStageCreateInfo> shaderStageCreateInfos;
    std::vector<VkBuffer> uniformBuffers;
    std::vector<VkDeviceMemory> uniformBuffersMemory;
    std::vector<VkDescriptorSet> descriptorSets;
    AssetsManager shaders = AssetsManager();

    void createInstance();
    void createSurface(GLFWwindow *window);
    void createLogicalDevice();
    void createSwapChain();
    void createImageViews();
    void createGraphicsPipeline();
    void createRenderPass();
    void createFrameBuffers();
    void createCommandPool();
    void createCommandBuffers();
    void createSyncObjects();
    void recreateSwapChain();
    void cleanupSwapChain();
    void createVertexBuffer();
    void createIndexBuffer();
    void createDescriptorSetLayout();
    void createUniformBuffers();
    void createDescriptorPool();
    void createDescriptorSets();
    void updateUniformBuffer(uint32_t currentImage);
    void pickPhysicalDevice();
    void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
    void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
    bool isDeviceSuitable(VkPhysicalDevice device);
    bool checkDeviceExtensionSupport(VkPhysicalDevice device);
    bool checkValidationLayerSupport();
    void setupDebugMessenger();
    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
    SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
    VkSurfaceFormatKHR chooseSwapSurfaceFormat(std::vector<VkSurfaceFormatKHR> const &availableFormats);
    VkPresentModeKHR chooseSwapPresentMode(std::vector<VkPresentModeKHR> const &availablePresentModes);
    VkExtent2D chooseSwapExtent(VkSurfaceCapabilitiesKHR const &capabilities);
    VkShaderModule createShaderModule(std::vector<uint32_t> const& code);
    std::vector<char const*> getRequiredExtensions();
    uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
    int rateDeviceSuitability(VkPhysicalDevice device);

    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                                    VkDebugUtilsMessageTypeFlagsEXT messageType,
                                                    VkDebugUtilsMessengerCallbackDataEXT const *pCallbackData,
                                                    void *pUserData);

};

}

#endif
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
#define GLM_ENABLE_EXPERIMENTAL

#include <string>
#include <optional>
#include <vector>

#include "vulkan/vulkan.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "GLFW/glfw3.h"

#include "config.hpp"
#include "utils.hpp"
#include "game_object.hpp"
#include "vertex.hpp"
#include "window_details.hpp"
#include "assets_manager.hpp"
#include "queue_family_indices.hpp"
#include "swap_chain_support_details.hpp"

namespace Zero {

class Renderer {

public:
    Renderer();
    ~Renderer();

protected:
    float distance = 2.0f;
    float radius = 5.0f;
    bool leftButtonDown = false;
    int frameBufferWidth = 0, frameBufferHeight = 0;

    std::vector<char const*> validationLayers = {"VK_LAYER_KHRONOS_validation"};
    std::vector<char const*> instanceExtensions = {"VK_KHR_get_physical_device_properties2", "VK_KHR_get_surface_capabilities2"};
    std::vector<char const*> deviceExtensions = {"VK_KHR_swapchain"};
    std::vector<std::string> optionalExtensions = {"VK_EXT_full_screen_exclusive", "VK_KHR_get_memory_requirements2", "VK_NV_ray_tracing"};
    bool const enableValidationLayers = Zero::ENABLE_VALIDATION_LAYERS;
    bool frameBufferResized = false;

    void drawFrame();
    void waitDeviceIdle();
    void updateButtonsPressed();
    void initVulkan(GLFWwindow *window);
    void uninitializeRenderer(GLFWwindow *window);
    void setMonitor(MonitorDetails *monitor) {currentMonitor = monitor;};
    void setFrameBufferResize(bool wasResized) {frameBufferResized = wasResized;};
    void setFrameBufferDimensions(int x, int y) {frameBufferWidth = x; frameBufferHeight = y;};

private:
    int const maxFramesInFlight = 2;
    bool vulkanDebugPedantic = false;
    size_t currentFrame = 0;

    GLFWwindow *window;
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
    VkImage textureImage;
    VkImageView textureImageView;
    VkSampler textureSampler;
    VkDeviceMemory textureImageMemory;
    VkImage depthImage;
    VkDeviceMemory depthImageMemory;
    VkImageView depthImageView;
    MonitorDetails *currentMonitor;
    GameObject house = GameObject("chalet");
    std::string rendererType = type(this);
    std::string title = Zero::GAME_NAME;
    std::string engineName = Zero::ENGINE_NAME;
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
    std::shared_ptr<spdlog::logger> rendererLogger = createSpdLogger(rendererType, spdlog::level::debug);
    std::shared_ptr<AssetsManager> assets = AssetsManager::getAssetsManager();

    //TEMPORARY
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;

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
    void createTextureImage();
    void createTextureImageView();
    void createTextureSampler();
    void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
    void createDepthResources();
    void updateUniformBuffer(uint32_t currentImage);
    void pickPhysicalDevice();
    void endSingleTimeCommands(VkCommandBuffer commandBuffer);
    void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
    void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
    void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
    void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
    bool isDeviceSuitable(VkPhysicalDevice device);
    bool checkDeviceExtensionSupport(VkPhysicalDevice device);
    bool checkValidationLayerSupport();
    bool hasStencilComponent(VkFormat format);
    void setupDebugMessenger();
    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
    SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
    VkSurfaceFormatKHR chooseSwapSurfaceFormat(std::vector<VkSurfaceFormatKHR> const &availableFormats);
    VkPresentModeKHR chooseSwapPresentMode(std::vector<VkPresentModeKHR> const &availablePresentModes);
    VkExtent2D chooseSwapExtent(VkSurfaceCapabilitiesKHR const &capabilities);
    VkShaderModule createShaderModule(std::vector<uint32_t> const &code);
    VkCommandBuffer beginSingleTimeCommands();
    VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);
    VkFormat findSupportedFormat(std::vector<VkFormat> const &candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
    VkFormat findDepthFormat();
    std::vector<char const*> getRequiredExtensions();
    uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
    int rateDeviceSuitability(VkPhysicalDevice device);

    // PFN_vkCreateRayTracingPipelinesNV vkCreateRayTracingPipelinesNV;
    // PFN_vkGetRayTracingShaderGroupHandlesNV vkGetRayTracingShaderGroupHandlesNV;
    // VkPhysicalDeviceRayTracingPropertiesNV rayTracingProperties{};


    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                                    VkDebugUtilsMessageTypeFlagsEXT messageType,
                                                    VkDebugUtilsMessengerCallbackDataEXT const *pCallbackData,
                                                    void *pUserData);

};

}

#endif
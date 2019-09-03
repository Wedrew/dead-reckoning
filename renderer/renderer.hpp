#ifndef RENDERER_H
#define RENDERER_H

#define VULKAN_ENABLE_LUNARG_VALIDATION

#include <string>
#include <optional>
#include <vector>

#include "vulkan/vulkan.h"
#include "GLFW/glfw3.h"
#include "utils/utils.hpp"
#include "window/window_details.hpp"
#include "assets_manager/assets_manager.hpp"

namespace zero {

struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;

    bool isComplete() {
        return graphicsFamily.has_value() and presentFamily.has_value();
    }
};

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
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

    void initVulkan(GLFWwindow *window);
    void uninitializeRenderer(GLFWwindow *window);
    void setMonitor(MonitorDetails *monitor) {currentMonitor = monitor;};
    void drawFrame();
    void waitDeviceIdle();
    void setFrameBufferResize(bool wasResized) {frameBufferResized = wasResized;};

private:
    const int maxFramesInFlight = 2;
    bool frameBufferResized = false;
    size_t currentFrame = 0;

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
    MonitorDetails *currentMonitor;
    std::string rendererType = type(this);
    std::string engineName = "Over Zero";
    std::shared_ptr<spdlog::logger> rendererLogger = zero::createSpdLogger(rendererType, spdlog::level::debug);
    std::vector<VkImage> swapChainImages;
    std::vector<VkImageView> swapChainImageViews;
    std::vector<VkFramebuffer> swapChainFramebuffers;
    std::vector<VkCommandBuffer> commandBuffers;
    std::vector<VkSemaphore> imageAvailableSemaphores;
    std::vector<VkSemaphore> renderFinishedSemaphores;
    std::vector<VkFence> inFlightFences;

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
    void pickPhysicalDevice();
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

    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                                    VkDebugUtilsMessageTypeFlagsEXT messageType,
                                                    VkDebugUtilsMessengerCallbackDataEXT const *pCallbackData,
                                                    void *pUserData);
};

}

#endif
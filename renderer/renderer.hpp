#ifndef RENDERER_H
#define RENDERER_H

#include <string>
#include <optional>
#include <vector>

#define VULKAN_ENABLE_LUNARG_VALIDATION
#define GLFW_INCLUDE_VULKAN

#include "GLFW/glfw3.h"
#include "utils/utils.hpp"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
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

private:
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
    MonitorDetails *currentMonitor;
    std::string rendererType = type(this);
    std::string engineName = "Over Zero";
    std::shared_ptr<spdlog::logger> rendererLogger = zero::createSpdLogger(rendererType, spdlog::level::debug);
    std::vector<VkImage> swapChainImages;
    std::vector<VkImageView> swapChainImageViews;
    AssetsManager shaders = AssetsManager("shaders");

    void createInstance();
    void createSurface(GLFWwindow *window);
    void createLogicalDevice();
    void createSwapChain();
    void createImageViews();
    void createGraphicsPipeline();
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
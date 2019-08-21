#include <fstream>
#include <iterator>

#include "assets_manager.hpp"

namespace fs = std::filesystem;

namespace zero {

AssetsManager::AssetsManager(std::string dirName) : assetsDir(fs::absolute(dirName)) {
    recursivelyAcquire(assetsDir);

    assetsLogger->info("Found directory {}", dirName);
}

void AssetsManager::recursivelyAcquire(fs::path const &path) {
    // Get all the files in the assets directory
    if(fs::exists(path) and fs::is_directory(path)) {
        for(auto const &file: fs::recursive_directory_iterator(path)) {
            if(not file.is_directory()) {
                std::ifstream vShadFrag{file.path()};
                std::string vShadFragContents{std::istreambuf_iterator<char>(vShadFrag), std::istreambuf_iterator<char>()};
                assets.insert(std::pair<fs::path, std::string>(file, vShadFragContents));
            }
        }
    }
}

void AssetsManager::refreshFiles() {
    assets.clear();
    recursivelyAcquire(assetsDir);
}

bool AssetsManager::compileShaders(bool optimize) {
    for(auto const &shader : assets) {
        // TODO: Add error handling
        shaderc_shader_kind kind;

        if(shader.first.extension().string() == ".frag") {
            kind = shaderc_fragment_shader;
        } else if(shader.first.extension().string() == ".vert") {
            kind = shaderc_vertex_shader;
        } else {
            kind = shaderc_compute_shader;
            assetsLogger->debug("Unrecongnized Stem: {}", shader.first.extension().string());
        }
        //auto preProcc = preprocessShader(shader.first, kind, shader.second);
        //auto spirVAssembly = compileToAssembly(shader.first, kind, shader.second, optimize);
        auto spirVBinary = compileFile(shader.first, kind, shader.second, optimize);

        spirVModules.insert(std::pair<fs::path, std::vector<uint32_t>>(shader.first, spirVBinary));
    }
    return true;
}

// Returns GLSL shader source text after preprocessing.
std::string AssetsManager::preprocessShader(fs::path const &path, shaderc_shader_kind kind, std::string const &source) {
    //options.AddMacroDefinition("MY_DEFINE", "1");

    auto result = compiler.PreprocessGlsl(source, kind, path.c_str(), options);

    if(result.GetCompilationStatus() not_eq shaderc_compilation_status_success) {
        assetsLogger->error("Failed to preprocess shader: {}", path.string());
        assetsLogger->error("Shaderc Error: {}", result.GetErrorMessage());
        return nullptr;
    } else {
        assetsLogger->debug("Successfully preprocessed shader: {}", path.string());
        return {result.cbegin(), result.cend()};
    }
}

// Compiles a shader to SPIR-V assembly. Returns the assembly text
// as a string.
std::string AssetsManager::compileToAssembly(fs::path const &path, shaderc_shader_kind kind, std::string const &source, bool optimize) {
    //options.AddMacroDefinition("MY_DEFINE", "1");

    if(optimize){
        options.SetOptimizationLevel(shaderc_optimization_level_size);
    }

    auto result = compiler.CompileGlslToSpvAssembly(source, kind, path.c_str(), options);

    if(result.GetCompilationStatus() not_eq shaderc_compilation_status_success) {
        assetsLogger->error("Failed to build assembly for: {}", path.string());
        assetsLogger->error("Shaderc Error: {}", result.GetErrorMessage());
        return nullptr;
    } else {
        assetsLogger->debug("Successfully assembled: {}", path.string());
        return {result.cbegin(), result.cend()};
    }
}

// Compiles a shader to a SPIR-V binary. Returns the binary as
// a vector of 32-bit words
std::vector<uint32_t> AssetsManager::compileFile(fs::path const &path, shaderc_shader_kind kind, std::string const &source, bool optimize) {
    //options.AddMacroDefinition("MY_DEFINE", "1");

    if(optimize) {
        options.SetOptimizationLevel(shaderc_optimization_level_size);
    }

    auto module = compiler.CompileGlslToSpv(source, kind, path.c_str(), options);

    if(module.GetCompilationStatus() not_eq shaderc_compilation_status_success) {
        assetsLogger->error("Failed to build binary for: {}", path.string());
        assetsLogger->error("Shaderc Error: {}", module.GetErrorMessage());
        return std::vector<uint32_t>();
    } else {
        assetsLogger->debug("Succesfully built binary for: {}", path.string());
        return {module.cbegin(), module.cend()};
    }
}
}

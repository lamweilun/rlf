#include <Engine/Engine.hpp>

#include <Node/Game/GameManagerNode.hpp>
#include <Node/Player/PlayerNode.hpp>
#include <Node/Player/PlayerBulletNode.hpp>

#ifdef RLF_EDITOR
#include <source_location>
#endif

static inline constexpr std::string_view assetsPathName = "assets";

int main() {
    auto& engine = rlf::Engine::getInstance();

    // Register game node types
    engine.setSetupFunc([]() {
        rlf::TypeManager::getInstance().registerType<ext::Node::GameManagerNode>();
        rlf::TypeManager::getInstance().registerType<ext::Node::PlayerNode>();
        rlf::TypeManager::getInstance().registerType<ext::Node::PlayerBulletNode>();
    });

#ifdef RLF_EDITOR
    // Set assets path to be this internal project folder
    std::filesystem::path p(std::source_location::current().file_name());
    auto                  assetsPath = p.parent_path().append(assetsPathName);
    engine.setAssetsDirectory(assetsPath);

    // Set shutdown function such that it will copy assets over to application directory
    engine.setShutdownFunc([](std::shared_ptr<rlf::Node::BaseNode>) {
        std::filesystem::path currentPath     = GetWorkingDirectory();
        std::filesystem::path destinationPath = std::filesystem::path(GetApplicationDirectory()).append(assetsPathName);
        std::filesystem::remove_all(destinationPath);
        auto const copyOptions = std::filesystem::copy_options::recursive;
        std::filesystem::copy(currentPath, destinationPath, copyOptions);

        // imgui.ini remove
        auto imguiConfigFile = destinationPath.append("imgui.ini");
        std::filesystem::remove(imguiConfigFile);
    });
#else
    // Set assets path to application directory
    std::filesystem::path p(GetApplicationDirectory());
    auto                  assetsPath = p.append(assetsPathName);
    engine.setAssetsDirectory(assetsPath);

    // Set initial world to load
    engine.setInitialWorldToLoad("world/game.json");
#endif

    // Run the engine
    engine.run();
}

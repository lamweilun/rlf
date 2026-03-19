#include <Engine/Engine.hpp>

#include <Node/Game/MainMenuManagerNode.hpp>
#include <Node/Game/GameManagerNode.hpp>
#include <Node/Player/PlayerNode.hpp>
#include <Node/Player/PlayerBulletNode.hpp>
#include <Node/Asteroid/AsteroidNode.hpp>

#ifdef RLF_EDITOR
#include <source_location>
#endif

static inline constexpr std::string_view assetsPathName = "assets";

int main()
{
    auto& engine = rlf::Engine::getInstance();

    // Register game node types
    engine.setSetupFunc([](rlf::NodeManager& nm)
                        {
        nm.registerType<ext::Node::MainMenuManagerNode>();
        nm.registerType<ext::Node::GameManagerNode>();
        nm.registerType<ext::Node::PlayerNode>();
        nm.registerType<ext::Node::PlayerBulletNode>();
        nm.registerType<ext::Node::AsteroidNode>(); });

#ifdef RLF_EDITOR
    // Set assets path to be this internal project folder
    std::filesystem::path p(std::source_location::current().file_name());
    auto                  assetsPath = p.parent_path().append(assetsPathName);
    engine.setAssetsDirectory(assetsPath);

    // Set shutdown function such that it will copy assets over to application directory
    engine.setShutdownFunc([](rlf::Node::BaseNode*)
                           {
        static constexpr std::string_view appName     = "exteroids";
        std::filesystem::path             currentPath = GetWorkingDirectory();
#ifdef RLF_DEBUG
        static constexpr std::string_view buildTypePathName = "Debug";
#else
        static constexpr std::string_view buildTypePathName = "Release";
#endif
        std::filesystem::path destinationPath = std::filesystem::path(GetApplicationDirectory())
                                                    .append("..")
                                                    .append("..")
                                                    .append(buildTypePathName)
                                                    .append(appName)
                                                    .append(assetsPathName);
        std::println("currentPath: {}, destinationPath: {}", currentPath.string(), destinationPath.string());
        std::filesystem::remove_all(destinationPath);
        std::filesystem::copy(currentPath, destinationPath, std::filesystem::copy_options::recursive | std::filesystem::copy_options::overwrite_existing);

        // imgui.ini remove
        auto imguiConfigFile = destinationPath.append("imgui.ini");
        std::filesystem::remove(imguiConfigFile); });
#else
    // Set assets path to application directory
    std::filesystem::path p(GetApplicationDirectory());
    auto                  assetsPath = p.append(assetsPathName);
    engine.setAssetsDirectory(assetsPath);

    // Set initial world to load
    engine.setInitialWorldToLoad("world/MainMenu.json");
#endif

    // Run the engine
    rlf::Engine::Config config{1920, 1080, "Exteroids"};
    engine.run(config);
}

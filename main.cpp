#include <System/TypeSystem.hpp>
#include <System/RenderSystem.hpp>
#include <System/PhysicsSystem.hpp>

#include <Util/Accessor/JsonDeserializer.hpp>
#include <Util/Accessor/JsonSerializer.hpp>

#include <game/Player/PlayerNode.hpp>
#include <game/Environment/WallNode.hpp>
#include <game/Ball/BallNode.hpp>

int main() {
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_WINDOW_HIGHDPI);
    InitWindow(1280, 720, "Hello rlf");
    SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));
    // ToggleFullscreen();

    rlf::TypeSystem::getInstance();
    auto& renderSystem = rlf::RenderSystem::getInstance();
    rlf::PhysicsSystem::getInstance();

    // DO NOT CHANGE THIS
    auto rootNode = std::make_shared<rlf::BaseNode>();
    rootNode->init();

    // Add new children here
    auto playerNode = rootNode->addChild<rlf::PlayerNode>();
    playerNode->setPosition({50.0f, 360.0f, 0.0f});

    auto topWallNode = rootNode->addChild<rlf::WallNode>();
    topWallNode->setPosition({640.0f, 20.0f, 0.0f});
    topWallNode->setScale({10.0f, 1200.0f, 1.0f});
    topWallNode->setRotationEulerDeg({0.0f, 0.0f, 90.0f});

    auto bottomWallNode = rootNode->addChild<rlf::WallNode>();
    bottomWallNode->setPosition({640.0f, 700.0f, 0.0f});
    bottomWallNode->setScale({10.0f, 1200.0f, 1.0f});
    bottomWallNode->setRotationEulerDeg({0.0f, 0.0f, -90.0f});

    auto backWallNode = rootNode->addChild<rlf::WallNode>();
    backWallNode->setPosition({1200.0f, 360.0f, 0.0f});
    backWallNode->setScale({10.0f, 700.0f, 1.0f});
    backWallNode->setRotationEulerDeg({0.0f, 0.0f, 180.0f});

    auto ballNode = rootNode->addChild<rlf::BallNode>();
    ballNode->setPosition({640.0f, 360.0f, 0.0f});

    while (!WindowShouldClose()) {
        // if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_O)) {
        //     rlf::Json     j = rootNode->serialize();
        //     std::ofstream ofs("output.json");
        //     ofs << j.dump(2);
        // } else if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_I)) {
        //     std::ifstream ifs("output.json");
        //     if (ifs.good()) {
        //         rlf::Json j = rlf::Json::parse(ifs);
        //         rootNode->deserialize(j);
        //     }
        // }

        BeginDrawing();
        ClearBackground(BLACK);

        rootNode->update();
        renderSystem.render();

#ifdef RLF_DEBUG
        DrawFPS(10, 10);
#endif
        EndDrawing();
    }

    rootNode->shutdown();

    CloseWindow();
}

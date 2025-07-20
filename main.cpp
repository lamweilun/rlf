#include <Node/Node.hpp>

#include <System/TypeSystem.hpp>
#include <System/RenderSystem.hpp>
#include <System/PhysicsSystem.hpp>

#include <Util/Accessor/JsonDeserializer.hpp>
#include <Util/Accessor/JsonSerializer.hpp>

#include <fstream>

int main() {
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_WINDOW_HIGHDPI);
    InitWindow(1280, 720, "Hello rlf");
    // ToggleFullscreen();

    rlf::TypeSystem::getInstance();
    auto& renderSystem = rlf::RenderSystem::getInstance();
    rlf::PhysicsSystem::getInstance();

    // DO NOT CHANGE THIS
    auto rootNode = std::make_shared<rlf::BaseNode>();

    auto playerNode = rootNode->addChild<rlf::PlayerNode>();
    playerNode->setPosition(Vector3{640, 600, 0});

    auto enemy1 = rootNode->addChild<rlf::EnemyNode>();
    enemy1->setPosition(Vector3{640, 360, 0});

    rootNode->init();

    while (!WindowShouldClose()) {
        if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_O)) {
            rlf::Json     j = rootNode->serialize();
            std::ofstream ofs("output.json");
            ofs << j.dump(2);
        } else if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_I)) {
            std::ifstream ifs("output.json");
            if (ifs.good()) {
                rlf::Json j = rlf::Json::parse(ifs);
                rootNode->deserialize(j);
            }
        }

        rootNode->update();

        BeginDrawing();
        ClearBackground(BLACK);

        renderSystem.render();

        DrawFPS(10, 10);
        EndDrawing();
    }

    rootNode->shutdown();

    CloseWindow();
}

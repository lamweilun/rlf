#pragma once

#include <System/ISystem.hpp>

namespace rlf::System {
    class EditorSystem : public ISystem {
    public:
        void init() override;
        void render() override;
        void shutdown() override;

    private:
        void displayHierarchyWindow();
    };
}

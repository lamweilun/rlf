#pragma once

namespace rlf {
    namespace System {
        class ResourceSystem;
    }
#ifdef RLF_EDITOR
    namespace acc {
        class ImGuiAccessor;
    }
#endif

    class IResource {
    public:
        std::string const& getFilePath() const;

    private:
        std::string mFilePath;
        friend class rlf::System::ResourceSystem;
#ifdef RLF_EDITOR
        friend class rlf::acc::ImGuiAccessor;
#endif
    };
}

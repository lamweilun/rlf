#pragma once

namespace rlf
{
    class ResourceSystem;
#ifdef RLF_EDITOR
    namespace acc
    {
        class ImGuiAccessor;
    }
#endif

    class IResource
    {
    public:
        std::string const& getFilePath() const;

    protected:
        void setFilePath(std::string const& filePath);

    private:
        std::string mFilePath;
        friend class rlf::ResourceSystem;
#ifdef RLF_EDITOR
        friend class rlf::acc::ImGuiAccessor;
#endif
    };
}

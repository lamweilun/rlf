#pragma once

namespace rlf {
    namespace System {
        class ResourceSystem;
    }

    class IResource {
    public:
        void               setFilePath(std::string const& filePath);
        std::string const& getFilePath() const;

    private:
        std::string mFilePath;

        friend class rlf::System::ResourceSystem;
    };
}

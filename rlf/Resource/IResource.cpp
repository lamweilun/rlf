#include <Resource/IResource.hpp>

namespace rlf {
    void IResource::setFilePath(std::string const& filePath) {
        mFilePath = filePath;
    }

    std::string const& IResource::getFilePath() const {
        return mFilePath;
    }
}

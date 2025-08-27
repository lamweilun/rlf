#include <Resource/IResource.hpp>

namespace rlf {
    std::string const& IResource::getFilePath() const {
        return mFilePath;
    }
    void IResource::setFilePath(std::string const& filePath) {
        mFilePath = filePath;
    }
}

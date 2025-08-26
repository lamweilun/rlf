#include <Resource/IResource.hpp>

namespace rlf {
    std::string const& IResource::getFilePath() const {
        return mFilePath;
    }
}

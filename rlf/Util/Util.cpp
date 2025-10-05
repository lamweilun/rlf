#include <Util/Util.hpp>

#include <sstream>

namespace rlf {
    std::string getAddressAsString(void* addr) {
        std::stringstream ss;
        ss << addr;
        return ss.str();
    }
}

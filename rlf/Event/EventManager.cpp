#include <Event/EventManager.hpp>

namespace rlf::Event {
    EventManager& EventManager::getInstance() {
        static EventManager em;
        return em;
    }
}

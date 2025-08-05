#pragma once

#include <Node/BaseNode.hpp>

namespace rlf::Node {
    template <class T>
    std::shared_ptr<T> BaseNode::addChild() {
        return std::static_pointer_cast<T>(addChild(T::getTypeName()));
    }

    template <class T>
    std::optional<std::shared_ptr<T>> BaseNode::getFirstChildOfType() const {
        auto child = getFirstChildOfType(T::getTypeName());
        if (!child.has_value()) {
            return std::nullopt;
        }
        return std::static_pointer_cast<T>(child.value());
    }

    template <class T>
    std::shared_ptr<T> BaseNode::getOrAddFirstChildOfType() {
        return std::static_pointer_cast<T>(getOrAddFirstChildOfType(T::getTypeName()));
    }
}

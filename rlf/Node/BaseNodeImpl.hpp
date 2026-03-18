#pragma once

#include <Node/BaseNode.hpp>

namespace rlf::Node {
    template <class T>
    T* BaseNode::addChild() {
        return std::static_pointer_cast<T>(addChild(T::getTypeName()));
    }

    template <class T>
    std::optional<T*> BaseNode::getFirstChildOfType() const {
        auto child = getFirstChildOfType(T::getTypeName());
        if (!child.has_value()) {
            return std::nullopt;
        }
        return std::static_pointer_cast<T>(child.value());
    }

    template <class T>
    T* BaseNode::addOrGetFirstChildOfType() {
        return std::static_pointer_cast<T>(addOrGetFirstChildOfType(T::getTypeName()));
    }

    template <class T>
    std::optional<T*> BaseNode::getFirstChildOfName(std::string_view childName) const {
        auto children = getChildren();
        for (auto child : children) {
            if (child->getName() == childName) {
                return std::static_pointer_cast<T>(child);
            }
        }
        return std::nullopt;
    }

    template <class T>
    bool BaseNode::is() {
        return dynamic_cast<T*>(this) != nullptr;
    }

    template <class T>
    T* BaseNode::as() {
        return static_cast<T*>(this);
    }

    template <class T>
    T* BaseNode::as() const {
        return static_cast<T*>(this);
    }
}

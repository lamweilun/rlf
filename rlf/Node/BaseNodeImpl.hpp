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
    std::shared_ptr<T> BaseNode::addOrGetFirstChildOfType() {
        return std::static_pointer_cast<T>(addOrGetFirstChildOfType(T::getTypeName()));
    }

    template <class T>
    std::optional<std::shared_ptr<T>> BaseNode::getFirstChildOfName(std::string_view childName) const {
        auto children = getChildren();
        for (auto child : children) {
            if (child->getName() == childName) {
                return std::static_pointer_cast<T>(child);
            }
        }
        return std::nullopt;
    }

    template <class T>
    std::shared_ptr<T> BaseNode::as() {
        return std::static_pointer_cast<T>(shared_from_this());
    }

    template <class T>
    std::shared_ptr<T> BaseNode::as() const {
        return std::static_pointer_cast<T>(shared_from_this());
    }
}

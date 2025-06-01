#pragma once

#include <variant>

namespace rlf {

    class NodeBase;
    class RigidbodyNode;
    class PlayerNode;
    class PlayerBulletNode;

    using Node = std::variant<
        rlf::NodeBase,
        rlf::RigidbodyNode,
        rlf::PlayerNode,
        rlf::PlayerBulletNode>;
}

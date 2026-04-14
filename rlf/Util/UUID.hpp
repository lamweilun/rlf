#pragma once

#include <boost/uuid.hpp>

namespace rlf
{
    using UUID = boost::uuids::uuid;

    UUID generateUUID();
}

void to_json(rlf::Json& j, rlf::UUID const& id);
void from_json(rlf::Json const& j, rlf::UUID& id);

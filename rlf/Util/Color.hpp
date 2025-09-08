#pragma once

#include <iostream>

std::ostream& operator<<(std::ostream& os, Color color);
void          to_json(rlf::Json& j, Color const& v);
void          from_json(rlf::Json const& j, Color& v);

bool operator==(Color const& lhs, Color const& rhs);
bool operator!=(Color const& lhs, Color const& rhs);

#pragma once

#include <iostream>

std::ostream& operator<<(std::ostream& os, Vector2 const& v2);
std::ostream& operator<<(std::ostream& os, Vector3 const& v3);
std::ostream& operator<<(std::ostream& os, Vector4 const& v4);

void to_json(rlf::Json& j, Vector2 const& v2);
void to_json(rlf::Json& j, Vector3 const& v3);
void to_json(rlf::Json& j, Vector4 const& v4);

void from_json(rlf::Json const& j, Vector2& v2);
void from_json(rlf::Json const& j, Vector3& v3);
void from_json(rlf::Json const& j, Vector4& v4);

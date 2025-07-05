#pragma once

#include <iostream>

std::ostream& operator<<(std::ostream& os, Vector2 const& v);
std::ostream& operator<<(std::ostream& os, Vector3 const& v);
std::ostream& operator<<(std::ostream& os, Vector4 const& v);

void to_json(rlf::Json& j, Vector2 const& v);
void to_json(rlf::Json& j, Vector3 const& v);
void to_json(rlf::Json& j, Vector4 const& v);

void from_json(rlf::Json const& j, Vector2& v);
void from_json(rlf::Json const& j, Vector3& v);
void from_json(rlf::Json const& j, Vector4& v);

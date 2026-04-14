#include <Util/UUID.hpp>

namespace rlf
{
    UUID generateUUID()
    {
        return boost::uuids::random_generator()();
    }
}

void to_json(rlf::Json& j, rlf::UUID const& id)
{
    j = boost::uuids::to_string(id);
}
void from_json(rlf::Json const& j, rlf::UUID& id)
{
    std::string                    id_string = j.get<std::string>();
    boost::uuids::string_generator gen;
    id = gen(id_string);
}

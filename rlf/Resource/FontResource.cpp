#include <Resource/FontResource.hpp>

#include <Engine/Engine.hpp>
#include <System/Resource/ResourceSystem.hpp>

namespace rlf
{
    void FontResource::setFont(std::shared_ptr<Font> font)
    {
        mFont = font;
    }

    std::shared_ptr<Font> FontResource::getFont() const
    {
        return mFont;
    }

    void to_json(rlf::Json& j, rlf::FontResource const& rsc)
    {
        j = rsc.getFilePath();
    }

    void from_json(rlf::Json const& j, rlf::FontResource& rsc)
    {
        std::string filePath = j.get<std::string>();
        rsc                  = rlf::Engine::getInstance().getSystem<rlf::ResourceSystem>()->getFontResource(filePath);
    }
}

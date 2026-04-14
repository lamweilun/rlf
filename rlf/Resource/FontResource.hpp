#pragma once

#include <Resource/IResource.hpp>

namespace rlf
{
    class FontResource : public IResource
    {
    public:
        void                  setFont(std::shared_ptr<Font> font);
        std::shared_ptr<Font> getFont() const;

    private:
        std::shared_ptr<Font> mFont;

        friend void to_json(rlf::Json& j, rlf::FontResource const& rsc);
        friend void from_json(rlf::Json const& j, rlf::FontResource& rsc);
    };
}

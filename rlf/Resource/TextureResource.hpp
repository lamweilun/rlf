#pragma once

#include <Resource/IResource.hpp>

namespace rlf {
    class TextureResource : public IResource {
    public:
        void                     setTexture(std::weak_ptr<::Texture> texture);
        std::weak_ptr<::Texture> getTexture() const;

    private:
        std::weak_ptr<::Texture> mTexture;

        friend void to_json(rlf::Json& j, rlf::TextureResource const& rsc);
        friend void from_json(rlf::Json const& j, rlf::TextureResource& rsc);
    };
}

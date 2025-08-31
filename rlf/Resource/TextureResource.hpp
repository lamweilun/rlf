#pragma once

#include <Resource/IResource.hpp>

namespace rlf {
    class TextureResource : public IResource {
    public:
        void                       setTexture(std::shared_ptr<::Texture> texture);
        std::shared_ptr<::Texture> getTexture() const;

        u32 getWidth() const;
        u32 getHeight() const;

    private:
        std::shared_ptr<::Texture> mTexture;

        friend void to_json(rlf::Json& j, rlf::TextureResource const& rsc);
        friend void from_json(rlf::Json const& j, rlf::TextureResource& rsc);
    };
}

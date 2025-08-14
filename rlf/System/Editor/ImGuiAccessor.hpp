#pragma once

#include <imgui.h>
#include <string_view>

#include <Util/Range.hpp>

namespace rlf::acc {
    class ImGuiAccessor {
    public:
        template <class T>
        void operator()(std::string_view name, T& t) {
            T temp = t;
            if constexpr (std::is_same_v<T, bool>) {
                ImGui::Checkbox(name.data(), &temp);
            } else if constexpr (std::is_same_v<T, f32>) {
                ImGui::DragFloat(name.data(), &temp);
            } else if constexpr (std::is_same_v<T, Vector2>) {
                ImGui::DragFloat2(name.data(), &temp.x);
            } else if constexpr (std::is_same_v<T, Vector3>) {
                ImGui::DragFloat3(name.data(), &temp.x);
            } else if constexpr (std::is_same_v<T, Vector4>) {
                ImGui::DragFloat4(name.data(), &temp.x);
            } else if constexpr (std::is_same_v<T, Color>) {
                std::array<int, 4> col{temp.r, temp.g, temp.b, temp.a};
                ImGui::DragInt4(name.data(), &col[0], 1.0f, 0, 255);
                temp.r = static_cast<unsigned char>(col[0]);
                temp.g = static_cast<unsigned char>(col[1]);
                temp.b = static_cast<unsigned char>(col[2]);
                temp.a = static_cast<unsigned char>(col[3]);
            } else if constexpr (std::is_same_v<T, std::string>) {
                char buffer[512];
                strcpy(buffer, temp.data());
                ImGui::InputText(name.data(), buffer, std::size(buffer));
                temp = buffer;
            }
            t = temp;
        }

        template <class T>
        void operator()(std::string_view name, rlf::Range<T>& t) {
            auto tempMin = t.getMin();
            auto tempMax = t.getMax();
            (*this)(std::string(name) + " min", tempMin);
            (*this)(std::string(name) + " max", tempMax);
            t.setMin(tempMin);
            t.setMax(tempMax);
        }

        // Non-const getter
        template <class T, class M>
        void operator()(std::string_view name,
                        M (T::*getter)(),
                        void (T::*setter)(M),
                        T& instance) {
            using MemberType = std::decay_t<M>;
            MemberType temp  = (instance.*getter)();
            (*this)(name, temp);
            (instance.*setter)(temp);
        }

        // Const getter
        template <class T, class M>
        void operator()(std::string_view name,
                        M (T::*getter)() const,
                        void (T::*setter)(M),
                        T& instance) {
            using MemberType = std::decay_t<M>;
            MemberType temp  = (instance.*getter)();
            (*this)(name, temp);
            (instance.*setter)(temp);
        }

    private:
    };
}

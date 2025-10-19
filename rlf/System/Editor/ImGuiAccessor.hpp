#pragma once

#include <imgui.h>

#include <Util/Range.hpp>

#include <Resource/TextureResource.hpp>
#include <Resource/SoundResource.hpp>
#include <Resource/FontResource.hpp>

#include <Engine/Engine.hpp>
#include <System/Resource/ResourceSystem.hpp>
#include <System/Editor/EditorSystem.hpp>

#include <string_view>
#include <sstream>
#include <set>
#include <tuple>

namespace rlf::acc {
    class ImGuiAccessor {
    public:
        template <class T>
        void operator()(std::string_view name, T& t) {
            T temp = t;
            if constexpr (std::is_same_v<T, bool>) {
                ImGui::Checkbox(name.data(), &temp);
            } else if constexpr (std::is_same_v<T, i8>) {
                ImGui::DragScalar(name.data(), ImGuiDataType_S8, &temp, 1.0f);
            } else if constexpr (std::is_same_v<T, i16>) {
                ImGui::DragScalar(name.data(), ImGuiDataType_S16, &temp, 1.0f);
            } else if constexpr (std::is_same_v<T, i32>) {
                ImGui::DragScalar(name.data(), ImGuiDataType_S32, &temp, 1.0f);
            } else if constexpr (std::is_same_v<T, i64>) {
                ImGui::DragScalar(name.data(), ImGuiDataType_S64, &temp, 1.0f);
            } else if constexpr (std::is_same_v<T, u8>) {
                ImGui::DragScalar(name.data(), ImGuiDataType_U8, &temp, 1.0f);
            } else if constexpr (std::is_same_v<T, u16>) {
                ImGui::DragScalar(name.data(), ImGuiDataType_U16, &temp, 1.0f);
            } else if constexpr (std::is_same_v<T, u32>) {
                ImGui::DragScalar(name.data(), ImGuiDataType_U32, &temp, 1.0f);
            } else if constexpr (std::is_same_v<T, u64>) {
                ImGui::DragScalar(name.data(), ImGuiDataType_U64, &temp, 1.0f);
            } else if constexpr (std::is_same_v<T, f32>) {
                ImGui::DragScalar(name.data(), ImGuiDataType_Float, &temp, 1.0f);
            } else if constexpr (std::is_same_v<T, f64>) {
                ImGui::DragScalar(name.data(), ImGuiDataType_Double, &temp, 1.0f);
            } else if constexpr (std::is_same_v<T, Vector2>) {
                ImGui::DragFloat2(name.data(), &temp.x);
            } else if constexpr (std::is_same_v<T, Vector3>) {
                ImGui::DragFloat3(name.data(), &temp.x);
            } else if constexpr (std::is_same_v<T, Vector4>) {
                ImGui::DragFloat4(name.data(), &temp.x);
            } else if constexpr (std::is_same_v<T, Color>) {
                auto col = Color4F::FromColor(temp);
                (*this)(name, col);
                temp = col.ToColor();
            } else if constexpr (std::is_same_v<T, Color4F>) {
                ImGui::ColorEdit4(name.data(), &temp.r);
            } else if constexpr (std::is_same_v<T, std::string>) {
                char buffer[512];
                strcpy(buffer, temp.data());
                ImGui::InputText(name.data(), buffer, std::size(buffer));
                temp = buffer;
            } else if constexpr (std::is_base_of_v<IResource, T>) {
                ImGui::LabelText(name.data(), "%s", temp.getFilePath().c_str());
                if (ImGui::BeginDragDropTarget()) {
                    if (ImGui::AcceptDragDropPayload("DragFromFileBrowser")) {
                        auto       editorSys   = rlf::Engine::getInstance().getSystem<System::EditorSystem>();
                        auto       resourceSys = rlf::Engine::getInstance().getSystem<System::ResourceSystem>();
                        auto const filepath    = editorSys->getDraggedFilePath();
                        if constexpr (std::is_same_v<T, TextureResource>) {
                            temp = resourceSys->getTextureResource(filepath);
                        } else if constexpr (std::is_same_v<T, SoundResource>) {
                            temp = resourceSys->getSoundResource(filepath);
                        } else if constexpr (std::is_same_v<T, FontResource>) {
                            temp = resourceSys->getFontResource(filepath);
                        }
                        temp.mFilePath = filepath;
                    }
                    ImGui::EndDragDropTarget();
                }
                ImGui::SameLine();
                std::stringstream ss;
                ss << &temp;
                std::string closeBtn = std::string("X##") + ss.str();
                if (ImGui::Button(closeBtn.c_str())) {
                    T newTemp;
                    std::swap(temp, newTemp);
                }
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

        // std::pair support
        template <class T1, class T2>
        void operator()(std::string_view name, std::pair<T1, T2>& p) {
            auto const childName = std::string(name) + "##" + getAddressAsString(&p);
            ImGui::BeginChild(childName.c_str(), ImVec2(0, 0), ImGuiChildFlags_Borders | ImGuiChildFlags_AutoResizeY);
            ImGui::Text("%s", name.data());
            auto const firstName  = std::string(name.data()) + std::string("first##") + getAddressAsString(&p.first);
            auto const secondName = std::string(name.data()) + std::string("second##") + getAddressAsString(&p.second);
            (*this)(firstName, p.first);
            (*this)(secondName, p.second);
            ImGui::EndChild();
        }

        // std::tuple support
        template <class... Ts>
        void operator()(std::string_view name, std::tuple<Ts...>& tup) {
            auto const childName = std::string(name) + "##" + getAddressAsString(&tup);
            ImGui::BeginChild(childName.c_str(), ImVec2(0, 0), ImGuiChildFlags_Borders | ImGuiChildFlags_AutoResizeY);
            ImGui::Text("%s", name.data());
            std::apply([this, name](Ts&... t) {
                size_t i = 0;
                ((*this)(std::string(name.data()) + ' ' + std::to_string(i++) + "##" + getAddressAsString(&t), t), ...);
            },
                       tup);
            ImGui::EndChild();
        }

        // std::array Support
        template <class T, size_t N>
        void operator()(std::string_view name, std::array<T, N>& arr) {
            if (ImGui::CollapsingHeader(name.data(), ImGuiTreeNodeFlags_DefaultOpen)) {
                for (size_t i = 0; i < N; ++i) {
                    std::string indexedName = std::string(name) + ' ' + std::to_string(i);
                    (*this)(indexedName, arr[i]);
                }
            }
        }

        // std::vector support
        template <class T>
        void operator()(std::string_view name, std::vector<T>& vec) {
            if (ImGui::CollapsingHeader(name.data(), ImGuiTreeNodeFlags_DefaultOpen)) {
                for (u32 i = 0; i < vec.size(); ++i) {
                    std::string indexedName = std::string(name) + ' ' + std::to_string(i);
                    (*this)(indexedName, vec[i]);

                    ImGui::SameLine();

                    auto const removeEntryButton = std::string("-##") + getAddressAsString(&vec[i]);
                    if (ImGui::Button(removeEntryButton.c_str())) {
                        auto itr = std::begin(vec);
                        std::advance(itr, i);
                        vec.erase(itr);
                        break;
                    }
                }
                {
                    auto const addVecButton = std::string("+##") + getAddressAsString(&vec);
                    if (ImGui::Button(addVecButton.c_str())) {
                        vec.emplace_back();
                    }
                }
            }
        }

        // std::set support
        template <class T>
        void operator()(std::string_view name, std::set<T>& s) {
            std::vector vec(std::begin(s), std::end(s));
            (*this)(name, vec);
            s = std::set(std::begin(vec), std::end(vec));
        }

        // std::map support
        template <class K, class T>
        void operator()(std::string_view name, std::map<K, T>& m) {
            std::vector<std::pair<K, T>> vec;
            vec.reserve(m.size());
            for (auto const& [key, val] : m) {
                vec.push_back({key, val});
            }
            (*this)(name, vec);
            m.clear();
            for (auto const& v : vec) {
                m.insert({v.first, v.second});
            }
        }

    private:
    };
}

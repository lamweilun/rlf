#pragma once

#include <random>

namespace rlf {

    namespace impl {
        template <class T>
        class RangeBase {
        public:
            RangeBase(T const& min = {}, T const& max = {}) : mMin{min}, mMax{max} {
            }
            ~RangeBase()                           = default;
            RangeBase(RangeBase const&)            = default;
            RangeBase(RangeBase&&)                 = default;
            RangeBase& operator=(RangeBase const&) = default;
            RangeBase& operator=(RangeBase&&)      = default;

            void setMin(T const& t) {
                mMin = t;
            }
            T const& getMin() const {
                return mMin;
            }

            void setMax(T const& t) {
                mMax = t;
            }
            T const& getMax() const {
                return mMax;
            }

        private:
            T mMin = {};
            T mMax = {};
        };
    }
    template <class T>
    class Range : public impl::RangeBase<T> {
    public:
        Range(T const& min = {}, T const& max = {}) : impl::RangeBase<T>(min, max) {
        }
        ~Range()                       = default;
        Range(Range const&)            = default;
        Range(Range&&)                 = default;
        Range& operator=(Range const&) = default;
        Range& operator=(Range&&)      = default;

        T getValue() const {
            if constexpr (std::is_integral_v<T>) {
                std::random_device               rd;
                std::mt19937                     gen(rd());
                std::uniform_int_distribution<T> dist(impl::RangeBase<T>::getMin(), impl::RangeBase<T>::getMax());
                return dist(gen);
            } else if constexpr (std::is_floating_point_v<T>) {
                std::random_device                rd;
                std::mt19937                      gen(rd());
                std::uniform_real_distribution<T> dist(impl::RangeBase<T>::getMin(), impl::RangeBase<T>::getMax());
                return dist(gen);
            } else if constexpr (std::is_same_v<Vector2, T>) {
                Vector2     value;
                auto const& minVal = impl::RangeBase<T>::getMin();
                auto const& maxVal = impl::RangeBase<T>::getMax();
                value.x            = Range<f32>(minVal.x, maxVal.x).getValue();
                value.y            = Range<f32>(minVal.y, maxVal.y).getValue();
                return value;
            } else if constexpr (std::is_same_v<Vector3, T>) {
                Vector3     value;
                auto const& minVal = impl::RangeBase<T>::getMin();
                auto const& maxVal = impl::RangeBase<T>::getMax();
                value.x            = Range<f32>(minVal.x, maxVal.x).getValue();
                value.y            = Range<f32>(minVal.y, maxVal.y).getValue();
                value.z            = Range<f32>(minVal.z, maxVal.z).getValue();
                return value;
            } else if constexpr (std::is_same_v<Vector4, T>) {
                Vector4     value;
                auto const& minVal = impl::RangeBase<T>::getMin();
                auto const& maxVal = impl::RangeBase<T>::getMax();
                value.x            = Range<f32>(minVal.x, maxVal.x).getValue();
                value.y            = Range<f32>(minVal.y, maxVal.y).getValue();
                value.z            = Range<f32>(minVal.z, maxVal.z).getValue();
                value.w            = Range<f32>(minVal.w, maxVal.w).getValue();
                return value;
            }
            return T{};
        }

        friend void to_json(rlf::Json& j, Range<T> const& t) {
            j["min"] = t.getMin();
            j["max"] = t.getMax();
        }

        friend void from_json(rlf::Json const& j, Range<T>& t) {
            t.setMin(j["min"]);
            t.setMax(j["max"]);
        }
    };
}

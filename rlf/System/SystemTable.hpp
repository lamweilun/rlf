#pragma once

#include <vector>
#include <unordered_map>

namespace rlf::System
{
    template <class T>
    class Table
    {
    public:
        void insert(T p)
        {
            if (mIndexLookup.contains(p))
            {
                return;
            }
            mIndexLookup[p] = mData.size();
            mData.push_back(p);
        }

        void erase(T p)
        {
            auto itr = mIndexLookup.find(p);
            if (itr == mIndexLookup.end())
            {
                return;
            }
            auto const index = itr->second;
            if (index == mData.size() - 1)
            {
                mIndexLookup.erase(itr);
                mData.pop_back();
                return;
            }

            std::swap(mData[index], mData.back());
            mData.pop_back();

            mIndexLookup.erase(itr);
            mIndexLookup[mData[index]] = index;
        }

        auto size() const
        {
            return mData.size();
        }

        auto begin() const
        {
            return std::begin(mData);
        }
        auto end() const
        {
            return std::end(mData);
        }

    private:
        std::vector<T>             mData;
        std::unordered_map<T, u64> mIndexLookup;
    };
}

#pragma once

#include <deque>

template<class T, class Comp>
std::deque<T> Merge(const std::deque<T>& half1, const std::deque<T>& half2, const Comp& comparator) {
        std::deque<T> result;
        auto it1 = half1.begin();
        auto it2 = half2.begin();
        const auto end1 = half1.end();
        const auto end2 = half2.end();

        while(it1 != end1&& it2 != end2) {
            if (comparator(*it1, *it2)) {
                result.push_back(*it1);
                ++it1;
            } else {
                result.push_back(*it2);
                ++it2;
            }
        }

        std::copy(it1,end1,std::back_inserter(result));
        std::copy(it2,end2,std::back_inserter(result));
        return result;
}

template<class T, class Comp>
std::deque<T> MergeSort(const std::deque<T>& src, const Comp& comparator) {
    if (src.size() <= 1) {
        return src;
    }

    const size_t mid = src.size() / 2;
    const std::deque<T> left_sorted = MergeSort(std::deque(src.begin(),src.begin()+mid), comparator);
    const std::deque<T> right_sorted = MergeSort(std::deque(src.begin()+mid,src.end()), comparator);
    return Merge(left_sorted, right_sorted,comparator);
}

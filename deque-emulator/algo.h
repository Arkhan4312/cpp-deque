#pragma once

#include <deque>

template<class T, class Comp>
std::deque<T> Merge(const std::deque<T>& half1, const std::deque<T>& half2, const Comp& comparator) {
        std::deque<T> result;
        size_t i = 0;
        size_t j = 0;

        while(i < half1.size()&& j < half2.size()) {
            if (comparator(half1[i], half2[j])) {
                result.push_back(half1[i]);
                ++i;
            } else {
                result.push_back(half2[j]);
                ++j;
            }
        }

        while (i < half1.size()) {
            result.push_back(half1[i]);
            ++i;
        }

        while (j < half2.size()) {
            result.push_back(half2[j]);
            ++j;
        }

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

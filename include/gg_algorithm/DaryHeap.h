// Copyright (c) 2022 shr-go. All rights reserved.
// Author: shr-go
#ifndef GGALGORITHM_DARYHEAP_H
#define GGALGORITHM_DARYHEAP_H

#include <vector>
#include <functional>
#include <stdexcept>

namespace gg_algorithm {

    template<typename T, int N, typename Container = std::vector<T>, typename Compare = std::less<typename Container::value_type>>
    class DaryHeap {
        typedef typename Container::size_type size_type;
        typedef typename Container::value_type value_type;
        typedef typename Container::const_reference const_reference;

    public:
        DaryHeap() = default;

        explicit DaryHeap(Compare comparator) : comparator_(comparator) {}

        const_reference top() const {
            if (empty())
                throw std::out_of_range("Container is empty");
            return container_.front();
        }

        bool empty() const {
            return container_.empty();
        }

        size_type size() {
            return container_.size();
        }

        void push(const value_type &value) {
            size_type index = container_.size();
            container_.push_back(value);
            up(index);
        }

        void push(value_type &&value) {
            size_type index = container_.size();
            container_.push_back(std::move(value));
            up(index);
        }

        template<class... Args>
        void emplace(Args &&... args) {
            size_type index = container_.size();
            container_.emplace_back(std::forward<Args>(args)...);
            up(index);
        }

        void pop() {
            if (empty())
                throw std::out_of_range("Container is empty");
            if (container_.size() > 1)
                std::swap(container_.front(), container_.back());
            container_.pop_back();
            if (!empty())
                down(0);
        }

        void swap(DaryHeap &other) {
            std::swap(container_, other.container_);
            std::swap(comparator_, other.comparator_);
        }

        void reserve(size_t number) {
            container_.reserve(number);
        }

        void clear() noexcept {
            container_.clear();
        }

        Container &container() {
            return container_;
        }

    private:
        Container container_;
        Compare comparator_;

        size_type parent(size_type index) {
            return (index - 1) / N;
        }

        size_type firstChild(size_type index) {
            return (index * N) + 1;
        }

        size_type lastChild(size_type index) {
            return (index + 1) * N;
        }

        void up(size_type index) {
            while (index > 0) {
                size_type parent_index = parent(index);
                if (comparator_(container_[parent_index], container_[index]))
                    break;
                std::swap(container_[index], container_[parent_index]);
                index = parent_index;
            }
        }

        void down(size_type index) {
            size_type size = container_.size();
            for (;;) {
                size_type first_child_index = firstChild(index);
                if (first_child_index >= size)
                    break;
                size_type cur_index = first_child_index;
                size_type last_child_index = lastChild(index);
                for (size_type i = first_child_index + 1; i <= last_child_index && i < size; ++i) {
                    if (comparator_(container_[i], container_[cur_index])) {
                        cur_index = i;
                    }
                }
                if (!comparator_(container_[cur_index], container_[index])) {
                    break;
                }
                std::swap(container_[index], container_[cur_index]);
                index = cur_index;
            }
        }
    };

}

#endif //GGALGORITHM_DARYHEAP_H

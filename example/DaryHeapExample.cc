// Copyright (c) 2022 shr-go. All rights reserved.
// Author: shr-go

#include "gg_algorithm/DaryHeap.h"
#include <iostream>

int main() {
    gg_algorithm::DaryHeap<int, 4> heap;
    heap.push(0);
    std::cout << heap.top() << std::endl;
    for (int i = 1; i <= 10; ++i) {
        heap.push(i);
    }
    std::cout << heap.top() << std::endl;
    while (!heap.empty()) {
        std::cout << heap.top() << std::endl;
        heap.pop();
    }
}

#include "sort.h"
#include <iostream>
#include <algorithm>

void BSort::sort(std::vector<std::string>& names) {
    std::cout << ">> [BSort] 시스템 안정 모드 버블 정렬 실행" << std::endl;
    int n = names.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (names[j] > names[j + 1]) std::swap(names[j], names[j + 1]);
        }
    }
}
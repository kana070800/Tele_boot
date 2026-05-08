#include "sort.h"
#include <iostream>
#include <algorithm>


void QSort::sort(std::vector<std::string>& names) {
    std::cout << ">> [QSort] 파일 시스템 고속 정렬 실행" << std::endl;
    std::sort(names.begin(), names.end());
}
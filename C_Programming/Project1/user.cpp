#include "user.h"
#include <iostream>

User::User() : strategy(nullptr) {}
User::~User() = default;

void User::setSortStrategy(std::unique_ptr<SortInterface> newStrategy) {
    strategy = std::move(newStrategy);
}

void User::Sort(std::vector<std::string>& data) {
    if (strategy) {
        strategy->sort(data);
    }
    else {
        std::cout << "정렬 전략이 설정되지 않았습니다." << std::endl;
    }
}//
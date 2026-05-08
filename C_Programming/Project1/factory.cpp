#include "sort.h"
#include "factory.h"
#include <iostream>

// 팩토리 구현부 (보통 별도 파일이나 하나에 몰아넣음)
std::unique_ptr<SortInterface> SortFactory::createSort(Type type) {
    if (type == Type::Quick) return std::make_unique<QSort>();
    if (type == Type::Bubble) return std::make_unique<BSort>();
    return nullptr;
}
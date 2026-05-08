#pragma once
#include "interface.h"
#include <memory>

class SortFactory {
public:
    enum class Type { Quick, Bubble };
    static std::unique_ptr<SortInterface> createSort(Type type);
};
#ifndef SORT_H
#define SORT_H

#include "interface.h"

// 퀵 정렬 클래스 선언
class QSort : public SortInterface {
public:
    void sort(std::vector<std::string>& names) override;
};

// 버블 정렬 클래스 선언
class BSort : public SortInterface {
public:
    void sort(std::vector<std::string>& names) override;
};

#endif
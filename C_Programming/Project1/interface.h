#ifndef _INTERFACE_H
#define _INTERFACE_H

#include <vector>
#include <string>

// 추상 클래스: 정렬의 규칙만 정함
class SortInterface {
public:
    virtual ~SortInterface() {}
    virtual void sort(std::vector<std::string>& names) = 0;
};

#endif
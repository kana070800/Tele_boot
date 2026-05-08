#ifndef USER_H
#define USER_H

#include <memory>
#include <vector>
#include <string>
#include "interface.h"

class User {
private:
    std::unique_ptr<SortInterface> strategy;

public:
    User();
    ~User();
    void setSortStrategy(std::unique_ptr<SortInterface> newStrategy);
    void Sort(std::vector<std::string>& data);
};

#endif
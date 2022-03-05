#pragma once
#include <utility>
#include <stdexcept>
#include <iostream>

struct PQNode
{
    int value = 0;
    PQNode *next = nullptr;
};
enum class Priority
{
    Low,
    Medium,
    High
};
class Pr_queue
{
private:
    PQNode *front;
    PQNode *rear_high;
    unsigned high_cnt;
    PQNode *rear_medium;
    unsigned medium_cnt;
    PQNode *rear_low;
    unsigned low_cnt;
    void copy_pointers(Pr_queue &&);
    void copy_values(const Pr_queue &); 
    void nulify(); 
    void erase(); 
public:
    Pr_queue();
    Pr_queue(const Pr_queue &);
    Pr_queue(Pr_queue &&);
    Pr_queue& operator=(const Pr_queue&);
    Pr_queue& operator=(Pr_queue&&);
    unsigned size() const;
    unsigned size_medium_priority() const;
    unsigned size_high_priority() const;
    unsigned size_low_priority() const;
    bool empty() const;
    void push(const int &, const Priority &);
    bool pop();
    std::pair<int, Priority> top() const;
    ~Pr_queue(); 
    friend std::ostream& operator<<(std::ostream&, const Pr_queue&);
};
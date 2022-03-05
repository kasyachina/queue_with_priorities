#include "pr_queue.h"

void Pr_queue::nulify()
{
    front = rear_high = rear_medium = rear_low = nullptr;
    high_cnt = medium_cnt = low_cnt = 0;
}
void Pr_queue::copy_pointers(Pr_queue &&q)
{
    front = q.front;
    rear_high = q.rear_high;
    rear_medium = q.rear_medium;
    rear_low = q.rear_low;

    high_cnt = q.high_cnt;
    medium_cnt = q.medium_cnt;
    low_cnt = q.low_cnt;
}
void Pr_queue::copy_values(const Pr_queue &q)
{
    nulify();
    unsigned cnt = 0;
    for (PQNode *ptr = q.front; ptr != nullptr; ptr = ptr->next, cnt++)
    {
        if (cnt < q.high_cnt)
        {
            push(ptr->value, Priority::High);
            continue;
        }
        if (cnt < q.high_cnt + q.medium_cnt)
        {
            push(ptr->value, Priority::Medium);
            continue;
        }
        if (cnt < q.size())
        {
            push(ptr->value, Priority::Low);
            continue;
        }
    }
}
Pr_queue::Pr_queue()
{
    nulify();
}
Pr_queue::Pr_queue(const Pr_queue &q)
{
    copy_values(q);
}
Pr_queue::Pr_queue(Pr_queue &&q)
{
    copy_pointers(std::move(q));
    q.nulify();
}
Pr_queue &Pr_queue::operator=(const Pr_queue &q)
{
    if (&q == this)
    {
        return *this;
    }
    erase();
    copy_values(q);
    return *this;
}
Pr_queue &Pr_queue::operator=(Pr_queue &&q)
{
    if (&q == this)
    {
        return *this;
    }
    copy_pointers(std::move(q));
    q.nulify();
    return *this;
}
unsigned Pr_queue::size() const
{
    return high_cnt + medium_cnt + low_cnt;
}
unsigned Pr_queue::size_high_priority() const
{
    return high_cnt;
}
unsigned Pr_queue::size_medium_priority() const
{
    return medium_cnt;
}
unsigned Pr_queue::size_low_priority() const
{
    return low_cnt;
}
bool Pr_queue::empty() const
{
    return (front == nullptr);
}
void Pr_queue::push(const int &value, const Priority &p)
{
    PQNode *n = new PQNode;
    n->value = value;
    if (p == Priority::High)
    {
        if (rear_high == nullptr)
        {
            n->next = front;
            front = n;
        }
        else
        {
            n->next = rear_high->next;
            rear_high->next = n;
        }
        high_cnt++;
        rear_high = n;
    }
    if (p == Priority::Medium)
    {
        if (rear_medium == nullptr)
        {
            if (rear_high == nullptr)
            {
                n->next = front;
                front = n;
            }
            else
            {
                n->next = rear_high->next;
                rear_high->next = n;
            }
        }
        else
        {
            n->next = rear_medium->next;
            rear_medium->next = n;
        }
        rear_medium = n;
        medium_cnt++;
    }
    if (p == Priority::Low)
    {
        if (rear_low == nullptr)
        {
            if (rear_medium == nullptr)
            {
                if (rear_high == nullptr)
                {
                    n->next = nullptr;
                    front = n;
                }
                else
                {
                    rear_high->next = n;
                }
            }
            else
            {
                rear_medium->next = n;
            }
        }
        else
        {
            n->next = rear_low->next;
            rear_low->next = n;
        }
        rear_low = n;
        low_cnt++;
    }
}
bool Pr_queue::pop()
{
    if (empty())
    {
        return 0;
    }
    if (front == rear_high)
    {
        rear_high = nullptr;
    }
    if (front == rear_medium)
    {
        rear_medium = nullptr;
    }
    if (front == rear_low)
    {
        rear_low = nullptr;
    }
    unsigned *a[3] = {&low_cnt, &medium_cnt, &high_cnt};
    (*a[static_cast<unsigned>(top().second)])--;
    PQNode *n = front;
    front = n->next;
    delete n;
    return 1;
}
std::pair<int, Priority> Pr_queue::top() const
{
    if (empty())
    {
        throw std::logic_error("Queue is empty");
    }
    Priority p;
    if (high_cnt != 0)
        p = Priority::High;
    else if (medium_cnt != 0)
        p = Priority::Medium;
    else if (low_cnt != 0)
        p = Priority::Low;
    return {front->value, p};
}
void Pr_queue::erase()
{
    PQNode *ptr = front;
    PQNode *ptr2;
    while (ptr != nullptr)
    {
        ptr2 = ptr;
        ptr = ptr2->next;
        delete ptr2;
    }
    nulify();
}
Pr_queue::~Pr_queue()
{
    erase();
}
std::ostream &operator<<(std::ostream &out, const Pr_queue &q)
{
    unsigned cnt = 0;
    PQNode *ptr = q.front;
    const unsigned *a[3] = {&q.high_cnt, &q.medium_cnt, &q.low_cnt};
    out << "[";
    for (unsigned flag = 0; flag < 3; ++flag)
    {
        out << "{";
        while (cnt < *a[flag])
        {
            if (cnt == 0)
                out << ptr->value;
            else
                out << ' ' << ptr->value;
            cnt++;
            ptr = ptr->next;
        }
        out << "}";
        cnt = 0;
    }
    return out << "]";
}
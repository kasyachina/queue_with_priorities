#include <iostream>
#include "pr_queue.h"
#include <string>

using namespace std;

ostream &operator<<(ostream &out, const pair<int, Priority> &p)
{
    string message[3] = {"low", "medium", "high"};
    return out << "(" << p.first << "," << message[static_cast<size_t>(p.second)] << ")";
}

int main()
{
    Priority h = Priority::High, m = Priority::Medium, l = Priority::Low;

    string message("Enter:\n"
                   "0 : To see menu\n"
                   "1 : To test constructors\n"
                   "2 : To test assignment operators\n"
                   "3 : To test number of elements of each priority\n"
                   "4 : To test emptiness\n"
                   "5 : To test push() method\n"
                   "6 : To test pop() method\n"
                   "7 : To test top() method\n");
    cout << message;
    int command;
    while (true)
    {
        cin >> command;
        if (command == 0)
        {
            cout << message;
        }
        else if (command == 1)
        {
            {
                Pr_queue q;
                cout << "Empty queue : " << q << endl
                     << endl;
            }
            {
                Pr_queue q1;
                q1.push(5, h);
                q1.push(3, l);
                q1.push(2, m);
                q1.push(7, h);
                cout << "Copying constructor : " << endl;
                cout << "q1 : " << q1 << endl;
                cout << "Pr_queue q2(q1)" << endl;
                Pr_queue q2(q1);
                cout << "q1 : " << q1 << endl;
                cout << "q2 : " << q2 << endl
                     << endl;
            }
            {
                Pr_queue q3;
                q3.push(5, h);
                q3.push(3, l);
                q3.push(2, m);
                q3.push(7, h);
                cout << "Moving constructor" << endl;
                cout << "q3 : " << q3 << endl;
                cout << "Pr_queue q4(std::move(q3))" << endl;
                Pr_queue q4(std::move(q3));
                cout << "q3 : " << q3 << endl;
                cout << "q4 : " << q4 << endl;
            }
        }
        else if (command == 2)
        {
            {
                Pr_queue q1, q2;
                q1.push(4, l);
                q1.push(1, h);
                q1.push(2, m);
                q1.push(3, m);
                cout << "Copying assignment operator" << endl;
                cout << "q1 : " << q1 << endl;
                cout << "q2 = q1" << endl;
                q2 = q1;
                cout << "q1 : " << q1 << endl;
                cout << "q2 : " << q2 << endl
                     << endl;
            }
            {
                Pr_queue q3, q4;
                q3.push(4, l);
                q3.push(1, h);
                q3.push(2, m);
                q3.push(3, m);
                cout << "Moving assignment operator" << endl;
                cout << "q3 : " << q3 << endl;
                cout << "q4 = std::move(q3)" << endl;
                q4 = std::move(q3);
                cout << "q3 : " << q3 << endl;
                cout << "q4 : " << q4 << endl;
            }
        }
        else if (command == 3)
        {
            Pr_queue q1;
            q1.push(7, m);
            q1.push(3, l);
            q1.push(1, h);
            q1.push(-1, l);
            cout << "q : " << q1 << endl;
            cout << "Number of high priority elements : " << q1.size_high_priority() << endl;
            cout << "Number of medium priority elements : " << q1.size_medium_priority() << endl;
            cout << "Number of low priority elements : " << q1.size_low_priority() << endl;
            cout << "Size : " << q1.size() << endl;
        }
        else if (command == 4)
        {
            cout << "Testing emptiness" << endl;
            Pr_queue q;
            cout << "q : " << q << endl;
            cout << "q.empty() = " << q.empty() << endl;
            q.push(4, m);
            cout << "q : " << q << endl;
            cout << "q.empty() = " << q.empty() << endl;
        }
        else if(command == 5)
        {
            cout << "Testing push() method" << endl;
            Pr_queue q;
            cout << "q : " << q << endl << endl;

            cout << "q.push(5, Medium)" << endl;
            q.push(5, m);
            cout << "q : " << q << endl << endl;

            cout << "q.push(2, High)" << endl;
            q.push(2, h);
            cout << "q : " << q << endl << endl;

            cout << "q.push(3, High)" << endl;
            q.push(3, h);
            cout << "q : " << q << endl << endl;

            cout << "q.push(2, Medium)" << endl;
            q.push(2, m);
            cout << "q : " << q << endl << endl;

            cout << "q.push(7, Low)" << endl;
            q.push(7, l);
            cout << "q : " << q << endl;
        }
        else if(command == 6)
        {
            cout << "Testing pop() method" << endl;
            Pr_queue q;
            q.push(2, l);
            q.push(7, l);
            q.push(1, h);
            q.push(9, h);
            cout << "q : " << q << endl << endl;
            while(!q.empty())
            {
                cout << "q.pop()" << endl;
                q.pop();
                cout << "q : " << q << endl << endl;
            }
        }
        else if(command == 7)
        {
            cout << "Testing top() method" << endl;
            Pr_queue q;
            q.push(7, l);
            q.push(5, m);
            q.push(8, l);
            q.push(1, l);
            q.push(2, m);
            cout << "q : " << q << endl << endl;
            while(!q.empty())
            {
                auto t = q.top();
                cout << "Top element is " << t << endl;
                cout << "q.pop()" << endl;
                q.pop();
            }
        }
        else 
        {
            cout << "Unlnown command number" << endl;
            break;
        }
    }
return 0;
}
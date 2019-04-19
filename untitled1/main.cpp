#include <iostream>
#include <stack>
#include <Windows.h>

using namespace std;

int main()
{
    cout << "ВВ" << endl;
    int n;
    cin >> n;
    stack <int> st_1;
    stack <int> st_2;
    for(int i = 0; i < n; i++)
    {
        cout << endl << "Введите число" << endl;
        int a;
        cin >> a;
        while(a != 0)
        {
            st_1.push(a % 10);
            a =  a / 10;
        }
        while(!st_1.empty())
        {
            st_2.push(st_1.top());
            st_1.pop();
        }
        cout << "Перевернутое число:" << endl;
        while(!st_2.empty())
        {
            cout << st_2.top();
            st_2.pop();
        }
    }
    return 0;
}

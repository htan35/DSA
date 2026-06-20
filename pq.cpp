#include <iostream>
#include <queue>
using namespace std;

int main()
{
    priority_queue<int> pq;

    int n;

    cout << "How many numbers do you want to insert? ";
    cin >> n;

    cout << "Enter " << n << " numbers:\n";

    for(int i = 0; i < n; i++)
    {
        int x;
        cin >> x;

        pq.push(x);

        cout << "Inserted: " << x << endl;
        cout << "Current Top: " << pq.top() << endl;
        cout << "-----------------\n";
    }

    cout << "\nFinal Top Element: " << pq.top() << endl;

    cout << "\nElements coming out of Max Heap:\n";

    while(!pq.empty())
    {
        cout << pq.top() << " ";
        pq.pop();
    }

    cout << endl;

    return 0;
}
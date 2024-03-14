#include <iostream>
#include <list>
#include <stack>

using namespace std;

const int N = 6;              // liczba wierzcholkow
list<int> adj_list[N + 1];     // listy sasiedztwa. Wierzcholki NUMERUJEMY OD 1


void add_edge(int u, int v)
{
    adj_list[u].push_back(v);
    adj_list[v].push_back(u);
}

// Graf z zadania
void construct_graph()
{
    add_edge(1, 2); add_edge(1, 3); add_edge(1, 4); add_edge(1, 5);
    add_edge(2, 3); add_edge(2, 4); add_edge(2, 6);
    add_edge(3, 5); add_edge(3, 6);
    add_edge(4, 5); add_edge(4, 6);
    add_edge(5, 6);
}


void euler_circuit(int start_vertex)
{
    stack<int> s;
    s.push(start_vertex);
    while (!s.empty()) {
        int v = s.top();
        if(!adj_list[v].empty())
        {
            int u = adj_list[v].back();
            s.push(u);
            adj_list[v].remove(u);
            adj_list[u].remove(v);
        }
        else {
            int k = s.top();
                s.pop();
                cout << k<< " ";
        }
    }

}


int main()
{
    construct_graph();
    euler_circuit(1);
    return 0;
}

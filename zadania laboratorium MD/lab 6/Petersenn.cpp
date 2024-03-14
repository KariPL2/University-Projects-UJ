#include <iostream>
#include <list>

using namespace std;
const int N = 10;              // liczba wierzcholkow

list <int> adj_list[N + 1];      // listy sasiedztwa. Wierzcholki NUMERUJEMY OD 1

bool DOPUSZCZALNE[N + 1];

int X[N + 1];                  // X[1..k] zawiera sciezke X[1],X[2],...,X[k]



void add_edge(int u, int v)
{
    adj_list[u].push_back(v); adj_list[v].push_back(u);
}


void construct_graph()
{
    add_edge(1, 2); add_edge(1, 5); add_edge(1, 6);
    add_edge(2, 3); add_edge(2, 7);
    add_edge(3, 4); add_edge(3, 8);
    add_edge(4, 5); add_edge(4, 9);
    add_edge(5, 10);
    add_edge(6, 8); add_edge(6, 9);
    add_edge(7, 9); add_edge(7, 10);
    add_edge(8, 10);
}

bool hamilton_cycle(int k)
{
    if (k == (N + 1))
    {
        // Sprawdzenie warunku "X[N] jest sąsiadem X[1]"
        int last_vertex = X[N];
        for (int neighbor : adj_list[last_vertex])
        {
            if (neighbor == X[1])
            {
                return true;
            }
        }
        return false;
    }
    else
    {
        for (int u : adj_list[X[k - 1]])
        {
            if (DOPUSZCZALNE[u])
            {
                X[k] = u;
                DOPUSZCZALNE[u] = false;

                if (hamilton_cycle(k + 1))
                {
                    return true;
                }

                DOPUSZCZALNE[u] = true;
            }
        }

        return false;
    }
}

bool hamilton_path(int k)
{
    if (k == (N + 1))
    {
        return true;
    }
    else
    {
        for (int u : adj_list[X[k - 1]])
        {
            if (DOPUSZCZALNE[u])
            {
                X[k] = u;
                DOPUSZCZALNE[u] = false;

                if (hamilton_path(k + 1))
                {
                    return true;
                }

                DOPUSZCZALNE[u] = true;
            }
        }

        return false;
    }
}

// Ponizsza funcja wypisuje przykladowy cykl Hamiltona rozpoczynajacy
// sie od start_vertex lub informuje, ze takowego nie ma.

void find_hamilton_cycle(int start_vertex)
{
    DOPUSZCZALNE[start_vertex] = false;
    for (int i = 0; i <= N; ++i)
    {
        if (i != start_vertex) {
            DOPUSZCZALNE[i] = true;
        }
    }

    X[1] = start_vertex;

    if (hamilton_cycle(2))
    {
        cout << "Cykl Hamiltona znaleziony:" << endl;
        for (int i = 1; i <= N; ++i)
        {
            cout << X[i] << " ";
        }
        cout << X[1] << endl;
    }
    else
    {
        cout << "Brak cyklu Hamiltona." << endl;
    }
}

void find_hamilton_path(int start_vertex)
{
    DOPUSZCZALNE[start_vertex] = false;
    for (int i = 0; i <= N; ++i)
    {
        if (i != start_vertex) {
            DOPUSZCZALNE[i] = true;
        }
    }

    X[1] = start_vertex;

    if (hamilton_path(2))
    {
        cout << "sciezka Hamiltona znaleziona z wierzcholka "<<start_vertex<<": " << endl;
        for (int i = 1; i <= N; ++i)
        {
            cout << X[i] << " ";
        }
        cout << "\n";
    }
    else
    {
        cout << "Brak sciezi Hamiltona z wierzcholka "<<start_vertex << endl;
    }
}
int main()
{
    construct_graph();
    find_hamilton_cycle(3);
    for (int i = 1; i <= N; i++)
    {
        find_hamilton_path(i);
    }
    return 0;
}
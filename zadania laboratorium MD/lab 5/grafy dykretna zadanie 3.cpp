#include <iostream>
#include <list>
#include <stack>
#include <vector>

using namespace std;

const int N = 18;
list<int> adj_list[N + 1];
int edge_count[N + 1];
void add_edge(int u, int v)
{
    adj_list[u].push_back(v);
    adj_list[v].push_back(u);
}

void construct_graph()
{
   /* add_edge(1, 2); add_edge(1, 3); add_edge(1, 4); add_edge(1, 5);
    add_edge(2, 3); add_edge(2, 4); add_edge(2, 6);
    add_edge(3, 5); add_edge(3, 6);
    add_edge(4, 5); add_edge(4, 6);
    add_edge(5, 6);*/
    add_edge(8,9); add_edge(9,11); add_edge(11,10); add_edge(10,8); add_edge(8,7); add_edge(7,15);
    add_edge(15,18); add_edge(18,16); add_edge(16,6); add_edge(6,1); add_edge(1,17); add_edge(17,5);
    add_edge(5,4); add_edge(4,3); add_edge(3,2); add_edge(2,1); add_edge(1,7); add_edge(7,6); add_edge(6,5);
    add_edge(5,13); add_edge(13,17); add_edge(17,16); add_edge(15,16); add_edge(15,14); add_edge(14,12); add_edge(12,8);

}
void remove_edge(int u, int v) {
    adj_list[v].remove(u);
    adj_list[u].remove(v);
}
void eulerian_circuit(int start_vertex, vector<int>& path)
{
    stack<int> s;
    s.push(start_vertex);

    while (!s.empty())
    {
        int v = s.top();

        if (!adj_list[v].empty())
        {
            int u = adj_list[v].back();
            s.push(u);
            remove_edge(u, v);
        }
        else
        {
            path.push_back(v);
            s.pop();
        }
    }
    
}

int main()
{
    vector<int> eulerian_path;
    construct_graph();
    eulerian_circuit(8, eulerian_path);//wyznaczam obwod eulera i przepisuje go na vector


    int s = eulerian_path.size() - 1;
    int k = eulerian_path.size();
    for (int i = 0; i < s; i++)
    {
        for (int j = i + 1; j < k; j++)
        {
            if (eulerian_path[i] == eulerian_path[j])//przechodze po vektorze w podwojnej petli szukajac duplikatow wierzchokow
            {
                
                for (int p = i; p <= j; p++)//jesli taki znajde to wypisuje caly cykl ktory zawieral sie w obwodzie eulera
                {
                    std::cout << eulerian_path[p] << " ";
                }
                std::cout << "\n";

                eulerian_path.erase(eulerian_path.begin() + i, eulerian_path.begin() + j );//nastepnie z vectora usuwam ten cykl oprocz wierzcholka z ktorego zaczynam
                //poniewaz poprzedni weirzcholek przed cyklem rowniez byl polaczony z wierzcholkiem z ktorego wypisany zostal cykl wiec nie usuwajac go nie usuwam rozwniez jednej z niewykorzystanych krawedzi miedzy nimi


                s = eulerian_path.size() - 1;//zmieniam rozmiar s i k w petlach tak aby nie przerkoczyc rozmiaru po usunieciu fragmentu vectora
                k = eulerian_path.size();
                break;//robie break poniewaz nie chce sprawdzac duplikatow w tym samym zakresie i oraz j po usunieciu cyklu z vectora
            }
        }
    }

    for (int i : eulerian_path)
    {
        std::cout << i << " ";//wypisuje to co zostalo czyli ostatni cykl z wierzcholkow ktore nie zostaly usuniete z vectora
    }


}
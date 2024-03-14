#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>


using namespace std;

/*
* Problem z treści zadania sprowadza się do wyróznienia wierzchołków w grafie, które są ze sobą połaczone
* Jako odpady rozumiemy pewien wierzchołek w grafie a mieszanki wybuchowe między odpadami możemy
* interpretować jako krawędzie między wioerzchołkami.Należy wypisać najmniejszą liczbę samochodów oraz
* ich przydział, który nie spowoduje wybuchu , tzn. możemy wyznaczyć minimalne kolorowanie wierzchołkow
* i zapamietując kolory poszczegolnyuch wierzcholkow jestesmy w stanie przypisac je do odpowiednich
* "wywózek".Działając w ten sposób jesteśmy pewni, że 2 połaczone wierzcholki (2 materialy, które dadzą wybuch)
* nie wyladują w jednej grupie kolorów (wywózek).Co do samego maksymalnego niebezpiecznego układu
* możemy rozumieć go jako grupę tych mieszanek, które nie możemy przewozić ze sobą razem parami.
* To sprowadza się do problemu maksymalnej kliki , w której miedzy kazdymi wierzcholkami(materialami)
* istnieja krawedzie(prowadza do wybuchu).
* 
*/






const int MAX_N = 100;

vector<int> colors(MAX_N);
vector<vector<int>> colored_groups;
vector<int> max_dangerous_set;

void add_edge(int u, int v, vector<vector<int>>& adjmatrix) {
    adjmatrix[u][v] = 1;
    adjmatrix[v][u] = 1;
}

bool canUseColor(int vertex, int color, vector<vector<int>>& adjacencyMatrix, int k) {
    for (int i = 1; i < k; ++i) {
        if (adjacencyMatrix[vertex][i] && colors[i] == color) {
            return false;
        }
    }
    return true;
}
// Funkcja colorGraph sprawdza, czy dany graf można pokolorować używając co najwyżej 'no_of_cols' kolorów.
// Jest to część algorytmu kolorowania grafu do rozwiązania problemu minimalnej liczby samochodów.
bool colorGraph(int k, int no_of_cols, vector<vector<int>>& adjacencyMatrix, int N) {
    if (k == N + 1) {
        return true;
    }

    for (int col = 1; col <= no_of_cols; ++col) {
        if (canUseColor(k, col, adjacencyMatrix, k)) {
            colors[k] = col;
            if (colorGraph(k + 1, no_of_cols, adjacencyMatrix, N)) {
                return true;
            }
        }
    }

    return false;
}
// Funkcja isColorable używa colorGraph do sprawdzenia minimalnej liczby samochodów.
bool isColorable(int no_of_cols, vector<vector<int>>& adjacencyMatrix, int N) {
    colors[1] = 1;

    for (int i = 2; i <= N; ++i) {
        colors[i] = 0;
    }

    return colorGraph(2, no_of_cols, adjacencyMatrix, N);
}

void groupVerticesByColor(int N) {
    colored_groups.resize(N + 1);


    for (int i = 1; i <= N; ++i) {
        colored_groups[colors[i]].push_back(i);
    }
}

void dfs(int vertex, vector<vector<int>>& adjacencyMatrix, vector<bool>& visited, vector<int>& current_clique) {
    visited[vertex] = true;
    current_clique.push_back(vertex);

    for (int neighbor = 1; neighbor < adjacencyMatrix.size(); ++neighbor) {
        if (adjacencyMatrix[vertex][neighbor] && !visited[neighbor]) {
            //sprawdzam sasiadow rozpatrywanego wierzcholka
            //jesli tacy istnieja i nie byli odwiedzeni ustawiam flage ze mam klike
            bool is_clique = true;

            for (int i : current_clique) {
                //nastepnie dla kazdego rozpatrzonego wczesniej sasaiada
                //sprawdzam czy rozpatrywany wierzcholek jest z nimi polaczony
                if (!adjacencyMatrix[neighbor][i]) {
                    is_clique = false;
                    break;
                }
            }
            //jesli tak dodaje go do kliki i wznawiam rozpatrywanie
            if (is_clique) {
                dfs(neighbor, adjacencyMatrix, visited, current_clique);
            }
        }
    }
}
void dfs_helper(int v, int N, vector<vector<int>>& adjacencyMatrix) {
    vector<bool> visited(N + 1, false);
    for (int start_vertex = v; start_vertex <= N; ++start_vertex) {
        if (!visited[start_vertex]) {
            vector<int> current_clique;
            dfs(start_vertex, adjacencyMatrix, visited, current_clique);

            if (current_clique.size() > max_dangerous_set.size()) {
                //jako ze sprawdzam mozliwe kliki z akzdego wierzcholka to jesli
                //napotkam klike o wiekszej liczbie wierzccholkow ustawiam ja jako maksymalna
                max_dangerous_set = current_clique;
            }
        }
    }
}

// Funkcja findMaxDangerousSet szuka maksymalnie niebezpiecznego układu, czyli maksymalnej kliki w grafie.
void findMaxDangerousSet(vector<vector<int>>& adjacencyMatrix, int N) {
    for (int start_vertex = 1; start_vertex <= N; ++start_vertex) {
        dfs_helper(start_vertex, N, adjacencyMatrix);
    }
   
}


int main() {
    ifstream myfile;
    myfile.open("zwiazki.txt");

    int n;
    myfile >> n;

    vector<vector<int>> adjacencyMatrix(n + 1, vector<int>(n + 1, 0));

    while (myfile.peek() != EOF) {
        int u, v;
        myfile >> u >> v;
        add_edge(u, v, adjacencyMatrix);
       // cout << u << " " << v << endl;
    }

    int min_no_colors = 0;

    colored_groups = vector<vector<int>>(MAX_N, vector<int>());

    for (int i = 1; i <= n; ++i) {
        if (isColorable(i, adjacencyMatrix, n)) {
            min_no_colors = i;
            break;
        }
    }

    groupVerticesByColor(n);

    for (int i = 1; i <= min_no_colors; ++i) {
        if (colored_groups[i].size() == 0) {
            min_no_colors = i;
            break;
        }
    }
    for (int i = 1; i <= min_no_colors; ++i) {
        cout << "Samochod " << i << ": ";
        for (int j : colored_groups[i]) {
            cout << j << " ";
        }
        cout << endl;
    }

    findMaxDangerousSet(adjacencyMatrix, n);

    cout << "Maksymalnie niebezpieczny uklad ma " << max_dangerous_set.size() << " elementy." << endl;
    cout << "Przykladowy taki uklad: ";
    for (int i : max_dangerous_set) {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}

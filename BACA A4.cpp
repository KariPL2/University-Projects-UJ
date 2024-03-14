// Karol Bargiel
#include <iostream>
#include <vector>
std::vector<std::vector<unsigned long long> > adj_matrix;


std::vector<std::vector<unsigned long long> > multiplyMatrices(std::vector<std::vector<unsigned long long> > a, std::vector<std::vector<unsigned long long> >& b, unsigned long long M) {
    int N = a.size();
    std::vector<std::vector<unsigned long long> > res(N, std::vector<unsigned long long>(N, 0));

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            for (int k = 0; k < N; k++) {
                res[i][j] += (a[i][k] * b[k][j]) % M;
            }
            res[i][j] %= M;
        }
    }
    return res;
}



std::vector<std::vector<unsigned long long> > matrixPowerL(unsigned long long L, std::vector<std::vector<unsigned long long> > mat, unsigned long long int M) {
    if (L == 1) {
        return mat;
    }

    std::vector<std::vector<unsigned long long> > half;
    half = matrixPowerL(L / 2, mat, M);


    if (L % 2 == 0) {
        return multiplyMatrices(half, half, M);
    }
    else {
        return multiplyMatrices(multiplyMatrices(half, half, M), mat, M);
    }
}



int main() {
    int Z;
    std::cin >> Z;

    long int N;
    unsigned long long M;
    unsigned long long L;

    for (int i = 0; i < Z; ++i) {
        
        std::cin >> N >> L >> M;

        

        adj_matrix.resize(N, std::vector<unsigned long long>(N, 0));

        for (int j = 0; j < N; ++j) {
            int no_cities;
            std::cin >> no_cities;
            for (int k = 0; k < no_cities; ++k) {
                int city;
                std::cin >> city;
                adj_matrix[j][city] = 1;
            }
        }

        if (L != 0) {
            std::vector<std::vector<unsigned long long> > res = matrixPowerL(L, adj_matrix, M);

            std::cout << res[0][N - 1] << std::endl;
            adj_matrix.clear();

        }
        else {
            std::cout << 0 << std::endl;
        }
        //res.clear();
        
    }


}
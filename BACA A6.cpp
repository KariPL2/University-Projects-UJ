//Karol Bargiel
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

const int dx[] = { 1, 0, -1, 0 };
const int dy[] = { 0, 1, 0, -1 };
vector<pair<int, int>> groups;


bool comparePixels(const pair<int,int>& p1, const pair<int, int>& p2) {
    if (p1.second == p2.second) {
        return p1.first < p2.first;
    }
    return p1.second < p2.second;
}

void DFS( pair<int,int>& badPixel, map<pair<int, int>, bool>& visitedPixels) {
    visitedPixels[badPixel] = true;
    int cx = badPixel.first;
    int cy = badPixel.second;

    for (int i = 0; i < 4; i++) {
        int nx = cx + dx[i];
        int ny = cy + dy[i];
        auto neighbor = make_pair(nx, ny);

        auto it = visitedPixels.find(neighbor);

        if (it != visitedPixels.end() && !it->second) {
            visitedPixels[neighbor] = true;
            DFS(neighbor, visitedPixels);
        }
    }
}

int main() {
    int Z;
    cin >> Z;

    while (Z-- > 0) {
        int H, W, M;
        cin >> H >> W >> M;

        map<pair<int, int>, bool> visitedPixels;
        vector < pair<int, int> > pairs(M);
        for (int i = 0; i < M; ++i) {
            int x, y;
            cin >> x >> y;
            pairs[i] = make_pair(x, y);
        }
        sort(pairs.begin(), pairs.end(), comparePixels);
        for (int i = 0; i < pairs.size(); i++)
        {
            visitedPixels[pairs[i]] = false;
        }
        for (int i = 0; i < M; i++) {
            if (!visitedPixels[pairs[i]]) {
                DFS( pairs[i], visitedPixels);
                groups.push_back({ pairs[i].first, pairs[i].second });
            }
        }

        cout << groups.size() << endl;

        for (const auto& component : groups) {
            cout << component.first << " " << component.second << endl;
        }
        groups.clear();
    }

    return 0;
}
#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <queue>

using namespace std;

class Graph {
private:
    vector<int> *adjacency_;
    int size_;
    const int INF = 400001;
public:
    Graph(int v) : size_(v) {
        adjacency_ = new vector<int>[v];
    }

    ~Graph() {
        delete[] adjacency_;
    }

    void add(int first, int second) {
        if (first != second) {
            adjacency_[first].push_back(second);
            adjacency_[second].push_back(first);
        }
    }

    void BFS(vector<int> &distances, queue<int> &searchPath, int pos){
        for (int i = 0; i<adjacency_[pos].size(); i++){
            int cur = adjacency_[pos][i];
            if (distances[cur] == INF){
                distances[cur] = distances[pos]+1;
                searchPath.push(cur);
            }
        }
        searchPath.pop();
    }

    vector<int> pathFinder() {
        vector<int> distances(size_);
        queue<int> searchPath;

        for (int i = 0; i < size_; i++) {
            distances[i] = INF;
        }
        distances[0] = 0;
        searchPath.push(0);

        while(!searchPath.empty()){
            BFS(distances, searchPath, searchPath.front());
        }

        return distances;
    }
};

int main() {
    vector<int> ans;
    int n, m, first, second;

    ifstream fin("pathbge1.in");
    ofstream fout("pathbge1.out");

    fin >> n >> m;

    Graph graph(n);
    for (int i = 0; i<m; i++){
        fin >> first >> second;
        graph.add(first-1, second-1);
    }

    ans = graph.pathFinder();

    for (int i = 0; i<ans.size(); i++){
        fout << ans[i] << ' ';
    }

    return 0;
}
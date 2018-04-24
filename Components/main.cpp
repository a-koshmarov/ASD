#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>

using namespace std;

class Graph {
private:
    vector<int> *adjacency_;
    int size_;
public:
    Graph(int v) : size_(v){
        adjacency_ = new vector<int>[v];
    }

    ~Graph(){
        delete[] adjacency_;
    }

    void add(int first, int second){
        if (first!=second){
            adjacency_[first].push_back(second);
            adjacency_[second].push_back(first);
        }
    }

    void DFS(vector<int> &components, int count, int node, bool visit[]){
        // Делаем текущую вершину посещенной
        visit[node] = true;

        // Присваиваем вершине номер текущей компоненты
        components[node] = count;

        for (int i = 0; i<adjacency_[node].size(); i++){
            int curr = adjacency_[node][i];
            if (!visit[curr]){
                DFS(components, count, curr, visit);
            }
        }

    }

    pair<vector<int>, int> components(){
        // Посещенные вершины
        auto *visit = new bool[size_];
        for (int i = 0; i<size_; i++){
            visit[i] = false;
        }

        int count = 0;
        vector<int> components(size_);
        for (int i = 0; i<size_; i++){
            if (!visit[i]){
                count++;

                // Запускаем DFS, если еще не были в вершине
                DFS(components, count, i, visit);
            }
        }
        return make_pair(components, count);
    }
};

int main() {
    vector<int> ans;
    int count, n, m, first, second;

    ifstream fin("components.in");
    ofstream fout("components.out");

    fin >> n >> m;

    Graph graph(n);
    for (int i = 0; i<m; i++){
        fin >> first >> second;
        graph.add(first-1, second-1);
    }

    tie(ans, count) = graph.components();

    fout << count << endl;
    for (int i = 0; i<ans.size(); i++){
        fout << ans[i] << ' ';
    }

    return 0;
}
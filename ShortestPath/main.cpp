#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>

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

    vector<int> pathFinder() {
        vector<int> distances(size_);
        auto *visit = new bool[size_];
        for (int i = 0; i < size_; i++) {
            visit[i] = false;
            distances[i] = INF;
        }
        distances[0] = 0;

        for (int i = 0; i < size_-1; i++) {
            int node = pickMinNode(distances, visit);
//            cout << "curr node is " << node << endl;
            for (int j = 0; j<adjacency_[node].size(); j++){
                int upd = adjacency_[node][j];
//                cout << "dist of "<< upd << " is " << distances[upd] << endl;
                if (distances[node] < INF && distances[node] + 1 < distances[upd]){
                    distances[upd] = distances[node] + 1;
//                    cout << "updated value of " << upd << " is " << distances[upd] << endl;
                }
            }
        }
        return distances;
    }

    int pickMinNode(vector<int> &dist, bool visit[]) {
        for (int i = 0; i < size_; i++) {
            if (!visit[i] && dist[i] < INF) {
                visit[i] = true;
                return i;
            }
        }
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
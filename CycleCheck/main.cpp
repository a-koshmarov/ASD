#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

class Graph {
private:
    vector<int> *adjacency_;
    int size_;
    const int INF = 100001;
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
        }
    }
    
    bool DFS_help(int pos, vector<int> &state, vector<int> &path, vector<int> &cycle, ostream &s){
        path.push_back(pos);
        state[pos] = 1;

        for (int i = 0; i<adjacency_[pos].size(); i++){
            int cur = adjacency_[pos][i];
            if (state[cur] == 0){
                DFS_help(cur, state, path, cycle, s);
            } else if (state[cur] == 1){
                bool start_cycle = false;
                s << "YES" << endl;

                for (int j = 0; j < path.size(); j++){
                    int cur_path = path[j];

                    if (cur == cur_path){
                        start_cycle = true;
                    }

                    if (start_cycle){
                        s << cur_path+1 << ' ';
                    }
                }
                s << endl;
                exit(0);
            }
        }
        path.pop_back();
        state[pos] = 3;
    }

    vector<int> cycleCheck(ostream &s){
        vector<int> state(INF, 0), path, cycle;

        for (int i = 0; i<size_; i++){
            if (state[i] == 0){
                DFS_help(i, state, path, cycle, s);
            }
        }
        s << "NO" << endl;
    }
};


int main() {
    int n, m, first, second;

    ifstream fin("cycle.in");
    ofstream fout("cycle.out");

    fin >> n >> m;

    Graph graph(n);
    for (int i = 0; i<m; i++){
        fin >> first >> second;
        graph.add(first-1, second-1);
    }

    graph.cycleCheck(fout);
    return 0;
}
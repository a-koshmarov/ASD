#include <iostream>
#include <fstream>
#include <vector>

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
        adjacency_[first].push_back(second);
    }

    void DFS(int pos, vector<int> &visited, vector<int> &topSorted, ostream &s){
        visited[pos] = 1;

        for(int i = 0; i<adjacency_[pos].size(); i++){
            int cur = adjacency_[pos][i];
            if (visited[cur] == 0){
                DFS(cur, visited, topSorted, s);
            } else if (visited[cur] == 1){
                s << -1 << endl;
                exit(0);
            }
        }

        topSorted.push_back(pos);
        visited[pos] = 2;
    }

    void topSort(ostream &s){
        vector<int> visited(size_);
        vector<int> topSorted;

        for (int i = 0; i <size_; i++){
            if (visited[i] == 0){
                DFS(i, visited, topSorted, s);
            }
        }

        while(!topSorted.empty()){
            s << topSorted.back()+1 << ' ';
            topSorted.pop_back();
        }
    }

//    void topSort(ostream &s){
//        vector<int> entries(size_, 0);
//        vector<int> topSorted;
//        queue<int> path;
//        int count = 0;
//
//        for (int i=0; i<size_; i++){
//            for (int j = 0; j<adjacency_[i].size(); j++){
//                int cur = adjacency_[i][j];
//                entries[cur]++;
//            }
//        }
//
//        for (int i = 0; i <size_; i++){
//            if (entries[i] == 0){
//                path.push(i);
//            }
//        }
//
//        while(!path.empty()){
//            int cur = path.front();
//            path.pop();
//
//            topSorted.push_back(cur);
//
//            for (int i = 0; i<adjacency_[cur].size(); i++){
//                int cur_node = adjacency_[cur][i];
//                entries[cur_node]--;
//                if (entries[cur_node] == 0){
//                    path.push(cur_node);
//                }
//            }
//            count++;
//        }
//
//        if (count!=size_){
//            s << "-1" << endl;
//            return;
//        }
//
//        for (int i = 0; i<size_; i++){
//            s << topSorted[i]+1 << ' ';
//        }
//    }
};

int main() {
    int n, m, first, second;

    ifstream fin("topsort.in");
    ofstream fout("topsort.out");

    fin >> n >> m;

    Graph graph(n);
    for (int i = 0; i<m; i++){
        fin >> first >> second;
        graph.add(first-1, second-1);
    }

    graph.topSort(fout);

    fin.close();
    fout.close();

    return 0;
}
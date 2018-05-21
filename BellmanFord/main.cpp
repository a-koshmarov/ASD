#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <queue>

using namespace std;
typedef pair<int, long long> Point;

struct Edge {
    int v_;
    int u_;
    long long weight_;

    Edge() = default;
    Edge(int u, int v, long long w) : u_(u), v_(v), weight_(w){}
};

class Graph {
private:
    int size_;
    int e_size_;
    vector<Edge> edges_;
    vector<Point> *adjacency_;

    const long long INF = 0x7FFFFFFFFFFFFFF0LL - (long long) 2e15;

public:
    Graph(int size, int edges_size) : size_(size), e_size_(edges_size){
        adjacency_ = new vector<Point>[size];
    }

    ~Graph(){
        delete [] adjacency_;
    }

    void add(int i, int j, long long elem){
        edges_.emplace_back(Edge(i, j, elem));
        adjacency_[i].emplace_back(make_pair(j, elem));
//        cout << "size is " << edges_.size() << endl;
    }

    void searchBFS(int pos, vector<bool> &negative){
        vector<int> visited(size_, 0);
        queue<int> searchPath;

        searchPath.push(pos);
        while(!searchPath.empty()){
            int cur = searchPath.front();

            negative[cur] = true;
            visited[cur] = 1;
            for (auto el:adjacency_[cur]){
                int toCheck = el.first;
                if(visited[toCheck]==0){
                    searchPath.push(toCheck);
                }
            }
            visited[cur] = 3;
            searchPath.pop();
        }
    }

    void pathFinder(int start, ostream &s){
        vector<long long> distance(size_, INF);
        vector<int> prev(size_, -1);
        vector<bool> negative(size_, false);
        vector<int> cycle;

        distance[start] = 0;

        for (int i = 0; i<size_-1; i++){
            for (int j = 0; j<e_size_; j++){
                int first = edges_[j].u_;
                int second = edges_[j].v_;
                long long weight = edges_[j].weight_;

                if (distance[first]!= INF && distance[second] > distance[first] + weight){
                    distance[second] = max(-INF, distance[first] + weight);
                    prev[second] = first;
                }
            }
        }

        for (int i = 0; i < e_size_; i++)
        {
            int first = edges_[i].u_;
            int second = edges_[i].v_;
            long long weight = edges_[i].weight_;
            if (distance[first] != INF && distance[first] + weight < distance[second]) {
//                cout << "cycle at " << second << endl;
                cycle.push_back(first);
            }
        }

        for (auto el:cycle){
            searchBFS(el, negative);
        }

        for (int i = 0; i< size_; i++){
            if (negative[i]){
                s << '-' << endl;
            } else if (distance[i] == INF){
                s << '*' << endl;
            } else {
                s << distance[i] << endl;
            }
        }
    }

    void print(){
        cout << "sizes " << e_size_ << ' ' << edges_.size() << endl;

        for (auto el:edges_){
            cout << "edge is " << el.u_ << ' ' << el.v_ << ' ' << el.weight_ << endl;
        }
    }
};


int main() {
    int n, m, start, first, second;
    long long elem;

    ifstream fin("path.in");
    ofstream fout("path.out");

    fin >> n >> m >> start;

    Graph graph(n, m);

    for (int i = 0; i < m; i++){
        fin >> first >> second >> elem;
        graph.add(first-1, second-1, elem);
    };

//    graph.print();
    graph.pathFinder(start-1, fout);

    fin.close();
    fout.close();

    return 0;
}
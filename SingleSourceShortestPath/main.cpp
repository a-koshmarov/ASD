#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <queue>

using namespace std;
typedef pair<long long, long long> Point;

class Graph {
private:
    int size_;
    vector<pair<int, long long>> *adjacency_;
    const long long INF = LLONG_MAX;

public:
    explicit Graph(int size) : size_(size){
        adjacency_ = new vector<pair<int, long long>>[size];
    }

    ~Graph(){
        delete[] adjacency_;
    }

    void add(int i, int j, long long elem){
        adjacency_[i].emplace_back(make_pair(j, elem));
        adjacency_[j].emplace_back(make_pair(i, elem));
    }


    long long pathFinder(int start, ostream &s){
        vector<long long> distance(size_, INF);
        priority_queue<Point, vector<Point>, greater<Point>> path;

        distance[start] = 0;
        path.push(make_pair(0, start));

        while(!path.empty()){
            long long minNode = path.top().second;
            path.pop();

            for (long long i = 0; i<adjacency_[minNode].size(); i++){
                Point cur = adjacency_[minNode][i];

                if (distance[cur.first] > distance[minNode] + cur.second){
                    distance[cur.first] = distance[minNode] + cur.second;
                    path.push(make_pair(distance[cur.first], cur.first));
                }
            }
        }

        for (auto el : distance){
            s << el << ' ';
        }
        s << endl;
    }
};


int main() {
    int n, start, finish;
    long long elem, m;

    ifstream fin("pathbgep.in");
    ofstream fout("pathbgep.out");

    fin >> n >> m;

    Graph graph(n);

    for (long long i = 0; i < m; i++){
        fin >> start >> finish >> elem;
        graph.add(start-1, finish-1, elem);
    };

    graph.pathFinder(0, fout);

    fin.close();
    fout.close();

    return 0;
}
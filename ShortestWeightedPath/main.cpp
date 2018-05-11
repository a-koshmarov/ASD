#include <iostream>
#include <fstream>
#include <vector>
#include <climits>

using namespace std;

class Graph {
private:
    int size_;
//    long long** matrix_;
    vector<vector<long long>> matrix_;
    const long long INF = LLONG_MAX;

public:
    explicit Graph(int size) : size_(size), matrix_(size, vector<long long>(size, -1)){
        for(int i = 0; i < size; ++i) {
            matrix_[i][i] = 0;
            for (int j = 0; j<size; j++){
                cout << matrix_[i][j];
            }
            cout << endl;
        }
    }

    ~Graph() = default;

    void add(int i, int j, long long elem){
        matrix_[i][j] = elem;
    }

    int pickNode(vector<long long> &distance, vector<bool> &visited){
        long long curValue = INF;
        int returnValue;

        for (int i = 0; i<size_; i++){
            if(!visited[i] && distance[i] <= curValue){
                returnValue = i;
                curValue = distance[i];
            }
        }

        return returnValue;
    }

    long long pathFinder(int start, int end){
        vector<long long> distance(size_, INF);
        vector<bool> visited(size_, false);

        distance[start] = 0;

        for (int i = 0; i<size_-1; i++){
            int curNode = pickNode(distance, visited);

            visited[curNode] = true;

            for(int nextNode = 0; nextNode<size_; nextNode++){
                if (!visited[nextNode] && matrix_[curNode][nextNode] != -1 && distance[curNode] != INF && distance[curNode] + matrix_[curNode][nextNode] < distance[nextNode]) {
                    distance[nextNode] = distance[curNode] + matrix_[curNode][nextNode];
                }
            }
        }

        if (distance[end]!=INF){
            return distance[end];
        } else {
            return -1;
        }
    }
};


int main() {
    int n, start, finish;
    long long elem, dist;

    ifstream fin("pathmgep.in");
    ofstream fout("pathmgep.out");

//    fin >> n >> start >> finish;

    Graph graph(5);

//    for (int i = 0; i < n; i++){
//        for (int j = 0; j < n; j++){
//            fin >> elem;
//            graph.add(i, j, elem);
//        }
//    };

//    dist = graph.pathFinder(start-1, finish-1);

//    fout << dist << endl;

    fin.close();
    fout.close();

    return 0;
}
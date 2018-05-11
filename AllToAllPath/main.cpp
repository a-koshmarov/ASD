#include <iostream>
#include <fstream>
#include <vector>
#include <climits>

using namespace std;

class Graph {
private:
    int size_;
    long long** matrix_;
    const long long INF = LLONG_MAX;

public:
    explicit Graph(int size) : size_(size){
        matrix_ = new long long*[size];
        for(int i = 0; i < size; i++) {
            matrix_[i] = new long long[size];
            for (int j = 0; j < size; j++){
                matrix_[i][j] = -1;
            }
            matrix_[i][i] = 0;
        }
    }

    ~Graph(){
        for(int i = 0; i < size_; ++i) {
            delete [] matrix_[i];
        }
        delete [] matrix_;
    };

    void add(int i, int j, long long elem){
        matrix_[i][j] = elem;
        matrix_[j][i] = elem;
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

    void pathFinder(int start, ostream &s){
        vector<long long> distance(size_, INF);
        vector<bool> visited(size_, false);

        distance[start] = 0;

        for (int i = 0; i<size_; i++){
            int curNode = pickNode(distance, visited);

            visited[curNode] = true;

            for(int nextNode = 0; nextNode<size_; nextNode++){
                if (!visited[nextNode] && matrix_[curNode][nextNode] != -1 && distance[curNode] != INF && distance[curNode] + matrix_[curNode][nextNode] < distance[nextNode]) {
                    distance[nextNode] = distance[curNode] + matrix_[curNode][nextNode];
                }
            }
        }

        for (auto el : distance){
            s << el << ' ';
        }
        s << endl;
    }

    void print(){
        for(int i = 0; i < size_; ++i) {
            for (int j = 0; j<size_; j++){
                cout << matrix_[i][j] << ' ';
            }
            cout << endl;
        }
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
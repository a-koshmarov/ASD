#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Graph {
private:
    vector<int> *adjacency_;
    vector<pair<int, int>> coords;

    const int INF = 400001;

    int size_;
    int S, T;
public:
    Graph(int v) : size_(v) {
        adjacency_ = new vector<int>[v];
    }

    ~Graph() {
        delete[] adjacency_;
    }

    void addCoord(int x, int y) {
        coords.emplace_back(make_pair(x, y));
    }

    void addAdj(int x, int y) {
        adjacency_[x].push_back(y);
        adjacency_[y].push_back(x);
    }

    void setT(int pos) {
        T = pos;
//        cout << "T is: " << coords[T].first << ' ' << coords[T].second << endl;
    }

    void setS(int pos) {
        S = pos;
//        cout << "S is: " << coords[S].first << ' ' << coords[S].second << endl;
    }

    int get() {
        cout << "T is " << T << endl;
        cout << "S is " << S << endl;
    }

    int getLastIndex() {
        return coords.size() - 1;
    }

    void BFS(vector<int> &distances, queue<int> &toSearch, int pos) {
        for (int i = 0; i < adjacency_[pos].size(); i++) {
            int cur = adjacency_[pos][i];
            if (distances[cur] == INF) {
                distances[cur] = distances[pos] + 1;
                toSearch.push(cur);
            }
        }
        toSearch.pop();
    }

    vector<int> pathFinder(int start) {
        vector<int> distances(coords.size(), INF);
        queue<int> toSearch;

        toSearch.push(start);
        distances[start] = 0;


        while (!toSearch.empty()) {
            BFS(distances, toSearch, toSearch.front());
        }

        return distances;
    }

    void updateCharPath(vector<int> &distances, vector<char> &charPath, int pos) {
        int curDist = distances[pos];
        int curX = coords[pos].first;
        int curY = coords[pos].second;
//        cout << "current x,y: " << curX << ' ' << curY << endl;

        for (auto el : adjacency_[pos]) {
            int newDist = distances[el];

            if (newDist == curDist - 1) {
                int newX = coords[el].first;
                int newY = coords[el].second;
//                cout << "new x,y: " << newX << ' ' << newY << endl;

                if (newX == curX - 1) {
                    charPath.push_back('D');
                } else if (newX == curX + 1) {
                    charPath.push_back('U');
                } else if (newY == curY - 1) {
                    charPath.push_back('R');
                } else if (newY == curY + 1) {
                    charPath.push_back('L');
                }

                updateCharPath(distances, charPath, el);
                break;
            }
        }
    }

    void printPath(ostream &s) {
        vector<int> distances = pathFinder(S);
        vector<char> charPath;

        if (distances[T] == INF) {
            s << -1 << endl;
        } else {
            s << distances[T] << endl;

            updateCharPath(distances, charPath, T);
            reverse(charPath.begin(), charPath.end());

            for (auto el : charPath) {
                s << el;
            }
        }
    }

    void print() {
        for (int i = 0; i < coords.size(); i++) {
            cout << "element is " << i << ": ";
            for (int j = 0; j < adjacency_[i].size(); j++) {
                cout << adjacency_[i][j] << ' ';
            }
            cout << endl;
        }
    }
};


int main() {
    int n, m;
    char elem;
    vector<vector<pair<char, int>>> lab(100);

    ifstream fin("input.txt");
    ofstream fout("output.txt");

    fin >> n >> m;

    Graph graph(n * m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            fin >> elem;
            lab[i].emplace_back(make_pair(elem, -1));

            if (elem != '#') {
                graph.addCoord(i, j);
//                cout << "current x,y: " << i << ' ' << j << endl;
                lab[i][j].second = graph.getLastIndex();

                if (elem == 'T') {
                    graph.setT(graph.getLastIndex());
                } else if (elem == 'S') {
                    graph.setS(graph.getLastIndex());
                }

                if (j != 0 && lab[i][j - 1].first != '#') {
                    graph.addAdj(graph.getLastIndex(), lab[i][j - 1].second);
                }

                if (i != 0 && lab[i - 1][j].first != '#') {
                    graph.addAdj(graph.getLastIndex(), lab[i - 1][j].second);
                }
            }
        }
    }
//    graph.print();
//    graph.get();

    graph.printPath(fout);
    return 0;
}

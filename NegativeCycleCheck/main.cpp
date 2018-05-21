#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <climits>

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

    const long double INF = 10e8;

public:
    Graph(int size) : size_(size), e_size_(0){
        adjacency_ = new vector<Point>[size];
    }

    ~Graph(){
        delete [] adjacency_;
    }

    void add(int i, int j, long long elem){
        if (elem<INF){
            edges_.emplace_back(Edge(i, j, elem));
            adjacency_[i].emplace_back(make_pair(j, elem));
            e_size_++;
        }
//        cout << "size is " << edges_.size() << endl;
    }

    vector<int> search(vector<long long> &distance, vector<int> &prev, vector<bool> &negative, int pos, ostream &s){
        vector<int> ans;
        vector<bool> visited(size_, false);
        int cur = pos;


        while(true){
            ans.push_back(cur);
            visited[cur] = true;
            cur = prev[cur];
            if (visited[cur]){
                ans.push_back(cur);
                break;
            }
        }
        return ans;
    }

    void pathFinder(int start, ostream &s){
        vector<long long> distance(size_, INF);
        vector<int> prev(size_, -1);
        vector<bool> negative(size_, false);
        vector<int> ans, fullAns;
        int cycle = -1;

        distance[start] = 0;

        for (int i = 0; i<size_-1; i++){
            for (int j = 0; j<e_size_; j++){
                int first = edges_[j].u_;
                int second = edges_[j].v_;
                long long weight = edges_[j].weight_;

                if (distance[second] > distance[first] + weight){
                    distance[second] = distance[first] + weight;
                    prev[second] = first;
                }
            }
        }

        for (int i = 0; i < e_size_; i++)
        {
            int first = edges_[i].u_;
            int second = edges_[i].v_;
            long long weight = edges_[i].weight_;
            long long dist = distance[second];
            if (distance[first] + weight < distance[second]) {
//                cout << "cycle at " << second << endl;
                cycle = first;
            }
        }

        if (cycle!=-1){
//            cout << "yes " << cycle <<endl;
            ans = search(distance, prev, negative, cycle, s);
        }

        if (!ans.empty()){
            int first = ans.back();
            ans.pop_back();
            reverse(ans.begin(), ans.end());
            fullAns.push_back(first);

            for (auto el:ans){
                fullAns.push_back(el);
                if (el == first) break;
            }

            s << "YES" << endl << fullAns.size() << endl;

            for(auto el:fullAns){
                s << el+1 << ' ';
            }
            s << endl;
        } else {
            s << "NO" << endl;
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
    int n;
    long long elem;

    ifstream fin("negcycle.in");
    ofstream fout("negcycle.out");

    fin >> n;

    Graph graph(n);

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            fin >> elem;
            graph.add(i, j, elem);
            if (i == j && elem < 0){
                fout << "YES" << endl << 2 << endl;
                fout << i+1 << ' ' << j+1 << endl;
                exit(0);
            }
        }
    };

//    graph.print();
    graph.pathFinder(0, fout);

    fin.close();
    fout.close();

    return 0;
}
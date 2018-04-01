#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int binSearch(vector<pair<int, pair<int, int>>> &arr, int value, int n) {
    int left = 0;
    int right = n;
    int m;
    while (true) {
        m = (left + right) / 2;

        if (value < arr[m].first)
            right = m - 1;
        else if (value > arr[m].first)
            left = m + 1;
        else
            return m;

        if (left > right)
            return -1;
    }
}

int main() {
    int n, m;
    bool first = true;
    int pos1, pos2, curr, count = 0;
    vector<int> numbers;
    vector<pair<int, pair<int, int>>> pairs;

    ifstream fin("binsearch.in");
    ofstream fout("binsearch.out");

    fin >> n;

    for (int i = 1; i <= n; i++) {
        fin >> curr;
        numbers.push_back(curr);
        if (first) {
            pos1 = i;
            first = !first;
            continue;
        }

        if (curr != numbers[i - 2]) {
            pos2 = i - 1;
            pairs.push_back(make_pair(numbers[i - 2], make_pair(pos1, pos2)));
            count++;
            pos1 = i;
        }

        if (i == n) {
            pos2 = i;
            pairs.push_back(make_pair(numbers[i-1], make_pair(pos1, pos2)));
            count++;
        }
    }

    fin >> m;

    for (int i = 0; i<m; i++){
        fin >> curr;
        int result = binSearch(pairs, curr, count);
        if (result != -1){
            fout << pairs[result].second.first << ' ' << pairs[result].second.second << endl;
        } else {
            fout << "-1 -1" << endl;
        }
    }


    fin.close();
    fout.close();
}
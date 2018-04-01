#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

void pushNums(vector<int> *nums, int *arr[4], int pos) {
    if (arr[pos][1]) { pushNums(nums, arr, arr[pos][1]); }
//        arr[pos][3] = 1;
    nums->push_back(arr[pos][0]);
//        cout << arr[pos][0] << endl;
    if (arr[pos][2]) { pushNums(nums, arr, arr[pos][2]); }
}

bool check(vector<int> &nums) {
//    cout << "in check" << endl;
    for (int i = 0; i < nums.size()-1; i++) {
        if (nums[i] >= nums[i + 1]) {
            return false;
        }
    }
    return true;
}

int main() {
    auto *numbers = new vector<int>;
    int n;

    ifstream fin("check.in");
    ofstream fout("check.out");

    fin >> n;
    int **data = new int *[n];
    for (int i = 0; i <= n; i++) {
        data[i] = new int[4];
    }


    if (n == 0 || n == 1) {
        fout << "YES";
    } else {
        for (int i = 1; i <= n; i++) {
            fin >> data[i][0] >> data[i][1] >> data[i][2];
            data[i][3] = 0;
        }
        pushNums(numbers, data, 1);

        if (check(*numbers)) {
            fout << "YES";
        } else {
            fout << "NO";
        }
    }

    fin.close();
    fout.close();
    return 0;
}
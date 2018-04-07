#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    double a, mid, left, right;
    double curr, prev, next, ans;
    bool high;
    ifstream fin("garland.in");
    ofstream fout("garland.out");
    fin >> n >> a;

    // Начальные положения для поиска положения 2 лампы
    left = 0;
    right = a;

    while (true) {
        mid = (left + right) / 2;

        // Выходим из цикла при достижении предела точности
        if (left == mid || right == mid) break;

        // Положения h{i} и h{i-1}
        curr = mid;
        prev = a;
        high = mid > 0;

        // Находим пололожение всех ламп, основываясь на положении 1 и 2
        for (int i = 0; i < n - 2; i++) {
            // h{i+1} = 2h{i} - h{i-1} + 2
            next = 2 * curr - prev + 2;
            high = high && (next > 0);
            if (!high) break;
            prev = curr;
            curr = next;
        }

        // Меняем границу поиска положения 2 лампы
        // Если последняя лампа > 0
        if (high) {
            right = mid;
            ans = curr;
        // Если последняя лампа < 0
        } else {
            left = mid;
        }

    }

    fout << fixed << setprecision(2) << ans << std::endl;
    fin.close();
    fout.close();
    return 0;
}
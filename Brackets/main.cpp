#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    bool nice;

    string brackets;
    vector<char> stack;
    vector<int> ans;


    ifstream infile;
    infile.open("input.txt");

    while(true){
        infile>>brackets;
        if(infile.eof()) break;
//        cout<<brackets<<endl;
        nice = true;
        for(int i=0; i<brackets.length();i++){
            if(brackets[i] == '[' || brackets[i] == '('){
                stack.push_back(brackets[i]);
            } else {
                if(!stack.empty()) {
                    if (brackets[i] == ']' && stack[stack.size() - 1] == '[') {
                        stack.pop_back();
                    } else if (brackets[i] == ')' && stack[stack.size() - 1] == '('){
                        stack.pop_back();
                    } else {
                        nice = false;
                    }
                } else {
                    nice = false;
                }
            }
        }

        if (!stack.empty())nice = false;

        if(nice){
            ans.push_back(1);
//            cout << 1 << ' ';
        } else {
            ans.push_back(0);
//            cout << 0 << ' ';
        }

        stack.clear();

    }
    infile.close();


    ofstream outfile;
    outfile.open("output.txt");

    for (int i=0; i<ans.size(); i++){
        if(ans[i]){
            outfile << "YES" <<endl;
        } else {
            outfile << "NO" << endl;
        }
    }

    outfile.close();
    return 0;
}
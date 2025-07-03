#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

vector<int> parseLine(const string& line) {
    vector<int> nums;
    int i = 0;
    int n = line.length();
    while (i < n) {
        int sign = 1;
        if (line[i] == '-') {
            sign = -1;
            i++;
        }
        int num = 0;
        bool hasDigit = false;
        while (i < n && isdigit(line[i])) {
            hasDigit = true;
            num = num * 10 + (line[i] - '0');
            i++;
        }
        if (hasDigit || !nums.empty()) { 
            nums.push_back(sign * num);
        }
        i++;
    }
    return nums;
}

vector<int> function(vector<int> nums, int T) {// method 1 
    vector<int> result;
    vector<bool> a(nums.size(), false);

    for (int i = 0; i < nums.size(); ++i) {
        if (!a[i]) {
            int count = 1;
            for (int j = i + 1; j < nums.size(); ++j) {
                if (nums[j] == nums[i]) {
                    count++;
                    a[j] = true;
                }
            }
            if (count > T) {
                result.push_back(nums[i]);
            }
        }
    }

    return result;
}

int main() {
    vector<string> lines;
    string line;
    while (getline(cin, line)) {
        lines.push_back(line);
    }

    vector<vector<int>> allResults;
    for (string l : lines) {
        vector<int> nums_all = parseLine(l);
        if (nums_all.empty()) {
            allResults.emplace_back();
            continue;
        }
        int T = nums_all[0];
        vector<int> nums(nums_all.begin() + 1, nums_all.end());
        vector<int> results = function(nums, T);
        allResults.push_back(results);
    }

    for (const vector<int>& res : allResults) {
        if (res.empty()) {
            cout << "NO" << endl;
        } else {
            for (size_t i = 0; i < res.size(); ++i) {
                if (i > 0) cout << " ";
                cout << res[i];
            }
            cout << endl;
        }
    }
    return 0;
}
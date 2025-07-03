#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

struct TreeNode {
    int data;
    int frequency;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int val) : data(val), frequency(1), left(nullptr), right(nullptr) {}
};

void insert(TreeNode*& root, int num) {
    if (!root) {
        root = new TreeNode(num);
    }
    else if (num < root->data) {
        insert(root->left, num);
    }
    else if (num > root->data) {
        insert(root->right, num);
    }
    else {
        root->frequency++;
    }
}

vector<int> function(vector<int> nums, int T) {//method 3
    TreeNode* root = nullptr;
    for (int num : nums) {
        insert(root, num);
    }
    vector<int> result;
    vector<bool> added(nums.size(), false);

    for (size_t i = 0; i < nums.size(); ++i) {
        int num = nums[i];
        TreeNode* current = root;
        int freq = 0;
        while (current) {
            if (num < current->data) {
                current = current->left;
            }
            else if (num > current->data) {
                current = current->right;
            }
            else {
                freq = current->frequency;
                break;
            }
        }
        if (freq > T && !added[i]) {
            result.push_back(num);
            for (size_t j = i; j < nums.size(); ++j) {
                if (nums[j] == num) {
                    added[j] = true;
                }
            }
        }
    }

    return result;
}


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
        }
        else {
            for (size_t i = 0; i < res.size(); ++i) {
                if (i > 0) cout << " ";
                cout << res[i];
            }
            cout << endl;
        }
    }
    return 0;
}
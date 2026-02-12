#include <bits/stdc++.h>
using namespace std;

/* ================= BINARY TREE ================= */

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = right = NULL;
    }
};

int height(Node* root) {
    if (!root) return 0;
    return 1 + max(height(root->left), height(root->right));
}

void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

/* ================= SLIDING WINDOW ================= */
// Longest substring with at most k distinct characters

int longestSubstring(string s, int k) {
    unordered_map<char,int> mp;
    int left = 0, ans = 0;

    for(int right = 0; right < s.size(); right++) {
        mp[s[right]]++;

        while(mp.size() > k) {
            mp[s[left]]--;
            if(mp[s[left]] == 0)
                mp.erase(s[left]);
            left++;
        }

        ans = max(ans, right - left + 1);
    }
    return ans;
}

/* ================= DIJKSTRA GRAPH ================= */

vector<int> dijkstra(int V, vector<vector<pair<int,int>>> &adj, int src) {
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    vector<int> dist(V, INT_MAX);

    dist[src] = 0;
    pq.push({0, src});

    while(!pq.empty()) {
        auto [d, node] = pq.top();
        pq.pop();

        for(auto &it : adj[node]) {
            int next = it.first;
            int weight = it.second;

            if(dist[node] + weight < dist[next]) {
                dist[next] = dist[node] + weight;
                pq.push({dist[next], next});
            }
        }
    }

    return dist;
}

/* ================= DYNAMIC PROGRAMMING ================= */
// 0/1 Knapsack

int knapsack(vector<int>& wt, vector<int>& val, int W) {
    int n = wt.size();
    vector<vector<int>> dp(n+1, vector<int>(W+1, 0));

    for(int i=1;i<=n;i++) {
        for(int w=0;w<=W;w++) {
            if(wt[i-1] <= w)
                dp[i][w] = max(val[i-1] + dp[i-1][w-wt[i-1]], dp[i-1][w]);
            else
                dp[i][w] = dp[i-1][w];
        }
    }
    return dp[n][W];
}

/* ================= BACKTRACKING ================= */
// Generate all subsets

void generateSubsets(vector<int>& nums, vector<int>& temp, int index) {
    if(index == nums.size()) {
        for(int x : temp) cout << x << " ";
        cout << endl;
        return;
    }

    temp.push_back(nums[index]);
    generateSubsets(nums, temp, index + 1);

    temp.pop_back();
    generateSubsets(nums, temp, index + 1);
}

/* ================= MAIN ================= */

int main() {

    // Tree
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);

    cout << "Tree Height: " << height(root) << endl;
    cout << "Inorder: ";
    inorder(root);
    cout << endl;

    // Sliding Window
    string s = "aaabbcc";
    cout << "Longest substring: " << longestSubstring(s, 2) << endl;

    // Graph
    int V = 3;
    vector<vector<pair<int,int>>> adj(V);
    adj[0].push_back({1,4});
    adj[0].push_back({2,1});
    adj[2].push_back({1,2});

    vector<int> dist = dijkstra(V, adj, 0);
    cout << "Dijkstra Distances: ";
    for(int d : dist) cout << d << " ";
    cout << endl;

    // DP Knapsack
    vector<int> wt = {1,3,4,5};
    vector<int> val = {1,4,5,7};
    cout << "Knapsack Result: " << knapsack(wt, val, 7) << endl;

    // Backtracking
    vector<int> nums = {1,2,3};
    vector<int> temp;
    cout << "Subsets:\n";
    generateSubsets(nums, temp, 0);

    return 0;
}

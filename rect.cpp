#include <vector>
#include <unordered_map>

using namespace std;i

long long len(vector<pair<int, int>>& curr) {
    long long res = 0;
    long long l = INT_MIN;
    long long r = INT_MIN;
    for(auto& e: curr) {
        if(e.first > r) {
            res += (long long)(r - l);
            l = e.first;
            r = e.second;
        } else {
            r = max(r, e.second);
        }
    }
    res += (long long)(r - l);
    return res;
}

void update(unordered_map<int, vector<pair<int, int>>>& left, unordered_map<int, vector<pair<int, int>>>& right, vector<pair<int, int>>& curr, int x) {
    vector<pair<int, int>> removed;
    int i = 0;
    int j = 0;
    while(i < curr.size() || j < right[x].size()) {
        if(j == right[x].size()) {
            removed.push_back(curr[i++]);
        } else {
            if(curr[i] == right[x][j]) {
                i++;
                j++;
            } else {
                removed.push_back(curr[i++]);
            }
        }
    }
    vector<pair<int, int>> added;
    i = 0;
    j = 0;
    while(i < removed.size() || j < left[x].size()) {
        if(i == removed.size()) added.push_back(left[x][j++]);
        else if(j == left[x].size()) added.push_back(removed[i++]);
        else {
            if(removed[i] < left[x][j]) added.push_back(removed[i++]);
            else added.push_back(left[x][j++]);
        }
    }
    swap(added, curr);
}

int area(vector<vector<int>>& rects) {
    unordered_map<int, vector<pair<int, int>>> left;
    unordered_map<int, vector<pair<int, int>>> right;
    vector<int> xTemp;
    long long c = 1000000007;
    for(auto& r: rects) {
        int x1 = r[0];
        int y1 = r[1];
        int x2 = r[2];
        int y2 = r[3];
        left[x1].push_back(make_pair(y1, y2));
        right[x2].push_back(make_pair(y1, y2));
        xTemp.push_back(x1);
        xTemp.push_back(x2);
    }
    unordered_set<int> x(xTemp.begin(), xTemp.end());
    for(auto it = left.begin(); it != left.end(); it++) sort(it->second.begin(), it->second.end());
    for(auto it = right.begin(); it != right.end(); it++) sort(it->second.begin(), it->second.end());
    vector<pair<int, int>> curr;
    int prev = INT_MIN;
    long long res = 0;
    bool first = true;
    for(auto it = x.begin(); it != x.end(); it++) {
        res += (long long)(*it - prev) * len(curr);
        res %= c;
        update(left, right, prev, *it);
    }
    return res;
}

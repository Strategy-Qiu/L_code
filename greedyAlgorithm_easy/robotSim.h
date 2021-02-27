#pragma once
#include<vector>
#include<iostream>
#include<unordered_set>
using namespace std;
//需要使用集合SET作为对障碍物使用得数据结构，以便我们可以有效地检查下一步是否受损
class Solution {
private:
    struct pair_hash
    {
        template <class T1, class T2>
        std::size_t operator () (std::pair<T1, T2> const& pair) const
        {
            std::size_t h1 = std::hash<T1>()(pair.first);
            std::size_t h2 = std::hash<T2>()(pair.second);

            return h1 ^ h2;
        }
    };
public:
    int robotSim(vector<int>& commands, vector<vector<int>>& obstacles) {
        int dx[4] = { 0, 1, 0, -1 };//各个方向上的位移
        int dy[4] = { 1, 0, -1, 0 };
        int x = 0, y = 0, di = 0;
        unordered_set<pair<int, int>, pair_hash> obstacleSet;
        for (vector<int> obstacle : obstacles)
            obstacleSet.insert(make_pair(obstacle[0], obstacle[1]));

        int ans = 0;
        for (int cmd : commands) {
            if (cmd == -2)
                di = (di + 3) % 4;
            else if (cmd == -1)
                di = (di + 1) % 4;
            else {
                for (int k = 0; k < cmd; ++k) {
                    int nx = x + dx[di];
                    int ny = y + dy[di];
                    //find函数如果找不到会返回一个指向容器中最后一个元素的迭代器
                    if (obstacleSet.find(make_pair(nx, ny)) == obstacleSet.end()) 
                    {
                        x = nx;
                        y = ny;
                        ans = max(ans, x * x + y * y);
                    }
                }
            }
        }
        return ans;
    }
};

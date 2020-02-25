#include<string>
#include<vector>

using namespace std;

class Solution {
public:
    bool robot(string command, vector<vector<int>>& obstacles, int x, int y) {
        int u_count = 0;
        int r_count = 0;
        for (char c : command)
        {
            if (c == 'U')
            {
                ++u_count;
            }

            if (c == 'R')
            {
                ++r_count;
            }
        }

        for (vector<int> obstacle : obstacles)
        {
            int m_x = obstacle[0];
            int m_y = obstacle[1];

            if (m_x >= x || m_y >= y)
            {
                continue;
            }

            if (is_on_the_path(m_x, m_y, u_count, r_count, command))
            {
                return false;
            }
        }

        return is_on_the_path(x, y, u_count, r_count, command);
    }

    bool is_on_the_path(int x, int y, int u_count, int r_count, string& command)
    {
        int count = (x + y) / command.size();
        int left_count = (x + y) % command.size();

        int left_u_count = 0;
        int left_r_count = 0;
        for (int i = 0; i < left_count; ++i)
        {
            if (command[i] == 'U')
            {
                ++left_u_count;
            }

            if (command[i] == 'R')
            {
                ++left_r_count;
            }
        }

        int total_u_count = left_u_count + count * u_count;
        int total_r_count = left_r_count + count * r_count;

        return total_u_count == y &&
            total_r_count == x;
    }
};
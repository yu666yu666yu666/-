#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

class KnightTour {
public:
    KnightTour() {
        board.resize(8, std::vector<int>(8, -1));
        moves = {{2, 1}, {1, 2}, {-1, 2}, {-2, 1},
                 {-2, -1}, {-1, -2}, {1, -2}, {2, -1}};
    }

    std::vector<std::pair<int, int>> startTour(int startX = 0, int startY = 0) {
        board[startX][startY] = 0; // 从给定位置开始
        std::vector<std::pair<int, int>> path; // 存储路径坐标
        path.emplace_back(startX, startY); // 添加起始位置

        if (!solveKnightTour(startX, startY, 1, path)) {
            std::cout << "没有找到解决方案\n";
            return {}; // 返回空数组表示没有解决方案
        } 
        
        return path; // 返回坐标路径
    }

private:
    std::vector<std::vector<int>> board;
    std::vector<std::pair<int, int>> moves;

    bool isSafe(int x, int y) {
        return (x >= 0 && x < 8 && y >= 0 && y < 8 && board[x][y] == -1);
    }

    bool solveKnightTour(int x, int y, int moveCount, std::vector<std::pair<int, int>>& path) {
        if (moveCount == 64) { // 所有方格都被访问
            return true;
        }

        for (const auto& move : moves) {
            int nextX = x + move.first;
            int nextY = y + move.second;
            if (isSafe(nextX, nextY)) {
                board[nextX][nextY] = moveCount;
                path.emplace_back(nextX, nextY); // 添加当前坐标到路径
                if (solveKnightTour(nextX, nextY, moveCount + 1, path)) {
                    return true;
                }
                board[nextX][nextY] = -1; // 回溯
                path.pop_back(); // 移除最后一步坐标
            }
        }

        return false;
    }
};

int main() {
    KnightTour knightTour;
    srand(static_cast<unsigned int>(time(0))); // 随机数种子
    int start_x = rand() % 8; // 随机起始位置
    int start_y = rand() % 8;

    // 获取路径坐标
    std::vector<std::pair<int, int>> result = knightTour.startTour(start_x, start_y);

    // 打印路径坐标
    if (!result.empty()) {
        std::cout << "路径坐标：\n";
        for (const auto& coord : result) {
            std::cout << "(" << coord.first << ", " << coord.second << ")\n";
        }
    }

    return 0;
}
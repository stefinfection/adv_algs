#include <iostream>
#include <random>

int main() {
    int t = 16e4;
    int runs = 50;

    //Create distribution to randomly pull from
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(-1, 1);

    int total_cross_count = 0;
    for (int i = 0; i < runs; i++) {
        int cross_count = 0;
        int x = 0;
        for (int j = 0; j < t; j++) {
            // Move x
            int delta = dist(gen);
            x += delta;

            if (x == 0) {
                cross_count++;
            }
        }
        std::cout << cross_count << std::endl;
        total_cross_count += cross_count;
    }
    std::cout << "Average cross count for t=" << std::to_string(t) << ": "
              << std::to_string(total_cross_count/runs) << std::endl;
    return 0;
}

#include <iostream>
#include <algorithm>
#include <random>

// Random reading sourced from here:
// https://stackoverflow.com/questions/19665818/generate-random-numbers-using-c11-random-library

int main() {
    int SAMPLE_SIZE = 400;
    int REPEAT = 100;

    // Create array with 1M entries: 52%+ 48%-
    int samples[1000000];
    for (auto i = 0; i < 520000; i++) {
        samples[i] = 1;
    }
    for (int i = 520000; i < 1000000; i++) {
        samples[i] = -1;
    }

    // Shuffle array
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(&samples[0], &samples[999999], gen);

    // Create distribution to pull random index from
    std::uniform_int_distribution<int> dist(0, 999999);

    int totals[] = {0,0}; // -1, +1
    for (int i = 0; i < REPEAT; i++) {
        // Count +/- in each random selection and report
        int counts[] = {0,0};
        for (int j = 0; j < SAMPLE_SIZE; j++) {
            int rand_idx = dist(gen);
            if (samples[rand_idx] < 0) {
                counts[0]++;
            } else {
                counts[1]++;
            }
        }
        totals[0] += counts[0];
        totals[1] += counts[1];
    }
    std::cout << totals[0] << " " << totals[1] << std::endl;
    std::cout << "Averages for " + std::to_string(SAMPLE_SIZE) + " random picks: " << std::endl;
    std::cout << std::to_string(totals[0]/SAMPLE_SIZE) + " -1s" << std::endl;
    std::cout << std::to_string(totals[1]/SAMPLE_SIZE) + " +1s" << std::endl;
    return 0;
}

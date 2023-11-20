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

    int plus_maj_count = 0;
    for (int i = 0; i < REPEAT; i++) {
        // Count +/- in each random selection and report
        int plus_count = 0;
        for (int j = 0; j < SAMPLE_SIZE; j++) {
            int rand_idx = dist(gen);
            if (samples[rand_idx] > 0) {
                plus_count++;
            }
        }
        std::cout << plus_count << std::endl;
        if (plus_count > SAMPLE_SIZE / 2) {
            plus_maj_count++;
        }
    }

    float prob = (float)plus_maj_count/(float)REPEAT;
    std::cout << "Probability of +1 majority for " + std::to_string(SAMPLE_SIZE) + " random picks: " << std::endl;
    std::cout << std::to_string((int)(prob * 100)) << "%" << std::endl;
    return 0;
}

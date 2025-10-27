#include <random>

double dboard(size_t darts, std::random_device& rd) {
    size_t count = 0;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0., 1.);

    for (auto i = 0u; i < darts; ++i) {
        double draw_x = dis(gen);
        double draw_y = dis(gen);
        if (std::sqrt(std::pow(draw_x, 2) + std::pow(draw_y, 2)) < 1) {
            ++count;
        }
    }

    return static_cast<double>(count) / static_cast<double>(darts) * 4.;
}

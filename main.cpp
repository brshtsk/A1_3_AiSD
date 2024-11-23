#include <fstream>
#include <random>
#include <cmath>

std::mt19937 gen(42);

double randomNum(double a, double b) { // Возвращаем случайное число в диапазоне [a, b]
  std::uniform_real_distribution<> distr(a, b);
  return distr(gen);
}

// Перменные с границами рассматриваемой области
double max_x = -std::numeric_limits<double>::infinity();
double min_x = std::numeric_limits<double>::infinity();
double max_y = -std::numeric_limits<double>::infinity();
double min_y = std::numeric_limits<double>::infinity();

struct Round { // Класс, описывающий круг
  Round(double x, double y, double r) : x(x), y(y), r(r) {
    if (x + r > max_x) max_x = x + r;
    if (x - r < min_x) min_x = x - r;
    if (y + r > max_y) max_y = y + r;
    if (y - r < min_y) min_y = y - r;
  }
  bool contains(double x, double y) const { // Проверяем, содержит ли круг точку с координатами (x, y)
    return (x - this->x) * (x - this->x) + (y - this->y) * (y - this->y) <= r * r;
  }

  double x, y, r;
};

double findCrossedSpace(const Round &r1, const Round &r2, const Round &r3, double total_amount = 1000000) {
  int inside_amount = 0; // Количество точек, попавших во все три круга

  for (int i = 0; i < total_amount; ++i) {
    double rand_x = randomNum(min_x, max_x);
    double rand_y = randomNum(min_y, max_y);
    if (r1.contains(rand_x, rand_y) && r2.contains(rand_x, rand_y) && r3.contains(rand_x, rand_y)) {
      ++inside_amount; // Если точка попала во все три круга, увеличиваем счетчик
    }
  }

  double square = (max_x - min_x) * (max_y - min_y); // Площадь рассматриваемой области

  return square * inside_amount / total_amount; // Умножаем на площадь долю попавших точек
}

int main() {
  std::ofstream outfile("results.txt");

  Round r1(1, 1, 1);
  Round r2(1.5, 2, std::sqrt(5) / 2);
  Round r3(2, 1.5, std::sqrt(5) / 2);

  for (int n = 100; n <= 100000; n += 500) {
    outfile << n << "\t" << findCrossedSpace(r1, r2, r3, n) << std::endl;
  }

  outfile.close();
}
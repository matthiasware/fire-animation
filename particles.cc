#include <SFML/Graphics.hpp>
#include <algorithm>
#include <iostream>
#include <random>
#include <unordered_map>
#include <vector>

// http://fabiensanglard.net/doom_fire_psx/index.html

const std::vector<sf::Color> cv{
    sf::Color(0x07, 0x07, 0x07), sf::Color(0x1F, 0x07, 0x07),
    sf::Color(0x2F, 0x0F, 0x07), sf::Color(0x47, 0x0F, 0x07),
    sf::Color(0x57, 0x17, 0x07), sf::Color(0x67, 0x1F, 0x07),
    sf::Color(0x77, 0x1F, 0x07), sf::Color(0x8F, 0x27, 0x07),
    sf::Color(0x9F, 0x2F, 0x07), sf::Color(0xAF, 0x3F, 0x07),
    sf::Color(0xBF, 0x47, 0x07), sf::Color(0xC7, 0x47, 0x07),
    sf::Color(0xDF, 0x4F, 0x07), sf::Color(0xDF, 0x57, 0x07),
    sf::Color(0xDF, 0x57, 0x07), sf::Color(0xD7, 0x5F, 0x07),
    sf::Color(0xD7, 0x5F, 0x07), sf::Color(0xD7, 0x67, 0x0F),
    sf::Color(0xCF, 0x6F, 0x0F), sf::Color(0xCF, 0x77, 0x0F),
    sf::Color(0xCF, 0x7F, 0x0F), sf::Color(0xCF, 0x87, 0x17),
    sf::Color(0xC7, 0x87, 0x17), sf::Color(0xC7, 0x8F, 0x17),
    sf::Color(0xC7, 0x97, 0x1F), sf::Color(0xBF, 0x9F, 0x1F),
    sf::Color(0xBF, 0x9F, 0x1F), sf::Color(0xBF, 0xA7, 0x27),
    sf::Color(0xBF, 0xA7, 0x27), sf::Color(0xBF, 0xAF, 0x2F),
    sf::Color(0xB7, 0xAF, 0x2F), sf::Color(0xB7, 0xB7, 0x2F),
    sf::Color(0xB7, 0xB7, 0x37), sf::Color(0xCF, 0xCF, 0x6F),
    sf::Color(0xDF, 0xDF, 0x9F), sf::Color(0xEF, 0xEF, 0xC7),
    sf::Color(0xFF, 0xFF, 0xFF)};

std::unordered_map<unsigned int, int> um{
    {117901311, 0},   {520554495, 1},   {789514239, 2},   {1192167423, 3},
    {1461127167, 4},  {1730086911, 5},  {1998522367, 6},  {2401699839, 7},
    {2670659583, 8},  {2940143615, 9},  {3209103359, 10}, {3343321087, 11},
    {3746498559, 12}, {3747022847, 13}, {3747022847, 14}, {3613329407, 15},
    {3613329407, 16}, {3613855743, 17}, {3480162303, 18}, {3480686591, 19},
    {3481210879, 20}, {3481737215, 21}, {3347519487, 22}, {3348043775, 23},
    {3348570111, 24}, {3214876671, 25}, {3214876671, 26}, {3215403007, 27},
    {3215403007, 28}, {3215929343, 29}, {3081711615, 30}, {3082235903, 31},
    {3082237951, 32}, {3486478335, 33}, {3755974655, 34}, {4025468927, 35},
    {4294967295, 36}};

void doFire(std::vector<sf::Vertex> &pixMat, int W, int H) {
  for (int x = 0; x < W; ++x) {
    for (int y = H - 1; y >= 1; --y) {
      int dest = y * W + x;
      int src = (dest - (rand() % 2) * W) - (rand() % 3) + 1;

      int color_index = um[pixMat[src].color.toInteger()];
      color_index = color_index - (rand() & 1);
      color_index = std::max(color_index, 0);
      pixMat[dest].color = cv[color_index];
    }
  }
}
int main() {
  const int H = 400;
  const int W = 500;

  sf::RenderTexture RT;
  RT.create(W, H);

  sf::RenderWindow window(sf::VideoMode(W, H, 32), "Test");
  window.setFramerateLimit(30);

  // Creates the sf::Vertex matrix
  std::vector<sf::Vertex> pixMat(H * W);

  for (int x = 0; x < W; ++x)
    for (int y = 0; y < H; ++y) {
      sf::Color c = (y == 0) ? cv[cv.size() - 1] : cv[0];
      pixMat[(y * W + x)] = sf::Vertex(sf::Vector2f(x, y), c);
    }

  int counter = 100;
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }
    doFire(pixMat, W, H);

    RT.draw(pixMat.data(), H * W, sf::Points);

    window.clear();
    window.draw(sf::Sprite(RT.getTexture()));
    window.display();
    if (!--counter) {
      for (int x = 0; x < W; ++x)
        pixMat[x] = sf::Vertex(sf::Vector2f(x, 0), cv[0]);
    }
  }
}
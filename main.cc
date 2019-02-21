#include <SFML/Graphics.hpp>
#include <random>
#include <unordered_map>
#include <vector>
#include <iostream>

const std::vector<sf::Color> cv{
    sf::Color(0xFF, 0xFF, 0xFF), sf::Color(0xEF, 0xEF, 0xC7),
    sf::Color(0xDF, 0xDF, 0x9F), sf::Color(0xCF, 0xCF, 0x6F),
    sf::Color(0xB7, 0xB7, 0x37), sf::Color(0xB7, 0xB7, 0x2F),
    sf::Color(0xB7, 0xAF, 0x2F), sf::Color(0xBF, 0xAF, 0x2F),
    sf::Color(0xBF, 0xA7, 0x27), sf::Color(0xBF, 0xA7, 0x27),
    sf::Color(0xBF, 0x9F, 0x1F), sf::Color(0xBF, 0x9F, 0x1F),
    sf::Color(0xC7, 0x97, 0x1F), sf::Color(0xC7, 0x8F, 0x17),
    sf::Color(0xC7, 0x87, 0x17), sf::Color(0xCF, 0x87, 0x17),
    sf::Color(0xCF, 0x7F, 0x0F), sf::Color(0xCF, 0x77, 0x0F),
    sf::Color(0xCF, 0x6F, 0x0F), sf::Color(0xD7, 0x67, 0x0F),
    sf::Color(0xD7, 0x5F, 0x07), sf::Color(0xD7, 0x5F, 0x07),
    sf::Color(0xDF, 0x57, 0x07), sf::Color(0xDF, 0x57, 0x07),
    sf::Color(0xDF, 0x4F, 0x07), sf::Color(0xC7, 0x47, 0x07),
    sf::Color(0xBF, 0x47, 0x07), sf::Color(0xAF, 0x3F, 0x07),
    sf::Color(0x9F, 0x2F, 0x07), sf::Color(0x8F, 0x27, 0x07),
    sf::Color(0x77, 0x1F, 0x07), sf::Color(0x67, 0x1F, 0x07),
    sf::Color(0x57, 0x17, 0x07), sf::Color(0x47, 0x0F, 0x07),
    sf::Color(0x2F, 0x0F, 0x07), sf::Color(0x1F, 0x07, 0x07),
    sf::Color(0x07, 0x07, 0x07)
};

std::unordered_map<unsigned int, int> um{
    {117901311, 36},
    {520554495, 35},  {789514239, 34},  {1192167423, 33},
    {1461127167, 32}, {1730086911, 31}, {1998522367, 30}, {2401699839, 29},
    {2670659583, 28}, {2940143615, 27}, {3209103359, 26}, {3343321087, 25},
    {3746498559, 24}, {3747022847, 23}, {3747022847, 22}, {3613329407, 21},
    {3613329407, 20}, {3613855743, 19}, {3480162303, 18}, {3480686591, 17},
    {3481210879, 16}, {3481737215, 15}, {3347519487, 14}, {3348043775, 13},
    {3348570111, 12}, {3214876671, 11}, {3214876671, 10}, {3215403007, 9},
    {3215403007, 8},  {3215929343, 7},  {3081711615, 6},  {3082235903, 5},
    {3082237951, 4},  {3486478335, 3},  {3755974655, 2},  {4025468927, 1},
    {4294967295, 0}};

template<int W, int H>
void spredFire(std::vector<sf::Vertex> &pixMat, int dest)
{
  int src = (dest - (rand() % 2) * W) - (rand() % 3) + 1;

  int color = um[pixMat[src].color.toInteger()];
  color = color + (rand() & rand() & rand() & 1);
  color = std::min(color, static_cast<int>(cv.size()) - 1);
  pixMat[dest].color = cv[color];
}

template<int W, int H>
void doFire(std::vector<sf::Vertex> &pixMat) {
  for (int x = 0; x < W; ++x) {
    for (int y = 1; y < H; y++) {
      spredFire<W, H>(pixMat, y * W + x);
    }
  }
}
int main() {
  const int H = 400;
  const int W = 400;

  sf::RenderTexture RT;
  RT.create(W, H);
  RT.setSmooth(true);
  
  sf::Texture doomLogoTexture;
  doomLogoTexture.loadFromFile("img/d00m.png");
  doomLogoTexture.setSmooth(true);

  sf::Sprite sprite;
  sprite.setTexture(doomLogoTexture);

  sf::RenderWindow window(sf::VideoMode(W, H, 32), "Doom Fire");
  window.setFramerateLimit(60);

  std::vector<sf::Vertex> pixMat(H * W);

  for (int x = 0; x < W; ++x)
    for (int y = 0; y < H; ++y) {
      sf::Color c = (y == 0) ? cv[0] : cv.back();
      pixMat[(y * W + x)] = sf::Vertex(sf::Vector2f(x, y), c);
    }

  int max_frames = 150;
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    doFire<W, H>(pixMat);

    RT.draw(pixMat.data(), H * W, sf::Points);

    window.clear();

    window.draw(sf::Sprite(RT.getTexture()));
    window.draw(sprite);

    window.display();
    
    if (!--max_frames) {
      for (int x = 0; x < W; ++x)
        for(int y = 0; y < 10; ++y)
            pixMat[x] = sf::Vertex(sf::Vector2f(x, y), cv.back());
    }
  }
}
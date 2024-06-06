#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <chrono>

// Clase PerlinNoise
class PerlinNoise {
public:
    PerlinNoise(unsigned int seed) {
        p.resize(256);
        std::iota(p.begin(), p.end(), 0);
        std::default_random_engine engine(seed);
        std::shuffle(p.begin(), p.end(), engine);
        p.insert(p.end(), p.begin(), p.end());
    }

    double noise(double x, double y, double z) const {
        int X = static_cast<int>(std::floor(x)) & 255;
        int Y = static_cast<int>(std::floor(y)) & 255;
        int Z = static_cast<int>(std::floor(z)) & 255;

        x -= std::floor(x);
        y -= std::floor(y);
        z -= std::floor(z);

        double u = fade(x);
        double v = fade(y);
        double w = fade(z);

        int A = p[X] + Y;
        int AA = p[A] + Z;
        int AB = p[A + 1] + Z;
        int B = p[X + 1] + Y;
        int BA = p[B] + Z;
        int BB = p[B + 1] + Z;

        return lerp(w, lerp(v, lerp(u, grad(p[AA], x, y, z),
                                     grad(p[BA], x - 1, y, z)),
                             lerp(u, grad(p[AB], x, y - 1, z),
                                  grad(p[BB], x - 1, y - 1, z))),
                    lerp(v, lerp(u, grad(p[AA + 1], x, y, z - 1),
                                 grad(p[BA + 1], x - 1, y, z - 1)),
                         lerp(u, grad(p[AB + 1], x, y - 1, z - 1),
                              grad(p[BB + 1], x - 1, y - 1, z - 1))));
    }

private:
    std::vector<int> p;

    double fade(double t) const {
        return t * t * t * (t * (t * 6 - 15) + 10);
    }

    double lerp(double t, double a, double b) const {
        return a + t * (b - a);
    }

    double grad(int hash, double x, double y, double z) const {
        int h = hash & 15;
        double u = h < 8 ? x : y;
        double v = h < 4 ? y : (h == 12 || h == 14 ? x : z);
        return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
    }
};

std::vector<std::vector<int>> generateWorld(int width, int height, const PerlinNoise& perlin) {
    std::vector<std::vector<int>> world(height, std::vector<int>(width, 0));

    int groundHeight = height / 1.1 ; //La altura del piso

    //Crear mundo superficial
    for (int x = 0; x < width; ++x) {
        double nx = static_cast<double>(x) / width;
        double elevation = perlin.noise(12 * nx, 0, 0);
        int columnHeight = static_cast<int>((elevation + 1) * groundHeight / 5) + groundHeight / 5;

        for (int y = 0; y < height; ++y) {
            if (y < columnHeight) {
                world[y][x] = 0; // Aire
            } else if (y < columnHeight + 5) {
                world[y][x] = 1; // Tierra
            } else {
                world[y][x] = 2; // Piedra
            }
        }
    }

    // Generación de cuevas usando Cellular Automata
    unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> distribution(0, 80);

    // Inicializar mapa de cuevas
    std::vector<std::vector<int>> caveMap(height, std::vector<int>(width, 1));
    for (int y = 1; y < height - 1; ++y) {
        for (int x = 1; x < width - 1; ++x) {
            if (distribution(generator) < 45 && world[y][x] != 1 ) {
                caveMap[y][x] = 0; // Espacio vacío
            }
        }
    }

    // Aplicar reglas del Cellular Automata
    for (int i = 0; i < 5; ++i) {
        std::vector<std::vector<int>> newCaveMap = caveMap;
        for (int y = 1; y < height - 1; ++y) {
            for (int x = 1; x < width - 1; ++x) {
                int neighborWallCount = 0;
                for (int ny = -1; ny <= 1; ++ny) {
                    for (int nx = -1; nx <= 1; ++nx) {
                        if (caveMap[y + ny][x + nx] == 1) {
                            neighborWallCount++;
                        }
                    }
                }
                if (neighborWallCount > 4) {
                    newCaveMap[y][x] = 1;
                } else if (neighborWallCount < 4) {
                    newCaveMap[y][x] = 0;
                }
            }
        }
        caveMap = newCaveMap;
    }

    // Integrar mapa de cuevas en el mundo
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (caveMap[y][x] == 0) {
                world[y][x] = 0; // Crear espacio vacío en el terreno
            }
        }
    }

    return world;
}

int main() {
    int width = 800;
    int height = 600;
    sf::RenderWindow window(sf::VideoMode(width, height), "Mundo Procedural Tipo Terraria");

    // Usar la hora actual como semilla para hacer la generación aleatoria
    unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
    PerlinNoise perlin(seed);

    // Generar el mundo
    auto world = generateWorld(width/3, height/3, perlin); // Reducir la resolución del terreno

    // Texturas para el mundo
    

    sf::RectangleShape pixel(sf::Vector2f(3, 3));

    // Bucle principal
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        // Dibujar el mundo
        for (int y = 0; y < height/3; ++y) {
            for (int x = 0; x < width/3; ++x) {
                pixel.setPosition(x*4, y*4);
                if (world[y][x] == 1) {
                    pixel.setFillColor(sf::Color::Green);
                } else if (world[y][x] == 2) {
                    pixel.setFillColor(sf::Color::Blue);
                } else {
                    pixel.setTexture(nullptr);
                    pixel.setFillColor(sf::Color::Transparent);
                }
                window.draw(pixel);
            }
        }

        window.display();
    }

    return 0;
}

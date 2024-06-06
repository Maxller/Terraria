#pragma once
#include <ChatGPT/PerlinNoise.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

class Mundo
{
private:
    PerlinNoise *perlin;
    std::vector<std::vector<int>> World;
    /* data */
public:
    Mundo(/* args */) {
        unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
        perlin = new PerlinNoise(seed);
    }
    void CrearMundo(int heigth, int width,std::string NombreMundo)
    {
        std::vector<std::vector<int>> world(heigth, std::vector<int>(width, 1));
        int groundheigth = heigth / 1.1; // La altura del piso
        
        // Crear mundo superficial
        for (int x = 0; x < width; ++x)
        {
            double nx = static_cast<double>(x) / width;
            double elevation = perlin->noise(12 * nx, 0, 0);
            int columnheigth = static_cast<int>((elevation + 1) * groundheigth / 5) + groundheigth / 5;
            
            for (int y = 0; y < heigth; ++y)
            {
                if (y < columnheigth)
                {
                    world[y][x] = 0; // Aire
                }
                else if (y < columnheigth + 5)
                {
                    world[y][x] = 1; // Tierra
                }
                else
                {
                    world[y][x] = 2; // Piedra
                }
            }
        }
        
        // Generación de cuevas usando Cellular Automata
        unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::default_random_engine generator(seed);
        std::uniform_int_distribution<int> distribution(0, 80);

        // Inicializar mapa de cuevas
        std::vector<std::vector<int>> caveMap(heigth, std::vector<int>(width, 1));
        for (int y = 1; y < heigth - 1; ++y)
        {
            for (int x = 1; x < width - 1; ++x)
            {
                if (distribution(generator) < 45 && world[y][x] != 1)
                {
                    caveMap[y][x] = 0; // Espacio vacío
                }
            }
        }

        // Aplicar reglas del Cellular Automata
        for (int i = 0; i < 5; ++i)
        {
            std::vector<std::vector<int>> newCaveMap = caveMap;
            for (int y = 1; y < heigth - 1; ++y)
            {
                for (int x = 1; x < width - 1; ++x)
                {
                    int neighborWallCount = 0;
                    for (int ny = -1; ny <= 1; ++ny)
                    {
                        for (int nx = -1; nx <= 1; ++nx)
                        {
                            if (caveMap[y + ny][x + nx] == 1)
                            {
                                neighborWallCount++;
                            }
                        }
                    }
                    if (neighborWallCount > 4)
                    {
                        newCaveMap[y][x] = 1;
                    }
                    else if (neighborWallCount < 4)
                    {
                        newCaveMap[y][x] = 0;
                    }
                }
            }
            caveMap = newCaveMap;
        }
        
        // Integrar mapa de cuevas en el mundo
        for (int y = 0; y < heigth; ++y)
        {
            for (int x = 0; x < width; ++x)
            {
                if (caveMap[y][x] == 0)
                {
                    world[y][x] = 0; // Crear espacio vacío en el terreno
                }
            }
        }
        World = world;
        GuardarMundo(NombreMundo);
        
    }
    void CargarMundo(std::string NombreMundo)
    {
         std::vector<std::vector<int>> data;
        std::ifstream inFile("./Mundos/" + NombreMundo);
        if (inFile.is_open()) {
        std::string line;
        while (std::getline(inFile, line)) {
            std::vector<int> row;
            std::istringstream iss(line);
            int num;
            while (iss >> num) {
                row.push_back(num);
            }
            data.push_back(row);
        }
        inFile.close();
    } else {
        std::cerr << "No se pudo abrir el archivo para lectura "  << std::endl;
    }
    }

    void GuardarMundo(std::string NombreMundo)
    {
        std::ofstream outFile("./Mundos/" + NombreMundo);
        if (outFile.is_open())
        {
            for (const auto &row : World)
            {
                for (const auto &elem : row)
                {
                    outFile << elem << " ";
                }
                outFile << "\n";
            }
            outFile.close();
        }
        else
        {
            std::cerr << "No se pudo abrir el archivo para escritura" << std::endl;
        }
    }

    void CambiarBloqueEn(int x, int y)
    {
    }

    ~Mundo() {}
};

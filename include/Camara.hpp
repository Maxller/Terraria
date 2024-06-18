#pragma once
#include <Mundo.hpp>

class Camara
{
private:
    int width, height, posX, posY;
    std::vector<std::vector<Bloque *>> camara;
    Mundo* world;

    void getBlocksOfWorld(){
        std::vector<Bloque *> BlocksInArrary;
        for (int y = posY; y < posY + height; y++)
        {
            for (int x = posX; x < posX + width; x++)
            {
                BlocksInArrary.push_back(world->getBlockAt(x,y));
            }
            camara.push_back(BlocksInArrary);
            BlocksInArrary.clear();
            
        }
    }
public:
    static const int Derecha = -1, Izquierda = 1, Arriba = -2, Abajo = 2;

    Camara(int width, int height){
        this -> width = width;
        this -> height = height;
    }

    void cargarCamara(Mundo* mundo){
        sf::Vector2f spawnCoords = mundo ->spawnCoords();
        posX = spawnCoords.x - width/2 ;
        posY = spawnCoords.y - height/2 ;
        world = mundo;
        getBlocksOfWorld();

    }


    void moverCamara(int Direccion){
        if(Direccion == 1 || Direccion == -1){
            posX -= Direccion;
        }
        else if(Direccion == 2 || Direccion == -2){
            posY -= Direccion/2;
        }
        camara.clear();
        getBlocksOfWorld();
    }
    std::vector<std::vector<Bloque *>> getCamara(){
        return camara;
    }
    Bloque* getBlockAt(int x, int y){
        return camara[y][x];
    }
    int getWidth(){
        return width;
    }
    int getHeight(){
        return height;
    }

    ~Camara();
};


Camara::~Camara()
{
}

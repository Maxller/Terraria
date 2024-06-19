#include <Juego.hpp>

int main(int argc, char const *argv[])
{
    sf::Clock clock;
    Juego *Terraria = new Juego();

    while (Terraria->IsRunning())
    {

        // Procesar eventos
        Terraria->HandleEvent();

        if(clock.getElapsedTime().asMilliseconds() > 1.6F){
            // Actualizar la lógica del juego
            // Aquí se actualiza el estado del juego (movimiento de personajes, etc.)
            Terraria->Update();

            // Dibujar los objetos del juego
            // Aquí se dibujan los objetos del juego (sprites, etc.)
            Terraria->Render();
            clock.restart();
        }
    }
    // Limpiar y liberar recursos (si es necesario)
    delete Terraria;
    return 0;
}

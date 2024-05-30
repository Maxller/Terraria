#include <Juego.hpp>


int main(int argc, char const *argv[])
{
    Juego* Terraria = new Juego(); 

    while (Terraria -> IsRunning())
    {
        
        // Procesar eventos
        Terraria -> HandleEvent();

        // Actualizar la lógica del juego
        // Aquí se actualiza el estado del juego (movimiento de personajes, etc.)
        Terraria -> Update();
        // Limpiar la ventana
        

        // Dibujar los objetos del juego
        // Aquí se dibujan los objetos del juego (sprites, etc.)
        Terraria -> Render();
        
    }
    // Limpiar y liberar recursos (si es necesario)
    delete Terraria;
    return 0;
}

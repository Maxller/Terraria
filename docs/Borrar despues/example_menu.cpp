#include <SFML/Graphics.hpp>
#include <iostream>

class Button
{
public:
    Button(const std::string &text, const sf::Font &font, int XPos, int YPos)
    {
        buttonText.setFont(font);
        buttonText.setString(text);
        buttonText.setCharacterSize(66);
        buttonText.setFillColor(sf::Color::White);
        buttonText.setPosition((XPos / 2) - (buttonText.getGlobalBounds().width / 2), YPos);
    }

    void draw(sf::RenderWindow &window)
    {
        window.draw(buttonText);
    }

    bool isMouseOver(sf::RenderWindow &window)
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::FloatRect buttonRect = buttonText.getGlobalBounds();
        return buttonRect.contains(static_cast<sf::Vector2f>(mousePos));
    }

    void setFillColor(sf::Color Color)
    {
        buttonText.setFillColor(Color);
    }

    void setPosition( int XPos, int YPos){
        buttonText.setPosition((XPos / 2) - (buttonText.getGlobalBounds().width / 2), YPos);
    }

private:
    sf::Text buttonText;
};

int main()
{
    int heigth = 600, width = 800;
    sf::RenderWindow window(sf::VideoMode(width, heigth), "Game Menu",sf::Style::Titlebar | sf::Style::Close);
    sf::Font font;

    if (!font.loadFromFile("./assets/Andy.ttf"))
    {
        std::cerr << "Error loading font\n";
        return -1;
    }
    sf::Texture logoTexture;
    if (!logoTexture.loadFromFile("./assets/custom-terraria-logo.png"))
    {
        std::cerr << "Error loading logo image\n";
        return -1;
    }
    sf::Sprite logoSprite;
    logoSprite.setTexture(logoTexture);
    logoSprite.setScale(1, 1);
    logoSprite.setPosition((width / 2) - (logoSprite.getGlobalBounds().width / 2), 50);

    Button playButton("Jugar", font, width, (heigth / 2) - 100);
    Button optionsButton("Opciones", font, width, (heigth / 2));
    Button exitButton("Salir", font, width, (heigth / 2) + 100);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (playButton.isMouseOver(window))
                {
                    std::cout << "Jugar presionado\n";
                    // Aquí se debe añadir la lógica para iniciar el juego
                }
                if (optionsButton.isMouseOver(window))
                {
                    std::cout << "Opciones presionado\n";
                    // Aquí se debe añadir la lógica para abrir las opciones
                }
                if (exitButton.isMouseOver(window))
                {
                    window.close();
                }
            }
        }

        if (playButton.isMouseOver(window))
            playButton.setFillColor(sf::Color::Green);
        else
            playButton.setFillColor(sf::Color::Cyan);

        if (optionsButton.isMouseOver(window))
            optionsButton.setFillColor(sf::Color::Green);
        else
            optionsButton.setFillColor(sf::Color::Cyan);

        if (exitButton.isMouseOver(window))
            exitButton.setFillColor(sf::Color::Green);
        else
            exitButton.setFillColor(sf::Color::Cyan);

        window.clear();
        window.draw(logoSprite);
        playButton.draw(window);
        optionsButton.draw(window);
        exitButton.draw(window);
        window.display();
    }

    return 0;
}

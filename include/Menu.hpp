#include <SFML/Graphics.hpp>
#include <iostream>

class Menu
{
private:
    class Button
    {
    private:
        sf::Text buttonText;

    public:
        Button(const std::string &text, const sf::Font &font, int width, int YPos)
        {
            buttonText.setFont(font);
            buttonText.setString(text);
            buttonText.setCharacterSize(66);
            buttonText.setFillColor(sf::Color::White);
            buttonText.setPosition((width / 2) - (buttonText.getGlobalBounds().width / 2), YPos);
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
    };
    Button *playButton;
    Button *optionsButton;
    Button *exitButton;
    sf::Texture logoTexture, backTexture;
    sf::Font font;
    sf::Sprite logoSprite, backSprite;

public:
    Menu(int width, int heigth)
    {

        if (!font.loadFromFile("./assets/Andy.ttf"))
        {
            std::cerr << "Error loading font\n";
        }

        if (!logoTexture.loadFromFile("./assets/custom-terraria-logo.png"))
        {
            std::cerr << "Error loading logo image\n";
        }
        if (backTexture.loadFromFile("./assets/Splash_9_0.png"))
            {
            std::cerr << "Error loading logo image\n";
            }

        logoSprite.setTexture(logoTexture);
        backSprite.setTexture(backTexture);
        logoSprite.setPosition((width / 2) - (logoSprite.getGlobalBounds().width / 2), 50);

        playButton = new Button("Jugar", font, width, (heigth / 2) - 100);
        optionsButton = new Button("Opciones", font, width, (heigth / 2));
        exitButton = new Button("Salir", font, width, (heigth / 2) + 100);
    }

    int displayMenu(sf::RenderWindow &window)
    {
        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                    return 0;
                }

                if (event.type == sf::Event::MouseButtonPressed)
                {
                    if (playButton->isMouseOver(window))
                    {
                        std::cout << "Jugar presionado\n";
                        return 1;
                    }
                    if (optionsButton->isMouseOver(window))
                    {
                        std::cout << "Opciones presionado\n";
                        return 2;
                    }
                    if (exitButton->isMouseOver(window))
                    {
                        window.close();
                        return 0;
                    }
                }
            }

            if (playButton->isMouseOver(window))
                playButton->setFillColor(sf::Color::Green);
            else
                playButton->setFillColor(sf::Color::Cyan);

            if (optionsButton->isMouseOver(window))
                optionsButton->setFillColor(sf::Color::Green);
            else
                optionsButton->setFillColor(sf::Color::Cyan);

            if (exitButton->isMouseOver(window))
                exitButton->setFillColor(sf::Color::Green);
            else
                exitButton->setFillColor(sf::Color::Cyan);

            window.clear();
            window.draw(backSprite);
            window.draw(logoSprite);
            playButton->draw(window);
            optionsButton->draw(window);
            exitButton->draw(window);
            window.display();
        }
        return 0;
    }
    ~Menu();
};

Menu::~Menu()
{
}

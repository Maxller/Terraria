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

        void Draw(sf::RenderWindow &window)
        {
            window.draw(buttonText);
        }

        bool CheckIfIsMouseOver(sf::RenderWindow &window)
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

        if (!font.loadFromFile("./assets/font/Andy.ttf"))
        {
            std::cerr << "Error loading font\n";
        }

        if (!logoTexture.loadFromFile("./assets/image/custom-terraria-logo.png"))
        {
            std::cerr << "Error loading logo image\n";
        }
        if (backTexture.loadFromFile("./assets/image/Splash_9_0.png"))
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

    int DisplayMenu(sf::RenderWindow &window)
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
                    if (playButton->CheckIfIsMouseOver(window))
                    {
                        std::cout << "Jugar presionado\n";
                        return 1;
                    }
                    if (optionsButton->CheckIfIsMouseOver(window))
                    {
                        std::cout << "Opciones presionado\n";
                        return 2;
                    }
                    if (exitButton->CheckIfIsMouseOver(window))
                    {
                        window.close();
                        return 0;
                    }
                }
            }

            if (playButton->CheckIfIsMouseOver(window))
                playButton->setFillColor(sf::Color::Green);
            else
                playButton->setFillColor(sf::Color::Cyan);

            if (optionsButton->CheckIfIsMouseOver(window))
                optionsButton->setFillColor(sf::Color::Green);
            else
                optionsButton->setFillColor(sf::Color::Cyan);

            if (exitButton->CheckIfIsMouseOver(window))
                exitButton->setFillColor(sf::Color::Green);
            else
                exitButton->setFillColor(sf::Color::Cyan);

            window.clear();
            window.draw(backSprite);
            window.draw(logoSprite);
            playButton->Draw(window);
            optionsButton->Draw(window);
            exitButton->Draw(window);
            window.display();
        }
        return 0;
    }
    ~Menu();
};

Menu::~Menu()
{
}

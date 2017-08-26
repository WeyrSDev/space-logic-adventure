#include <memory>

#include <SFML/Graphics.hpp>

#include "tileset.hpp"
#include "level.hpp"

auto createCenteredWindow(int width, int height) {
    auto window = std::make_unique<sf::RenderWindow>(sf::VideoMode(width, height), "Space Logic Adventure", sf::Style::Titlebar | sf::Style::Close);
    int posX = (sf::VideoMode::getDesktopMode().width - window->getSize().x) / 2,
        posY = (sf::VideoMode::getDesktopMode().height - window->getSize().y) / 2;
    window->setPosition(sf::Vector2i(posX, posY));
    return window;
}

int main() {
    auto window = createCenteredWindow(860, 700);
    
    sf::Texture background_tx;
    background_tx.loadFromFile("assets/background.png");
    background_tx.setRepeated(true);
    background_tx.setSmooth(true);
    sf::Sprite background_sp(background_tx);
    background_sp.setTextureRect({ 0, 0, static_cast<int>(window->getSize().x), static_cast<int>(window->getSize().y) });

    auto level = Level("2.txt", "assets/tileset.png", {
        { Level::TileAppearance::FIELD_VERTICAL, Tileset::metalTileConnectStraight_NE },
        { Level::TileAppearance::FIELD_VERTICAL_OPENED_TOP, Tileset::metalTileConnectEnd_SE },
        { Level::TileAppearance::FIELD_VERTICAL_OPENED_BOTTOM, Tileset::metalTileConnectEnd_NE },
        { Level::TileAppearance::FIELD_HORIZONTAL, Tileset::metalTileConnectStraight_NW },
        { Level::TileAppearance::FIELD_HORIZONTAL_OPENED_LEFT, Tileset::metalTileConnectEnd_NW },
        { Level::TileAppearance::FIELD_HORIZONTAL_OPENED_RIGHT, Tileset::metalTileConnectEnd_SW },
        { Level::TileAppearance::FIELD_UP_RIGHT_TURN, Tileset::metalTileConnectCornerInner_SE },
        { Level::TileAppearance::FIELD_LEFT_UP_TURN, Tileset::metalTileConnectCornerInner_NW },
        { Level::TileAppearance::FIELD_DOWN_RIGHT_TURN, Tileset::metalTileConnectCornerInner_SW },
        { Level::TileAppearance::FIELD_LEFT_DOWN_TURN, Tileset::metalTileConnectCornerInner_NE },
        { Level::TileAppearance::PLAYER_FACED_TOP, Tileset::astronaut_NE },
        { Level::TileAppearance::PLAYER_FACED_BOTTOM, Tileset::astronaut_SW },
        { Level::TileAppearance::PLAYER_FACED_LEFT, Tileset::astronaut_NW },
        { Level::TileAppearance::PLAYER_FACED_RIGHT, Tileset::astronaut_SE },
        { Level::TileAppearance::FINISH_OVERLAY, Tileset::spaceCraft3_NE }
    });

    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                window->close();
                break;
            case sf::Event::KeyPressed:
                switch (event.key.code) {
                case sf::Keyboard::Left:
                    level.movePlayer(Level::ROTATE_COUNTERCLOCKWISE);
                    break;
                case sf::Keyboard::Right:
                    level.movePlayer(Level::ROTATE_CLOCKWISE);
                    break;
                case sf::Keyboard::Up:
                    level.movePlayer(Level::FRONT);
                    break;
                case sf::Keyboard::Down:
                    level.movePlayer(Level::BACK);
                    break;
                }
            }
        }
        window->draw(background_sp);
        window->draw(level);
        window->display();
    }

    return 0;
}

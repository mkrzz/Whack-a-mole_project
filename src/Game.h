
#ifndef WHACKAMOLESFML_GAME_H
#define WHACKAMOLESFML_GAME_H

#include <SFML/Graphics.hpp>

class Game
{
	public:
	Game(sf::RenderWindow& window);
	~Game();
	bool init();
	void update(float dt);
	void render();
	void mouseClicked(sf::Event event);
	void keyPressed(sf::Event event);

	private:
	bool collisionCheck(sf::Vector2i click, sf::Sprite sprite);
	void spawn();

	sf::RenderWindow& window;
	sf::Sprite background;
	sf::Texture background_texture;
	sf::Sprite bird;
	sf::Texture bird_texture;
	sf::Font font;
	sf::Text title_text;
    sf::Text score_text;
    sf::Clock game_clock;
    sf::Text timer_text;
    sf::Time game_duration;
    sf::Text game_over_text;

	bool in_menu;
	sf::Text menu_text;
	sf::Text play_option;
	sf::Text quit_option;
    sf::RectangleShape text_box;
    
    

	bool game_over      = false;
	bool play_selected = true;
    bool birdActive;
	bool reverse = false;
	float speed = 200;

	int score = 0;

};

#endif // WHACKAMOLESFML_GAME_H

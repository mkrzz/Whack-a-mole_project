
#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
	srand(time(NULL));
}

Game::~Game()
{

}

bool Game::init()
{
  in_menu = true;



  // init sprite

  if (!background_texture.loadFromFile("../Data/Images/background.png"))
  {
    std::cout << "background texture did not load \n";
  }
  background.setTexture(background_texture);
  background.setScale(2, 1.5);

  if (!bird_texture.loadFromFile("../Data/Images/bird.png"))
  {
    std::cout << "Bird texture did not load \n";
  }
  bird.setTexture(bird_texture);
  bird.setPosition(1, 325);
  bird.setScale(0.5, 0.5);

  if (!font.loadFromFile("../Data/Fonts/bubble.ttf"))
  {
    std::cout << "Font did not load";
  }

  //whack a mole text in game 
  title_text.setString("Whack-a-mole");
  title_text.setFont(font);
  title_text.setCharacterSize(100);
  title_text.setFillColor(sf::Color(255, 255, 255, 128));
  title_text.setPosition(
    window.getSize().x / 2 - title_text.getGlobalBounds().width / 2, 60);

  // play text 
  play_option.setString("[play]");
  play_option.setFont(font);
  play_option.setCharacterSize(80);
  play_option.setFillColor(sf::Color::White);
  play_option.setPosition(
  window.getSize().x / 2 - 150 - play_option.getGlobalBounds().width / 2,
  window.getSize().y / 2 - 70);

  // quit text
  quit_option.setString("quit");    
  quit_option.setFont(font);
  quit_option.setCharacterSize(80);
  quit_option.setFillColor(sf::Color::White);
  quit_option.setPosition(
  window.getSize().x / 2 + 150 - quit_option.getGlobalBounds().width / 2,
  window.getSize().y / 2 - 70);

  menu_text.setString("The ultimate whack-a-mole challenge awaits!");
  menu_text.setFont(font);
  menu_text.setCharacterSize(50);
  menu_text.setFillColor(sf::Color::White);
  menu_text.setPosition(
    window.getSize().x / 2 - menu_text.getGlobalBounds().width / 2,
    180);

  //white box in menu screen
  text_box.setSize(sf::Vector2f(1730, 950));
  text_box.setPosition(100, 50);
  text_box.setFillColor(sf::Color(0, 0, 0, 80));
  text_box.setOutlineColor(sf::Color::White);
  text_box.setOutlineThickness(1);

  //score text 
  score_text.setFont(font);
  score_text.setCharacterSize(50);
  score_text.setFillColor(sf::Color::Blue);
  score_text.setPosition(10, 10);
  score_text.setString("Score: 0");

  game_duration = sf::seconds(60);
  timer_text.setFont(font);
  timer_text.setCharacterSize(50);
  timer_text.setFillColor(sf::Color::Blue);
  timer_text.setPosition(window.getSize().x - 220, 10);
  timer_text.setString("Time: 60");

  return true;
}

void Game::update(float dt)
{
  {
    //bird moves from left to right
    if 
        
      ((bird.getPosition().x >
       (window.getSize().x - bird.getGlobalBounds().width)) ||
      (bird.getPosition().x < 0))
    {
      reverse = !reverse; 
    }

    
    //bird moves from right to left and the sprite is flipped 
    
    if (reverse)
    {
      bird.move(1.0f * speed * dt, 0);
      bird.setTextureRect(sf::IntRect(
      0, 0, bird.getLocalBounds().width, bird.getLocalBounds().height));

    }
    else
    {
      bird.move(-1.0f * speed * dt, 0);
      bird.setTextureRect(sf::IntRect(
      bird.getLocalBounds().width,
      0,
      -bird.getLocalBounds().width,
      bird.getLocalBounds().height));
    }
  }

  score_text.setString("Score: " + std::to_string(score));

  //game over function

  if (!game_over)
  {
    
    sf::Time elapsed   = game_clock.getElapsedTime();
    sf::Time remaining = game_duration - elapsed;

    int remainingSeconds = static_cast<int>(remaining.asSeconds());
    timer_text.setString(
      "Time: " + std::to_string(std::max(remainingSeconds, 0)));

    if (remaining <= sf::Time::Zero)
    {
      game_over = true;
      bird.setPosition(-1000, -1000);

      
    }
  }
}

void Game::render()
{
  

  if (in_menu)
  {
    window.draw(text_box);
    window.draw(play_option);
    window.draw(quit_option);
    window.draw(menu_text);
    
  }
  else  
  {
    window.draw(background);
    window.draw(title_text);
    window.draw(bird);
    window.draw(score_text);
    window.draw(timer_text);

    
  }
  
  // display game over

  if (game_over)
  {
    
    game_over_text.setFont(font);
    game_over_text.setCharacterSize(250);
    game_over_text.setFillColor(sf::Color::Blue);
    game_over_text.setString("Game Over!");
    game_over_text.setPosition(
    window.getSize().x / 2 -
    game_over_text.getGlobalBounds().width / 2, 
    window.getSize().y / 2 -
    game_over_text.getGlobalBounds().height / 2); 
  }

  
  if (game_over)
  {
    window.draw(game_over_text);
  }
}
  


void Game::mouseClicked(sf::Event event)
{
  // get the click position
  sf::Vector2i click = sf::Mouse::getPosition(window);

  // check if in bounds of bird Sprite
  if (birdActive && collisionCheck(click, bird))
  {
    score +=1;
    // destroy bird if clicked
    birdActive = false;
    
    // spawn new bird
    spawn();
  }
}

void Game::keyPressed(sf::Event event)
{
  if (
    (event.key.code == sf::Keyboard::Left) ||
    (event.key.code == sf::Keyboard::Right))
  {
    play_selected = !play_selected;
    if (play_selected)
    {
      play_option.setString("[play]");
      quit_option.setString("quit");
    }
    else
    {
      play_option.setString("play");
      quit_option.setString("[quit]");
    }
  }
  else if (event.key.code == sf::Keyboard::Enter)
  {
    if (play_selected)
    {
      in_menu = false;
      game_clock.restart();
      game_over = false;
    }
    else
    {
      window.close();
    }
  }
}

bool Game::collisionCheck(sf::Vector2i click, sf::Sprite sprite)
{
  
  sf::FloatRect bounds = sprite.getGlobalBounds();

  return bounds.contains((click.x),(click.y));
 
  return false;

}

void Game::spawn()
{
  //spawns new bird at random location
  float x = static_cast<float>(
    rand() %
    (window.getSize().x - static_cast<int>(bird.getGlobalBounds().width)));
  float y = static_cast<float>(
    rand() %
    (window.getSize().y - static_cast<int>(bird.getGlobalBounds().height)));
    bird.setPosition(x, y);

  float randomScale = 0.5f + static_cast<float>(rand()) /
                (static_cast<float>(RAND_MAX / (1.0f - 0.5f)));
  
  //random scale of spawned birds
  bird.setScale(randomScale, randomScale);

  birdActive = true;
}

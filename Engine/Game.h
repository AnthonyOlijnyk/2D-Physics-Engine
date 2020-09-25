#pragma once

#include "GameState.h"

class Game
{
private:

	sf::RenderWindow *window;
	sf::Event sfEvent;

	// dt or delta time keeps track of how long it takes
	// to render a frame
	sf::Clock dtClock;
	float dt;

	//creating a stack of possible states ie. menu
	std::stack<State*> states;

	//initializing the window and states
	void initWindow();
	void initStates();

public:
	Game();
	virtual ~Game();

	// reseting dt on game loop
	void updateDt();
	// updating SFML on game loop
	void updateSFMLEvents();
	void update();
	void render();
	// running game
	void run();
};


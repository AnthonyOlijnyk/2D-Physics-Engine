#pragma once

#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <map>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class State
{
private:
	sf::RenderWindow* window;
	std::vector<sf::Texture*> textures;

public:
	State(sf::RenderWindow* window);
	virtual ~State();

	// pure virtual functions (functions = 0) must be defined by
	// inherited classes (this is like abstract in Java)
	virtual void endState() = 0;

	virtual void update(const float& dt) = 0;
	// if there is no target, render to window
	// if there is a target, render there instead
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
};


#pragma once

#include "Entity.h"

class State
{
private:

protected:
	sf::RenderWindow* window;
	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keybinds;
	bool quit;

	std::vector<sf::Texture*> textures;

	virtual void initKeybinds() = 0;

public:
	State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys);
	virtual ~State();

	// const after function declaration means that all variables in
	// functions should be const
	const bool& getQuit() const;

	// pure virtual functions (functions = 0) must be defined by
	// inherited classes (this is like abstract in Java)
	virtual void checkForQuit();
	virtual void endState() = 0;


	virtual void updateInput(const float& dt) = 0;

	virtual void update(const float& dt) = 0;
	// if there is no target, render to window
	// if there is a target, render there instead
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
};


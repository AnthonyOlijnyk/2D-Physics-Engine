#include "Game.h"

void Game::initWindow() {

    // getting file reference from window.ini in Config folder
    std::ifstream ifs("Config/window.ini");

    // setting default setting parameters
    std::string title = "None";
    sf::VideoMode window_bounds(800, 600);
    unsigned framerate_limit = 120;
    bool vertical_sync_enabled = false;

    // reading from the file
    // since the file is formatted where each line corresponds
    // to a different setting, each read in will be perfectly lined up
    // with the given setting
    if (ifs.is_open()) {
        // using getline here because title is a string
        std::getline(ifs, title);
        ifs >> window_bounds.width >> window_bounds.height;
        ifs >> framerate_limit;
        ifs >> vertical_sync_enabled;
    }

    ifs.close();

    // creates a window with specified parameters
	this->window = new sf::RenderWindow(window_bounds, title);
    this->window->setFramerateLimit(framerate_limit);
    this->window->setVerticalSyncEnabled(vertical_sync_enabled);
}

void Game::initKeys() {
    // emplace just adds to the map if the key is unique
    this->supportedKeys.emplace("Escape", sf::Keyboard::Key::Escape);
    this->supportedKeys.emplace("A", sf::Keyboard::Key::A);
    this->supportedKeys.emplace("D", sf::Keyboard::Key::D);
    this->supportedKeys.emplace("W", sf::Keyboard::Key::W);
    this->supportedKeys.emplace("S", sf::Keyboard::Key::S);

    // will print 0
    //std::cout << supportedKeys["A"] << std::endl;
}

void Game::initStates() {
    // initialize game state with base window
    this->states.push(new GameState(this->window, &this->supportedKeys));
}

Game::Game() {
    // initWindow and initStates called on creation of game object
    this->initWindow();
    this->initKeys();
    this->initStates();
}

Game::~Game() {
    // kills window
	delete this->window;

    // kills all states in stack
    while (!this->states.empty()) {
        delete this->states.top();
        this->states.pop();
    }
}

void Game::endApplication() {
    std::cout << "Ending Application!" << std::endl;
}

void Game::updateDt() {
    // updates the dt variable with the time it takes to update and
    // render one frame (can check with system("cls") [clear screen])
    this->dt = this->dtClock.restart().asSeconds();
}

void Game::updateSFMLEvents() {
    while (this->window->pollEvent(this->sfEvent))
    {
        // if exit button pressed, close window
        if (this->sfEvent.type == sf::Event::Closed)
            this->window->close();
    }
}

void Game::update() {
    // calls updateSFMLEvents
    this->updateSFMLEvents();

    // if the stack isn't empty, update the dt
    if (!this->states.empty()) {
        this->states.top()->update(this->dt);

        if (this->states.top()->getQuit()) {
            this->states.top()->endState();
            delete this->states.top();
            this->states.pop();
        }
    }
    // applications end
    else {
        this->endApplication();
        this->window->close();
    }
}

void Game::render() {
    this->window->clear();

    // render the current state at the top of the stack
    if (!this->states.empty()) {
        this->states.top()->render();
    }

    this->window->display();
}

void Game::run() {
    // if the window is open, update and render
    while (this->window->isOpen())
    {
        this->updateDt();
        this->update();
        this->render();
    }
}
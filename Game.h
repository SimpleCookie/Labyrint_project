
#ifndef GAME_H
#define GAME_H
#include "Maze/Maze.h"
#include "Character.h"

class Game {
public:
	static void start(int w, int h);
private:
	static const char WALK_UP, WALK_DOWN, WALK_LEFT, WALK_RIGHT, PICKUP;
	Game(int w, int h);
	void init();
	bool isPlaying() const;
    void checkEvents();
	void printMaze();

protected:
	Game(){}
	bool playing;
	Maze maze;
	Character player;
};

#endif
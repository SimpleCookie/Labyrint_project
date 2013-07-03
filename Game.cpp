
#include "Game.h"
#include <iostream>
#include "Linux/Linux.h"

const char Game::WALK_UP='w', Game::WALK_DOWN='s', Game::WALK_LEFT='a', Game::WALK_RIGHT='d', Game::PICKUP='?';

Game::Game(int w, int h):playing(false) {
	maze.Create_maze(w,h);
}

void Game::init() {
	playing = true;
		// TODO: behöver implementeras
}
bool Game::isPlaying() const {
	return playing;
}

void Game::start(int w, int h){
	Game main_game(w,h);
	// Här gör vi en init
	main_game.init();
	while(main_game.isPlaying()){
		main_game.checkEvents();		// skapa en event funktion(kanske ett objekt event inuti klassen beroende på hur komplext det blir)
		main_game.printMaze();			// skriv ut den färdigrenderade mazen med items props och karaktärer
	}
}

void Game::checkEvents(){
	keyboard k;
	int c = k.getch();			// väntar på input från playern
	while(k.kbhit())		// for clearing the buffer
		k.getch();
	try{
		switch(c){
			case 27:				// escape-key
				playing = false;
				break;
			case WALK_UP:
				if(maze[player.getY()-1][player.getX()] != Maze::WALL)
					player.walkUp();			// y--
				break;
			case WALK_DOWN:
				if(maze[player.getY()+1][player.getX()] != Maze::WALL)
					player.walkDown();		// y++
				break;
			case WALK_RIGHT:
				if(maze[player.getY()][player.getX()+1] != Maze::WALL)
					player.walkRight();		// x++
				break;
			case WALK_LEFT:
				if(maze[player.getY()][player.getX()-1] != Maze::WALL)
					player.walkLeft();			// x--
				break;
			// ....
			default:
				//....
				break;
		}
	}
	catch(...){}
}

void Game::printMaze(){
	char c = maze[player.getY()][player.getX()];
	maze[player.getY()][player.getX()] = Character::TECKEN;
	maze.Print_maze();

	maze[player.getY()][player.getX()] = c;
}
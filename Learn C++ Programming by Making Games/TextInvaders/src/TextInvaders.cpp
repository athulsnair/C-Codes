//============================================================================
// Name        : TextInvaders.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <ctime>
#include <cmath>
#include <cstring>
#include <string>
#include <cstdlib>
#include <algorithm> // for sort
#include <fstream> // for file i/o
#include "TextInvaders.h"
#include "CursesUtils.h"
using namespace std;

void InitGame(Game & game);
void InitPlayer(const Game & game, Player & player);
void ResetPlayer(const Game & game, Player & player);
void ResetMissile(Player & player);
int HandleInput(Game & game, Player & player, AlienSwarm& aliens, Shield shields[], int numberOfShields, HighScoreTable& table);
void UpdateGame(clock_t dt, Game & game, Player & player, Shield shields[], int numberOfShields, AlienSwarm& aliens, AlienUFO& ufo);
void DrawGame(const Game & game, const Player & player, Shield shields[], int numberOfShields, const AlienSwarm& aliens, const AlienUFO& ufo, const HighScoreTable& table);
void MovePlayer(const Game & game, Player & player, int dx);
void DrawPlayer(const Player & player, const char *sprite[]);
void PlayerShoot(Player & player);
void UpdateMissile(Player & player);
void InitShields(const Game & game, Shield shields[], int numberOfShields);
void CleanUpshields(Shield shields[], int numberOfShields);
void DrawShields(const Shield shields[], int numberOfShields);

// return the shield index of the which shield got hit,
// return NOT_IN_PLAY if nothing was hit
// also return the shield collision point
int IsCollision(const Position& projectile, const Shield shields[], int numberOfShields, Position & shieldCollisionPoint);
void ResolveShieldCollision(Shield shields[], int shieldIndex, const Position& shieldCollisionPoint);
void InitAliens(const Game& game, AlienSwarm& aliens);
void DrawAliens(const AlienSwarm& aliens);
bool IsCollision(const Player& player, const AlienSwarm& aliens, Position& alienCollisionPositionInArray);
int ResolveAlienCollision(AlienSwarm& aliens, const Position& hitPositionInAliensArray);
bool UpdateAliens(Game& game, AlienSwarm& aliens, Player& player, Shield shiels[], int numberOfShields);
void ResetMovementTime(AlienSwarm& aliens);

void FindEmptyRowsAndColumns(const AlienSwarm& aliens, int& emptyColsLeft, int& emptyColsRight, int& emptyRowsBottom);
void DestroyShields(const AlienSwarm& aliens, Shield shields[], int numberOfShields);
void CollideShieldsWithAliens(Shield shields[], int numberOfShields, int xPos, int yPos, const Size& size);

bool ShouldShootBomb(const AlienSwarm& aliens);
void ShootBomb(AlienSwarm& aliens, int columnToShoot);
bool UpdateBombs(const Game& game, AlienSwarm& aliens, Player& player, Shield shields[], int numberOfShields);
bool IsCollision(const Position& projectile, const Position& spritePosition, const Size& spriteSize);

void ResetGame(Game& game, Player& player, AlienSwarm& aliens, Shield shields[], int numberOfShields);
void ResetShields(const Game& game, Shield shields[], int numberOfShields);
void DrawGameOverScreen(const Game & game);
void DrawIntroScreen(const Game& game);

void ResetUFO(const Game& game, AlienUFO& ufo);
void UpdateUFO(const Game& game, AlienUFO& ufo);
void PutUFOInPlay(const Game& game, AlienUFO& ufo);
void DrawUFO(const AlienUFO& ufo);

void ResetGameOverPositionCursor(Game& game);
void AddHighScore(HighScoreTable& table, int score, const string& name);
bool ScoreCompare(const Score& score1, const Score& score2);
void DrawHightScoreTable(const Game& game, const HighScoreTable& table);
void SaveHighScore(const HighScoreTable& table);
void LoadHighScore(HighScoreTable& table);

string test;

/*int activeColumns[NUM_ALIEN_COLUMNS]; // columns that still exist - some aliens are still alive in that column
int numActiveCols = 0;
int emptyColsLeft = 0;
int emptyColsRight = 0;
int emptyRowsBottom = 0;
int numberOfColumns;*/
//int numberOfShots;

int main() {

	srand(time(NULL));

	Game game;
	Player player;
	Shield shields[NUM_SHIELDS];
	AlienSwarm aliens;
	AlienUFO ufo;
	HighScoreTable table;

	InitializeCurses(true);

	InitGame(game);
	game.level = 1;
	InitPlayer(game, player);
	InitShields(game, shields, NUM_SHIELDS);
	InitAliens(game, aliens);
	ResetUFO(game, ufo);

	LoadHighScore(table);

	bool quit =  false;
	int input;

	string AlienX, AlienY, ShieldX, ShieldY;


	clock_t lastTIme = clock();

	while(!quit)
	{
		input = HandleInput(game, player, aliens, shields, NUM_SHIELDS, table);

		if(input != 'q')
		{
			clock_t currentTime = clock();
			clock_t dt = currentTime - lastTIme;

			if(dt > CLOCKS_PER_SEC/FPS)
			{
				lastTIme = currentTime;

				UpdateGame(dt, game, player, shields, NUM_SHIELDS, aliens, ufo);
				ClearScreen(); // Curses utils
				DrawGame(game, player, shields, NUM_SHIELDS,aliens, ufo, table);
				RefreshScreen(); // Curses utils
				//AlienX = to_string(numActiveCols);
				//ShieldX = to_string(shields[2].position.x);
				//mvprintw(0,0,"numActiveCols: ");
				//mvprintw(0,15,AlienX.c_str());
				//mvprintw(0,30,"Bombs: %i",aliens.numberOfBombsInPlay);
				//mvprintw(1,0,"activeColumns: %i, %i, %i, %i, %i, %i, %i, %i, %i, %i, %i",activeColumns[0], activeColumns[1], activeColumns[2], activeColumns[3], activeColumns[4], activeColumns[5],
						//activeColumns[6], activeColumns[7], activeColumns[8], activeColumns[9], activeColumns[10]);
				//mvprintw(2,0,"numberOfColumns:%i emptyColsLeft: %i", numberOfColumns, emptyColsLeft);
				//mvprintw(1,10,"NumberOfShots: %i", numberOfShots);
				/*missileX = to_string(player.missile.x);
				missileY = to_string(player.missile.y);
				playerX = to_string(player.position.x);
				playerY = to_string(player.position.y);
				shield1X = to_string(shields[0].position.x);
				shield1Y = to_string(shields[0].position.y);
				shield1Right = to_string(shields[0].position.x + SHIELD_SPRITE_WIDTH);
				shield1Top = to_string(shields[0].position.y + SHIELD_SPRITE_HEIGHT);
				mvprintw(0,0,"MissileX: ");
				mvprintw(0,10,missileX.c_str());
				mvprintw(1,0,"MissileY: ");
				mvprintw(1,10,missileY.c_str());
				mvprintw(2,0,"playerX: ");
				mvprintw(2,9,playerX.c_str());
				mvprintw(3,0,"playerY: ");
				mvprintw(3,9,playerY.c_str());
				mvprintw(4,0,"shield1X: ");
				mvprintw(4,9,shield1X.c_str());
				mvprintw(5,0,"shield1Y: ");
				mvprintw(5,9,shield1Y.c_str());
				mvprintw(6,0,"shield1Right: ");
				mvprintw(6,14,shield1Right.c_str());
				mvprintw(7,0,"shield1Top: ");
				mvprintw(7,14,shield1Top.c_str());*/

			}
		}
		else
		{
			quit = true;
		}
	}

	shutdownCurses();
	CleanUpshields(shields, NUM_SHIELDS);

	return 0;
}

void InitGame(Game & game)
{
	game.windowSize.height = ScreenHeight();
	game.windowSize.width = ScreenWidth();
	game.currentStates = GS_INTRO; // for now - TODO: change to GS_INTRO at the end

	game.waitTimer = 0;
	game.gameTimer = 0;

	ResetGameOverPositionCursor(game);
}

void InitPlayer(const Game & game, Player & player)
{
	player.lives = MAX_NUMBER_OF_LIVES;
	player.spriteSize.width = PLAYER_SPRITE_WIDTH;
	player.spriteSize.height = PLAYER_SPRITE_HEIGHT;
	player.score = 0;
	ResetPlayer(game, player);

}

int HandleInput(Game & game, Player & player, AlienSwarm& aliens, Shield shields[], int numberOfShields, HighScoreTable& table)
{
	int input = GetChar();

	switch(input)
	{
	case 's':
		if(game.currentStates == GS_INTRO)
		{
			game.currentStates = GS_HIGH_SCORES;
		}
		break;
	case 'q':
		return input;
	case AK_RIGHT:
		if(game.currentStates == GS_PLAY)
		{
			MovePlayer(game, player, PLAYER_MOVEMENT_AMOUNT);
		}
		else if(game.currentStates == GS_GAME_OVER)
		{
			game.gameOverHPositionCursor = (game.gameOverHPositionCursor + 1) % MAX_NUMBER_OF_CHARACTERS_IN_NAME;
		}

		break;
	case AK_LEFT:
		if(game.currentStates == GS_PLAY)
		{
			MovePlayer(game, player, -PLAYER_MOVEMENT_AMOUNT);
		}
		else if(game.currentStates == GS_GAME_OVER)
		{
			game.gameOverHPositionCursor = game.gameOverHPositionCursor - 1;

			if(game.gameOverHPositionCursor < 0)
			{
				game.gameOverHPositionCursor = MAX_NUMBER_OF_CHARACTERS_IN_NAME - 1;
			}
		}

		break;
	case AK_UP:
		if(game.currentStates == GS_GAME_OVER)
		{
			game.gameOverVPositionCursor[game.gameOverHPositionCursor] = game.gameOverVPositionCursor[game.gameOverHPositionCursor] - 1;

			if(game.gameOverVPositionCursor[game.gameOverHPositionCursor] < 0)
			{
				game.gameOverVPositionCursor[game.gameOverHPositionCursor] = MAX_ALPHABET_CHARACTERS - 1;
			}

			game.playerName[game.gameOverHPositionCursor] = 'A' + game.gameOverVPositionCursor[game.gameOverHPositionCursor];
		}

		break;
	case AK_DOWN:
		if(game.currentStates == GS_GAME_OVER)
		{
			game.gameOverVPositionCursor[game.gameOverHPositionCursor] = (game.gameOverVPositionCursor[game.gameOverHPositionCursor] + 1) % MAX_ALPHABET_CHARACTERS;
			game.playerName[game.gameOverHPositionCursor] = 'A' + game.gameOverVPositionCursor[game.gameOverHPositionCursor];
		}

		break;
	case ' ':
		if(game.currentStates == GS_PLAY)
		{
			PlayerShoot(player);
		}
		else if(game.currentStates == GS_PLAYER_DEAD)
		{
			player.lives--;
			player.animation = 0;

			if(player.lives == 0)
			{
				game.currentStates = GS_GAME_OVER;
				ResetGameOverPositionCursor(game);

			}
			else
			{
				game.currentStates = GS_WAIT;
				game.waitTimer = 10;
			}
		}
		else if(game.currentStates == GS_INTRO)
		{
			game.currentStates = GS_PLAY;
		}
		else if(game.currentStates == GS_GAME_OVER)
		{
			game.playerName[MAX_NUMBER_OF_CHARACTERS_IN_NAME] = '\0';
			AddHighScore(table, player.score, std::string(game.playerName));
			game.currentStates = GS_HIGH_SCORES;
		}
		else if(game.currentStates == GS_HIGH_SCORES)
		{
			game.currentStates = GS_INTRO;
			ResetGame(game, player, aliens, shields, numberOfShields);
		}

	}

	return input;
}

void ResetPlayer(const Game & game, Player & player)
{
	player.position.x = game.windowSize.width / 2 - player.spriteSize.width / 2;
	player.position.y = game.windowSize.height - player.spriteSize.height - 1;
	player.animation = 0;
	player.score = 0; // I added
	player.lives = MAX_NUMBER_OF_LIVES; // I added
	ResetMissile(player);
}

void ResetMissile(Player & player)
{
	player.missile.x = NOT_IN_PLAY;
	player.missile.y = NOT_IN_PLAY;
}

void UpdateGame(clock_t dt, Game & game, Player & player, Shield shields[], int numberOfShields, AlienSwarm& aliens, AlienUFO& ufo)
{
	game.gameTimer += dt;

	if(game.currentStates == GS_PLAY)
	{
		UpdateMissile(player);
		Position shieldCollisionPoint;

		int shieldIndex = IsCollision(player.missile, shields, numberOfShields, shieldCollisionPoint);

		if(shieldIndex != NOT_IN_PLAY)
		{
			ResetMissile(player);
			ResolveShieldCollision(shields, shieldIndex, shieldCollisionPoint);
		}

		Position playerAlienCollisionPoint;

		if(IsCollision(player, aliens, playerAlienCollisionPoint))
		{
			ResetMissile(player);
			player.score += ResolveAlienCollision(aliens, playerAlienCollisionPoint);
		}

		if(UpdateAliens(game, aliens, player, shields, numberOfShields))
		{
			game.currentStates = GS_PLAYER_DEAD;
		}
		if(aliens.numAliensLeft == 0)
		{
			//game.level++;

			game.level = (game.level % NUM_LEVELS) + 1;
			game.currentStates =  GS_WAIT;
			game.waitTimer = WAIT_TIME;
			ResetGame(game, player, aliens, shields, numberOfShields);
		}

		if(ufo.position.x == NOT_IN_PLAY)
		{
			// put UFO in play somehow
			if(game.gameTimer % 500 == 13)
			{
				PutUFOInPlay(game, ufo);
			}
		}
		else
		{
			//update UFO
			if(IsCollision(player.missile, ufo.position, ufo.size))
			{
				player.score += ufo.points;
				ResetMissile(player);
				ResetUFO(game, ufo);
			}
			else
			{
				UpdateUFO(game, ufo);
			}
		}
	}
	else if(game.currentStates == GS_PLAYER_DEAD)
	{
		player.animation = (player.animation + 1) % 2;
	}
	else if(game.currentStates == GS_WAIT)
	{
		game.waitTimer--;

		if(game.waitTimer == 0)
		{
			game.currentStates = GS_PLAY;
		}
	}
}

void DrawGame(const Game & game, const Player & player, Shield shields[], int numberOfShields, const AlienSwarm& aliens, const AlienUFO& ufo, const HighScoreTable& table)
{
	if(game.currentStates == GS_PLAY || game.currentStates == GS_PLAYER_DEAD || game.currentStates == GS_WAIT)
	{
		if(game.currentStates == GS_PLAY || game.currentStates == GS_WAIT)
		{
			DrawPlayer(player, PLAYER_SPRITE);
		}
		else
		{
			DrawPlayer(player, PLAYER_EXPLOSION_SPRITE);
		}

		DrawShields(shields, numberOfShields);
		DrawAliens(aliens);
		DrawUFO(ufo);
	}
	else if(game.currentStates == GS_GAME_OVER)
	{
		DrawGameOverScreen(game);
	}
	else if(game.currentStates == GS_INTRO)
	{
		DrawIntroScreen(game);
	}
	else if(game.currentStates == GS_HIGH_SCORES)
	{
		DrawHightScoreTable(game, table);
	}
}

void MovePlayer(const Game & game, Player & player, int dx)
{
	if(player.position.x + player.spriteSize.width + dx > game.windowSize.width) // make sure player doesn't go off the screen to the right
	{
		player.position.x = game.windowSize.width - player.spriteSize.width; // the right most position player can be
	}
	else if(player.position.x + dx < 0)	// make sure player can't go off the screen to the left
	{
		player.position.x = 0;	// the left most position the player can be
	}
	else
	{
		player.position.x += dx;
	}
}

void DrawPlayer(const Player & player, const char *sprite[])
{
	DrawSprite(player.position.x, player.position.y, sprite, player.spriteSize.height, player.animation * player.spriteSize.height);

	if(player.missile.x != NOT_IN_PLAY)
	{
		DrawCharacter(player.missile.x, player.missile.y, PLAYER_MISSILE_SPRITE);
	}

	mvprintw(0, 0, "Score: %i, Lives: %i", player.score, player.lives);
}

void PlayerShoot(Player & player)
{
	if(player.missile.x == NOT_IN_PLAY || player.missile.y == NOT_IN_PLAY)
	{
		player.missile.y = player.position.y - 1;
		player.missile.x = player.position.x + player.spriteSize.width / 2;
	}
}

void UpdateMissile(Player & player)
{
	if(player.missile.y != NOT_IN_PLAY)
	{
		player.missile.y -= PLAYER_MISSILE_SPEED;

		//std::cout << player.missile.y;

		if(player.missile.y < 0)
		{
			ResetMissile(player);
		}
	}
}

void InitShields(const Game & game, Shield shields[], int numberOfShields)
{
	for(int i = 0; i < numberOfShields; i++)
	{
		Shield & shield = shields[i];

		for(int row = 0; row < SHIELD_SPRITE_HEIGHT; row++)
		{
			shield.sprite[row] = new char[SHIELD_SPRITE_WIDTH + 1];
		}
	}

	ResetShields(game, shields, numberOfShields);
}

void CleanUpshields(Shield shields[], int numberOfShields)
{
	for(int i = 0; i < numberOfShields; i++)
	{
		Shield & shield = shields[i];

		for(int row = 0; row < SHIELD_SPRITE_HEIGHT; row++)
		{
			delete [] shield.sprite[row];
		}
	}
}

void DrawShields(const Shield shields[], int numberOfShields)
{
	for(int i = 0; i < numberOfShields; i++)
	{
		const Shield & shield = shields[i];

		DrawSprite(shield.position.x, shield.position.y, (const char **)shield.sprite, SHIELD_SPRITE_HEIGHT);
	}
}

int IsCollision(const Position& projectile, const Shield shields[], int numberOfShields, Position & shieldCollisionPoint)
{
	//mvprintw(9, 0, "HHH");
	shieldCollisionPoint.x = NOT_IN_PLAY;
	shieldCollisionPoint.y = NOT_IN_PLAY;

	if(projectile.y != NOT_IN_PLAY)
	{
		for(int i = 0; i < numberOfShields; i++)
		{
			const Shield& shield = shields[i];

			if(projectile.x >= shield.position.x && projectile.x < (shield.position.x + SHIELD_SPRITE_WIDTH) //is it in line horizontally?
			&& (projectile.y >= shield.position.y && projectile.y < shield.position.y + SHIELD_SPRITE_HEIGHT)//is it in line vertically?
			&& shield.sprite[projectile.y - shield.position.y][projectile.x - shield.position.x] != ' ') //does it collide with part of the shield
			{
				//we collided
				shieldCollisionPoint.x = projectile.x - shield.position.x;
				shieldCollisionPoint.y = projectile.y - shield.position.y;
				return i;
			}
		}
	}

	return NOT_IN_PLAY;
}

void ResolveShieldCollision(Shield shields[], int shieldIndex, const Position& shieldCollisionPoint)
{
	shields[shieldIndex].sprite[shieldCollisionPoint.y][shieldCollisionPoint.x] = ' ';
}

void InitAliens(const Game& game, AlienSwarm& aliens)
{
	for(int r = 0; r < NUM_ALIEN_ROWS; r++)
	{
		for(int c = 0; c < NUM_ALIEN_COLUMNS; c++)
		{
			aliens.aliens[r][c] = AS_ALIVE;
		}
	}

	//ResetMovementTime(aliens);

	aliens.animation = 0;
	aliens.direction = 1;
	aliens.explosionTimer = NOT_IN_PLAY;
	aliens.numAliensLeft = NUM_ALIEN_ROWS * NUM_ALIEN_COLUMNS;
	aliens.numberOfBombsInPlay = 0;
	aliens.spriteSize.height = ALIEN_SPRITE_HEIGHT;
	aliens.spriteSize.width = ALIEN_SPRITE_WIDTH;
	aliens.position.x = (game.windowSize.width - (NUM_ALIEN_COLUMNS * (aliens.spriteSize.width + ALIENS_X_PADDING))) / 2;
	aliens.position.y = game.windowSize.height - NUM_ALIEN_COLUMNS - NUM_ALIEN_ROWS * aliens.spriteSize.height - ALIENS_Y_PADDING * (NUM_ALIEN_ROWS - 1) - 3 + game.level;
	aliens.line = NUM_ALIEN_COLUMNS - (game.level - 1);


	for(int i = 0; i < MAX_NUMBER_OF_ALENT_BOMBS; i++)
	{
		aliens.bombs[i].animation = 0;
		aliens.bombs[i].positon.x = NOT_IN_PLAY;
		aliens.bombs[i].positon.y = NOT_IN_PLAY;
	}

	ResetMovementTime(aliens);
}

void DrawAliens(const AlienSwarm& aliens)
{
	// draw 1 row of 30 point aliens
	const int NUM_30_POINT_ALIEN_ROWS = 1;

	for(int col = 0; col < NUM_ALIEN_COLUMNS; col++)
	{
		int x = aliens.position.x + col * ( aliens.spriteSize.width + ALIENS_X_PADDING);
		int y = aliens.position.y;

		if(aliens.aliens[0][col] == AS_ALIVE)
		{
			DrawSprite(x, y, ALIEN30_SPRITE, aliens.spriteSize.height, aliens.animation * aliens.spriteSize.height);
		}
		else if(aliens.aliens[0][col] == AS_EXPLODING)
		{
			DrawSprite(x, y, ALIEN_EXPLODING, aliens.spriteSize.height);
		}
	}

	// draw 2 row of 20 point aliens
	const int NUM_20_POINT_ALIEN_ROWS = 2;

	for(int row = 0; row < NUM_20_POINT_ALIEN_ROWS; row++)
	{
		for(int col = 0; col < NUM_ALIEN_COLUMNS; col++)
		{
			int x = aliens.position.x + col * (aliens.spriteSize.width + ALIENS_X_PADDING);
			int y = aliens.position.y + row * (aliens.spriteSize.height + ALIENS_Y_PADDING) + ((aliens.spriteSize.height + ALIENS_Y_PADDING) * NUM_30_POINT_ALIEN_ROWS);

			if(aliens.aliens[row + NUM_30_POINT_ALIEN_ROWS][col] == AS_ALIVE)
			{
				DrawSprite(x, y, ALIEN20_SPRITE, aliens.spriteSize.height, aliens.animation * aliens.spriteSize.height);
			}
			else if(aliens.aliens[row + NUM_30_POINT_ALIEN_ROWS][col] == AS_EXPLODING)
			{
				DrawSprite(x, y, ALIEN_EXPLODING, aliens.spriteSize.height);
			}
		}
	}

	// draw 2 row of 10 point aliens
	const int NUM_10_POINT_ALIEN_ROWS = 2;

	for(int row = 0; row < NUM_10_POINT_ALIEN_ROWS; row++)
	{
		for(int col = 0; col < NUM_ALIEN_COLUMNS; col++)
		{
			int x = aliens.position.x + col * (aliens.spriteSize.width + ALIENS_X_PADDING);
			int y = aliens.position.y + row * (aliens.spriteSize.height + ALIENS_Y_PADDING) + ((aliens.spriteSize.height + ALIENS_Y_PADDING) * NUM_20_POINT_ALIEN_ROWS) + ((aliens.spriteSize.height + ALIENS_Y_PADDING) * NUM_30_POINT_ALIEN_ROWS);

			if(aliens.aliens[row + NUM_30_POINT_ALIEN_ROWS + NUM_20_POINT_ALIEN_ROWS][col] == AS_ALIVE)
			{
				DrawSprite(x, y, ALIEN10_SPRITE, aliens.spriteSize.height, aliens.animation * aliens.spriteSize.height);
			}
			else if(aliens.aliens[row + NUM_30_POINT_ALIEN_ROWS + NUM_20_POINT_ALIEN_ROWS][col] == AS_EXPLODING)
			{
				DrawSprite(x, y, ALIEN_EXPLODING, aliens.spriteSize.height);
			}
		}
	}

	if(aliens.numberOfBombsInPlay > 0)
	{
		for(int i = 0; i < MAX_NUMBER_OF_ALENT_BOMBS; i++)
		{
			if(aliens.bombs[i].positon.x != NOT_IN_PLAY && aliens.bombs[i].positon.y != NOT_IN_PLAY)
			{
				DrawCharacter(aliens.bombs[i].positon.x, aliens.bombs[i].positon.y, ALIEND_BOMB_SPRITE[aliens.bombs[i].animation]);
			}
		}
	}
}

bool IsCollision(const Player& player, const AlienSwarm& aliens, Position& alienCollisionPositionInArray)
{
	alienCollisionPositionInArray.x = NOT_IN_PLAY;
	alienCollisionPositionInArray.y = NOT_IN_PLAY;

	for(int row = 0; row < NUM_ALIEN_ROWS; row++)
	{
		for(int col = 0; col < NUM_ALIEN_COLUMNS; col++)
		{
			int xPos = aliens.position.x + col * (aliens.spriteSize.width + ALIENS_X_PADDING);
			int yPos = aliens.position.y + row * (aliens.spriteSize.height + ALIENS_Y_PADDING);

			if((player.missile.x >= xPos && player.missile.x < xPos + aliens.spriteSize.width)
				&& (player.missile.y >= yPos && player.missile.y < yPos + aliens.spriteSize.height)
				&& (aliens.aliens[row][col] == AS_ALIVE))
			{
				alienCollisionPositionInArray.x = col;
				alienCollisionPositionInArray.y = row;

				return true;
			}
		}
	}

	return false;
}

int ResolveAlienCollision(AlienSwarm& aliens, const Position& hitPositionInAliensArray)
{
	aliens.aliens[hitPositionInAliensArray.y][hitPositionInAliensArray.x] = AS_EXPLODING;
	aliens.numAliensLeft--;

	if(aliens.explosionTimer == NOT_IN_PLAY)
	{
		aliens.explosionTimer = ALIEN_EXPLOSION_TIME;
	}

	if(hitPositionInAliensArray.y == 0)
	{
		return 30;
	}
	else if(hitPositionInAliensArray.y >=1 && hitPositionInAliensArray.y < 3)
	{
		return 20;
	}
	else
		return 10;
}

bool UpdateAliens(Game& game, AlienSwarm& aliens, Player& player, Shield shields[], int numberOfShields)
{
	if(UpdateBombs(game, aliens, player, shields, numberOfShields))
	{
		return true;
	}

	if(aliens.explosionTimer >= 0)
	{
		aliens.explosionTimer--; // if explosionTimer == 0, then explosionTimer = NOT_IN_PLAY(-1)
	}

	for(int row = 0; row < NUM_ALIEN_ROWS; row++)
	{
		for(int col = 0; col < NUM_ALIEN_COLUMNS; col++)
		{
			if(aliens.aliens[row][col] == AS_EXPLODING && aliens.explosionTimer == NOT_IN_PLAY)
			{
				aliens.aliens[row][col] = AS_DEAD;
			}
		}
	}


	aliens.movementTime--;

	bool moveHorizontal = 0 >= aliens.movementTime;
	int emptyColsLeft = 0;
	int emptyColsRight = 0;
	int emptyRowsBottom = 0;

	FindEmptyRowsAndColumns(aliens, emptyColsLeft, emptyColsRight, emptyRowsBottom);

	int numberOfColumns = NUM_ALIEN_COLUMNS - emptyColsLeft - emptyColsRight;
  	int leftAlienPosition = aliens.position.x + emptyColsLeft * (aliens.spriteSize.width + ALIENS_X_PADDING);
	int rightAlienPosition = leftAlienPosition + numberOfColumns * aliens.spriteSize.width + (numberOfColumns-1)*ALIENS_X_PADDING;

	if(((rightAlienPosition >= game.windowSize.width && aliens.direction > 0) || (leftAlienPosition <= 0 && aliens.direction < 0)) && moveHorizontal && aliens.line > 0)
	{
		//move down
		moveHorizontal = false;
		aliens.position.y++;
		aliens.line--;
		aliens.direction = -aliens.direction;
		ResetMovementTime(aliens);
		DestroyShields(aliens, shields, numberOfShields);

		if(aliens.line == 0)
		{
			game.currentStates = GS_GAME_OVER;
			return false;
		}

	}

	if(moveHorizontal)
	{
		aliens.position.x += aliens.direction;
		ResetMovementTime(aliens);
		aliens.animation = aliens.animation == 0?1:0;
		DestroyShields(aliens, shields, numberOfShields);
	}

	if(!moveHorizontal)
	{

		int activeColumns[NUM_ALIEN_COLUMNS]; // columns that still exist - some aliens are still alive in that column
		int numActiveCols = 0;

		for(int col = emptyColsLeft; col < NUM_ALIEN_COLUMNS - emptyColsRight; col++)
		{
			for(int row = 0; row < NUM_ALIEN_ROWS; row++)
			{
				if(aliens.aliens[row][col] == AS_ALIVE)
				{
					activeColumns[numActiveCols] = col;
					numActiveCols++;

					break;
				}
			}
		}

		if(ShouldShootBomb(aliens))
		{
			if(numActiveCols > 0)
			{
				int numberOfShots = (rand() % 3 + 1) - aliens.numberOfBombsInPlay; // make sure that there are only 3 bombs in play
				//numberOfShots = 0;
				//numberOfShots = (rand() % 3 + 1) - aliens.numberOfBombsInPlay;

				for(int i = 0; i < numberOfShots; i++)
				{
					int columnToShoot = rand() % numActiveCols;

					//ShootBomb(aliens, columnToShoot);
					ShootBomb(aliens, activeColumns[columnToShoot]);
				}
			}
		}
		//numberOfShots = 0;
	}

	return false;
}

void ResetMovementTime(AlienSwarm& aliens)
{
	aliens.movementTime = aliens.line * 2 + (5 * (float(aliens.numAliensLeft) / float(NUM_ALIEN_ROWS * NUM_ALIEN_COLUMNS)));
}

void FindEmptyRowsAndColumns(const AlienSwarm& aliens, int& emptyColsLeft, int& emptyColsRight, int& emptyRowsBottom)
{
	// number of empty columns on left
	bool found = false;

	for(int col = 0; col < NUM_ALIEN_COLUMNS && !found; col++)
	{
		for(int row = 0; row < NUM_ALIEN_ROWS && !found; row++)
		{
			if(aliens.aliens[row][col] == AS_DEAD)
			{
				if(row == NUM_ALIEN_ROWS - 1) // at the bottom row
				{
					emptyColsLeft++;
				}
			}
			else
			{
				found = true;
			}
		}
	}

	// number of empty columns on right
	found = false;

	for(int col = NUM_ALIEN_COLUMNS - 1; col >= 0 && !found; col--)
	{
		for(int row = 0; row < NUM_ALIEN_ROWS && !found; row++)
		{
			if(aliens.aliens[row][col] == AS_DEAD)
			{
				if(row == NUM_ALIEN_ROWS - 1)
				{
					emptyColsRight++;
				}
			}
			else
			{
				found = true;
			}
		}
	}

	// number of empty columns on bottom
	found = false;

	for(int row = NUM_ALIEN_ROWS - 1; row >= 0 && !found; row--)
	{
		for(int col = 0; row < NUM_ALIEN_COLUMNS - 1 && !found; col++)
		{
			if(aliens.aliens[row][col] == AS_DEAD)
			{
				if(col == NUM_ALIEN_COLUMNS - 1) //right most column
				{
					emptyRowsBottom++;
				}
			}
			else
			{
				found = true;
			}
		}
	}
}

void DestroyShields(const AlienSwarm& aliens, Shield shields[], int numberOfShields)
{
	for(int row = 0; row < NUM_ALIEN_ROWS; row++)
	{
		for(int col = 0; col < NUM_ALIEN_COLUMNS; col++)
		{
			if(aliens.aliens[row][col] == AS_ALIVE)
			{
				int xPos = aliens.position.x + col * (aliens.spriteSize.width + ALIENS_X_PADDING);
				int yPos = aliens.position.y + row * (aliens.spriteSize.height + ALIENS_Y_PADDING);

				CollideShieldsWithAliens(shields, numberOfShields, xPos, yPos, aliens.spriteSize);
			}
		}
	}
}

void CollideShieldsWithAliens(Shield shields[], int numberOfShields, int alienPositionX, int alienPositionY, const Size& size)
{
	for(int s = 0; s < NUM_SHIELDS; s++)
	{
		Shield& shield = shields[s];

		if(alienPositionX < (shield.position.x + SHIELD_SPRITE_WIDTH) && alienPositionX + size.width >= shield.position.x &&
				alienPositionY < (shield.position.y + SHIELD_SPRITE_HEIGHT) && alienPositionY + size.height >= shield.position.y)
		{
			int dy = alienPositionY - shield.position.y;
			int dx = alienPositionX - shield.position.x;

			for(int h = 0; h < size.height; h++)
			{
				int shieldY = dy + h;

				if(shieldY >= 0 && shieldY < SHIELD_SPRITE_HEIGHT)
				{
					for(int w = 0; w < size.width; w++)
					{
						int shieldX = dx + w;

						if(shieldX >= 0 && shieldX < SHIELD_SPRITE_WIDTH)
						{
							shield.sprite[shieldY][shieldX] = ' ';
						}
					}
				}
			}
			break;
		}
	}
}

bool ShouldShootBomb(const AlienSwarm& aliens)
{
	return int(rand() % (70 - int(float(NUM_ALIEN_ROWS * NUM_ALIEN_COLUMNS) /float(aliens.numAliensLeft+1))))==1;
}

void ShootBomb(AlienSwarm& aliens, int columnToShoot)
{
	int bombId = NOT_IN_PLAY;

	for(int i = 0; i < MAX_NUMBER_OF_ALENT_BOMBS; i++)
	{
		if(aliens.bombs[i].positon.x == NOT_IN_PLAY || aliens.bombs[i].positon.y == NOT_IN_PLAY)
		{
			bombId = i;
			break;
		}
	}

	for(int r = NUM_ALIEN_ROWS - 1; r >= 0; r--)
	{
		if(aliens.aliens[r][columnToShoot] == AS_ALIVE)
		{
			int xPos = aliens.position.x + columnToShoot * (aliens.spriteSize.width + ALIENS_X_PADDING) + 1; // "middle of the alien"
			int yPos = aliens.position.y + r * (aliens.spriteSize.height + ALIENS_Y_PADDING) + aliens.spriteSize.height; // bottom of the alien

			aliens.bombs[bombId].animation = 0;
			aliens.bombs[bombId].positon.x = xPos;
			aliens.bombs[bombId].positon.y = yPos;
			aliens.numberOfBombsInPlay++;
			break;
		}
	}
}

bool UpdateBombs(const Game& game, AlienSwarm& aliens, Player& player, Shield shields[], int numberOfShields)
{
	int numBombSprites = strlen(ALIEND_BOMB_SPRITE);

	for(int i = 0; i < MAX_NUMBER_OF_ALENT_BOMBS; i++)
	{
		if(aliens.bombs[i].positon.x != NOT_IN_PLAY && aliens.bombs[i].positon.y != NOT_IN_PLAY)
		{
			aliens.bombs[i].positon.y += ALIEN_BOMB_SPEED;
			aliens.bombs[i].animation = (aliens.bombs[i].animation + 1) % numBombSprites;

			Position collisionPoint;

			int shieldIndex = IsCollision(aliens.bombs[i].positon, shields, numberOfShields, collisionPoint);

			if(shieldIndex != NOT_IN_PLAY)
			{
				aliens.bombs[i].positon.x = NOT_IN_PLAY;
				aliens.bombs[i].positon.y = NOT_IN_PLAY;
				aliens.bombs[i].animation = 0;
				aliens.numberOfBombsInPlay--;

				ResolveShieldCollision(shields, shieldIndex, collisionPoint);
			}
			else if(IsCollision(aliens.bombs[i].positon, player.position, player.spriteSize))
			{
				aliens.bombs[i].positon.x = NOT_IN_PLAY;
				aliens.bombs[i].positon.y = NOT_IN_PLAY;
				aliens.bombs[i].animation = 0;
				aliens.numberOfBombsInPlay--;

				return true;
			}
			else if(aliens.bombs[i].positon.y >= game.windowSize.height)
			{
				aliens.bombs[i].positon.x = NOT_IN_PLAY;
				aliens.bombs[i].positon.y = NOT_IN_PLAY;
				aliens.bombs[i].animation = 0;
				aliens.numberOfBombsInPlay--;
			}
		}
	}

	return false;
}

bool IsCollision(const Position& projectile, const Position& spritePosition, const Size& spriteSize)
{
	return (projectile.x >= spritePosition.x && projectile.x < (spritePosition.x + spriteSize.width)) &&
			(projectile.y >= spritePosition.y && projectile.y < (spritePosition.y + spriteSize.height));
}

void ResetGame(Game& game, Player& player, AlienSwarm& aliens, Shield shields[], int numberOfShields)
{
	game.gameTimer = 0;
	//game.waitTimer = 0; // if added this game freezes after first level

	ResetPlayer(game, player);
	ResetShields(game, shields, numberOfShields);
	InitAliens(game, aliens);
}

void ResetShields(const Game& game, Shield shields[], int numberOfShields)
{
	int firstPadding = ceil(float(game.windowSize.width - SHIELD_SPRITE_WIDTH * numberOfShields)/float(numberOfShields + 1));
	int xPadding = floor(float(game.windowSize.width - SHIELD_SPRITE_WIDTH * numberOfShields)/float(numberOfShields + 1));

	for(int i = 0; i < numberOfShields; i++)
	{
		Shield & shield = shields[i];

		shield.position.x = firstPadding + i * (SHIELD_SPRITE_WIDTH + xPadding);
		shield.position.y = game.windowSize.height - PLAYER_SPRITE_HEIGHT - 1 - SHIELD_SPRITE_HEIGHT -2;

		for(int row = 0; row < SHIELD_SPRITE_HEIGHT; row++)
		{
			strcpy(shield.sprite[row] , SHIELD_SPRITE[row]);
		}
	}
}

void DrawGameOverScreen(const Game & game)
{
	string gameOverString = "Game Over!";
	string pressSpaceString = "Press Space Bar to Continue";
	string namePromptString = "Please Enter Your Name: ";

	const int yPos = game.windowSize.height/2 - 2;
	const int gameOverXPos = game.windowSize.width / 2 - gameOverString.length() / 2;
	const int pressSpaceXPos = game.windowSize.width / 2 - pressSpaceString.length() / 2;
	const int namePromptXPos =  game.windowSize.width / 2 - namePromptString.length() / 2;

	DrawString(gameOverXPos, yPos, gameOverString);
	DrawString(pressSpaceXPos, yPos + 1, pressSpaceString);
	DrawString(namePromptXPos, yPos+3, namePromptString);

	for(int i = 0; i < MAX_NUMBER_OF_CHARACTERS_IN_NAME; i++)
	{
		if(i == game.gameOverHPositionCursor)
		{
			attron(A_UNDERLINE);
		}

		DrawCharacter(game.windowSize.width/2 - MAX_NUMBER_OF_CHARACTERS_IN_NAME/2 + i, yPos+5, game.playerName[i]);

		if(i == game.gameOverHPositionCursor)
		{
			attroff(A_UNDERLINE);
		}
	}
}

void DrawIntroScreen(const Game& game)
{
	string startString = "Welcome to Text Invaders";
	string pressSpaceString = "Press Space Bar to Start";
	string pressSString = "Press (S) for High Score";

	const int yPos = game.windowSize.height/2;
	const int startStringrXPos = game.windowSize.width / 2 - startString.length() / 2;
	const int pressSpaceXPos = game.windowSize.width / 2 - pressSpaceString.length() / 2;
	const int pressSXPos = game.windowSize.width / 2 - pressSString.length() / 2;

	DrawString(startStringrXPos, yPos, startString);
	DrawString(pressSpaceXPos, yPos + 1, pressSpaceString);
	DrawString(pressSXPos, yPos + 2, pressSString);
}

void ResetUFO(const Game& game, AlienUFO& ufo)
{
	ufo.size.height = ALIEN_UFO_SPRITE_HEIGHT;
	ufo.size.width = ALIEN_UFO_SPRITE_WIDTH;
	ufo.position.x = NOT_IN_PLAY; // no UFO on screen
	ufo.position.y =  ufo.size.height;
	ufo.points = ((rand() % 4) + 1) * 50;
}

void UpdateUFO(const Game& game, AlienUFO& ufo)
{
	ufo.position.x+=1;

	if(ufo.position.x + ufo.size.width >= game.windowSize.width)
	{
		ResetUFO(game, ufo);
	}
}

void PutUFOInPlay(const Game& game, AlienUFO& ufo)
{
	ufo.position.x =  0;
}

void DrawUFO(const AlienUFO& ufo)
{
	if(ufo.position.x != NOT_IN_PLAY)
	{
		DrawSprite(ufo.position.x, ufo.position.y, ALIEN_UFO_SPRITE, ufo.size.height);
	}
}

void ResetGameOverPositionCursor(Game& game)
{
	game.gameOverHPositionCursor = 0; // first letter
	for(int i = 0; i < MAX_NUMBER_OF_CHARACTERS_IN_NAME; i++)
	{
		game.playerName[i] = 'A';
		game.gameOverVPositionCursor[i] = 0; // be at 'A'
	}
}

void AddHighScore(HighScoreTable& table, int score, const string& name)
{
	 Score highScore;

	 highScore.score = score;
	 highScore.name = name;

	 table.scores.push_back(highScore);

	 sort(table.scores.begin(), table.scores.end(), ScoreCompare);

	 SaveHighScore(table);

}

bool ScoreCompare(const Score& score1, const Score& score2)
{
	return score1.score < score2.score;
}

void DrawHightScoreTable(const Game& game, const HighScoreTable& table)
{
	string title = "High Score";

	int titleXPos = game.windowSize.width/2 - title.length()/2;
	int yPos = 5;
	int yPadding = 2;

	attron(A_UNDERLINE);
	DrawString(titleXPos, yPos, title);
	attroff(A_UNDERLINE);

	for(int i = 0; i < table.scores.size() && i < MAX_HIGH_SCORE; i++)
	{
		Score score = table.scores[i];

		mvprintw(yPos + (i+1)*yPadding, titleXPos - MAX_NUMBER_OF_CHARACTERS_IN_NAME, "%s\t\t%i", score.name.c_str(), score.score);
	}
}

void SaveHighScore(const HighScoreTable& table)
{
	ofstream outFile;

	outFile.open(FILE_NAME);

	if(outFile.is_open())
	{
		for(int i = 0; i < table.scores.size() && i < MAX_HIGH_SCORE; i++)
		{
			outFile << table.scores[i].name << " " <<  table.scores[i].score << endl;
		}

		outFile.close();
	}
}

void LoadHighScore(HighScoreTable& table)
{
	ifstream inFile;
	Score score;

	int scoreVal;
	string name;

	inFile.open(FILE_NAME);

	if(inFile.is_open())
	{
		while(!inFile.eof())
		{
			inFile >> ws;

			if(inFile.eof())
				break;

			inFile >> name >> scoreVal;
			score.name = name;
			score.score = scoreVal;

			table.scores.push_back(score);
		}

		inFile.close();
	}
}

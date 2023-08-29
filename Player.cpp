#include "Player.h"
#include <iostream>
#include <string>

// BASE CLASS //

//Create a Player with the indicated name.
Player::Player(std::string name)
	:m_name(name)
{
}

//Return the name of the player.
std::string Player::name() const
{
	return m_name;
}

//Return true if the player is human.
bool Player::isInteractive() const
{
	return false;
}

//Since this class is designed as a base class, it should have a virtual destructor.
Player::~Player()
{
}

// HUMAN PLAYER //

//Create a Player with the indicated name.
HumanPlayer::HumanPlayer(std::string name)
	:Player(name)
{
}

//Return true if the player is human.
bool HumanPlayer::isInteractive() const
{
	return true;
}

// A HumanPlayer chooses its move by prompting a person running the program for a move
int HumanPlayer::chooseMove(const Board& b, Side s) const
{
	int hole = -1;
	while (hole == -1)
	{
		std::cout <<"Select a hole, " << this->name() << ": ";
		std::cin >> hole;
		//std::cout << hole;
		if (hole > b.holes() || hole < 1)
		{
			std::cout << "Invalid hole number" << std::endl;
			hole = -1;
		}
		else if (b.beans(s, hole) == 0)
		{
			std::cout << "There are no beans in that hole." << std::endl;
			hole = -1;
		}
	}
	return hole;
}

BadPlayer::BadPlayer(std::string name)
	:Player(name)
{
}

bool BadPlayer::isInteractive() const
{
	return false;
}

int BadPlayer::chooseMove(const Board& b, Side s) const
{
	int hole = -1;
	for (int i = 1; i <= b.holes(); i++)
	{
		if (b.beans(s, i) != 0)
		{
			hole = i;
			break;
		}
	}
	std::cout << this->name() << " chooses hole " << hole << std::endl;
	return hole;
}

// SMART PLAYER //

SmartPlayer::SmartPlayer(std::string name)
	:Player(name)
{
}

bool SmartPlayer::isInteractive() const
{
	return false;
}

// evaluates the current board and returns a value based on how good the board is for the player
int SmartPlayer::evaluate(const Board& b, Side s) const
{
	if (b.beansInPlay(s) == 0 || b.beansInPlay(opponent(s)) == 0)
	{
		if (b.beansInPlay(s) + b.beans(s, 0) > b.beansInPlay(opponent(s)) + b.beans(opponent(s), 0))
		{
			return 1000;
		}
		else if (b.beansInPlay(s) + b.beans(s, 0) < b.beansInPlay(opponent(s)) + b.beans(opponent(s), 0))
		{
			return -1000;
		}
		else
		{
			return 0;
		}
	}
	if (b.beans(s, 0) > b.totalBeans() / 2)
	{
		return 1000;
	}
	else if (b.beans(opponent(s), 0) > b.totalBeans() / 2)
	{
		return -1000;
	}
	else
	{
		return b.beans(s, 0) - b.beans(opponent(s), 0);
	}
}

// use the minimax algorithm to find the best move
void SmartPlayer::minimaxMove(int depth, const Board& b, Side s, int& bestHole, int& value) const
{
	// Set the max number of recursions we want
	int numIterations = 5;
	value = -999;
	
	// If we are at the end of the game, return the value of the board
	if (b.beansInPlay(SOUTH) == 0 || b.beansInPlay(NORTH) == 0)
	{
		bestHole = -1;
		if (b.beans(s, 0) == b.beans(opponent(s), 0) + b.beansInPlay(opponent(s)))
		{
			value = 0;
			return;
		}
		// we win
		else if (b.beans(s, 0) > b.beans(opponent(s), 0) + b.beansInPlay(opponent(s)))
		{
			value = 100;
			return;
		}
		// we lose 
		else
		{
			value = -100;
			return;
		}
	}
	// check for max recursions
	else if (depth == numIterations)
	{
		value = evaluate(b, s);
		return;
	}
	
	for (int i = 1; i <= b.holes(); i++)
	{
		if (b.beans(s, i) == 0)
		{
			continue;
		}
		Board tempBoard = b;
		Side tempSide;
		int tempHole;
		int tempValue;
		tempBoard.sow(s, i, tempSide, tempHole);
		// if the last bean is in an empty hole on our side, capture
		if (tempBoard.beans(tempSide, tempHole) == 1 && tempHole != 0 && tempBoard.beans(opponent(tempSide), tempHole) != 0 && tempSide == s)
		{
			tempBoard.moveToPot(opponent(tempSide), tempHole, tempSide);
			tempBoard.moveToPot(tempSide, tempHole, tempSide);
		}
		// evaluate the board
		if (s == SOUTH)
			tempValue = tempBoard.beans(SOUTH, 0) - tempBoard.beans(NORTH, 0);
		else
			tempValue = tempBoard.beans(NORTH, 0) - tempBoard.beans(SOUTH, 0);
		
		int newBestHole;
		int newValue;
		int diff;
		
		if (s == NORTH)
		{
			// recurse if we get an extra turn
			if (tempHole == 0 && tempSide == s)
			{
				minimaxMove(depth, tempBoard, s, newBestHole, newValue);
				diff = newValue + tempValue;
				if (diff > value)
				{
					// evaluate if new value is better
					bestHole = i;
					value = diff;
				}	
				
			}
			else
			{
				// recurse the opposite side if we don't get an extra turn 
				minimaxMove(depth + 1, tempBoard, opponent(s), newBestHole, newValue);			
				diff = tempValue - newValue;
				if (diff > value)
				{
					// evaluate if new value is better
					bestHole = i;
					value = diff;
				}
			}
		}
		else if (s == SOUTH)
			// repeat for south side 
		{
			if (tempHole == 0 && tempSide == s)
			{
				minimaxMove(depth, tempBoard, s, newBestHole, newValue);
				diff = newValue + tempValue;
				if (diff > value)
				{
					bestHole = i;
					value = diff;
				}
			}			
			else
			{
				minimaxMove(depth + 1, tempBoard, opponent(s), newBestHole, newValue);
				diff = tempValue - newValue;
				if (diff > value)
				{
					bestHole = i;
					value = diff;
				}
			}
		}
	}
	// whatever bestHole is set to is the best move
	return;
}

int SmartPlayer::chooseMove(const Board& b, Side s) const
{
	// check for invalid board
	if (b.beansInPlay(SOUTH) == 0 || b.beansInPlay(NORTH) == 0)
	{
		return -1;
	}
	
	int hole; 
	// find the first nonempty hole
	for (int i = 1; i <= b.holes(); i++)
	{
		if (b.beans(s, i) != 0)
		{
			hole = i;
			break;
		}
	}
	int value = -9999;
	// choose the best move with minimaxMove
	minimaxMove(0, b, s, hole, value);

	std::cout << this->name() << " chooses hole " << hole << std::endl;
	return hole;
}
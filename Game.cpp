#include "Game.h"
#include <iostream>

//Construct a Game to be played with the indicated players on a copy of the board b.
	//The player on the south side always moves first.
Game::Game(const Board& b, Player* south, Player* north)
	: m_board(b), m_south(south), m_north(north), m_turn(SOUTH)
{
}

//Display the game's board in a manner of your choosing, provided you show the names of the players and a reasonable representation of the state of the board.
void Game::display() const
{
	// center north's name
	int numSpaces = (m_board.holes()) - 1;
	for (int i = 0; i < numSpaces; i++)
		std::cout << " ";
	// print north's name
	std::cout << m_north->name() << std::endl;
	// print north's beans
	std::cout << "  ";
	for (int i = 1; i <= m_board.holes(); i++)
	{
		std::cout << m_board.beans(NORTH, i) << " ";
	}
	std::cout << std::endl;
	// print north's pot
	std::cout << m_board.beans(NORTH, 0) << " ";
	// print south's pot
	for (int i = 1; i <= m_board.holes(); i++)
	{
		std::cout << "  ";
	}
	std::cout << m_board.beans(SOUTH, 0) << std::endl;
	// print south's beans
	std::cout << "  ";
	for (int i = 1; i <= m_board.holes(); i++)
	{
		std::cout << m_board.beans(SOUTH, i) << " ";
	}
	std::cout << std::endl;
	// center south's name
	for (int i = 0; i < numSpaces; i++)
		std::cout << " ";
	// print south's name
	std::cout << m_south->name() << std::endl;
}

//If the game is over(i.e., the move member function has been called and returned false), 
	//set over to true; otherwise, set over to false and do not change anything else.
	//If the game is over, set hasWinner to true if the game has a winner, or false if it resulted in a tie.
	//If hasWinner is set to false, leave winner unchanged; otherwise, set it to the winning side.
void Game::status(bool& over, bool& hasWinner, Side& winner) const
{
	// if both players have beans on the board, game is not over
	if (m_board.beansInPlay(NORTH) > 0 && m_board.beansInPlay(SOUTH) > 0)
	{
		over = false;
		return;
	}
	else {
		// if one player has no beans on the board, game is over
		if (m_board.beansInPlay(NORTH) == 0 || m_board.beansInPlay(SOUTH) == 0)		
		{
			over = true;
			// if one player has more beans in their pot, they win
			if (m_board.beans(NORTH, 0) + m_board.beansInPlay(NORTH) > m_board.beans(SOUTH, 0) + m_board.beansInPlay(SOUTH))
			{
				hasWinner = true;
				winner = NORTH;
			}
			else if (m_board.beans(NORTH, 0) + m_board.beansInPlay(NORTH) < m_board.beans(SOUTH, 0) + m_board.beansInPlay(SOUTH))
			{
				hasWinner = true;
				winner = SOUTH;
			}
			else
			{
				// if both players have the same number of beans in their pot, it's a tie
				hasWinner = false;
			}
		}
	}
}

bool Game::move(Side s)
{
	bool hasWinner = false;
	Side winner = SOUTH;
	std::string name;

	// if the game is over
	//if (m_over == true)
	//{
	//	// sweep all beans into the respective pots
	//	if (m_board.beansInPlay(NORTH) == 0 || m_board.beansInPlay(SOUTH) == 0)
	//	{
	//		for (int i = 1; i <= m_board.holes(); i++)
	//		{
	//			m_board.moveToPot(NORTH, i, NORTH);
	//			m_board.moveToPot(SOUTH, i, SOUTH);
	//		}
	//	}
		// returns false because no move is made 
		//return false;
	//}
	while (true) // loop until turn ends 
	{
		if (s == NORTH && m_board.beansInPlay(NORTH) == 0)
		{
			m_over = true;
			return false;
		}
		else if (s == SOUTH && m_board.beansInPlay(SOUTH) == 0)
		{
			m_over = true;
			return false;
		}
		int m_move = -1;
		if (s == SOUTH)
		{
			m_move = m_south->chooseMove(m_board, s); // get move from south player
		}
		else if (s == NORTH)
		{
			m_move = m_north->chooseMove(m_board, s); // get move from north player
		}
		if (m_move == -1) // invalid side 
		{
			break;
		}
		int endHole;
		Side endSide;
		// sow the seeds and get the ending hole and side
		m_board.sow(m_turn, m_move, endSide, endHole);
		// if turn ends on the same side
		if (endSide == m_turn)
		{
			// if last seed ends in pot
			if (endHole == 0)
			{
				//status(m_over, hasWinner, winner);
				// check for winner 
				if (s == NORTH && m_board.beansInPlay(NORTH) == 0)
				{
					m_over = true;
					break;
				}
				else if (s == SOUTH && m_board.beansInPlay(SOUTH) == 0)
				{
					m_over = true;
					break;
				}
				// otherwise, display board and get another turn
				display();
				if (m_turn == SOUTH)
				{
					name = m_south->name();
				}
				else if (m_turn == NORTH)
				{
					name = m_north->name();
				}
				std::cout << name << " gets another turn." << std::endl;
				continue;
			}
			// if last seed ends in hole with 1 bean and opposite hole has beans, capture other side's beans 
			if (m_board.beans(endSide, endHole) == 1 && m_board.beans(opponent(endSide), endHole) != 0 && endSide == m_turn)
			{
				m_board.moveToPot(m_turn, endHole, m_turn);
				m_board.moveToPot(opponent(m_turn), endHole, m_turn);
			}
			break;
		}
		// turn ended on opposite side, so move is over 
		else
		{
			break;
		}
	}
	// full turn is over, so switch turn to opponent and return true
	if (m_over == false)
		m_turn = opponent(m_turn);

	return true;
}

void Game::play()
{
	bool hasWinner = false;
	Side winner = SOUTH;
	bool enter = false;

	// if both players are not interactive, prompt user to press ENTER to continue
	if (!m_north->isInteractive() && !m_south->isInteractive())
	{
		enter = true;
	}
	display();
	// loop until game is over
	while (move(m_turn))
	{
		// display the board
		display();
		//status(m_over, hasWinner, winner);
		if (enter)
		{
			std::cout << "Press ENTER to continue";
			std::cin.ignore(10000, '\n');
		}
	}
	std::string name;
	if (m_over && (m_board.beansInPlay(NORTH) > 0 || m_board.beansInPlay(SOUTH) > 0))
	{
		display();

		if (!m_board.beansInPlay(NORTH))
			name = m_north->name();
		else
			name = m_south->name();

		std::cout << name << " has no beans left to sow." << std::endl;

		if (m_board.beansInPlay(NORTH))
			name = m_north->name();
		else
			name = m_south->name();

		std::cout << "Sweeping remaining beans into " << name << "'s pot." << std::endl;

		for (int i = 1; i <= m_board.holes(); i++)
		{
			m_board.moveToPot(NORTH, i, NORTH);
			m_board.moveToPot(SOUTH, i, SOUTH);
		}
		display();
	}
	// loop ends when game is over, so announce winner 
	status(m_over, hasWinner, winner);
	if (hasWinner)
	{
		if (winner == SOUTH)
		{
			std::cout << "The winner is " << m_south->name() << "." << std::endl;
		}
		else if (winner == NORTH)
		{
			std::cout << "The winner is " << m_north->name() << "." << std::endl;
		}
	}
	else
	{
		std::cout << "The game resulted in a tie." << std::endl;
	}
}

//Return the number of beans in the indicated hole or pot of the game's board, 
	//or −1 if the hole number is invalid. This function exists so that we and you can more easily test your program.
int Game::beans(Side s, int hole) const
{
	return m_board.beans(s, hole);
}
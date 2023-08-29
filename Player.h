#ifndef PLAYER_INCLUDED
#define PLAYER_INCLUDED

#include "Side.h"
#include "Board.h"
#include <string>

////========================================================================
//// Timer t;                 // create and start a timer
//// t.start();               // restart the timer
//// double d = t.elapsed();  // milliseconds since timer was last started
////========================================================================
//
//#include <chrono>
//
//class Timer
//{
//public:
//	Timer()
//	{
//		start();
//	}
//	void start()
//	{
//		m_time = std::chrono::high_resolution_clock::now();
//	}
//	double elapsed() const
//	{
//		std::chrono::duration<double, std::milli> diff =
//			std::chrono::high_resolution_clock::now() - m_time;
//		return diff.count();
//	}
//private:
//	std::chrono::high_resolution_clock::time_point m_time;
//};

//// Advance jumpy timer only after jumpInterval calls to elapsed
//class JumpyTimer
//{
//public:
//	JumpyTimer(int jumpInterval)
//		: m_jumpInterval(jumpInterval), m_callsMade(0)
//	{
//		actualElapsed();
//	}
//	double elapsed()
//	{
//		m_callsMade++;
//		if (m_callsMade == m_jumpInterval)
//		{
//			m_lastElapsed = m_timer.elapsed();
//			m_callsMade = 0;
//		}
//		return m_lastElapsed;
//	}
//	double actualElapsed()
//	{
//		m_lastElapsed = m_timer.elapsed();
//		return m_lastElapsed;
//	}
//private:
//	Timer m_timer;
//	int m_jumpInterval;
//	int m_callsMade;
//	int m_lastElapsed;
//};

class Player {
public:
	Player(std::string name);
	//Create a Player with the indicated name.
	std::string name() const;
	//Return the name of the player.
	virtual bool isInteractive() const;
	//Return false if the player is a computer player.
	//Return true if the player is human.Most kinds of players will be computer players.
	virtual int chooseMove(const Board& b, Side s) const = 0;
	//Every concrete class derived from this class must implement this function so that if the player 
	//were to be playing side sand had to make a move given board b, the function returns the move the player would choose.If no move is possible, return −1.
	virtual ~Player();
	//Since this class is designed as a base class, it should have a virtual destructor.
private:
	std::string m_name;
};

//A HumanPlayer chooses its move by prompting a person running the program for a move
//(reprompting if necessary until the person enters a valid hole number), and returning that choice.
//We will never test for a situation where the user doesn't enter an integer when prompted for a hole number. 
//(The techniques for dealing with the issue completely correctly are a distraction to this project, and involve 
//either a function like stoi or strtol, or the type istringstream.)
class HumanPlayer : public Player 
{
public:
	HumanPlayer(std::string name);
	bool isInteractive() const;
	int chooseMove(const Board& b, Side s) const;
};

//A BadPlayer is a computer player that chooses an arbitrary valid move and returns that choice.
class BadPlayer : public Player
{
public:
	BadPlayer(std::string name);
	bool isInteractive() const;
	int chooseMove(const Board& b, Side s) const;
};

//A SmartPlayer is a computer player that chooses a move based on a simple strategy.
class SmartPlayer : public Player
{
public:
	SmartPlayer(std::string name);
	bool isInteractive() const;
	int chooseMove(const Board& b, Side s) const;
private:
	void minimaxMove(int depth, const Board& b, Side s, int& bestHole, int& value) const;
	int evaluate(const Board& b, Side s) const;
};
#endif // PLAYER_INCLUDED
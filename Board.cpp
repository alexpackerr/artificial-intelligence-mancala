#include "Board.h"
#include <iostream>
		
Board::Board(int nHoles, int nInitialBeansPerHole)
{
	// if nHoles is not positive, act as if it were 1
	if (nHoles <= 0)
		nHoles = 1;
	// if nInitialBeansPerHole is negative, act as if it were 0
	if (nInitialBeansPerHole < 0)
		nInitialBeansPerHole = 0;
	
	// construct a board with the specified number of holes and beans per side 
	m_nHoles = nHoles;
	m_nInitialBeansPerHole = nInitialBeansPerHole;
	// create pots 
	m_northHoles.push_back(0);
	m_southHoles.push_back(0);
	// add initial beans into each hole 
	for (int i = 0; i < m_nHoles; i++)
	{
		m_northHoles.push_back(m_nInitialBeansPerHole);
		m_southHoles.push_back(m_nInitialBeansPerHole);
	}
}

Board::Board(const Board& other)
{
	// copy constructor, copy all data members
	m_nHoles = other.m_nHoles;
	m_nInitialBeansPerHole = other.m_nInitialBeansPerHole;
	m_northHoles = other.m_northHoles;
	m_southHoles = other.m_southHoles;
}

//Return the number of holes on a side(not counting the pot).
int Board::holes() const
{
	return m_nHoles;
}

//Return the number of beans in the indicated hole or pot, or −1 if the hole number is invalid.
int Board::beans(Side s, int hole) const
{
	if (hole < 0 || hole > m_nHoles)
		return -1;
	if (s == NORTH)
		return m_northHoles[hole];
	else
		return m_southHoles[hole];
}


int Board::beansInPlay(Side s) const
{
	int total = 0;
	if (s == NORTH)
	{
		// add up all the beans in the north holes
		for (int i = 1; i <= m_nHoles; i++)
			total += m_northHoles[i];
	}
	else
	{
		// add up all the beans in the south holes
		for (int i = 1; i <= m_nHoles; i++)
			total += m_southHoles[i];
	}
	// returns total number of beans in play on that side 
	return total;
}

//Return the total number of bans in the game, including any in the pots.
int Board::totalBeans() const
{
	return beansInPlay(NORTH) + beansInPlay(SOUTH) + m_northHoles[0] + m_southHoles[0];
}

	// Otherwise, it will return true after sowing the beans : 
		//the beans are removed from hole(s, hole) and sown counterclockwise, including s's pot if encountered, but skipping s's opponent's pot. 
		//The function sets the parameters endSide and endHole to the side and hole where the last bean was placed. 
		//(This function does not make captures or multiple turns; different Kalah variants have different rules about these issues, so dealing with them should not be the responsibility of the Board class.)
bool Board::sow(Side s, int hole, Side& endSide, int& endHole)
{
	// If the hole indicated by(s, hole) is empty or invalid or a pot, 
	// this function returns false without changing anything.
	if (hole < 1 || hole > m_nHoles)
	{
		return false;
	}
	int beans = 0;
	if (s == NORTH)
	{
		//get the number of beans in the hole
		beans = m_northHoles[hole]; 
		if (beans == 0)
			return false;
		//empty the hole
		m_northHoles[hole] = 0; 
		
		int it = hole - 1;
		while(beans != 0)
		{
			// loop in reverse for north side 
			for (int i = it; i > 0 && beans != 0; i--)
			{
				// add a bean
				m_northHoles[i]++;
				beans--;
				if (beans == 0)
				{
					endSide = NORTH;
					endHole = i;
					return true;
				}
			}
			if (beans != 0)
			{
				m_northHoles[0]++;
				beans--;
			}
			if (beans == 0)
			{
				endSide = NORTH;
				endHole = 0;
				return true;
			}
			// if there are still beans left, go to south side
			//it = m_nHoles;
			for (int i = 1; i < m_southHoles.size(); i++)
			{
				m_southHoles[i]++;
				beans--;
				if (beans == 0)
				{
					endSide = SOUTH;
					endHole = i;
					return true;
				}
			}
			if (beans != 0)
			{
				it = m_northHoles.size() - 1;
			}
		}
		return true;
	}
	else
	{
		// repeat for south side 
		// get number of beans in hole 
		int beans = m_southHoles[hole];
		if (beans == 0)
			return false;
		// empty hole 
		m_southHoles[hole] = 0;

		int it = hole + 1;
		while (beans != 0)
		{
			for (int i = it; i < m_southHoles.size() && beans != 0; i++)
			{
				// add a bean 
				m_southHoles[i]++;
				beans--;
				if (beans == 0)
				{
					endSide = SOUTH;
					endHole = i;
					return true;
				}
			}
			// add to south's pot if possible 
			if (beans != 0)
			{
				m_southHoles[0]++;
				beans--;
			}
			if (beans == 0)
			{
				endSide = SOUTH;
				endHole = 0;
				return true;
			}
			// if there are still beans, go to north side
			it = 1;
			for (int i = m_nHoles; i > 0; i--)
			{
				m_northHoles[i]++;
				beans--;
				if (beans == 0)
				{
					endSide = NORTH;
					endHole = i;
					return true;
				}
			}
		}
	}
	return true;
}

//If the indicated hole is invalid or a pot, return false without changing anything.
	//Otherwise, move all the beans in hole(s, hole) into the pot belonging to potOwnerand return true.
bool Board::moveToPot(Side s, int hole, Side potOwner)
{
	if (hole < 1 || hole > m_nHoles)
		return false;
	if (potOwner == NORTH && s == NORTH)
	{
		m_northHoles[0] += m_northHoles[hole];
		m_northHoles[hole] = 0;
		return true;
	}
	else if (potOwner == NORTH && s == SOUTH)
	{
		m_northHoles[0] += m_southHoles[hole];
		m_southHoles[hole] = 0;
		return true;
	}
	else if (potOwner == SOUTH && s == SOUTH)
	{
		m_southHoles[0] += m_southHoles[hole];
		m_southHoles[hole] = 0;
		return true;
	}
	else
	{
		m_southHoles[0] += m_northHoles[hole];
		m_northHoles[hole] = 0;
		return true;
	}
	
}

//If the indicated hole is invalid or beans is negative, this function returns false without changing anything.
//Otherwise, it will return true after setting the number of beans in the indicated hole or pot to the value of the third parameter. 
//(This could change what beansInPlay and totalBeans return if they are called later.) This function exists solely so that weand you can more easily test your program : 
//None of your code that implements the member functions of any class is allowed to call this function directly or indirectly. (We'll show an example of its use below.)
bool Board::setBeans(Side s, int hole, int beans)
{
	if (hole < 0 || hole > m_nHoles || beans < 0)
		return false;
	if (s == NORTH)
		m_northHoles[hole] = beans;
	else
		m_southHoles[hole] = beans;
	
	return true;
}
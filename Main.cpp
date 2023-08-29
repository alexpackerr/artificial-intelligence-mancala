//// PLAY GAME //
//#include "Board.h"
//#include "Game.h"
//
//
//int main()
//{
//	HumanPlayer a("Lexi");
//	HumanPlayer m("Dad");
//	Board b(6, 4);
//	//b.setBeans(SOUTH, 6, 1);
//	//b.setBeans(NORTH, 2, 1);
//	//b.setBeans(SOUTH, 5, 2);
//	//b.setBeans(SOUTH, 3, 1);
//	Game g(b, &a, &m);
//	g.play();
//}
//
//// BAD PLAYERS PLAY GAME //
//#include "Board.h"
//#include "Game.h"
//#include "Player.h"
//int main()
//{
//	BadPlayer bp1("Bart");
//	BadPlayer bp2("Homer");
//	Board b(3, 2);
//	Game g(b, &bp1, &bp2);
//	g.play();
//}

//// timer tests
//#include "Player.h"
//#include "Board.h"
//#include "Game.h"
//#include <iostream>
//#include <cassert>
//
//unsigned long f_helper(int n, double timeLimit, JumpyTimer& timer);
//unsigned long f(int n);
//
//unsigned long f(int n)
//{
//	double timeLimit = 4900;
//	JumpyTimer timer(1000);
//	unsigned long result = f_helper(n, timeLimit, timer);
//	std::cout << timer.elapsed() << " ms" << std::endl;
//	return result;
//}
//
//unsigned long f_helper(int n, double timeLimit, JumpyTimer& timer)
//{
//	unsigned long callCount = 1;
//	if (n == 0)
//	{
//		callCount += 0;
//	}
//	else if (timeLimit <= 0)
//	{
//		callCount += 0;
//	}
//	else
//	{
//		for (int branchesLeft = 10; branchesLeft > 0; branchesLeft--)
//		{
//			double thisBranchLimit = timeLimit / branchesLeft;
//			double startTime = timer.elapsed();
//			callCount += f_helper(n - 1, thisBranchLimit, timer);
//			timeLimit -= (timer.elapsed() - startTime);
//			if (timeLimit <= 0)
//				timeLimit = 0;
//		}
//	}
//	return callCount;
//}
//
//int main()
//{
//	unsigned long result = f(10);
//	std::cout << result / 1000000.0 << " million calls" << std::endl;
//}

//// BAD PLAYER VS HUMAN PLAYS GAME
//#include "Board.h"
//#include "Game.h"
//#include "Player.h"
//
//int main()
//{
//	HumanPlayer hp("Dane");
//	BadPlayer bp("Beep Boop Doop");
//	Board b(3, 2);
//	Game g(b, &hp, &bp);
//	g.play();
//}

// SMART PLAYER VS HUMAN PLAYS GAME
#include "Board.h"
#include "Game.h"
#include "Player.h"

int main()
{
	HumanPlayer hp("Isaac");
	SmartPlayer bp("Beep beep boop");
	Board b(6, 4);
	Game g(b, &hp, &bp);
	g.play();
}

//// SMART PLAYER VS BAD PLAYER
//#include "Board.h"
//#include "Game.h"
//#include "Player.h"
//
//int main()
//{
//	BadPlayer hp("Marge");
//	SmartPlayer bp("Homer");
//	Board b(6, 4);
//	Game g(b, &hp, &bp);
//	g.play();
//}

//// TEST 1 //
//#include "Board.h"
//#include "Side.h"
//#include <iostream>
//#include <cassert>
//using namespace std;
//
//void doBoardTests()
//{
//	Board b(3, 2);
//	assert(b.holes() == 3 && b.totalBeans() == 12 &&
//		b.beans(SOUTH, POT) == 0 && b.beansInPlay(SOUTH) == 6);
//	b.setBeans(SOUTH, 1, 1);
//	b.moveToPot(SOUTH, 2, SOUTH);
//	assert(b.totalBeans() == 11 && b.beans(SOUTH, 1) == 1 &&
//		b.beans(SOUTH, 2) == 0 && b.beans(SOUTH, POT) == 2 &&
//		b.beansInPlay(SOUTH) == 3);
//	Side es;
//	int eh;
//	b.sow(SOUTH, 3, es, eh);
//	assert(es == NORTH && eh == 3 && b.beans(SOUTH, 3) == 0 &&
//		b.beans(NORTH, 3) == 3 && b.beans(SOUTH, POT) == 3 &&
//		b.beansInPlay(SOUTH) == 1 && b.beansInPlay(NORTH) == 7);
//	assert(b.beans(NORTH, 3) == 3);
//}
//
//int main()
//{
//	doBoardTests();
//	cout << "Passed all tests" << endl;
//}

//// TEST 2 // 
//#include "Game.h"
//#include "Player.h"
//#include "Board.h"
//#include "Side.h"
//#include <iostream>
//#include <cassert>
//using namespace std;
//
//void doGameTests()
//{
//	BadPlayer bp1("Bart");
//	BadPlayer bp2("Homer");
//	Board b(3, 0);
//	b.setBeans(SOUTH, 1, 2);
//	b.setBeans(NORTH, 2, 1);
//	b.setBeans(NORTH, 3, 2);
//	Game g(b, &bp1, &bp2);
//	bool over;
//	bool hasWinner;
//	Side winner;
//	//    Homer
//	//   0  1  2
//	// 0         0
//	//   2  0  0
//	//    Bart
//	g.status(over, hasWinner, winner);
//	assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 0 &&
//		g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 1 && g.beans(NORTH, 3) == 2 &&
//		g.beans(SOUTH, 1) == 2 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 0);
//
//	g.move(SOUTH);
//	//   0  1  0
//	// 0         3
//	//   0  1  0
//	g.status(over, hasWinner, winner);
//	assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
//		g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 1 && g.beans(NORTH, 3) == 0 &&
//		g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 1 && g.beans(SOUTH, 3) == 0);
//
//	g.move(NORTH);
//	//   1  0  0
//	// 0         3
//	//   0  1  0
//	g.status(over, hasWinner, winner);
//	assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
//		g.beans(NORTH, 1) == 1 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
//		g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 1 && g.beans(SOUTH, 3) == 0);
//
//	g.move(SOUTH);
//	//   1  0  0
//	// 0         3
//	//   0  0  1
//	g.status(over, hasWinner, winner);
//	assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
//		g.beans(NORTH, 1) == 1 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
//		g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 1);
//
//	g.move(NORTH);
//	//   0  0  0
//	// 1         4
//	//   0  0  0
//	g.status(over, hasWinner, winner);
//	assert(over && g.beans(NORTH, POT) == 1 && g.beans(SOUTH, POT) == 4 &&
//		g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
//		g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 0);
//	assert(hasWinner && winner == SOUTH);
//}
//
//int main()
//{
//	doGameTests();
//	cout << "Passed all tests" << endl;
//}

//// TEST 3 //
//#include "Player.h"
//#include "Board.h"
//#include "Side.h"
//#include <iostream>
//#include <cassert>
//using namespace std;
//
//void doPlayerTests()
//{
//	HumanPlayer hp("Marge");
//	assert(hp.name() == "Marge" && hp.isInteractive());
//	BadPlayer bp("Homer");
//	assert(bp.name() == "Homer" && !bp.isInteractive());
//	SmartPlayer sp("Lisa");
//	assert(sp.name() == "Lisa" && !sp.isInteractive());
//	Board b(3, 2);
//	b.setBeans(SOUTH, 2, 0);
//	cout << "=========" << endl;
//	int n = hp.chooseMove(b, SOUTH);
//	cout << "=========" << endl;
//	assert(n == 1 || n == 3);
//	n = bp.chooseMove(b, SOUTH);
//	assert(n == 1 || n == 3);
//	n = sp.chooseMove(b, SOUTH);
//	assert(n == 1 || n == 3);
//}
//
//int main()
//{
//	doPlayerTests();
//	cout << "Passed all tests" << endl;
//}

//#include "Board.h"
//#include "Player.h"
//#include "Game.h"
//#include "Side.h"
//
//#include <iostream>
//#include <cassert>
//using namespace std;
//
//void testcases();
//
//int main()
//{
//    testcases();
//    //    Board board(6,4);
//    //    board.moveToPot(NORTH, 1, NORTH);
//    //    board.moveToPot(NORTH, 2, NORTH);
//    //    board.moveToPot(NORTH, 3, NORTH);
//    //    board.moveToPot(NORTH, 4, NORTH);
//    //    board.moveToPot(NORTH, 5, NORTH);
//    //    board.moveToPot(NORTH, 6, NORTH);
//    //    board.setBeans(NORTH, 0, 0);
//    //
//    //    SmartPlayer smartP("smart");
//    //    HumanPlayer humanP("caro");
//    //
//    //    Game game(board,&smartP,&humanP);
//    //    game.move();
//    //    game.display();
//    //    game.play();
//
//    return 0;
//}
////protect from capture
////    Board e(6, 0);
////    e.setBeans(NORTH, 4, 1);
////    e.setBeans(SOUTH, 2, 1);
////    e.setBeans(SOUTH, 5, 1);
//    //do a capture
////    Board e(6, 0);
////    e.setBeans(NORTH, 6, 1);
////    e.setBeans(SOUTH, 2, 1);
////    e.setBeans(SOUTH, 5, 1);
//
//void testcases()
//{
//    // board test
//    int nHoles = 6;
//    int nInitialBeansPerHole = 4;
//    Board a(nHoles, nInitialBeansPerHole);
//
//    assert(a.beansInPlay(NORTH) == 4 * 6);
//    assert(a.beansInPlay(SOUTH) == 4 * 6);
//    assert(a.totalBeans() == 4 * 6 * 2);
//    assert(a.setBeans(NORTH, 3, 0) == 1);
//    assert(a.setBeans(NORTH, -1, 0) == 0);
//    assert(a.setBeans(NORTH, 7, 0) == 0);
//    assert(a.totalBeans() == 4 * 6 * 2 - 4);
//    assert(a.beansInPlay(NORTH) == 4 * 5);
//    assert(a.beansInPlay(SOUTH) == 4 * 6);
//    assert(a.setBeans(NORTH, 3, 4) == 1);
//    Side endSide = SOUTH;
//    int endHole = 999;
//    assert(a.sow(NORTH, 3, endSide, endHole) == 1
//        && endSide == SOUTH
//        && endHole == 1);
//    //  5 5 0 4 4 4
//    //1              0
//    //  5 4 4 4 4 4
//    assert(a.totalBeans() == 4 * 6 * 2);
//    assert(a.beansInPlay(NORTH) == 4 * 6 - 2);
//    assert(a.beansInPlay(SOUTH) == 4 * 6 + 1);
//    assert(a.holes() == 6);
//    assert(a.totalBeans() == 4 * 6 * 2);
//
//    Board board(6, 3);
//    //test beans
//    assert(board.beans(NORTH, 0) == 0);
//    assert(board.beans(NORTH, 1) == 3);
//    assert(board.beans(NORTH, 2) == 3);
//    assert(board.beans(NORTH, 3) == 3);
//    assert(board.beans(NORTH, 4) == 3);
//    assert(board.beans(NORTH, 5) == 3);
//    assert(board.beans(NORTH, 6) == 3);
//    assert(board.beans(NORTH, 7) == -1);
//    assert(board.beans(NORTH, -1) == -1);
//    assert(board.beans(SOUTH, 0) == 0);
//    assert(board.beans(SOUTH, 1) == 3);
//    assert(board.beans(SOUTH, 2) == 3);
//    assert(board.beans(SOUTH, 3) == 3);
//    assert(board.beans(SOUTH, 4) == 3);
//    assert(board.beans(SOUTH, 5) == 3);
//    assert(board.beans(SOUTH, 6) == 3);
//    assert(board.beans(SOUTH, 7) == -1);
//    assert(board.beans(SOUTH, 8) == -1);
//    assert(board.beans(SOUTH, 8) == -1);
//
//    //test totalbeans and set and beansInPlay
//    assert(board.beansInPlay(NORTH) == 18);
//    assert(board.beansInPlay(SOUTH) == 18);
//    assert(board.totalBeans() == 2 * 18);
//    assert(board.setBeans(NORTH, 1, 20));
//    assert(board.beansInPlay(NORTH) == 18 - 3 + 20);
//    assert(board.beansInPlay(SOUTH) == 18);
//    assert(!board.setBeans(NORTH, -1, 20));
//    assert(!board.setBeans(NORTH, 9, 20));
//    assert(board.beans(NORTH, 1) == 20);
//    assert(board.totalBeans() == 18 * 2 - 3 + 20);
//    assert(board.setBeans(NORTH, 0, 20));
//    assert(board.totalBeans() == 18 * 2 - 3 + 20 * 2);
//
//    //test movetopot
//    assert(board.moveToPot(NORTH, 2, NORTH));
//    assert(board.beans(NORTH, 0) == 23);
//
//    assert(board.moveToPot(NORTH, 1, NORTH));
//    assert(!board.moveToPot(NORTH, 0, NORTH));
//    assert(board.moveToPot(NORTH, 2, SOUTH));
//    assert(board.moveToPot(SOUTH, 2, SOUTH));
//    assert(!board.moveToPot(SOUTH, 0, SOUTH));
//
//    //test sow
//    Board c(6, 4);
//    //    Side endSide;
//    int endhole;
//    //Test the Sow Function
//    assert(c.sow(NORTH, 3, endSide, endhole));
//    assert(endhole == 1);
//    assert(endSide == SOUTH);
//
//    assert(c.sow(NORTH, 1, endSide, endhole));
//    assert(endhole == 4);
//    assert(endSide == SOUTH);
//
//    assert(!c.sow(NORTH, 0, endSide, endhole));
//    assert(c.setBeans(SOUTH, 1, 20));
//    assert(c.sow(SOUTH, 1, endSide, endhole));
//    assert(endhole == 6);
//    assert(endSide == NORTH);
//    assert(c.sow(SOUTH, 1, endSide, endhole));
//    assert(endhole == 2);
//    assert(endSide == SOUTH);
//
//    cout << "board -- all passed\n";
//
//    //test player
//    //human player
//    HumanPlayer will("will");
//    assert(will.isInteractive());
//
//    //bad player
//    Board d(6, 4);
//    assert(d.setBeans(SOUTH, 1, 0));
//    assert(d.setBeans(SOUTH, 2, 0));
//    assert(d.setBeans(SOUTH, 3, 0));
//    assert(d.setBeans(SOUTH, 4, 0));
//    assert(d.setBeans(SOUTH, 5, 0));
//    assert(d.setBeans(SOUTH, 6, 0));
//    BadPlayer bad("BadComputer");
//    assert(!bad.isInteractive());
//    assert(bad.name() == "BadComputer");
//    //The bad player should choose the the lowest possible hole that is availiable
//    assert(bad.chooseMove(d, SOUTH) == -1);
//    assert(bad.chooseMove(d, NORTH) == 1);
//    d.sow(NORTH, 1, endSide, endhole);
//    assert(bad.chooseMove(d, NORTH) == 2);
//    d.sow(NORTH, 2, endSide, endhole);
//    assert(bad.chooseMove(d, NORTH) == 1);
//
//
//    cout << "player -- all passed\n";
//
//    //test game class
//
//    BadPlayer bp1("Bart");
//    BadPlayer bp2("Homer");
//    Board f(3, 0);
//    f.setBeans(SOUTH, 1, 2);
//    f.setBeans(NORTH, 2, 1);
//    f.setBeans(NORTH, 3, 2);
//    Game g(f, &bp1, &bp2);
//    bool over;
//    bool hasWinner;
//    Side winner;
//    g.status(over, hasWinner, winner);
//    assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 0 &&
//        g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 1 && g.beans(NORTH, 3) == 2 &&
//        g.beans(SOUTH, 1) == 2 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 0);
//
//    g.move(SOUTH);
//    g.status(over, hasWinner, winner);
//    assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
//        g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 1 && g.beans(NORTH, 3) == 0 &&
//        g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 1 && g.beans(SOUTH, 3) == 0);
//    g.move(NORTH);
//    g.status(over, hasWinner, winner);
//    assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
//        g.beans(NORTH, 1) == 1 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
//        g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 1 && g.beans(SOUTH, 3) == 0);
//    g.move(SOUTH);
//    g.status(over, hasWinner, winner);
//    assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
//        g.beans(NORTH, 1) == 1 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
//        g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 1);
//    g.move(NORTH);
//
//    Board alpha(1, 1);
//    alpha.setBeans(NORTH, 0, 9);
//    alpha.setBeans(NORTH, 1, 2);
//    alpha.setBeans(SOUTH, 1, 0);
//    alpha.setBeans(SOUTH, 0, 10);
//
//    BadPlayer cert("billy");
//    BadPlayer dad("jef");
//    Game beta(alpha, &cert, &dad);
//
//    bool ov = false;
//    bool haW = false;
//    Side wen = SOUTH;
//    beta.status(ov, haW, wen);
//    assert(ov && haW && wen == NORTH);
//    alpha.setBeans(NORTH, 1, 1);
//    Game gamma(alpha, &cert, &dad);
//    gamma.status(ov, haW, wen);
//    assert(ov && !haW);
//
//    cout << "game -- all passed\n";
//
//    //smart player tests
//    SmartPlayer smartP("smart");
//    HumanPlayer humanP("caro");
//
//    //  do a capture
//    Board board1(4, 0);
//    board1.setBeans(NORTH, 2, 1);
//    board1.setBeans(SOUTH, 1, 1);
//    board1.setBeans(SOUTH, 3, 1);
//    Game game1(board1, &smartP, &humanP);
//    assert(smartP.chooseMove(board1, SOUTH) == 1);
//
//      //do a capture
//    Board board0(4, 0);
//    board0.setBeans(SOUTH, 2, 1);
//    board0.setBeans(NORTH, 1, 1);
//    board0.setBeans(NORTH, 3, 1);
//    Game game0(board0, &humanP, &smartP);
//    assert(smartP.chooseMove(board0, NORTH) == 1);
//
//    // protect
//    Board board2(4, 0);
//    board2.setBeans(NORTH, 2, 1);
//    board2.setBeans(SOUTH, 1, 1);
//    board2.setBeans(SOUTH, 3, 1);
//    board2.setBeans(SOUTH, 2, 1);
//    Game game2(board2, &smartP, &humanP);
//        game2.display();
//        game2.move(SOUTH);
//        game2.display();
//        assert(smartP.chooseMove(board2, SOUTH) == 1);
//
//
//    // protect from capture
//    Board board3(5, 0);
//    board3.setBeans(NORTH, 3, 1);
//    board3.setBeans(SOUTH, 1, 1);
//    board3.setBeans(SOUTH, 4, 1);
//    Game game3(board3, &smartP, &humanP);
//    assert(smartP.chooseMove(board3, SOUTH) == 4);
//
//    // do a capture
//    Board board4(6, 1);
//    board4.setBeans(NORTH, 3, 50);
//    board4.setBeans(SOUTH, 3, 0);
//    board4.setBeans(SOUTH, 6, 0);
//    Game game4(board4, &smartP, &humanP);
//    assert(smartP.chooseMove(board4, SOUTH) == 2);
//
//    // put a bean in the pot then capture better player
//    Board board5(6, 1);
//    board5.setBeans(SOUTH, 2, 3);
//    board5.setBeans(SOUTH, 4, 0);
//    board5.setBeans(SOUTH, 5, 0);
//    board5.setBeans(SOUTH, 5, 0);
//    board5.setBeans(NORTH, 5, 19);
//    board5.setBeans(SOUTH, 6, 0);
//    Game game5(board5, &smartP, &humanP);
//    assert(smartP.chooseMove(board5, SOUTH) == 2);
//
//    // do a hard capture
//    Board board6(6, 1);
//    board6.setBeans(SOUTH, 2, 3);
//    board6.setBeans(SOUTH, 4, 0);
//    board6.setBeans(SOUTH, 5, 0);
//    board6.setBeans(SOUTH, 5, 0);
//    board6.setBeans(NORTH, 5, 19);
//    Game game6(board6, &smartP, &humanP);
//    assert(smartP.chooseMove(board6, SOUTH) == 6);
//}
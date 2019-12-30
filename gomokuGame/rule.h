#pragma once
#include "GA.h"
#include <string.h>
#include <stdio.h>
#include <vector>
#include <algorithm>
/*********************版本一*************************/
#define weightOwn5     500000		// 口oooo口  AI在該空位下能形成活五
#define weightEnemy5   49000		//			 對方在該空位下能形成活五

#define weightOwn4_live     10000	// 口ooo口   AI在該空位下能形成活四-有两個連五點
#define weightOwn4		    9500	//		     AI在該空位下能形成四四
#define weightEnemy4		8500	//			 對方在該空位下能否成為四四
#define weightEnemy4_live	7000	//			 對方在該空位下能否成為活四

#define weightOwn4_died     3500	//		     AI在該空位下能形成死四
#define weightOwn3_live     3000	// 口oo口    AI在該空位下能形成活三
#define weightEnemy3_live   2800	//			 對方在該空位下能形成活三

#define weightOwn2_live     1600	// 口o口     AI在該空位下能形成活二
#define weightEnemy2_live   1400	//			 對方在該空位下能形成活二

#define weightEnemy4_died     500		//		 對方在該空位是否能形成死四
#define weightEnemy3_died   300	    //			 電腦在該空位是否能形成死三
#define weightOwn3_died     100     //			 對方在該空位是否能形成死三

/*********************版本二*************************/
#define longLink		150000	//長連		至少五顆棋子連在一起
#define live4			50000   //活四		011110
								//死四活三
#define die4			100
#define rush4			1000
#define live3			500		//活三		01110 010110
#define rush3			200
#define die3			10
#define live2			50		//活二		00110 01010 010010
#define rush2			5
#define die2			3
#define scoreMax 150000
#define scoreSecond 50000

#define gomokuline 15


 struct coordinate
{
	int x;
	int y;
	/*******************
	  -------------
	  | 0 | 1 | 2 |
	  -------------
	  | 3 | o | 4 |
	  -------------
	  | 5 | 6 | 7 |
	  -------------
	  [x][y][LatticeIndex]=weight
	**********************/
	int weightLattice[8];
};

 struct coordinate_
 {
	 int x;
	 int y;
	 std::string color;//1:black 2:white
	 /*******************
	   -------------
	   | 0 | 1 | 2 |
	   -------------
	   | 3 | o | 4 |
	   -------------
	   | 5 | 6 | 7 |
	   -------------
	   [x][y][LatticeIndex]=weight
	 **********************/
	 int ownLattice[8];
	 int enemyLattice[8];
	 //[0]:直連  [1]:橫漣  [2]:左上至右下斜連 [3]:右上至左下的斜連
	 int weightLattice[4];
 };


 public class rule
{
	public:
		rule();
		void calculationNextStep(int recodeList[][gomokuline], std::string user);
		int bestX;
		int bestY;
		int bestWeight = -1;
		int IsWin(int X, int Y, int recodeList[][gomokuline], std::string user);
	
		/*new function about record count of the chess*/
		coordinate_ calculationChessCount(int X, int Y, int recodeList[][gomokuline], std::string user);
		coordinate_ calculationWeight(coordinate_ countSet, std::string user);

		int getLongLink(coordinate_ countSet, std::string user, int recodeList[][gomokuline]);
		int getLive4(coordinate_ countSet, std::string user);
		int getLive3(coordinate_ countSet, std::string user);
		int getLive2(coordinate_ countSet, std::string user);
		int getRush4(coordinate_ countSet, std::string user);
		int getRush3(coordinate_ countSet, std::string user);
		int getRush2(coordinate_ countSet, std::string user);
		int getDie4(coordinate_ countSet, std::string user);
		int getDie3(coordinate_ countSet, std::string user);
		int getDie2(coordinate_ countSet, std::string user);

		int computing2_1(point p, std::string user, int recodeList[][gomokuline]);
		bool checkChess(point p, int recodeList[][gomokuline]);
		int getWhoArrayValue(std::string user, std::string identity);

		/* 小函式 */
		int calculationPositionX(int x, int arrayIndex, int currentLinkCount);
		int calculationPositionY(int y, int arrayIndex, int currentLinkCount);
	
		// step1. 依據XY位置搜尋附近區域直到整個外圍都是空著(pic.米字)
		std::vector<std::vector<int>> findNeedCalculationCoordinate(int recodeList[][gomokuline]);
private:
		//step2. 賦予預測座標權重
		coordinate  calculationSomeoneWeight(int X,int Y, int recodeList[][gomokuline], std::string user);
		//step3. get total weight
		int calculationTotalWeight(coordinate weightSet);

		/*  計算權重相關函式  */
		//完成下一步棋將5連線的函式
		coordinate getWeight5(coordinate weightSet, int recodeList[][gomokuline], std::string user);
		coordinate getWeight4(coordinate weightSet, int recodeList[][gomokuline], std::string user);
		coordinate getWeight3(coordinate weightSet, int recodeList[][gomokuline], std::string user);
		coordinate getWeight2(coordinate weightSet, int recodeList[][gomokuline], std::string user);

		/* 小函式 */

		int calculationDoubleWeight(coordinate weightSet);
		int checkDirectOnChessForSingle(point p, int index, std::string user, int recodeList[][gomokuline]);
	

		
};




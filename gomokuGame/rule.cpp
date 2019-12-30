#include "stdafx.h"
#include "rule.h"

rule::rule()
{
}

void rule::calculationNextStep(int recodeList[][gomokuline],std::string user)
{
	coordinate weight,bestCoordinate;
	coordinate_ countCoord;
	int currentTotalWeight;
	std::vector<std::vector<int>> canForecastingPosition;
	// step1. 依據XY位置搜尋附近區域直到只個外圍都是空著
	canForecastingPosition = findNeedCalculationCoordinate(recodeList);
	bestX = 0;
	bestY = 0;
	bestWeight = -1;
	// step2. 依序丟入要預測的位置，計算每位置的權重
	for (int i = 0; i < gomokuline; i++)
	{
		for (int j = 0; j < gomokuline; j++)
		{
			if (canForecastingPosition[i][j] == 0)
			{
				// (x,y,棋盤目前的紀錄)
				weight = calculationSomeoneWeight(i, j, recodeList, user);
				//step3. 計算最值得下的步
				currentTotalWeight = calculationTotalWeight(weight);
				if (bestWeight < currentTotalWeight)
				{
					bestWeight = currentTotalWeight;
					bestX = weight.x;
					bestY = weight.y;
				}
				//countCoord=calculationChessCount(i, j, recodeList, user);
				//countCoord = calculationWeight(countCoord, user);
				/*	for (int j = 0; j < 7; j++)
					{
						printf("(%d,%d)  own:%d enemy:%d \n", countCoord.x, countCoord.y, countCoord.ownLattice[j], countCoord.enemyLattice[j]);
					}*/
				
			}
		}
	}

}

int rule::IsWin(int X, int Y, int recodeList[][gomokuline], std::string user)
{
	//預測位置的[]滿足四個同顏色連在一起的成就
	int totaaLinkCount = 5;
	int linkCountME;
	coordinate coordinate_;
	coordinate_.x = X;
	coordinate_.y = Y;
	for (int i = 0; i < sizeof(coordinate_.weightLattice) / sizeof(coordinate_.weightLattice[0]); i++)
		coordinate_.weightLattice[i] = 0;
	//[0-7]的權重


	for (int arrayIndex = 0; arrayIndex < sizeof(coordinate_.weightLattice) / sizeof(coordinate_.weightLattice[0]); arrayIndex++)
	{
		linkCountME = 0;
		for (int j = 0, linkCountMe_ = 0; j <= totaaLinkCount; j++)
		{
			if (recodeList[calculationPositionX(coordinate_.x, arrayIndex, j)][calculationPositionY(coordinate_.y, arrayIndex, j)] == getWhoArrayValue(user, "own"))
			{
				linkCountMe_++;
				linkCountME = linkCountMe_;
				printf(" !!!!!!sorce:%d %d %d  %d\n", recodeList[calculationPositionX(coordinate_.x, arrayIndex, j)][calculationPositionY(coordinate_.y, arrayIndex, j)], calculationPositionX(coordinate_.x, arrayIndex, j), calculationPositionY(coordinate_.x, arrayIndex, j), linkCountME);
			}
			else
			{
			}
		}
		coordinate_.weightLattice[arrayIndex] = linkCountME;
	}
	if ((coordinate_.weightLattice[0] + coordinate_.weightLattice[7] - 1) == 5 ||
		(coordinate_.weightLattice[1] + coordinate_.weightLattice[6] - 1) == 5 ||
		(coordinate_.weightLattice[2] + coordinate_.weightLattice[5] - 1) == 5 ||
		(coordinate_.weightLattice[3] + coordinate_.weightLattice[4] - 1) == 5)
	{
		return 1;
	}
	else 
	{
		
		return 0;
	}
}

std::vector<std::vector<int>> rule::findNeedCalculationCoordinate(int recodeList[][gomokuline])
{
	std::vector<int> corrdinate_;
	corrdinate_.assign(gomokuline, -1);
	std::vector<std::vector<int>> corrdinate;
	corrdinate.assign(gomokuline, corrdinate_);

	for (int x = 0; x < gomokuline; x++)
	{
		for (int y = 0; y < gomokuline; y++)
		{
			if (recodeList[x][y] != 0)
			{
				for (int i = x - 1; i <= x + 1; i ++) 
				{
					for (int j = y - 1; j <= y + 1; j ++)
					{
						//過濾邊界
						if (i < 0 || j<0 || i> gomokuline - 1 || j>gomokuline - 1)
							continue;
						if (recodeList[i][j] == 0)
						{
							corrdinate[i][j] = 0;
						}
					}
				}
			}
		}
	}/*
	printf("\n\n\n");
	for (int i = 0; i < gomokuline; i++)
	{
		for (int j = 0; j < gomokuline; j++)
		{
			printf("%d  ", corrdinate[j][i]);
		}
		printf("\n");
	}*/
	return corrdinate;
}

coordinate rule::calculationSomeoneWeight(int X, int Y, int recodeList[][gomokuline], std::string user)
{	/* init (預測位置，周圍權重集合)*/
	coordinate message;
	message.x = X;
	message.y = Y;
	for (int i = 0; i < sizeof(message.weightLattice) / sizeof(message.weightLattice[0]); i++)
		message.weightLattice[i] = 0;

	//是否能連成五條線
	message = getWeight5(message,recodeList,user);
	message = getWeight4(message, recodeList, user);
	//message = getWeight3(message, recodeList, user);
	message = getWeight2(message, recodeList, user);
	//for (int i = 0; i < sizeof(message.weightLattice) / sizeof(message.weightLattice[0]); i++)
	//	printf("wwww%d\n",message.weightLattice[i]);
	
	return message;
}

int rule::calculationTotalWeight(coordinate weightSet)
{
	int totalWeight = 0;
	for (int i = 0; i < sizeof(weightSet.weightLattice) / sizeof(weightSet.weightLattice[0]); i++)
		totalWeight += weightSet.weightLattice[i];
	return totalWeight;
}

coordinate rule::getWeight5(coordinate weightSet, int recodeList[][gomokuline], std::string user)
{
	//預測位置的[]滿足四個同顏色連在一起的成就
	int totaaLinkCount = 4;
	int linkCountME, linkCountEnemy;
	//[0-7]的權重
	for (int arrayIndex = 0; arrayIndex < sizeof(weightSet.weightLattice) / sizeof(weightSet.weightLattice[0]); arrayIndex++)
	{
		//計算是否有已有四顆同顏色棋子連線
		linkCountME=0, linkCountEnemy=0;
		for (int j = 0, linkCountMe_ = 0, linkCountEnemy_ = 0; j <= totaaLinkCount; j++)
		{
			if (recodeList[calculationPositionX(weightSet.x, arrayIndex, j)][calculationPositionY(weightSet.y, arrayIndex, j)] == getWhoArrayValue(user, "own"))
			{
				linkCountMe_++;
				linkCountME = linkCountMe_;
			}
			else if (recodeList[calculationPositionX(weightSet.x, arrayIndex, j)][calculationPositionY(weightSet.y, arrayIndex, j)] == getWhoArrayValue(user, "enemy"))
			{
				linkCountEnemy_++;
				linkCountEnemy = linkCountEnemy_;
			}
		}
		if (linkCountME == totaaLinkCount)
			weightSet.weightLattice[arrayIndex] += weightOwn5;
		if (linkCountEnemy == totaaLinkCount)
			weightSet.weightLattice[arrayIndex] += weightEnemy5;
		//printf("arrayIndex: %d   weightSet: %d \n", arrayIndex, weightSet.weightLattice[arrayIndex]);
	}
	return weightSet;
}

coordinate rule::getWeight4(coordinate weightSet, int recodeList[][gomokuline], std::string user)
{
	//活四 死四 四四
	//預測位置的[]滿足三個同顏色連在一起的成就
	int totaaLinkCount = 3;
	int linkCountME, linkCountEnemy;//紀錄有幾顆棋子
	bool IsDie = false;//是否為死四
	coordinate doubleWeight4;//用於紀錄雙四，own:1 enemy: 2 none:0

	//[0-7]的權重
	for (int arrayIndex = 0; arrayIndex < sizeof(weightSet.weightLattice) / sizeof(weightSet.weightLattice[0]); arrayIndex++)
	{
		//計算是否有已有三顆同顏色棋子連線- 死四活四
		linkCountME = 0, linkCountEnemy = 0;
		for (int j = 0, linkCountMe_ = 0, linkCountEnemy_ = 0; j <= totaaLinkCount; j++)
		{
			if (recodeList[calculationPositionX(weightSet.x, arrayIndex, j)][calculationPositionY(weightSet.y, arrayIndex, j)] == getWhoArrayValue(user, "own"))
			{
				linkCountMe_++;
				linkCountME = linkCountMe_;

				//判斷是否為死四 口ooox
				if (linkCountME == totaaLinkCount)
				{
					//printf("原始 x: %d y:%d  move x:%d y:%d j:%d \n",weightSet.x, weightSet.y, calculationPositionX(weightSet.x, arrayIndex, (j)), calculationPositionY(weightSet.y, arrayIndex, (j)),j);
					//printf("!!!!!!!!x: %d y:%d index:%d  %d == %d  \n", calculationPositionX(weightSet.x, arrayIndex, (j + 1)), calculationPositionY(weightSet.y, arrayIndex, (j + 1)), arrayIndex, recodeList[calculationPositionX(weightSet.x, arrayIndex, j + 1)][calculationPositionY(weightSet.y, arrayIndex, j + 1)], getWhoArrayValue(user, "enemy"));
					if (recodeList[calculationPositionX(weightSet.x, arrayIndex, (j + 1))][calculationPositionY(weightSet.y, arrayIndex, (j + 1))] == getWhoArrayValue(user, "enemy"))
						IsDie = true; 
					else
						IsDie = false;
				}
			}
			else if (recodeList[calculationPositionX(weightSet.x, arrayIndex, j)][calculationPositionY(weightSet.y, arrayIndex, j)] == getWhoArrayValue(user, "enemy"))
			{
				linkCountEnemy_++;
				linkCountEnemy = linkCountEnemy_;
				//判斷是否為死四
				if (linkCountEnemy == totaaLinkCount)
				{
					if (recodeList[calculationPositionX(weightSet.x, arrayIndex, j + 1)][calculationPositionY(weightSet.y, arrayIndex, j + 1)] == getWhoArrayValue(user, "own"))
						IsDie = true;
					else
						IsDie = false;
				}
			}
		}
		if (IsDie == false)
		{
			if(linkCountME!= totaaLinkCount&& linkCountEnemy!= totaaLinkCount)
				doubleWeight4.weightLattice[arrayIndex] = 0;
			else 
			{
				//活四
				if (linkCountME == totaaLinkCount)
				{
					weightSet.weightLattice[arrayIndex] += weightOwn4_live;
					doubleWeight4.weightLattice[arrayIndex] = 1;
				}
				if (linkCountEnemy == totaaLinkCount)
				{
					weightSet.weightLattice[arrayIndex] += weightEnemy4_live;
					doubleWeight4.weightLattice[arrayIndex] = 2;
				}
			}
		}
		else 
		{
			if (linkCountME != totaaLinkCount && linkCountEnemy != totaaLinkCount)
				doubleWeight4.weightLattice[arrayIndex] = 0;
			else
			{
				//死四
				if (linkCountME == totaaLinkCount)
				{
					weightSet.weightLattice[arrayIndex] += weightOwn4_died;
					doubleWeight4.weightLattice[arrayIndex] = 1;
				}
				if (linkCountEnemy == totaaLinkCount)
				{
					weightSet.weightLattice[arrayIndex] += weightEnemy4_died;
					doubleWeight4.weightLattice[arrayIndex] = 2;
				}
			}
		}
		//printf("X: %d Y: %d arrayIndex: %d   weightSet: %d \n",weightSet.x,weightSet.y, arrayIndex, weightSet.weightLattice[arrayIndex]);
	}
	//此function用於統計是否能形成雙四，因為這是全體問題所以以'0'表示他所存放的位置
	switch (calculationDoubleWeight(doubleWeight4))
	{
		case 0://無法形成雙四
			weightSet.weightLattice[0] += 0;
			break;
		case 1://能形成我方雙四
			weightSet.weightLattice[0] += weightOwn4;
			break;
		case 2://敵方形成雙四
			weightSet.weightLattice[0] += weightEnemy4;
			break;
		default:
			break;
	}
	return weightSet;
}

coordinate rule::getWeight3(coordinate weightSet, int recodeList[][gomokuline], std::string user)
{
	//活三 死三
	//預測位置的[]滿足兩個同顏色連在一起的成就
	int totaaLinkCount = 2;
	int linkCountME, linkCountEnemy;//紀錄有幾顆棋子
	bool IsDie = false;//是否為死三
	coordinate doubleWeight4;//用於紀錄雙三，own:1 enemy: 2 none:0

	//[0-7]的權重
	for (int arrayIndex = 0; arrayIndex < sizeof(weightSet.weightLattice) / sizeof(weightSet.weightLattice[0]); arrayIndex++)
	{
		//計算是否有已有兩顆同顏色棋子連線- 死三活三
		linkCountME = 0, linkCountEnemy = 0;
		for (int j = 0, linkCountMe_ = 0, linkCountEnemy_ = 0; j <= totaaLinkCount; j++)
		{
			if (recodeList[calculationPositionX(weightSet.x, arrayIndex, j)][calculationPositionY(weightSet.y, arrayIndex, j)] == getWhoArrayValue(user, "own"))
			{
				linkCountMe_++;
				linkCountME = linkCountMe_;

				//判斷是否為死三 口ooox
				if (linkCountME == totaaLinkCount)
				{
					if (recodeList[calculationPositionX(weightSet.x, arrayIndex, (j + 1))][calculationPositionY(weightSet.y, arrayIndex, (j + 1))] == getWhoArrayValue(user, "enemy"))
						IsDie = true;
					else
						IsDie = false;
				}
			}
			else if (recodeList[calculationPositionX(weightSet.x, arrayIndex, j)][calculationPositionY(weightSet.y, arrayIndex, j)] == getWhoArrayValue(user, "enemy"))
			{
				linkCountEnemy_++;
				linkCountEnemy = linkCountEnemy_;
				//判斷是否為死三
				if (linkCountEnemy == totaaLinkCount)
				{
					if (recodeList[calculationPositionX(weightSet.x, arrayIndex, j + 1)][calculationPositionY(weightSet.y, arrayIndex, j + 1)] == getWhoArrayValue(user, "own"))
						IsDie = true;
					else
						IsDie = false;
				}
			}
		}
		if (IsDie == false)
		{
			if (linkCountME != totaaLinkCount && linkCountEnemy != totaaLinkCount)
				doubleWeight4.weightLattice[arrayIndex] = 0;
			else
			{
				//活三
				if (linkCountME == totaaLinkCount)
				{
					weightSet.weightLattice[arrayIndex] += weightOwn3_live;
					//doubleWeight4.weightLattice[arrayIndex] = 1;
				}
				if (linkCountEnemy == totaaLinkCount)
				{
					weightSet.weightLattice[arrayIndex] += weightEnemy3_live;
					//doubleWeight4.weightLattice[arrayIndex] = 2;
				}
			}
		}
		else
		{
			if (linkCountME != totaaLinkCount && linkCountEnemy != totaaLinkCount)
				doubleWeight4.weightLattice[arrayIndex] = 0;
			else
			{
				//死三
				if (linkCountME == totaaLinkCount)
				{
					weightSet.weightLattice[arrayIndex] += weightOwn3_died;
					//doubleWeight4.weightLattice[arrayIndex] = 1;
				}
				if (linkCountEnemy == totaaLinkCount)
				{
					weightSet.weightLattice[arrayIndex] += weightEnemy3_died;
					//doubleWeight4.weightLattice[arrayIndex] = 2;
				}
			}
		}
		//printf("X: %d Y: %d arrayIndex: %d   weightSet: %d \n", weightSet.x, weightSet.y, arrayIndex, weightSet.weightLattice[arrayIndex]);
	}

	return weightSet;
}

coordinate rule::getWeight2(coordinate weightSet, int recodeList[][gomokuline], std::string user)
{
	//活二 死二
	//預測位置的[]滿足1個同顏色連在一起的成就
	int totaaLinkCount = 1;
	int linkCountME, linkCountEnemy;//紀錄有幾顆棋子
	//[0-7]的權重
	for (int arrayIndex = 0; arrayIndex < sizeof(weightSet.weightLattice) / sizeof(weightSet.weightLattice[0]); arrayIndex++)
	{
		//計算是否有已有兩顆同顏色棋子連線- 死二活二
		linkCountME = 0, linkCountEnemy = 0;
		for (int j = 0, linkCountMe_ = 0, linkCountEnemy_ = 0; j <= totaaLinkCount; j++)
		{
			if (recodeList[calculationPositionX(weightSet.x, arrayIndex, j)][calculationPositionY(weightSet.y, arrayIndex, j)] == getWhoArrayValue(user, "own"))
			{
				linkCountMe_++;
				linkCountME = linkCountMe_;
			}
			else if (recodeList[calculationPositionX(weightSet.x, arrayIndex, j)][calculationPositionY(weightSet.y, arrayIndex, j)] == getWhoArrayValue(user, "enemy"))
			{
				linkCountEnemy_++;
				linkCountEnemy = linkCountEnemy_;
			}
		}

		//活二
		if (linkCountME == totaaLinkCount)
			weightSet.weightLattice[arrayIndex] += weightOwn2_live;

		if (linkCountEnemy == totaaLinkCount)
			weightSet.weightLattice[arrayIndex] += weightEnemy2_live;
	}
	return weightSet;
}

int rule::getWhoArrayValue(std::string user, std::string identity)
{
	//黑子為1 白子為2
	if (user == "white")
		return	identity =="own" ? 2 : 1;
	else if (user == "black")
		return	identity == "own" ? 1 : 2;
}

int rule::calculationPositionX(int x, int arrayIndex, int currentLinkCount)
{
	switch (arrayIndex)
	{
		case 0://left-top
			if (x == 0)
				return x;
		return x - currentLinkCount;
		break;
		case 1://top
			return x;
		break;
		case 2://right-top
			if (x == gomokuline-1)
				return x;
			return x+currentLinkCount;
			break;
		case 3://left
			if (x == 0)
				return x;
			return x-currentLinkCount;
			break;
		case 4://right
			if (x == gomokuline - 1)
				return x;
			return x+currentLinkCount;
			break;
		case 5://left-down
			if (x == 0)
				return x;
			return x-currentLinkCount;
			break;
		case 6://down
			return x;
			break;
		case 7://right-down
			if (x == gomokuline - 1)
				return x;
			return x+currentLinkCount;
			break;
	}
}
int rule::calculationPositionY(int y, int arrayIndex, int currentLinkCount)
{
	switch (arrayIndex)
	{
		case 0://left-top
			if (y == 0)
				return y;
			return y-currentLinkCount;
			break;
		case 1://top
			if (y == 0)
				return y;
			return y-currentLinkCount;
			break;
		case 2://right-top
			if (y == 0)
				return y;
			return y-currentLinkCount;
			break;
		case 3://left
			return y;
			break;
		case 4://right
			return y;
			break;
		case 5://left-down
			if (y == gomokuline-1)
				return y;
			return y+currentLinkCount;
			break;
		case 6://down
			if (y == gomokuline - 1)
				return y;
			return y+currentLinkCount;
			break;
		case 7://right-down
			if (y == gomokuline - 1)
				return y;
			return y+currentLinkCount;
			break;
	}
	
}

int rule::calculationDoubleWeight(coordinate weightSet)
{
	int ownDouble = 0, enemyDouble = 0;
	for (int arrayIndex = 0; arrayIndex < sizeof(weightSet.weightLattice) / sizeof(weightSet.weightLattice[0]); arrayIndex++)
	{
		if (weightSet.weightLattice[arrayIndex] == 1)
			ownDouble += 1;
		else if (weightSet.weightLattice[arrayIndex] == 2)
			enemyDouble += 1;
	}
	if (ownDouble > 1)
		return 1;
	else if (enemyDouble > 1)
		return 2;
	else
		return 0;
}

int rule::checkDirectOnChessForSingle(point p, int index, std::string user, int recodeList[][gomokuline])
{
	int j = 1;
	int count = 0;
	while (true)
	{
		if (recodeList[calculationPositionX(p.x, index, j)][calculationPositionY(p.y, index, j)] == getWhoArrayValue(user, "own"))
		{
			//printf("jjjjjjjj:%d\n",j);
			count++;
			j++;
			return count;
		}
		else
			return count;
	}
}

coordinate_ rule::calculationChessCount(int X, int Y, int recodeList[][gomokuline], std::string user)
{
	/*init */
	coordinate_ coord;
	coord.x = X;
	coord.y = Y;
	coord.color = user;
	for (int i = 0; i < sizeof(coord.ownLattice) / sizeof(coord.ownLattice[0]); i++)
	{
		coord.ownLattice[i] = 0;
		coord.enemyLattice[i] = 0;
	}
	//calculation own count
	for (int arrayIndex = 0; arrayIndex < sizeof(coord.ownLattice) / sizeof(coord.ownLattice[0]); arrayIndex++)
	{
		//如果有敵人擋住 就乘上負號 - own
		for (int j = 1; j < 5; j++)
		{
			//printf("(%d,%d)  j:%d recodeList:%d \n", coord.x, coord.y, arrayIndex, recodeList[calculationPositionX(coord.x, arrayIndex, j)][calculationPositionY(coord.y, arrayIndex, j)]);
			if (recodeList[calculationPositionX(coord.x, arrayIndex, j)][calculationPositionY(coord.y, arrayIndex, j)] == getWhoArrayValue(user, "own"))
				coord.ownLattice[arrayIndex] += 1;
			else if (recodeList[calculationPositionX(coord.x, arrayIndex, j)][calculationPositionY(coord.y, arrayIndex, j)] == getWhoArrayValue(user, "enemy"))
			{
				coord.ownLattice[arrayIndex] *= (-1);
				break;
			}
			else
				break;
		}
	}
	
	/*for (int i = 0; i < gomokuline; i++)
	{
		for (int j = 0; j < gomokuline; j++)
			printf("%d ", recodeList[j][i]);
		printf("\n");
	}
	printf("\n\n (%d,%d)\n", coord.x, coord.y);
	printf("0: %d 7:%d\n", coord.ownLattice[0], coord.ownLattice[7]);
	printf("1: %d 6:%d\n", coord.ownLattice[1], coord.ownLattice[6]);
	printf("2: %d 5:%d\n", coord.ownLattice[2], coord.ownLattice[5]);
	printf("3: %d 4:%d\n", coord.ownLattice[3], coord.ownLattice[4]);
	*/

	//calculation enemy count
	/*for (int arrayIndex = 0; arrayIndex < sizeof(coord.enemyLattice) / sizeof(coord.enemyLattice[0]); arrayIndex++)
	{
		//如果有敵人擋住 就乘上負號 
		for (int j = 1; j < 5; j++)
		{
			if (recodeList[calculationPositionX(coord.x, arrayIndex, j)][calculationPositionY(coord.y, arrayIndex, j)] == getWhoArrayValue(user, "enemy"))
			{
				coord.enemyLattice[arrayIndex] += 1;
			}
			else if (recodeList[calculationPositionX(coord.x, arrayIndex, j)][calculationPositionY(coord.y, arrayIndex, j)] == getWhoArrayValue(user, "own"))
			{
				coord.enemyLattice[arrayIndex] *= (-1);
				break;
			}
			else
				break;
		}
	}*/
	return coord;
}

coordinate_ rule::calculationWeight(coordinate_ countSet, std::string user)
{
	coordinate_ weight;
	for (int i = 0; i < sizeof(weight.weightLattice) / sizeof(weight.weightLattice[0]); i++)
		weight.weightLattice[i] = 0;

	//weight = getLongLink(countSet, user);


	return weight;
}




int rule::getLongLink(coordinate_ countSet, std::string user, int recodeList[][gomokuline])
{
	//printf("!! (%d,%d)  ", countSet.x, countSet.y);
	//判斷是否五連 +1是預測要下的位置
	if ((abs(countSet.ownLattice[1]) + abs(countSet.ownLattice[6]) + 1) >= 5 && countSet.ownLattice[1] >= 0 && countSet.ownLattice[6] >= 0)
	{
		/*for (int i = 0; i < gomokuline; i++)
		{
			for (int j = 0; j < gomokuline; j++)
				printf("%d ", recodeList[j][i]);
			printf("\n");
		}*/
		//printf("|||||||||||||| %d %d  user:%s\n", (abs(countSet.ownLattice[1])), abs(countSet.ownLattice[6]),user.c_str());
		return longLink;
	}
		//countSet.weightLattice[0] += longLink;

	if ((abs(countSet.ownLattice[3]) + abs(countSet.ownLattice[4]) + 1) >= 5 && countSet.ownLattice[3] >= 0 && countSet.ownLattice[4] >= 0)
	{
		//printf("---------------------\n");
		return longLink;
	}
		//countSet.weightLattice[1] += longLink;

	if ((abs(countSet.ownLattice[0]) + abs(countSet.ownLattice[7]) + 1) >= 5 && countSet.ownLattice[0] >= 0 && countSet.ownLattice[7] >= 0)
	{
		//printf("\\\\\\\\\\\\\\\\\\\\\n");
		return longLink;
	}
		//countSet.weightLattice[2] += longLink;

	if ((abs(countSet.ownLattice[2]) + abs(countSet.ownLattice[5]) + 1) >= 5 && countSet.ownLattice[2] >= 0 && countSet.ownLattice[5] >= 0)
	{
		//printf("/////////////////// \n");
		return longLink;
	}
		//countSet.weightLattice[3] += longLink;
	return 0;
	//return countSet;
}

int rule::getLive4(coordinate_ countSet, std::string user)
{
	if (abs(countSet.ownLattice[1]) + abs(countSet.ownLattice[6]) + 1 == 4 && countSet.ownLattice[1] >= 0 && countSet.ownLattice[6] >= 0)
	{
		//printf("live4 (%d,%d)", countSet.x, countSet.y);
		return live4;
	}	
		//countSet.weightLattice[0] += live4;

	if (abs(countSet.ownLattice[3]) + abs(countSet.ownLattice[4]) + 1 == 4 && countSet.ownLattice[3] >= 0 && countSet.ownLattice[4] >= 0)
		return live4;
		//countSet.weightLattice[1] += live4;

	if (abs(countSet.ownLattice[0]) + abs(countSet.ownLattice[7]) + 1 == 4 && countSet.ownLattice[0] >= 0 && countSet.ownLattice[7] >= 0)
		return live4;
		//countSet.weightLattice[2] += live4;

	if (abs(countSet.ownLattice[2]) + abs(countSet.ownLattice[5]) + 1 == 4 && countSet.ownLattice[2] >= 0 && countSet.ownLattice[5] >= 0)
		return live4;
		//countSet.weightLattice[3] += live4;
	return 0;
	//return countSet;
}

int rule::getLive3(coordinate_ countSet, std::string user)
{
	if (abs(countSet.ownLattice[1]) + abs(countSet.ownLattice[6]) + 1 == 3 && countSet.ownLattice[1] >= 0 && countSet.ownLattice[6] >= 0)
		return live3;
		//	countSet.weightLattice[0] += live3;

	if (abs(countSet.ownLattice[3]) + abs(countSet.ownLattice[4]) + 1 == 3 && countSet.ownLattice[3] >= 0 && countSet.ownLattice[4] >= 0)
		return live3;
		//	countSet.weightLattice[1] += live3;

	if (abs(countSet.ownLattice[0]) + abs(countSet.ownLattice[7]) + 1 == 3 && countSet.ownLattice[0] >= 0 && countSet.ownLattice[7] >= 0)
	{
		//printf("live3 (%d,%d)", countSet.x,countSet.y);
		return live3;
	}
		//	countSet.weightLattice[2] += live3;

	if (abs(countSet.ownLattice[2]) + abs(countSet.ownLattice[5]) + 1 == 3 && countSet.ownLattice[2] >= 0 && countSet.ownLattice[5] >= 0)
		return live3;
		//	countSet.weightLattice[3] += live3;
	return 0;
	//return countSet;
}

int rule::getLive2(coordinate_ countSet, std::string user)
{
	if (abs(countSet.ownLattice[1]) + abs(countSet.ownLattice[6]) + 1 == 2 && countSet.ownLattice[1] >= 0 && countSet.ownLattice[6] >= 0)
		return live2;
		//countSet.weightLattice[0] += live2;

	if (abs(countSet.ownLattice[3]) + abs(countSet.ownLattice[4]) + 1 == 2 && countSet.ownLattice[3] >= 0 && countSet.ownLattice[4] >= 0)
		return live2;
	//countSet.weightLattice[1] += live2;

	if (abs(countSet.ownLattice[0]) + abs(countSet.ownLattice[7]) + 1 == 2 && countSet.ownLattice[0] >= 0 && countSet.ownLattice[7] >= 0)
		return live2;
	//countSet.weightLattice[2] += live2;

	if (abs(countSet.ownLattice[2]) + abs(countSet.ownLattice[5]) + 1 == 2 && countSet.ownLattice[2] >= 0 && countSet.ownLattice[5] >= 0)
		return live2;
	//countSet.weightLattice[3] += live2;

	return 0;
	//return countSet;
}

int rule::getRush4(coordinate_ countSet, std::string user)
{
	if (abs(countSet.ownLattice[1]) + abs(countSet.ownLattice[6]) + 1 == 4 && (countSet.ownLattice[1] >= 0 || countSet.ownLattice[6] >= 0))
		return rush4;
		//	countSet.weightLattice[0] += live4;

	if (abs(countSet.ownLattice[3]) + abs(countSet.ownLattice[4]) + 1 == 4 && (countSet.ownLattice[3] >= 0 || countSet.ownLattice[4] >= 0))
		return rush4;
		//	countSet.weightLattice[1] += live4;

	if (abs(countSet.ownLattice[0]) + abs(countSet.ownLattice[7]) + 1 == 4 && (countSet.ownLattice[0] >= 0 || countSet.ownLattice[7] >= 0))
		return rush4;
		//	countSet.weightLattice[2] += live4;

	if (abs(countSet.ownLattice[2]) + abs(countSet.ownLattice[5]) + 1 == 4 && (countSet.ownLattice[2] >= 0 || countSet.ownLattice[5] >= 0))
		return rush4;
		//	countSet.weightLattice[3] += live4;
	return 0;
	//return countSet;
}

int rule::getRush3(coordinate_ countSet, std::string user)
{
	if (abs(countSet.ownLattice[1]) + abs(countSet.ownLattice[6]) + 1 == 3 && (countSet.ownLattice[1] >= 0 || countSet.ownLattice[6] >= 0))
		return rush3;
		//countSet.weightLattice[0] += live3;

	if (abs(countSet.ownLattice[3]) + abs(countSet.ownLattice[4]) + 1 == 3 && (countSet.ownLattice[3] >= 0 || countSet.ownLattice[4] >= 0))
		return rush3;
		//countSet.weightLattice[1] += live3;

	if (abs(countSet.ownLattice[0]) + abs(countSet.ownLattice[7]) + 1 == 3 && (countSet.ownLattice[0] >= 0 || countSet.ownLattice[7] >= 0))
		return rush3;
		//countSet.weightLattice[2] += live3;

	if (abs(countSet.ownLattice[2]) + abs(countSet.ownLattice[5]) + 1 == 3 && (countSet.ownLattice[2] >= 0 || countSet.ownLattice[5] >= 0))
		return rush3;
		//countSet.weightLattice[3] += live3;
	return 0;
	//return countSet;
}

int rule::getRush2(coordinate_ countSet, std::string user)
{
	if (abs(countSet.ownLattice[1]) + abs(countSet.ownLattice[6]) + 1 == 2 && (countSet.ownLattice[1] >= 0 || countSet.ownLattice[6] >= 0) )
		return rush2;
		//countSet.weightLattice[0] += live2;

	if (abs(countSet.ownLattice[3]) + abs(countSet.ownLattice[4]) + 1 == 2 && (countSet.ownLattice[3] >= 0 || countSet.ownLattice[4] >= 0))
		return rush2;
		//countSet.weightLattice[1] += live2;

	if (abs(countSet.ownLattice[0]) + abs(countSet.ownLattice[7]) + 1 == 2 && (countSet.ownLattice[0] >= 0 || countSet.ownLattice[7] >= 0))
		return rush2;
		//countSet.weightLattice[2] += live2;

	if (abs(countSet.ownLattice[2]) + abs(countSet.ownLattice[5]) + 1 == 2 && (countSet.ownLattice[2] >= 0 || countSet.ownLattice[5] >= 0))
		return rush2;
		//countSet.weightLattice[3] += live2;

		
	return 0;
	//return countSet;
}

int rule::getDie4(coordinate_ countSet, std::string user)
{
	if (abs(countSet.ownLattice[1]) + abs(countSet.ownLattice[6]) + 1 == 4 && (countSet.ownLattice[1] < 0 && countSet.ownLattice[6] < 0))
		return die4;
	//	countSet.weightLattice[0] += live4;

	if (abs(countSet.ownLattice[3]) + abs(countSet.ownLattice[4]) + 1 == 4 && (countSet.ownLattice[3] < 0 && countSet.ownLattice[4] < 0))
		return die4;
	//	countSet.weightLattice[1] += live4;

	if (abs(countSet.ownLattice[0]) + abs(countSet.ownLattice[7]) + 1 == 4 && (countSet.ownLattice[0] < 0 && countSet.ownLattice[7] < 0))
		return die4;
	//	countSet.weightLattice[2] += live4;

	if (abs(countSet.ownLattice[2]) + abs(countSet.ownLattice[5]) + 1 == 4 && (countSet.ownLattice[2] < 0 && countSet.ownLattice[5] < 0))
		return die4;
	//	countSet.weightLattice[3] += live4;
	return 0;

}

int rule::getDie3(coordinate_ countSet, std::string user)
{
	if (abs(countSet.ownLattice[1]) + abs(countSet.ownLattice[6]) + 1 == 3 && (countSet.ownLattice[1] < 0 && countSet.ownLattice[6] < 0))
		return die3;
	//	countSet.weightLattice[0] += live4;

	if (abs(countSet.ownLattice[3]) + abs(countSet.ownLattice[4]) + 1 == 3 && (countSet.ownLattice[3] < 0 && countSet.ownLattice[4] < 0))
		return die3;
	//	countSet.weightLattice[1] += live4;

	if (abs(countSet.ownLattice[0]) + abs(countSet.ownLattice[7]) + 1 == 3 && (countSet.ownLattice[0] < 0 && countSet.ownLattice[7] < 0))
		return die3;
	//	countSet.weightLattice[2] += live4;

	if (abs(countSet.ownLattice[2]) + abs(countSet.ownLattice[5]) + 1 == 3 && (countSet.ownLattice[2] < 0 && countSet.ownLattice[5] < 0))
		return die3;
	//	countSet.weightLattice[3] += live4;
	return 0;
}

int rule::getDie2(coordinate_ countSet, std::string user)
{
	
	if (abs(countSet.ownLattice[1]) + abs(countSet.ownLattice[6]) + 1 == 2 && (countSet.ownLattice[1] < 0 && countSet.ownLattice[6] < 0))
		return die2;
	//	countSet.weightLattice[0] += live4;

	if (abs(countSet.ownLattice[3]) + abs(countSet.ownLattice[4]) + 1 == 2 && (countSet.ownLattice[3] < 0 && countSet.ownLattice[4] < 0))
		return die2;
	//	countSet.weightLattice[1] += live4;

	if (abs(countSet.ownLattice[0]) + abs(countSet.ownLattice[7]) + 1 == 2 && (countSet.ownLattice[0] < 0 && countSet.ownLattice[7] < 0))
		return die2;
	//	countSet.weightLattice[2] += live4;

	if (abs(countSet.ownLattice[2]) + abs(countSet.ownLattice[5]) + 1 == 2 && (countSet.ownLattice[2] < 0 && countSet.ownLattice[5] < 0))
		return die2;
	//	countSet.weightLattice[3] += live4;
	return 0;
}

int rule::computing2_1(point p, std::string user, int recodeList[][gomokuline])
{
	std::vector<int> container;
	if (checkDirectOnChessForSingle(p, 0, user, recodeList)+1 == 2)
		container.push_back(5);
	if (checkDirectOnChessForSingle(p, 1, user, recodeList)+1 == 2)
		container.push_back(5);
	if (checkDirectOnChessForSingle(p, 2, user, recodeList)+1 == 2)
		container.push_back(5);
	if (checkDirectOnChessForSingle(p, 3, user, recodeList)+1 == 2)
		container.push_back(5);
	if (checkDirectOnChessForSingle(p, 4, user, recodeList)+1 == 2)
		container.push_back(5);
	if (checkDirectOnChessForSingle(p, 5, user, recodeList)+1 == 2)
		container.push_back(5);
	if (checkDirectOnChessForSingle(p, 6, user, recodeList)+1 == 2)
		container.push_back(5);
	if (checkDirectOnChessForSingle(p, 7, user, recodeList)+1 == 2)
		container.push_back(5);
	//printf("finish 1\n");

	if (checkDirectOnChessForSingle(p, 0, user, recodeList) + 1 == 1)
		container.push_back(1);
	if (checkDirectOnChessForSingle(p, 1, user, recodeList) + 1 == 1)
		container.push_back(1);
	if (checkDirectOnChessForSingle(p, 2, user, recodeList) + 1 == 1)
		container.push_back(1);
	if (checkDirectOnChessForSingle(p, 3, user, recodeList) + 1 == 1)
		container.push_back(1);
	if (checkDirectOnChessForSingle(p, 4, user, recodeList) + 1 == 1)
		container.push_back(1);
	if (checkDirectOnChessForSingle(p, 5, user, recodeList) + 1 == 1)
		container.push_back(1);
	if (checkDirectOnChessForSingle(p, 6, user, recodeList) + 1 == 1)
		container.push_back(1);
	if (checkDirectOnChessForSingle(p, 7, user, recodeList) + 1 == 1)
		container.push_back(1);
	//printf("finish 2\n");
	if (checkDirectOnChessForSingle(p, 0, user, recodeList) + checkDirectOnChessForSingle(p, 7, user, recodeList) + 1 == 2)
		container.push_back(7);
	if (checkDirectOnChessForSingle(p, 1, user, recodeList) + checkDirectOnChessForSingle(p, 6, user, recodeList) + 1 == 2)
		container.push_back(7);
	if (checkDirectOnChessForSingle(p, 2, user, recodeList) + checkDirectOnChessForSingle(p, 5, user, recodeList) + 1 == 2)
		container.push_back(7);
	if (checkDirectOnChessForSingle(p, 3, user, recodeList) + checkDirectOnChessForSingle(p, 4, user, recodeList) + 1 == 2)
		container.push_back(7);
	//printf("finish 3\n");
	if (checkDirectOnChessForSingle(p, 0, user, recodeList) + checkDirectOnChessForSingle(p, 7, user, recodeList) + 1 == 1)
		container.push_back(3);
	if (checkDirectOnChessForSingle(p, 1, user, recodeList) + checkDirectOnChessForSingle(p, 6, user, recodeList) + 1 == 1)
		container.push_back(3);
	if (checkDirectOnChessForSingle(p, 2, user, recodeList) + checkDirectOnChessForSingle(p, 5, user, recodeList) + 1 == 1)
		container.push_back(3);
	if (checkDirectOnChessForSingle(p, 3, user, recodeList) + checkDirectOnChessForSingle(p, 4, user, recodeList) + 1 == 1)
		container.push_back(3);
	//printf("finish push\n");
	std::sort(container.begin(), container.end());
	//printf("finish sort\n");

	//返回最大的兩個和
	return container[container.size() - 2] + container[container.size() - 1];
}

bool rule::checkChess(point p, int recodeList[][gomokuline])
{

	int j = 1;
	for (int index = 0; index < 8; index++)
	{
		if (recodeList[calculationPositionX(p.x, index, j)][calculationPositionY(p.y, index, j)] != 0)
			return true;
	}
	return false;
	
}

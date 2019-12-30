#include"stdafx.h"
#include "geneticA.h"

board::board()
{
}

board::board(int recodeList[][gomokuline])
{
	//vector 沒做初始化 可能會有問題
	point_ p;
	for (int i = 0; i < gomokuline; i++)
	{
		for (int j = 0; j < gomokuline; j++)
			this->recodeListBoard[i][j] = recodeList[i][j];
	}

	this->n_in_line = 5;
	for (int i = 0; i < gomokuline; i++)
	{
		for (int j = 0; j < gomokuline; j++)
		{
			if (recodeList[i][j] == 0)
			{
				p.x = i;
				p.y = j;
				availables.push_back(p);
			}
			else
			{
				p.x = i;
				p.y = j;
				unavailables.push_back(p);
			}
		}
	}
}

std::vector<point_> board::get_avil(int recodeList[][gomokuline])
{
	

	std::vector<int> unfreeX;
	std::vector<int> unfreeY;
	for (int i = 0; i < unavailables.size(); i++)
	{
		unfreeX.push_back(this->unavailables[i].x);
		unfreeY.push_back(this->unavailables[i].y);
	}
	int upX, downX, leftY, rightY;
	std::sort(unfreeX.begin(), unfreeX.end());
	std::sort(unfreeY.begin(), unfreeY.end());

	//x最小最大值 y最小最大值 > 確認邊界
	upX = unfreeX[0];
	downX = unfreeX[unfreeX.size() - 1]+1;
	leftY = unfreeY[0];
	rightY = unfreeY[unfreeY.size() - 1]+1;

	//確認邊界
	if (upX != 0)
		upX -= 1;
	if (downX != gomokuline-1)
		downX += 1;
	if (leftY != 0)
		leftY -= 1;
	if (rightY != gomokuline - 1)
		rightY += 1;

	point_ p;
	std::vector<point_> avail_pos;
	for (int i = upX; i < downX; i++)
	{
		for (int j = leftY; j < rightY; j++)
		{
			if (recodeList[i][j] == 0)
			{
				//printf("(%d,%d)\n", i, j);
				p.x = i;
				p.y = j;
				avail_pos.push_back(p);
			}
		}
	}

	return avail_pos;
}

point_ board::update(std::string user, point_ move)
{
	//更新棋盤
	for (int i = 0; i < availables.size(); i++)
	{

		if (move.x == availables[i].x && move.y == availables[i].y)
		{
			//printf("upde delete (%d,%d)\n", move.x, move.y);
			availables.erase(availables.begin() + i);
		}
	}
	unavailables.push_back(move);
	return point_();
}

std::vector<point_> board::mutata(std::vector<point_> origin_individual, std::vector<point_> DNA_base)
{
	std::vector<point_> ind = origin_individual;
	int pos = rand() % (ind.size());
	point_ gene = ind[pos];
	//printf("!!!!%d  ", pos);
	while (gene.x == ind[pos].x&&gene.y == ind[pos].y)
	{
		gene = DNA_base[rand() % (DNA_base.size())];
	}
	ind[pos] = gene;
	return ind;
}

void board::crrorover(std::vector<point_> individual1, std::vector<point_> individual2)
{
	std::vector<point_> individual1_ = individual1;
	std::vector<point_> individual2_ = individual2;

	if (individual1_.size() != individual2_.size())
	{
		printf("crrorover 倆個基因串長度不一樣\n");
		return;
	}
	int pos = rand() % (individual1_.size());
	//printf("pos:%d\n ", pos);
	std::vector<point_> temp;
	//[pos:]
	for (int i = pos; i < individual1_.size(); i++)
		temp.push_back(individual1_[i]);
	
	//printf("temp size : %d  *********************\n ", temp.size());
	individual1_.erase(individual1_.begin()+pos, individual1_.end());
	//printf("individual1_ size : %d  *********************\n ", individual1_.size());

	//for (int i = pos; i < individual2_.size(); i++)
		//individual1_.push_back(individual2_[i]);
	
	for (int i = pos; i < individual2_.size(); i++)
	{
		//判斷在individual1_ 有沒有重複的點
		int is = false;
		for (int j = 0; j < individual2_.size(); j++)
		{
			if (individual2_[i].x == individual1[j].x &&individual2_[i].y == individual1[j].y)
				is = true; break;
		}
		//有重複的點
		if (is)
			individual1_.push_back(individual1[i]);
		else
			individual1_.push_back(individual2_[i]);
		
	}
	individual2_.erase(individual2_.begin() + pos, individual2_.end());
	//printf("individual2_ size : %d  *********************\n ", individual2_.size());
	//for (int i = pos; i < individual1_.size(); i++)
	//	individual2_.push_back(temp[i-pos]);
	
	for (int i = pos; i < individual1_.size(); i++)
	{
		//判斷在individual1_ 有沒有重複的點
		int is = false;
		for (int j = 0; j < individual1_.size(); j++)
		{
			if (temp[i - pos].x == individual2[i].x &&temp[i - pos].y == individual2[i].y)
				is = true; break;
		}
		//有重複的點
		if (is)
			individual2_.push_back(individual2[i]);
		else
			individual2_.push_back(temp[i - pos]);

	}

	//printf("1:%d 2:%d\n", individual1_.size(), individual2_.size());

	this->individual1 = individual1_;
	this->individual2 = individual2_;

}

population::population()
{
}

population::population(std::vector<point_> potentialGene)
{
	this->DNA_base = potentialGene;
	this->DNA_length = 7;
	this->mutate_rate_limit = 0.01;
	this->start_number = 2000;
	this->number_limit = 3500;
	this->survival_rate = 0.1;

	//currentGeneration = beginGeneration();

}

population::population(std::vector<point_> potential_position, int DNA_length, double mutate_rate_limit, int start_number, int number_limit, double sruvival_rate, int recodeList[][gomokuline], double time_limit)
{
	this->DNA_base = potential_position;
	this->DNA_length = DNA_length;
	this->mutate_rate_limit = mutate_rate_limit;
	this->start_number = start_number;
	this->number_limit = number_limit;
	this->survival_rate = sruvival_rate;
	this->time_limit = time_limit;
	for (int i = 0; i < gomokuline; i++)
	{
		for (int j = 0; j < gomokuline; j++)
			this->recodeListPopulation[i][j] = recodeList[i][j];
	}
	currentGeneration = beginGeneration();
}

void population::select(std::string user, int gen)
{
	std::fstream  file;
	if (gen == 1)
		file.open("sult1.txt", std::ios::out);
	if (gen == 2)
		file.open("sult2.txt", std::ios::out);
	if (gen == 3)
		file.open("sult3.txt", std::ios::out);
	if (gen == 4)
		file.open("sult4.txt", std::ios::out);
	if (gen == 5)
		file.open("sult5.txt", std::ios::out);
	if (gen == 6)
		file.open("sult6.txt", std::ios::out);
	if (gen == 7)
		file.open("sult7.txt", std::ios::out);
	if (gen == 8)
		file.open("sult8.txt", std::ios::out);
	if (gen == 9)
		file.open("sult9.txt", std::ios::out);
	if (gen == 10)
		file.open("sult10.txt", std::ios::out);
	//選擇
	individualfitSetAndAllIndividualfit fit;
	std::vector<individualfitSetAndAllIndividualfit> point_fit;

	//pp p;
	//double fit;
	std::vector<int> grade;
	for (int i = 0 ;i< currentGeneration.size(); i++) 
	{
		fit = eval_individual(currentGeneration[i], recodeListPopulation, user,gen);
		file << gen << " " << fit.fit << std::endl;

		//p.fit = fit.fit;
		//p.Generation = currentGeneration[i];
		fit.Generation = currentGeneration[i];
		point_fit.push_back(fit);
	}
	//排序 降序
	std::sort(point_fit.begin(), point_fit.end(),GAcompare);
	//for (int i = 0; i < point_fit.size(); i++)
	//	printf("%lf  ", point_fit[i].fit);
	//printf("\nfited!!!\n");

	//排序 依據個人適應度高到低
	for(int i=0;i< point_fit.size();i++)
		std::sort(point_fit[i].individualfit.begin(), point_fit[i].individualfit.end(), GAcompare3);

	std::vector <std::vector<point_>> newGene;
	for (int i = 0; i < currentGeneration.size()*survival_rate; i++)
	{
		//printf("size:%d\n", point_fit[i].Generation);
		newGene.push_back(point_fit[i].Generation);
	}
	
	currentGeneration.clear();
	currentGeneration = newGene;
	currentIndividualfitSetAndAllIndividualfit = point_fit;
	//for (int i = 0; i < currentGeneration.size(); i++)
	//	printf("size:%d\n", currentGeneration[i].size());
	file.close();
}

int population::fitness(point_ p, int recodeList[][gomokuline], std::string user, int gen)
{
	int score = 0;
	rule * rule_ = new rule();
	coordinate_ cal = rule_->calculationChessCount(p.x,p.y,recodeList,user);

	//printf("(%d,%d) 1:%d -:%d  \:%d /:%d \n", cal.x, cal.y, cal.ownLattice[1], cal.ownLattice[6], cal.ownLattice[3], cal.ownLattice[4]);
	//長連
	score = std::max(score, rule_->getLongLink(cal, user, recodeList));

	//score +=  rule_->getLongLink(cal, user);
	//活四
	score = std::max(score, rule_->getLive4(cal, user));
	//score += rule_->getLive4(cal, user);

	//衝四
	score = std::max(score, rule_->getRush4(cal, user));
	//score += rule_->getRush4(cal, user);

	//死四
	score = std::max(score, rule_->getDie4(cal, user));
	//score += rule_->getDie4(cal, user);

	//活三
	score = std::max(score, rule_->getLive3(cal, user));
	//score += rule_->getLive3(cal, user);

	//衝三
	score = std::max(score, rule_->getRush3(cal, user));
	//score += rule_->getRush3(cal, user);
	//死三
	score = std::max(score, rule_->getDie3(cal, user));
	//score += rule_->getDie3(cal, user);
	//活二
	score = std::max(score, rule_->getLive2(cal, user));
	//score += rule_->getLive2(cal, user);
	//衝二
	score = std::max(score, rule_->getRush2(cal, user));
	//score += rule_->getRush2(cal, user);
	//死二
	score = std::max(score, rule_->getDie2(cal, user));
	//score += rule_->getDie2(cal, user);
	if (score > scoreMax)
		return scoreMax;
	return score;
}

int population::evalMove(point_ p, int recodeList[][gomokuline], std::string user, int gen)
{

	if (recodeList[p.x][p.y] != 0)
	{
		//printf("return-1   \n");
		return -1;
	}
	//crossoverTemp1 define in class "population"  
	
	crossoverTemp1 = fitness(p, recodeList, user,gen);
	if (user == "white")
		user = "black";
	else
		user = "white";
	int temp2=0;
	temp2= fitness(p, recodeList, user,gen);


	return crossoverTemp1 +temp2;
}

individualfitSetAndAllIndividualfit population::eval_individual(std::vector<point_> set, int recodeList[][gomokuline], std::string user, int gen)
{
	individualfitSetAndAllIndividualfit fit;
	std::fstream  file;
	if (gen == 1)
		file.open("esult1.txt", std::ios::out);
	if (gen == 2)
		file.open("esult2.txt", std::ios::out);
	if (gen == 3)
		file.open("esult3.txt", std::ios::out);
	if (gen == 4)
		file.open("esult4.txt", std::ios::out);
	if (gen == 5)
		file.open("esult5.txt", std::ios::out);
	if (gen == 6)
		file.open("esult6.txt", std::ios::out);
	if (gen == 7)
		file.open("esult7.txt", std::ios::out);
	if (gen == 8)
		file.open("esult8.txt", std::ios::out);
	if (gen == 9)
		file.open("esult9.txt", std::ios::out);
	if (gen == 10)
		file.open("esult10.txt", std::ios::out);
	int copylist[gomokuline][gomokuline];
	for (int i = 0; i < gomokuline; i++)
	{
		for (int j = 0; j < gomokuline; j++)
			copylist[i][j] = recodeList[i][j];
	}
	int value = 0;
	int sign = 1;
	bool me_win = false;
	bool enemy_win = false;
	int player=(user=="white" ? 2:1);
	std::string me = user;
	//for(int i=0;i<set.size();i++)
	//	printf("(%d,%d):%d \n", set[i].x, set[i].y, recodeList[set[i].x][set[i].y]);
	for (int i = 0; i < set.size(); i++)
	{
		if (me_win)
			value += 2 * scoreMax;
		else if (enemy_win)
			value -= 2 * scoreMax;
		else
		{
			//printf("!! (%d,%d)  ", set[i].x, set[i].y);
			int evaluation = evalMove(set[i], copylist, user,gen);
			//printf(" \n user : %s evaluation :%d\n",user.c_str(), evaluation);
			file << gen << " " << evaluation << std::endl;
			if (crossoverTemp1 == scoreMax || crossoverTemp1 == scoreSecond)
			{
				if (user == me)
				{
					//me_win = true;
					//printf("我贏了 %d", crossoverTemp1);
				}
				else
				{
					//enemy_win = true;
					//printf("我書了,%d", crossoverTemp1);
				}
			}
			p3 p;
			p.p = set[i];
			p.fit = evaluation;

			fit.individualfit.push_back(p);
			value += sign * evaluation;
			//printf("val :%d \n", value);
			//if (recodeList[set[i].x][set[i].y] == 0)
			//{
				//for (int i = 0; i < gomokuline; i++)
				//{
				//	for (int j = 0; j < gomokuline; j++)
				//		printf("%d ", copylist[j][i]);
				//	printf("\n");
				//}
				copylist[set[i].x][set[i].y] = player;
	

				if (user == "white")
					player = 2;
				else
					player = 1;
				//recodeListPopulation[set[i].x][set[i].y] = player;
							//交換
				if (user == "white")
					user = "black";
				else
					user = "white";


				sign = -sign;
			//}

		}
	}
	//printf(" set size: %d \n\n",set.size());
	//printf("value : %d \n", value);
	fit.fit = value;
	Gadd = value;
	file.close();
	return fit;
}

std::vector <std::vector<point_>> population::beginGeneration()
{
	//if (DNA_base.size() > DNA_length)
	//	printf("這個基因串不足夠 %d", DNA_length);
	
	std::vector <std::vector<point_>> generation;
	for (int i = 0; i < this->start_number; i++)
	{
		//隨機選取七個點 當作基因串
		std::vector<point_> DNA;
		for (int j = 0; j < DNA_length; )
		{
			bool is = false;
			point_ p = DNA_base[rand() % DNA_base.size()];
			if (DNA.size() != NULL)
			{
				//檢查是否有重複
				for (int been = 0; been < DNA.size(); been++)
				{
					if (DNA[been].x == p.x &&DNA[been].y == p.y)
						is = true;
				}
				if (!is)
				{
					DNA.push_back(p);
					j++;
				}
			}
			else 
			{
				DNA.push_back(p);
				j++;
			}
		}
		//for (int i = 0; i < DNA.size(); i++)
		//	printf("(%d,%d)  ", DNA[i].x, DNA[i].y);
		//printf("\n");
		generation.push_back(DNA);
	}

	return generation;
}

bool population::find_best_firsts()
{
	// 當前最好的一步
	bool stop=false;
	bool is = false;
	std::vector<pp> p;
	pp p_;
	std::vector<p3> ppp;//fit = count
	p3 p3_;
	for (int i = 0; i < currentGeneration.size(); i++)
	{
		is = false;
		if (ppp.size() == NULL)
		{
			for (int j = 0; j < ppp.size(); j++)
			{
				if (currentGeneration[i][0].x == ppp[j].p.x && currentGeneration[i][0].y == ppp[j].p.y)
				{
					ppp[i].fit += 1;
					is = true;
				}
			}
			if (!is)
			{
				p3_.fit = 1;
				//p3_.p = currentGeneration[i][0];
				p3_.p = currentIndividualfitSetAndAllIndividualfit[i].individualfit[0].p;
				ppp.push_back(p3_);
			}
		}
		else
		{
			p3_.fit = 1;
			//p3_.p = currentGeneration[i][0];
			p3_.p = currentIndividualfitSetAndAllIndividualfit[i].individualfit[0].p;
			ppp.push_back(p3_);
		}
	}
	//排序
	std::sort(ppp.begin(), ppp.end(), GAcompare3);
	//for (int i = 0; i < ppp.size(); i++)
	//	printf("%d  ", ppp[i].fit);
	//printf("\n");

	point_ best_first;
	best_first = ppp[0].p;

	//如果收斂了就提前結束
	stop = (ppp[0].fit == currentGeneration.size());
	//printf("stop : %d\n", stop);

	if (best_5.size() >= 5)
		best_5.erase(best_5.begin());
	best_5.push_back(best_first);
	//printf("best_5 size = %d\n", best_5.size());


	// 當前最好的一步
	/*
	for (int i = 0; i < currentGeneration.size(); i++)
	{
		if (p.size() == NULL)
		{
			for (int j = 0; j < p.size(); j++)
			{
				if (currentGeneration[i]== p[j].Generation)
				{
					p[i].fit += 1;
					continue;
				}
				p_.fit = 1;
				p_.Generation = currentGeneration[i];
				p.push_back(p_);
			}
		}
		else
		{
			p_.fit = 1;
			p_.Generation = currentGeneration[i];
			p.push_back(p_);
		}
	}
	//排序
	std::sort(p.begin(), p.end(), GAcompare);
	for (int i = 0; i < p.size(); i++)
		printf("%d  ", p[i].fit);
	printf("p1:end\n");

	std::vector<point_> best_first_;
	best_first_ = p[0].Generation;
	if (best_5_2.size() >= 5)
		best_5_2.erase(best_5_2.begin());
	best_5_2.push_back(best_first_);*/


	return stop;
}

void population::generate_next()
{
	double Probability = (double)rand() / (RAND_MAX + 1.0);
	int mutate_number = rand() % (int)(mutate_rate_limit*number_limit);
	int crossover_number = this->number_limit - currentGeneration.size() - mutate_number;
	//printf("generate_next  mutate_number=%d  crossover_number=%d\n", mutate_number, crossover_number);
	board* board_ = new board();
	//for (int i = 0; i < currentGeneration.size(); i++)
	//		printf("generate_next*******size: %d ************************\n", currentGeneration[i].size());
	//crossover
	if (Probability > mutate_rate_limit) 
	{
		for (int i = 0; i < crossover_number; i += 2)
		{
			std::vector<point_> individual1 = currentGeneration[rand() % (currentGeneration.size())];
			std::vector<point_> individual2 = currentGeneration[rand() % (currentGeneration.size())];
			board_->crrorover(individual1, individual2);
			currentGeneration.push_back(board_->individual1);
			currentGeneration.push_back(board_->individual2);
		}
	/*	for (int i = 0; i < currentGeneration.size(); i++)
		{
			for (int j = 0; j < currentGeneration[i].size(); j++)
				printf("corrover**( %d ,%d )** ", currentGeneration[i][j]);
			printf("\n");
		}*/
	}
	else 
	{
		//mutate
		for (int i = 0; i < mutate_number; i ++)
		{
			std::vector<point_> p = currentGeneration[rand() % (currentGeneration.size())];
			//printf("p*******size: %d ************************\n", DNA_base.size());
			std::vector<point_> newDNA = board_->mutata(p,DNA_base);
			//printf("mutate*******size: %d ************************\n", newDNA.size());
			currentGeneration.push_back(newDNA);
		}
		//for (int i = 0; i < currentGeneration.size(); i++)
		//	printf("mutate*******size: %d ************************\n", currentGeneration[i].size());
	}
}

bool population::GAcompare(individualfitSetAndAllIndividualfit a, individualfitSetAndAllIndividualfit b)
{
	return (a.fit > b.fit);
}
bool population::GAsort2(int a, int b)
{
	return (a > b);
}
bool population::GAcompare3(p3 a, p3 b)
{
	return (a.fit > b.fit);
}

geneticA::geneticA(int recodeList[][gomokuline], std::string user,int n_in_line, int DNA_length, double mutate_rate_limit, int start_number, int number_limit, double sruvival_rate, double time_limit)
{

	this->n_in_line = n_in_line;
	this->DNA_length = DNA_length;
	this->mutate_rate_limit = mutate_rate_limit;
	this->start_number = start_number;
	this->number_limit = number_limit;
	this->sruvival_rate = sruvival_rate;
	this->time_limit = time_limit;
	current_board = new board(recodeList);
	player_turn = user;

	potential_position = current_board->get_avil(recodeList);
	population_ = new population(potential_position, DNA_length, mutate_rate_limit, start_number, number_limit, sruvival_rate, recodeList, time_limit);

}

geneticA::geneticA()
{
}


double geneticA::select_function()
{
	return 0.0;
}

bool geneticA::check_function(std::vector<point_> individual1)
{
	std::vector<point_> rememberList;
	bool is=false;
	for (int i = 0; i < individual1.size(); i++)
	{
		if (rememberList.size() != NULL)
		{
			//檢查是否有重複
			for (int been = 0; been < rememberList.size(); been++)
			{
				if (rememberList[been].x == individual1[i].x &&rememberList[been].y == individual1[i].y)
				{
					is = true;
					break;
				}
			}
			if (!is)
				rememberList.push_back(individual1[i]);
			else
				break;
		}
		else
		{
			rememberList.push_back(individual1[i]);
		}

	}
	//is>>> T:重複  F:沒重複
	return !is;
}

point_ geneticA::get_action(std::string user)
{
	int gen = 0;
	clock_t start, end;
	double cpu_time_used;
	start = clock();
	end = clock();
	std::fstream  file;
	file.open("result1.txt", std::ios::out);
	//for(int i=0;i<population_->currentGeneration.size();i++)
	//	printf("size: %d\n", population_->currentGeneration[i].size());
	for (int i = 0; ((double)(end - start)) / CLOCKS_PER_SEC <= time_limit ; i++)
	{
		printf("gen:%d\n", ++gen);
		population_->Gadd = 0;
		population_->select(user, gen);
		//printf("gene  %d\n", gen);
		if (population_->find_best_firsts())
		{
			file << gen << " " << population_->Gadd << std::endl;
			file.close();
			printf("return 1!!!!!!!!!!!\n");
			end = clock();
			return population_->best_5[4];//當前最新加入的
		}
		
		//檢查是否收斂
		int count = 0, tatget = 0;
		for (int j = 0; j < population_->best_5.size(); j++)
		{
			if (j == population_->best_5.size()-1)
				break;
			for (int k = j + 1; k < population_->best_5.size(); k++)
			{
				if (population_->best_5[j].x == population_->best_5[k].x&&
					population_->best_5[j].y == population_->best_5[k].y)
				{
					count++;
				}
				tatget++;
			}
		}
		//4+3+2+1
		printf("tatget:%d count:%d\n", tatget, count);
		if (count == tatget && tatget>=10)
		{
			file << gen << " " << population_->Gadd << std::endl;
			printf("return 2!!!!!!!!!!!\n");
			file.close();
			end = clock();
			return population_->best_5[0];
		}
		else
			population_->generate_next();
		//for (int i = 0; i < population_->currentGeneration.size(); i++)
		//	printf("generate_next*******size: %d ************************\n", population_->currentGeneration[i].size());
		end = clock();
		file << gen<<" "<<population_->Gadd << std::endl;
		
		printf("time: %lf\n", ((double)(end - start)) / CLOCKS_PER_SEC);
	}


	//已離開迴圈，計算在best_5重複性
	std::vector<point_> best;
	for (int i = 0; i < population_->best_5.size(); i++)
	{
		bool check = false;
		if (best.size() != NULL)
		{
			for (int k = 0; k < best.size(); k++)
			{
				if (best[k].x == population_->best_5[i].x&&
					best[k].y == population_->best_5[i].y)
				{
					check = true;
				}
			}
			if(!check)
				best.push_back(population_->best_5[i]);
		}
		else 
		{
			best.push_back(population_->best_5[i]);
		}
	}


	for (int i = 0; i < best.size(); i++)
	{
		if (best[best.size() - i - 1].x != NULL
			&& best[best.size() - i - 1].y != NULL)
		{
			file.close();
			return best[best.size() - i - 1];
		}
	}
}

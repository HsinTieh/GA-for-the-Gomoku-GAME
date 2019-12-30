#include "stdafx.h"
#include "GA.h"
#include"rule.h"
GA::GA(int recodeList[][gomokuline])
{
	srand(time(NULL));
	/// 突变概率:5%,交叉概率:80%,原始种群:100,总共代数:2000,基因串长度8
	this->mutationRate = 0.02;
	this->crossoverRate = 0.8;
	this->initPopulationCount = 100;
	this->maxGenerationCount = 100;
	this->genomeSize = 8;
	createPopulation(recodeList);
}

GA::~GA()
{
}

double GA::getCrossoverRate()
{
	return this->crossoverRate;
}

double GA::getMutationRate()
{
	return this->mutationRate;
}

int GA::getMaxGenerationCount()
{
	return this->maxGenerationCount;
}

std::vector<genomes> GA::getGenome()
{
	return this->genome;
}


int GA::getInitPopulationCount()
{
	return this->initPopulationCount;
}



int GA::getGenomeSize()
{
	return genomeSize;
}

void GA::setGenome(std::vector<genomes> genome)
{
	this->genome = genome;
}

genomes GA::getBestGenome()
{
	return this->bestGenome;
}

void GA::calculationFitness(genomes* ge, std::string user, int recodeList[][gomokuline])
{
		//printf("cal \n");
		double maxPower = DBL_MAX * (-1);
		double minPower = DBL_MAX;
		int maxPowerIndex = 0;
		int minPowerIndex = 0;
		rule* rule_ = new rule();
		point chess;
		std::string currentChessType = user;
		
		//printf("222size :%d \n", ge->genes.size());
		for (int i = 0; i < ge->genes.size(); i++)
		{
			//printf("****************************\n");
			recodeList[ge->genes[i].x][ge->genes[i].y] = rule_->getWhoArrayValue(user, "own");
			//printf("(%d,%d) = %d\n", ge->genes[i].x, ge->genes[i].y, recodeList[ge->genes[i].x][ge->genes[i].y]);

			/*if (recodeList[ge->genes[i].x][ge->genes[i].y] != 0)
			{
				chess = ge->genes[i];
				printf("! %d  ", i);
			}*/
			//printf("\n i = %d\n",i);
			
			double tempPower = singlePower(ge->genes[i], user, recodeList) * 1 * pow(0.96, i);
			printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!%lf\n",  tempPower);
			if (tempPower > maxPower)
			{
				maxPowerIndex = i;
				maxPower = tempPower;
			}
			if (tempPower < minPower)
			{
				minPowerIndex = i;
				minPower = tempPower;
			}

			if (maxPower > (100 * pow(0.96, i)))
				break;

			if (user == "black")
				user = "white";
			else if (user == "white")
				user = "black";
			//printf("*********************** change :%s********************************\n",user);

		}
		//printf("init for end  ");
		///////
		if (abs(minPower) > abs(maxPower))
		{
			ge->setBestGenesIndex(minPowerIndex);
			ge->setFitness(minPower);
		}
		else
		{
			ge->setBestGenesIndex(maxPowerIndex);
			ge->setFitness(maxPower);
		}
		//printf("fitness: %d \n", ge->reFitness());
		//printf("333size :%d \n", ge->genes.size());
		for (int i=0;i< ge->genes.size();i++)
			recodeList[ge->genes[i].x][ge->genes[i].y] = 0;
		//printf("444size :%d \n", ge->genes.size());
		
		ge->genes = creatGene(genomeSize, recodeList);
		printf("inti end \n");
		
	
}

void GA::updateAllFitness()
{
	this->allFitness = 0;
	for (int i = 0; i < genome.size(); i++)
		this->allFitness += abs(genome[i].reFitness());
}

void GA::updateFitness(int recodeList[][gomokuline],std::string user)
{
	for (int i = 0; i < genome.size(); i++)
	{
		printf("genome count :%d\n", i);
		calculationFitness(&genome[i], user, recodeList);
		//genome[i].setFitness(calculationFitness(genome[i],user,recodeList));
	}
}

 bool GA::GAcompare(genomes a, genomes b)
{
	return (a.reFitness() > b.reFitness());
}

void GA::setParameter(double crossoverRate, double mutationRate, int initPopulationCount, int maxGenerationCoount, int genomeSize, int recodeList[][gomokuline])
{
	this->crossoverRate = crossoverRate;
	this->mutationRate = mutationRate;
	this->initPopulationCount = initPopulationCount;
	this->maxGenerationCount = maxGenerationCoount;
	this->genomeSize = genomeSize;
	//創造族群
	createPopulation(recodeList);
}

void GA::createPopulation(int recodeList[][gomokuline])
{
	std::vector<genomes> list;
	genomes *ge;
	for (int i = 0; i < initPopulationCount; i++)
	{
		ge = new genomes(genomeSize, recodeList);
		list.push_back(*ge);
	}
	genome = list;
}
///////////////////////////////////////////
void GA::select()
{
	probability prob;
	std::vector<genomes> list;
	updateAllFitness();
	printf("updateAllFitness = %lf \n", allFitness);
	for (int i = 0; i < genome.size(); i++)
	{
		if (prob.probabilityResult(abs(genome[i].reFitness()) / this->allFitness))
			list.push_back(genome[i]);
	}
	nextGenome = list;
}
///////////////////////////////////////////////
void GA::bron()
{
	probability prob;
	if (prob.probabilityResult(crossoverRate))
	{
		printf("crossovering...........\n");
		//随机两個父代
		genomes parent = genome[rand() % (0 + genome.size() / 2)];
		genomes parent2 = genome[rand() % (0 + genome.size() / 2)];

		std::vector<genomes> childs = parent.ToCrossover(parent2);
		for (int i = 0; i < childs.size(); i++)
			nextGenome.push_back(childs[i]);
		printf("crossovered \n");

	}

}

void GA::mutation()
{
	probability prob;
	if (prob.probabilityResult(mutationRate))
	{
		printf("mutationing ......\n");
		if (nextGenome.size() > 1)
			nextGenome[rand() % (nextGenome.size())].mutate();
		printf("mutationed\n");

	}
}

int GA::singlePower(point p, std::string user, int recodeList[][gomokuline])
{
	rule *rule_ = new rule();
	coordinate_ coor = rule_->calculationChessCount(p.x, p.y, recodeList, user);
	if (rule_->getLongLink(coor, user, recodeList) > 0)
		return (user == "white") ? longLink : longLink * (-1);
	if (rule_->getLive4(coor, user) > 0)
		return (user == "white") ? live4 : live4 * (-1);
	if (rule_->getRush4(coor, user) > 0)
		return (user == "white") ? rush4 : rush4 * (-1);
	if (rule_->getLive3(coor, user) > 0)
		return (user == "white") ? live3 : live3 * (-1);
	if (rule_->getRush3(coor, user) > 0)
		return (user == "white") ? rush3 : rush3 * (-1);
	//printf("return singlePower\n");

	int count = rule_->computing2_1(p, user, recodeList);
	//printf("return singlePower 2 or 1\n");

	return (user == "white") ? count : (count * -1);
}

std::vector<point> GA::creatGene(int count, int recodeList[][gomokuline])
{
	std::vector<point> list;
	point p;
	p.x = -1;
	p.y = -1;
	probability* pro =new probability();
	rule* rule_ = new rule();;
	for (int i = 0; i < count; i++)
	{
		while (true)
		{
			p = pro->CreateRandGene();
			/////// ==? != ?
			if (recodeList[p.x][p.y] == 0 && !(rule_->checkChess(p, recodeList)))
			{
				list.push_back(p);
				//printf("gene : (%d , %d) \n", p.x, p.y);
				break;
			}
		}
	}
	return list;

}

void GA::enter(std::string user, int recodeList[][gomokuline])
{
	//printf("maxGenerationCount: %d \n", maxGenerationCount);
	for (int i = 0; i < this->maxGenerationCount; i++) 
	{
		printf("~~~~~~~~~~~~~~~~~~~~~i:%d\n", i);
		updateFitness(recodeList,user);
		//排序
		printf("排序");
		//std::sort(genome.begin(), genome.end(), std::bind(compare,this, std::placeholders::_1, std::placeholders::_2));
		std::sort(genome.begin(), genome.end(), GAcompare);
		//for (int k = 0; k < genome.size(); k++)
		//{
		//	printf("%d  ", genome[k].reFitness());
		//}
		//printf("\nsort end\n");
		printf("最好的適應度與最差的適應度相同");
		//最好的適應度與最差的適應度相同
		if (genome.size() == 0 || genome[genome.size() - 1].reFitness() == genome[0].reFitness())
			break;

		if (abs(genome[genome.size() - 1].reFitness()) < abs(genome[0].reFitness()))
			this->bestGenome = genome[0];
		else
			this->bestGenome = genome[genome.size() - 1];
		printf("select");
		select();
		printf("bron");
		bron();
		printf("mutation");
		mutation();
		printf("nextGenome");
		genome = nextGenome;
	}


}

void GA::printfCuttentGe()
{
	printf("*********************************\n");
	for (int i = 0; i < genome.size(); i++)
		printf("fitness : %lf \n",genome[i].reFitness());
	printf("*********************************\n");
}

genomes::genomes()
{
}

genomes::genomes(int count, int recodeList[][gomokuline])
{
	this->genes = creatGenome(count, recodeList);
}

genomes::genomes(std::vector<point> genes)
{
	this->genes = genes;
}

genomes::~genomes()
{
}

std::vector<point> genomes::creatGenome(int count, int recodeList[][gomokuline])
{
	std::vector<point> list;
	point p;
	p.x = -1;
	p.y = -1;
	probability* pro = new probability();
	rule* rule_ = new rule();;
	for (int i = 0; i < count; i++)
	{
		while (true)
		{
			p = pro->CreateRandGene();
			/////// ==? != ?
			if (recodeList[p.x][p.y] == 0 && checkBeenCreatPoint(p, list) && (rule_->checkChess(p, recodeList)))
			{
				list.push_back(p);
				printf("i = %d  gene : (%d , %d) \n", i,p.x, p.y);
				break;
			}
		}
	}
	return list;
}





std::vector<genomes> genomes::ToCrossover(genomes parent2)
{
	crossover* cross = new crossover(this->genes, parent2.genes, 3);
	return cross->getChild();
}

int genomes::findGenes(point p, genomes genome)
{
	for (int i = 0; i < genome.genes.size(); i++)
	{
		if(genome.genes[i].x == p.x && genome.genes[i].y == p.y)
			return i;
	}
	return -1;
}

void genomes::mutate()
{
	//突變
	int count = rand() % (4) + 1; //1-4
	for (int i = 0; i < count; i++)
	{
		printf("mutate count : %d\n", i);
		int index1 = rand() % (this->genes.size() - 0);
		int index2 = rand() % (this->genes.size() - 0);

		point randGene = this->genes[index1];
		this->genes[index1] = this->genes[index2];
		this->genes[index2] = randGene;
	}
}

int genomes::compare(genomes other)
{
	if (this->fitness > other.fitness)
		return 1;
	else if (this->fitness == other.fitness)
		return 0;
	else
		return -1;
}

double genomes::reFitness()
{
	return this->fitness;
}

void genomes::setFitness(double fitness)
{
	this->fitness = fitness;
}

point genomes::reBestGenes()
{
	return this->bestGenes;
}

void genomes::setBestGenes(point bestGenes)
{
	this->bestGenes = bestGenes;
}

int genomes::reBestGenesIndex()
{
	return this->bestGenesIndex;
}

void genomes::setBestGenesIndex(int bestGenesIndex)
{
	this->bestGenesIndex = bestGenesIndex;
}


crossover::crossover(std::vector<point> parent, std::vector<point> parent2, int count)
{
	srand(time(NULL));

	this->parent = parent;
	this->parent2 = parent2;
	this->child.resize(parent.size());
	this->child2.resize(parent2.size());
	this->staticGens.resize(count);
	generateRandGen();

}

std::vector<genomes> crossover::getChild()
{
	std::vector<point> filterAfterParent = filterParent();
	std::vector<point> filterAfterParent2 = filterParent2();
	std::vector<genomes> ge;

	int index = 0;
	for (int i = 0; index < this->child.size(); index++)
	{
		if (child[index].x != NULL && child[index].y != NULL)
			continue;
		else
		{
			if (i >= filterAfterParent2.size())
				child[index] = this->parent[index];
			else
			{
				child[index] = filterAfterParent2[i];
				i++;
			}
		}
	}

	int index2 = 0;
	for (int i = 0; index2 < this->child2.size(); index2++)
	{
		if (child2[index2].x != NULL && child2[index2].y != NULL)
			continue;
		else
		{
			if (i >= filterAfterParent.size())
				child2[index2] = this->parent2[index2];
			else
			{
				child2[index2] = filterAfterParent[i];
				i++;
			}
		}
	}
	ge.push_back(child);
	ge.push_back(child2);
	return ge;
}

void crossover::generateRandGen()
{
	std::vector<point> randParent;
	for (int i = 0; i < randGenCount; i++)
	{
		if (i % 2 == 0)
			randParent = this->parent;
		else
			randParent = this->parent2;
		staticGens[i] = randParent[rand() % (randParent.size() - 0 + 1)];
	}
}

std::vector<point> crossover::filterParent()
{
	std::vector<point> filter;
	for (int i = 0; i < this->parent.size(); i++)
	{
		filter.push_back(parent[i]);
		child[i].x = NULL;
		child[i].y = NULL;
		for (int index = 0; index < this->randGenCount; index++)
		{
			if (staticGens[index].x == parent[i].x && staticGens[index].y == parent[i].y)
			{
				child[i] = staticGens[index];
				filter.pop_back();
				break;
			}
		}
	}
	return filter;
}

std::vector<point> crossover::filterParent2()
{
	std::vector<point> filter;
	for (int i = 0; i < this->parent2.size(); i++)
	{
		filter.push_back(parent2[i]);
		child2[i].x = NULL;
		child2[i].y = NULL;
		for (int index = 0; index < this->randGenCount; index++)
		{
			if (staticGens[index].x == parent2[i].x && staticGens[index].y == parent2[i].y)
			{
				child2[i] = staticGens[index];
				filter.pop_back();
				break;
			}
		}
	}
	return filter;
}

bool probability::probabilityResult(double rate)
{

	double rate_ = rate;
	int randMAX = 1;
	while (rate_ < 10 && rate_ != 0)
	{
		rate_ = rate_ * 10;
		randMAX = randMAX * 10;
	}

	//如果发生概率事件,执行委托函数
	if ((double)rand() / (RAND_MAX + 1.0) <= rate_)
		return true;

}

point probability::CreateRandGene()
{
	point p;

	p.y = rand() % (15);
	p.x = rand() % (15);
	return p;
}

bool genomes::checkBeenCreatPoint(point p, std::vector<point> BeenCreatPoint)
{

	if (BeenCreatPoint.size() != NULL)
	{
		for (int i = 0; i < BeenCreatPoint.size(); i++)
		{
			if (BeenCreatPoint[i].x == p.x && BeenCreatPoint[i].y == p.y)
			{
				return false;
			}
		}
	}
	else
	{
		
		return true;
	}
	
	return true;
}

#pragma once
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <algorithm>
#include <functional>
#define gomokuline 15
public struct point
{
	int x;
	int y;
};
public class genomes
{
private:

	point bestGenes;
	int bestGenesIndex = 0;
	double fitness;
public:
	std::vector<point> genes;
	//		function		//
	genomes();
	genomes(int count, int recodeList[][gomokuline]);
	genomes(std::vector<point> genes);
	~genomes();
	std::vector<point> creatGenome(int count, int recodeList[][gomokuline]);

	std::vector<genomes> ToCrossover(genomes parent2);
	int findGenes(point p, genomes genome);
	void mutate();
	int compare(genomes other);


	double reFitness();
	void setFitness(double fitness);
	point reBestGenes();
	void setBestGenes(point bestGenes);
	int reBestGenesIndex();
	void setBestGenesIndex(int bestGenesIndex);

	//檢查是否已經生成點座標
	
	bool checkBeenCreatPoint(point p, std::vector<point> BeenCreatPoint);
};


public class GA
{
	public:
		GA(int recodeList[][gomokuline]);
		~GA();
		double getCrossoverRate();
		double getMutationRate();
		int getMaxGenerationCount();
		int getInitPopulationCount();
		int getGenomeSize();
		void setGenome(std::vector<genomes> genome);
		genomes getBestGenome();
		std::vector<genomes> getGenome();
		static bool GAcompare(genomes a, genomes b);
		void enter(std::string user, int recodeList[][gomokuline]);
		void printfCuttentGe();
		double fitness;//族群適應度
		double allFitness;
		genomes bestGenome;//目前最好的個體

	private:
		double crossoverRate; //交配概率
		double mutationRate; //變異概率
		int initPopulationCount;//原始族群數
		int maxGenerationCount;//最大族群數
		int genomeSize;//每個族群的大小
		std::vector<genomes> genome;//族群容器
		std::vector<genomes> nextGenome;//下一個種族

		//計算適應度
		void calculationFitness(genomes* ge, std::string user, int recodeList[][gomokuline]);
		void updateAllFitness();
		void updateFitness(int recodeList[][gomokuline], std::string user);

		void setParameter(double crossoverRate, double mutationRate, int initPopulationCount, int maxGenerationCoount, int genomeSize, int recodeList[][gomokuline]);
		void createPopulation(int recodeList[][gomokuline]);
		void select();
		void bron();
		void mutation();
		int singlePower(point p, std::string user, int recodeList[][gomokuline]);
		std::vector<point> creatGene(int count, int recodeList[][gomokuline]);


};

public class crossover
{
public:
	crossover(std::vector<point> parent, std::vector<point> child, int count);
	std::vector<genomes> getChild();
private:
	std::vector<point> parent;
	std::vector<point> child;
	std::vector<point> parent2;
	std::vector<point> child2;
	std::vector<point> staticGens;

	int randGenCount;

	void generateRandGen();
	std::vector<point> filterParent();
	std::vector<point> filterParent2();

};


class probability
{
private:
	double globleRand;
public:
	bool probabilityResult(double rate);
	point CreateRandGene();
};
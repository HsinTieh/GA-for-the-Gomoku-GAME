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

	//�ˬd�O�_�w�g�ͦ��I�y��
	
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
		double fitness;//�ڸs�A����
		double allFitness;
		genomes bestGenome;//�ثe�̦n������

	private:
		double crossoverRate; //��t���v
		double mutationRate; //�ܲ����v
		int initPopulationCount;//��l�ڸs��
		int maxGenerationCount;//�̤j�ڸs��
		int genomeSize;//�C�ӱڸs���j�p
		std::vector<genomes> genome;//�ڸs�e��
		std::vector<genomes> nextGenome;//�U�@�Ӻر�

		//�p��A����
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
#include "rule.h"
#include <math.h>
#include <time.h>
#include<fstream>
struct point_
{
	int x;
	int	y;
};

struct pp
{
	std::vector<point_> Generation;
	double fit;
};

struct p3
{
	point_ p;
	int fit;
};

struct fitForIndividualfit
{
	point_ p;
	std::vector<int> fit;

};
struct individualfitSetAndAllIndividualfit
{
	point_ p;
	std::vector<p3>  individualfit;
	int fit;
	std::vector<point_> Generation;

};

class board
{
public:
	int recodeListBoard[gomokuline][gomokuline];
	board();
	board(int recodeList[][gomokuline]);
	std::vector<point_> mutata(std::vector<point_> origin_individual, std::vector<point_> DNA_base);
	void crrorover(std::vector<point_> individual1, std::vector<point_> individual2);
	std::vector<point_> individual1;
	std::vector<point_> individual2;
	//計算可下的位置有哪些
	std::vector<point_> get_avil(int recodeList[][gomokuline]);
private:
	int n_in_line;
	//可下的位置集合
	std::vector<point_> availables;
	//不可下的位置集合
	std::vector<point_> unavailables;

	point_ update(std::string user,point_ move);

};

class population
{
public:
	int recodeListPopulation[gomokuline][gomokuline];
	population();
	population(std::vector<point_> potentialGene);
	population(std::vector<point_>potential_position, int DNA_length, double mutate_rate_limit, int start_number, int number_limit, double sruvival_rate, int recodeList[][gomokuline],double time_limit);
	void select(std::string user,int gen);
	int fitness(point_ p, int recodeList[][gomokuline], std::string user, int gen);
	int evalMove(point_ p, int recodeList[][gomokuline], std::string user, int gen);
	individualfitSetAndAllIndividualfit eval_individual(std::vector<point_> set, int recodeList[][gomokuline], std::string user, int gen);
	
	bool find_best_firsts();
	void generate_next();
	std::vector<point_> best_5;
	std::vector<std::vector<point_> >best_5_2;
	std::vector <std::vector<point_>> currentGeneration;//二維
	std::vector <individualfitSetAndAllIndividualfit>  currentIndividualfitSetAndAllIndividualfit;
	std::vector<double> aaaaa;
	double Gadd;

private:
	//限制運行時間
	double time_limit;
	//個體基因
	std::vector<point_> DNA_base;
	int DNA_length;
	//總體數量
	int start_number;
	int number_limit;
	//概率
	double mutate_rate_limit;
	//選擇
	double survival_rate;

	int crossoverTemp1 = 0;
	std::vector <std::vector<point_>> beginGeneration();
	//GAsort1
	static bool GAcompare(individualfitSetAndAllIndividualfit a, individualfitSetAndAllIndividualfit b);
	static bool GAsort2(int  a, int  b);

	static bool GAcompare3(p3 a, p3 b);
	

};


class geneticA 
{
	public:
		geneticA(int recodeList[][gomokuline], std::string user, int n_in_line, int DNA_length, double mutate_rate_limit, int start_number, int number_limit, double sruvival_rate,double time_limit);

		geneticA();
		double select_function();
		bool check_function(std::vector<point_> individual1);
		point_ get_action(std::string user);
	private:
		board* current_board;
		std::string player_turn;
		int n_in_line;

		//double time_limit;
		std::vector<point_> potential_position;
		population *population_;

		//初始化 Population 會用到
		int DNA_length;
		double mutate_rate_limit;
		int start_number;
		int number_limit;
		double sruvival_rate;
		double time_limit;
};
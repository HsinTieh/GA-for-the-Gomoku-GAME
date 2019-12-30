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
	//�p��i�U����m������
	std::vector<point_> get_avil(int recodeList[][gomokuline]);
private:
	int n_in_line;
	//�i�U����m���X
	std::vector<point_> availables;
	//���i�U����m���X
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
	std::vector <std::vector<point_>> currentGeneration;//�G��
	std::vector <individualfitSetAndAllIndividualfit>  currentIndividualfitSetAndAllIndividualfit;
	std::vector<double> aaaaa;
	double Gadd;

private:
	//����B��ɶ�
	double time_limit;
	//�����]
	std::vector<point_> DNA_base;
	int DNA_length;
	//�`��ƶq
	int start_number;
	int number_limit;
	//���v
	double mutate_rate_limit;
	//���
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

		//��l�� Population �|�Ψ�
		int DNA_length;
		double mutate_rate_limit;
		int start_number;
		int number_limit;
		double sruvival_rate;
		double time_limit;
};
#pragma once
#include<iostream>
#include<fstream>
#include<time.h>

using namespace std;

class Food;
class Game;
class Wall;
class Snake;

struct coor {
	int x, y;
	coor* next, * last;
};

class Wall {
private:
	coor* head, * tail;
	bool destructed;

public:
	Wall(Game&);
	Wall(istream&, Game&);
	void append(int, int, Game&);
	coor* wall_head();
	~Wall();
};

class Food {
private:
	coor* head, * tail;
	bool destructed;

public:
	Food(Game&);
	Food(istream&, Game&);
	void append(int, int, Game&);
	coor* food_head();
	void remove(int, int, Game&);
	void new_food(Game&);
	~Food();
};

class Game {
private:
	int mode;
	char map[40][40]; //0���հ� 1��ǽ 2��ʳ�� 3����
	int lives;
	int score;
	bool destructed;
	int maxs;
	int blank;
public:
	friend class Wall; //�ǵ�������Ԫ�࣡
	friend class Food; 
	friend class Snake;
	Game(int md);
	Game(istream&);
	int query(int, int);
	void upd_map(int, int, int);
	void upd_view(int, int, int);
	void show_UI();
	void add_score();
	int get_score();
	void die();
	bool over();
	int get_mode();
	void set_mode(int);
	~Game();
};

class Snake {
private:
	coor* head, * tail;
	int dir;
	int removed_x, removed_y;
	bool destructed;
public:
	friend class Wall;
	friend class Food;
	Snake(Game&);
	Snake(istream&, Game&);
	void append(int, int, Game&);
	coor* snake_head();
	void move(int, Game&);
	void recover(Game&);
	bool reset(Game&, Food&, Wall&, int);
	int get_dir();
	~Snake();
};

int menu(); //��ҳ��
int menu1(); //���롾��ʼ��Ϸ����ѡ����Ϸģʽ
void menu2(); //���롾��ʷ��¼�������ʾ
int button_judge(int x, int y, int r[3][4]);
int Keyboard_monitor(int time_limit, bool flag);
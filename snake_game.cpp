/**
 * Snake game
 * You can play by yourself or see how AI performs
 */
#include <ncurses.h>
#include <stdlib.h> //replace with C++ random function?
#include <iostream>
#include <signal.h>
#include <sys/time.h>
#include <deque>
#include <time.h>
#include <queue>
#include <stack>

using namespace std;

struct Position {
	int x;
	int y;
	Position() : x(0), y(0) {};
	Position(int xi, int yi) : x(xi), y(yi) {};
};

class Snake {
public:
	static const char SNAKEHEAD = '*';
	static const char SNAKEBODY = '+';
	int direction;
	enum DIRECTION { DOWN = 0, UP, LEFT, RIGHT, KEEP };
	deque<Position> s;
	int length;
	//Snake() {};
};

class Game {
public:
	static int istimeup;
	int width;
	int height;
	char **status;
	char score[8];
	WINDOW *board;
	WINDOW *cntl;
	Snake snake;
	enum policy { HUMAN = 0, LOW_AI, NORMAL_AI, SMART_AI, INSINE_AI };
	int type;
	Position food;
	//the interval between every move of snake, unit is millisecond
	int interval;
	deque<Position> path;

	Game();
	Game(int w, int h);
};

Game::Game() {}
Game::Game(int w, int h) : width(w), height(h) {}

int Game::istimeup = 0;

int parse(int argc, char *argv) {
	//return Game::HUMAN;
	//return Game::LOW_AI;
	return Game::NORMAL_AI;
}

int displayWorld(Game& game) {
	//mvwaddch(game.board, game.height, game.width, ' ' | A_NORMAL);
	//wrefresh(game.board);
	//wrefresh(game.cntl);
	wnoutrefresh(game.board);
	wnoutrefresh(game.cntl);
	doupdate();
}

void game_over(int exit_status) {
	endwin();
	cout << "exit: " << exit_status << endl;
	exit(exit_status);
}

void timeup(int cp) {
	//cout << "timeup " << endl;
	Game::istimeup = 1;
}

void place_food(Game& game) {
	int remain = (game.height - 2) * (game.width - 2) - game.snake.s.size();
	if (remain == 0) {
		//big win
		game_over(2);
	}
	int nfp = rand() % remain;

	int cur = 0;
	nfp++;
	for (int i = 0; i < game.width - 2; i++) {
		for (int j = 0; j < game.height - 2; j++) {
			if (game.status[i + 1][j + 1] != '#')
				nfp--;
			if (!nfp) {
				//game.status[i + 1][j + 1] = '#';
				mvwaddch(game.board, j + 1, i + 1, '#' | A_NORMAL);
				game.food.x = i + 1;
				game.food.y = j + 1;
			}
		}
	}
	game.path.clear();
}

//util function: transfer integer like 312 to str "312"
char *_itos(int score, char *str) {
	int digits[10];
	int i = 0;
	while (score >= 10) {
		digits[i++] = score % 10;
		score = score / 10;
	}
	digits[i++] = score;
	int j = 0;
	while(i > 0) {
		str[j++] = digits[i - 1] + '0';
		i--;
	}
	str[j] = '\0';
	return str;
}

void updateStatus(Game& game) {
	mvwaddstr(game.cntl, 0, 10,
		_itos(game.snake.s.size(), game.score));
}

void init(int type, Game& game) {
	game.width = 32;
	game.height = 32;
	game.type = type;
	game.interval = 500;

	//set characters set: default ISO-8859-1
 	setlocale(LC_ALL, "");

 	initscr();
 	cbreak();
 	noecho();
 	//keypad(game.board, TRUE);

 	game.board = newwin(game.height, game.width, 0, 0);
 	nodelay(game.board, TRUE);

 	srand(static_cast<int>(time(NULL)));
 	Position s;
 	s.x = (rand() % (game.width - 2)) + 1;
 	s.y = (rand() % (game.height - 2)) + 1;
 	game.status = new char*[game.width];
 	for (int i = 0; i < game.width; i++) {
 		game.status[i] = new char[game.height];
 		if (!game.status[i]) {
 			cout << "Alloc failed: " << i << endl;
 			exit(2);
 		}
 	}
 	//memset((char *)game.status, ' ', game.width * game.height);
 	game.snake.s.push_back(s);
 	game.snake.direction = rand() % 4;
 	mvwaddch(game.board, s.y, s.x, Snake::SNAKEHEAD | A_NORMAL);
 	game.status[s.x][s.y] = '#';
 	//draw board
 	for (int i = 0; i < game.height; i++) {
 		mvwaddch(game.board, i, 0, '#' | A_NORMAL);
 		game.status[0][i] = '#';
 		mvwaddch(game.board, i, game.width - 1, '#' | A_NORMAL);
 		game.status[game.width - 1][i] = '#';
 	}
 	for (int i = 0; i < game.width; i++) {
 		mvwaddch(game.board, 0, i, '#' | A_NORMAL);
 		game.status[i][0] = '#';
 		mvwaddch(game.board, game.height - 1, i, '#' | A_NORMAL);
 		game.status[i][game.height - 1] = '#';
 	}
 	place_food(game);

 	game.cntl = newwin(3, game.width, game.height, 0);
 	mvwaddstr(game.cntl, 0, 3, "Score:");
}

void move(Game& game, int d) {
	//cout << "move " << d << endl;

	//calculate next position of snake head
	if (d != Snake::KEEP)
		game.snake.direction = d;
	Position head = game.snake.s.front();
	//cout << "head, x: " << head.x << ", y: " << head.y << " " << game.snake.s.size() << endl;
	switch (game.snake.direction) {
		case Snake::DOWN:
		head.y++; break;
		case Snake::UP:
		head.y--; break;
		case Snake::LEFT:
		head.x--; break;
		case Snake::RIGHT:
		head.x++; break;
		default:;
	}

	//check valid:
	if (head.x <= 0 || head.y <= 0 || head.x >= game.width - 1 || head.y >= game.height - 1) {
		//crash
		sleep(3);
		endwin();
		cout << "head, x: " << head.x << ", y: " << head.y << endl;

 		game_over(1);
	}

	//snake move a step forward
	game.snake.s.push_front(head);
	//cout << "move ahead, x: " << head.x << ", y: " << head.y << endl;
	mvwaddch(game.board, head.y, head.x, Snake::SNAKEHEAD | A_NORMAL);
	game.status[head.x][head.y] = '#';
	//update body if there is one
	if (game.snake.s.size() > 1) {
		mvwaddch(game.board, game.snake.s[1].y, 
			game.snake.s[1].x, Snake::SNAKEBODY | A_NORMAL);
	}
	//is food?
	if (head.x == game.food.x && head.y == game.food.y) {
		//eat this food, regenerate a new food
		place_food(game);
	} else {
		//no food, clean the tail
		Position tail = game.snake.s.back();
		game.snake.s.pop_back();
		//cout << "clear tail, x: " << tail.x << ", y: " << tail.y << endl;
		mvwaddch(game.board, tail.y, tail.x, ' ' | A_NORMAL);
		game.status[tail.x][tail.y] = ' ';
	}
}

void action(Game &game) {
	bool action = false;
	struct itimerval timer;
	timer.it_value.tv_sec = 1;
	timer.it_value.tv_usec = 0;
	timer.it_interval.tv_sec = 1;
	timer.it_interval.tv_usec = 0;
	signal(SIGALRM, timeup);
	setitimer(ITIMER_REAL, &timer, NULL);
	//istimeup = false;
	int c;
	while(1) {
		Game::istimeup = 0;
		action = false;
		while (!Game::istimeup && !action) {
			if ((c = wgetch(game.board)) == ERR) {
 				//mvwaddch(farm, y, x, '#');
 			} else if (c == 'q') {
 				game_over(0);
	 		} else {
 				switch (c) {
 					case 'w':
 					action = true;
 					c = Snake::UP;
 					break;
 					case 'a':
 					action = true;
 					c = Snake::LEFT;
 					break;
 					case 's':
 					action = true;
 					c = Snake::DOWN;
 					break;
	 				case 'd':
	 				action = true;
	 				c = Snake::RIGHT;
	 				break;
 					default: ;
 				}
 			}
 		}
 		//wait;
 		if (!action) {
			c = Snake::KEEP;
		}
		move(game, c);
 		while (!Game::istimeup) ;
		updateStatus(game);
		displayWorld(game);
	}
}

int ramble(Game& game) {
	//peek a random feasible direction
	int ds[4];
	Position head = game.snake.s.front();
	//check left
	int p = 0;
	if (head.x - 1 > 0 && game.status[head.x - 1][head.y] != '#') {
		ds[p++] = Snake::LEFT;
	}
	if (head.x + 1 < game.width - 1 && game.status[head.x + 1][head.y] != '#') {
		ds[p++] = Snake::RIGHT;
	}
	if (head.y - 1 > 0 && game.status[head.x][head.y - 1] != '#') {
		ds[p++] = Snake::UP;
	}
	if (head.y + 1 < game.height - 1 && game.status[head.x][head.y + 1] != '#') {
		ds[p++] = Snake::DOWN;
	}

	if (p == 0) return Snake::KEEP;

	int pick = rand() % p;
	//cout << "Next: " << ds[pick] << endl;
	return ds[pick];
}

int shortestpath(Game& game) {
	int graph[game.width][game.height];
	for (int i = 0; i < game.width; i++) {
		for (int j = 0; j < game.height; j++) {
			if (game.status[i][j] == '#' || game.status[i][j] == Snake::SNAKEHEAD
				|| game.status[i][j] == Snake::SNAKEBODY)
				graph[i][j] = 3;
			else
				graph[i][j] = 0;
		}
	}
	//bfs
	deque<Position> vstak;
	Position target = game.food;
	Position source = game.snake.s.front();
	graph[target.x][target.y] = 0;
	vstak.push_back(source);
	graph[source.x][source.y] = 1;
	Position path[game.width][game.height];
	static int debug = 0;
	//cout << "dfs: " << endl;
	while (!vstak.empty()) {
		Position p = vstak[0];
		vstak.pop_front();

		if (p.x == target.x && p.y == target.y) { //find the food
			game.path.clear();
			//game.path.insert(p);
			//cout << "Find\n";
			while (p.x != source.x || p.y != source.y) {
				game.path.push_front(p);
				p = path[p.x][p.y];
			}
			cout << "  Find " << debug++ << "\n";
			return 0;
		}
		//up
		if (p.y - 1 > 0 && graph[p.x][p.y - 1] == 0) {
			graph[p.x][p.y - 1] = 1;
			Position tmp(p.x, p.y - 1);
			vstak.push_back(tmp);
			path[p.x][p.y - 1] = p;
		}
		//down
		if (p.y + 1 < game.height - 1 && graph[p.x][p.y + 1] == 0) {
			graph[p.x][p.y + 1] = 1;
			Position tmp(p.x, p.y + 1);
			vstak.push_back(tmp);
			path[p.x][p.y + 1] = p;
		}
		//left
		if (p.x - 1 > 0 && graph[p.x - 1][p.y] == 0) {
			graph[p.x - 1][p.y] = 1;
			Position tmp(p.x - 1, p.y);
			vstak.push_back(tmp);
			path[p.x - 1][p.y] = p;
		}
		//right
		if (p.x + 1 < game.width - 1 && graph[p.x + 1][p.y] == 0) {
			graph[p.x + 1][p.y] = 1;
			Position tmp(p.x + 1, p.y);
			vstak.push_back(tmp);
			path[p.x + 1][p.y] = p;
		}
		graph[p.x][p.y] = 2;
	}
	//no answer so far, try to move one step forward randomly
	return ramble(game);
	//return Snake::KEEP;
}

int ptom(Position s, Position n) {
	if (s.x > n.x)
		return Snake::LEFT;
	if (s.x < n.x)
		return Snake::RIGHT;
	if (s.y > n.y)
		return Snake::UP;
	if (s.y < n.y)
		return Snake::DOWN;
	return Snake::KEEP;
}

int ai(Game& game, int level) {
	//find path 
	int d = Snake::KEEP;
	switch (level) {
		case Game::LOW_AI:
		d = ramble(game);
		break;
		case Game::NORMAL_AI: {
			//cout << "normal ai" << endl;
			if (game.path.empty())
				d = shortestpath(game);
			if (game.path.empty())
				break;
			Position next = game.path[0];
			game.path.pop_front();
			d = ptom(game.snake.s.front(), next);
			break;
		}
		default:
		;
	}
	return d;
}

void robot(Game& game, int level) {
	bool result = false;
	int direction;
	struct timespec ts;
	ts.tv_sec = 0;
	//500ms
	ts.tv_nsec = 100 * 1000 * 1000;
	while (1) {
		result = false;
		direction = ai(game, level);
		//wait
		nanosleep(&ts, NULL);
		move(game, direction);
		updateStatus(game);
		displayWorld(game);
	}
}

void perform(Game& game) {
	switch (game.type) {
		case Game::HUMAN:
		action(game);
		break;
		case Game::LOW_AI:
		case Game::NORMAL_AI:
		robot(game, game.type);
		break;
		default: ;
	}
}

void run(Game& game) {
		//displayWorld();
		//by human or by AI
		perform(game);
		//move snake
		//move();
		//sleep to wait slow human
		//wait();
}

//question 1: how to clear screen using ncurses?
int main(int argc, char *argv) {
	//parse cmdline arguments and print usage if necessary
	int type;
	Game game;
	type = parse(argc, argv);
	init(type, game);
	run(game);
}
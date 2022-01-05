#pragma once
#include <iostream>

using namespace std;

class game
{

protected:
	virtual void start() = 0;
	virtual bool have_winner() = 0;
	virtual void take_turn() = 0;
	virtual int get_winner() = 0;

	int current_player = 0;
	int number_of_players;
public:
	explicit game(int number_of_players_) : number_of_players(number_of_players_) {}

	void run()
	{
		start();
		while (!have_winner())
		{
			take_turn();
		}
		cout << "player " << get_winner() << "wins\n";
	}
};

class chess : public game
{
	int turns = 0;
	int max_turns = 10;

public:
	explicit chess() : game(2) {}
protected:
	void start() override {}
	bool have_winner() override
	{
		return turns == max_turns;
	}
	void take_turn() override
	{
		++turns;
		current_player = (current_player + 1) % number_of_players;
	}
	int get_winner() override
	{
		return current_player;
	}

};
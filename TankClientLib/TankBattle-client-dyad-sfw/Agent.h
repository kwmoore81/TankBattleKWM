#pragma once
#include "TankBattleHeaders.h"
#include "TankBattleNet.h"
#include "vec2.h"
#include <iostream>
#include "Solver.h"
#include "Grid.h"
#include "Graph.h"
#include "sfwdraw.h"


class Agent
{
	tankNet::TankBattleStateData current, previous;
	tankNet::TankBattleCommand tex;
	tankNet::TankTacticalInfo tack;
	tankNet::TankTacticalInfo eTack;

	vec2 lkPos;
	vec2 tPos;
	float enemyH;
	Grid map;
	enum cannonState
	{
		Scan, Aim, Fire, CStop
	};

	enum tankState
	{
		Forward, Right, Left, Reverse, Scout, TStop
	};

	float randTimer = 0;
	vec2 target;
	cannonState cCannon; // = Scan;
	tankState cTank;

	void scan();
	void aim();
	void fire();
	void cStop();
	void scout();
	void forward();
	void right();
	void left();
	void reverse();
	void tStop();
public:


	void SetCannonState(cannonState eCannon);
	void SetTankState(tankState eTank);

	cannonState GetCannonState();
	tankState GetTankState();

	tankNet::TankBattleCommand update(const tankNet::TankBattleStateData &state);

};


#pragma once
#include "TankBattleHeaders.h"
#include "TankBattleNet.h"
#include "vec2.h"


class Agent
{
	tankNet::TankBattleStateData current, previous;
	tankNet::TankBattleCommand tex;
	tankNet::TankTacticalInfo tack;
	tankNet::TankTacticalInfo eTack;

	vec2 lkPos;
	vec2 tPos;
	enum cannonState
	{
		Scan, Aim, Fire
	};

	enum tankState
	{
		Forward, Right, Left, Reverse
	};

	cannonState cCannon; // = Scan;
	tankState cTank;

	void scan();
	void aim();
	void fire();
	void forward();
	void right();
	void left();
	void reverse();
public:


	void SetCannonState(cannonState eCannon);
	void SetTankState(tankState eTank);

	cannonState GetCannonState();
	tankState GetTankState();

	tankNet::TankBattleCommand update(const tankNet::TankBattleStateData &state);

};


#pragma once
#include "TankBattleHeader.h"
#include "TankBattleHeaders.h"
#include "TankBattleNet.h"



class Agent
{
	tankNet::TankBattleStateData current, previous;

	enum cannonState
	{
		Scan, Aim, Fire
	};

	cannonState cCannon;
	
	void scan()
	{
		tankNet::CannonMovementOptions::RIGHT;
	}
	void aim();
	void fire();

public:

	void SetCannonState(cannonState eCannon);
	cannonState GetCannonState();
	
	tankNet::TankBattleCommand update(const tankNet::TankBattleStateData &state);

};


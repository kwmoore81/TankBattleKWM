#include "Agent.h"

void Agent::SetCannonState(cannonState eCannon)
{
	 
	cCannon = eCannon;
}

void Agent::SetTankState(tankState eTank)
{
	cTank = eTank;
}

void Agent::scan()
{
	if (tack.inSight != 0)
	{
		tex.cannonMove = tankNet::CannonMovementOptions::RIGHT;
	}

	else {
		SetTankState(Forward);
		SetCannonState(Fire);
	}
}

void Agent::aim()
{
	
}

void Agent::fire()
{
	if (tack.inSight != 0)
	{
		tex.fireWish = 1;
	}
}

void Agent::forward()
{
	if (tack.inSight != 0)
	{
		tex.tankMove = tankNet::TankMovementOptions::FWRD;
		SetCannonState(Fire);
		if (current.currentHealth < previous.currentHealth)
		{
			SetTankState(Reverse);
		}
	}
	
	else {
		tex.fireWish = 0;
		tex.tankMove = tankNet::TankMovementOptions::HALT;
		tex.cannonMove = tankNet::CannonMovementOptions::RIGHT;

		if (lkPos < tPos)
		{
			SetTankState(Reverse);
		}

		else
		{
			tex.tankMove = tankNet::TankMovementOptions::FWRD;
		}
	}
}

void Agent::right()
{
	tex.tankMove = tankNet::TankMovementOptions::RIGHT;
}

void Agent::left()
{
	tex.tankMove = tankNet::TankMovementOptions::LEFT;
}

void Agent::reverse()
{
	tex.tankMove = tankNet::TankMovementOptions::BACK;
}

tankNet::TankBattleCommand Agent::update(const tankNet::TankBattleStateData & state)
{

	if (state.tacticoolCount <= 0)
	{
		SetTankState(Forward);
		SetCannonState(Scan);
	}
	tack = state.tacticoolData[0];
	tPos.x = state.position[0];
	tPos.y = state.position[3];
	lkPos.x = tack.lastKnownPosition[0];
	lkPos.y = tack.lastKnownPosition[3];
	switch (cCannon)
	{
	case Scan: scan(); break;
	case Aim: aim(); break;
	case Fire: fire(); break;
	}

	switch (cTank)
	{
	case Forward: forward(); break;
	case Left: left(); break;
	case Right: right(); break;
	case Reverse: reverse(); break;
	}

	return tex;
}
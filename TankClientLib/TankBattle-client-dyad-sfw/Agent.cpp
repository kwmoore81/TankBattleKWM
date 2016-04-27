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
	vec2 tf = vec2::fromXZ(current.cannonForward);
	vec2 cp = vec2::fromXZ(current.position);

	tex.fireWish = 0;

	tex.cannonMove = tankNet::CannonMovementOptions::RIGHT;

	for (int aimTarget = 0; aimTarget < current.playerCount - 1; ++aimTarget)
	{ 
		if (current.tacticoolData[aimTarget].inSight && current.canFire)
		{
			target = vec2::fromXZ(current.tacticoolData[aimTarget].lastKnownPosition);

			if (dot(tf, normal(target - cp)) > .87f)
			{
				SetCannonState(Fire);
			}
			break;
		}
	}
	/*if (tack.inSight != 0)
	{
		tex.cannonMove = tankNet::CannonMovementOptions::RIGHT;
	}

	else {
		SetTankState(Forward);
		SetCannonState(Fire);
	}*/
}



void Agent::fire()
{
	vec2 canF = vec2::fromXZ(current.cannonForward);
	if (tack.inSight != 0)
	{
		if (dot(canF, lkPos) < .87f)
		{
			tex.fireWish = current.canFire;
		}
		else if (dot(perp(canF), lkPos) < 0)
		{
			tex.cannonMove = tankNet::CannonMovementOptions::RIGHT;
		}
		else 
		{
			tex.cannonMove = tankNet::CannonMovementOptions::LEFT;
		}
		
	}
	else
	{
		SetCannonState(Scan);
	}
}

void Agent::cStop()
{
	tex.cannonMove = tankNet::CannonMovementOptions::HALT;
	SetCannonState(Fire);
	if (tack.inSight == 0)
	{
		SetTankState(Scout);
		SetCannonState(Scan);
	}
}

std::list<vec2> path;

void Agent::scout()
{
	vec2 canF = vec2::fromXZ(current.cannonForward);
	vec2 cp = vec2::fromXZ(current.position);
	vec2 cf = vec2::fromXZ(current.forward);

	randTimer -= sfw::getDeltaTime();
	if (tack.inSight != 0)
	{
		target = lkPos;
		SetCannonState(Aim);
	}
	else if (/*distance(target, cp) < 20 ||*/ randTimer < 0)
	{
		target = vec2::random() * vec2 { 50, 50 };
		randTimer = rand() % 4 + 2;
	}

	vec2 tf = normal(target - cp);

	if (dot(cf, tf) > .87f)
	{
		tex.tankMove = tankNet::TankMovementOptions::FWRD;
	}
	
	else if (cf < target)
	{
		tex.tankMove = tankNet::TankMovementOptions::RIGHT;
		tex.cannonMove = tankNet::CannonMovementOptions::RIGHT;
	}
	else
	{
		tex.cannonMove = tankNet::CannonMovementOptions::LEFT;
		tex.tankMove = tankNet::TankMovementOptions::LEFT;
	}
}

void Agent::aim()
{
	vec2 cp = vec2::fromXZ(current.position);
	vec2 cf = vec2::fromXZ(current.forward);
	vec2 canF = vec2::fromXZ(current.cannonForward);
	if (tack.inSight != 0 && distance(target, cp) < 35)
	{
		SetTankState(TStop);
		SetCannonState(CStop);

		if (dot(canF, lkPos) > .86f)
		{
			tex.tankMove = tankNet::TankMovementOptions::RIGHT;
		}
		else
		{
			SetCannonState(Fire);
		}
		//canF = lkPos;
		//cf = lkPos;
		//SetTankState(Forward);
	}
	else
	{
		SetTankState(Scout);
	}
	if (current.currentHealth < previous.currentHealth)
	{
		SetTankState(Reverse);
	}
}

void Agent::forward()
{
	tex.tankMove = tankNet::TankMovementOptions::FWRD;
	if (tack.inSight != 0)
	{
		SetCannonState(Aim);
		
	}
	
	else {
		tex.fireWish = 0;
		tex.tankMove = tankNet::TankMovementOptions::HALT;
		tex.cannonMove = tankNet::CannonMovementOptions::RIGHT;
	     }
		if (current.currentHealth < previous.currentHealth)
		{
			SetTankState(Reverse);
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
	
	if (tack.inSight == 0)
	{
		SetTankState(Scout);
		SetCannonState(Scan);
	}

}

void Agent::tStop()
{
	vec2 cp = vec2::fromXZ(current.position);
	tex.tankMove = tankNet::TankMovementOptions::HALT;
	if (tack.inSight == 0 || distance(target, cp) > 35)
	{
		SetTankState(Scout);
		SetCannonState(Scan);
	}
}

tankNet::TankBattleCommand Agent::update(const tankNet::TankBattleStateData &state)
{

	if (state.tacticoolCount <= 0)
	{
		SetTankState(Scout);
		SetCannonState(Scan);
	}

	current = state;
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
	case CStop: cStop(); break;
	
	}

	switch (cTank)
	{
	case Scout: scout(); break;
	case Forward: forward(); break;
	case Left: left(); break;
	case Right: right(); break;
	case Reverse: reverse(); break;
	case TStop: tStop(); break;
	}

	return tex;
}
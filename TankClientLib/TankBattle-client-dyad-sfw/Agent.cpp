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
				cCannon = Fire;
				
			}
			break;
		}
	}
	
}

void Agent::fire()
{
	vec2 canF = vec2::fromXZ(current.cannonForward);
	vec2 tf = vec2::fromXZ(current.cannonForward);
	vec2 cp = vec2::fromXZ(current.position);
	
	tex.cannonMove = tankNet::CannonMovementOptions::HALT;
	cTank = TStop;
	tex.fireWish = current.canFire;
	
	
	
	if (tack.inSight == 0)
	{
		cCannon = Scan;
		cTank = Scout;
	}
	
		if (tack.inSight != 0)
		{
			
			if (dot(perp(cNormal), lkPosNorm) < .87)
			{

				tex.cannonMove = tankNet::CannonMovementOptions::RIGHT;
				tex.fireWish = current.canFire;			
		
			}
			else
			{
				tex.cannonMove = tankNet::CannonMovementOptions::LEFT;
				tex.fireWish = current.canFire;
			}
			
		}
		
}

void Agent::cRight()
{
	vec2 canF = vec2::fromXZ(current.cannonForward);
	tex.cannonMove = tankNet::CannonMovementOptions::RIGHT;

	if (dot(canF, lkPos) < .30f)
	{
		cCannon = CStop;
		tex.fireWish = current.canFire;
	}
	else if (tack.inSight == 0)
	{
		cCannon = Scan;
		cTank = Scout;
	}
}

void Agent::cLeft()
{
	vec2 canF = vec2::fromXZ(current.cannonForward);
	tex.cannonMove = tankNet::CannonMovementOptions::LEFT;

	if (dot(canF, lkPos) < .30f)
	{
		cCannon = CStop;
		tex.fireWish = current.canFire;
	}
	else if (tack.inSight == 0)
	{
		cCannon = Scan;
		cTank = Scout;
	}
}

void Agent::cStop()
{
	tex.cannonMove = tankNet::CannonMovementOptions::HALT;
	cCannon = Fire;
	if (tack.inSight == 0)
	{
		cCannon = Fire;
	}
	else
	{
		cTank = Scout;
	}
}

std::list<vec2> path;

void Agent::scout()
{
	vec2 canF = vec2::fromXZ(current.cannonForward);
	vec2 cp = vec2::fromXZ(current.position);
	vec2 cf = vec2::fromXZ(current.forward);

	randTimer -= sfw::getDeltaTime();

	if (randTimer < 0)
	{
		target = vec2::random() * vec2 { 50, 50 };
		randTimer = rand() % 4 + 2;
	}

	vec2 tf = normal(target - cp);

	if (dot(cf, tf) > .87f)
	{
		tex.tankMove = tankNet::TankMovementOptions::FWRD;

		if (current.position - previous.position < 20)
		{
			cTank = Reverse;
		}
		if (current.currentHealth < previous.currentHealth)
		{
			cTank = Reverse;
		}
		cTank = Scout;
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

	previous = current;
}

	void Agent::forward()
{
	tex.tankMove = tankNet::TankMovementOptions::FWRD;
	
	if (current.position - previous.position < 20)
	{
		cTank = Reverse;
	}
		if (current.currentHealth < previous.currentHealth)
		{
			cTank = Reverse;
		}
		cTank = Scout;
}

void Agent::right()
{
	tex.tankMove = tankNet::TankMovementOptions::RIGHT;
	
	cTank = Scout;
	
}

void Agent::left()
{
	tex.tankMove = tankNet::TankMovementOptions::LEFT;

	cTank = Scout;
}

void Agent::reverse()
{
	tex.tankMove = tankNet::TankMovementOptions::BACK;
	
	if (current.position - previous.position > 20)
	{
		tex.tankMove = tankNet::TankMovementOptions::BACK;
	}
	else
	{
		cTank = Scout;
		cCannon = Scan;
	}

}

void Agent::tStop()
{
	vec2 cp = vec2::fromXZ(current.position);
	tex.tankMove = tankNet::TankMovementOptions::HALT;
	if (tack.inSight == 0 || distance(target, cp) > 25)
	{
		cTank = Scout;
		cCannon = Scan;
	}
}

tankNet::TankBattleCommand Agent::update(const tankNet::TankBattleStateData &state)
{

	if (state.tacticoolCount <= 0)
	{
		cTank = Scout;
		cCannon = Scan;
	}
	cForward.x = state.cannonForward[0];
	cForward.y = state.cannonForward[3];
	cNormal = normal(cForward);

	current = state;
	tack = state.tacticoolData[0];
	tPos.x = state.position[0];
	tPos.y = state.position[3];
	
	lkPos.x = tack.lastKnownPosition[0];
	lkPos.y = tack.lastKnownPosition[3];
	lkPosNorm = normal(lkPos - tPos);

	 
	
	switch (cCannon)
	{
	case Scan: scan(); break;
	case Fire: fire(); break;
	case CRight: cRight(); break;
	case CLeft: cLeft(); break;
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
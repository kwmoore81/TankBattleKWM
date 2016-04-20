#include "Agent.h"

void Agent::SetCannonState(cannonState eCannon)
{
	 cCannon = eCannon;
}



tankNet::TankBattleCommand Agent::update(const tankNet::TankBattleStateData & state)
{
	SetCannonState(Scan);

	switch (cCannon)
	{
	case Scan: scan(); break;
	case Aim: aim(); break;
	case Fire: fire(); break;
	}

	return tankNet::TankBattleCommand();
}








/*
** MinGenerals(tm)
** Copyright 2025 CommunityRTS
**
** The above copyright notice applies to additions and/or other modifications
** made to this file by CommunityRTS.
**
** This file incorporates original work covered by the following copyright and
** permission notice:
**
**		Command & Conquer Generals(tm)
**		Command & Conquer Generals Zero Hour(tm)
**		Copyright 2025 Electronic Arts Inc.
**
**		This program is free software: you can redistribute it and/or modify
**		it under the terms of the GNU General Public License as published by
**		the Free Software Foundation, either version 3 of the License, or
**		(at your option) any later version.
**
**		This program is distributed in the hope that it will be useful,
**		but WITHOUT ANY WARRANTY; without even the implied warranty of
**		MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**		GNU General Public License for more details.
**
**		You should have received a copy of the GNU General Public License
**		along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

// FILE: BehaviorModule.h /////////////////////////////////////////////////////////////////////////////////
// Author: Steven Johnson
// Desc:	 
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef __BehaviorModule_H_
#define __BehaviorModule_H_

#include "Common/GameType.h"
#include "Common/Module.h"

//-------------------------------------------------------------------------------------------------
class Team;
class ThingTemplate;

//-------------------------------------------------------------------------------------------------
class BodyModuleInterface;
class CollideModuleInterface;
class ContainModuleInterface;
class CreateModuleInterface;
class DamageModuleInterface;
class DestroyModuleInterface;
class DieModuleInterface;
class SpecialPowerModuleInterface;
class UpdateModuleInterface;
class UpgradeModuleInterface;

//-------------------------------------------------------------------------------------------------
class ParkingPlaceBehaviorInterface;
class RebuildHoleBehaviorInterface;
class BridgeBehaviorInterface;
class BridgeTowerBehaviorInterface;
class BridgeScaffoldBehaviorInterface;
class OverchargeBehaviorInterface;
class TransportPassengerInterface;
class CaveInterface;
class LandMineInterface;

class ProjectileUpdateInterface;
class AIUpdateInterface;
class ExitInterface;
class DelayedUpgradeUpdateInterface;
class DockUpdateInterface;
class RailedTransportDockUpdateInterface;
class SpecialPowerUpdateInterface;
class SlavedUpdateInterface;
class SpawnBehaviorInterface;
class SlowDeathBehaviorInterface;
class PowerPlantUpdateInterface;
class ProductionUpdateInterface;
class HordeUpdateInterface;
class SpecialPowerTemplate;
class WeaponTemplate;
class DamageInfo;
class ParticleSystemTemplate;


//-------------------------------------------------------------------------------------------------
class BehaviorModuleData : public ModuleData
{
public:
	BehaviorModuleData()
	{
	}

	static void buildFieldParse(MultiIniFieldParse& p) 
	{
    ModuleData::buildFieldParse(p);
	}
};

//-------------------------------------------------------------------------------------------------
class BehaviorModuleInterface
{
public:

	virtual BodyModuleInterface* getBody() = 0;
	virtual CollideModuleInterface* getCollide() = 0;
	virtual ContainModuleInterface* getContain() = 0;
	virtual CreateModuleInterface* getCreate() = 0;
	virtual DamageModuleInterface* getDamage() = 0;
	virtual DestroyModuleInterface* getDestroy() = 0;
	virtual DieModuleInterface* getDie() = 0;
	virtual SpecialPowerModuleInterface* getSpecialPower() = 0;
	virtual UpdateModuleInterface* getUpdate() = 0;
	virtual UpgradeModuleInterface* getUpgrade() = 0;

	// interface acquisition
	virtual ParkingPlaceBehaviorInterface* getParkingPlaceBehaviorInterface() = 0;
	virtual RebuildHoleBehaviorInterface* getRebuildHoleBehaviorInterface() = 0;
	virtual BridgeBehaviorInterface* getBridgeBehaviorInterface() = 0;
	virtual BridgeTowerBehaviorInterface* getBridgeTowerBehaviorInterface() = 0;
	virtual BridgeScaffoldBehaviorInterface* getBridgeScaffoldBehaviorInterface() = 0;
	virtual OverchargeBehaviorInterface* getOverchargeBehaviorInterface() = 0;
	virtual TransportPassengerInterface* getTransportPassengerInterface() = 0;
	virtual CaveInterface* getCaveInterface() = 0;
	virtual LandMineInterface* getLandMineInterface() = 0;
	virtual DieModuleInterface* getEjectPilotDieInterface() = 0;
	// move from UpdateModuleInterface (srj)
	virtual ProjectileUpdateInterface* getProjectileUpdateInterface() = 0;
	virtual AIUpdateInterface* getAIUpdateInterface() = 0;
	virtual ExitInterface* getUpdateExitInterface() = 0;
	virtual DelayedUpgradeUpdateInterface* getDelayedUpgradeUpdateInterface() = 0;
	virtual DockUpdateInterface* getDockUpdateInterface() = 0;
	virtual RailedTransportDockUpdateInterface *getRailedTransportDockUpdateInterface( void ) = 0;
	virtual SlowDeathBehaviorInterface* getSlowDeathBehaviorInterface() = 0;
	virtual SpecialPowerUpdateInterface* getSpecialPowerUpdateInterface() = 0;
	virtual SlavedUpdateInterface* getSlavedUpdateInterface() = 0;
	virtual ProductionUpdateInterface* getProductionUpdateInterface() = 0;
	virtual HordeUpdateInterface* getHordeUpdateInterface() = 0;
	virtual PowerPlantUpdateInterface* getPowerPlantUpdateInterface() = 0;
	virtual SpawnBehaviorInterface* getSpawnBehaviorInterface() = 0;

};

//-------------------------------------------------------------------------------------------------
class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{

	MEMORY_POOL_GLUE_ABC( BehaviorModule )

public:

	BehaviorModule( Thing *thing, const ModuleData* moduleData );
	// virtual destructor prototype defined by MemoryPoolObject

	static Int getInterfaceMask() { return 0; }
	static ModuleType getModuleType() { return MODULETYPE_BEHAVIOR; }

	virtual BodyModuleInterface* getBody() { return NULL; }
	virtual CollideModuleInterface* getCollide() { return NULL; }
	virtual ContainModuleInterface* getContain() { return NULL; }
	virtual CreateModuleInterface* getCreate() { return NULL; }
	virtual DamageModuleInterface* getDamage() { return NULL; }
	virtual DestroyModuleInterface* getDestroy() { return NULL; }
	virtual DieModuleInterface* getDie() { return NULL; }
	virtual SpecialPowerModuleInterface* getSpecialPower() { return NULL; }
	virtual UpdateModuleInterface* getUpdate() { return NULL; }
	virtual UpgradeModuleInterface* getUpgrade() { return NULL; }

	virtual ParkingPlaceBehaviorInterface* getParkingPlaceBehaviorInterface() { return NULL; }
	virtual RebuildHoleBehaviorInterface* getRebuildHoleBehaviorInterface() { return NULL; }
	virtual BridgeBehaviorInterface* getBridgeBehaviorInterface() { return NULL; }
	virtual BridgeTowerBehaviorInterface* getBridgeTowerBehaviorInterface() { return NULL; }
	virtual BridgeScaffoldBehaviorInterface* getBridgeScaffoldBehaviorInterface() { return NULL; }
	virtual OverchargeBehaviorInterface* getOverchargeBehaviorInterface() { return NULL; }
	virtual TransportPassengerInterface* getTransportPassengerInterface() { return NULL; }
	virtual CaveInterface* getCaveInterface() { return NULL; }
	virtual LandMineInterface* getLandMineInterface() { return NULL; }
	virtual DieModuleInterface* getEjectPilotDieInterface() { return NULL; }
	// interface acquisition (moved from UpdateModule)
	virtual ProjectileUpdateInterface* getProjectileUpdateInterface() { return NULL; }
	virtual AIUpdateInterface* getAIUpdateInterface() { return NULL; }
	virtual ExitInterface* getUpdateExitInterface() { return NULL; }
	virtual DelayedUpgradeUpdateInterface* getDelayedUpgradeUpdateInterface() { return NULL; }
	virtual DockUpdateInterface* getDockUpdateInterface() { return NULL; }
	virtual RailedTransportDockUpdateInterface *getRailedTransportDockUpdateInterface( void ) { return NULL; }
	virtual SlowDeathBehaviorInterface* getSlowDeathBehaviorInterface() { return NULL; }
	virtual SpecialPowerUpdateInterface* getSpecialPowerUpdateInterface() { return NULL; }
	virtual SlavedUpdateInterface* getSlavedUpdateInterface() { return NULL; }
	virtual ProductionUpdateInterface* getProductionUpdateInterface() { return NULL; }
	virtual HordeUpdateInterface* getHordeUpdateInterface() { return NULL; }
	virtual PowerPlantUpdateInterface* getPowerPlantUpdateInterface() { return NULL; }
	virtual SpawnBehaviorInterface* getSpawnBehaviorInterface() { return NULL; }

protected:

	// snapshot methods
	virtual void crc( Xfer *xfer );
	virtual void xfer( Xfer *xfer );
	virtual void loadPostProcess( void );

};
inline BehaviorModule::BehaviorModule( Thing *thing, const ModuleData* moduleData ) : ObjectModule( thing, moduleData ) { }
inline BehaviorModule::~BehaviorModule() { }

//-------------------------------------------------------------------------------------------------
class ParkingPlaceBehaviorInterface
{
public:
	struct PPInfo
	{
		Coord3D		parkingSpace; 
		Real			parkingOrientation;
		Coord3D		runwayPrep; 
		Coord3D		runwayStart; 
		Coord3D		runwayEnd; 
		Coord3D		runwayApproach;
		Coord3D		hangarInternal;
		Real			hangarInternalOrient;
	};
	virtual Bool shouldReserveDoorWhenQueued(const ThingTemplate* thing) const = 0; 
	virtual Bool hasAvailableSpaceFor(const ThingTemplate* thing) const = 0; 
	virtual Bool hasReservedSpace(ObjectID id) const = 0; 
	virtual Bool reserveSpace(ObjectID id, Real parkingOffset, PPInfo* info) = 0;
	virtual void releaseSpace(ObjectID id) = 0; 
	virtual Bool reserveRunway(ObjectID id, Bool forLanding) = 0;
	virtual void releaseRunway(ObjectID id) = 0; 
	virtual Int getRunwayCount() const = 0;
	virtual ObjectID getRunwayReservation(Int r) = 0;
	virtual void transferRunwayReservationToNextInLineForTakeoff(ObjectID id) = 0;
	virtual Real getApproachHeight() const = 0;
	virtual void setHealee(Object* healee, Bool add) = 0;
	virtual void killAllParkedUnits() = 0;
	virtual void defectAllParkedUnits(Team* newTeam, UnsignedInt detectionTime) = 0;
};

//-------------------------------------------------------------------------------------------------
class TransportPassengerInterface
{
public:
	virtual Bool tryToEvacuate( Bool exposeStealthedUnits ) = 0; ///< Will try to kick everybody out with game checks, and will return whether anyone made it
};

//-------------------------------------------------------------------------------------------------
class CaveInterface
{
public:
	virtual void tryToSetCaveIndex( Int newIndex ) = 0;	///< Called by script as an alternative to instancing separate objects.  'Try', because can fail.
	virtual void setOriginalTeam( Team *oldTeam ) = 0;	///< This is a distributed Garrison in terms of capturing, so when one node triggers the change, he needs to tell everyone, so anyone can do the un-change.
};

//-------------------------------------------------------------------------------------------------
class LandMineInterface
{
public:
	virtual void setScootParms(const Coord3D& start, const Coord3D& end) = 0;
	virtual void disarm() = 0;
};

//-------------------------------------------------------------------------------------------------

#endif

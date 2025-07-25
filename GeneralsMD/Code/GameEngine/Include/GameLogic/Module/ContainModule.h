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

// FILE: ContainModule.h /////////////////////////////////////////////////////////////////////////////////
// Author: Colin Day, September 2001
// Desc:	 
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef __ContainModule_H_
#define __ContainModule_H_

#include "Common/Module.h"
#include "GameLogic/WeaponBonusConditionFlags.h" // Can't forward a typedef.  This should me made a BitFlags class.
#include "GameLogic/Damage.h"

//-------------------------------------------------------------------------------------------------
class OpenContain;
class Player;
class ExitInterface;
class Matrix3D;
class Weapon;
enum CommandSourceType;

//-------------------------------------------------------------------------------------------------
enum ObjectEnterExitType
{
	WANTS_TO_ENTER,
	WANTS_TO_EXIT,
	WANTS_NEITHER
};


enum EvacDisposition
{
  EVAC_INVALID = 0,
  EVAC_TO_LEFT,
  EVAC_TO_RIGHT,
  EVAC_BURST_FROM_CENTER,

};

//-------------------------------------------------------------------------------------------------

typedef std::list<Object*> ContainedItemsList;

//-------------------------------------------------------------------------------------------------
typedef ModuleData ContainModuleData;

//-------------------------------------------------------------------------------------------------

typedef void (*ContainIterateFunc)( Object *obj, void *userData );		///< callback type for contain iterate

//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
class ContainModuleInterface
{
public:
	
	// we have a two basic container types that it is convenient to query and use
	virtual OpenContain *asOpenContain() = 0;

	// our object changed position... react as appropriate.
	virtual void containReactToTransformChange() = 0;


	// containment is the basis for many complex systems, it helps us to have a formal
	// place where we can monitor the outside world if we need to

	//===============================================================================================
	// Containment ==================================================================================
	//===============================================================================================

	virtual Bool isGarrisonable() const = 0;
	virtual Bool isBustable() const = 0;
	virtual Bool isSpecialZeroSlotContainer() const = 0;
	virtual Bool isHealContain() const = 0;
	virtual Bool isTunnelContain() const = 0;
	virtual Bool isRiderChangeContain() const = 0;
	virtual Bool isImmuneToClearBuildingAttacks() const = 0;
  virtual Bool isSpecialOverlordStyleContainer() const = 0;
  virtual Bool isAnyRiderAttacking() const = 0;
	
	///< if my object gets selected, then my visible passengers should, too
	///< this gets called from
	virtual void clientVisibleContainedFlashAsSelected() = 0; 



	/**
		this is used for containers that must do something to allow people to enter or exit...
		eg, land (for Chinook), open door (whatever)... it's called with wants=WANTS_TO_ENTER
		when something is in the enter state, and wants=ENTS_NOTHING when the unit has
		either entered, or given up...
	*/
	virtual void onObjectWantsToEnterOrExit(Object* obj, ObjectEnterExitType wants) = 0;

	// returns true iff there are objects currently waiting to enter.
	virtual Bool hasObjectsWantingToEnterOrExit() const = 0;

	/**
		return the player that *appears* to control this unit, given an observing player.
		if null, use getObject()->getControllingPlayer() instead.
	*/
	virtual const Player* getApparentControllingPlayer(const Player* observingPlayer) const = 0;

	virtual void recalcApparentControllingPlayer() = 0;
 
	//
	// you will want to override onContaining() and onRemoving() if you need to
	// do special actions at those event times for your module
	//
	virtual void onContaining( Object *obj, Bool wasSelected ) = 0;		///< object now contains 'obj'
	virtual void onRemoving( Object *obj ) = 0;			///< object no longer contains 'obj'
	virtual void onCapture( Player *oldOwner, Player *newOwner ) = 0; // Very important to handle capture of container, don't want to differ in teams from passenger to us.
	virtual void onSelling() = 0;///< Container is being sold.  Most people respond by kicking everyone out, but not all.

	virtual Int getContainMax() const = 0; ///< The max needs to be virtual, but only two inheritors care.  -1 means "I don't care".

	virtual ExitInterface* getContainExitInterface() = 0;
	
	virtual void orderAllPassengersToExit( CommandSourceType, Bool instantly ) = 0; ///< All of the smarts of exiting are in the passenger's AIExit. removeAllFrommContain is a last ditch system call, this is the game Evacuate
	virtual void orderAllPassengersToIdle( CommandSourceType ) = 0; ///< Just like it sounds
	virtual void orderAllPassengersToHackInternet( CommandSourceType ) = 0; ///< Just like it sounds
	virtual void markAllPassengersDetected() = 0;										///< Cool game stuff got added to the system calls since this layer didn't exist, so this regains that functionality
 
	//
	// interface for containing objects inside of objects.  Objects that are
	// contained remove their drawable representations entirely from the client
	//
	/** 
		can this container contain this kind of object? 
		and, if checkCapacity is TRUE, does this container have enough space left to hold the given unit?
	*/
	virtual Bool isValidContainerFor(const Object* obj, Bool checkCapacity) const = 0;
	virtual void addToContain( Object *obj ) = 0;						///< add 'obj' to contain list
	virtual void addToContainList( Object *obj ) = 0;		///< The part of AddToContain that inheritors can override (Can't do whole thing because of all the private stuff involved)
	virtual void removeFromContain( Object *obj, Bool exposeStealthUnits = FALSE ) = 0;			///< remove 'obj' from contain list
	virtual void removeAllContained( Bool exposeStealthUnits = FALSE ) = 0;									///< remove all objects on contain list
	virtual void killAllContained( void ) = 0;									///< kill all objects on contain list
  virtual void harmAndForceExitAllContained( DamageInfo *info ) = 0; // apply canned damage against those containes 
	virtual Bool isEnclosingContainerFor( const Object *obj ) const = 0;	///< Does this type of Contain Visibly enclose its contents?
	virtual Bool isPassengerAllowedToFire( ObjectID id = INVALID_ID ) const = 0;	///< Hey, can I shoot out of this container?
	virtual void setPassengerAllowedToFire( Bool permission = TRUE ) = 0;	///< Hey, can I shoot out of this container?
	virtual void setOverrideDestination( const Coord3D * ) = 0; ///< Instead of falling peacefully towards a clear spot, I will now aim here
	virtual Bool isDisplayedOnControlBar() const = 0;///< Does this container display its contents on the ControlBar?
	virtual Int getExtraSlotsInUse( void ) = 0;
	virtual Bool isKickOutOnCapture() = 0;///< Does this contain module kick people out when captured?

	// list access
	virtual void iterateContained( ContainIterateFunc func, void *userData, Bool reverse ) = 0;		///< iterate the contain list
	virtual UnsignedInt getContainCount() const = 0;											///< contained count
	virtual const ContainedItemsList* getContainedItemsList() const = 0;
	virtual const Object *friend_getRider() const = 0; ///< Damn.  The draw order dependency bug for riders means that our draw module needs to cheat to get around it.
	virtual Real getContainedItemsMass() const = 0;
	virtual UnsignedInt getStealthUnitsContained() const = 0;
	
	virtual Bool calcBestGarrisonPosition( Coord3D *sourcePos, const Coord3D *targetPos ) = 0;
	virtual Bool attemptBestFirePointPosition( Object *source, Weapon *weapon, Object *victim ) = 0;
	virtual Bool attemptBestFirePointPosition( Object *source, Weapon *weapon, const Coord3D *targetPos ) = 0;

	// Player Occupancy.
	virtual PlayerMaskType getPlayerWhoEntered(void) const = 0;

	virtual void processDamageToContained(Real percentDamage) = 0; ///< Do our % damage to units now.
  virtual Object* getClosestRider ( const Coord3D *pos ) = 0;

	virtual void enableLoadSounds( Bool enable ) = 0;

  virtual void setEvacDisposition( EvacDisposition disp ) = 0;

	virtual Bool isWeaponBonusPassedToPassengers() const = 0;
	virtual WeaponBonusConditionFlags getWeaponBonusPassedToPassengers() const = 0;


	// this exists really just so someone can override it to prevent pip showings...
	virtual Bool getContainerPipsToShow(Int& numTotal, Int& numFull)
	{
		numTotal = getContainMax();
		numFull = getContainCount() + getExtraSlotsInUse();
// srj sez: this makes the pips display in the same manner as the inventory control bar...
//		numTotal = getContainMax() - getExtraSlotsInUse();
//		numFull = getContainCount();

		return true;
	}
};
//-------------------------------------------------------------------------------------------------

#endif

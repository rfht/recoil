/* This file is part of the Spring engine (GPL v2 or later), see LICENSE.html */

#ifndef GROUNDBLOCKINGOBJECTMAP_H
#define GROUNDBLOCKINGOBJECTMAP_H

#include <map>

#include "System/creg/creg_cond.h"
#include "System/float3.h"


class CSolidObject;
typedef std::map<int, CSolidObject*> BlockingMapCell;
typedef BlockingMapCell::const_iterator BlockingMapCellIt;
typedef std::vector<BlockingMapCell> BlockingMap;


class CGroundBlockingObjectMap
{
	CR_DECLARE(CGroundBlockingObjectMap);

public:
	CGroundBlockingObjectMap(int numSquares) {
		groundBlockingMap.resize(numSquares);
	}

	void AddGroundBlockingObject(CSolidObject* object);
	void AddGroundBlockingObject(CSolidObject* object, const unsigned char* yardMap, unsigned char mask);
	void RemoveGroundBlockingObject(CSolidObject* object);

	void OpenBlockingYard(CSolidObject* yard, const unsigned char* yardMap);
	void CloseBlockingYard(CSolidObject* yard, const unsigned char* yardMap);
	bool CanCloseYard(CSolidObject* object);

	// these retrieve either the top-most or the bottom-most
	// object in a given cell, or NULL if the cell is empty
	CSolidObject* GroundBlocked(int x, int z) const;
	CSolidObject* GroundBlocked(const float3& pos) const;

	// same as GroundBlocked(), but does not bounds-check mapSquare
	CSolidObject* GroundBlockedUnsafe(int mapSquare) const;

	bool GroundBlocked(int x, int z, CSolidObject* ignoreObj) const;
	bool GroundBlocked(const float3& pos, CSolidObject* ignoreObj) const;

	// for full thread safety, access via GetCell would need to be mutexed, but it appears only sim thread uses it
	const BlockingMapCell& GetCell(int mapSquare) const {
		return groundBlockingMap[mapSquare];
	}

private:
	BlockingMap groundBlockingMap;
};

extern CGroundBlockingObjectMap* groundBlockingObjectMap;

#endif

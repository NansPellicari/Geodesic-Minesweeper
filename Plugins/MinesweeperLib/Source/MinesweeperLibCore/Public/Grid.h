#pragma once

#include "CoreMinimal.h"

struct MINESWEEPERLIBCORE_API FGridSlot
{
	FGridSlot() {}

	FGridSlot(bool bInIsBomb, int32 InAsideBombsNumber)
		: bIsBomb(bInIsBomb), AsideBombsNumber(InAsideBombsNumber) {}

	bool bIsBomb = false;
	bool bIsFound = false;
	int32 Position = 0;
	int32 AsideBombsNumber = 0;
};

struct MINESWEEPERLIBCORE_API FGridData
{
	FGridData() {}
	FGridData(int32 InRows, int32 InColumns) : Rows(InRows), Columns(InColumns) {}

	int32 Rows = 4;
	int32 Columns = 4;
	/** This will be automatically computed by NGrid::Build(). */
	int32 BombsAmount = -1;
	TArray<TArray<FGridSlot>> Data;
	int32 Num() const;
	FGridSlot& GetSlot(int32 Row, int32 Column);
	void GetColAndRowFromPosition(const int32 Position, int32& Col, int32& Row) const;
	FGridSlot& GetSlot(int32 Position);
	FGridSlot GetSlot(int32 Position) const;
	void AddSlot(int32 Row, FGridSlot Slot);
	void SlotFoundAt(uint32 Position);
	bool IsInValidRange(const int32& Row, const int32& Col) const;
	int32 GetSlotIndex(const int32& Row, const int32& Col) const;
};

/**
 * 
 */
class MINESWEEPERLIBCORE_API NGrid
{
public:
	NGrid() {}
	static void Build(FGridData& Grid, int32 BombsAmount = -1);
};

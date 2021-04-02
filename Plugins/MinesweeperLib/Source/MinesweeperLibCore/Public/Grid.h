#pragma once

#include "CoreMinimal.h"

struct MINESWEEPERLIBCORE_API FGridSlot
{
	FGridSlot() {}

	FGridSlot(bool bInIsBomb, int32 InAsideBombsNumber)
		: bIsBomb(bInIsBomb), AsideBombsNumber(InAsideBombsNumber) {}

	bool bIsBomb = false;
	int32 AsideBombsNumber = 0;
};

struct MINESWEEPERLIBCORE_API FGridData
{
	FGridData(int32 InRows, int32 InColumns) : Rows(InRows), Columns(InColumns) {}

	int32 Rows = 4;
	int32 Columns = 4;
	/**
	 * This will be automatically computed by NGrid::Build() if its value stick to -1.
	 * You can change the value here if you want to override it.
	 */
	int32 BombsAmount = -1;
	TArray<TArray<FGridSlot>> Data;
	int32 Num();
	FGridSlot GetSlot(int32 Row, int32 Column);
	FGridSlot GetSlot(int32 Position);
	void AddSlot(int32 Row, FGridSlot Slot);
};

/**
 * 
 */
class MINESWEEPERLIBCORE_API NGrid
{
public:
	NGrid() {}
	static void Build(FGridData& Grid);
	static bool IsInValidRange(const FGridData& Grid, const int32& Row, const int32& Col);
	static int32 GetSlotIndex(const FGridData& Grid, const int32& Row, const int32& Col);
};

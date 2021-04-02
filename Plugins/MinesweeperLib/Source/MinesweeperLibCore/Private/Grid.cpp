#include "MinesweeperLibCore/Public/Grid.h"

#include <iostream>

#include "Misc/NansAssertionMacros.h"

int32 FGridData::Num()
{
	return Columns * Rows;
}

FGridSlot FGridData::GetSlot(int32 Row, int32 Column)
{
	mycheck(Data.IsValidIndex(Row));
	mycheck(Data[Row].IsValidIndex(Column));
	return Data[Row][Column];
}

FGridSlot FGridData::GetSlot(int32 Position)
{
	mycheck(Position < Num());
	const int32 Col = Position % Columns;
	const int32 Row = FMath::Floor<int32>(Position / Columns);

	std::cout << "Row " << Row << " \n";

	mycheck(Data.IsValidIndex(Row));
	mycheck(Data[Row].IsValidIndex(Col));

	return Data[Row][Col];
}

void FGridData::AddSlot(int32 Row, FGridSlot Slot)
{
	// TODO should check if the Row is the next array increment
	if (!Data.IsValidIndex(Row))
	{
		Data.Add(TArray<FGridSlot>());
	}

	mycheck(Data[Row].Num() < Columns);

	Data[Row].Add(Slot);
}

void NGrid::Build(FGridData& Grid, int32 BombsAmount)
{
	Grid.Data.Empty();
	TArray<int32> Bombs;
	const int32 MaxCells = Grid.Num();

	BombsAmount = BombsAmount == -1 ? MaxCells / 6.4f : BombsAmount;
	BombsAmount = FMath::Max<int32>(BombsAmount, 1);
	Grid.BombsAmount = BombsAmount;

	// Create bombs positions
	for (int32 BombIndex = 0; BombIndex < BombsAmount; ++BombIndex)
	{
		bool bIsSaved = false;
		while (bIsSaved == false)
		{
			int32 BombPos = FMath::RandRange(0, MaxCells);

			if (!Bombs.Contains(BombPos))
			{
				Bombs.Add(BombPos);
				bIsSaved = true;
			}
		}
	}

	// Create Grid data
	int32 CellPosition = 0;
	for (int32 Row = 0; Row < Grid.Rows; ++Row)
	{
		for (int32 Col = 0; Col < Grid.Columns; ++Col)
		{
			FGridSlot Slot;
			if (Bombs.Contains(CellPosition))
			{
				Slot.bIsBomb = true;
			}
			else
			{
				for (int32 Matrix = 0; Matrix < 9; ++Matrix)
				{
					const int32 MatrixRow = Matrix % 3;
					const int32 MatrixCol = FMath::Floor<int32>(Matrix / 3);
					int32 GridRow = MatrixRow == 0 ? Row - 1 : MatrixRow == 2 ? Row + 1 : Row;
					int32 GridCol = MatrixCol == 0 ? Col - 1 : MatrixCol == 2 ? Col + 1 : Col;
					const int32 AsideSlotNumber = IsInValidRange(Grid, GridRow, GridCol)
													  ? GetSlotIndex(Grid, GridRow, GridCol)
													  : -1;
					if (AsideSlotNumber >= 0 && Bombs.Contains(AsideSlotNumber))
					{
						Slot.AsideBombsNumber++;
					}
				}
			}

			Grid.AddSlot(Row, Slot);

			CellPosition++;
		}
	}
}

bool NGrid::IsInValidRange(const FGridData& Grid, const int32& Row, const int32& Col)
{
	return Row >= 0 && Row < Grid.Rows && Col >= 0 && Col < Grid.Columns;
}

int32 NGrid::GetSlotIndex(const FGridData& Grid, const int32& Row, const int32& Col)
{
	const int32 Idx = (Row) * Grid.Columns + Col;
	return Idx;
}

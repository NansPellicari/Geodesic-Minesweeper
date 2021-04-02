#include "MinesweeperLibCore/Public/Grid.h"

#include "Misc/NansAssertionMacros.h"

int32 FGridData::Num() const
{
	return Columns * Rows;
}

FGridSlot& FGridData::GetSlot(int32 Row, int32 Column)
{
	mycheck(Data.IsValidIndex(Row));
	mycheck(Data[Row].IsValidIndex(Column));

	return Data[Row][Column];
}

void FGridData::GetColAndRowFromPosition(const int32 Position, int32& Col, int32& Row) const
{
	Col = Position % Columns;
	Row = FMath::Floor<int32>(Position / Columns);

	mycheck(Data.IsValidIndex(Row));
	mycheck(Data[Row].IsValidIndex(Col));
}

FGridSlot& FGridData::GetSlot(int32 Position)
{
	mycheck(Position < Num() && Position >= 0);

	int32 Col;
	int32 Row;
	GetColAndRowFromPosition(Position, Col, Row);

	return Data[Row][Col];
}

FGridSlot FGridData::GetSlot(int32 Position) const
{
	mycheck(Position < Num());

	int32 Col;
	int32 Row;
	GetColAndRowFromPosition(Position, Col, Row);

	return Data[Row][Col];
}

void FGridData::AddSlot(int32 Row, FGridSlot Slot)
{
	mycheck(Row < Rows);

	if (!Data.IsValidIndex(Row))
	{
		Data.Add(TArray<FGridSlot>());
	}

	mycheck(Data[Row].Num() < Columns);

	Data[Row].Add(Slot);
}

bool FGridData::IsInValidRange(const int32& Row, const int32& Col) const
{
	return Row >= 0 && Row < Rows && Col >= 0 && Col < Columns;
}

int32 FGridData::GetSlotIndex(const int32& Row, const int32& Col) const
{
	const int32 Idx = (Row) * Columns + Col;
	return Idx;
}


void FGridData::SlotFoundAt(uint32 Position)
{
	int32 Col;
	int32 Row;
	GetColAndRowFromPosition(Position, Col, Row);
	FGridSlot& Slot = GetSlot(Row, Col);

	if (Slot.bIsBomb) return;

	Slot.bIsFound = true;

	const bool bIsEmpty = Slot.AsideBombsNumber == 0;
	if (!bIsEmpty) return;

	TArray<FVector2D> CrossGrid = {
		FVector2D(Row - 1, Col),
		FVector2D(Row, Col - 1),
		FVector2D(Row, Col + 1),
		FVector2D(Row + 1, Col),
	};

	for (int32 Neighbour = 0; Neighbour < 4; ++Neighbour)
	{
		int32 GridRow = CrossGrid[Neighbour].X;
		int32 GridCol = CrossGrid[Neighbour].Y;
		const int32 AsideSlotNumber = IsInValidRange(GridRow, GridCol)
										  ? GetSlotIndex(GridRow, GridCol)
										  : -1;
		if (AsideSlotNumber > -1)
		{
			FGridSlot& AsideSlot = GetSlot(GridRow, GridCol);
			if (AsideSlot.bIsBomb) continue;

			if (!AsideSlot.bIsFound)
			{
				AsideSlot.bIsFound = true;
				SlotFoundAt(AsideSlotNumber);
			}
		}
	}
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
	int32 SlotPosition = 0;
	for (int32 Row = 0; Row < Grid.Rows; ++Row)
	{
		for (int32 Col = 0; Col < Grid.Columns; ++Col)
		{
			FGridSlot Slot;
			Slot.Position = SlotPosition;
			if (Bombs.Contains(SlotPosition))
			{
				Slot.bIsBomb = true;
			}
			else
			{
				for (int32 Neighbour = 0; Neighbour < 9; ++Neighbour)
				{
					const int32 NeighbourRow = Neighbour % 3;
					const int32 NeighbourCol = FMath::Floor<int32>(Neighbour / 3);
					int32 GridRow = NeighbourRow == 0 ? Row - 1 : NeighbourRow == 2 ? Row + 1 : Row;
					int32 GridCol = NeighbourCol == 0 ? Col - 1 : NeighbourCol == 2 ? Col + 1 : Col;
					const int32 AsideSlotNumber = Grid.IsInValidRange(GridRow, GridCol)
													  ? Grid.GetSlotIndex(GridRow, GridCol)
													  : -1;
					if (AsideSlotNumber >= 0 && Bombs.Contains(AsideSlotNumber))
					{
						Slot.AsideBombsNumber++;
					}
				}
			}

			Grid.AddSlot(Row, Slot);

			SlotPosition++;
		}
	}
}

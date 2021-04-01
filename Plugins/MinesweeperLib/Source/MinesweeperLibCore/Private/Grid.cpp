#include "MinesweeperLibCore/Public/Grid.h"

#include <iostream>

void NGrid::Build()
{
	GridData.Empty();
	TArray<int32> Bombs;
	const int32 MaxCells = Width * Height;

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


	for (int32 H = 0; H < Height; ++H)
	{
		if (!GridData.IsValidIndex(H))
		{
			GridData.Add(TArray<int32>());
		}
		std::cout << "row: " << H << "\n";
		for (int32 W = 0; W < Width; ++W)
		{
			const int32 CellPosition = H * Width + W;
			
			GridData[H].Add(0);
			std::cout << "column: " << W << " at position: " << CellPosition << "\n";
		}
	}
}

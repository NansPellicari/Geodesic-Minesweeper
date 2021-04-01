#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class NGrid
{
public:
	NGrid(int32 InWidth, int32 InHeight, int32 InBombsAmount) : Width(InWidth), Height(InHeight),
																BombsAmount(InBombsAmount) {}

	void Build();

private:
	int32 Width;
	int32 Height;
	int32 BombsAmount;

	TArray<TArray<int32>> GridData;
};

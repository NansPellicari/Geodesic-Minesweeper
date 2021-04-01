#include "CoreMinimal.h"
#include "IMinesweeperLibCore.h"
#include "Modules/ModuleManager.h"


class FMinesweeperLibCore : public IMinesweeperLibCore
{
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

IMPLEMENT_MODULE(FMinesweeperLibCore, MinesweeperLibCore)


void FMinesweeperLibCore::StartupModule() { }


void FMinesweeperLibCore::ShutdownModule() {}

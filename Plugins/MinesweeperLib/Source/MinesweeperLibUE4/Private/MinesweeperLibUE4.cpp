#include "CoreMinimal.h"
#include "IMinesweeperLibUE4.h"
#include "Modules/ModuleManager.h"


class FMinesweeperLibUE4 : public IMinesweeperLibUE4
{
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

IMPLEMENT_MODULE(FMinesweeperLibUE4, MinesweeperLibUE4)


void FMinesweeperLibUE4::StartupModule()
{
	// This code will execute after your module is loaded into memory (but after global variables are initialized, of course.)
}


void FMinesweeperLibUE4::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

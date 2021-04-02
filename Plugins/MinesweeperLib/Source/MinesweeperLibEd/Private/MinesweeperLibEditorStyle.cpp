#include "MinesweeperLibEditorStyle.h"

#include "EditorStyleSet.h"
#include "Framework/Application/SlateApplication.h"
#include "Interfaces/IPluginManager.h"
#include "Slate/SlateGameResources.h"
#include "Styling/CoreStyle.h"
#include "Styling/SlateStyleRegistry.h"

TSharedPtr<FSlateStyleSet> FMinesweeperLibEditorStyle::MinesweeperLibEditorStyleInstance = nullptr;

void FMinesweeperLibEditorStyle::Initialize()
{
	if (!MinesweeperLibEditorStyleInstance.IsValid())
	{
		MinesweeperLibEditorStyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*MinesweeperLibEditorStyleInstance);
	}
}

void FMinesweeperLibEditorStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*MinesweeperLibEditorStyleInstance);
	ensure(MinesweeperLibEditorStyleInstance.IsUnique());
	MinesweeperLibEditorStyleInstance.Reset();
}

FName FMinesweeperLibEditorStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("MinesweeperLibEditorStyle"));
	return StyleSetName;
}

FString RelativePathToPluginPath(const FString& RelativePath, const ANSICHAR* Extension)
{
	static FString ContentDir = IPluginManager::Get().FindPlugin(TEXT("MinesweeperLib"))->GetContentDir();
	return (ContentDir / RelativePath) + Extension;
}

#define IMAGE_BRUSH( RelativePath, ... ) FSlateImageBrush( Style->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )

const FVector2D Icon20x20(20.0f, 20.0f);
const FVector2D Icon40x40(40.0f, 40.0f);

TSharedRef<FSlateStyleSet> FMinesweeperLibEditorStyle::Create()
{
	TSharedRef<FSlateStyleSet> Style = MakeShareable(new FSlateStyleSet("MinesweeperLibEditorStyle"));

	TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(TEXT("MinesweeperLib"));
	if (Plugin.IsValid())
	{
		Style->SetContentRoot(FPaths::Combine(Plugin->GetBaseDir(), TEXT("Resources")));
	}

	// Toolbar Icons
	Style->Set(
		"MinesweeperLibEditor.Play",
		new IMAGE_BRUSH("Icons/icon_MinesweeperLibEditor_PlayMineSweeper_40x", Icon40x40)
	);
	Style->Set(
		"MinesweeperLibEditor.Play.Small",
		new IMAGE_BRUSH("Icons/icon_MinesweeperLibEditor_PlayMineSweeper_40x", Icon20x20)
	);


	return Style;
}

#undef IMAGE_BRUSH


void FMinesweeperLibEditorStyle::ReloadTextures()
{
	FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
}

const ISlateStyle& FMinesweeperLibEditorStyle::Get()
{
	return *MinesweeperLibEditorStyleInstance;
}

#include "CoreMinimal.h"
#include "IMinesweeperLibEd.h"
#include "LevelEditor.h"
#include "MinesweeperCommands.h"
#include "MinesweeperLibEditorStyle.h"
#include "Framework/MultiBox/MultiBoxExtender.h"
#include "Interfaces/IMainFrameModule.h"
#include "Modules/ModuleManager.h"
#include "UI/SMineSweeperWindow.h"

class FMinesweeperLibEd : public IMinesweeperLibEd
{
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	TSharedPtr<FExtender> ToolbarExtender;
	TSharedPtr<const FExtensionBase> Extension;

	void MyButton_Clicked();
	void AddToolbarExtension(FToolBarBuilder& Builder) const;
};

IMPLEMENT_MODULE(FMinesweeperLibEd, MinesweeperLibEd)


void FMinesweeperLibEd::StartupModule()
{
	// Initialize editor style for Minesweeper
	FMinesweeperLibEditorStyle::Initialize();

	FMinesweeperCommands::Register();
	TSharedPtr<FUICommandList> CommandList = MakeShareable(new FUICommandList());

	CommandList->MapAction(
		FMinesweeperCommands::Get().MyButton,
		FExecuteAction::CreateRaw(this, &FMinesweeperLibEd::MyButton_Clicked),
		FCanExecuteAction()
	);

	ToolbarExtender = MakeShareable(new FExtender());

	Extension = ToolbarExtender->AddToolBarExtension(
		"Game",
		EExtensionHook::First,
		CommandList,
		FToolBarExtensionDelegate::CreateRaw(this, &FMinesweeperLibEd::AddToolbarExtension)
	);

	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>(
		FName(TEXT("LevelEditor"))
	);
	LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
}


void FMinesweeperLibEd::ShutdownModule()
{
	ToolbarExtender->RemoveExtension(Extension.ToSharedRef());
	Extension.Reset();
	ToolbarExtender.Reset();
	FMinesweeperLibEditorStyle::Shutdown();
}

void FMinesweeperLibEd::MyButton_Clicked()
{
	const TSharedRef<SWindow> MineSweeperWindow = SNew(SWindow)
		.Title(FText::FromString(TEXT("MineSweeper Window")))
		.ClientSize(FVector2D(850, 850))
		.SupportsMaximize(false)
		.SupportsMinimize(false);

	MineSweeperWindow->SetContent(
		SNew(SMineSweeperWindow)
	);

	IMainFrameModule& MainFrameModule = FModuleManager::LoadModuleChecked<IMainFrameModule>(TEXT("MainFrame"));

	if (MainFrameModule.GetParentWindow().IsValid())
	{
		FSlateApplication::Get().AddWindowAsNativeChild(
			MineSweeperWindow,
			MainFrameModule.GetParentWindow().ToSharedRef()
		);
	}
	else
	{
		FSlateApplication::Get().AddWindow(MineSweeperWindow);
	}
}

void FMinesweeperLibEd::AddToolbarExtension(FToolBarBuilder& Builder) const
{
	const FSlateIcon IconBrush = FSlateIcon(
		FMinesweeperLibEditorStyle::GetStyleSetName(),
		"MinesweeperLibEditor.Play",
		"MinesweeperLibEditor.Play.Small"
	);
	Builder.AddToolBarButton(
		FMinesweeperCommands::Get().MyButton,
		NAME_None,
		FText::FromString("MineSweeper"),
		FText::FromString("Launch the Minesweeper game"),
		IconBrush,
		NAME_None
	);
}

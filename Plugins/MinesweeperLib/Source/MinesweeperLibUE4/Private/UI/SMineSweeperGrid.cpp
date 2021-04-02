#include "UI/SMineSweeperGrid.h"

#include "EditorFontGlyphs.h"
#include "EditorStyleSet.h"
#include "Grid.h"
#include "SlateOptMacros.h"

#define LOCTEXT_NAMESPACE "MinesweeperUE4"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SMineSweeperGrid::Construct(const FArguments& InArgs)
{
	TMap<EGameStatus, FText> GameOverTexts = {
		{EGameStatus::Fail, LOCTEXT("GameOverFailedText", "Oooh you've exploded...")},
		{EGameStatus::Success, LOCTEXT("GameOverSuccessText", "Congratulations!!! The grid is safe!")},
	};

	TMap<EGameStatus, FText> GameOverIcons = {
		{EGameStatus::Fail, FEditorFontGlyphs::Frown_O},
		{EGameStatus::Success, FEditorFontGlyphs::Smile_O},
	};

	TMap<EGameStatus, FLinearColor> GameOverColors = {
		{EGameStatus::Fail, FLinearColor::Red},
		{EGameStatus::Success, FLinearColor::Green},
	};

	ChildSlot
	[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		  .HAlign(HAlign_Center).VAlign(VAlign_Top).AutoHeight()
		  .Padding(0.f, 10.f)
		[
			SNew(SBorder)
			.BorderImage(FEditorStyle::GetBrush("Graph.StateNode.Body"))
			.BorderBackgroundColor(FLinearColor::White)
			.ForegroundColor(FLinearColor::Black)
			.Padding(10.f)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				  .HAlign(HAlign_Center).VAlign(VAlign_Center).AutoWidth()
				  .Padding(5.f, 0.f)
				[
					SNew(STextBlock)
				.Font(FEditorStyle::Get().GetFontStyle("NormalFont"))
				.Text_Lambda(
										[this]()
										{
											return FText::Format(
												LOCTEXT("BombsNumberLabel", "Bombs: {0}"),
												GridData.BombsAmount
											);
										}
									)
				]
				+ SHorizontalBox::Slot()
				  .HAlign(HAlign_Center).VAlign(VAlign_Top).AutoWidth()
				[
					SNew(SButton)
				  .Text(LOCTEXT("ReplayLabel", "Replay"))
				  .ForegroundColor(FLinearColor::Black)
				  .ButtonColorAndOpacity(FLinearColor::Green)
				  .OnClicked(this, &SMineSweeperGrid::OnReplayClicked)
				]
				+ SHorizontalBox::Slot()
				  .HAlign(HAlign_Center).VAlign(VAlign_Top).AutoWidth()
				[
					SNew(SButton)
				  .Text(LOCTEXT("CheatModeLabel", "Cheat Mode"))
				  .ForegroundColor(FLinearColor::Black)
				  .ButtonColorAndOpacity_Lambda(
									 [this]() { return !bCheatMode ? FLinearColor::Gray : FLinearColor::Yellow; }
								 )
				  .OnClicked(this, &SMineSweeperGrid::OnCheatModeClicked)
				]
			]

		]
		+ SVerticalBox::Slot()
		  .HAlign(HAlign_Center).VAlign(VAlign_Top).AutoHeight()
		[
			SNew(SScrollBox)
			.Orientation(Orient_Horizontal)
			+ SScrollBox::Slot()
			[
				SAssignNew(Grid, SUniformGridPanel)
				  .SlotPadding(0.5f)
				  .MinDesiredSlotHeight(5.f)
				  .MinDesiredSlotWidth(5.f)
			]
		]
		+ SVerticalBox::Slot()
		  .HAlign(HAlign_Center).VAlign(VAlign_Top).AutoHeight().Padding(10.f)
		[
			SNew(SBorder)
			.BorderImage(FEditorStyle::GetBrush("Graph.StateNode.Body"))
			.BorderBackgroundColor_Lambda([this, GameOverColors] { return GameOverColors[GameStatus]; })
			.ForegroundColor(FLinearColor::White)
			.Padding(10.f)
			.Visibility_Lambda([this] { return GameIsOver() ? EVisibility::Visible : EVisibility::Collapsed; })
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				  .HAlign(HAlign_Center).VAlign(VAlign_Center).AutoWidth()
				[
					SNew(STextBlock)
					.Font(FEditorStyle::Get().GetFontStyle("FontAwesome.18"))
					.TextStyle(FEditorStyle::Get(), "NormalText.Important")
					.Text_Lambda([this, GameOverIcons] { return GameOverIcons[GameStatus]; })
				]
				+ SHorizontalBox::Slot()
				  .HAlign(HAlign_Center).VAlign(VAlign_Center).AutoWidth()
				  .Padding(5.f, 0)
				[
					SNew(STextBlock)
					.Text_Lambda([this, GameOverTexts] { return GameOverTexts[GameStatus]; })
				]
			]
		]
	];

	GridData = FGridData();
	ChangeGrid(FVector2D(InArgs._Rows, InArgs._Columns));
}

void SMineSweeperGrid::ChangeGrid(const FVector2D& InSize)
{
	GameStatus = EGameStatus::Running;
	Grid->ClearChildren();

	GridData.Rows = InSize.Y;
	GridData.Columns = InSize.X;

	NGrid::Build(GridData);

	uint32 Position = 0;

	for (int32 Row = 0; Row < GridData.Rows; ++Row)
	{
		for (int32 Col = 0; Col < GridData.Columns; ++Col)
		{
			const FGridSlot Slot = GridData.GetSlot(Row, Col);
			FString Number = Slot.AsideBombsNumber == 0 ? TEXT("") : FString::FromInt(Slot.AsideBombsNumber);
			FText Text = Slot.bIsBomb
							 ? FEditorFontGlyphs::Bomb // fa-bomb
							 : FText::FromString(Number);

			FSlateFontInfo Font = Slot.bIsBomb
									  ? FEditorStyle::Get().GetFontStyle("FontAwesome.11")
									  : FCoreStyle::GetDefaultFontStyle("Bold", 11);

			Grid->AddSlot(Col, Row)
			[
				SNew(SBox)
				.WidthOverride(25.f)
				.HeightOverride(25.f)
				.IsEnabled_Lambda([this]() { return !GameIsOver(); })
				[
					SNew(SButton)
					.ForegroundColor(GetCellColor(Slot.AsideBombsNumber))
					.IsEnabled_Raw(this, &SMineSweeperGrid::IsButtonEnable, Position)
					.OnClicked(this, &SMineSweeperGrid::HandleButtonClicked, Position)
					.ToolTipText(FText::Format(LOCTEXT("GridSlotButtonTooltip", "Are you suuuure? {0}"), Position))
					.ContentPadding(2.f)
					.HAlign(HAlign_Center)
					[
						SNew(STextBlock)
						.Visibility_Raw(this, &SMineSweeperGrid::HandleButtonDetailsVisibility, Position)
						.Font(Font)
						.Text(Text)
					]
				]
			];
			Position++;
		}
	}
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SMineSweeperGrid::Refresh()
{
	ChangeGrid(FVector2D(GridData.Columns, GridData.Rows));
}

FReply SMineSweeperGrid::OnReplayClicked()
{
	Refresh();
	return FReply::Handled();
}

EVisibility SMineSweeperGrid::HandleButtonDetailsVisibility(uint32 Position) const
{
	if (bCheatMode) return EVisibility::Visible;
	const FGridSlot Slot = GridData.GetSlot(Position);
	if (GameIsOver() && Slot.bIsBomb) return EVisibility::Visible;
	if (Slot.bIsFound) return EVisibility::Visible;
	return EVisibility::Hidden;
}

bool SMineSweeperGrid::IsButtonEnable(uint32 Position) const
{
	const FGridSlot Slot = GridData.GetSlot(Position);
	return !Slot.bIsFound;
}

FReply SMineSweeperGrid::OnCheatModeClicked()
{
	bCheatMode = !bCheatMode;
	return FReply::Handled();
}

inline bool SMineSweeperGrid::GameIsOver() const
{
	return GameStatus == EGameStatus::Fail || GameStatus == EGameStatus::Success;
}

FReply SMineSweeperGrid::HandleButtonClicked(uint32 Position)
{
	FGridSlot& Slot = GridData.GetSlot(Position);
	if (Slot.bIsBomb)
	{
		UE_LOG(LogTemp, Error, TEXT("%s You've clicked on a bomb!!!"), ANSI_TO_TCHAR(__FUNCTION__));
		GameStatus = EGameStatus::Fail;
	}
	else
	{
		GridData.SlotFoundAt(Position);
		if (GridData.Num() - GridData.GetDiscovered() == GridData.BombsAmount)
		{
			GameStatus = EGameStatus::Success;
		}
	}

	return FReply::Handled();
}

FLinearColor SMineSweeperGrid::GetCellColor(const int32 BombsNumber)
{
	FLinearColor Color = FLinearColor::Black;
	switch (BombsNumber)
	{
		case 1:
			Color = FLinearColor::Blue;
			break;
		case 2:
			Color = FColor::FromHex("00851f");
			break;
		case 4:
			Color = FColor::FromHex("a40019");
			break;
		case 5:
			Color = FColor::FromHex("912400");
			break;
		case 6:
			Color = FColor::FromHex("bd2f00");
			break;
		case 7:
			Color = FColor::FromHex("f5520a");
			break;
		case 8:
			Color = FColor::FromHex("ff0000");
			break;
		case 0:
		default:
			break;
	}
	return Color;
}

#undef LOCTEXT_NAMESPACE

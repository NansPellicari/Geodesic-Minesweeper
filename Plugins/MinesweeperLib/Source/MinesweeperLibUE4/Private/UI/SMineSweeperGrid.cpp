#include "UI/SMineSweeperGrid.h"


#include "EditorFontGlyphs.h"
#include "EditorStyleSet.h"
#include "Grid.h"
#include "SlateOptMacros.h"

#define LOCTEXT_NAMESPACE "MinesweeperUE4"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SMineSweeperGrid::Construct(const FArguments& InArgs)
{
	ChildSlot
	[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		  .HAlign(HAlign_Center).VAlign(VAlign_Top).AutoHeight()
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
	];

	GridData = FGridData();
	ChangeGrid(FVector2D(InArgs._Rows, InArgs._Columns));
}

void SMineSweeperGrid::ChangeGrid(const FVector2D& InSize)
{
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
									  : FEditorStyle::Get().GetFontStyle("NormalFont");

			Grid->AddSlot(Col, Row)
			[
				SNew(SBox)
				.WidthOverride(25.f)
				.HeightOverride(25.f)
				.IsEnabled_Lambda([this]() { return !bGameIsOver; })
				[
					SNew(SButton)
					.ForegroundColor(GetCellColor(Slot.AsideBombsNumber))
					.OnClicked(this, &SMineSweeperGrid::HandleButtonClicked, Position)
					.ToolTipText(LOCTEXT("GridSlotButtonTooltip", "Are you suuuure?"))
					.ContentPadding(2.f)
					.HAlign(HAlign_Center)
					[
						SNew(STextBlock)
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
	bGameIsOver = false;
	UE_LOG(LogTemp, Log, TEXT("%s Refresh"), ANSI_TO_TCHAR(__FUNCTION__));
	ChangeGrid(FVector2D(GridData.Columns, GridData.Rows));
}

FReply SMineSweeperGrid::OnReplayClicked()
{
	UE_LOG(LogTemp, Log, TEXT("%s Replay"), ANSI_TO_TCHAR(__FUNCTION__));
	Refresh();
	return FReply::Handled();
}

FReply SMineSweeperGrid::HandleButtonClicked(uint32 Position)
{
	UE_LOG(LogTemp, Log, TEXT("%s clicked on %i"), ANSI_TO_TCHAR(__FUNCTION__), Position);
	FGridSlot Slot = GridData.GetSlot(Position);
	if (Slot.bIsBomb)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s You've clicked on a bomb!!!"), ANSI_TO_TCHAR(__FUNCTION__));
		bGameIsOver = true;
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
			Color = FColor::FromHex("1aa101");
			break;
		case 4:
			Color = FColor::FromHex("a40019");
			break;
		case 5:
			Color = FColor::FromHex("a40019");
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

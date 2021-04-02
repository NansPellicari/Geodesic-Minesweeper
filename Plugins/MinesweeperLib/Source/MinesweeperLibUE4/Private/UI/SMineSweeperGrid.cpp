#include "UI/SMineSweeperGrid.h"

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

	ChangeGrid(FVector2D(InArgs._Rows, InArgs._Columns));
}

void SMineSweeperGrid::ChangeGrid(const FVector2D& InSize)
{
	Columns = InSize.X;
	Rows = InSize.Y;
	Grid->ClearChildren();
	uint32 Position = 0;
	for (uint32 Row = 0; Row < Rows; ++Row)
	{
		for (uint32 Col = 0; Col < Columns; ++Col)
		{
			Grid->AddSlot(Col, Row)
			[
				SNew(SBox)
				.WidthOverride(25.f)
				.HeightOverride(25.f)
				[
					SNew(SButton)
					  .OnClicked(this, &SMineSweeperGrid::HandleButtonClicked, Position)
					  .ContentPadding(2.f)
					  .HAlign(HAlign_Center)
				]
			];
			Position++;
		}
	}
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SMineSweeperGrid::Refresh()
{
	UE_LOG(LogTemp, Warning, TEXT("%s Refresh"), ANSI_TO_TCHAR(__FUNCTION__));
	ChangeGrid(FVector2D(Columns, Rows));
}

FReply SMineSweeperGrid::OnReplayClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("%s Replay"), ANSI_TO_TCHAR(__FUNCTION__));
	Refresh();
	return FReply::Handled();
}

FReply SMineSweeperGrid::HandleButtonClicked(uint32 Position)
{
	UE_LOG(LogTemp, Warning, TEXT("%s clicked on %i"), ANSI_TO_TCHAR(__FUNCTION__), Position);
	return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE

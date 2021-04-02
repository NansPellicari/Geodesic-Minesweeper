#include "UI/SMineSweeperWindow.h"

#include "SlateOptMacros.h"
#include "UI/SMineSweeperGrid.h"
#include "Widgets/Input/SNumericEntryBox.h"

#define LOCTEXT_NAMESPACE "MinesweeperUE4"

const FVector2D FMinesweeperGridSize::Beginner(8, 8);
const FVector2D FMinesweeperGridSize::Advanced(16, 16);
const FVector2D FMinesweeperGridSize::Expert(32, 16);

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SMineSweeperWindow::Construct(const FArguments& InArgs)
{
	ChildSlot
	[
		SNew(SScrollBox)
		.Orientation(Orient_Vertical)
		+ SScrollBox::Slot()
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot() // The buttons row
			  .HAlign(HAlign_Center).VAlign(VAlign_Top).AutoHeight().Padding(20.f)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				  .HAlign(HAlign_Center).VAlign(VAlign_Top).AutoWidth()
				[
					SNew(SButton)
				  .Text(LOCTEXT("ButtonBeginnerLabel", "Beginner"))
				  .ForegroundColor(FLinearColor::White)
				  .ButtonColorAndOpacity(FLinearColor::Blue)
				  .OnClicked(this, &SMineSweeperWindow::OnLevelClicked, FMinesweeperGridSize::Beginner)
				]
				+ SHorizontalBox::Slot()
				  .HAlign(HAlign_Center).VAlign(VAlign_Top).AutoWidth()
				[
					SNew(SButton)
				  .Text(LOCTEXT("ButtonAdvancedLabel", "Advanced"))
				  .ForegroundColor(FLinearColor::Black)
				  .ButtonColorAndOpacity(FLinearColor::Green)
				  .OnClicked(this, &SMineSweeperWindow::OnLevelClicked, FMinesweeperGridSize::Advanced)
				]
				+ SHorizontalBox::Slot()
				  .HAlign(HAlign_Center).VAlign(VAlign_Top).AutoWidth()
				[
					SNew(SButton)
				  .Text(LOCTEXT("ButtonExpertLabel", "Expert"))
				  .ForegroundColor(FLinearColor::White)
				  .ButtonColorAndOpacity(FLinearColor::Red)
				  .OnClicked(this, &SMineSweeperWindow::OnLevelClicked, FMinesweeperGridSize::Expert)
				]
				+ SHorizontalBox::Slot()
				  .HAlign(HAlign_Center)
				  .VAlign(VAlign_Top)
				  .AutoWidth()
				[
					SNew(SButton)
					  .Text(LOCTEXT("ButtonCustomLabel", "Custom"))
					  .OnClicked(this, &SMineSweeperWindow::OnCustomClicked)
				]
			]
			+ SVerticalBox::Slot() // The optional custom field (width, height)
			  .HAlign(HAlign_Center).VAlign(VAlign_Top).AutoHeight().Padding(5.f)
			[
				SNew(SHorizontalBox)
				// Only make this slot visible when user click on the button "custom"
				.Visibility_Lambda([this] { return bIsCustom ? EVisibility::Visible : EVisibility::Collapsed; })
				+ SHorizontalBox::Slot() // Width Field
				  .HAlign(HAlign_Left).VAlign(VAlign_Center).AutoWidth()
				[
					SNew(STextBlock)
				.Text(LOCTEXT("GridWidthLabel", "Width"))
				.Margin(FMargin(5.f, 0))
				]
				+ SHorizontalBox::Slot()
				  .HAlign(HAlign_Left)
				  .VAlign(VAlign_Center)
				[
					SNew(SNumericEntryBox<int32>)
				  .MinDesiredValueWidth(75)
				  .MinValue(4)
				  .MaxValue(32)
				  .MinSliderValue(4)
				  .MaxSliderValue(32)
				  .Value(this, &SMineSweeperWindow::OnGetPreviewWidthValue)
				  .OnValueCommitted(this, &SMineSweeperWindow::WidthChanged)
				]
				+ SHorizontalBox::Slot() // Height Field
				  .HAlign(HAlign_Left).VAlign(VAlign_Center).AutoWidth()
				[
					SNew(STextBlock)
				  .Text(LOCTEXT("GridHeightLabel", "Height"))
				  .Margin(FMargin(5.f, 0))
				]
				+ SHorizontalBox::Slot()
				  .HAlign(HAlign_Left)
				  .VAlign(VAlign_Center)
				[
					SNew(SNumericEntryBox<int32>)
				  .MinDesiredValueWidth(75)
				  .MinValue(4)
				  .MaxValue(32)
				  .MinSliderValue(4)
				  .MaxSliderValue(32)
				  .Value(this, &SMineSweeperWindow::OnGetPreviewHeightValue)
				  .OnValueCommitted(this, &SMineSweeperWindow::HeightChanged)
				]
			]
			+ SVerticalBox::Slot() // The grid
			  .HAlign(HAlign_Center).VAlign(VAlign_Top)
			[
				SAssignNew(Grid, SMineSweeperGrid)
			.Rows(FMinesweeperGridSize::Beginner.X)
			.Columns(FMinesweeperGridSize::Beginner.Y)
			]
		]

	];
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION


FReply SMineSweeperWindow::OnLevelClicked(const FVector2D GridSize)
{
	bIsCustom = false;
	ChangeGridConfig(GridSize);
	return FReply::Handled();
}

FReply SMineSweeperWindow::OnCustomClicked()
{
	bIsCustom = true;
	return FReply::Handled();
}


void SMineSweeperWindow::ChangeGridConfig(const FVector2D& GridSize)
{
	if (!GridSize.Equals(ChosenConfig))
	{
		Grid->ChangeGrid(GridSize);
		ChosenConfig = GridSize;
	}
}

void SMineSweeperWindow::WidthChanged(int32 NewValue, ETextCommit::Type)
{
	ChangeGridConfig(FVector2D(FMath::Min<int32>(NewValue, 32), ChosenConfig.Y));
}

void SMineSweeperWindow::HeightChanged(int32 NewValue, ETextCommit::Type)
{
	ChangeGridConfig(FVector2D(ChosenConfig.X, FMath::Min<int32>(NewValue, 32)));
}

#undef LOCTEXT_NAMESPACE

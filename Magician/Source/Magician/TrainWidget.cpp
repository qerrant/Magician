#include "TrainWidget.h"

void UTrainWidget::NativeConstruct()
{
	Super::NativeConstruct();

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController != nullptr)
	{
		MagicianPC = Cast<AMagicianPlayerController>(PlayerController);
	}
	
	AddButton->OnClicked.AddUniqueDynamic(this, &UTrainWidget::AddNewTemplate);
	ClearButton->OnClicked.AddUniqueDynamic(this, &UTrainWidget::ClearPoints);
}

void UTrainWidget::AddNewTemplate()
{
	if (!ensure(MagicianPC != nullptr)) return;
	const FString Name = NameTextBox->GetText().ToString();
	MagicianPC->AddTemplateToDataTable(Name);
}

void UTrainWidget::ClearPoints()
{
	if (!ensure(MagicianPC != nullptr)) return;
	MagicianPC->HideTrainWidget();
}

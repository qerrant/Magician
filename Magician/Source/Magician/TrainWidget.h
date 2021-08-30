#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "MagicianPlayerController.h"
#include "TrainWidget.generated.h"


UCLASS()
class MAGICIAN_API UTrainWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	class UButton* AddButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* ClearButton;

	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* NameTextBox;

protected:
	UFUNCTION()
	void AddNewTemplate();

	UFUNCTION()
	void ClearPoints();

protected:
	void NativeConstruct() override;
	
private:
	AMagicianPlayerController* MagicianPC;
	
};

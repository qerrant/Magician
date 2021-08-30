#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UnistrokeDataTable.generated.h"

USTRUCT()
struct MAGICIAN_API FUnistrokeDataTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	FUnistrokeDataTable();
	~FUnistrokeDataTable();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FVector2D> Points;

};

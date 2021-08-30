#include "MagicianPawn.h"

AMagicianPawn::AMagicianPawn()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AMagicianPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMagicianPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMagicianPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMagicianPawn::SpawnShape(const FString &Name)
{
	if (ShapeMap.Contains(Name))
	{
		FTransform ShapeTransform = FTransform();
		float y = FMath::RandRange(-350, 350);
		ShapeTransform.SetLocation(FVector(350, y, 350));
		GetWorld()->SpawnActor<AActor>(ShapeMap[Name], ShapeTransform);
	}
}


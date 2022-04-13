#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Math/UnrealMathUtility.h"
#include "Components/InputComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "PlayerPaddle.generated.h"

UCLASS()
class PONG_API APlayerPaddle : public APawn {
	GENERATED_BODY()

public:
	APlayerPaddle();

	UPROPERTY(VisibleAnywhere, Category = "Switch Components")
	UStaticMeshComponent* VisualMesh;

	APlayerController* Player;

	FVector Movement;

protected:

	void Move(float Move);

	void Pause();

public:	
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FVector GetPaddleVelocity();
};
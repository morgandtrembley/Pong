#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pong/Ball.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "MenuPaddle.generated.h"

UCLASS()
class PONG_API AMenuPaddle : public AActor
{
	GENERATED_BODY()
	
public:	
	AMenuPaddle();

	UPROPERTY(VisibleAnywhere, Category = "Switch Components")
	UStaticMeshComponent* VisualMesh;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	ABall* Ball;

	FVector Movement;
	FVector BallPosition;
	FVector PaddlePosition;

public:	
	virtual void Tick(float DeltaTime) override;
};

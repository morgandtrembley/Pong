#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ball.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "AIPaddle.generated.h"

UCLASS()
class PONG_API AAIPaddle : public AActor {
	GENERATED_BODY()
	
public:	
	AAIPaddle();

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

	FVector GetPaddleVelocity();
};

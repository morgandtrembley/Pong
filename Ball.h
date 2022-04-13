#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/AudioComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "UObject/ConstructorHelpers.h"
#include "PlayerPaddle.h"
#include "AIPaddle.h"
#include "PongGameModeBase.h"
#include "Ball.generated.h"

UCLASS()
class PONG_API ABall : public AActor {
	GENERATED_BODY()
	
public:	
	ABall();

	UPROPERTY(VisibleAnywhere, Category = "Switch Components")
	class USphereComponent* CollisionMesh;

	UPROPERTY(VisibleAnywhere, Category = "Switch Components")
	UStaticMeshComponent* VisualMesh;

	USoundCue* CollisionAudioCue;
	UAudioComponent* CollisionAudioComponent;

protected:
	virtual void BeginPlay() override;

	void SetBallPosition(float DeltaTime);

	void CheckBounds();

	UPROPERTY(EditAnywhere)
	APlayerPaddle* PlayerPaddle;

	UPROPERTY(EditAnywhere)
	AAIPaddle* AIPaddle;

	FVector BallVelocity;
	FVector BallLocation;

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
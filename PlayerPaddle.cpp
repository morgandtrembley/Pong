#include "PlayerPaddle.h"

#define PADDLE_MOVE_SPEED 1000

APlayerPaddle::APlayerPaddle() {
	PrimaryActorTick.bCanEverTick = true;

	// visual component
	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualMesh"));
	VisualMesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeVisualAsset(TEXT("/Game/MyContent/paddle.paddle"));
	if (CubeVisualAsset.Succeeded()) {
		VisualMesh->SetStaticMesh(CubeVisualAsset.Object);
		VisualMesh->SetRelativeLocation(FVector(0, 0, 0));
		VisualMesh->SetWorldScale3D(FVector(0.5, 0.4, 0.4));
	}
}

FVector APlayerPaddle::GetPaddleVelocity() {
	return Movement;
}

void APlayerPaddle::Pause() {
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Game Paused"));
	}
}

void APlayerPaddle::Move(float move) {
	Movement.X = move * PADDLE_MOVE_SPEED;
}

void APlayerPaddle::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	// move paddle
	if (Movement.X != 0) {
		const FVector NewLocation = GetActorLocation() + (Movement * DeltaTime);
		if (NewLocation.X < 600 && NewLocation.X > -600) {
			SetActorLocation(NewLocation);
		}
	}
}

// Called to bind functionality to input
void APlayerPaddle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAxis(TEXT("Move"), this, &APlayerPaddle::Move);
	InputComponent->BindAction(TEXT("Pause"), IE_Pressed, this, &APlayerPaddle::Pause);
}


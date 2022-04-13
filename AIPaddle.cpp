#include "AIPaddle.h"

AAIPaddle::AAIPaddle() {
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

FVector AAIPaddle::GetPaddleVelocity() {
	return Movement;
}

void AAIPaddle::BeginPlay() {
	Super::BeginPlay();
	
	// get ball from level
	Ball = Cast<ABall>(UGameplayStatics::GetActorOfClass(GetWorld(), ABall::StaticClass()));
}

void AAIPaddle::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	BallPosition = Ball->GetActorLocation();
	PaddlePosition = GetActorLocation();

	// AI logic
	if (BallPosition.Y + PaddlePosition.Y > 250 && PaddlePosition.Y > 0 || BallPosition.Y + PaddlePosition.Y < -250 && PaddlePosition.Y < 0) {
		if (FMath::Abs(BallPosition.X - PaddlePosition.X) < 100) {
			Movement.X = 2 * (BallPosition.X - PaddlePosition.X);
		}
		else {
			Movement.X = 4 * (BallPosition.X - PaddlePosition.X);
		}
	}
	else {
		Movement.X = 0;
	}

	// paddle movement
	FVector NewLocation = PaddlePosition + (Movement * DeltaTime);
	if (NewLocation.X > -600 && NewLocation.X < 600) {
		SetActorLocation(NewLocation);
	}
}
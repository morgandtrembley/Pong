#include "MenuPaddle.h"

AMenuPaddle::AMenuPaddle() {
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

void AMenuPaddle::BeginPlay() {
	Super::BeginPlay();
	
	// get ball from level
	Ball = Cast<ABall>(UGameplayStatics::GetActorOfClass(GetWorld(), ABall::StaticClass()));
}

void AMenuPaddle::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	BallPosition = Ball->GetActorLocation();

	PaddlePosition = GetActorLocation();

	// logic for main menu paddles
	if (abs(BallPosition.Y - PaddlePosition.Y) < 400) {
		Movement.X = 2 * (BallPosition.X - PaddlePosition.X);
	}
	else if (FMath::Abs(Movement.X) > 10) {
		if (Movement.X > 0) {
			Movement.X -= 10;
		}
		else {
			Movement.X += 10;
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

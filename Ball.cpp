#include "Ball.h"

ABall::ABall() {
	PrimaryActorTick.bCanEverTick = true;

	// collider component
	CollisionMesh = CreateDefaultSubobject<USphereComponent>(TEXT("Collision Mesh"));
	CollisionMesh->InitSphereRadius(100);
	CollisionMesh->SetupAttachment(RootComponent);
	CollisionMesh->SetRelativeLocation(FVector(0, 0, 0));
	CollisionMesh->SetWorldScale3D(FVector(0.4f));

	CollisionMesh->OnComponentBeginOverlap.AddDynamic(this, &ABall::BeginOverlap);

	// visual component
	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualMesh"));
	VisualMesh->SetupAttachment(CollisionMesh);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/MyContent/ball.ball"));
	if (SphereVisualAsset.Succeeded()) {
		VisualMesh->SetStaticMesh(SphereVisualAsset.Object);
		VisualMesh->SetRelativeLocation(FVector(0, 0, 0));
	}

	// audio collision component
	static ConstructorHelpers::FObjectFinder<USoundCue> CollisionCue(TEXT("/Game/MyContent/Collision.Collision"));
	CollisionAudioCue = CollisionCue.Object;

	CollisionAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Collision Audio Component"));
	CollisionAudioComponent->SetupAttachment(CollisionMesh);
	CollisionAudioComponent->bAutoActivate = false;
	CollisionAudioComponent->SetRelativeLocation(FVector(0,0,0));

	if (CollisionAudioCue->IsValidLowLevelFast()) {
		CollisionAudioComponent->SetSound(CollisionAudioCue);
	}
}

// check if ball is out of bounds and reset
void ABall::CheckBounds() {
	BallLocation = GetActorLocation();
	if (abs(BallLocation.X) > 900 || abs(BallLocation.Y) > 1600) {
		SetActorLocation(FVector(0,0,80));
	}
}

void ABall::SetBallPosition(float DeltaTime) {
	FVector Location = GetActorLocation();
	Location += BallVelocity * DeltaTime;
	SetActorLocation(Location);
}

void ABall::BeginPlay() {
	Super::BeginPlay();
	
	BallVelocity = FVector(FMath::RandRange(-300,300), 500, 0);

	PlayerPaddle = Cast<APlayerPaddle>(UGameplayStatics::GetActorOfClass(GetWorld(), APlayerPaddle::StaticClass()));
	AIPaddle = Cast<AAIPaddle>(UGameplayStatics::GetActorOfClass(GetWorld(), AAIPaddle::StaticClass()));
}

void ABall::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	CheckBounds();

	BallVelocity *= 1.00005;
	SetBallPosition(DeltaTime);
	
}

void ABall::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	CollisionAudioComponent->Play();

	// logic for ball collisions with walls, goals and paddles
	if (OtherActor->ActorHasTag(TEXT("XAxis"))) {
		BallVelocity *= FVector(-1,1,0);
	}
	if (OtherActor->ActorHasTag(TEXT("YAxis"))) {
		BallVelocity *= FVector(1, -1, 0);
	}

	if (OtherActor->ActorHasTag(TEXT("PlayerPaddle"))) {
		BallVelocity.X += PlayerPaddle->APlayerPaddle::GetPaddleVelocity().X / 5;
	}
	if (OtherActor->ActorHasTag(TEXT("AIPaddle"))) {
		BallVelocity.X += AIPaddle->AAIPaddle::GetPaddleVelocity().X;
	}

	if (OtherActor->ActorHasTag(TEXT("Goal"))) {
		SetActorLocation(FVector(0,0,80));
		BallVelocity = FVector(FMath::RandRange(-300, 300), 500, 0);
	}
}
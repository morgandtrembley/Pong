#include "PongGameModeBase.h"

APongGameModeBase::APongGameModeBase() {

}

void APongGameModeBase::BeginPlay() {

	// set starting scores
	PlayerScore = 0;
	AIScore = 0;

	// assign paddles from level to correct 'team'
	TArray<AActor*> temp;
	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), ATriggerVolume::StaticClass(), "YAxis", temp);
	if (temp[0]->ActorHasTag("Player")) {
		PlayerGoal = Cast<ATriggerVolume>(temp[0]);
		AIGoal = Cast<ATriggerVolume>(temp[1]);
	}
	else {
		AIGoal = Cast<ATriggerVolume>(temp[0]);
		PlayerGoal = Cast<ATriggerVolume>(temp[1]);
	}
	temp.Empty();

	// assign spotlights from level to correct 'team'
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpotLight::StaticClass(), temp);
	if (temp[0]->ActorHasTag("AI")) {
		PlayerSpotLight = Cast<ASpotLight>(temp[0]);
		AISpotLight = Cast<ASpotLight>(temp[1]);
	}
	else {
		AISpotLight = Cast<ASpotLight>(temp[0]);
		PlayerSpotLight = Cast<ASpotLight>(temp[1]);
	}

	// collision for scoring
	PlayerGoal->OnActorBeginOverlap.AddDynamic(this, &APongGameModeBase::PlayerGoalOverlap);
	AIGoal->OnActorBeginOverlap.AddDynamic(this, &APongGameModeBase::AIGoalOverlap);
}

// move AI spotlight When AI Scores (player's goal is overlapped)
void APongGameModeBase::PlayerGoalOverlap(AActor* PrimaryActor, AActor* OtherActor) {
	SpotLightLocation = PlayerSpotLight->GetActorLocation();
	if (SpotLightLocation.Y < -570) {
		SpotLightLocation.Y += 150;
		AISpotLight->SetActorLocation(SpotLightLocation);
	}
}

// move Player spotlight When Player Scores
void APongGameModeBase::AIGoalOverlap(AActor* PrimaryActor, AActor* OtherActor) {
	SpotLightLocation = AISpotLight->GetActorLocation();
	if (SpotLightLocation.Y < -570) {
		SpotLightLocation.Y += 150;
		PlayerSpotLight->SetActorLocation(SpotLightLocation);
	}
}
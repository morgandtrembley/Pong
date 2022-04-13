#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Engine/TriggerVolume.h"
#include "Engine/SpotLight.h"
#include "PongGameModeBase.generated.h"

UCLASS()
class PONG_API APongGameModeBase : public AGameModeBase {
	GENERATED_BODY()
	
public:
	APongGameModeBase();

	int AIScore;
	int PlayerScore;
	FVector SpotLightLocation;

	ATriggerVolume* PlayerGoal;
	ATriggerVolume* AIGoal;
	ASpotLight* PlayerSpotLight;
	ASpotLight* AISpotLight;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void PlayerGoalOverlap(AActor* PrimaryActor, AActor* OtherActor);

	UFUNCTION()
	void AIGoalOverlap(AActor* PrimaryActor, AActor* OtherActor);
};

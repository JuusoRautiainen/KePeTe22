// copyright anssi.grohn@karelia.fi 2019

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "SkyBoxActor.generated.h"

UCLASS()
class ESCAPEINSPACE_API ASkyBoxActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASkyBoxActor();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UProceduralMeshComponent* mesh;
	
	TArray <FVector> Vertices;
	TArray <FVector2D> TexCoords;
	TArray <int32> Triangles;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void GenerateSphere(int verticalSlices, int horizontalSlices);
	void PostActorCreated() override;

};
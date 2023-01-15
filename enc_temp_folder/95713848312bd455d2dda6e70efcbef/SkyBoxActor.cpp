// copyright anssi.grohn@karelia.fi 2019


#include "SkyBoxActor.h"

// Sets default values
ASkyBoxActor::ASkyBoxActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	mesh = CreateDefaultSubobject<UProceduralMeshComponent>("Procedural Mesh,");
	RootComponent = mesh;


}

// Called when the game starts or when spawned
void ASkyBoxActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASkyBoxActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void ASkyBoxActor::GenerateSphere(int verticalSlices, int horizontalSlices)
{
	float R = 20.0f;
	float angle = 0.0f;
	float sinAngle;
	float cosAngle;
	
	float stepSizeVertical = 180.0f / verticalSlices;
	float stepSizeHorizontal = 360.0f / horizontalSlices;
	float vangle = 90.0f;
	for (int v = 0; v <= verticalSlices; v++, vangle-=stepSizeVertical)
	{
		float hangle = 0.0f, radiusMultiplierAtHeight = 1.0f;
		float height = 0.0;
		FMath::SinCos(&height, &radiusMultiplierAtHeight, FMath::DegreesToRadians(vangle));
		for (int h = 0; h <= horizontalSlices; h++, hangle += stepSizeHorizontal)
		{
			float X, Y;
			FMath::SinCos(&X, &Y, FMath::DegreesToRadians(hangle));
			Vertices.Add(FVector(X* radiusMultiplierAtHeight, Y* radiusMultiplierAtHeight, height)*R);
			UE_LOG(LogTemp, Warning, TEXT("Added vertex %d: %s"), Vertices.Num() - 1, *Vertices.Last(0).ToString());
		}
	}
	

	Vertices.Add(FVector(0, 0, R));

	Vertices.Add(FVector(R, 0, 0));
	Vertices.Add(FVector(0, R, 0));
	Vertices.Add(FVector(-R, 0, 0));
	Vertices.Add(FVector(0, -R, 0));

	Vertices.Add(FVector(0, 0, -R));

	TexCoords.Add(FVector2D(0.5,1));

	TexCoords.Add(FVector2D(0.00,0.5));
	TexCoords.Add(FVector2D(0.25,0.5));
	TexCoords.Add(FVector2D(0.50,0.5));
	TexCoords.Add(FVector2D(0.75,0.5));

	TexCoords.Add(FVector2D(0.5,0.0));

	Triangles.Add(0);
	Triangles.Add(1);
	Triangles.Add(2);

	Triangles.Add(0);
	Triangles.Add(2);
	Triangles.Add(3);

	Triangles.Add(0);
	Triangles.Add(3);
	Triangles.Add(4);

	Triangles.Add(0);
	Triangles.Add(4);
	Triangles.Add(1);

	Triangles.Add(5);
	Triangles.Add(2);
	Triangles.Add(1);

	Triangles.Add(5);
	Triangles.Add(3);
	Triangles.Add(2);

	Triangles.Add(5);
	Triangles.Add(4);
	Triangles.Add(3);

	Triangles.Add(5);
	Triangles.Add(1);
	Triangles.Add(4);

	mesh ->CreateMeshSection_LinearColor(0,  Vertices, Triangles,  TArray<FVector>(), TexCoords, TArray<FLinearColor>(), TArray<FProcMeshTangent>(), true);
}

void ASkyBoxActor::PostActorCreated()
{
	GenerateSphere(2,0);
}

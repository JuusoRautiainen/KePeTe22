// copyright anssi.grohn@karelia.fi 2019


#include "TerminalActor.h"

// Sets default values
ATerminalActor::ATerminalActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Screen mesh"));
	RootComponent = Mesh;

}

// Called when the game starts or when spawned
void ATerminalActor::BeginPlay()
{
	Super::BeginPlay();
	if (ScreenTextureResolution.X < 100 || ScreenTextureResolution.Y < 100)
	{
		UE_LOG(LogTemp, Error, TEXT("Screen texture resolution is not set in Terminal!"));
		return;
	}
	ScreenTexture = UCanvasRenderTarget2D::CreateCanvasRenderTarget2D(GetWorld(), UCanvasRenderTarget2D::StaticClass(), 
		ScreenTextureResolution.X, ScreenTextureResolution.Y);
	ScreenTexture->OnCanvasRenderTargetUpdate.AddDynamic(this, &ATerminalActor::RenderScreen);
	ScreenTexture->ClearColor = ClearColor;

	 materialInstance = UMaterialInstanceDynamic::Create(Mesh->GetMaterial(0), this);
	Mesh->SetMaterial(0, materialInstance);
	materialInstance->SetTextureParameterValue(ScreenTextureParamName, ScreenTexture);
	
}
void ATerminalActor::UpdateText()
{
	if (ScreenTexture == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Screen texture is not set in Terminal!"));
	}
	else
	{
		ScreenTexture->UpdateResource();
	}
	
}
void ATerminalActor::RenderScreen(UCanvas* Canvas, int32 Width, int32 Height)
{
	Canvas->SetDrawColor(FontColor);
	for (int i = 0; i < Lines.Num(); i++)
	{
		Canvas->DrawText(Font, Lines[i], IndentationAmount, LineHeight+LineHeight*i, FontScale, FontScale, FFontRenderInfo());
	}
}

// Called every frame
void ATerminalActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void ATerminalActor::AddLine(const FString& line)
{
	if (Lines.Num() >= MaxLines)
	{
		Lines.RemoveAt(0);
	}
	Lines.Add(line);
	UpdateText();
}


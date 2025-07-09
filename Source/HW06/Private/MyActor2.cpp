// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor2.h"

// Sets default values
AMyActor2::AMyActor2()
{

	SpeedX = 200.0f;
	ElapsedTime = 0.0f;

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);
	
	// Static Mesh를 코드에서 설정
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Resources/Props/SM_TableRound.SM_TableRound"));
	if (MeshAsset.Succeeded())
	{
		StaticMeshComp->SetStaticMesh(MeshAsset.Object);
	}
	
	// Material을 코드에서 설정
	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("/Game/Resources/Props/Materials/M_Bush.M_Bush"));
	if (MaterialAsset.Succeeded())
	{
		StaticMeshComp->SetMaterial(0, MaterialAsset.Object);
	}
}

// Called when the game starts or when spawned
void AMyActor2::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyActor2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ElapsedTime += DeltaTime; // 경과 시간 업데이트	

	if (ElapsedTime < 3.0f)
	{
		// 액터의 앞 방향(로컬 X축)으로 이동하기
		// 액터가 바라보는 방향으로 계속 이동합니다. (더 자주 쓰여요!)
		FVector LocalDirection = GetActorForwardVector(); // 액터의 앞 방향 벡터 가져오기
		FVector LocalOffset = LocalDirection * SpeedX * DeltaTime; // 이번 프레임에 이동할 거리 계산
		AddActorLocalOffset(LocalOffset);
	}
	else if (ElapsedTime < 6.0f)
	{
		FVector LocalDirection = GetActorForwardVector() * -1.0f; // 액터의 뒷 방향 벡터 가져오기
		FVector LocalOffset = LocalDirection * SpeedX * DeltaTime; // 이번 프레임에 이동할 거리 계산
		AddActorLocalOffset(LocalOffset);
				
	}
	else
	{
		ElapsedTime = 0;
	}
}


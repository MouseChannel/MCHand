// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <vector>
#include "MyCamrta.h"
#include "HandManager.generated.h"

UCLASS()
class UEHANDDEMO_API AHandManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHandManager();
	void (*MCHand_Init)(const char*);
	void (*MCHand_NeedJoint)();
	void (*MCHand_NeedMesh)();
	int*(*MCHand_GetLeftMeshFace)();
	int*(*MCHand_GetRightMeshFace)();
	int* (*MCHand_Infer)();
	float*(*MCHand_GetLeftJoint)();
	float*(*MCHand_GetRightJoint)();
	float*(*MCHand_GetLeftMesh)();
	float*(*MCHand_GetRightMesh)();
	float*(*MCHand_vis_joint)();
	void (*OnlyTest)();
	void (*RegisterCallback)(void (const char* input));

	static TArray<int> lface;
	static TArray<int> rface;
	static TArray<float> lvert;
	static TArray<float> rvert;
	static TArray<FVector3d> lvertices;
	static TArray<FVector3d> rvertices;
	static TArray<float> vis_joint;
	static int frame_w;
	static int frame_h;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	UMyCamrta* myca;
};

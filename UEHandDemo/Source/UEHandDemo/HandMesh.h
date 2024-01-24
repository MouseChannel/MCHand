// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DynamicMeshActor.h"
#include "HandManager.h"
#include "HandMesh.generated.h"

/**
 * 
 */
UCLASS()
class UEHANDDEMO_API AHandMesh : public ADynamicMeshActor
{
	GENERATED_BODY()

public:
	AHandMesh();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	UPROPERTY(EditAnywhere)
	bool is_left;

private:
	
	bool has_Init = false;
};


class MCDynamicMesh3 : public FDynamicMesh3
{
	void AddVertexs(TArray<FVector3d> verts);

	void AddTriangles();
};

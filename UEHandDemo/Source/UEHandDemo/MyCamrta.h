// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyCamrta.generated.h"

/**
 * 
 */
UCLASS()
class UEHANDDEMO_API UMyCamrta : public UUserWidget
{
	GENERATED_BODY()

public:
	class UImage* ImageWidget;
	UTexture2D* TemporaryTexture;
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	TArray<uint8> Pixels;
	// uint8* Pixels;
};

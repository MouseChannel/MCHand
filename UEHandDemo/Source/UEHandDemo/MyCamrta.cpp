// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCamrta.h"

#include "HandManager.h"
#include "Components/Image.h"

void UMyCamrta::NativeConstruct()
{
	Super::NativeConstruct();

	ImageWidget = Cast<UImage>(GetWidgetFromName(TEXT("myImage"))); // 替换为你的UImage控件的名称

	// if (ImageWidget != nullptr)
	// {
	// 	TemporaryTexture = UTexture2D::CreateTransient(640, 480, PF_R8G8B8A8);
	// }


	// Pixels.SetNum(640 * 480*4);
}

void UMyCamrta::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);


	auto frame_w = AHandManager::frame_w;
	auto frame_h = AHandManager::frame_h;
	if (frame_w == 0 || frame_h == 0 || AHandManager::vis_joint.Num() == 0)
	{
		return;
	}
	if (TemporaryTexture == nullptr || TemporaryTexture->GetSizeX() != frame_w || TemporaryTexture->GetSizeY() !=
		frame_h)
	{
		TemporaryTexture = UTexture2D::CreateTransient(frame_w, frame_h, PF_R8G8B8A8);
	}
	if (Pixels.Num() != frame_h * frame_w * 4)
	{
		Pixels.SetNum(frame_h * frame_w * 4);
	}

	auto& vis_data = AHandManager::vis_joint;

	for (int i = 0; i < vis_data.Num() / 3; i++)
	{
		Pixels[i * 4 + 0] = (uint8)vis_data[i * 3]; // R
		Pixels[i * 4 + 1] = (uint8)vis_data[i * 3 + 1]; // R
		Pixels[i * 4 + 2] = (uint8)vis_data[i * 3 + 2]; // R


		Pixels[i * 4 + 3] = 255; // R
	}


	void* Data = TemporaryTexture->GetPlatformData()->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
	FMemory::Memcpy(Data, Pixels.GetData(), frame_w * frame_h * 4);
	TemporaryTexture->GetPlatformData()->Mips[0].BulkData.Unlock();


	TemporaryTexture->UpdateResource();

	ImageWidget->SetBrushFromTexture(TemporaryTexture);
}

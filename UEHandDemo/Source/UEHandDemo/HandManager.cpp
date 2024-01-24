// Fill out your copyright notice in the Description page of Project Settings.


#include "HandManager.h"


// std::vector<int> ALoadSDK::lface = std::vector<int>();
// std::vector<int> ALoadSDK::rface = std::vector<int>();
TArray<int> AHandManager::lface;
TArray<int> AHandManager::rface;
TArray<float> AHandManager::vis_joint;
int AHandManager::frame_w;
int AHandManager::frame_h;
TArray<FVector3d> AHandManager::lvertices;
TArray<FVector3d> AHandManager::rvertices;

// Sets default values
AHandManager::AHandManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}


// Called when the game starts or when spawned
void AHandManager::BeginPlay()
{
	const char* Message = "Your log message";
	FString aa = Message;
	UE_LOG(LogTemp, Warning, TEXT("%s"), *aa);

	// myca->TTest();
	// // myca->Update(vis_joint);
	//  
	// return;

	Super::BeginPlay();
	void* LibraryHandle = FPlatformProcess::GetDllHandle(
		TEXT("/home/mocheng/project/MCHAND/cmake-build-debug/libsrc.so"));
	if (LibraryHandle != nullptr)
	{
		MCHand_Init = (void(*)(const char*))FPlatformProcess::GetDllExport(
			LibraryHandle, TEXT("MCHand_Init"));
		MCHand_NeedJoint = (void(*)(void))FPlatformProcess::GetDllExport(
			LibraryHandle, TEXT("MCHand_NeedJoint"));
		MCHand_NeedMesh = (void(*)(void))FPlatformProcess::GetDllExport(
			LibraryHandle, TEXT("MCHand_NeedMesh"));
		MCHand_GetLeftMeshFace = (int*(*)(void))FPlatformProcess::GetDllExport(
			LibraryHandle, TEXT("MCHand_GetLeftMeshFace"));
		MCHand_GetRightMeshFace = (int*(*)(void))FPlatformProcess::GetDllExport(
			LibraryHandle, TEXT("MCHand_GetRightMeshFace"));
		MCHand_Infer = (int*(*)(void))FPlatformProcess::GetDllExport(
			LibraryHandle, TEXT("MCHand_Infer"));
		MCHand_GetLeftJoint = (float*(*)(void))FPlatformProcess::GetDllExport(
			LibraryHandle, TEXT("MCHand_GetLeftJoint"));
		MCHand_GetRightJoint = (float*(*)(void))FPlatformProcess::GetDllExport(
			LibraryHandle, TEXT("MCHand_GetRightJoint"));
		MCHand_GetLeftMesh = (float*(*)(void))FPlatformProcess::GetDllExport(
			LibraryHandle, TEXT("MCHand_GetLeftMesh"));
		MCHand_GetRightMesh = (float*(*)(void))FPlatformProcess::GetDllExport(
			LibraryHandle, TEXT("MCHand_GetRightMesh"));
		MCHand_vis_joint = (float*(*)(void))FPlatformProcess::GetDllExport(
			LibraryHandle, TEXT("MCHand_vis_joint"));
		RegisterCallback = (void(*)(void (const char* input)))
			FPlatformProcess::GetDllExport(
				LibraryHandle, TEXT("RegisterCallback"));
		OnlyTest = (void(*)(void))FPlatformProcess::GetDllExport(
			LibraryHandle, TEXT("OnlyTest"));
		check(MCHand_Init)
		check(MCHand_NeedJoint)
		check(MCHand_NeedMesh)
		check(MCHand_GetLeftMeshFace)
		check(MCHand_GetRightMeshFace)
		check(MCHand_GetLeftJoint)
		check(MCHand_GetRightJoint)
		check(MCHand_GetLeftMesh)
		check(MCHand_GetRightMesh)
		check(MCHand_vis_joint)
		// OnlyTest();
		int a = 0;
	}

	// void (*LogFun)(const char* input);
	auto LogFun = [](const char* input)
	{
		FString aa = input;
		UE_LOG(LogTemp, Warning, TEXT("%s"), *aa);
	};
	RegisterCallback(LogFun);
	OnlyTest();
	MCHand_Init("/home/mocheng/project/RECONSTRCUT/InterWild/demo/mochengres.onnx");

	auto llface = MCHand_GetLeftMeshFace();
	auto rrface = MCHand_GetRightMeshFace();
	MCHand_NeedJoint();
	MCHand_NeedMesh();
	lface.SetNum(4614);
	rface.SetNum(4614);
	FMemory::Memcpy(lface.GetData(), llface, lface.Num() * sizeof(int));
	FMemory::Memcpy(rface.GetData(), rrface, rface.Num() * sizeof(int));
 


	lvertices.SetNum(778);
	rvertices.SetNum(778);


	// UE_LOG(LogTemp, Warning, TEXT("%d,%d,%d,%d"), IntArrayView[0], IntArrayView[1], IntArrayView[2], IntArrayView[4]);
}


// Called every frame
void AHandManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	 
	auto w_h = MCHand_Infer();
	frame_w = w_h[0];
	frame_h = w_h[1];
	if(vis_joint.Num()!=frame_h*frame_w*3)
	{
		vis_joint.SetNum(frame_h*frame_w*3);
	}
	MCHand_GetLeftJoint();
	MCHand_GetRightJoint();
	UE_LOG(LogTemp, Warning, TEXT("%d %d "), frame_w, frame_h  );
	// UE_LOG(LogTemp, Warning, TEXT("%f %f %f"), left_jpiont[0], left_jpiont[1], left_jpiont[2] );

	auto vis = MCHand_vis_joint();
	// UE_LOG(LogTemp, Warning, TEXT("Manager Tick"));


	FMemory::Memcpy(vis_joint.GetData(), vis, vis_joint.Num() * sizeof(float));

	auto left_mesh_raw = MCHand_GetLeftMesh();
	auto right_mesh_raw = MCHand_GetRightMesh();
	UE_LOG(LogTemp, Warning, TEXT("%f %f %f"), left_mesh_raw[0], left_mesh_raw[1], left_mesh_raw[2] );
	for (int i = 0; i < lvertices.Num(); i++)
	{
		lvertices[i] = FVector3d{left_mesh_raw[i * 3], left_mesh_raw[i * 3 + 1], left_mesh_raw[i * 3 + 2]};
		rvertices[i] = FVector3d{right_mesh_raw[i * 3], right_mesh_raw[i * 3 + 1], right_mesh_raw[i * 3 + 2]};
	}


	// myca->Update(vis_joint);
}

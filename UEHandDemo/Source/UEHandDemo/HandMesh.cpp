// Fill out your copyright notice in the Description page of Project Settings.


#include "HandMesh.h"


#include "Generators/MeshShapeGenerator.h"


AHandMesh::AHandMesh()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AHandMesh::BeginPlay()
{
	Super::BeginPlay();
	UE::Geometry::FDynamicMesh3 Mesh;
	TArray<FVector3d> Vertices;
	Vertices.Emplace(0, 0, 0); // V0
	Vertices.Emplace(1, 0, 0); // V1
	Vertices.Emplace(1, 1, 0); // V2
	Vertices.Emplace(0, 1, 0); // V3
	Vertices.Emplace(0, 0, 1); // V4
	Vertices.Emplace(1, 0, 1); // V5
	Vertices.Emplace(1, 1, 1); // V6
	Vertices.Emplace(0, 1, 1); // V7

	// 添加立方体的顶点
	for (const FVector3d& Vertex : Vertices)
	{
		Mesh.AppendVertex(Vertex * 1000);
	}


	// 添加立方体的三角形面
	Mesh.AppendTriangle(0, 1, 2);
	Mesh.AppendTriangle(0, 2, 3);
	Mesh.AppendTriangle(4, 5, 6);
	Mesh.AppendTriangle(4, 6, 7);
	Mesh.AppendTriangle(0, 1, 5);
	Mesh.AppendTriangle(0, 5, 4);
	Mesh.AppendTriangle(2, 3, 7);
	Mesh.AppendTriangle(2, 7, 6);
	Mesh.AppendTriangle(0, 3, 7);
	Mesh.AppendTriangle(0, 7, 4);
	Mesh.AppendTriangle(1, 2, 6);
	Mesh.AppendTriangle(1, 6, 5);
	// DynamicMeshComponent->EditMesh()
	DynamicMeshComponent->SetMesh(std::move(Mesh));
}


void AHandMesh::Tick(float DeltaSeconds)
{
	 
	auto& verts_data =is_left ? AHandManager::lvertices:AHandManager::rvertices;
	if (verts_data.Num() == 0 || AHandManager::lface.Num() == 0)
	{
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("HERE Tick  "));

	if (has_Init)
	{
		DynamicMeshComponent->EditMesh([verts_data](UE::Geometry::FDynamicMesh3& data)
		{
			for (int i = 0; i < verts_data.Num(); i++)
			{
				data.SetVertex(i, verts_data[i] * 1000);
			}
			// auto rr = data.GetVertex(2);
			// rr[0] += 100;
			// data.SetVertex(2, rr);
			auto rrr = data.GetVertex(0);
			// UE_LOG(LogTemp, Warning, TEXT("HERE Tick%f %f %f "), rrr[0], rrr[1], rrr[2]);
		
			UE_LOG(LogTemp, Warning, TEXT("HERE Tick%d %d %d "), AHandManager::lface.Num(), AHandManager::lface[1],
			       AHandManager::lface[2]);
		}, EDynamicMeshComponentRenderUpdateMode::FastUpdate);
	}
	else
	{
		UE::Geometry::FDynamicMesh3 Mesh;
		 
		for (int i = 0; i < verts_data.Num(); i++)
		{
			Mesh.AppendVertex(verts_data[i] * 1000);
		}
		auto rr = Mesh.GetVertex(0);;
		 
		auto& faces = is_left ? AHandManager::lface : AHandManager::rface;
		for (int i = 0; i < faces.Num() / 3; i++)
		{
			Mesh.AppendTriangle(faces[i * 3], faces[i * 3 + 1], faces[i * 3 + 2]);
		}

		DynamicMeshComponent->SetMesh(std::move(Mesh));
		has_Init = true;
	}

	 
}

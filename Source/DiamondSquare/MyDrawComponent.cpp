// Copyright (c) 2017, Vadim Petrov - MIT License

#include "DiamondSquare.h"
#include "MyDrawComponent.h"
#include "Runtime/Engine/Public/SceneManagement.h"
#include "DiamondSquareMapGeneration.h"

using namespace std;

class FDiamondSquareProxy : public FPrimitiveSceneProxy
{

public:

	FDiamondSquareProxy(UPrimitiveComponent* Component)
		: FPrimitiveSceneProxy(Component)
	{
	}

	virtual FPrimitiveViewRelevance GetViewRelevance(const FSceneView* View) const override
	{
		FPrimitiveViewRelevance Result;
		Result.bDrawRelevance = IsShown(View);
		Result.bShadowRelevance = IsShadowCast(View);
		Result.bDynamicRelevance = true;

		return Result;
	}

	virtual uint32 GetMemoryFootprint(void) const override
	{
		return(sizeof(*this) + GetAllocatedSize());
	}

	virtual bool CanBeOccluded() const override
	{
		return false;
	}

	virtual void GetDynamicMeshElements(const TArray<const FSceneView *>& Views, const FSceneViewFamily& ViewFamily, uint32 VisibilityMap, class FMeshElementCollector& Collector) const override
	{
		DiamondSquareMapGeneration algorithm = DiamondSquareMapGeneration(65);

		algorithm.init_blocks_cords(algorithm);
		algorithm.setScaleASmooth(10, 250);
		
		map<int, vector<vector<double>>> blocks = algorithm.getBlocks();

		for (int32 ViewIndex = 0; ViewIndex < Views.Num(); ViewIndex++)
		{
			FPrimitiveDrawInterface* PDI = Collector.GetPDI(ViewIndex);

			typedef map<int, vector<vector<double>>>::const_iterator MapIterator;
			for (MapIterator iter = blocks.begin(); iter != blocks.end(); iter++)
			{
				FVector p0 = FVector(blocks[iter->first][0][0], blocks[iter->first][0][2], blocks[iter->first][0][1]);
				FVector p1 = FVector(blocks[iter->first][1][0], blocks[iter->first][1][2], blocks[iter->first][1][1]);
				FVector p2 = FVector(blocks[iter->first][2][0], blocks[iter->first][2][2], blocks[iter->first][2][1]);
				FVector p3 = FVector(blocks[iter->first][3][0], blocks[iter->first][3][2], blocks[iter->first][3][1]);

				PDI->DrawLine(p0, p1, FColor::Yellow, SDPG_World, 1.f);
				PDI->DrawLine(p1, p2, FColor::Yellow, SDPG_World, 1.f);
				PDI->DrawLine(p2, p3, FColor::Yellow, SDPG_World, 1.f);
				PDI->DrawLine(p3, p0, FColor::Yellow, SDPG_World, 1.f);
			}
		}
	}
};

FPrimitiveSceneProxy* UMyDrawComponent::CreateSceneProxy()
{
	return new FDiamondSquareProxy(this);
}
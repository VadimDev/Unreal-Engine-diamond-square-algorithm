// Copyright (c) 2017, Vadim Petrov - MIT License

#pragma once

#include "Runtime/Engine/Classes/Components/PrimitiveComponent.h"
#include "Runtime/Engine/Public/PrimitiveSceneProxy.h"
#include "MyDrawComponent.generated.h"

UCLASS(ClassGroup = Experimental, meta = (BlueprintSpawnableComponent))
class DIAMONDSQUARE_API UMyDrawComponent : public UPrimitiveComponent
{
	GENERATED_BODY()

public:

	virtual FPrimitiveSceneProxy* CreateSceneProxy() override;
};

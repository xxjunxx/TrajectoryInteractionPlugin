// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EdMode.h"

class FTrajInteractionPluginEdMode : public FEdMode
{
public:
	const static FEditorModeID EM_TrajInteractionPluginEdModeId;
public:
	FTrajInteractionPluginEdMode();
	virtual ~FTrajInteractionPluginEdMode();

	// FEdMode interface
	virtual void Enter() override;
	virtual void Exit() override;
	//virtual void Tick(FEditorViewportClient* ViewportClient, float DeltaTime) override;
	//virtual void Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI) override;
	//virtual void ActorSelectionChangeNotify() override;
	bool UsesToolkits() const override;
	// End of FEdMode interface
};

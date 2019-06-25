// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "TrajInteractionPluginEdMode.h"
#include "TrajInteractionPluginEdModeToolkit.h"
#include "Toolkits/ToolkitManager.h"
#include "EditorModeManager.h"

const FEditorModeID FTrajInteractionPluginEdMode::EM_TrajInteractionPluginEdModeId = TEXT("EM_TrajInteractionPluginEdMode");

FTrajInteractionPluginEdMode::FTrajInteractionPluginEdMode()
{

}

FTrajInteractionPluginEdMode::~FTrajInteractionPluginEdMode()
{

}

void FTrajInteractionPluginEdMode::Enter()
{
	FEdMode::Enter();

	if (!Toolkit.IsValid() && UsesToolkits())
	{
		Toolkit = MakeShareable(new FTrajInteractionPluginEdModeToolkit);
		Toolkit->Init(Owner->GetToolkitHost());
	}
}

void FTrajInteractionPluginEdMode::Exit()
{
	if (Toolkit.IsValid())
	{
		FToolkitManager::Get().CloseToolkit(Toolkit.ToSharedRef());
		Toolkit.Reset();
	}

	// Call base Exit method to ensure proper cleanup
	FEdMode::Exit();
}

bool FTrajInteractionPluginEdMode::UsesToolkits() const
{
	return true;
}





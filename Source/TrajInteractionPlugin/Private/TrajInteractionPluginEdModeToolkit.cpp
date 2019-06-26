// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "TrajInteractionPluginEdModeToolkit.h"
#include "TrajInteractionPluginEdMode.h"
#include "Engine/Selection.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Text/STextBlock.h"
#include "EditorModeManager.h"

#define LOCTEXT_NAMESPACE "FTrajInteractionPluginEdModeToolkit"

FTrajInteractionPluginEdModeToolkit::FTrajInteractionPluginEdModeToolkit()
{
}

void FTrajInteractionPluginEdModeToolkit::Init(const TSharedPtr<IToolkitHost>& InitToolkitHost)
{
	struct Locals
	{
		static bool IsWidgetEnabled()
		{
			return GEditor->GetSelectedActors()->Num() != 0;
		}

		static FReply OnButtonClick(int32 buttonValue)
		{
			USelection* SelectedActors = GEditor->GetSelectedActors();

			// Let editor know that we're about to do something that we want to undo/redo
			GEditor->BeginTransaction(LOCTEXT("MoveActorsTransactionName", "MoveActors"));

			// For each selected actor
			for (FSelectionIterator Iter(*SelectedActors); Iter; ++Iter)
			{
				if (AActor* LevelActor = Cast<AActor>(*Iter))
				{
					// Register actor in opened transaction (undo/redo)
					LevelActor->Modify();
				

					if (LevelActor->IsA(ATrajectoryActor::StaticClass()))
					{
						ATrajectoryActor* TActor = Cast<ATrajectoryActor>(LevelActor);
						switch (buttonValue)
						{
						case 0:
							TActor->ChangeTrajectoryPath();
							break;
						case 1:
							TActor->ChangeMesh();
							break;
						case 2:
							TActor->ChangeColor();
							break;
						case 3:
							TActor->ChangeSize();
							break;
						case 4:
							TActor->Init();
							break;
						case 5:
							TActor->CreateTrajectory();
							break;
						default:
							break;
						}
						
					}
				}
			}

			// We're done moving actors so close transaction
			GEditor->EndTransaction();

			return FReply::Handled();
		}

		static TSharedRef<SWidget> MakeButton(FText InLabel, const int32 buttonValue)
		{
			return SNew(SButton)
				.Text(InLabel)
				.OnClicked_Static(&Locals::OnButtonClick, buttonValue);
		}
	};

	const float Factor = 256.0f;

	SAssignNew(ToolkitWidget, SBorder)
		.HAlign(HAlign_Center)
		.Padding(25)
		.IsEnabled_Static(&Locals::IsWidgetEnabled)
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			.HAlign(HAlign_Center)
			.Padding(50)
			[
				SNew(STextBlock)
				.AutoWrapText(true)
				.Text(LOCTEXT("HelperLabel", "Select some actors and move them around using buttons below"))
			]
			+ SVerticalBox::Slot()
				.HAlign(HAlign_Center)
				.AutoHeight()
				[
					Locals::MakeButton(LOCTEXT("ChangeTrajectory", "ChangeTrajectory"), 0)
				]
			+ SVerticalBox::Slot()
				.HAlign(HAlign_Center)
				.AutoHeight()
				[
					Locals::MakeButton(LOCTEXT("ChangeMesh", "Change Mesh"), 1)
				]
			+ SVerticalBox::Slot()
				.HAlign(HAlign_Center)
				.AutoHeight()
				[
					Locals::MakeButton(LOCTEXT("ChangeColor", "Change Color"), 2)
				]
			+ SVerticalBox::Slot()
				.HAlign(HAlign_Center)
				.AutoHeight()
				[
					Locals::MakeButton(LOCTEXT("ChangeSize", "Change Size"), 3)
				]
			+ SVerticalBox::Slot()
				.HAlign(HAlign_Center)
				.AutoHeight()
				[
					Locals::MakeButton(LOCTEXT("Init", "Init"), 4)
				]
			+ SVerticalBox::Slot()
				.HAlign(HAlign_Center)
				.AutoHeight()
				[
					Locals::MakeButton(LOCTEXT("CreateTrajectory", "Create Trajectory"), 5)
				]
		];
		
	FModeToolkit::Init(InitToolkitHost);
}

FName FTrajInteractionPluginEdModeToolkit::GetToolkitFName() const
{
	return FName("TrajInteractionPluginEdMode");
}

FText FTrajInteractionPluginEdModeToolkit::GetBaseToolkitName() const
{
	return NSLOCTEXT("TrajInteractionPluginEdModeToolkit", "DisplayName", "TrajInteractionPluginEdMode Tool");
}

class FEdMode* FTrajInteractionPluginEdModeToolkit::GetEditorMode() const
{
	return GLevelEditorModeTools().GetActiveMode(FTrajInteractionPluginEdMode::EM_TrajInteractionPluginEdModeId);
}

#undef LOCTEXT_NAMESPACE

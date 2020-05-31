// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Ascila/Animation/AnimNotify/ATHEquipBow.h"
#include "Character/Ascila/ATHAscila.h"

void UATHEquipBow::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp != nullptr && MeshComp->GetOwner() != nullptr)
	{
		AATHAscila* AscilaCharacter = Cast<AATHAscila>(MeshComp->GetOwner());
		if (AscilaCharacter != nullptr)
		{
			AscilaCharacter->SetEquipBowState(true);
		}
	}
}
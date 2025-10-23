// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "PlayerSEData.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_API UPlayerSEData : public UDataTable
{
	GENERATED_BODY()

	
};

USTRUCT()
struct PROTOTYPE_API FPlayerSE : public FTableRowBase
{
	GENERATED_BODY()

public:
	//TMap ���g���� SE ���Ǘ�
	UPROPERTY(EditAnywhere, Category = "Sound")
	TMap<FName, TObjectPtr<USoundBase>> _seMap;		//SE�̃}�b�v

};
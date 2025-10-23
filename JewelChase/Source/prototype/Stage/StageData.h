//--------------------------------------------------------------------
// �t�@�C���� �FStageData.h
// �T�v       �F�X�e�[�W�i��Q����G�j�̐����𐧌䂷��\����
// �쐬��     �F0231�{��
// �X�V���e   �F11/25�@�쐬
//--------------------------------------------------------------------
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "StageData.generated.h"

/**
 *
 */
UCLASS()
class PROTOTYPE_API UStageData : public UDataTable
{
	GENERATED_BODY()

};

UENUM(BlueprintType) 
enum class heliStatus : uint8
{	
	None UMETA(DisplayName = "None"),
	Right UMETA(DisplayName = "Right"),
	Center UMETA(DisplayName = "Center"),
	Left UMETA(DisplayName = "Left")
};

USTRUCT()
struct PROTOTYPE_API FMapStruct : public FTableRowBase
{
	GENERATED_BODY()

public:
	//�I�u�W�F�N�g�̎��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameData", DisplayName = "Type", meta = (IgnoreForMemberInitializationTest))
	int32 ObjecType;

	//X���[��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameData", DisplayName = "Xlane", meta = (IgnoreForMemberInitializationTest))
	int32 xlane;

	//Y���[��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameData", DisplayName = "Ylane", meta = (IgnoreForMemberInitializationTest))
	int32 ylane;

	//Z���[��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameData", DisplayName = "Zlane", meta = (IgnoreForMemberInitializationTest))
	int32 zlane;

	//�w���R�v�^�[�Ǘ��p
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameData", DisplayName = "HeliStatus", meta = (IgnoreForMemberInitializationTest))
	heliStatus HeliStatus;
};
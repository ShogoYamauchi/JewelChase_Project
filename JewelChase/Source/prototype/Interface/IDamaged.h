//--------------------------------------------------------------------
// �t�@�C�����FIDamaged
// �T�v�@�@�@�FIsDamaged�֐����u���Ă���C���^�[�t�F�C�X
// �쐬�ҁ@�@�F�����
// �X�V���e�@�F11/29
//--------------------------------------------------------------------
#pragma once

#include "CoreMinimal.h"
#include "IDamaged.generated.h"

UINTERFACE(BlueprintType, meta = (CannotImplementInterfaceInBlueprint))
class PROTOTYPE_API UDamaged : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class PROTOTYPE_API IDamaged
{
	GENERATED_IINTERFACE_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Transformation")
	virtual void IsDamaged(int damage) = 0;
};
//--------------------------------------------------------------------
// �t�@�C�����FIMovement
// �T�v�@�@�@�FMoveRight�֐����u���Ă���C���^�[�t�F�C�X
// �쐬�ҁ@�@�F�����
// �X�V���e�@�F11/25
//--------------------------------------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "IDead.generated.h"

UINTERFACE(BlueprintType, meta = (CannotImplementInterfaceInBlueprint))
class PROTOTYPE_API UDead : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class PROTOTYPE_API IDead
{
	GENERATED_IINTERFACE_BODY()

public:
	//UFUNCTION(BlueprintCallable, Category = "Transformation")
	virtual void Dead() = 0;
};

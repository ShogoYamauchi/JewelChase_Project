//--------------------------------------------------------------------
// �t�@�C�����FIMovement
// �T�v�@�@�@�FMoveRight�֐����u���Ă���C���^�[�t�F�C�X
// �쐬�ҁ@�@�F�����
// �X�V���e�@�F11/25
//--------------------------------------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "IMovement.generated.h"

UINTERFACE(BlueprintType, meta = (CannotImplementInterfaceInBlueprint))
class PROTOTYPE_API UMovement : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class PROTOTYPE_API IMovement
{
	GENERATED_IINTERFACE_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Move")
	virtual void Move(float moveSpeed) = 0;
};

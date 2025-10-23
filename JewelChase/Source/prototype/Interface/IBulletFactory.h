//--------------------------------------------------------------------
// �t�@�C�����FIBulletFactory
// �T�v�@�@�@�F�e���C���X�^���X������֐��̃C���^�[�t�F�[�X
// �쐬�ҁ@�@�F�����
// �X�V���e�@�F11/25
//--------------------------------------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "IBulletFactory.generated.h"

UINTERFACE(BlueprintType, meta = (CannotImplementInterfaceInBlueprint))
class PROTOTYPE_API UBulletFactory : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class PROTOTYPE_API IBulletFactory
{
	GENERATED_IINTERFACE_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Transformation")
	virtual void SpawnBullet() = 0;
};


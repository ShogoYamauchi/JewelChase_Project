//--------------------------------------------------------------------
// �t�@�C���� �FInGameController.h
// �T�v       �F�C���Q�[����ʂ̃R���g���[��
// �쐬��     �F0231�{��
// �X�V���e   �F12/03�@�쐬
//--------------------------------------------------------------------
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InGameController.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_API AInGameController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
};

//--------------------------------------------------------------------
// �t�@�C���� �FInGameModeBase.h
// �T�v       �F�C���Q�[����ʂ̃Q�[�����[�h��ݒ肷��
// �쐬��     �F0231�{��
// �X�V���e   �F12/03�@�쐬
//--------------------------------------------------------------------
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "InGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_API AInGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AInGameModeBase();
	void StartPlay();
};

//--------------------------------------------------------------------
// �t�@�C���� �FInGameModeBase.cpp
// �T�v       �F�C���Q�[����ʂ̃Q�[�����[�h��ݒ肷��
// �쐬��     �F0231�{��
// �X�V���e   �F12/03�@�쐬
//--------------------------------------------------------------------

#include "InGameModeBase.h"
#include "InGameController.h"

AInGameModeBase::AInGameModeBase()
    : Super()
{
    //�g�p����R���g���[�����C���Q�[���R���g���[���ɐݒ�
    PlayerControllerClass = AInGameController::StaticClass();

    //DefaultPawnClass��ݒ�
    static ConstructorHelpers::FClassFinder<AActor> Character(TEXT("/Game/0116_sakagami/BP/BP_PlayerCharacter"));
    if (Character.Class != nullptr)
    {
        DefaultPawnClass = Character.Class;
    }
}

void AInGameModeBase::StartPlay()
{
    Super::StartPlay();
}
//--------------------------------------------------------------------
// �t�@�C���� �FInGameController.cpp
// �T�v       �F�C���Q�[����ʂ̃R���g���[��
// �쐬��     �F0231�{��
// �X�V���e   �F12/03�@�쐬
//--------------------------------------------------------------------

#include "InGameController.h"

void AInGameController::BeginPlay()
{
    Super::BeginPlay();

    //�����ŃC���v�b�g�Ώۂ��v���C���AUI�����ɐݒ�
    SetInputMode(FInputModeGameAndUI());
}
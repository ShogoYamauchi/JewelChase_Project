//--------------------------------------------------------------------
// �t�@�C���� �FGameOver.cpp
// �T�v       �F�Q�[���I�[�o�[��UI
// �쐬��     �F0231�{��
// �X�V���e   �F02/24�@�쐬�A
//--------------------------------------------------------------------

#include "GameOver.h"
#include "Kismet/GameplayStatics.h"

void UGameOver::NativeConstruct()
{
	Super::NativeConstruct();

	//�Q�[�����ꎞ��~
	UGameplayStatics::SetGamePaused(GetWorld(), true);

	//���͎�t��UI����݂̂ɂ���
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(FInputModeUIOnly());

	//SEManager���擾���A�Z���N�g����o�^
	_seManager = USEManager::GetInstance(GetWorld());
	_seManager->RegisterSE("select", _selectSE);

	//���g���C�{�^���Ƀo�C���h
	_retryButton = Cast<UButton>(GetWidgetFromName("Retry"));
	if (_retryButton) {
		if (!_retryButton->OnPressed.IsBound()) {
			_retryButton->OnPressed.AddDynamic(this, &UGameOver::RetryPressed);
		}
	}

	//�X�e�[�W�Z���N�g�{�^���Ƀo�C���h
	_quitButton = Cast<UButton>(GetWidgetFromName("Quit"));
	if (_quitButton) {
		if (!_quitButton->OnPressed.IsBound()) {
			_quitButton->OnPressed.AddDynamic(this, &UGameOver::QuitPressed);
		}
	}
}
	
// �֐����FRetryPressed
// ���@���F�Ȃ�
// �߂�l�Fvoid
// �������e�F�����X�e�[�W�����g���C����{�^��
void UGameOver::RetryPressed()
{
	//���݂̃X�e�[�W�����擾���A�J���Ȃ���
	FString Lvname = UGameplayStatics::GetCurrentLevelName(GetWorld());
	UGameplayStatics::OpenLevel(GetWorld(), FName(Lvname));
}
	
// �֐����FQuitPressed
// ���@���F�Ȃ�
// �߂�l�Fvoid
// �������e�F�X�e�[�W�Z���N�g�ɖ߂�{�^��
void UGameOver::QuitPressed()
{
	//�Ö���UI�𐶐����A�X�e�[�W�Z���N�g�֑J��
	pm_ui_QuitPause = CreateWidget<UBlackOut>(GetWorld(), m_ui_QuitPause);
	if (pm_ui_QuitPause){
		pm_ui_QuitPause->AddToViewport();
		pm_ui_QuitPause->SetOpenLevelName("Master_StageSelect");
	}

	//�Z���N�g����炷
	_seManager->PlaySE2D("select");
}
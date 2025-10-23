//--------------------------------------------------------------------
// �t�@�C���� �FPause.cpp
// �T�v       �F�C���Q�[�����̃|�[�Y���
// �쐬��     �F0231�{��
// �X�V���e   �F02/24�@�쐬�A
//--------------------------------------------------------------------

#include "Pause.h"
#include "Kismet/GameplayStatics.h"

void UPause::NativeConstruct()
{
	Super::NativeConstruct();

	//�Q�[�����ꎞ��~
	UGameplayStatics::SetGamePaused(GetWorld(), true);

	//���͎�t��UI����݂̂ɂ���
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(FInputModeUIOnly());

	//SEManager���擾���A�Z���N�g����o�^
	_seManager = USEManager::GetInstance(GetWorld());
	_seManager->RegisterSE("select", _selectSE);

	//�v���C���[���Q�Ƃ��A���
	TSubclassOf<APlayerCharacter> findClass;
	findClass = APlayerCharacter::StaticClass();
	_player = UGameplayStatics::GetActorOfClass(GetWorld(), findClass);

	//���݂̃v���C���[�̏�Ԃ��擾
	_beginPlayerStatus = Cast<APlayerCharacter>(_player)->GetPlayerStatus();

	//�v���C���[�̏�Ԃ�Uncontroll�ɂ���
	Cast<APlayerCharacter>(_player)->SetPlayerStatus(PlayerStatus::Uncontroll);

	init();
}

// �֐����Finit
// ���@���F�Ȃ�
// �߂�l�Fvoid
// �������e�F����������
void UPause::init()
{
	//�ĊJ�{�^���Ƀo�C���h
	_backButton = Cast<UButton>(GetWidgetFromName("Back"));
	if (_backButton) {
		if (!_backButton->OnPressed.IsBound()) {
			_backButton->OnPressed.AddDynamic(this, &UPause::BackPressed);
		}
	}

	//���g���C�{�^���Ƀo�C���h
	_retryButton = Cast<UButton>(GetWidgetFromName("Retry"));
	if (_retryButton) {
		if (!_retryButton->OnPressed.IsBound()) {
			_retryButton->OnPressed.AddDynamic(this, &UPause::RetryPressed);
		}
	}

	//�X�e�[�W�Z���N�g�{�^���Ƀo�C���h
	_quitButton = Cast<UButton>(GetWidgetFromName("Quit"));
	if (_quitButton) {
		if (!_quitButton->OnPressed.IsBound()) {
			_quitButton->OnPressed.AddDynamic(this, &UPause::QuitPressed);
		}
	}
}

// �֐����FBackPressed
// ���@���F�Ȃ�
// �߂�l�Fvoid
// �������e�F�|�[�Y��ʂ���āA�C���Q�[���ɖ߂�{�^��
void UPause::BackPressed()
{
	//�ĊJ����UI�𐶐�
	pm_ui_BackPause = CreateWidget<UUserWidget>(GetWorld(), m_ui_BackPause);
	if (pm_ui_BackPause){
		pm_ui_BackPause->AddToViewport();
	}

	//���g���폜
	RemoveFromParent();

	//�Z���N�g����炷
	_seManager->PlaySE2D("select");

	//�v���C���[�̏�Ԃ����ɖ߂�
	Cast<APlayerCharacter>(_player)->SetPlayerStatus(_beginPlayerStatus);
}

// �֐����FRetryPressed
// ���@���F�Ȃ�
// �߂�l�Fvoid
// �������e�F�����X�e�[�W�����g���C����{�^��
void UPause::RetryPressed()
{
	//���݂̃X�e�[�W�����擾���A�J���Ȃ���
	FString Lvname = UGameplayStatics::GetCurrentLevelName(GetWorld());
	UGameplayStatics::OpenLevel(GetWorld(), FName(Lvname));
}

// �֐����FQuitPressed
// ���@���F�Ȃ�
// �߂�l�Fvoid
// �������e�F�X�e�[�W�Z���N�g�ɖ߂�{�^��
void UPause::QuitPressed()
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



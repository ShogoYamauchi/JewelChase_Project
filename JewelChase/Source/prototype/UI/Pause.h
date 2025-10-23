//--------------------------------------------------------------------
// �t�@�C���� �FPause.h
// �T�v       �F�C���Q�[�����̃|�[�Y���
// �쐬��     �F0231�{��
// �X�V���e   �F02/24�@�쐬�A
//--------------------------------------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "prototype/SEManager.h"
#include "prototype/Player/PlayerCharacter.h"
#include "Components/Button.h"
#include "BlackOut.h"
#include "Pause.generated.h"

UCLASS()
class PROTOTYPE_API UPause : public UUserWidget
{
	GENERATED_BODY()

public:
	void NativeConstruct() override;

private:
	void init();

	UFUNCTION(BlueprintCallable)
	void BackPressed();
	UFUNCTION(BlueprintCallable)
	void RetryPressed();
	UFUNCTION(BlueprintCallable)
	void QuitPressed();

private:

	UPROPERTY()
	TObjectPtr<AActor> _player = nullptr;		//�v���C���[

	UPROPERTY()
	TObjectPtr<USEManager> _seManager = nullptr;	//SEManager

	UPROPERTY(EditAnywhere, Category = "SelectSE")
	TObjectPtr<USoundBase> _selectSE;		//�Z���N�g��SE

	UPROPERTY()
	PlayerStatus _beginPlayerStatus;	//�|�[�Y�ɓ��������̏�Ԃ���

	UPROPERTY()
	TObjectPtr<UButton> _backButton;	//�ĊJ�{�^��

	UPROPERTY()
	TObjectPtr<UButton> _retryButton;	//���g���C�{�^��

	UPROPERTY()
	TObjectPtr<UButton> _quitButton;	//�X�e�[�W�Z���N�g�{�^��

	//--------�ĊJ����UI
	UPROPERTY(EditAnywhere, Category = "UI_QuitPause")
	TSubclassOf<UUserWidget> m_ui_BackPause;

	UPROPERTY()
	UUserWidget* pm_ui_BackPause = nullptr;
	//---------------------------------

	//--------�Ö�UI
	UPROPERTY(EditAnywhere, Category = "UI_BlackOut")
	TSubclassOf<UBlackOut> m_ui_QuitPause;

	UPROPERTY()
	UBlackOut* pm_ui_QuitPause = nullptr;
	//---------------------------------
};
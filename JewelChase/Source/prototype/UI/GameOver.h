//--------------------------------------------------------------------
// �t�@�C���� �FGameOver.h
// �T�v       �F�Q�[���I�[�o�[��UI
// �쐬��     �F0231�{��
// �X�V���e   �F02/24�@�쐬�A
//--------------------------------------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "prototype/SEManager.h"
#include "BlackOut.h"
#include "GameOver.generated.h"

UCLASS()
class PROTOTYPE_API UGameOver : public UUserWidget
{
	GENERATED_BODY()

public:
	void NativeConstruct() override;

private:
	UFUNCTION(BlueprintCallable)
	void RetryPressed();
	UFUNCTION(BlueprintCallable)
	void QuitPressed();
	
private:
	UPROPERTY()
	TObjectPtr<USEManager> _seManager = nullptr;	//SEManager

	UPROPERTY(EditAnywhere, Category = "SelectSE")
	TObjectPtr<USoundBase> _selectSE;		//�Z���N�g��SE

	UPROPERTY()
	TObjectPtr<UButton> _retryButton;	//���g���C�{�^��

	UPROPERTY()
	TObjectPtr<UButton> _quitButton;	//�X�e�[�W�Z���N�g�{�^��

	//--------�Ö�UI
	UPROPERTY(EditAnywhere, Category = "UI_BlackOut")
	TSubclassOf<UBlackOut> m_ui_QuitPause;

	UPROPERTY()
	UBlackOut* pm_ui_QuitPause = nullptr;
	//---------------------------------
};

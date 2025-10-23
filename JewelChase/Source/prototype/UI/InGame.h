//--------------------------------------------------------------------
// �t�@�C���� �FInGame.h
// �T�v       �F�C���Q�[������UI���܂Ƃ߂�
// �쐬��     �F0231�{��
// �X�V���e   �F02/24�@�쐬�A
//--------------------------------------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "prototype/Player/PlayerCharacter.h"
#include "Components/WrapBox.h"
#include "InGame.generated.h"

UCLASS()
class PROTOTYPE_API UInGame : public UUserWidget
{
	GENERATED_BODY()

public:
	void NativeConstruct() override;

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
private:
	void init();

	void UpdateHP();

	void UpdateBullet();

private:
	UPROPERTY()
	TObjectPtr<APlayerCharacter> _player = nullptr;		//�v���C���[

	UPROPERTY(EditAnywhere, Category = "InGameUI")
	TMap<FName, TSubclassOf<UUserWidget>> _ingameUIs;	//�C���Q�[������UI����

	UPROPERTY()
	TObjectPtr<UWrapBox> _hpPanel;			//HP�̃p�l��

	UPROPERTY()
	TObjectPtr<UWrapBox> _bulletPanel;		//�c�e���̃p�l��

	UPROPERTY()
	TObjectPtr<UCanvasPanel> _reloadPanel;	//�����[�h�̃p�l��

	float _gameoverTime = 0.0f;		//�Q�[���I�[�o�[�ɂȂ��Ă���̌o�ߎ���

	int _beforeHP;					//�O���HP

	int _beforebulletNum;			//�O��̎c�e��

	bool _bGameOver = false;		//�Q�[���I�[�o�[�ɂȂ�����

	bool _createGameOverUI = true;	//�Q�[���I�[�o�[UI�𐶐��ł��邩
};

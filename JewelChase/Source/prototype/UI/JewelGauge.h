//--------------------------------------------------------------------
// �t�@�C���� �FJewelGauge.h
// �T�v       �F�W���G���Q�[�W��UI
// �쐬��     �F0231�{��
// �X�V���e   �F02/24�@�쐬�A
//--------------------------------------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Components/Image.h"
#include "prototype/SEManager.h"
#include "prototype/Player/PlayerCharacter.h"
#include "Engine/TimerHandle.h"
#include "JewelGauge.generated.h"

UCLASS()
class PROTOTYPE_API UJewelGauge : public UUserWidget
{
	GENERATED_BODY()

public:
	void NativePreConstruct() override;

	void NativeConstruct() override;

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	void IncreaseGauge(float InDeltaTime);

	void DecreaseGauge(float InDeltaTime);

	void GaugeUpAnim();

	void MaxGaugeAnim(float InDeltaTime);

	void AnimReset();

private:
	UPROPERTY()
	TObjectPtr<AActor> _player = nullptr;		//�v���C���[

	UPROPERTY()
	TObjectPtr<USEManager> _seManager = nullptr;	//SEManager

	UPROPERTY(EditAnywhere, Category = "canJewelSE")
	TObjectPtr<USoundBase> _canJewelSE;	//���܂�������SE

	UPROPERTY()
	TMap<FName, TObjectPtr<UImage>> _gaugeAnimImages;	//���܂������̃A�j���[�V�����摜

	UPROPERTY()
	UMaterialInstanceDynamic* _jewelGaugeMat;	//�Q�[�W�̃}�e���A��

	UPROPERTY()
	FTimerHandle _timer;	//�֐��̍ċA�������f�B���C�������čs���̂ɕK�v�ȃn���h��

	float _maxVal;	//�Q�[�W�̍ő�l

	float _beforeVal = 0.0f;	//�O��ύX�����������̃Q�[�W�̒l

	float _currentVal = 0.0f;	//���݂̃A�j���[�V�������̃Q�[�W��

	float _rushTime = 10.0f;	//�W���G�����b�V����������

	float _decreaseTime = 0.0f;	//�W���G�����b�V�����A�Q�[�W������������ϐ�

	float _animTime = 0.0f;		//�Q�[�W�����܂��Ă鎞�̈�摜�̕`��^�C��

	int _animIndex = 0;			//�Q�[�W�����܂��Ă鎞�̌��݂̕\���摜�ԍ�

	bool _backIndex = false;	//�Q�[�W�����܂��Ă鎞�̕`��ԍ��𑝉��A���������邩

	bool _canPlaySE = true;		//�Q�[�W�����܂�������SE����x�����炷���߂̕ϐ�
};

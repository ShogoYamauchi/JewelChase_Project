//--------------------------------------------------------------------
// �t�@�C����	�FCameraShakeActorComponent.h
// �T�v�@�@�@	�F�J�����̃V�F�C�N���s��
// �쐬�ҁ@�@	�F�_�엮��
// �X�V���e�@	�F2/1  �쐬
//                2/15 �����E�����ς�
//--------------------------------------------------------------------

// �C���N���[�h�K�[�h
#pragma once

// �C���N���[�h
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Camera/CameraComponent.h"
#include "CameraShakeActorComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROTOTYPE_API UCameraShakeActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCameraShakeActorComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//----------------------------------
	// �֐����FStartCameraShakeForComponent
	// ���@���Ffloat�^ �V�F�C�N���鎞�ԁAflaot�^ �V�F�C�N�̐U��
	// �߂�l�F�Ȃ�
	// ���@�e�F�J�����̃V�F�C�N�̎��ԂƋ�����ݒ肵�ăV�F�C�N���J�n����֐�
	//----------------------------------
	/* ForCameraShakeActorComponent */
	UFUNCTION(BlueprintCallable, Category = "CameraShake")
	void StartCameraShakeForComponent(float Duration, float Amplitude);

private:
	// �R���|�[�l���g�̂��Ă���Actor
	UPROPERTY()
	AActor* _ownerActor;

	// �V�F�C�N�̎c�莞��
	float _shakeTimeRemaining;
	// �ŏ��̃V�F�C�N�̎���
	float _firstShakeTime;
	// �V�F�C�N�̐U��
	float _shakeAmplitude;

	// �V�F�C�N�����ǂ����̃t���O
	bool _bIsShake;
};

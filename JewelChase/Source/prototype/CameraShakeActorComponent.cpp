//--------------------------------------------------------------------
// �t�@�C����	�FCameraShakeActorComponent.cpp
// �T�v�@�@�@	�F�J�����̃V�F�C�N���s��
// �쐬�ҁ@�@	�F�_�엮��
// �X�V���e�@	�F2/1  �쐬
//                2/15 �����E�����ς�
//--------------------------------------------------------------------

// �C���N���[�h
#include "CameraShakeActorComponent.h"
#include "Camera/CameraComponent.h"

UCameraShakeActorComponent::UCameraShakeActorComponent()
	: _ownerActor(nullptr)
	, _shakeTimeRemaining(0.0f)
	, _firstShakeTime(0.0f)
	, _shakeAmplitude(0.0f)
	, _bIsShake(false)
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickGroup = TG_PostUpdateWork; // �Ō��Tick�����s
}

void UCameraShakeActorComponent::BeginPlay()
{
	Super::BeginPlay();
	// Owner���i�[
	_ownerActor = GetOwner<AActor>();
}

void UCameraShakeActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (_bIsShake == false && _ownerActor == nullptr)
	{
		// Owner���i�[
		_ownerActor = GetOwner<AActor>();
		return;  // �������^�[��
	}

	// �V�F�C�N�̎c�莞�Ԃ����炷
	_shakeTimeRemaining -= DeltaTime;

	if (_shakeTimeRemaining <= 0.0f)
	{
		// �V�F�C�N�̏I��
		_bIsShake = false;

		// ���̈ʒu�ɖ߂�
		if (UCameraComponent* CameraComponent = _ownerActor->FindComponentByClass<UCameraComponent>())
		{
			CameraComponent->SetRelativeLocation(FVector::ZeroVector);
		}
	}
	else
	{
		// �U�������Ԍo�߂ɉ����Č���������
		// 1.0�`0.0�̊ԂŃV�F�C�N�̐i�s���\���i�J�n����͂P�ɂȂ�܂��jFMath::Pow(�ݏ�̌��ƂȂ鐔,�w���j
		float AmplitudeFactor = FMath::Pow(_shakeTimeRemaining / _firstShakeTime, 3.0f);
		// ���̒l��h��   FMath::Clamp(�ϐ�,�ŏ��l,�ő�l);
		AmplitudeFactor = FMath::Clamp(AmplitudeFactor, 0.0f, 1.0f);

		// ���݂̐U��
		float CurrentAmplitude = _shakeAmplitude * AmplitudeFactor;

		// �����_���ɃJ������h�炷
		FVector ShakeOffset = FVector(
			FMath::RandRange(-CurrentAmplitude, CurrentAmplitude), // X���̗h��
			FMath::RandRange(-CurrentAmplitude, CurrentAmplitude), // Y���̗h��
			FMath::RandRange(-CurrentAmplitude, CurrentAmplitude)  // Z���̗h��
		);

		// �V�����ʒu��ݒ�
		if (UCameraComponent* CameraComponent = _ownerActor->FindComponentByClass<UCameraComponent>())
		{
			UE_LOG(LogTemp, Warning, TEXT("AmplitudeFactor: %f"), AmplitudeFactor);
			CameraComponent->AddLocalOffset(ShakeOffset);
		}
	}
}

//----------------------------------
// �֐����FStartCameraShakeForComponent
// ���@���Ffloat�^ �V�F�C�N���鎞�ԁAflaot�^ �V�F�C�N�̐U��
// �߂�l�F�Ȃ�
// ���@�e�F�J�����̃V�F�C�N�̎��ԂƋ�����ݒ肵�ăV�F�C�N���J�n����֐�
//----------------------------------
void UCameraShakeActorComponent::StartCameraShakeForComponent(float ShakeTime, float Amplitude)
{
	// �V�F�C�N��L����
	_bIsShake = true;
	// �V�F�C�N���Ԃ��i�[
	_shakeTimeRemaining = ShakeTime;
	// �ŏ��̃V�F�C�N���Ԃ��i�[
	_firstShakeTime = ShakeTime;
	// �U���i�h��̋����j���i�[
	_shakeAmplitude = Amplitude;
}
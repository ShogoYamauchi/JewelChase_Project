//--------------------------------------------------------------------
// �t�@�C����   �FFlyAwayActorComponent.cpp
// �T�v�@�@�@	�F������΂�����
// �쐬�ҁ@�@	�F�_�엮��
// �X�V���e�@	�F1/24 �쐬
//                1/26 ������΂������ƃt���O���t�ɂ��鏈���̍쐬
//                2/7  ������񂾎��Ԃ�����Destroy���鏈���̍쐬
//--------------------------------------------------------------------

// �C���N���[�h
#include "FlyAwayActorComponent.h"

UFlyAwayActorComponent::UFlyAwayActorComponent()
	:_ownerActor(nullptr)
	, _destroyTime(0.0f)
	, _flyingTime(0.0f)
	, _canFlyFlag(false)
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UFlyAwayActorComponent::BeginPlay()
{
	Super::BeginPlay();
	_ownerActor = GetOwner<AActor>();
	_flyingTime = 0.0f;
}

void UFlyAwayActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (_canFlyFlag == true)
	{
		if (_ownerActor == nullptr)
		{
			return;
		}

		// �e���̑��x���܂Ƃ߂��x�N�g�����쐬 ���t���[���������ǉ�����Ă���
		FVector FlySpeed = FVector(_flySpeed.X, _flySpeed.Y, _flySpeed.Z *= 1.01f);

		// ���݂̍��W�� ���x �~ DeltaTime �����Z
		FVector CurrentLocation = _ownerActor->GetActorLocation();
		CurrentLocation += FlySpeed * DeltaTime;

		// �v�Z�����V�������W�ɐݒ�
		_ownerActor->SetActorLocation(CurrentLocation);

		// ���ł��鎞�Ԃ����Z
		_flyingTime += DeltaTime;

		// ���ł��鎞�Ԃ��󂷎��Ԃ𒴂�����
		if (_flyingTime >= _destroyTime)
		{
			_ownerActor->Destroy();		// ���̃R���|�[�l���g�����Ă�Actor��j��
		}
	}
}

//----------------------------------
// �֐����FChangeFlyFlag
// ���@���F�Ȃ�
// �߂�l�F�Ȃ�
// ���@�e�F������΂��������s�����̃t���O���t�ɂ���
//----------------------------------
void UFlyAwayActorComponent::ChangeFlyFlag()
{
	_canFlyFlag = !_canFlyFlag;
}


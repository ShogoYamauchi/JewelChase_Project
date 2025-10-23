//--------------------------------------------------------------------
//����ҁ@�F���@���
//��������F2024/12/23
//�ŏI�X�V�F2024/12/23
//�T�@�v�@�F�v���C���[�̓�������
//--------------------------------------------------------------------
#include "MoveRightComponent.h"

UMoveRightComponent::UMoveRightComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UMoveRightComponent::BeginPlay()
{
	Super::BeginPlay();

	_ownerCharacter = Cast<ACharacter>(GetOwner());
}

void UMoveRightComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMoveRightComponent::Move(float AxisValue)
{
	/*
	//�E
	if (AxisValue > 0.0f)
	{
		FRotator NewRotation = FRotator(0.0f, 90.0f + _rotation, 0.0f);
		//�����̂�Yaw(Z����])�������Q�[���ɔ��f����Ȃ�
		//SetActorRotation(NewRotation);

		GetMesh()->SetWorldRotation(NewRotation);	//��p��
	}
	//��
	else if (AxisValue < 0.0f)
	{
		FRotator newRotation = FRotator(0.0f, 90.0f + (-_rotation), 0.0f);
		//SetActorRotation(NewRotation);

		GetMesh()->SetWorldRotation(newRotation);
	}
	else
	{
		FRotator newRotation = FRotator(0.0f, 90.0f, 0.0f);
		//SetActorRotation(NewRotation);

		GetMesh()->SetWorldRotation(newRotation);
	}
	*/

#if false
	// �E�����̃x�N�g�����擾���A���̕����Ɉړ�
	//���ݍ��W���擾
	FVector mypos = GetOwner()->GetActorLocation();
	//���ݍ��W������Z�����v�Z
	mypos.Y += AxisValue * _moveSpeed;
	//���ۂ̍��W�ɉ��Z
	GetOwner()->SetActorLocation(mypos);
#endif // false


	_ownerCharacter->AddMovementInput(_ownerCharacter->GetActorRightVector(), AxisValue);

}


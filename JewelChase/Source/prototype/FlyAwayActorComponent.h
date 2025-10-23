//--------------------------------------------------------------------
// �t�@�C����   �FFlyAwayActorComponent.h
// �T�v�@�@�@	�F������΂�����
// �쐬�ҁ@�@	�F�_�엮��
// �X�V���e�@	�F1/24 �쐬
//                1/26 ������΂������ƃt���O���t�ɂ��鏈���̍쐬
//                2/7  ������񂾎��Ԃ�����Destroy���鏈���̍쐬
//--------------------------------------------------------------------

// �C���N���[�h�K�[�h
#pragma once

// �C���N���[�h
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FlyAwayActorComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROTOTYPE_API UFlyAwayActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFlyAwayActorComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//----------------------------------
	// �֐����FChangeFlyFlag
	// ���@���F�Ȃ�
	// �߂�l�F�Ȃ�
	// ���@�e�F������΂��������s�����̃t���O���t�ɂ���
	//----------------------------------
	UFUNCTION(BlueprintCallable, Category = "Fly Settings")
	void ChangeFlyFlag();
private:
	// �R���|�[�l���g�̂��Ă���Actor
	UPROPERTY()
	AActor* _ownerActor;

	// �ړ��X�s�[�h
	UPROPERTY(EditAnywhere, Category = "Fly Settings")
	FVector _flySpeed;

	// �󂷎���
	UPROPERTY(EditAnywhere, Category = "Fly Settings")
	float _destroyTime;

	// ���ł��鎞��
	float _flyingTime;

	// ������΂����̃t���O
	bool _canFlyFlag;
};

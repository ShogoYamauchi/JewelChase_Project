//--------------------------------------------------------------------
// �t�@�C�����FBullet.h
// �T�v�@�@�@�F�e
// �쐬�ҁ@�@�F�����
// �X�V���e�@�F12/02
//--------------------------------------------------------------------
#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "prototype/Interface/IMovement.h"
#include "PlayerBullet.generated.h"

UCLASS()
class PROTOTYPE_API APlayerBullet final : public AActor , public IMovement
{
	GENERATED_BODY()
	
public:	
	APlayerBullet();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float deltaTime) override;

	//----------------------------------
	// �֐����FMove
	// ���@���Fvoid
	// �߂�l�Fvoid
	// �e�̓���
	//----------------------------------
	virtual void Move(float moveSpeed)override;

	void ChaseTarget(AActor* targetActor);

	//----------------------------------
	// �֐����FDestroyBullet
	// ���@���Ffloat
	// �߂�l�Fvoid
	// �e����������
	//----------------------------------
	void DestroyBullet(float deltaTime);

	//----------------------------------
	// �֐����FSetDirection
	// ���@���Ffloat
	// �߂�l�FFVector
	// �e��������������ݒ�
	//----------------------------------
	void SetDirection(FVector direction);

	void SetBulletAttack(int Attack);

	void SetTarget(AActor* target);

	int GetBulletAttack();

private:

	UPROPERTY()
	TObjectPtr<AActor> _target;

	//�e������������
	FVector _direction = FVector::ZeroVector;

	//�e�̑��x
	UPROPERTY(EditAnywhere)
	float _moveSpeed = 50.0f;

	//�����鎞��
	UPROPERTY(EditAnywhere)
	float _destroyTime = 2.0f;

	float _timer;

	UPROPERTY(EditAnywhere)
	int BulletAttack = 1;
};

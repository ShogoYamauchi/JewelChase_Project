//--------------------------------------------------------------------
// �t�@�C�����FBullet.cpp
// �T�v�@�@�@�F�e
// �쐬�ҁ@�@�F�����
// �X�V���e�@�F12/02
//--------------------------------------------------------------------

#include "PlayerBullet.h"
#include "Kismet/GameplayStatics.h"

APlayerBullet::APlayerBullet()
	: _target(nullptr)
	, _timer(0.0f)
{
	PrimaryActorTick.bCanEverTick = true;
}

void APlayerBullet::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerBullet::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	//if (_target && _target->GetWorld())
	//{
	//	ChaseTarget(_target);
	//}	�R��
	// �^�[�Q�b�g�����݂��邩�ۂ��@�R��
	if (IsValid(_target))// �R��
	{
		ChaseTarget(_target);
	}
	else
	{
		Move(_moveSpeed);
	}

	DestroyBullet(deltaTime);
}

void APlayerBullet::Move(float moveSpeed)
{
#if false
	//���ۂ̓���
	if (_targetPos == FVector::ZeroVector)
	{
		return;
	}
	FVector myPos = GetActorLocation();


#else
	//�e�X�g�p�̓���
	//FVector3f mypos = static_cast<FVector3f>(GetActorLocation());
	//mypos.X += moveSpeed;
	//SetActorLocation(static_cast<FVector>(mypos));

	SetActorLocation(GetActorLocation() + _direction * moveSpeed);

#endif // 0
}

void APlayerBullet::ChaseTarget(AActor* targetActor)
{
	const float VELOCITY_COMPENSTATION = 12.0f;	//���x�␳�l

	//�^�[�Q�b�g�����Ȃ���΍폜����
	if (!IsValid(_target))
	{
		this->Destroy();
	}

	// �^�[�Q�b�g������Ώ���
	if (_target && targetActor)
	{
		FVector targetLocation = targetActor->GetActorLocation();
		FVector myLocation = GetActorLocation();

		// �^�[�Q�b�g�����̐��K���x�N�g��
		FVector direction = (targetLocation - myLocation).GetSafeNormal();
		_direction = direction; //�R���i�^�[�Q�b�g�����݂���Ԃɔ�ԕ����������Ă����j

		// ���x���l�����Ĉړ�
		float deltaTime = GetWorld()->GetDeltaSeconds();
		SetActorLocation(myLocation + direction * (_moveSpeed + VELOCITY_COMPENSTATION));// �R���i�g�����v�̃X�s�[�h���x�������������j�������Ƃ���12����ԋ߂��X�s�[�h�ɂȂ�
	}
}

void APlayerBullet::DestroyBullet(float deltaTime)
{
	_timer += deltaTime;
	if (_timer >= _destroyTime)
	{
		_timer = 0.0f;
		this->Destroy();
	}
}

void APlayerBullet::SetDirection(FVector direction)
{
	_direction = direction;
}

void APlayerBullet::SetTarget(AActor* target)
{
	_target = target;
}

void APlayerBullet::SetBulletAttack(int Attack)
{
	BulletAttack = Attack;
}

int APlayerBullet::GetBulletAttack()
{
	return BulletAttack;
}
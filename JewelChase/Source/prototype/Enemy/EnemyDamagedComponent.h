//--------------------------------------------------------------------
// �t�@�C�����FEnemyDamagedComponent.h
// �T�v�@�@�@�F�G�̃_���[�W���󂯂�R���|�[�l���g�N���X
// �쐬�ҁ@�@�F�R���@����
// �X�V���e�@�F2024/11/29	�N���X�̍쐬 
//--------------------------------------------------------------------

#pragma once

#include "prototype/Interface/IDamaged.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyDamagedComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROTOTYPE_API UEnemyDamagedComponent : public UActorComponent
{
	// UE�̃I�u�W�F�N�g�N���X�ɕK���擪�ɏ����}�N��
	GENERATED_BODY()

protected:
	// �Q�[���X�^�[�g���A�܂��͐������ɌĂ΂�鏈��
	virtual void BeginPlay() override;

public:
	// �R���X�g���N�^
	UEnemyDamagedComponent();
	// ���t���[���̍X�V����
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// �_���[�W���󂯂���
	//void UpDateDamaged(float deltatime);

	// �_���[�W���󂯂�֐�
	void IsDamaged(int damage);
	// �_���[�W���o
	void IsDamagedEffect();


private:

	//UPROPERTY(EditAnywhere)
	//int	 PlayerAttackPower;		// �y�f�o�b�O�p�zPlayer�̍U���́@
};

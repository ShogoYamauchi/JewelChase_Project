//--------------------------------------------------------------------
// �t�@�C�����FEnemyDamagedComponent.cpp
// �T�v�@�@�@�F�G�̃_���[�W���󂯂�R���|�[�l���g�N���X
// �쐬�ҁ@�@�F�R���@����
// �X�V���e�@�F2024/11/29	�N���X�̍쐬 
//           �F2024/12/05	�����������炱�̃R���|�[�l���g����Ȃ������E�E�E
//--------------------------------------------------------------------

#include "EnemyDamagedComponent.h"

// Sets default values for this component's properties
UEnemyDamagedComponent::UEnemyDamagedComponent()
{
	// ���t���[���A���̃N���X��Tick()���ĂԂ��ǂ��������߂�t���O
	// �K�v�ɉ����āA�p�t�H�[�}���X����̂��߂ɐ؂邱�Ƃ��ł���B
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// �Q�[���X�^�[�g���A�܂��͐������ɌĂ΂�鏈��
void UEnemyDamagedComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...	
}

// ���t���[���̍X�V����
void UEnemyDamagedComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

// �֐����FIsDamagedEffect
// �����F
// �߂�l�F�Ȃ�
// 
void UEnemyDamagedComponent::IsDamagedEffect()
{
	;
}

//--------------------------------------------------------------------
// �t�@�C�����FEnemyDeadComponent.cpp
// �T�v�@�@�@�F���S���邽�߂̃R���|�[�l���g�N���X
// �쐬�ҁ@�@�F�R���@����
// �X�V���e�@�F2024/11/29	�N���X�̍쐬 
//--------------------------------------------------------------------

#include "EnemyDeadComponent.h"

// �R���X�g���N�^
UEnemyDeadComponent::UEnemyDeadComponent()
{
	// ���t���[���A���̃N���X��Tick()���ĂԂ��ǂ��������߂�t���O
	// �K�v�ɉ����āA�p�t�H�[�}���X����̂��߂ɐ؂邱�Ƃ��ł���B
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// �Q�[���X�^�[�g���A�܂��͐������ɌĂ΂�鏈��
void UEnemyDeadComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

// ���t���[���̍X�V����
void UEnemyDeadComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}


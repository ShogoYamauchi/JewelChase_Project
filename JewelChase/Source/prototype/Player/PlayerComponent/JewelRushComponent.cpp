//--------------------------------------------------------------------
//����ҁ@�F���@���
//��������F2024/12/23
//�ŏI�X�V�F2024/12/23
//�T�@�v�@�F�v���C���[JewelRush
//--------------------------------------------------------------------
#include "JewelRushComponent.h"

UJewelRushComponent::UJewelRushComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UJewelRushComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UJewelRushComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


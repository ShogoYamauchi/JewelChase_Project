//--------------------------------------------------------------------
//����ҁ@�F���@���
//��������F2024/12/23
//�ŏI�X�V�F2024/12/23
//�T�@�v�@�F�v���C���[JewelRush
//--------------------------------------------------------------------
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "JewelRushComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROTOTYPE_API UJewelRushComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UJewelRushComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};

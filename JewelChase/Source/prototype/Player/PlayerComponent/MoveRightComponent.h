//--------------------------------------------------------------------
//����ҁ@�F���@���
//��������F2024/12/23
//�ŏI�X�V�F2024/12/23
//�T�@�v�@�F�v���C���[�̓�������
//--------------------------------------------------------------------
#pragma once

#include "prototype/Interface/IMovement.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Character.h"
#include "MoveRightComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROTOTYPE_API UMoveRightComponent : public UActorComponent, public IMovement
{
	GENERATED_BODY()
	//
public:
	UMoveRightComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Move(float AxisValue) override;

private:
	UPROPERTY()
	TObjectPtr<ACharacter> _ownerCharacter = nullptr;

	UPROPERTY(EditAnywhere)
	float _moveSpeed = 7.0f;

};

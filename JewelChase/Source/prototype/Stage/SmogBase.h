//--------------------------------------------------------------------
// �t�@�C���� �FSmogBase.h
// �T�v       �F���̊�Ղ̃N���X�B
// �쐬��     �F0231�{��
// �X�V���e   �F1/19�@�쐬
//--------------------------------------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SmogBase.generated.h"

UCLASS()
class PROTOTYPE_API ASmogBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASmogBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	AActor* pStageMng;
	float moveSpeed;
};

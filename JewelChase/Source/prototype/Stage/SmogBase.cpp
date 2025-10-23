//--------------------------------------------------------------------
// �t�@�C���� �FSmogBase.cpp
// �T�v       �F���̊�Ղ̃N���X�B
// �쐬��     �F0231�{��
// �X�V���e   �F1/19�@�쐬
//--------------------------------------------------------------------


#include "SmogBase.h"
#include "prototype/Stage/StageManager.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASmogBase::ASmogBase()
	: moveSpeed(0)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASmogBase::BeginPlay()
{
	Super::BeginPlay();
	
	//AStageManager�^�̃I�u�W�F�N�g��T���A�Ǘ�
	TSubclassOf<AStageManager> findClass;
	findClass = AStageManager::StaticClass();

	pStageMng = UGameplayStatics::GetActorOfClass(GetWorld(), findClass);

	if (IsValid(pStageMng))
	{
		moveSpeed = Cast<AStageManager>(pStageMng)->Get_movespeed();
	}
}

// Called every frame
void ASmogBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector pos = GetActorLocation();

	if (pos.X > -1000.0f)
	{
		FVector newpos = FVector(pos.X - moveSpeed, pos.Y, pos.Z);

		SetActorLocation(newpos);
	}
	else
	{
		FVector newpos = FVector(5000.0f, pos.Y, pos.Z);

		SetActorLocation(newpos);
	}
}


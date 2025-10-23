//--------------------------------------------------------------------
// �t�@�C���� �FItemBase.cpp
// �T�v       �F�A�C�e���̊�Ղ̃N���X�B�@�\�͓��ɂȂ�
// �쐬��     �F0231�{��
// �X�V���e   �F1/19�@�쐬
//--------------------------------------------------------------------


#include "ItemBase.h"

// Sets default values
AItemBase::AItemBase()
	:bget(false)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AItemBase::BeginPlay()
{
	Super::BeginPlay();

	SetBeginZpos();
}

// Called every frame
void AItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bget) 
	{
		UptoDestroy();
	}
}

void AItemBase::SetBeginZpos()
{
	BeginZpos = GetActorLocation().Z;
}

float AItemBase::GetBeginZpos()
{
	return BeginZpos;
}

void AItemBase::bgetON()
{
	bget = true;
	getZpos = GetActorLocation().Z;
}

void AItemBase::UptoDestroy()
{
	FVector pos = GetActorLocation();
	SetActorLocation(FVector(pos.X, pos.Y, pos.Z + 10.0f));

	if (GetActorLocation().Z > getZpos + 150.0f)
	{
		Destroy();
	}
}
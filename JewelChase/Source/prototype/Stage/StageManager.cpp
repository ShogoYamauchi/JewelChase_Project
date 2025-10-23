//--------------------------------------------------------------------
// �t�@�C���� �FStageManager.cpp
// �T�v       �F�X�e�[�W�����ׂ̈̔ԍ��Acsv�p�X���Ǘ�����N���X
// �쐬��     �F0231�{��
// �X�V���e   �F11/29�@�쐬�A
//--------------------------------------------------------------------
#include "StageManager.h"
#include "prototype/Player/PlayerCharacter.h"
#include "prototype/Stage/ItemBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AStageManager::AStageManager()
	:_bgoalspawn(false)
	, toDefaultAddZpos(0.0f)
	, bItemsFloating(true)
	, bMagnet(false)
	, magnetTime(0.0f)
	, _bStart(false)
	, _bGoal(false)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	srand(time(NULL));
}

// Called when the game starts or when spawned
void AStageManager::BeginPlay()
{
	Super::BeginPlay();

	//BP�̃v���p�e�B�Őݒ肵�����[�������V���傫��������
	if (_stagelane > 7) { _stagelane = 7; }
}

// Called every frame
void AStageManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateFloating();

	approachItem(DeltaTime);
}

// �֐����FGet_csvpass
// ���@���F�Ȃ�
// �߂�l�FTSoftObjectPtr<UDataTable>
// �������e�F���ɐ�������X�e�[�W��csv�p�X��Ԃ�
TSoftObjectPtr<UDataTable> AStageManager::Get_csvpath()
{
	_stagenum++;
	return _csvpath[_stagenum - 1];
}

// �֐����FGet_goalpath
// ���@���F�Ȃ�
// �߂�l�FTSoftObjectPtr<UDataTable>
// �������e�F�S�[���I�u�W�F�N�g��z�u�����X�e�[�W��csv�p�X��Ԃ�
TSoftObjectPtr<UDataTable> AStageManager::Get_goalpath()
{
	_bgoalspawn = true;
	return _goalpath;
}

// �֐����FGet_stagenum
// ���@���F�Ȃ�
// �߂�l�Fint16
// �������e�F�X�e�[�W�ԍ���Ԃ�
int32 AStageManager::Get_stagenum()
{
	return _stagenum;
}

// �֐����FGet_maxstagenum
// ���@���F�Ȃ�
// �߂�l�Fint16
// �������e�F�ő�X�e�[�W�ԍ���Ԃ�
int32 AStageManager::Get_maxstagenum()
{
	return _maxstagenum;
}

// �֐����FGet_stagelane
// ���@���F�Ȃ�
// �߂�l�Fint8
// �������e�F�X�e�[�W�̃��[������Ԃ�
int8 AStageManager::Get_stagelane()
{
	return _stagelane;
}

// �֐����FGet_movespeed
// ���@���F�Ȃ�
// �߂�l�Ffloat
// �������e�F�X�e�[�W�̈ړ����x��Ԃ�
float AStageManager::Get_movespeed()
{
	return _movespeed;
}

// �֐����FGet_bgoalspawn
// ���@���F�Ȃ�
// �߂�l�Fbool
// �������e�F�S�[���X�e�[�W���X�|�[����������Ԃ�
bool AStageManager::Get_bgoalspawn()
{
	return _bgoalspawn;
}

// �֐����FUpdateFloating
// ���@���F�Ȃ�
// �߂�l�F�Ȃ�
// �������e�F�A�C�e���̕��V���X�V����
void AStageManager::UpdateFloating()
{
	if (bItemsFloating)
	{
		toDefaultAddZpos += zmoveLength;

		if (toDefaultAddZpos > 25.0f) {
			toDefaultAddZpos = 25.0f;
			bItemsFloating = false;
		}
	}
	else
	{
		toDefaultAddZpos -= zmoveLength;

		if (toDefaultAddZpos < -25.0f) {
			toDefaultAddZpos = -25.0f;
			bItemsFloating = true;
		}
	}

	for (auto Item : Items)
	{
		if (IsValid(Item) && !Cast<AItemBase>(Item)->Getbget())
		{
			FVector beforepos = Item->GetActorLocation();
			FVector newpos = FVector(beforepos.X, beforepos.Y, Cast<AItemBase>(Item)->GetBeginZpos() + toDefaultAddZpos);

			Item->SetActorLocation(newpos);
		}
	}
}

// �֐����FSetItems
// ���@���FTArray<AActor*>
// �߂�l�F�Ȃ�
// �������e�FUpdateFloating()�ōX�V����A�C�e�����X�e�[�W�x�[�X����󂯎��
void AStageManager::SetItems(TArray<AActor*> Others)
{
	Items = Others;
}

// �֐����F_bMagnetOn
// ���@���F�Ȃ�
// �߂�l�F�Ȃ�
// �������e�F�}�O�l�b�g���擾�����Ƃ��ɃA�C�e�����߂Â�����
//			 bool�^��true�ɂ���
void  AStageManager::_bMagnetOn()
{
	bMagnet = true;
}

// �֐����FapproachItem
// ���@���Ffloat DeltaTime
// �߂�l�F�Ȃ�
// �������e�F�}�O�l�b�g���擾���Ă���Ƃ��ɃA�C�e�����v���C���ɐڋ߂�����
void AStageManager::approachItem(float DeltaTime)
{
	if (bMagnet) {
		TSubclassOf<APlayerCharacter> findClass;
		findClass = APlayerCharacter::StaticClass();

		AActor* pPlayer = UGameplayStatics::GetActorOfClass(GetWorld(), findClass);
		FVector PlayerLocation = pPlayer->GetActorLocation();

		float DistanceX;
		float DistanceY;
		float DistanceZ;
		float Distancetotal;

		for (auto Item : Items)
		{
			if (IsValid(Item) && Item->GetActorLocation().X < 1500.0f && !Cast<AItemBase>(Item)->Getbget()) {
				FVector ItemLocation = Item->GetActorLocation();

				DistanceX = PlayerLocation.X - ItemLocation.X;
				DistanceY = PlayerLocation.Y - ItemLocation.Y;
				DistanceZ = PlayerLocation.Z - ItemLocation.Z;

				Distancetotal = abs(DistanceX) + abs(DistanceY) + abs(DistanceZ);

				float SetXpos = ItemLocation.X - (abs(DistanceX) / Distancetotal) * magnetmoveLength;

				float SetYpos;

				if (DistanceY > 0.0f) SetYpos = ItemLocation.Y + (abs(DistanceY) / Distancetotal) * magnetmoveLength;
				else SetYpos = ItemLocation.Y - (abs(DistanceY) / Distancetotal) * magnetmoveLength;

				float SetZpos = ItemLocation.Z;

				if (DistanceZ < 0.0f) SetZpos = ItemLocation.Z - (abs(DistanceZ) / Distancetotal) * magnetmoveLength * 5.0;
				else  SetZpos = ItemLocation.Z + (abs(DistanceZ) / Distancetotal) * magnetmoveLength * 2.35;
				

				FVector newItemLocation = FVector(SetXpos, SetYpos, SetZpos);

				Item->SetActorLocation(newItemLocation);
			}
		}

		magnetTime += DeltaTime;

		if (magnetTime > 5.0f)
		{
			bMagnet = false;
			magnetTime = 0.0f;

			for (auto Item : Items)
			{
				if (IsValid(Item))
				{
					Cast<AItemBase>(Item)->SetBeginZpos();
				}
			}
		}
	}
}


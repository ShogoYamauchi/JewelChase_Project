//--------------------------------------------------------------------
// �t�@�C���� �FStageBase.h
// �T�v       �F�X�e�[�W�i��Q����G�j�̐����𐧌䂷��N���X
// �쐬��     �F0231�{��
// �X�V���e   �F11/25�@�쐬�A�v���p�e�B�ƃ��\�b�h���쐬
//--------------------------------------------------------------------
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StageBase.generated.h"

UCLASS()
class PROTOTYPE_API AStageBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AStageBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	void SpawnObject();

	void CommonSpawn(float xPos);

	void SpawnEnemy();

	void SpawnNextStage();

	void Move();

	void DeleteStage();

	AActor* SearchStageMng();

private:
	//���̃X�e�[�W���X�|�[�����������̊m�F�p
	bool _bspawnstage;

	//�}�b�v�ړ����x
	float _movespeed;

	int8 _stagelane; //�X�e�[�W�}�l�[�W������擾

	TSoftObjectPtr<UDataTable> StageDataTable;

	UPROPERTY()
	AActor* pStageMng;

	AActor* pPlayer;

	//BP�|�C���^
	UPROPERTY(EditAnywhere, Category = "Common")//�X�e�[�W���ʃI�u�W�F�N�g�@�S�[����99
		TSubclassOf<class AActor> _commons[6];
	UPROPERTY(EditAnywhere, Category = "obstacles")//��Q���@1�`10
		TSubclassOf<class AActor> _obstacles[10];
	UPROPERTY(EditAnywhere, Category = "Jewel")//�W���G���@11�`20
		TSubclassOf<class AActor>  _jewels[5];
	UPROPERTY(EditAnywhere, Category = "Item")//�A�C�e���@21�`30
		TSubclassOf<class AActor>  _Items[7];
	UPROPERTY(EditAnywhere, Category = "enemy")//�G�l�~�[�@31�`40
		TSubclassOf<class AActor> _enemys[3];
};

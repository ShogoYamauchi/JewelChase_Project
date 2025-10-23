//--------------------------------------------------------------------
// �t�@�C���� �FStageManager.h
// �T�v       �F�X�e�[�W�����ׂ̈̔ԍ��Acsv�p�X���Ǘ�����N���X
// �쐬��     �F0231�{��
// �X�V���e   �F11/29�@�쐬�A
//--------------------------------------------------------------------
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StageData.h"
#include "StageManager.generated.h"

UCLASS()
class PROTOTYPE_API AStageManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AStageManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void UpdateFloating();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	TSoftObjectPtr<UDataTable> Get_csvpath();
	TSoftObjectPtr<UDataTable> Get_goalpath();

	UFUNCTION(BlueprintCallable)
	int32 Get_stagenum();
	UFUNCTION(BlueprintCallable)
	int32 Get_maxstagenum();

	int8 Get_stagelane();
	UFUNCTION(BlueprintCallable)
	float Get_movespeed();
	bool Get_bgoalspawn();
	
	void SetItems(TArray<AActor*> Others);

	UFUNCTION(BlueprintCallable)
	void  _bMagnetOn();

	void approachItem(float DeltaTime);

	UFUNCTION(BlueprintCallable)
	void _bStartON() { _bStart = true; }

	UFUNCTION(BlueprintCallable)
	bool get_bStart()const { return _bStart; }

	UFUNCTION(BlueprintCallable)
	void _bGoalON()	{_bGoal = true;	}

	UFUNCTION(BlueprintCallable)
	bool get_bGoal()const{return _bGoal;	}

	// �Ë�����
	void SetHeliStatus(int other) {

		_BeginHeliState = other;
		UE_LOG(LogTemp, Log, TEXT("set_BeginHeliState=[%d]"), _BeginHeliState);
	}

	int GetHeliStatus() {
		UE_LOG(LogTemp, Log, TEXT("get_BeginHeliState=[%d]"), _BeginHeliState);
		return _BeginHeliState;
	}

private:
	UPROPERTY(EditAnywhere, meta = (EditCondition = "Data"))
	int32 _maxstagenum;					    //�ő�X�e�[�W�ԍ�
	UPROPERTY(EditAnywhere, meta = (EditCondition = "Data"))
	float _movespeed;					    //�X�e�[�W�S�̂̈ړ����x
	UPROPERTY(EditAnywhere, meta = (EditCondition = "Data"))
	int8 _stagelane;					    //�X�e�[�W�S�̂̉��̃��[����
	UPROPERTY(EditAnywhere, meta = (EditCondition = "Data"))
	TSoftObjectPtr<UDataTable> _csvpath[100];//���ɐ�������X�e�[�W��csv�p�X
	UPROPERTY(EditAnywhere, meta = (EditCondition = "Data"))
	TSoftObjectPtr<UDataTable> _goalpath;//�S�[���X�e�[�W��csv�p�X
	UPROPERTY(EditAnywhere, meta = (EditCondition = "Data"))
	float zmoveLength;//�A�C�e�����㉺�ɕ��V���鑬�x
	UPROPERTY(EditAnywhere, meta = (EditCondition = "Data"))
	float magnetmoveLength;//�A�C�e�����㉺�ɕ��V���鑬�x

	UPROPERTY()
	TArray<AActor*> Items;//�X�e�[�W��̃A�C�e�����擾
	float toDefaultAddZpos;//���V���̃|�W�V������ݒ�
	bool bItemsFloating;//�オ�邩�����邩

	bool bMagnet;

	float magnetTime;

	bool _bgoalspawn;//���łɃS�[�����X�|�[��������

	int32 _stagenum;//�X�e�[�W�ԍ�

	int _BeginHeliState;	// �Ë�����

	bool _bStart;

	bool _bGoal;
};

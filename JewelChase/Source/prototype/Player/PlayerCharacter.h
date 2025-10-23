//--------------------------------------------------------------------
//����ҁ@�F���@���
//��������F2024/11/22
//�ŏI�X�V�F2025/02/10
//�T�@�v�@�F�v���C���[�̃x�[�X����
//--------------------------------------------------------------------

#pragma once

#pragma region interface
#include "IMovement.h"
#include "IDamaged.h"
#include "IDead.h"
#include "IBulletFactory.h"
#pragma endregion
#include "SEManager.h"
#include "PlayerBullet.h"
#include "PlayerSEData.h"
#include "Components/CapsuleComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"
#include "PlayerCharacter.generated.h"

UENUM(BlueprintType)
enum class PlayerStatus : uint8
{
	Idle UMETA(DisplayName = "Idle"),
	Running UMETA(DisplayName = "Running"),
	Jumping UMETA(DisplayName = "Jumping"),
	Damaged UMETA(DisplayName = "Damaged"),
	Invincible UMETA(DisplayName = "Invincible"),
	Die UMETA(DisplayName = "Die"),
	Uncontroll UMETA(DisplayName = "Uncontroll"),
	Goal UMETA(DisplayName = "Goal")
};

class UBlinkingComponent;
class UPlayerHitByPoliceCarComponent;
class UJustJumpActorComponent;

UCLASS()
class PROTOTYPE_API APlayerCharacter final : public ACharacter, public IMovement, public IBulletFactory, public IDamaged, public IDead
{
	GENERATED_BODY()

public:
	APlayerCharacter();

protected:
	virtual void BeginPlay() override;

public:

	virtual void Tick(float deltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* playerInputComponent) override;

	//----------------------------------
	// �֐����FOnOverlapBegin
	// ���@���FUPrimitiveComponent* ,AActor* ,UPrimitiveComponent* ,FVector ,FHitResult&
	// �߂�l�Fvoid
	// ���������u�Ԃɏ�������֐�
	//----------------------------------
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

#pragma region JumpFunction
	//�Q�[�v���̂܂�
	void UpdateJump(float deltaTime);
	void JumpStart();
	void JumpEnd();
	//animation�������������Ȃ����炲�艟��
	//�W�����v��̍d��
	void Jumprigor();
#pragma endregion

	//----------------------------------
	// �֐����FMove
	// ���@���Ffloat
	// �߂�l�Fvoid
	// ���ړ��̊֐�
	//----------------------------------
	virtual void Move(float moveSpeed) override;

	//----------------------------------
	// �֐����FPlayerPosControl
	// ���@���F����
	// �߂�l�Fvoid
	// ���ړ��̊֐�
	//----------------------------------
	void PlayerPosControl();

	//----------------------------------
	// �֐����FIsDamaged
	// ���@���Fint
	// �߂�l�Fvoid
	// �_���[�W���󂯂��ۂ̊֐�
	//----------------------------------
	/*UFUNCTION(BlueprintCallable, Category = "Transformation")
	virtual void IsDamaged(int damage)override;*/
	void IsDamaged(int damage)override;

	//----------------------------------
	// �֐����FIDead
	// ���@���Fint
	// �߂�l�Fvoid
	// ���ʂƂ��̏���
	//----------------------------------
	virtual void Dead()override;

	//----------------------------------
	// �֐����FInvincibleTime
	// ���@���F����
	// �߂�l�Fvoid
	// �_���[�W��̖��G����
	//----------------------------------
	UFUNCTION(BlueprintCallable)
	void InvincibleTime();

	void InvincibleTimeEnd();

#pragma region MouseFunction
	//----------------------------------
	// �֐����FSetMouseCursor
	// ���@���F����
	// �߂�l�Fvoid
	// �J�[�\����\������֐�
	//----------------------------------
	void ShowMouseCursor();

	//----------------------------------
	// �֐����FMouseRangeControl
	// ���@���F����
	// �߂�l�Fvoid
	// �J�[�\���̈ړ��͈͂𐧌䂷��֐�
	//----------------------------------
	void MouseRangeControl();
#pragma endregion

#pragma region BulletFunction
	//----------------------------------
	// �֐����FGetViewToWorldPos
	// ���@���FFVector& ,FVector&
	// �߂�l�Fbool
	// �J�[�\���̃X�N���[�����W�����[���h���W�ɕϊ����Ԃ��֐�
	//----------------------------------
	bool GetViewToWorldPos(FVector& location, FVector& direction);

	//----------------------------------
	// �֐����FSpawnBullet
	// ���@���F����
	// �߂�l�Fvoid
	// �g�����v�𐶐�����֐�
	//----------------------------------
	virtual void SpawnBullet()override;

	//----------------------------------
	// �֐����FReloadBulletTimer
	// ���@���F����
	// �߂�l�Fvoid
	// �e�������[�h����܂ł̏���
	//----------------------------------
	void ReloadBulletTimer();

	//----------------------------------
	// �֐����FReloadBullet
	// ���@���F����
	// �߂�l�Fvoid
	// �e�������[�h����֐�
	//----------------------------------
	UFUNCTION(BlueprintCallable)
	void ReloadBullet();

#pragma endregion 

	//----------------------------------
	// �֐����FJewelRushStart
	// ���@���F����
	// �߂�l�Fvoid
	// ���b�V���̍ŏ��ɂ��Ă����������Ƃ���������
	//----------------------------------
	void JewelRushStart();

	//----------------------------------
	// �֐����FJewelRushTime
	// ���@���F����
	// �߂�l�Fvoid
	// ���b�V����
	//----------------------------------
	void JewelRushTime();

	//----------------------------------
	// �֐����FJewelRushEnd
	// ���@���F����
	// �߂�l�Fvoid
	// ���b�V���̍Ō�ɂ��Ă����������Ƃ���������
	//----------------------------------
	void JewelRushEnd();

	//----------------------------------
	// �֐����FJewelRushBlinking
	// ���@���F����
	// �߂�l�Fvoid
	// ���b�V�����ɓ_�ł�����֐�
	//----------------------------------
	void ToggleMaterial();

	//�t���O��؂�ւ���֐�
	void ChangeOnBlinkingFlag();

	//----------------------------------
	// �֐����FSpawnParticleEffect
	// ���@���F����
	// �߂�l�Fvoid
	// �p�[�e�B�N���𐶐�����֐�
	//----------------------------------
	void SpawnParticleEffect(FVector offset);

	//----------------------------------
	// �֐����FRegisterSE
	// ���@���F����
	// �߂�l�Fvoid
	// SE��SEManager�ɓo�^����֐�
	//----------------------------------
	void RegisterSE();

	UFUNCTION(BlueprintCallable, Category = "GetFunctions")
	PlayerStatus GetPlayerStatus()const { return MyStatus; }

	UFUNCTION(BlueprintCallable, Category = "SetFunctions")
	void SetPlayerStatus(PlayerStatus status) { MyStatus = status; }

	UFUNCTION(BlueprintCallable, Category = "GetFunctions")
	float GetReloadBulletTime()const { return _reloadBulletTime; }

	UFUNCTION(BlueprintCallable, Category = "GetFunctions")
	float GetBulletAttack()const { return _bulletAttack; }

	//���݂̃W���G���Q�[�W���擾
	UFUNCTION(BlueprintCallable, Category = "GetFunctions")
	uint8 GetJewelRushgageNum()const { return _jewelRushGageNum; }
	//�W���G���Q�[�W�̍ő吔���擾
	UFUNCTION(BlueprintCallable, Category = "GetFunctions")
	uint8 GetJewelRushgageMaxNum()const { return _jewelRushGageMaxNum; }

	//�c�e�����擾
	UFUNCTION(BlueprintCallable, Category = "GetFunctions")
	uint8 GetLimitBulletNum()const { return _limitBulletNum; }
	//�c�e���̏����l���擾
	UFUNCTION(BlueprintCallable, Category = "GetFunctions")
	uint8 GetInitialLimitBulletNum()const { return _initialLimitBulletNum; }

#pragma region HP
	UFUNCTION(BlueprintGetter, Category = "GetFunctions")
	uint8 GetHP()const { return _hp; }
	UFUNCTION(BlueprintSetter, Category = "SetFunctions")
	void SetHP(uint8 hp) {
		if (hp >= _MAX_HP)
		{
			return;
		}
		_hp = hp;
	}

	UFUNCTION()
	void AddHP(uint8 addHp) {
		if ((_hp + addHp) > _MAX_HP)
		{
			return;
		}
		_hp += addHp;
	}
#pragma endregion

	UFUNCTION(BlueprintCallable, Category = "GetFunctions")
	bool GetisJewelRush()const { return _isJewelRush; }

	UFUNCTION(BlueprintCallable, Category = "GetFunctions")
	bool GetIsAttack()const { return _isAttack; }

	UFUNCTION(BlueprintCallable, Category = "GetFunctions")
	bool GetIsJumping()const { return _isJumping; }


	UPROPERTY(BlueprintReadWrite, Category = "PlayerStatus")
	PlayerStatus MyStatus;		//�v���C���[�̏��

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet")
	TSubclassOf<class APlayerBullet> PlayerBulletClass;		//��������e�̃N���X

	// JJ��Perfect�̂Ƃ���UI
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> WBP_JJPerfectClass;

private:
	/*
	UPROPERTY(EditAnywhere, Category = "Data")
	TSoftObjectPtr<UDataTable> _playerDataTable;	//�v���C���[��SE

	FPlayerSE _data;	//SE�f�[�^
	*/
#pragma region JewelRushMaterial
	// JewelRush���̃}�e���A��
	UPROPERTY(EditAnywhere, Category = "Materials")
	TObjectPtr<UMaterialInterface> _jewelRushMaterial0;
	UPROPERTY(EditAnywhere, Category = "Materials")
	TObjectPtr<UMaterialInterface> _jewelRushMaterial1;

	// ���̃}�e���A����ۑ�����
	UPROPERTY()
	TObjectPtr<UMaterialInterface> _originalMaterial0;
	UPROPERTY()
	TObjectPtr<UMaterialInterface> _originalMaterial1;
#pragma endregion

	UPROPERTY(EditAnywhere)
	TObjectPtr<UPlayerHitByPoliceCarComponent> _pPlayerHitByPoliceCarComponent = nullptr;		//�x�@�̓��������̏������s�����߂̃R���|�[�l���g

	UPROPERTY(EditAnywhere)
	TObjectPtr<UBlinkingComponent> _pBlinkingComponent = nullptr;		//�_�ł����邽�߂̃R���|�[�l���g

	UPROPERTY(EditAnywhere)
	TObjectPtr<UJustJumpActorComponent> _pJustJumpActorComponent = nullptr;		//�W���X�g�W�����v�̏������s�����߂̃R���|�[�l���g

#pragma region Sound

	//TMap ���g���� SE ���Ǘ�
	UPROPERTY(EditAnywhere, Category = "Sound")
	TMap<FName, TObjectPtr<USoundBase>> _seMap;		//SE�̃}�b�v

	UPROPERTY()
	TObjectPtr<USEManager> _seManager = nullptr;	//SEManager

	UPROPERTY(EditAnywhere, Category = "Effects")
	TObjectPtr<UParticleSystem> _jewelRushEffect = nullptr;		//�W���G�����b�V�����̃G�t�F�N�g
#pragma endregion

	UPROPERTY();
	TObjectPtr<UCapsuleComponent> _capsuleComponent;	//���g�̃J�v�Z���R���|�[�l���g

	UPROPERTY(EditAnywhere, meta = (AllowPreserveRatio), Category = "Bullet")
	FVector _bulletOffsetPos;	//�e�̐����ʒu
	FVector _beforeJumpPos;		//�W�����v����O�̍��W

	UPROPERTY(EditAnywhere, Category = "Bullet")
	FVector _offsetBulletPos = FVector(0.10, 0.0, -0.10);	//�e�̐����ʒu

	UPROPERTY(EditAnywhere, meta = (AllowPreserveRatio), Category = "Cursor")
	FVector2D _maxCursorPos = FVector2D(1920.0, 700.0);		//�J�[�\���̍ő�ړ��͈�
	UPROPERTY(EditAnywhere, meta = (AllowPreserveRatio), Category = "Cursor")
	FVector2D _minCursorPos = FVector2D(0.0, 0.0);		//�J�[�\���̍ŏ��ړ��͈�

	FName _jewelName[4] = { "Jewel_blue","Jewel_red","Jewel_yellow","Jewel_purple" };	//�W���G���̖��O

	UPROPERTY(EditAnywhere, Category = "Move")
	float _rotation = 35.0f;	//�ړ�����ۂ̉�]�p�xZ(Yaw)
	UPROPERTY(EditAnywhere, Category = "Move")
	float _moveSpeed = 7.0f;	//�ړ����x

	UPROPERTY(EditAnywhere, Category = "Move")
	float _maxPosY = 500.0f;	//�ő�ړ�����
	UPROPERTY(EditAnywhere, Category = "Move")
	float _minPosY = -500.0f;	//�ő�ړ�����

#pragma region Jump
	UPROPERTY(EditAnywhere, Category = "Jump")
	float _jumpPower = 1000.0f;		//�W�����v��
	float _jumpTime;						//
	UPROPERTY(EditAnywhere, Category = "Jump")
	float _gravity = 2000.0f;	//�d��

	UPROPERTY(EditAnywhere, Category = "Jump")
	float _jumpRigorTime = 0.2f;	//�W�����v��̍d������
#pragma endregion	

	UPROPERTY(EditAnywhere)
	float _invincibleTime = 2.0f;	//���G����

	UPROPERTY(EditAnywhere, Category = "JewelRush")
	float _jewelRushTime = 10.0f;	//�W���G�����b�V�����s������
	UPROPERTY(EditAnywhere, Category = "JewelRush")
	float _blinkingStartTime = 7.0f;		//�W���G�����b�V�����̓_�Ŏ���
	float _toggleTime = 0.2f;					//�_�ł̊Ԋu
	const float _initialToggleTime = _toggleTime;	//�����̓_�ł̊Ԋu

	UPROPERTY(EditAnywhere, Category = "Bullet")
	float _reloadBulletTime = 2.0f;		//�e�̃����[�h����

	UPROPERTY(EditAnywhere, Category = "Color")
	FColor _color = FColor::Red;

	UPROPERTY(EditAnywhere, Category = "Bullet", Meta = (ClampMin = "0", ClampMax = "5", UIMin = "0", UIMax = "13"))
	uint8 _limitBulletNum = 13u;	//�c�e��

	uint8 _initialLimitBulletNum;	//�ŏ��̒e�̒e����ێ�

	UPROPERTY(EditAnywhere, Category = "Bullet")
	uint8 _bulletAttack = 1u;	//�e�̍U����

	uint8 _initialBulletAttack;		//�ŏ��̒e�̍U���͂�ێ�

	UPROPERTY(EditAnywhere, Category = "JewelRush")
	uint8 _jewelRushBulletAttack = 2u;	//���b�V�����̍U����

	uint8 _jewelRushGageNum;					//���݂̃��b�V���Q�[�W
	UPROPERTY(EditAnywhere, Category = "JewelRush")
	uint8 _jewelRushGageMaxNum = 100u;	//�ő僉�b�V���Q�[�W��

	uint8 _jewelRushGageIncrementNum[4] = { 1u,5u,10u,30u };	//�W���G�����Ƃ̃Q�[�W������

#pragma region HP
	//BP��hp��get��set���ł���悤�ɂȂ�
	UPROPERTY(EditAnywhere, Category = "HP", BlueprintGetter = GetHP, BlueprintSetter = SetHP, meta = (ClampMin = "0", ClampMax = "5"))
	uint8 _hp = 3u;		//�̗�
	const uint8 _MAX_HP = 5u;	//�ő�̗�

#pragma endregion

	bool _isJumping;			//�W�����v�ł��邩
	bool _canControl;			//���͂ł��邩
	bool _isReload;				//�����[�h����
	bool _isJewelRush;			//�W���G�����b�V������
	bool _isInvincible;			//���G���Ԓ���
	bool _isAttack;				//�U������

	bool _isJumpRigor;			//�W�����v��̍d������
	bool _isBlinking;			//�_�ł�؂�ւ���
	bool _onBlinking;			//�_�Œ���
};

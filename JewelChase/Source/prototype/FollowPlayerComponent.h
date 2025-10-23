//--------------------------------------------------------------------
// �t�@�C����	�FFollowPlayerComponent.h
// �T�v�@�@�@	�F�v���C���[��Ǐ]����R���|�[�l���g
// �쐬�ҁ@�@	�F�_�엮��
// �X�V���e�@	�F1/17 �쐬
//                     �v���C���[��Ǐ]���铮��ŕK�v�ȍ��W���i�[����ϐ��Ɗ֐��̐錾
//                     ���o���̃t���O��錾
//				  1/19 �J�����̕�ԑ��x��錾
//--------------------------------------------------------------------

// �C���N���[�h�K�[�h
#pragma once

// �C���N���[�h
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FollowPlayerComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROTOTYPE_API UFollowPlayerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFollowPlayerComponent();
	~UFollowPlayerComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//----------------------------------
	// �֐����FChangeIsDirectionFlag
	// ���@���F�Ȃ�
	// �߂�l�F�Ȃ�
	// ���@�e�F���o�������Ǘ�����t���O���t�ɂ���֐�
	//----------------------------------
	UFUNCTION(BlueprintCallable, Category = "FollowPlayerComponent")
	void ChangeIsDirectionFlag();

	//----------------------------------
	// �֐����FSetPlayerPawn
	// ���@���F�Ȃ�
	// �߂�l�F�Ȃ�
	// ���@�e�F�v���C���[��Pawn���擾����֐�
	//----------------------------------
	void SetPlayerPawn();

private:
	//----------------------------------
	// �֐����FFollowPlayer
	// ���@���F�Ȃ�
	// �߂�l�F�Ȃ�
	// ���@�e�F�v���C���[��Ǐ]�����鏈���̊֐�
	//----------------------------------
	void FollowPlayer();

	// �v���C���[��Pawn
	UPROPERTY()
	APawn* _playerPawn;

	// ���̃R���|�[�l���g�����Ă���Actor�̍��W
	FVector _currentLocation;
	// �v���C���[�̍��W
	FVector _playerLocation;

	// �J�����̕�ԑ��x�i���̒l����������Ώ������قǂ�����蓮���j
	UPROPERTY(EditAnywhere)
	float _cameraMoveSpeed;

	// ���o���Ȃ̂����Ǘ�����t���O
	bool _isDirectionFlag;
};
//--------------------------------------------------------------------
// �t�@�C�����FFollowPlayerComponent.h
// �T�v�@�@�@�F�v���C���[��Ǐ]����R���|�[�l���g
// �쐬�ҁ@�@�F�_�엮��
// �X�V���e�@�F1/17 �쐬
//				    �v���C���[��Ǐ]���铮��Ɋւ���ϐ��Ɗ֐��̍쐬�i�������j
//                  ���o�������Ǘ�����t���O�̕ύX���s���֐��̒�`
//             1/19 ���o�������Ǘ�����t���O���t�ɂ���֐��̓��e��ύX
//                  �v���C���[��Ǐ]�����鏈���̊֐��̓��e��ύX
//--------------------------------------------------------------------

// �C���N���[�h
#include "FollowPlayerComponent.h"
#include "Kismet/GameplayStatics.h"

UFollowPlayerComponent::UFollowPlayerComponent()
	: _playerPawn(nullptr)
	, _isDirectionFlag(true)
{
	PrimaryComponentTick.bCanEverTick = true;
}

UFollowPlayerComponent::~UFollowPlayerComponent()
{
}

void UFollowPlayerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ���̃R���|�[�l���g�����Ă���Actor�̍��W��ϐ��Ɋi�[����
	_currentLocation = GetOwner()->GetActorLocation();

	// �^�[�Q�b�g��ݒ肷��
	SetPlayerPawn();
}

void UFollowPlayerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// �v���C���[��Ǐ]���鏈��
	if (_isDirectionFlag == false)
	{
		FollowPlayer();
	}
}

//----------------------------------
// �֐����FChangeIsDirectionFlag
// ���@���F�Ȃ�
// �߂�l�F�Ȃ�
// ���@�e�F���o�������Ǘ�����t���O���t�ɂ���֐�
//----------------------------------
void UFollowPlayerComponent::ChangeIsDirectionFlag()
{
	_isDirectionFlag = !_isDirectionFlag;
}

//----------------------------------
// �֐����FSetPlayerPawn
// ���@���F�Ȃ�
// �߂�l�F�Ȃ�
// ���@�e�F�v���C���[��Pawn���擾����֐�
//----------------------------------
void UFollowPlayerComponent::SetPlayerPawn()
{
	// �v���C���[��Pawn���擾����
	_playerPawn = UGameplayStatics::GetPlayerPawn(this->GetWorld(), 0);

	// �v���C���[�̍��W���i�[����
	if (_playerPawn != nullptr)
	{
		_playerLocation = _playerPawn->GetActorLocation();
	}
}


//----------------------------------
// �֐����FFollowPlayer
// ���@���F�Ȃ�
// �߂�l�F�Ȃ�
// ���@�e�F�v���C���[��Ǐ]�����鏈���̊֐�
//----------------------------------
void UFollowPlayerComponent::FollowPlayer()
{
	if (_playerPawn == nullptr)
	{
		// �v���C���[��Pawn���擾����֐�
		SetPlayerPawn();
		return;
	}

	// �v���C���[�̍��W���i�[����
	_playerLocation = _playerPawn->GetActorLocation();

	// �V�������W���쐬����
	FVector TargetLocation = FVector(_currentLocation.X, _playerLocation.Y, _currentLocation.Z);

	// ���݂̍��W����ڕW���W�ɕ�Ԃ��ĐV�������W���v�Z
	FVector NewLocation = FMath::VInterpTo(
		_currentLocation,					// ���݂̍��W
		TargetLocation,						// �ڕW���W
		GetWorld()->GetDeltaSeconds(),		// �t���[�����Ƃ̃f���^����
		_cameraMoveSpeed					// ��ԑ��x
	);

	if (GetOwner())
	{
		// �V�������W�����݂̍��W�Ɋi�[
		_currentLocation = NewLocation;
		// ���W���X�V����
		GetOwner()->SetActorLocation(NewLocation);
	}
}


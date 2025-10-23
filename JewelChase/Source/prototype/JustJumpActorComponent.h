//--------------------------------------------------------------------
// �t�@�C����	�FJustJumpActorComponent.h
// �T�v�@�@�@	�F�W���X�g�W�����v
// �쐬�ҁ@�@	�F�_�엮��
// �X�V���e�@	�F1/27 �쐬
//				  2/1  �����͊����i�������A�������j
//                2/11 ���������i�������j
//				  2/23 ��������
//--------------------------------------------------------------------

// �C���N���[�h�K�[�h
#pragma once

// �C���N���[�h
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "JustJumpActorComponent.generated.h"

// �W�����v�̎�ނ̗񋓌^
UENUM(BlueprintType)
enum class EJumpStatus : uint8
{
	EmptyJump  UMETA(DisplayName = "EmptyJump"),
	NormalJump UMETA(DisplayName = "NormalJump"),
	JustJump   UMETA(DisplayName = "JustJump"),
	MaxNum     UMETA(Hidden)
};

// �W���X�g�W�����v���s���Ƃ��Ɏg�p����l�̍\����
struct JustJumpParams
{
	FVector HalfBoxSize;		// ���C�L���X�g��Box�̑傫��
	float DistancePlayer;       // ���C��\������v���C���[����̋���
	float RayEnd;               // ���C�̏I�_
	float RayBoxHeight;			// ���C�L���X�g�̍���
	float MinJustJumpDistance;	// �W���X�g�W�����v�̍ŏ��̋���
	float MaxJustJumpDistance;	// �W���X�g�W�����v�̍ő�̋���
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROTOTYPE_API UJustJumpActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	// �v���p�e�B�ύX��ێ�����֐�
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

	UJustJumpActorComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//----------------------------------
	// �֐����FJumpStatusToDisplayName
	// ���@���FEJumpStatus�^
	// �߂�l�FFString�^
	// ���@�e�F�W�����v�̃X�e�[�^�X��UMETA��߂��֐� ��GetDisplayNameTextByValue��int64�^�Ȃ̂�int64�ɃL���X�g���Ă��܂�
	//----------------------------------
	UFUNCTION(BlueprintCallable, Category = "JumpStatus")
	FString JumpStatusToDisplayName(EJumpStatus State)
	{
		return StaticEnum<EJumpStatus>()->GetDisplayNameTextByValue(static_cast<int64>(State)).ToString();
	}

	//----------------------------------
	// �֐����FJustJumpRay
	// ���@���F�Ȃ�
	// �߂�l�FEJumpStatus�^
	// ���@�e�F�W���X�g�W�����v�����f���郌�C�̍쐬
	//----------------------------------
	EJumpStatus JustJumpRay();

	//----------------------------------
	// �֐����FAddItemToIgnore
	// ���@���F�Ȃ�
	// �߂�l�F�Ȃ�
	// ���@�e�F���[���h�ɂ���A�C�e���𖳎����郊�X�g�ɒǉ�
	//----------------------------------
	void AddItemToIgnore();

private:
	// �W�����v�̎�ނ̗񋓌^
	EJumpStatus _eJumpStatus;
	// ���O����Actor�̃|�C���^�[
	UPROPERTY()
	TArray<AActor*> _ignoreItemsActor;     // �A�C�e��
	UPROPERTY()
	TArray<AActor*> _ignoreSmogsActor;     // ��

	// �R���|�[�l���g�̂��Ă���Actor
	UPROPERTY()
	AActor* _ownerActor;

	// ���C�L���X�g�Ŏ擾���镨
	FCollisionObjectQueryParams _objectQueryParams;

	// ���C�L���X�g�Ŗ������镨
	FCollisionQueryParams _ignoreParams;

	// ���C�L���X�g��Box�̑傫��
	UPROPERTY(EditAnywhere, Category = "JustJumpRayParams")
	FVector _halfBoxSize;

	// ���C��\������v���C���[����̋���
	UPROPERTY(EditAnywhere, Category = "JustJumpRayParams")
	float _distancePlayer;
	// ���C�̏I�_
	UPROPERTY(EditAnywhere, Category = "JustJumpRayParams")
	float _rayEnd;
	// ���C�L���X�g�̍���
	UPROPERTY(EditAnywhere, Category = "JustJumpRayParams")
	float _rayBoxHeight;
	// �W���X�g�W�����v�̍ŏ��̋���
	UPROPERTY(EditAnywhere, Category = "JustJumpRayParams")
	float _minJustJumpDistance;
	// �W���X�g�W�����v�̍ő�̋���
	UPROPERTY(EditAnywhere, Category = "JustJumpRayParams")
	float _maxJustJumpDistance;
};

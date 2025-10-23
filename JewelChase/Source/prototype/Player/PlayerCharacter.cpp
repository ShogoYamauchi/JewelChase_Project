//--------------------------------------------------------------------
//����ҁ@�F���@���
//��������F2024/11/22
//�ŏI�X�V�F2025/02/10
//�T�@�v�@�F�v���C���[�̃x�[�X����
//--------------------------------------------------------------------
#include "PlayerCharacter.h"
#include "BlinkingComponent.h"
#include "Player/PlayerComponent/PlayerHitByPoliceCarComponent.h"
#include "JustJumpActorComponent.h"
#include "Blueprint/UserWidget.h"  // UUserWidget�̃C���N���[�h
#include "UI/JJPerfectWidget.h"
#include "Kismet/GameplayStatics.h"

#define JUMP_HEIGHT (_jumpTime * _jumpTime * (-_gravity) / 2) + (_jumpTime * _jumpPower)

class UPrimitiveComponent;
class APlayerController;
class UJJPerfectWidget;

APlayerCharacter::APlayerCharacter()
	: MyStatus(PlayerStatus::Running)
	, _beforeJumpPos(FVector::ZeroVector)
	, _jumpTime(0.0f)
	, _initialLimitBulletNum(_limitBulletNum)
	, _initialBulletAttack(_bulletAttack)
	, _isJumping(false)
	, _canControl(true)
	, _isReload(false)
	, _isJewelRush(false)
	, _isInvincible(false)
	, _isAttack(false)
	, _isJumpRigor(false)
	, _isBlinking(false)
{
	PrimaryActorTick.bCanEverTick = true;

	_pPlayerHitByPoliceCarComponent = CreateDefaultSubobject<UPlayerHitByPoliceCarComponent>(TEXT("_pPlayerHitByPoliceCarComponent"));	//�@�x�@�̓��������̏������s�����߂̃R���|�[�l���g 
	_pBlinkingComponent = CreateDefaultSubobject<UBlinkingComponent>(TEXT("_pBlinkingComponent"));	// �_�ł����邽�߂̃R���|�[�l���g
	_pJustJumpActorComponent = CreateDefaultSubobject<UJustJumpActorComponent>(TEXT("_pJustJumpActorComponent"));	//�@JunstJump�̏������s�����߂̃R���|�[�l���g

	_originalMaterial0 = nullptr;
	_originalMaterial1 = nullptr;

	_capsuleComponent = GetCapsuleComponent();
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	/*
	if (_playerDataTable)
	{
		TArray<FName> RowNames = _playerDataTable->GetRowNames();
		_data = *(_playerDataTable->FindRow<FPlayerSE>(RowNames[0], FString()));
	}
	*/

	//SEManager���擾
	_seManager = USEManager::GetInstance(this);

	RegisterSE();

	//USEManager::GetInstance()->RegisterSE(TEXT("Attack"), AttackSE);

	if (GetMesh())
	{
		_originalMaterial0 = GetMesh()->GetMaterial(0);
		_originalMaterial1 = GetMesh()->GetMaterial(1);
	}

	// �R���|�[�l���g�̓o�^�E�v���C���[�̉��͈͂�ݒ肷��
	if (_pPlayerHitByPoliceCarComponent)
	{
		_pPlayerHitByPoliceCarComponent->ClampPlayerYLocation(_maxPosY, _minPosY);	// �R���|�[�l���g�Ƀv���C���[�̉��͈͂�ݒ�
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("No _pPlayerHitByPoliceCarComponent"));
	}

	//�J�[�\���̕\��
	ShowMouseCursor();

#if true
	//�C�x���g�̃f���Q�[�g���o�C���h
	if (UPrimitiveComponent* PrimitiveRoot = Cast<UPrimitiveComponent>(GetRootComponent()))
	{
		PrimitiveRoot->SetNotifyRigidBodyCollision(true);
		PrimitiveRoot->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

		// Overlap �C�x���g���o�C���h
		PrimitiveRoot->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OnOverlapBegin);
	}
#endif
}

void APlayerCharacter::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	//Player��Y���W�𐧌�
	PlayerPosControl();

	//�}�E�X�̈ړ��͈͂𐧌�
	MouseRangeControl();

	FVector myPos = GetActorLocation();
	myPos.X = 0.0f;
	//X����0�ɌŒ�
	SetActorLocation(myPos);

	if (MyStatus == PlayerStatus::Die)
	{
		return;
	}

	//�W�����v��
	UpdateJump(deltaTime);

	//�����[�h����
	if (_limitBulletNum <= 0u && !_isReload)
	{
		ReloadBulletTimer();
	}

	//���S����
	if (_hp <= 0u)
	{
		Dead();
	}

	//�_�ŏ���
	if (_onBlinking)
	{
		_toggleTime -= deltaTime;

		if (_toggleTime <= 0.0f)
		{
			//�_�ŏ���
			ToggleMaterial();
			_toggleTime = _initialToggleTime;
		}
	}
	if (MyStatus == PlayerStatus::Uncontroll)
	{
		//RunSE���~
		if (_seMap["Run"] != nullptr)
		{
			_seManager->StopSE(TEXT("Run"));
		}
	}
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* playerInputComponent)
{
	Super::SetupPlayerInputComponent(playerInputComponent);

	if (!_canControl)
	{
		return;
	}

	//���E�ړ�
	if (!_isJumping)
	{
		playerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::Move);
	}

	playerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharacter::JumpStart);
	//�������Ŏˌ��ł��Ȃ�why?��
	//playerInputComponent->BindAction("Click", IE_Repeat, this, &APlayerCharacter::SpawnBullet);
	playerInputComponent->BindAction("Click", IE_Pressed, this, &APlayerCharacter::SpawnBullet);
	playerInputComponent->BindAction("JewelRush", IE_Pressed, this, &APlayerCharacter::JewelRushStart);
}

// BeginOverlap �C�x���g
void APlayerCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//UE_LOG(LogTemp, Log, TEXT("Player Hit %s"),*OtherActor->GetName());
	if (!OtherActor)
	{
		return;
	}
	//Enemy�ɓ��������珈��
	if (OtherActor->ActorHasTag("Enemy") || OtherActor->ActorHasTag("Oil_Explosion"))
	{
		//1�_���[�W�󂯂�
		IsDamaged(1);

		if (OtherActor->ActorHasTag("PoliceCar") && !_isInvincible && !_isJewelRush)
		{
			if (_pPlayerHitByPoliceCarComponent)
			{
				//UE_LOG(LogTemp, Log, TEXT("Player Hit PoliceCar"));
				// �m�b�N�o�b�N����
				_pPlayerHitByPoliceCarComponent->TriggerKnockBack(this, OtherActor);

			}
		}

#if false
		UKismetSystemLibrary::PrintString(
			this,                            // �R���e�L�X�g�I�u�W�F�N�g�i�ʏ��`this`�j
			OtherActor->GetName(),			 // �\�����镶����
			true,                            // �X�N���[���ɕ\�����邩
			true,                            // �R���\�[���ɕ\�����邩
			FColor::Red,                     // �����̐F
			2.0f                             // �\�����ԁi�b�j
		);
#endif 
		return;
	}

	//�z��̒������擾
	const int length = sizeof(_jewelRushGageIncrementNum) / sizeof(_jewelRushGageIncrementNum[0]);

	for (int i = 0; i < length; i++)
	{
		//jewel�n��tag�������珈��
		if (OtherActor->ActorHasTag(_jewelName[i]))
		{
			if (_seMap["Get_Jewel"] != nullptr)
			{
				_seManager->PlaySE2D(TEXT("Get_Jewel"));
			}

#if true
			if (_isJewelRush)
			{
				return;
			}
#endif

			//�W���G�����b�V���Q�[�W�ɉ��Z
			_jewelRushGageNum += _jewelRushGageIncrementNum[i];

			//Max���傫�����Max�ɕ␳
			if (_jewelRushGageNum > _jewelRushGageMaxNum)
			{
				_jewelRushGageNum = _jewelRushGageMaxNum;
			}

			return;
		}
	}

#if false
	//�f�o�b�N�p�֐�
	//��������Actor��\��
	UKismetSystemLibrary::PrintString(
		this,                            // �R���e�L�X�g�I�u�W�F�N�g�i�ʏ��`this`�j
		OtherActor->GetName(),			 // �\�����镶����
		true,                            // �X�N���[���ɕ\�����邩
		true,                            // �R���\�[���ɕ\�����邩
		FColor::Red,                     // �����̐F
		2.0f                             // �\�����ԁi�b�j
	);
#endif

	if (OtherActor->ActorHasTag("Heal"))
	{
		AddHP(1);

		if (_seMap["Get_Heal"] != nullptr)
		{
			_seManager->PlaySE2D(TEXT("Get_Heal"));
		}

		return;
	}
}

#pragma region JumpFunction
void APlayerCharacter::UpdateJump(float deltaTime)
{
	if (!_isJumping)
	{
		return;
	}
	float nowJumpHeight = JUMP_HEIGHT;

	_jumpTime += deltaTime;

	FVector nowPos = GetActorLocation();

	if (nowJumpHeight < 0.0f)
	{
		JumpEnd();
	}
	else
	{
		SetActorLocation(FVector(nowPos.X, nowPos.Y, _beforeJumpPos.Z + nowJumpHeight), true);
	}
}

void APlayerCharacter::JumpStart()
{
	if (MyStatus == PlayerStatus::Uncontroll)
	{
		return;
	}

	if (MyStatus == PlayerStatus::Damaged)
	{
		return;
	}

	if (MyStatus == PlayerStatus::Die)
	{
		return;
	}

	if (!_canControl)
	{
		return;
	}

	if (_isJumpRigor)
	{
		return;
	}

	if (!_isJumping)
	{
		_isJumping = true;

		//RunSE���~
		if (_seMap["Run"] != nullptr)
		{
			_seManager->StopSE(TEXT("Run"));
		}

		//JumpSE���Đ�
		if (_seMap["Jump"] != nullptr)
		{
			_seManager->PlaySE2D(TEXT("Jump"));
		}
		if (_seMap["JumpVoice"] != nullptr)
		{
			_seManager->PlaySE2D(TEXT("JumpVoice"));
		}

#if false
		if (_pJustJumpActorComponent->JustJumpRay() == _pJustJumpActorComponent->JumpStatus::JustJump)
		{
			UKismetSystemLibrary::PrintString(
				this,                            // �R���e�L�X�g�I�u�W�F�N�g�i�ʏ��`this`�j
				"JustJump",			 // �\�����镶����
				true,                            // �X�N���[���ɕ\�����邩
				true,                            // �R���\�[���ɕ\�����邩
				FColor::Green,                     // �����̐F
				2.0f                             // �\�����ԁi�b�j
			);

			ReloadBullet();
		}
#endif // false

		_beforeJumpPos = GetActorLocation();

		FRotator NewRotation = FRotator(0.0f, 90.0f, 0.0f);
		//�����̂�Yaw(Z����])�������Q�[���ɔ��f����Ȃ�
		//SetActorRotation(NewRotation);

		GetMesh()->SetWorldRotation(NewRotation);	//��p��

		// �W���X�g�W�����v�̏���
		EJumpStatus EJumpStatus = _pJustJumpActorComponent->JustJumpRay();

		if (_limitBulletNum >= 13u || _isReload == true) return;	// �������^�[��

		if (EJumpStatus == EJumpStatus::NormalJump)
		{
			for (int i = 0; i < 3; i++)
			{
				++_limitBulletNum;
			}
		}
		else if (EJumpStatus == EJumpStatus::JustJump)
		{
			for (int i = 0; i < 5; i++)
			{
				++_limitBulletNum;
			}

			// Perfect��UI��\��
			if (WBP_JJPerfectClass)
			{
				// �E�B�W�F�b�g���쐬
				UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), WBP_JJPerfectClass);

				if (Widget == nullptr)
				{
					return;  // �������^�[��
				}

				// �E�B�W�F�b�g����ʂɒǉ�
				Widget->AddToViewport();

				// �L���X�g���ăA�j���[�V�������擾
				UJJPerfectWidget* PerfectWidget = Cast<UJJPerfectWidget>(Widget);
				if (PerfectWidget && PerfectWidget->PerfectAnimation)
				{
					PerfectWidget->PlayAnimation(PerfectWidget->PerfectAnimation);
				}
			}
		}
	}
}

void APlayerCharacter::JumpEnd()
{
	if (_seMap["Jump"] != nullptr)
	{
		_seManager->StopSE(TEXT("Jump"));
	}
	if (_seMap["JumpVoice"] != nullptr)
	{
		_seManager->StopSE(TEXT("JumpVoice"));
	}

	_jumpTime = 0.0f;

	_isJumping = false;

#if true
	_isJumpRigor = true;

	//�^�C�}�[�p�̃��[�J���ϐ�
	FTimerHandle TimerHandle;

	//n�b��Ɋ֐����Ăяo��
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &APlayerCharacter::Jumprigor, _jumpRigorTime, false);
#endif // 0

	if (MyStatus == PlayerStatus::Damaged)
	{
		return;
	}

	MyStatus = PlayerStatus::Running;
}

void APlayerCharacter::Jumprigor()
{
	_isJumpRigor = false;
}
#pragma endregion 

void APlayerCharacter::Move(float AxisValue)
{
	if (_isJumping)
	{
		return;
	}

	if (MyStatus == PlayerStatus::Uncontroll)
	{
		return;
	}

	if (MyStatus == PlayerStatus::Damaged)
	{
		return;
	}

	if (MyStatus == PlayerStatus::Die)
	{
		return;
	}

	MyStatus = PlayerStatus::Running;

	//RunSE���Đ�
	if (_seMap["Run"] != nullptr)
	{
		_seManager->PlaySE2DLoop("Run");
	}
	//�E
	if (AxisValue > 0.0f)
	{
		FRotator NewRotation = FRotator(0.0f, 90.0f + _rotation, 0.0f);
		//�����̂�Yaw(Z����])�������Q�[���ɔ��f����Ȃ�
		//SetActorRotation(NewRotation);

		GetMesh()->SetWorldRotation(NewRotation);	//��p��
	}
	//��
	else if (AxisValue < 0.0f)
	{
		FRotator newRotation = FRotator(0.0f, 90.0f + (-_rotation), 0.0f);
		//SetActorRotation(NewRotation);

		GetMesh()->SetWorldRotation(newRotation);
	}
	else
	{
		FRotator newRotation = FRotator(0.0f, 90.0f, 0.0f);
		//SetActorRotation(NewRotation);

		GetMesh()->SetWorldRotation(newRotation);
	}

#if false
	//�f�o�b�N�p�֐�
	//��������Actor��\��
	UKismetSystemLibrary::PrintString(
		this,                            // �R���e�L�X�g�I�u�W�F�N�g�i�ʏ��`this`�j
		FString::FromInt(AxisValue),			 // �\�����镶����
		true,                            // �X�N���[���ɕ\�����邩
		true,                            // �R���\�[���ɕ\�����邩
		FColor::Red,                     // �����̐F
		2.0f                             // �\�����ԁi�b�j
	);
#endif

	MyStatus = PlayerStatus::Running;
	// �E�����̃x�N�g�����擾���A���̕����Ɉړ�
	//���ݍ��W���擾
	FVector mypos = GetActorLocation();
	//���ݍ��W������Z�����v�Z
	mypos.Y += AxisValue * _moveSpeed;
	//���ۂ̍��W�ɉ��Z
	SetActorLocation(mypos);
}

void APlayerCharacter::PlayerPosControl()
{
	FVector nowLocation = GetActorLocation();
	FVector newLocation = nowLocation;

	if (nowLocation.Y > _maxPosY)
	{
		newLocation.Y = _maxPosY;
		SetActorLocation(newLocation);
	}
	else if (nowLocation.Y < _minPosY)
	{
		newLocation.Y = _minPosY;
		SetActorLocation(newLocation);
	}
}

void APlayerCharacter::IsDamaged(int damage)
{
	if (_isInvincible)
	{
		return;
	}

	if (_isJewelRush)
	{
		return;
	}

	if (MyStatus == PlayerStatus::Damaged)
	{
		return;
	}

	MyStatus = PlayerStatus::Damaged;

	//if (_seMap["Run"] != nullptr)
	//{
	//	_seManager->StopSE("Run");
	//}

	//if (_seMap["Jump"] != nullptr)
	//{
	//	_seManager->StopSE("Jump");
	//}

	_hp -= damage;

	if (_hp > 0)
	{
		//�_���[�W����
		if (_seMap["Damage"] != nullptr)
		{
			_seManager->PlaySE2D("Damage");
		}
		//�_���[�W����
		if (_seMap["DamageVoice"] != nullptr)
		{
			_seManager->PlaySE2D("DamageVoice");
		}
	}
}

void APlayerCharacter::Dead()
{
	if (_hp > 0u)
	{
		return;
	}

	if (_capsuleComponent)
	{
		_capsuleComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	//RunSE���~
	if (_seMap["Run"] != nullptr && MyStatus != PlayerStatus::Die)
	{
		_seManager->StopSE(TEXT("Run"));
	}

	if (_seMap["Dead"] != nullptr)
	{
		_seManager->PlaySE2D(TEXT("Dead"));
	}
	if (_seMap["Damage"] != nullptr)
	{
		_seManager->PlaySE2D(TEXT("Damage"));
	}

	MyStatus = PlayerStatus::Die;

}

void APlayerCharacter::InvincibleTime()
{
	if (MyStatus == PlayerStatus::Die)
	{
		return;
	}

	_isInvincible = true;

#if false
	UKismetSystemLibrary::PrintString(
		this,                            // �R���e�L�X�g�I�u�W�F�N�g�i�ʏ��`this`�j
		"InvincibleTime",			 // �\�����镶����
		true,                            // �X�N���[���ɕ\�����邩
		true,                            // �R���\�[���ɕ\�����邩
		FColor::Red,                     // �����̐F
		2.0f                             // �\�����ԁi�b�j
	);
#endif

	// �_�ł�����
	_pBlinkingComponent->TriggerBlinking(_invincibleTime);

	MyStatus = PlayerStatus::Invincible;

	//�^�C�}�[�p�̃��[�J���ϐ�
	FTimerHandle TimerHandle;

	//n�b��Ɋ֐����Ăяo��
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &APlayerCharacter::InvincibleTimeEnd, _invincibleTime, false);
}

void APlayerCharacter::InvincibleTimeEnd()
{
	_isInvincible = false;

	MyStatus = PlayerStatus::Running;
}

#pragma region MouseFunction
void APlayerCharacter::ShowMouseCursor()
{
	//if (MyStatus == PlayerStatus::Uncontroll)
	//{
	//	return;
	//}
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	//// �J�[�\����\��
	if (PlayerController)
	{
		PlayerController->bShowMouseCursor = true; // �J�[�\����\��
	}

	//// �K�v�ɉ����ē��̓��[�h��ݒ�
	//FInputModeGameAndUI InputMode;
	//SetInputMode(InputMode);
}

void APlayerCharacter::MouseRangeControl()
{
	if (MyStatus == PlayerStatus::Uncontroll)
	{
		return;
	}

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	FVector2D nowCursorPos;
	//Cursor�̍��W���擾
	if (PlayerController->GetMousePosition(nowCursorPos.X, nowCursorPos.Y))
	{
		if (nowCursorPos == FVector2D::ZeroVector)
		{
			return;
		}


		//�}�E�X�̍��W�𐧌�
		nowCursorPos.X = FMath::Clamp(nowCursorPos.X, _minCursorPos.X, _maxCursorPos.X);
		nowCursorPos.Y = FMath::Clamp(nowCursorPos.Y, _minCursorPos.Y, _maxCursorPos.Y);
		PlayerController->SetMouseLocation(nowCursorPos.X, nowCursorPos.Y);

#if false	//�f�o�b�N�p
		//�}�E�X�̍��W��\��
		FString debug = FString::Printf(TEXT("X: %.2f, Y: %.2f"), nowCursorPos.X, nowCursorPos.Y);

		UKismetSystemLibrary::PrintString(
			this,                            // �R���e�L�X�g�I�u�W�F�N�g�i�ʏ��`this`�j
			debug,			 // �\�����镶����
			true,                            // �X�N���[���ɕ\�����邩
			true,                            // �R���\�[���ɕ\�����邩
			FColor::Red,                     // �����̐F
			2.0f                             // �\�����ԁi�b�j
		);
#endif
	}
}
#pragma endregion 

#pragma region BulletFunction
bool APlayerCharacter::GetViewToWorldPos(FVector& location, FVector& direction)
{
	//�}�E�X�̍��W
	float MouseX, MouseY;
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	if (PlayerController == nullptr)
	{
		return false;
	}

	//�R���p�C������������̂ň�U�ۗ�
#if false
	PlayerController->GetMousePosition(MouseX, MouseY);

	FMatrix view;
	FMatrix proj;
	FMatrix vp;
	FMinimalViewInfo MinimalViewInfo;

	auto pCameraMng = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
	MinimalViewInfo = pCameraMng->POV;
	UGameplayStatics::GetViewProjectionMatrix(viewInfo, view, proj, vp);

	//�}�E�X�̈ʒu
	FVector mousePos(MouseX, MouseY, 0.0f);


	//�v���W�F�N�V�����̋t�s��

	//view�̋t�s��

#endif

	// �}�E�X�̈ʒu���擾
	if (PlayerController->GetMousePosition(MouseX, MouseY))
	{
		// �X�N���[�����W�����[���h���W�ƕ����ɕϊ�
		//ScreenX, ScreenY: �X�N���[����̈ʒu�iX, Y���W�j
		//WorldLocation : ���[���h��Ԃ̊�ʒu�i�ʏ�A�J�����̈ʒu�ɋ߂��j
		//WorldDirection : ��ʏ�̓_���烏�[���h��ԂɌ����������x�N�g��
		return PlayerController->DeprojectScreenPositionToWorld(MouseX, MouseY, location, direction);
	}
	return false;
}

void APlayerCharacter::SpawnBullet()
{
	if (MyStatus == PlayerStatus::Uncontroll)
	{
		return;
	}

	if (MyStatus == PlayerStatus::Damaged)
	{
		return;
	}

	if (MyStatus == PlayerStatus::Die)
	{
		return;
	}

	if (_limitBulletNum <= 0u)
	{
		return;
	}

	// ���ˈʒu�ƌ���
	if (PlayerBulletClass)
	{
		//AttackSE���Đ�
		if (_seMap["Shooting"] != nullptr)
		{
			_seManager->PlaySE2D(TEXT("Shooting"));
		}

		_limitBulletNum--;

		if (_isJewelRush)
		{
			_limitBulletNum = _initialLimitBulletNum;
		}

		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

		if (!PlayerController)
		{
			return;
		}

		FHitResult HitResult;	//����������

		AActor* ClickedActor = nullptr;	//�N���b�N�����A�N�^�[  �R��

		//�N���b�N�������̂��擾
		if (PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, HitResult))
		{
			//�A�N�^�[���擾
			ClickedActor = HitResult.GetActor();
		}
		//�������擾�ł��Ȃ�
		//GetHitResultUnderCursor���ƃR���W�����v���Z�b�g��BlockAll��Custom����Ȃ��Ɠ�����Ȃ�
		//��p��
		//LineTraceMultiByChannel
		//OverlapMultiByChannel

		//�N���b�N�����A�N�^�[������΂��N���b�N�����̂�Enemy�^�O�������珈��
		if (ClickedActor && ClickedActor->ActorHasTag("Enemy"))
		{
#if false	//�f�o�b�N�p
			//�}�E�X�̍��W��\��

			UKismetSystemLibrary::PrintString(
				this,                            // �R���e�L�X�g�I�u�W�F�N�g�i�ʏ��`this`�j
				ClickedActor->GetName(),			 // �\�����镶����
				true,                            // �X�N���[���ɕ\�����邩
				true,                            // �R���\�[���ɕ\�����邩
				FColor::Red,                     // �����̐F
				2.0f                             // �\�����ԁi�b�j
			);
#endif

			//PlayerBullet�����[���h�ɃX�|�[��
			APlayerBullet* Bullet = GetWorld()->SpawnActor<APlayerBullet>(PlayerBulletClass);

			if (Bullet) // �R���@�i�N���b�V�������������j
			{
				Bullet->SetActorLocation(GetActorLocation() + _offsetBulletPos);	//�R���i��������g�����v���o�Ă���̒������j

				// �N���b�N�����A�N�^�[�����[���h�ɑ��݂��鎞����������`����
				if (IsValid(ClickedActor))Bullet->SetTarget(ClickedActor); //�R���i���S�ʂ��l���āj
			}
		}

		//�N���b�N�����A�N�^�[�����Ȃ��������̓N���b�N�����A�N�^�[��Enemy�Ŗ�����Ώ���
		if (!ClickedActor || !ClickedActor->ActorHasTag("Enemy"))
		{
			FVector MuzzleLocation = GetActorLocation() + _bulletOffsetPos;  // ���ˈʒu
			FRotator MuzzleRotation = GetActorRotation();  // ���ˊp�x

			//�o���b�g�̃^�[�Q�b�g���擾
			FVector location, direction;

			if (GetViewToWorldPos(location, direction)) {
				direction = ((location + (direction * 1000.0f)) - MuzzleLocation).GetSafeNormal();
			}
			else {
				//��肭�����Ȃ������ꍇ�͂����ŉ��Ƃ�����
			}
			//PlayerBullet�����[���h�ɃX�|�[��
			APlayerBullet* Bullet = GetWorld()->SpawnActor<APlayerBullet>(PlayerBulletClass, MuzzleLocation, MuzzleRotation);

			if (!Bullet || direction == FVector::ZeroVector)
			{
				return;
			}

			Bullet->SetDirection(direction + _offsetBulletPos);
		}
	}
}

void APlayerCharacter::ReloadBulletTimer()
{
	if (_isJewelRush)
	{
		return;
	}

	_isReload = true;

	//�^�C�}�[�p�̃��[�J���ϐ�
	FTimerHandle TimerHandle;

#if true
	//Reload_StartSE���Đ�
	if (_seMap["Reload_Start"] != nullptr)
	{
		_seManager->PlaySE2DLoop(TEXT("Reload_Start"));
	}
#endif // 0

	//n�b��Ɋ֐����Ăяo��
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &APlayerCharacter::ReloadBullet, _reloadBulletTime, false);
}

void APlayerCharacter::ReloadBullet()
{
#if true
	//Reload_StartSE���~
	if (_seMap["Reload_Start"] != nullptr)
	{
		_seManager->StopSE(TEXT("Reload_Start"));
	}

	//Reload_EndSE���Đ�
	if (_seMap["Reload_End"] != nullptr)
	{
		_seManager->PlaySE2D(TEXT("Reload_End"));
	}
#endif // 0

	_limitBulletNum = _initialLimitBulletNum;

	_isReload = false;
}
#pragma endregion 

//���V�t�g����������Ăяo�����
void APlayerCharacter::JewelRushStart()
{
	//�Q�[�W�����܂��Ă��Ȃ������珈��
	if (_jewelRushGageNum < _jewelRushGageMaxNum)
	{
		return;
	}

	if (MyStatus == PlayerStatus::Uncontroll)
	{
		return;
	}

	if (MyStatus == PlayerStatus::Damaged)
	{
		return;
	}

	if (MyStatus == PlayerStatus::Die)
	{
		return;
	}

	if (_isJewelRush)
	{
		return;
	}

	if (_seMap["JewelRush_Start"] != nullptr)
	{
		_seManager->PlaySE2D(TEXT("JewelRush_Start"));
	}

	//�G�t�F�N�g�𐶐�
	SpawnParticleEffect(FVector::ZeroVector);

	_isJewelRush = true;

	//�c�e���������l�ɕύX
	_limitBulletNum = _initialLimitBulletNum;

	_jewelRushGageNum = 0u;

	//�}�e���A����ύX
	if (GetMesh())
	{
		//�G�������g0�Ԗڂ̃}�e���A����ύX
		if (_jewelRushMaterial0)
		{
			GetMesh()->SetMaterial(0, _jewelRushMaterial0);
		}
		//�G�������g1�Ԗڂ̃}�e���A����ύX
		if (_jewelRushMaterial1)
		{
			GetMesh()->SetMaterial(1, _jewelRushMaterial1);
		}
	}

	JewelRushTime();

}

void APlayerCharacter::JewelRushTime()
{
	if (!_isJewelRush)
	{
		return;
	}

	_bulletAttack = _jewelRushBulletAttack;

	//�^�C�}�[�p�̃��[�J���ϐ�
	FTimerHandle TimerHandle;

	FTimerHandle _blinkStartTimerHandle;

	//n�b��ɓ_�ŊJ�n
	GetWorld()->GetTimerManager().SetTimer(_blinkStartTimerHandle, this, &APlayerCharacter::ChangeOnBlinkingFlag, _blinkingStartTime, false);

	//�����^�C�}�[�����Z�b�g����
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);

	//n�b��Ɋ֐����Ăяo��
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &APlayerCharacter::JewelRushEnd, _jewelRushTime, false);

#if false
	UKismetSystemLibrary::PrintString(
		this,                            // �R���e�L�X�g�I�u�W�F�N�g�i�ʏ��`this`�j
		FString::FromInt(_jewelRushTime),			 // �\�����镶����
		true,                            // �X�N���[���ɕ\�����邩
		true,                            // �R���\�[���ɕ\�����邩
		FColor::Red,                     // �����̐F
		2.0f                             // �\�����ԁi�b�j
	);
#endif
}

void APlayerCharacter::JewelRushEnd()
{
	if (_seMap["JewelRush_End"] != nullptr)
	{
		_seManager->PlaySE2D(TEXT("JewelRush_End"));
	}

	_isJewelRush = false;

	_onBlinking = false;

	_bulletAttack = _initialBulletAttack;

	//_jewelRushTime = _initialJewelRushTime;

	//�}�e���A�������ɖ߂�
	if (GetMesh())
	{
		//�G�������g0�Ԗڂ̃}�e���A�������ɖ߂�
		if (_originalMaterial0)
		{
			GetMesh()->SetMaterial(0, _originalMaterial0);
		}
		//�G�������g1�Ԗڂ̃}�e���A�������ɖ߂�
		if (_originalMaterial1)
		{
			GetMesh()->SetMaterial(1, _originalMaterial1);
		}
	}
}

void APlayerCharacter::ToggleMaterial()
{
	_isBlinking = !_isBlinking;

	if (_isBlinking)
	{
		// �}�e���A����_�ŗp�̂��̂ɕύX
		if (_isBlinking)
		{
			GetMesh()->SetMaterial(0, _jewelRushMaterial0);
			GetMesh()->SetMaterial(1, _jewelRushMaterial1);
		}
	}
	else
	{
		// �}�e���A����ʏ�̂��̂ɖ߂�
		if (_originalMaterial0 && _originalMaterial1)
		{
			GetMesh()->SetMaterial(0, _originalMaterial0);
			GetMesh()->SetMaterial(1, _originalMaterial1);
		}
	}
}

void APlayerCharacter::ChangeOnBlinkingFlag()
{
	_onBlinking = !_onBlinking;
}

void APlayerCharacter::SpawnParticleEffect(FVector offset)
{
	if (_jewelRushEffect)
	{
		UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			_jewelRushEffect,
			FVector::ZeroVector + offset,
			GetActorRotation()
		);
	}
}

void APlayerCharacter::RegisterSE()
{
	// **USEManager �� SE ��o�^**
	if (_seMap["Jump"] != nullptr)
	{
		_seManager->RegisterSE(TEXT("Jump"), _seMap["Jump"]);
	}
	if (_seMap["Run"] != nullptr)
	{
		_seManager->RegisterSE(TEXT("Run"), _seMap["Run"]);
	}
	if (_seMap["JumpVoice"] != nullptr)
	{
		_seManager->RegisterSE(TEXT("JumpVoice"), _seMap["JumpVoice"]);
	}
	if (_seMap["Damage"] != nullptr)
	{
		_seManager->RegisterSE(TEXT("Damage"), _seMap["Damage"]);
	}
	if (_seMap["Reload_Start"] != nullptr)
	{
		_seManager->RegisterSE(TEXT("Reload_Start"), _seMap["Reload_Start"]);
	}
	if (_seMap["Reload_End"] != nullptr)
	{
		_seManager->RegisterSE(TEXT("Reload_End"), _seMap["Reload_End"]);
	}
	if (_seMap["JewelRush_Start"] != nullptr)
	{
		_seManager->RegisterSE(TEXT("JewelRush_Start"), _seMap["JewelRush_Start"]);
	}
	if (_seMap["JewelRush_End"] != nullptr)
	{
		_seManager->RegisterSE(TEXT("JewelRush_End"), _seMap["JewelRush_End"]);
	}
	if (_seMap["Get_Jewel"] != nullptr)
	{
		_seManager->RegisterSE(TEXT("Get_Jewel"), _seMap["Get_Jewel"]);
	}
	if (_seMap["Get_Heal"] != nullptr)
	{
		_seManager->RegisterSE(TEXT("Get_Heal"), _seMap["Get_Heal"]);
	}
	if (_seMap["Can_JewelRush"] != nullptr)
	{
		_seManager->RegisterSE(TEXT("Can_JewelRush"), _seMap["Can_JewelRush"]);
	}
	if (_seMap["DamageVoice"] != nullptr)
	{
		_seManager->RegisterSE(TEXT("DamageVoice"), _seMap["DamageVoice"]);
	}
	if (_seMap["Shooting"] != nullptr)
	{
		_seManager->RegisterSE(TEXT("Shooting"), _seMap["Shooting"]);
	}
	if (_seMap["Dead"] != nullptr)
	{
		_seManager->RegisterSE(TEXT("Dead"), _seMap["Dead"]);
	}
}
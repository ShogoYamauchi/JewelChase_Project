//--------------------------------------------------------------------
// �t�@�C���� �FInGame.cpp
// �T�v       �F�C���Q�[������UI���܂Ƃ߂�
// �쐬��     �F0231�{��
// �X�V���e   �F02/24�@�쐬�A
//--------------------------------------------------------------------

#include "InGame.h"
#include "Kismet/GameplayStatics.h"

void UInGame::NativeConstruct()
{
	Super::NativeConstruct();

	//�v���C���[���Q�Ƃ��A���
	TSubclassOf<APlayerCharacter> findClass;
	findClass = APlayerCharacter::StaticClass();
	_player = Cast<APlayerCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), findClass));

	init();
}

void UInGame::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	//�Q�[���I�[�o�[
	if (_bGameOver)
	{
		_gameoverTime += InDeltaTime;

		//��莞�Ԍo��+�Q�[���I�[�o�[��UI�𐶐��ł���
		if (_gameoverTime > 2.0f && _createGameOverUI)
		{
			UUserWidget* gameover = CreateWidget<UUserWidget>(GetWorld(), _ingameUIs["GameOver"]);
			gameover->AddToViewport();

			_createGameOverUI = false;
		}
	}
	//�v���C��
	else
	{
		UpdateHP();

		UpdateBullet();

		//�c�e����0
		if (_player->GetLimitBulletNum() <= 0)
		{
			UUserWidget* reload = CreateWidget<UUserWidget>(GetWorld(), _ingameUIs["Reload"]);
			_reloadPanel->AddChildToCanvas(reload);
		}
	}
}

// �֐����Finit
// ���@���F�Ȃ�
// �߂�l�Fvoid
// �������e�F����������
void UInGame::init()
{
	//---------HP�̃p�l�����擾�A�����l��UI�𐶐�
	_hpPanel = Cast<UWrapBox>(GetWidgetFromName("WrapBox_HP"));

	for (int i = 0; i < _player->GetHP(); i++)
	{
		UUserWidget* hp = CreateWidget<UUserWidget>(GetWorld(), _ingameUIs["HP"]);
		_hpPanel->AddChildToWrapBox(hp);
	}

	_beforeHP = _player->GetHP();
	//------------------------------------------

	//---------�c�e���̃p�l�����擾�A�����l��UI�𐶐�
	_bulletPanel = Cast<UWrapBox>(GetWidgetFromName("WrapBox_Bullet"));

	for (int i = 0; i < _player->GetLimitBulletNum(); i++)
	{
		UUserWidget* bullet = CreateWidget<UUserWidget>(GetWorld(), _ingameUIs["Bullet"]);
		_bulletPanel->AddChildToWrapBox(bullet);
	}

	_beforebulletNum = _player->GetLimitBulletNum();
	//------------------------------------------

	//�W���G���Q�[�WUI�𐶐�
	UUserWidget* jewelgauge = CreateWidget<UUserWidget>(GetWorld(), _ingameUIs["Jewel"]);
	Cast<UCanvasPanel>(GetWidgetFromName("Jewel_Panel"))->AddChildToCanvas(jewelgauge);

	//�S�[���܂ł̋�����UI�𐶐�
	UUserWidget* distanceGoal = CreateWidget<UUserWidget>(GetWorld(), _ingameUIs["Distance"]);
	Cast<UCanvasPanel>(GetWidgetFromName("Distance_Panel"))->AddChildToCanvas(distanceGoal);

	//�X�R�AUI�𐶐�
	UUserWidget* score = CreateWidget<UUserWidget>(GetWorld(), _ingameUIs["Score"]);
	Cast<UCanvasPanel>(GetWidgetFromName("Score_Panel"))->AddChildToCanvas(score);

	//�����[�h�̃p�l�����擾
	_reloadPanel = Cast<UCanvasPanel>(GetWidgetFromName("Reload_Panel"));
}

// �֐����FUpdateHP
// ���@���F�Ȃ�
// �߂�l�Fvoid
// �������e�FHPUI���X�V
void UInGame::UpdateHP()
{
	//HP�ɕϓ�������
	if (_beforeHP != _player->GetHP())
	{
		//�O����Ⴂ
		if (_beforeHP > _player->GetHP())
		{
			//���炷
			_hpPanel->RemoveChildAt(_player->GetHP());

			_beforeHP = _player->GetHP();

			//HP��0
			if (_beforeHP <= 0)
			{
				_bGameOver = true;

				//�v���C���[��݉�������
				_player->CustomTimeDilation = 0.6f;
			}
		}
		//�O���荂��
		else 
		{
			//HPUI�ǉ�
			UUserWidget* hp = CreateWidget<UUserWidget>(GetWorld(), _ingameUIs["HP"]);
			_hpPanel->AddChildToWrapBox(hp);

			_beforeHP = _player->GetHP();
		}
	}
}

// �֐����FUpdateBullet
// ���@���F�Ȃ�
// �߂�l�Fvoid
// �������e�F�c�e��UI���X�V
void UInGame::UpdateBullet()
{
	//�c�e���ɕϓ�������
	if (_beforebulletNum != _player->GetLimitBulletNum())
	{
		//�O����Ⴂ
		if (_beforebulletNum > _player->GetLimitBulletNum())
		{
			//���炷
			_bulletPanel->RemoveChildAt(_player->GetLimitBulletNum());

			_beforebulletNum = _player->GetLimitBulletNum();
		}
		//�O���荂��
		else
		{
			//�����𑝂₷
			for (int i = _beforebulletNum; i < _player->GetLimitBulletNum(); i++)
			{
				UUserWidget* bullet = CreateWidget<UUserWidget>(GetWorld(), _ingameUIs["Bullet"]);
				_bulletPanel->AddChildToWrapBox(bullet);
			}

			_beforebulletNum = _player->GetLimitBulletNum();
		}
	}
}
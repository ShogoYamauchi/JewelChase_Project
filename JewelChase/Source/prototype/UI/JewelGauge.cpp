//--------------------------------------------------------------------
// �t�@�C���� �FJewelGauge.cpp
// �T�v       �F�W���G���Q�[�W��UI
// �쐬��     �F0231�{��
// �X�V���e   �F02/24�@�쐬�A
//--------------------------------------------------------------------

#include "JewelGauge.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

void UJewelGauge::NativePreConstruct()
{
	Super::NativePreConstruct();

	//�A�j���[�V�����p�摜���擾�A�Ǘ�
	_gaugeAnimImages.Add("0", Cast<UImage>(GetWidgetFromName("Image_0")));
	_gaugeAnimImages.Add("1", Cast<UImage>(GetWidgetFromName("Image_1")));
	_gaugeAnimImages.Add("2", Cast<UImage>(GetWidgetFromName("Image_2")));
	_gaugeAnimImages.Add("3", Cast<UImage>(GetWidgetFromName("Image_3")));
	_gaugeAnimImages.Add("4", Cast<UImage>(GetWidgetFromName("Image_4")));
	_gaugeAnimImages.Add("5", Cast<UImage>(GetWidgetFromName("Image_5")));
	_gaugeAnimImages.Add("6", Cast<UImage>(GetWidgetFromName("Image_6")));

	//�Q�[�W�̃}�e���A�����擾�A�Ǘ�
	_jewelGaugeMat = Cast<UImage>(GetWidgetFromName("Image_front"))->GetDynamicMaterial();
}

void UJewelGauge::NativeConstruct()
{
	Super::NativeConstruct();

	//�v���C���[���Q�Ƃ��A���
	TSubclassOf<APlayerCharacter> findClass;
	findClass = APlayerCharacter::StaticClass();
	_player = UGameplayStatics::GetActorOfClass(GetWorld(), findClass);

	_maxVal = float(Cast<APlayerCharacter>(_player)->GetJewelRushgageMaxNum());

	//SEManager���擾���A���܂������̉���o�^
	_seManager = USEManager::GetInstance(GetWorld());
	_seManager->RegisterSE("canJewel", _canJewelSE);
}

void UJewelGauge::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	//�W���G�����b�V����
	if (Cast<APlayerCharacter>(_player)->GetisJewelRush())
	{
		DecreaseGauge(InDeltaTime);

		//�A�j���[�V�����p�ϐ������Z�b�g
		if (_animIndex != 0 || _backIndex || _animTime != 0.0f)
		{
			AnimReset();
		}
	}
	//�W���G�����b�V��������Ȃ�
	else
	{
		//�O��̃Q�[�W�ʂƕύX����������
		if (float(Cast<APlayerCharacter>(_player)->GetJewelRushgageNum()) != _beforeVal)
		{
			IncreaseGauge(InDeltaTime);
		}
	}
}

// �֐����FIncreaseGauge
// ���@���Ffloat InDeltaTime
// �߂�l�Fvoid
// �������e�F�Q�[�W��������
void UJewelGauge::IncreaseGauge(float InDeltaTime)
{
	_beforeVal = (float(Cast<APlayerCharacter>(_player)->GetJewelRushgageNum()) * 2.0f) / _maxVal;

	GaugeUpAnim();

	//�Q�[�W�����܂��Ă�����
	if (_beforeVal >= 2.0f)
	{
		_decreaseTime = 0.0f;
		MaxGaugeAnim(InDeltaTime);

		if (_canPlaySE)
		{
			//���܂�������SE����x�����炷
			_seManager->PlaySE2D("canJewel");
			_canPlaySE = false;
		}
	}
	//���܂��ĂȂ��Ƃ�
	else
	{
		_canPlaySE = true;
	}
}

// �֐����FIncreaseGauge
// ���@���Ffloat InDeltaTime
// �߂�l�Fvoid
// �������e�F�Q�[�W��������
void UJewelGauge::DecreaseGauge(float InDeltaTime)
{
	_decreaseTime += InDeltaTime;

	//���b�V���^�C���ƌ��݂̌o�ߎ��Ԃ��������l���Q�[�W�ɓK�p
	float gaugeval = ((_rushTime - _decreaseTime) / _rushTime) * 2.0f;
	_jewelGaugeMat->SetScalarParameterValue("Value", gaugeval);
}

// �֐����FGaugeUpAnim
// ���@���F�Ȃ�
// �߂�l�Fvoid
// �������e�F�Q�[�W�̏��X�ɑ����鏈��
void UJewelGauge::GaugeUpAnim()
{
	_currentVal = ((_beforeVal - _currentVal) * 0.25f) + _currentVal;

	//����0.000001�ȓ��Ȃ�
	if (UKismetMathLibrary::NearlyEqual_FloatFloat(_currentVal, _beforeVal, 1.0E-6F))
	{
		_currentVal = _beforeVal;
		_jewelGaugeMat->SetScalarParameterValue("Value", _currentVal);
	}
	else
	{
		_jewelGaugeMat->SetScalarParameterValue("Value", _currentVal);
		
		//������x���̊֐����Ăяo��
		GetWorld()->GetTimerManager().SetTimer(_timer, this, &UJewelGauge::GaugeUpAnim, 0.016f, false, 0.0f);
	}	
}

// �֐����FMaxGaugeAnim
// ���@���F�Ȃ�
// �߂�l�Fvoid
// �������e�F�Q�[�W�����܂������̃A�j���[�V��������
void UJewelGauge::MaxGaugeAnim(float InDeltaTime)
{
	_animTime += InDeltaTime;

	//��莞�Ԍo�߂���
	if (_animTime > 0.15f)
	{
		//���݂̃C���f�b�N�X�̉摜���\���ɂ���
		switch (_animIndex)
		{
		case 0:
			_gaugeAnimImages["0"]->SetRenderOpacity(0.0f);
			break;
		case 1:
			_gaugeAnimImages["1"]->SetRenderOpacity(0.0f);
			break;
		case 2:
			_gaugeAnimImages["2"]->SetRenderOpacity(0.0f);
			break;
		case 3:
			_gaugeAnimImages["3"]->SetRenderOpacity(0.0f);
			break;
		case 4:
			_gaugeAnimImages["4"]->SetRenderOpacity(0.0f);
			break;
		case 5:
			_gaugeAnimImages["5"]->SetRenderOpacity(0.0f);
			break;
		case 6:
			_gaugeAnimImages["6"]->SetRenderOpacity(0.0f);
			break;
		}

		//�C���f�b�N�X�����炷
		if (_backIndex)
		{
			_animIndex--;

			if (_animIndex == 0) { _backIndex = false; }
		}
		//�C���f�b�N�X�𑝂₷
		else
		{
			_animIndex++;

			if (_animIndex == 6) { _backIndex = true; }
		}

		_animTime = 0.0f;
	}
	//��莞�Ԍo�߂��ĂȂ�
	else
	{
		//���݂̃C���f�b�N�X�̉摜��\������
		switch (_animIndex)
		{
		case 0:
			_gaugeAnimImages["0"]->SetRenderOpacity(1.0f);
			break;
		case 1:
			_gaugeAnimImages["1"]->SetRenderOpacity(1.0f);
			break;
		case 2:
			_gaugeAnimImages["2"]->SetRenderOpacity(1.0f);
			break;
		case 3:
			_gaugeAnimImages["3"]->SetRenderOpacity(1.0f);
			break;
		case 4:
			_gaugeAnimImages["4"]->SetRenderOpacity(1.0f);
			break;
		case 5:
			_gaugeAnimImages["5"]->SetRenderOpacity(1.0f);
			break;
		case 6:
			_gaugeAnimImages["6"]->SetRenderOpacity(1.0f);
			break;
		}
	}
}

// �֐����FAnimReset
// ���@���F�Ȃ�
// �߂�l�Fvoid
// �������e�F�W���G�����b�V���J�n��A��x�A�j���[�V�����֘A�����Z�b�g
void UJewelGauge::AnimReset()
{
	_gaugeAnimImages["0"]->SetRenderOpacity(0.0f);
	_gaugeAnimImages["1"]->SetRenderOpacity(0.0f);
	_gaugeAnimImages["2"]->SetRenderOpacity(0.0f);
	_gaugeAnimImages["3"]->SetRenderOpacity(0.0f);
	_gaugeAnimImages["4"]->SetRenderOpacity(0.0f);
	_gaugeAnimImages["5"]->SetRenderOpacity(0.0f);
	_gaugeAnimImages["6"]->SetRenderOpacity(0.0f);

	_animIndex = 0;
	_animTime = 0.0f;
	_backIndex = false;
}
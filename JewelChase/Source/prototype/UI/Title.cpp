//--------------------------------------------------------------------
// �t�@�C���� �FTitle.cpp
// �T�v       �F�^�C�g����ʂł̃��C����UI
// �쐬��     �F0231�{��
// �X�V���e   �F02/24�@�쐬�A
//--------------------------------------------------------------------


#include "Title.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UTitle::NativeConstruct()
{
	Super::NativeConstruct();

	init();

	//�^�C�g���R�[���ABGM��炷
	if (_seMap["TitleCall"] != nullptr)_seManager->PlaySE2D("TitleCall");
	if (TitleBGM != nullptr)PlaySound(TitleBGM);
}

void UTitle::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	//�J�n���̈Ö�������Ȃ珈�����s��
	if (IsValid(_beginblackoutImage)) {
		BeginTick(InDeltaTime);
	}

	TitleLogoScaleUpDown(InDeltaTime);

	_time += InDeltaTime;

	if (_time > 47.0f && !_createDemo)
	{
		//�f���v���C���[�r�[UI�𐶐�
		pm_ui_demoplay = CreateWidget<UUserWidget>(GetWorld(), m_ui_demoplay);
		if (pm_ui_demoplay){
			pm_ui_demoplay->AddToViewport();
		}

		//�^�C�g����ʂ��J���Ȃ���UI(�{�^��)�𐶐�
		pm_ui_openTitle = CreateWidget<UUserWidget>(GetWorld(), m_ui_openTitle);
		if (pm_ui_openTitle){
			pm_ui_openTitle->AddToViewport();
		}

		_createDemo = true;
	}
}

// �֐����Finit
// ���@���F�Ȃ�
// �߂�l�Fvoid
// �������e�F����������
void UTitle::init()
{
	//SEManager���擾���ASE��o�^
	_seManager = USEManager::GetInstance(GetWorld());
	if(_seMap["select"] != nullptr) _seManager->RegisterSE("select", _seMap["select"]);
	if (_seMap["start"] != nullptr) _seManager->RegisterSE("start", _seMap["start"]);
	if (_seMap["TitleCall"] != nullptr) _seManager->RegisterSE("TitleCall", _seMap["TitleCall"]);

	//�X�^�[�g�{�^���Ƀo�C���h
	_startButton = Cast<UButton>(GetWidgetFromName("Start"));
	if (_startButton) {
		if (!_startButton->OnPressed.IsBound()) {
			_startButton->OnPressed.AddDynamic(this, &UTitle::StartPressed);
		}
	}

	//�G���h�{�^���Ƀo�C���h
	_endButton = Cast<UButton>(GetWidgetFromName("GameEnd"));
	if (_endButton) {
		if (!_endButton->OnPressed.IsBound()) {
			_endButton->OnPressed.AddDynamic(this, &UTitle::EndPressed);
		}
	}

	//�I�v�V�����{�^���Ƀo�C���h
	_optionButton = Cast<UButton>(GetWidgetFromName("Option"));
	if (_optionButton) {
		if (!_optionButton->OnPressed.IsBound()) {
			_optionButton->OnPressed.AddDynamic(this, &UTitle::OptionPressed);
		}
	}

	//�J�n���̈Ö����擾�A�����x�͍ő�
	_beginblackoutImage = Cast<UImage>(GetWidgetFromName("BlackOut"));
	_beginblackoutImage->SetRenderOpacity(1.0f);

	//�^�C�g�����S���擾
	_titleLogo = Cast<UImage>(GetWidgetFromName("TitleLogo"));
	_titleLogo->SetRenderOpacity(1.0f);
}

// �֐����FBeginTick
// ���@���Ffloat InDeltaTime
// �߂�l�Fvoid
// �������e�F�J�n�����b�̏���
void UTitle::BeginTick(float InDeltaTime)
{
	//�O���̏���
	if (!_beginAfter)
	{
		_beginblackoutOpacity += InDeltaTime * 2.0f;

		//0.5�b�o�߂�����
		if (_beginblackoutOpacity >= 1.0f)
		{
			_beginAfter = true;
		}
	}
	//�㔼�̏���
	else
	{		
		//�J�n���̈Ö��̓����x�����X�ɉ�����
		_beginblackoutOpacity -= InDeltaTime * 2.0f;
		_beginblackoutImage->SetRenderOpacity(_beginblackoutOpacity);

		//�����ɂȂ�����
		if (_beginblackoutOpacity < 0.0f)
		{
			//�Ö�������
			_beginblackoutImage->RemoveFromParent();
		}
	}
}

// �֐����FTitleLogoScaleUpDown
// ���@���Ffloat InDeltaTime
// �߂�l�Fvoid
// �������e�F�^�C�g�����S�̊g�k
void UTitle::TitleLogoScaleUpDown(float InDeltaTime)
{
	//�g��
	if (_logoScaleUpDown)
	{
		_logoRenderScale += InDeltaTime / 10.0f;

		if (_logoRenderScale > 1.0f)
		{
			//���̃t���[�����烍�S���k��������
			_logoScaleUpDown = false;
		}
		else
		{
			//���S�̃T�C�Y��K�p
			_titleLogo->SetRenderScale(FVector2D(_logoRenderScale, _logoRenderScale));
		}
	}
	//�k��
	else
	{
		_logoRenderScale -= InDeltaTime / 10.0f;

		if (_logoRenderScale < 0.85f)
		{
			//���̃t���[�����烍�S���g�傳����
			_logoScaleUpDown = true;
		}
		else
		{
			//���S�̃T�C�Y��K�p
			_titleLogo->SetRenderScale(FVector2D(_logoRenderScale, _logoRenderScale));
		}
	}
		
}

// �֐����FStartPressed
// ���@���F�Ȃ�
// �߂�l�Fvoid
// �������e�F�X�e�[�W�Z���N�g�ɑJ�ڂ���{�^��
void UTitle::StartPressed()
{
	//�Ö���UI�𐶐����A�X�e�[�W�Z���N�g�֑J��
	pm_ui_blackout = CreateWidget<UBlackOut>(GetWorld(), m_ui_blackout);
	if (pm_ui_blackout){
		pm_ui_blackout->AddToViewport();
		pm_ui_blackout->SetOpenLevelName("Master_StageSelect");
	}

	//�X�^�[�g����炷
	if (_seMap["start"] != nullptr) _seManager->PlaySE2D("start");
}

// �֐����FEndPressed
// ���@���F�Ȃ�
// �߂�l�Fvoid
// �������e�F�Q�[���������I��������{�^��
void UTitle::EndPressed()
{
	UKismetSystemLibrary::QuitGame(this, UGameplayStatics::GetPlayerController(this,0),
		EQuitPreference::Quit, false);
}

// �֐����FOptionPressed
// ���@���F�Ȃ�
// �߂�l�Fvoid
// �������e�F�Q�[���������I��������{�^��
void UTitle::OptionPressed()
{
	//�I�v�V������UI�𐶐�
	pm_ui_OptionTitle = CreateWidget<UUserWidget>(GetWorld(), m_ui_OptionTitle);
	if (pm_ui_OptionTitle){
		pm_ui_OptionTitle->AddToViewport();
	}

	//�Z���N�g����炷
	if (_seMap["select"] != nullptr) _seManager->PlaySE2D("select");
}
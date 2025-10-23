//--------------------------------------------------------------------
// �t�@�C���� �FTitle.h
// �T�v       �F�^�C�g����ʂł̃��C����UI
// �쐬��     �F0231�{��
// �X�V���e   �F02/24�@�쐬�A
//--------------------------------------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "prototype/SEManager.h"
#include "BlackOut.h"
#include "Title.generated.h"

UCLASS()
class PROTOTYPE_API UTitle : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void NativeConstruct() override;

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	void init();

	void BeginTick(float InDeltaTime);

	void TitleLogoScaleUpDown(float InDeltaTime);

	UFUNCTION(BlueprintCallable)
	void StartPressed();
	UFUNCTION(BlueprintCallable)
	void EndPressed();
	UFUNCTION(BlueprintCallable)
	void OptionPressed();

private:
	UPROPERTY()
	TObjectPtr<USEManager> _seManager = nullptr;	//SEManager

	UPROPERTY(EditAnywhere, Category = "Sound")
	TMap<FName, TObjectPtr<USoundBase>> _seMap;		//SE

	UPROPERTY(EditAnywhere, Category = "BGM")
	TObjectPtr<USoundBase> TitleBGM;		//BGM

	UPROPERTY()
	TObjectPtr<UButton> _startButton;	//�X�^�[�g�{�^��

	UPROPERTY()
	TObjectPtr<UButton> _endButton;		//�G���h�{�^��

	UPROPERTY()
	TObjectPtr<UButton> _optionButton;	//�I�v�V�����{�^��

	UPROPERTY()
	TObjectPtr<UImage> _beginblackoutImage;	//�J�n���̈Ö�

	UPROPERTY()
	TObjectPtr<UImage> _titleLogo;	//�^�C�g�����S

	//--------�I�v�V����UI
	UPROPERTY(EditAnywhere, Category = "UI_Option")
	TSubclassOf<UUserWidget> m_ui_OptionTitle;

	UPROPERTY()
	UUserWidget* pm_ui_OptionTitle = nullptr;
	//---------------------------------

	//--------�Ö�UI
	UPROPERTY(EditAnywhere, Category = "UI_BlackOut")
	TSubclassOf<UBlackOut> m_ui_blackout;

	UPROPERTY()
	UBlackOut* pm_ui_blackout = nullptr;
	//---------------------------------

	//--------�f���v���C���[�r�[UI
	UPROPERTY(EditAnywhere, Category = "UI_DemoPlay")
	TSubclassOf<UUserWidget> m_ui_demoplay;

	UPROPERTY()
	UUserWidget* pm_ui_demoplay = nullptr;
	//---------------------------------

	//--------�^�C�g����ʂ��J���Ȃ���UI(�{�^��)
	UPROPERTY(EditAnywhere, Category = "UI_OpenTitle")
	TSubclassOf<UUserWidget> m_ui_openTitle;

	UPROPERTY()
	UUserWidget* pm_ui_openTitle = nullptr;
	//---------------------------------

	float _beginblackoutOpacity = 0.0f;	//�J�n���̈Ö��̓����x

	float _logoRenderScale = 0.85f; //���S�̃T�C�Y

	float _time = 0.0f;	//����

	bool _beginAfter = false;	//�J�n���琔�b�̏����̂��߂̕ϐ�

	bool _logoScaleUpDown = true;	//true�Ŋg��Afalse�ŏk��

	bool _createDemo = false;	//�f���v���C���[�r�[UI�𐶐�������
};

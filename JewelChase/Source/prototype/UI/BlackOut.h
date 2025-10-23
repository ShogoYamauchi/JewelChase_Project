//--------------------------------------------------------------------
// �t�@�C���� �FBlackOut.h
// �T�v       �F�Ö���UI
// �쐬��     �F0231�{��
// �X�V���e   �F02/24�@�쐬�A
//--------------------------------------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "BlackOut.generated.h"

UCLASS()
class PROTOTYPE_API UBlackOut : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void NativeConstruct() override;

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SetOpenLevelName(FName name) { _lvName = name; }	//�ǂ̃��x���ɑJ�ڂ��邩�w��

private:
	FName _lvName;	//���ɑJ�ڂ��郌�x��

	UPROPERTY()
	TObjectPtr<UImage> _blackoutImage;	//�Ö��̉摜

	float _time = 0.0f;	//�o�ߎ���
};

// �C���N���[�h�K�[�h
#pragma once

// �C���N���[�h
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "JJPerfectWidget.generated.h"

UCLASS()
class PROTOTYPE_API UJJPerfectWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// �A�j���[�V�������i�[����ϐ�
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* PerfectAnimation;
};

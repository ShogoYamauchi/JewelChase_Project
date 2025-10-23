//--------------------------------------------------------------------
// �t�@�C���� �FBlackOut.cpp
// �T�v       �F�Ö���UI
// �쐬��     �F0231�{��
// �X�V���e   �F02/24�@�쐬�A
//--------------------------------------------------------------------

#include "BlackOut.h"
#include "Kismet/GameplayStatics.h"

void UBlackOut::NativeConstruct()
{
	Super::NativeConstruct();

	//�Ö��̉摜���擾���A�����ɂ���
	_blackoutImage = Cast<UImage>(GetWidgetFromName("Image"));
	_blackoutImage->SetRenderOpacity(0.0f);
}

void UBlackOut::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	_time += InDeltaTime;

	_blackoutImage->SetRenderOpacity(_time * 1.5f);

	//���̃��x���ɑJ��
	if (_blackoutImage->GetRenderOpacity() > 2.0f)
	{
		UGameplayStatics::OpenLevel(GetWorld(), FName(_lvName));
	}
}
//--------------------------------------------------------------------
//����ҁ@�F���@���
//��������F2025/02/04
//�ŏI�X�V�F2025/02/10
//�T�@�v�@�FSE���Ǘ�����
//--------------------------------------------------------------------

#include "SEManager.h"
#include "Kismet/GameplayStatics.h"

USEManager* USEManager::GetInstance(UObject* WorldContextObject)
{
	if (!WorldContextObject)
	{
		return nullptr;
	}

	UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(WorldContextObject);
	return GameInstance ? GameInstance->GetSubsystem<USEManager>() : nullptr;
}

void USEManager::RegisterSE(FName key, USoundBase* sound)
{
	if (!sound)
	{
		return;
	}

	_seMap.Add(key, sound);
}

void USEManager::PlaySE2D(FName key)
{
	if (_seMap.Contains(key))
	{
		UE_LOG(LogTemp, Log, TEXT("PlaySE2D : %s"), *key.ToString());
		
		// ��񂾂��Đ��i���[�v���Ȃ��j
		UGameplayStatics::PlaySound2D(GWorld, _seMap[key]);
	}
}

void USEManager::PlaySE3D(UObject* worldContextObject, USoundBase* sound, FName key, FVector location)
{
	if (sound)
	{
		UGameplayStatics::PlaySoundAtLocation(worldContextObject, sound, location);
	}
}

void USEManager::PlaySE2DLoop(FName key)
{
	if (_seMap.Contains(key))
	{
		// ���łɃ��[�v�Đ�����Ă���Ȃ牽�����Ȃ�
		if (_loopingSEMap.Contains(key))
		{
			return;
		}

		// AudioComponent ���쐬
		UAudioComponent* AudioComp = UGameplayStatics::SpawnSound2D(GWorld, _seMap[key]);
		if (AudioComp)
		{
			AudioComp->Play();
			_loopingSEMap.Add(key, AudioComp);
		}
	}
}

void USEManager::PlayeSE3DLoop(UObject* worldContextObject, FName key)
{
	if (_seMap.Contains(key))
	{
		// ���łɃ��[�v�Đ�����Ă���Ȃ牽�����Ȃ�
		if (_loopingSEMap.Contains(key))
		{
			return;
		}

		// AudioComponent ���쐬
		UAudioComponent* AudioComp = UGameplayStatics::SpawnSound2D(worldContextObject, _seMap[key]);
		if (AudioComp)
		{
			AudioComp->Play();
			_loopingSEMap.Add(key, AudioComp);
		}
	}
}

void USEManager::StopSE(FName key)
{
	if (_loopingSEMap.Contains(key))
	{
		UAudioComponent* AudioComp = _loopingSEMap[key];
		if (AudioComp)
		{
			//�����N���b�V������
			AudioComp->Stop();
		}
		_loopingSEMap.Remove(key);
	}
}
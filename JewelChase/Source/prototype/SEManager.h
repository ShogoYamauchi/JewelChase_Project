//--------------------------------------------------------------------
//����ҁ@�F���@���
//��������F2025/02/04
//�ŏI�X�V�F2025/02/10
//�T�@�v�@�FSE���Ǘ�����
//--------------------------------------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundBase.h"
#include "SEManager.generated.h"

	/* ����Manager�̎g����
	//#include"SEManager.h"���C���N���[�h����
	//SE��o�^����ꍇ��USoundBase*�^�̕ϐ���
	//UPROPERTY(EditAnywhere)�ŗp�ӂ�BP���ŃA�^�b�`����

	UPROPERTY(EditAnywhere)
	USoundBase*�@Sound;		//�o�^������SE�܂���BGM

	//�C���X�^���X���擾
	USEManager _seManager = USEManager::GetInstance(this);

	// SE ��o�^
	_seManager->RegisterSE(TEXT("Sound"), Sound);

	// 2D SE �� 1 �񂾂��Đ�
	_seManager->PlaySE2D(TEXT("Sound"));

	// 2D SE �����[�v�Đ�
	_seManager->PlaySE2DLoop(TEXT("Sound"));

	// ���[�vSE���~
	_seManager->StopSE(TEXT("Sound"));
	*/

UCLASS()
class PROTOTYPE_API USEManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	USEManager() {}
	//void BeginDestroy() override {}		//�f�X�g���N�^
	~USEManager() {}		//�f�X�g���N�^

	//�V���O���g�����擾
	UFUNCTION(BlueprintPure, Category = "MySingleton")
	static USEManager* GetInstance(UObject* WorldContextObject);

	//----------------------------------
	// �֐����FRegisterSE
	// ���@���FFName,USoundBase*
	// �߂�l�Fvoid
	// SE��o�^
	//----------------------------------
	UFUNCTION(BlueprintCallable, Category = "Sound")
	void RegisterSE(FName key, USoundBase* sound);

	//----------------------------------
	// �֐����FPlaySE2D
	// ���@���FUObject*,WorldContextObject,FName
	// �߂�l�Fvoid
	// SE���Đ�
	//----------------------------------
	UFUNCTION(BlueprintCallable, Category = "Sound")
	void PlaySE2D(FName key);

	//----------------------------------
	// �֐����FPlaySE3D
	// ���@���FUObject*,WorldContextObject,FName
	// �߂�l�Fvoid
	// SE���Đ�
	//----------------------------------
	UFUNCTION(BlueprintCallable, Category = "Sound")
	void PlaySE3D(UObject* worldContextObject, USoundBase* sound, FName key, FVector location);

	//----------------------------------
	// �֐����FPlaySE2DLoop
	// ���@���F����
	// �߂�l�Fvoid
	// SE�����[�v�Đ�
	//----------------------------------
	UFUNCTION(BlueprintCallable, Category = "Sound")
	void PlaySE2DLoop(FName Key);

	//----------------------------------
	// �֐����FPlayeSE3DLoop
	// ���@���F����
	// �߂�l�Fvoid
	// SE�����[�v�Đ�
	//----------------------------------
	UFUNCTION(BlueprintCallable, Category = "Sound")
	void PlayeSE3DLoop(UObject* worldContextObject, FName key);

	//----------------------------------
	// �֐����FStopSE
	// ���@���FFName
	// �߂�l�Fvoid
	// SE���~
	//----------------------------------
	UFUNCTION(BlueprintCallable, Category = "Sound")
	void StopSE(FName key);

private:

	//SE�f�[�^
	UPROPERTY()
	TMap<FName, TObjectPtr<USoundBase>> _seMap;

	//���[�v�p��AudioComponent���Ǘ�
	UPROPERTY()
	TMap<FName, TObjectPtr<UAudioComponent>> _loopingSEMap;
};

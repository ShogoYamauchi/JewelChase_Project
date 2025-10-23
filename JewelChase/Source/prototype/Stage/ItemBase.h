//--------------------------------------------------------------------
// �t�@�C���� �FItemBase.h
// �T�v       �F�A�C�e���̊�Ղ̃N���X�B�@�\�͓��ɂȂ�
// �쐬��     �F0231�{��
// �X�V���e   �F1/19�@�쐬
//--------------------------------------------------------------------
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemBase.generated.h"

UCLASS()
class PROTOTYPE_API AItemBase : public AActor
{
	GENERATED_BODY()

private:	
	void UptoDestroy();

protected:	
	virtual void BeginPlay() override;	

public:
	AItemBase();
	virtual void Tick(float DeltaTime) override;

	void SetBeginZpos();
	float GetBeginZpos();
	UFUNCTION(BlueprintCallable)
	void bgetON();
	bool Getbget() const { return bget; }

private:
	float BeginZpos;
	bool bget;
	float getZpos;
};

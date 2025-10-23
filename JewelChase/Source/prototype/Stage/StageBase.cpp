//--------------------------------------------------------------------
// �t�@�C���� �FStageBase.cpp
// �T�v       �F�X�e�[�W�i��Q����G�j�̐����𐧌䂷��N���X
// �쐬��     �F0231�{��
// �X�V���e   �F11/25�@�쐬�A�v���p�e�B�ƃ��\�b�h���쐬
//              11/29  �X�e�[�W�}�l�[�W���[�����csv�p�X�擾�𒲐���
//--------------------------------------------------------------------

#include "StageBase.h"
#include "StageData.h"
#include "StageManager.h"
#include "prototype/Enemy/HelicopterAttackComponent.h"
#include "prototype/Player/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

//�R���X�g���N�^
AStageBase::AStageBase()
    : _bspawnstage(false)
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
}

//�������̂ݏ���
void AStageBase::BeginPlay()
{
    Super::BeginPlay();

    pStageMng = SearchStageMng();
    pPlayer = UGameplayStatics::GetActorOfClass(GetWorld(), APlayerCharacter::StaticClass());

    _stagelane = Cast<AStageManager>(pStageMng)->Get_stagelane();
    _movespeed = Cast<AStageManager>(pStageMng)->Get_movespeed();

    //�X�e�[�W�ԍ����ő�ł͂Ȃ��Ƃ��X�e�[�W��ǂݍ���
    if (Cast<AStageManager>(pStageMng)->Get_stagenum() <= Cast<AStageManager>(pStageMng)->Get_maxstagenum())
    {
        //�X�e�[�W�}�l�[�W������csv���擾
        StageDataTable = Cast<AStageManager>(pStageMng)->Get_csvpath();

        SpawnObject();
    }
    //�X�e�[�W�ԍ����ő�̂Ƃ��S�[����ǂݍ���
    else
    {
        //�X�e�[�W�}�l�[�W������csv���擾
        StageDataTable = Cast<AStageManager>(pStageMng)->Get_goalpath();

        SpawnObject();
    }
    FName ItemTag = "Item";
    TArray<AActor*> Items;
    UGameplayStatics::GetAllActorsWithTag(GetWorld(), ItemTag, Items);

    Cast<AStageManager>(pStageMng)->SetItems(Items);
   
}

//���t���[������
void AStageBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

     if (Cast<APlayerCharacter>(pPlayer)->GetHP() > 0 && Cast<AStageManager>(pStageMng) ->get_bStart())
     {
        SpawnNextStage();

        DeleteStage();

        Move();
     }
}

// �֐����FSpawnObject
// ���@���F�Ȃ�
// �߂�l�Fvoid
// �������e�F��Q�����X�e�[�W�ɔz�u���A�e�q�֌W���\�z
void AStageBase::SpawnObject()
{
    CommonSpawn(-1000.0f);

    FTransform SpawnTr;
    FVector pos;
    AActor* spawnActor = nullptr;

    if (StageDataTable == nullptr)
    {
        // �Q�Ƃł��Ȃ��ꍇ�͓����ǂ�.
        StageDataTable.LoadSynchronous();
    }

    if (StageDataTable)
    {
        // �f�[�^�e�[�u������S�f�[�^���擾����.
        TArray<FName> RowNames = StageDataTable->GetRowNames();

        for (auto RowName : RowNames)
        {
            const FMapStruct* data = StageDataTable->FindRow<FMapStruct>(RowName, FString());
            if (!data)
            {
                continue;
            }

            //�I�u�W�F�N�g�������͈͊O�̂��̂Ȃ琶�����Ȃ�
            if (data->ylane > _stagelane)
            {

            }

            //csv�̃��[������ǂݎ��|�W�V��������
            float X = 500.0f * float(data->xlane);
            float Y = 180.0f * float(data->ylane - 4);
            float Z = 50.0f * float(data->zlane);

            pos = GetActorLocation() + FVector(X, Y, Z);

            SpawnTr.SetLocation(pos);

            //csv�f�[�^�̃I�u�W�F�N�g�^�C�v���Q�Ƃ��X�|�[��
            switch (data->ObjecType)
            {
            case 1://�S�~��
                if (_obstacles[0] != nullptr) {
                    spawnActor = GetWorld()->SpawnActor<AActor>(_obstacles[0], SpawnTr);
                }
                break;
            case 2://�X��
                if (_obstacles[1] != nullptr) {
                    spawnActor = GetWorld()->SpawnActor<AActor>(_obstacles[1], SpawnTr);
                }
                break;
            case 3://�o���P�[�h
                if (_obstacles[2] != nullptr) {
                    spawnActor = GetWorld()->SpawnActor<AActor>(_obstacles[2], SpawnTr);
                }
                break;
            case 4://�ԁi�_��J���[�j
                if (_obstacles[3] != nullptr) {
                    spawnActor = GetWorld()->SpawnActor<AActor>(_obstacles[3], SpawnTr);
                }
                break;
            case 5://�ԁi���J���[�j
                if (_obstacles[4] != nullptr) {
                    spawnActor = GetWorld()->SpawnActor<AActor>(_obstacles[4], SpawnTr);
                }
                break;
            case 6://�ԁi���c�J���[�j
                if (_obstacles[5] != nullptr) {
                    spawnActor = GetWorld()->SpawnActor<AActor>(_obstacles[5], SpawnTr);
                }
                break;
            case 7://�ԁi�R���J���[�j
                if (_obstacles[6] != nullptr) {
                    spawnActor = GetWorld()->SpawnActor<AActor>(_obstacles[6], SpawnTr);
                }
                break;
            case 8://�ԁi�{�ԃJ���[�j
                if (_obstacles[7] != nullptr) {
                    spawnActor = GetWorld()->SpawnActor<AActor>(_obstacles[7], SpawnTr);
                }
                break;
            case 9://�ԁi�X�{�J���[�j
                if (_obstacles[8] != nullptr) {
                    spawnActor = GetWorld()->SpawnActor<AActor>(_obstacles[8], SpawnTr);
                }
                break;
            case 10://�I�C����
                if (_obstacles[9] != nullptr) {
                    spawnActor = GetWorld()->SpawnActor<AActor>(_obstacles[9], SpawnTr);
                }
                break;


            case 11://�W���G��
                if (_jewels[0] != nullptr) {
                    spawnActor = GetWorld()->SpawnActor<AActor>(_jewels[0], SpawnTr);
                }
                break;
            case 12://�ԃW���G��
                if (_jewels[1] != nullptr) {
                    spawnActor = GetWorld()->SpawnActor<AActor>(_jewels[1], SpawnTr);
                }
                break;
            case 13://���W���G��
                if (_jewels[2] != nullptr) {
                    spawnActor = GetWorld()->SpawnActor<AActor>(_jewels[2], SpawnTr);
                }
                break;
            case 14://���W���G��
                if (_jewels[3] != nullptr) {
                    spawnActor = GetWorld()->SpawnActor<AActor>(_jewels[3], SpawnTr);
                }
                break;

            case 21://�̗͉�
                if (_Items[0] != nullptr) {
                    spawnActor = GetWorld()->SpawnActor<AActor>(_Items[0], SpawnTr);
                }
                break;
            case 22://�}�O�l�b�g
                if (_Items[1] != nullptr) {
                    spawnActor = GetWorld()->SpawnActor<AActor>(_Items[1], SpawnTr);
                }
                break;
            case 23://�J�[�h�ω�"J"
                if (_Items[2] != nullptr) {
                    spawnActor = GetWorld()->SpawnActor<AActor>(_Items[2], SpawnTr);
                }
                break;
            case 24://�J�[�h�ω�"Q"
                if (_Items[3] != nullptr) {
                    spawnActor = GetWorld()->SpawnActor<AActor>(_Items[3], SpawnTr);
                }
                break;
            case 25://�J�[�h�ω�"K"
                if (_Items[4] != nullptr) {
                    spawnActor = GetWorld()->SpawnActor<AActor>(_Items[4], SpawnTr);
                }
                break;

            case 31://�x�@
                if (_enemys[0] != nullptr) {
                    spawnActor = GetWorld()->SpawnActor<AActor>(_enemys[0], SpawnTr);
                }
                break;
            case 32://�w���R�v�^�[
                if (_enemys[1] != nullptr) {
                    Cast<AStageManager>(pStageMng)->SetHeliStatus(int(data->HeliStatus));
                    spawnActor = GetWorld()->SpawnActor<AActor>(_enemys[1], SpawnTr);
                    //Cast<UHelicopterAttackComponent>(spawnActor)->SetMoveTargetNumber(data->HeliStatus); // �N���b�V�������
                    
                }
                break;
            case 33://�|���J�[
                if (_enemys[2] != nullptr) {
                    spawnActor = GetWorld()->SpawnActor<AActor>(_enemys[2], SpawnTr);
                }
                break;
            case 91://Stage1�S�[��
                if (_commons[3] != nullptr) {
                    CommonSpawn(1000.0f);
                    spawnActor = GetWorld()->SpawnActor<AActor>(_commons[3], SpawnTr);
                }
                break;
            case 92://Stage2�S�[��
                if (_commons[4] != nullptr) {
                    CommonSpawn(1000.0f);
                    spawnActor = GetWorld()->SpawnActor<AActor>(_commons[4], SpawnTr);
                }
                break;
            case 93://Stage3�S�[��
                if (_commons[5] != nullptr) {
                    CommonSpawn(1000.0f);
                    spawnActor = GetWorld()->SpawnActor<AActor>(_commons[5], SpawnTr);
                }
                break;
            default:
                break;
            }

            //StageBase��e�ɂ��A�e�q�֌W���\�z
            // �Ë�����
            if (IsValid(spawnActor) && data->ObjecType != 32 && data->ObjecType != 33) {
                spawnActor->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
            }
        }
    }
}

// �֐����FCommonSpawn
// ���@���F�Ȃ�
// �߂�l�Fvoid
// �������e�F�S�X�e�[�W���ʂ̃I�u�W�F�N�g���X�|�[��
void AStageBase::CommonSpawn(float xPos)
{
    FTransform SpawnTr;
    FVector pos;
    AActor* spawnActor = nullptr;

    float ypos = float(_stagelane) * 180.0f;

    //���̕ǂ��쐬
    for (int i = 1; i >= -1; i -= 2)
    {
        SpawnTr.SetRotation(FQuat(0.0f, 0.0f, 0.0f, 1.0f));
        pos = GetActorLocation() + FVector(xPos, float(i) * (ypos / 2.0f), 0.0f);
        SpawnTr.SetLocation(pos);

        if (i == 1) {
            FQuat newrotation = FQuat(0.0f, 0.0f, 180.0f, 1.0f);
            SpawnTr.SetRotation(newrotation);
        }

        spawnActor = GetWorld()->SpawnActor<AActor>(_commons[0], SpawnTr);

        //StageBase��e�ɂ��A�e�q�֌W���\�z
        if (IsValid(spawnActor)) {
            spawnActor->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
        }
    }

    //�n�ʂ̓������𐶐�
    {
        pos = GetActorLocation() + FVector(xPos, 0.0f, 0.0f);
        SpawnTr.SetLocation(pos);

        spawnActor = GetWorld()->SpawnActor<AActor>(_commons[1], SpawnTr);

        //StageBase��e�ɂ��A�e�q�֌W���\�z
        if (IsValid(spawnActor)) {
            spawnActor->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
        }
    }
}

// �֐����FSpawnEnemy
// ���@���F�Ȃ�
// �߂�l�Fvoid
// �������e�F�G�l�~�[���o��������
void AStageBase::SpawnEnemy()
{

}

// �֐����FSpawnNextStage
// ���@���F�Ȃ�
// �߂�l�Fvoid
// �������e�F���̃X�e�[�W���X�|�[��������
void AStageBase::SpawnNextStage()
{
    if (!Cast<AStageManager>(pStageMng)->Get_bgoalspawn() && GetActorLocation().X < 1000.0f && !_bspawnstage)
    {
        FTransform SpawnTr;
        SpawnTr.SetLocation(FVector(5000.f, 0.f, 0.f));

        if (_commons[2] != nullptr) {
            GetWorld()->SpawnActor<AActor>(_commons[2], SpawnTr);
        }

        _bspawnstage = true;
    }
}

// �֐����FMove
// ���@���F�Ȃ�
// �߂�l�Fvoid
// �������e�F�X�e�[�W���v���C�������i-X�j�ֈړ�������
void AStageBase::Move()
{
    FVector nextpos = GetActorLocation() + FVector(-_movespeed, 0.0f, 0.0f);

    SetActorLocation(nextpos);
}

// �֐����FDeleteStage
// ���@���F�Ȃ�
// �߂�l�Fvoid
// �������e�F�X�e�[�W������pos�܂ŗ�����폜
void AStageBase::DeleteStage()
{
    if (GetActorLocation().X < -5000.0f)
    {
        Cast<AActor>(this)->Destroy();
    }
}

// �֐����FSearchStageMng
// ���@���F�Ȃ�
// �߂�l�FAActor*
// �������e�F�X�e�[�W�}�l�[�W���[��T���A�Ԃ�
AActor* AStageBase::SearchStageMng()
{
    //AStageManager�^�̃I�u�W�F�N�g��T���A�Ǘ�
    TSubclassOf<AStageManager> findClass;
    findClass = AStageManager::StaticClass();

    AActor* stageManager = UGameplayStatics::GetActorOfClass(GetWorld(), findClass);

    //AStageManager�^�̃I�u�W�F�N�g���P�ȏ゠���
    if (IsValid(stageManager))
    {
        return stageManager;
    }
    return nullptr;
}
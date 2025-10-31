//--------------------------------------------------------------------
// ファイル名	：JustJumpActorComponent.cpp
// 概要　　　	：ジャストジャンプ
// 作成者　　	：神野琉生
// 更新内容　	：1/27 作成
//				  1/29 LineTraceSingleByObjectTypeを使ったレイキャストの作成（動作未確認）
//				  2/1  処理完成（未調整、未実装）
//                2/11 処理完成（未調整）
//                2/23 調整完了
//--------------------------------------------------------------------

// インクルード
#include "JustJumpActorComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/EngineTypes.h"
#include "DrawDebugHelpers.h"			// トレースのデバッグの時に必要なヘッダーファイル

// プロパティ変更を保持する関数
#if WITH_EDITOR
void UJustJumpActorComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	// プロパティが変更されたことをエディタに通知
	Modify();
}
#endif

UJustJumpActorComponent::UJustJumpActorComponent()
	: _eJumpStatus(EJumpStatus::EmptyJump)
	, _ownerActor(nullptr)
	, _halfBoxSize(FVector::ZeroVector)
	, _distancePlayer(50.0f)
	, _rayEnd(200.0f)
	, _rayBoxHeight(0.0f)
	, _minJustJumpDistance(0.0f)
	, _maxJustJumpDistance(0.0f)
{
	PrimaryComponentTick.bCanEverTick = true;

	// レイキャストで無視する対象の配列を初期化する
	_ignoreItemsActor.Reset();
	_ignoreSmogsActor.Reset();
}

void UJustJumpActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// このコンポーネントがついているActorを取得
	_ownerActor = GetOwner<AActor>();

	if (!_ownerActor)
	{
		return;
	}

	// レイキャストで無視するアクターをタグで取得して保持する
	FName ItemTag = "Item";
	FName SmogTag = "Smog";
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), ItemTag, _ignoreItemsActor);
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), SmogTag, _ignoreSmogsActor);

	// 無視するリストに自分自身と特定のアクターを追加
	_ignoreParams.ClearIgnoredActors();				     // 配列のリセット
	_ignoreParams.AddIgnoredActor(_ownerActor);          // 自分
	_ignoreParams.AddIgnoredActors(_ignoreSmogsActor);	 // 霧
	_ignoreParams.AddIgnoredActors(_ignoreItemsActor);	 // アイテム

	// レイキャストで取得するチャンネルを設定
	TArray<ECollisionChannel> ObjectChannels = {
		ECollisionChannel::ECC_WorldDynamic,
		ECollisionChannel::ECC_WorldStatic
	};

	// すべてのチャンネルを取得するチャンネルに追加
	for (const ECollisionChannel& Channel : ObjectChannels)
	{
		_objectQueryParams.AddObjectTypesToQuery(Channel);
	}
}

void UJustJumpActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

//----------------------------------
// 関数名：JustJumpRay
// 引　数：なし
// 戻り値：EJumpStatus型
// 内　容：ジャストジャンプか判断するレイの作成
//----------------------------------
EJumpStatus UJustJumpActorComponent::JustJumpRay()
{
	// ジャンプの列挙型を初期化
	_eJumpStatus = EJumpStatus::EmptyJump;

	// ワールド内のアイテムをレイキャストで無視するリストに追加
	AddItemToIgnore();

	// 所有Actorがなかったら処理終了
	if (!_ownerActor)
	{
		return _eJumpStatus;
	}

	// プレイヤーの距離
	FVector PlayerLocation = _ownerActor->GetActorLocation();
	// プレイヤーの回転
	FRotator PlayerRotation = _ownerActor->GetActorRotation();

	// レイキャストの高さを設定
	PlayerLocation.Z += _rayBoxHeight;

	// ボックスの始点をプレイヤーの前方に設定
	FVector TraceStart = PlayerLocation + PlayerRotation.Vector() * _distancePlayer;
	// ボックスの終点をさらに前方に設定
	FVector TraceEnd = TraceStart + PlayerRotation.Vector() * _rayEnd;

	// レイキャストの結果の格納用
	FHitResult Hit;

	// レイキャストを実行
	GetWorld()->SweepSingleByObjectType(
		OUT Hit,									  // 当たったもの
		TraceStart,								      // 始点座標
		TraceEnd,									  // 終点座標
		FQuat::Identity,							  // トレースの形状の回転
		_objectQueryParams,							  // 衝突チャネル
		FCollisionShape::MakeBox(_halfBoxSize),       // トレースの形状を指定
		_ignoreParams								  // 無視するアクターの設定
	);

#if true
	// デバッグ用のログ出力、ジャストジャンプのパラメータの値を出力
	UE_LOG(LogTemp, Warning, TEXT("Params.HalfBoxSize: %s"), *_halfBoxSize.ToString());
	UE_LOG(LogTemp, Warning, TEXT("Params.DistancePlayer: %f"), _distancePlayer);
	UE_LOG(LogTemp, Warning, TEXT("Params.RayBoxHeight: %f"), _rayBoxHeight);
	UE_LOG(LogTemp, Warning, TEXT("Params.MinJustJumpDistance: %f"), _minJustJumpDistance);
	UE_LOG(LogTemp, Warning, TEXT("Params.MaxJustJumpDistance: %f"), _maxJustJumpDistance);

	// ジャストかを判断する範囲の表示
	// 線で表示
	DrawDebugLine(
		GetWorld(),          // 描画を行うワールド
		TraceStart,          // 始点
		TraceEnd,            // 終点
		FColor::Green,       // 色
		false,               // true: 永続的に描画 / false: 一定時間で消える
		1.0f,                // 描画が消えるまでの時間（-1.0f ならフレームごとに更新）
		0,                   // 描画の優先度（0: 通常, 1: 上位）
		1.0f                 // 太さ
	);

	// 四角で表示
	DrawDebugBox(
		GetWorld(),				          // 描画を行うワールド
		(TraceStart + TraceEnd) / 2.0f,   // 中心座標
		_halfBoxSize,		              // 半径
		FQuat::Identity,		          // 回転
		FColor::Red,			          // 色
		false,					          // true: 永続的に描画 / false: 一定時間で消える
		1.0f,					          // 描画が消えるまでの時間（-1.0f ならフレームごとに更新）
		0,						          // 描画の優先度（0: 通常, 1: 上位）
		2.0f					          // 線の太さ
	);

	// ジャストジャンプの始点
	FVector JustJumpRayStart = PlayerLocation + PlayerRotation.Vector() * (_distancePlayer + _minJustJumpDistance);
	// ジャストジャンプの終点
	FVector JustJumpRayEnd = TraceStart + PlayerRotation.Vector() * _maxJustJumpDistance;
	// ジャストジャンプの中心座標
	FVector JustJumpCenter = PlayerLocation + PlayerRotation.Vector() * (_distancePlayer + (_maxJustJumpDistance - _minJustJumpDistance) / 2.0f);

	// ジャストジャンプの範囲を表示する
	// 線で表示
	DrawDebugLine(
		GetWorld(),          // 描画を行うワールド
		JustJumpRayStart,    // 始点
		JustJumpRayEnd,      // 終点
		FColor::Blue,        // 色
		false,               // true: 永続的に描画 / false: 一定時間で消える
		1.0f,                // 描画が消えるまでの時間（-1.0f ならフレームごとに更新）
		0,                   // 描画の優先度（0: 通常, 1: 上位）
		1.0f                 // 太さ
	);

	// 四角で表示
	DrawDebugBox(
		GetWorld(),				// 描画を行うワールド
		JustJumpCenter,		    // 中心座標
		_halfBoxSize,	        // 半径
		FQuat::Identity,		// 回転
		FColor::Blue,			// 色
		false,					// true: 永続的に描画 / false: 一定時間で消える
		1.0f,					// 描画が消えるまでの時間（-1.0f ならフレームごとに更新）
		0,						// 描画の優先度（0: 通常, 1: 上位）
		2.0f					// 太さ
	);

#endif

	// レイがActorとヒットしたら行う処理
	if (Hit.bBlockingHit == true && Hit.GetActor())
	{
		// ヒットしたものからActorの取得
		const AActor* HitActor = Hit.GetActor();

		if (HitActor == nullptr)
		{
			// ヒットしたものがなかったら空のジャンプを返す
			_eJumpStatus = EJumpStatus::EmptyJump;
			return _eJumpStatus;
		}

		if (HitActor->ActorHasTag(FName("Enemy")))
		{
			// ヒット地点までの距離を取得
			float HitDistance = Hit.Distance;

			// ジャストジャンプの範囲内にあるかを判定
			if (_minJustJumpDistance <= HitDistance && HitDistance <= _maxJustJumpDistance)
			{
				_eJumpStatus = EJumpStatus::JustJump;    // ジャストジャンプ
			}
			else
			{
				_eJumpStatus = EJumpStatus::NormalJump;  // 通常のジャンプ
			}
		}
	}

	// 判定結果を返す
	return _eJumpStatus;
}

//----------------------------------
// 関数名：AddItemToIgnore
// 引　数：なし
// 戻り値：なし
// 内　容：ワールドにあるアイテムを無視するリストに追加
//----------------------------------
void UJustJumpActorComponent::AddItemToIgnore()
{
	// レイキャストで無視するアイテムの配列を初期化する
	_ignoreItemsActor.Reset();

	// レイキャストで無視するアクターをタグで取得して保持する
	FName ItemTag = "Item";
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), ItemTag, _ignoreItemsActor);

	// 無視するアクターを追加
	_ignoreParams.AddIgnoredActors(_ignoreItemsActor);
}
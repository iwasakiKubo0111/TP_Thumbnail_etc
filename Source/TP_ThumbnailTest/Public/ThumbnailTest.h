// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SubWindowBase.h"
#include "ThumbnailTest.generated.h"

/**
 * WBP_ThumbnailTestの親クラス
 */
UCLASS()
class TP_THUMBNAILTEST_API UThumbnailTest : public UUserWidget
{
	GENERATED_BODY()

public:
	// コンストラクタ 本体が実装されていない場合ライブコーディングが失敗するのでコメントアウトする。
	//UThumbnailTest();

	virtual void NativeDestruct() override;

	// Widget版 Tick([MEMO]Widgetの場合NativeTickというものを使う)
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	virtual void OnWindowClosed();

	// ウィンドウ作成
	UFUNCTION(BlueprintCallable, Category = "ThumbnailTest|SubWindow")
	void CreateWindow(const FVector2D& windowSize, const FVector2D& windowPos, const FText& tilte);

	// ウィジット追加
	UFUNCTION(BlueprintCallable, Category = "ThumbnailTest|SubWindow")
	void SetWidget(class UWidget* setWidget);

	UFUNCTION(BlueprintCallable, Category = "ThumbnailTest|SubWindow")
	void DebugNowWindowsTitle();

private:
	// ウィンドウ情報
	TSharedPtr<class SWindow> m_CreateWindow;

	// 別で作成されれたウィジェット配置用
	TSharedPtr<class SOverlay> m_WindowOverlay;

	TSharedPtr<USubWindowBase> SubWindowClassInstance;


};

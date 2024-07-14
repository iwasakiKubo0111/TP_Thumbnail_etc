// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widgets/SWindow.h"
#include "Framework/Application/SlateApplication.h"
#include "SubWindowBase.generated.h"

/**
 * 
 */
UCLASS()
class TP_THUMBNAILTEST_API USubWindowBase : public UUserWidget
{
	GENERATED_BODY()

	//USubWindowBase(const TSharedPtr<SWindow>& InWindow);

	void NativeConstruct() override;

	virtual void NativeDestruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void OnSubWindowClosed(const TSharedRef<SWindow>& Window);

	//virtual void OnWindowClose() override;


public:
	// ウィンドウ情報
	TSharedPtr<class SWindow> m_Window;

	// 別で作成されたウィジェット配置用
	//TSharedPtr<class SOverlay> m_WindowOverlay;


	
};



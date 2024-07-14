// Fill out your copyright notice in the Description page of Project Settings.


#include "ThumbnailTest.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Slate.h"
#include "SlateCore.h"
#include "Engine/GameViewportClient.h"
#include "Engine/Engine.h"
#include "Components/Widget.h"

//このウィンドウが破棄される時に呼ばれる
void UThumbnailTest::NativeDestruct()
{
	Super::NativeDestruct();

	if (m_WindowOverlay) {
		// ここ重要。この処理をしないとベージコレクションされるまでリセットされないアクタのスレートポインタを保持している。というエラーが出る
		m_WindowOverlay.Get()->ClearChildren();
		m_WindowOverlay.Reset();
	}

	if (m_CreateWindow) {
		FSlateApplication::Get().RequestDestroyWindow(m_CreateWindow.ToSharedRef());
	}

	UKismetSystemLibrary::PrintString(GEngine->GetWorld(), TEXT("ウィンドウを破棄します"));
	
}

// Tick
void UThumbnailTest::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	// おまじない
	Super::NativeTick(MyGeometry, InDeltaTime);

	//文字化けする場合は[ファイル] > [名前をつけて<当該ファイル名>を保存] > [上書き保存]のプルダウン > UTF8 を選択で保存する。
	//UKismetSystemLibrary::PrintString(GEngine->GetWorld(), TEXT("C++ テスト"));

}

void UThumbnailTest::OnWindowClosed()
{
	UKismetSystemLibrary::PrintString(GEngine->GetWorld(), TEXT("OnWindowClosedが発火"));
}

/*
*	ウィンドウの作成
*	param : windowSize	ウィンドウのサイズ
*	param : windowPos	ウィンドウの位置
*	param : tilte		ウィンドウのタイトル
*/
void UThumbnailTest::CreateWindow(const FVector2D& windowSize, const FVector2D& windowPos, const FText& title)
{
	if (GEngine && GEngine->GameViewport) {
		// ウィンドウ作成
		m_CreateWindow = SNew(SWindow)
			.Title(title/*LOCTEXT("CreateWindow", "Title")*/)
			.AutoCenter(EAutoCenter::None)
			.ScreenPosition(windowPos)
			.ClientSize(windowSize)
			.CreateTitleBar(true);

		m_WindowOverlay = SNew(SOverlay);

		//ウィンドウに設定する
		m_CreateWindow->SetContent(m_WindowOverlay.ToSharedRef());

		// 作成したウィンドウを親ウィンドウを設定して即座表示する
		//FSlateApplication::Get().AddWindowAsNativeChild(m_CreateWindow.ToSharedRef(), GEngine->GameViewport->GetWindow().ToSharedRef(), true);
		FSlateApplication::Get().AddWindow(m_CreateWindow.ToSharedRef(),true);
		FSlateApplication::Get().SetKeyboardFocus(m_CreateWindow.ToSharedRef());
	}
}

/*
*	ウィジットの設定
*	param : setWidget 追加するウィジット
*/
void UThumbnailTest::SetWidget(UWidget* setWidget)
{
	if (m_WindowOverlay) {
		// ウィットを設定するためにオーバーレイに指定されたウィジェットを設定する
		auto OVerlaySlot = m_WindowOverlay.Get()->AddSlot();
		//m_WindowOverlay.
		OVerlaySlot.AttachWidget(setWidget->TakeWidget());
	}
}

void UThumbnailTest::DebugNowWindowsTitle()
{

	TArray<TSharedRef<SWindow>> windows = FSlateApplication::Get().GetTopLevelWindows();
	
	for (TSharedRef<SWindow> window : windows)
	{
		UKismetSystemLibrary::PrintString(GEngine->GetWorld(), window->GetTitle().ToString());
	}
	UKismetSystemLibrary::PrintString(GEngine->GetWorld(), TEXT("現在のGetTopLevelWindowsで取得した数は") + FString::FromInt(windows.Num()));
}


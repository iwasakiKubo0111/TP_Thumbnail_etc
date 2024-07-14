// Fill out your copyright notice in the Description page of Project Settings.


#include "SubWindowBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Widgets/SWindow.h"
#include "Framework/Application/SlateApplication.h"

//USubWindowBase::USubWindowBase(const TSharedPtr<SWindow>& InWindow) : Super(InWindow)
//{
//	UKismetSystemLibrary::PrintString(GEngine->GetWorld(), TEXT("サブウィンドウのOnSubWindowClosedが呼ばれました"));
//}

void USubWindowBase::NativeConstruct()
{
	Super::NativeConstruct();
	UKismetSystemLibrary::PrintString(GEngine->GetWorld(), TEXT("サブウィンドウのコンストラクタが呼ばれました"));

	m_Window = FSlateApplication::Get().GetActiveTopLevelWindow();
	//TSharedPtr<SWindow> window = this->GetClass();
	m_Window->SetOnWindowClosed(FOnWindowClosed::CreateUObject(this, &USubWindowBase::OnSubWindowClosed));
}

//このウィンドウが破棄される時に呼ばれる
void USubWindowBase::NativeDestruct()
{
	Super::NativeDestruct();

	//if (m_WindowOverlay) {
	//	// ここ重要。この処理をしないとベージコレクションされるまでリセットされないアクタのスレートポインタを保持している。というエラーが出る
	//	m_WindowOverlay.Get()->ClearChildren();
	//	m_WindowOverlay.Reset();
	//}

	if (m_Window) {
		FSlateApplication::Get().RequestDestroyWindow(m_Window.ToSharedRef());
	}
	UKismetSystemLibrary::PrintString(GEngine->GetWorld(), TEXT("サブウィンドウを破棄します"));
}

void USubWindowBase::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	// おまじない
	Super::NativeTick(MyGeometry, InDeltaTime);
	//UKismetSystemLibrary::PrintString(GEngine->GetWorld(), TEXT("!!"));
	//文字化けする場合は[ファイル] > [名前をつけて<当該ファイル名>を保存] > [上書き保存]のプルダウン > UTF8 を選択で保存する。
	//UKismetSystemLibrary::PrintString(GEngine->GetWorld(), TEXT("C++ テスト"));

}

void USubWindowBase::OnSubWindowClosed(const TSharedRef<SWindow>& Window)
{
	// サブウィンドウが閉じられたときの処理をここに記述
	UKismetSystemLibrary::PrintString(GEngine->GetWorld(), TEXT("サブウィンドウのOnSubWindowClosedが呼ばれました"));
	// ウィジェットの削除
	//this->RemoveFromParent();
	if (!IsPendingKill())
	{
		// 自身のインスタンスを削除
		UKismetSystemLibrary::PrintString(GEngine->GetWorld(), TEXT("UEGCにこのインスタンスの削除を指示"));
		this->ConditionalBeginDestroy();
	}

	//Window->RequestDestroyWindow();
	//FSlateApplication::Get().RequestDestroyWindow(Window);
}
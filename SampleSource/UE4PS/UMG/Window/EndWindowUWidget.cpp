// Fill out your copyright notice in the Description page of Project Settings.

#include "EndWindowUWidget.h"

/*
 */
void UEndWindowUWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//
	//

	m_textTitle = FindWidget<UTextBlock>(TEXT("TextTitle"));

	m_BtnReStart = FindWidget<UButton>(TEXT("ButtonReStart"));
	//m_BtnReStart->OnClicked.AddDynamic(this, &UEndWindowUWidget::RestartFunc);

	m_BtnEndGame = FindWidget<UButton>(TEXT("ButtonEndGame"));
	//m_BtnEndGame->OnClicked.AddDynamic(this, &UEndWindowUWidget::EndGameFunc);

}

/*

*/
void UEndWindowUWidget::ShowWindow(void* arg1, void* arg2)
{
	Super::ShowWindow(arg1, arg2);

	if (arg1 != nullptr) 
	{
		FString str = *(FString*)arg1;
		m_textTitle->SetText(FText::FromString(str));
	}
	
}

/*
 */
void UEndWindowUWidget::CloseWindow()
{
	Super::CloseWindow();
}

/*
 */
void UEndWindowUWidget::RestartFunc()
{
	UE_LOG(LogClass, Log, TEXT("RestartFunc"));

	UGameplayStatics::OpenLevel(GetWorld(), "FieldSample");
}

/*
 */
void UEndWindowUWidget::EndGameFunc()
{
	UE_LOG(LogClass, Log, TEXT("EndGameFunc"));

	GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RegisterUserWidget.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"
#include "Interfaces/IHttpRequest.h"
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"
#include "Components/CircularThrobber.h"
#include "UI/MessageUserWidget.h"


/* �����ʼ�� */
bool URegisterUserWidget::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	/* ���ذ�ť */
	BackBtn = Cast<UButton>(GetWidgetFromName(TEXT("Button_Back")));

	/* �ǳ������ */
	NicknameInput = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("EditableTextBox_Nickname")));

	/* ��������� */
	PasswordInput = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("EditableTextBox_Password")));

	/* ȷ����������� */
	RePasswordInput = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("EditableTextBox_RePassword")));

	/* ע���˺Ű�ť */
	RegBtn = Cast<UButton>(GetWidgetFromName(TEXT("Button_Reg")));

	/* ע�ᰴť����¼� */
	RegBtn->OnClicked.AddDynamic(this, &URegisterUserWidget::RegBtnOnClickedEvent);

	/* Loading */
	CircularThrobber = Cast<UCircularThrobber>(GetWidgetFromName(TEXT("CircularThrobber_Loading")));

	/* ��ʼ����Ϣ��ʾ�� */
	MessageWidget = Cast<UMessageUserWidget>(GetWidgetFromName(TEXT("BP_MessageUserWidget")));

	return true;
}

/* ע���˺Ű�ť����¼� */
void URegisterUserWidget::RegBtnOnClickedEvent()
{

	/* ��ȡ�ǳ� */
	FString Nickname = NicknameInput->GetText().ToString();

	/* ��ȡ���� */
	FString Password = PasswordInput->GetText().ToString();

	/* ��ȡȷ������ */
	FString RePassword = RePasswordInput->GetText().ToString();

	/* �ǳƳ��ȱ������1 */
	if (Nickname.Len() < 2) {
		MessageTip("Nickname need 2-6 characters!");
		return;
	}

	if (Password.IsEmpty() || RePassword.IsEmpty()) {
		MessageTip("please input password!");
		return;
	}

	/* �ж����������Ƿ�һ�� */
	if (!Password.Equals(RePassword))
	{
		MessageTip("twice password not same!");
		return;
	}

	/* ��ʾ����Ч�� */
	CircularThrobber->SetVisibility(ESlateVisibility::Visible);

	/* ���ð�ť������ */
	RegBtn->SetIsEnabled(false);

	/* �����˺�ע�� */
	AccountRegesterFromServer(Nickname, Password);
}

/*ע���˺ŷ���*/
void URegisterUserWidget::AccountRegesterFromServer(FString& Nickname, FString& Password)
{
	/* ����Ҫ�ύ��Json�ַ��� */
	FString RegisterInfo;

	/* ��������Jsonд���� */
	TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> JsonWriter = TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>::Create(&RegisterInfo);
	
	/* ��ʼд������ */
	JsonWriter->WriteObjectStart();
	
	/* д���ǳƵ�Json */
	JsonWriter->WriteValue("nickname", Nickname);

	/* д�����뵽Json */
	JsonWriter->WriteValue("password", Password);

	/* �ر�Jsonд�� */
	JsonWriter->WriteObjectEnd();

	/* �ر�Jsonд���� */
	JsonWriter->Close();

	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, RegisterInfo);

	/* ����HTTP���� */
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();

	/* ��������ʽ */
	HttpRequest->SetVerb("POST");

	/* ��������ͷ */
	HttpRequest->SetHeader("Content-Type", "application/json;charset=utf-8");

	/* ��������URL */
	HttpRequest->SetURL("http://localhost:3000/user/register");

	/* �����ϴ����� */
	HttpRequest->SetContentAsString(RegisterInfo);

	/* ��������ɹ���ί�з��� */
	HttpRequest->OnProcessRequestComplete().BindUObject(this, &URegisterUserWidget::RequestComplete);

	/* ��������� */
	HttpRequest->ProcessRequest();
}

/* ������Ӧ���� */
void URegisterUserWidget::RequestComplete(FHttpRequestPtr RequestPtr, FHttpResponsePtr ResponsePtr, bool bIsSuccess)
{
	
	/* ��ʾ����Ч������ */
	CircularThrobber->SetVisibility(ESlateVisibility::Hidden);

	/* ���ð�ť���� */
	RegBtn->SetIsEnabled(true);

	/* �ж���Ӧ״̬�Ƿ�����Ӧ�� */
	if (!EHttpResponseCodes::IsOk(ResponsePtr->GetResponseCode()))
	{
		return;
	}

	/* ��ȡ����ֵ */
	FString Data = ResponsePtr->GetContentAsString();

	/* ����һ��Json���� */
	TSharedPtr<FJsonObject> JsonObject;

	/* ����Json������ */
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(Data);

	/* Json�����л� */
	bool bIsParse = FJsonSerializer::Deserialize(JsonReader, JsonObject);

	/* �ж��Ƿ�����ɹ� */
	if(bIsParse)
	{
		FString Status =  JsonObject->GetStringField("status");
		FString Msg = JsonObject->GetStringField("msg");
		MessageTip("Register Success!");
	}
}

/* ��Ϣ��ʾ */
void URegisterUserWidget::MessageTip(FString msg)
{
	MessageWidget->SetVisibility(ESlateVisibility::Visible);
	MessageWidget->MsgBlock->SetText(FText::FromString(msg));
}

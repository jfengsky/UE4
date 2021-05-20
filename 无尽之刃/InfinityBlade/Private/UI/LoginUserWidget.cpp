// Fill out your copyright notice in the Description page of Project Settings.

#include "LoginUserWidget.h"

/** �ؼ�������ɵĳ�ʼ������ */
bool ULoginUserWidget::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	/** ��ʼ�����ذ�ť */
	BackBtn = Cast<UButton>(GetWidgetFromName(TEXT("Button_Back")));
	/** ��ʼ���ǳ������ */
	NicknameInput = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("EditableTextBox_Nickname")));
	/** ��ʼ����������� */
	PasswordInput = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("EditableTextBox_Password")));
	/** ��ʼ����¼��ť */
	LoginBtn = Cast<UButton>(GetWidgetFromName(TEXT("Button_Login")));
	/** ��¼��ť����¼� */
	LoginBtn->OnClicked.AddDynamic(this, &ULoginUserWidget::LoginBtnOnClickedEvent);

	/** ��ʼ���������ؼ� */
	CircularThrobber = Cast<UCircularThrobber>(GetWidgetFromName(TEXT("CircularThrobber_Loading")));
	/** ��ʼ����Ϣ��ʾ�� */
	MessageUserWidget = Cast<UMessageUserWidget>(GetWidgetFromName(TEXT("Message_Box")));

	return true;
}

/** ��¼��ť����¼� */
void ULoginUserWidget::LoginBtnOnClickedEvent()
{
	/** ��ȡ�û�������ǳ� */
	FString Nickname = NicknameInput->GetText().ToString();
	/** ��ȡ�û���������� */
	FString Password = PasswordInput->GetText().ToString();

	/** У���ǳ��Ƿ�Ϊ�� */
	if (Nickname.IsEmpty())
	{
		/** ��ʾ��Ϣ */
		MessageUserWidget->MsgBlock->SetText(FText::FromString("Nickname Is Empty"));
		MessageUserWidget->SetVisibility(ESlateVisibility::Visible);

		return;
	}

	/** У�������Ƿ�Ϊ�� */
	if (Password.IsEmpty())
	{
		/** ��ʾ��Ϣ */
		MessageUserWidget->MsgBlock->SetText(FText::FromString("Password Is Empty"));
		MessageUserWidget->SetVisibility(ESlateVisibility::Visible);

		return;
	}

	/** �û���¼ */
	AccountLoginFromServer(Nickname, Password);

	/** ���ؽ�������ʾ */
	CircularThrobber->SetVisibility(ESlateVisibility::Visible);
	/** ��¼��ť���ò����� */
	LoginBtn->SetIsEnabled(false);
}

/** �û���¼�ķ��� */
void ULoginUserWidget::AccountLoginFromServer(FString Nickname, FString Password)
{
	/** �ύ��Json */
	FString Data;
	/** ����Jsonд���� */
	TSharedRef<TJsonWriter<TCHAR,TCondensedJsonPrintPolicy<TCHAR>>> JsonWriter = TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>::Create(&Data);
	/** ��д�� */
	JsonWriter->WriteObjectStart();
	/** д���ǳ� */
	JsonWriter->WriteValue("nickname", Nickname);
	/** д������ */
	JsonWriter->WriteValue("password", Password);
	/** �ر�д�� */
	JsonWriter->WriteObjectEnd();
	/** �ر�Jsonд����*/
	JsonWriter->Close();

	/** ����HTTP���� */
	TSharedRef<IHttpRequest> Request = FHttpModule::Get().CreateRequest();
	/** ��������ͷ */
	Request->SetHeader("Content-Type", "application/json;charset=utf-8");
	/** ��������ʽ */
	Request->SetVerb("POST");
	/** ������������� */
	Request->SetContentAsString(Data);
	/** �����URL */
	Request->SetURL("http://118.31.2.218:7900/user/login-user");
	/** ��������ɹ��Ļص����� */
	Request->OnProcessRequestComplete().BindUObject(this, &ULoginUserWidget::RequestComplete);
	/** ��ʼ�������� */
	Request->ProcessRequest();
}

/** �������Ӧ���� */
void ULoginUserWidget::RequestComplete(FHttpRequestPtr RequestPtr, FHttpResponsePtr ResponsePtr, bool bIsSuccess)
{
	/** ���ؿ��������� */
	CircularThrobber->SetVisibility(ESlateVisibility::Hidden);
	/** ���õ�¼��ť����״̬ */
	LoginBtn->SetIsEnabled(true);

	/** �ж���Ӧ��״̬ */
	if (!EHttpResponseCodes::IsOk(ResponsePtr->GetResponseCode()))
	{
		return;
	}

	/** ����Json������ */
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(ResponsePtr->GetContentAsString());
	/** ����Json���� */
	TSharedPtr<FJsonObject> JsonObject;
	/** �����л�Json */
	bool bIsOk = FJsonSerializer::Deserialize(JsonReader, JsonObject);
	/** �ж��Ƿ����л��ɹ� */
	if (bIsOk)
	{
		/** ��ȡ�������ݵ�msg */
		FString Msg = JsonObject->GetStringField("msg");

		/** ��ȡ���ص����ݵ�data */
		TSharedPtr<FJsonObject> JsonData = JsonObject->GetObjectField("data");
		/** ��data�л�ȡ�û���id */
		FString Id = JsonData->GetStringField("id");
		/** ��data�л�ȡ�û���nickname */
		FString Nickname = JsonData->GetStringField("nickname");
		/** �ж�nickname�Ƿ�Ϊ�� */
		if (!Nickname.IsEmpty())
		{
			/** ��ȡ���Զ����GameInstance */
			UCustomGameInstance* GameInstace = Cast<UCustomGameInstance>(GetWorld()->GetGameInstance());
			/** ��id���浽GameInstance */
			GameInstace->ContextMap.Add("id", Id);
			/** �ؿ����л� */
			UGameplayStatics::OpenLevel(GetWorld(), TEXT("/Game/Map/Map_Main"));
		}
		else
		{
			/** ��ʾ��Ϣ */
			MessageUserWidget->MsgBlock->SetText(FText::FromString(Msg));
			MessageUserWidget->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

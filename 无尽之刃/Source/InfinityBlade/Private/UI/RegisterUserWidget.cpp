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


/* 组件初始化 */
bool URegisterUserWidget::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	/* 返回按钮 */
	BackBtn = Cast<UButton>(GetWidgetFromName(TEXT("Button_Back")));

	/* 昵称输入框 */
	NicknameInput = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("EditableTextBox_Nickname")));

	/* 密码输入框 */
	PasswordInput = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("EditableTextBox_Password")));

	/* 确认密码输入框 */
	RePasswordInput = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("EditableTextBox_RePassword")));

	/* 注册账号按钮 */
	RegBtn = Cast<UButton>(GetWidgetFromName(TEXT("Button_Reg")));

	/* 注册按钮点击事件 */
	RegBtn->OnClicked.AddDynamic(this, &URegisterUserWidget::RegBtnOnClickedEvent);

	/* Loading */
	CircularThrobber = Cast<UCircularThrobber>(GetWidgetFromName(TEXT("CircularThrobber_Loading")));

	/* 初始化信息提示框 */
	MessageWidget = Cast<UMessageUserWidget>(GetWidgetFromName(TEXT("BP_MessageUserWidget")));

	return true;
}

/* 注册账号按钮点击事件 */
void URegisterUserWidget::RegBtnOnClickedEvent()
{

	/* 获取昵称 */
	FString Nickname = NicknameInput->GetText().ToString();

	/* 获取密码 */
	FString Password = PasswordInput->GetText().ToString();

	/* 获取确认密码 */
	FString RePassword = RePasswordInput->GetText().ToString();

	/* 昵称长度必须大于1 */
	if (Nickname.Len() < 2) {
		MessageTip("Nickname need 2-6 characters!");
		return;
	}

	if (Password.IsEmpty() || RePassword.IsEmpty()) {
		MessageTip("please input password!");
		return;
	}

	/* 判断两次密码是否一至 */
	if (!Password.Equals(RePassword))
	{
		MessageTip("twice password not same!");
		return;
	}

	/* 显示加载效果 */
	CircularThrobber->SetVisibility(ESlateVisibility::Visible);

	/* 设置按钮不可用 */
	RegBtn->SetIsEnabled(false);

	/* 进行账号注册 */
	AccountRegesterFromServer(Nickname, Password);
}

/*注册账号方法*/
void URegisterUserWidget::AccountRegesterFromServer(FString& Nickname, FString& Password)
{
	/* 创建要提交的Json字符串 */
	FString RegisterInfo;

	/* 创建共享Json写入器 */
	TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> JsonWriter = TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>::Create(&RegisterInfo);
	
	/* 开始写入数据 */
	JsonWriter->WriteObjectStart();
	
	/* 写入昵称到Json */
	JsonWriter->WriteValue("nickname", Nickname);

	/* 写入密码到Json */
	JsonWriter->WriteValue("password", Password);

	/* 关闭Json写入 */
	JsonWriter->WriteObjectEnd();

	/* 关闭Json写入器 */
	JsonWriter->Close();

	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, RegisterInfo);

	/* 创建HTTP请求 */
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();

	/* 设置请求方式 */
	HttpRequest->SetVerb("POST");

	/* 设置请求头 */
	HttpRequest->SetHeader("Content-Type", "application/json;charset=utf-8");

	/* 设置请求URL */
	HttpRequest->SetURL("http://localhost:3000/user/register");

	/* 设置上传数据 */
	HttpRequest->SetContentAsString(RegisterInfo);

	/* 设置请求成功后委托方法 */
	HttpRequest->OnProcessRequestComplete().BindUObject(this, &URegisterUserWidget::RequestComplete);

	/* 请求服务器 */
	HttpRequest->ProcessRequest();
}

/* 请求响应方法 */
void URegisterUserWidget::RequestComplete(FHttpRequestPtr RequestPtr, FHttpResponsePtr ResponsePtr, bool bIsSuccess)
{
	
	/* 显示加载效果隐藏 */
	CircularThrobber->SetVisibility(ESlateVisibility::Hidden);

	/* 设置按钮可用 */
	RegBtn->SetIsEnabled(true);

	/* 判断响应状态是否正常应码 */
	if (!EHttpResponseCodes::IsOk(ResponsePtr->GetResponseCode()))
	{
		return;
	}

	/* 获取返回值 */
	FString Data = ResponsePtr->GetContentAsString();

	/* 创建一个Json对象 */
	TSharedPtr<FJsonObject> JsonObject;

	/* 创建Json解析器 */
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(Data);

	/* Json反序列化 */
	bool bIsParse = FJsonSerializer::Deserialize(JsonReader, JsonObject);

	/* 判断是否解析成功 */
	if(bIsParse)
	{
		FString Status =  JsonObject->GetStringField("status");
		FString Msg = JsonObject->GetStringField("msg");
		MessageTip("Register Success!");
	}
}

/* 信息提示 */
void URegisterUserWidget::MessageTip(FString msg)
{
	MessageWidget->SetVisibility(ESlateVisibility::Visible);
	MessageWidget->MsgBlock->SetText(FText::FromString(msg));
}

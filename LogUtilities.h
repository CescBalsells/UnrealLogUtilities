#pragma once

#include "CoreMinimal.h"

#define LOGS 1

#if LOGS
#define LOGERROR(text, ...)						UE_LOG(LogTemp, Error, TEXT(text), ##__VA_ARGS__);
#define LOGWARN(text, ...)						UE_LOG(LogTemp, Warning, TEXT(text), ##__VA_ARGS__);
#define LOG(text, ...)							UE_LOG(LogTemp, Log, TEXT(text), ##__VA_ARGS__);

#define LOGERROR_SCREEN(time, text, ...)		{\
												LOGERROR(text, ##__VA_ARGS__)\
												if(GEngine)\
												GEngine->AddOnScreenDebugMessage(-1, time, FColor::Red, FString::Printf(TEXT(text), ##__VA_ARGS__));\
												}
#define LOGWARN_SCREEN(time, text, ...)			{\
												LOGWARN(text, ##__VA_ARGS__)\
												if(GEngine)\
												GEngine->AddOnScreenDebugMessage(-1, time, FColor::Yellow, FString::Printf(TEXT(text), ##__VA_ARGS__));\
												}
#define LOG_SCREEN(time, text, ...)				{\
												LOG(text, ##__VA_ARGS__)\
												if(GEngine)\
												GEngine->AddOnScreenDebugMessage(-1, time, FColor::White, FString::Printf(TEXT(text), ##__VA_ARGS__));\
												}

#define LOGERROR_MESSAGE(line, file, text, ...)		{\
													FMessageLog("PIE").Error(FText::FromString(file + " (" + FString::FromInt(line) + ") " + text));\
													}
#define LOGWARN_MESSAGE(line, file, text, ...)		{\
													FMessageLog("PIE").Warning(FText::FromString(file + " (" + FString::FromInt(line) + ") " + text));\
													}
#define LOG_MESSAGE(line, file, text, ...)			{\
													FMessageLog("PIE").Info(FText::FromString(file + " (" + FString::FromInt(line) + ") " + text));\
													}
#else
#define LOGERROR(text, ...) {}
#define LOGWARN(text, ...) {}
#define LOG(text, ...) {}
#define LOGERROR_SCREEN(time, text, ...) {}
#define LOGWARN_SCREEN(time, text, ...)	{}
#define LOG_SCREEN(time, text, ...) {}
#define LOGERROR_MESSAGE(line, file, text, ...) {}
#define LOGWARN_MESSAGE(line, file, text, ...) {}
#define LOG_MESSAGE(line, file, text, ...) {}
#define LOGERROR(text, ...) {}
#endif

#if UE_EDITOR
#define CHECK_NULL(Object) IsNull(Object, __LINE__, __FILE__)
#else
#define CHECK_NULL(Object) IsNull(Object, 0, FString(""))
#endif

static bool IsNull(const void* const& Object, int line /*= __LINE__*/, FString file /*=  __FILE__*/)
{
	if (Object == nullptr)
	{
		LOG_SCREEN(5.0f, "Object is NULL");
#if WITH_EDITORONLY_DATA
		LOGERROR_MESSAGE(line, file, "is NULL");
#endif
		return false;
	}

	return true;
}

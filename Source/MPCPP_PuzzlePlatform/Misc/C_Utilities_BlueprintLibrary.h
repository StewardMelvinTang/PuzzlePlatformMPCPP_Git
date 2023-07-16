// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "C_Utilities_BlueprintLibrary.generated.h"

/**
 * 
 */
UCLASS()
class MPCPP_PUZZLEPLATFORM_API UC_Utilities_BlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Utilities")
	static void ShowEditorToast(FString messageString);
	
};

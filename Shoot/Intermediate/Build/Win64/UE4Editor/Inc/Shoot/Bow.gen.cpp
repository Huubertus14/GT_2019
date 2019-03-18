// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Shoot/Bow.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeBow() {}
// Cross Module References
	SHOOT_API UClass* Z_Construct_UClass_ABow_NoRegister();
	SHOOT_API UClass* Z_Construct_UClass_ABow();
	ENGINE_API UClass* Z_Construct_UClass_ACharacter();
	UPackage* Z_Construct_UPackage__Script_Shoot();
	SHOOT_API UFunction* Z_Construct_UFunction_ABow_MoveForward();
	SHOOT_API UFunction* Z_Construct_UFunction_ABow_MoveRight();
	ENGINE_API UClass* Z_Construct_UClass_USceneComponent_NoRegister();
// End Cross Module References
	void ABow::StaticRegisterNativesABow()
	{
		UClass* Class = ABow::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "MoveForward", &ABow::execMoveForward },
			{ "MoveRight", &ABow::execMoveRight },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_ABow_MoveForward_Statics
	{
		struct Bow_eventMoveForward_Parms
		{
			float Val;
		};
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_Val;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_ABow_MoveForward_Statics::NewProp_Val = { UE4CodeGen_Private::EPropertyClass::Float, "Val", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000080, 1, nullptr, STRUCT_OFFSET(Bow_eventMoveForward_Parms, Val), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ABow_MoveForward_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ABow_MoveForward_Statics::NewProp_Val,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ABow_MoveForward_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Bow.h" },
		{ "ToolTip", "handles moving forward/backward" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ABow_MoveForward_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ABow, "MoveForward", RF_Public|RF_Transient|RF_MarkAsNative, nullptr, (EFunctionFlags)0x00020401, sizeof(Bow_eventMoveForward_Parms), Z_Construct_UFunction_ABow_MoveForward_Statics::PropPointers, ARRAY_COUNT(Z_Construct_UFunction_ABow_MoveForward_Statics::PropPointers), 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ABow_MoveForward_Statics::Function_MetaDataParams, ARRAY_COUNT(Z_Construct_UFunction_ABow_MoveForward_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ABow_MoveForward()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ABow_MoveForward_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ABow_MoveRight_Statics
	{
		struct Bow_eventMoveRight_Parms
		{
			float Val;
		};
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_Val;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_ABow_MoveRight_Statics::NewProp_Val = { UE4CodeGen_Private::EPropertyClass::Float, "Val", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000080, 1, nullptr, STRUCT_OFFSET(Bow_eventMoveRight_Parms, Val), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ABow_MoveRight_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ABow_MoveRight_Statics::NewProp_Val,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ABow_MoveRight_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Bow.h" },
		{ "ToolTip", "handles strafing" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ABow_MoveRight_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ABow, "MoveRight", RF_Public|RF_Transient|RF_MarkAsNative, nullptr, (EFunctionFlags)0x00020401, sizeof(Bow_eventMoveRight_Parms), Z_Construct_UFunction_ABow_MoveRight_Statics::PropPointers, ARRAY_COUNT(Z_Construct_UFunction_ABow_MoveRight_Statics::PropPointers), 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ABow_MoveRight_Statics::Function_MetaDataParams, ARRAY_COUNT(Z_Construct_UFunction_ABow_MoveRight_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ABow_MoveRight()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ABow_MoveRight_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_ABow_NoRegister()
	{
		return ABow::StaticClass();
	}
	struct Z_Construct_UClass_ABow_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_OurVisibleComponent_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_OurVisibleComponent;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ABow_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_ACharacter,
		(UObject* (*)())Z_Construct_UPackage__Script_Shoot,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_ABow_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_ABow_MoveForward, "MoveForward" }, // 1182340390
		{ &Z_Construct_UFunction_ABow_MoveRight, "MoveRight" }, // 3769026776
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ABow_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "Bow.h" },
		{ "ModuleRelativePath", "Bow.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ABow_Statics::NewProp_OurVisibleComponent_MetaData[] = {
		{ "Category", "Bow" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Bow.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ABow_Statics::NewProp_OurVisibleComponent = { UE4CodeGen_Private::EPropertyClass::Object, "OurVisibleComponent", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000080009, 1, nullptr, STRUCT_OFFSET(ABow, OurVisibleComponent), Z_Construct_UClass_USceneComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ABow_Statics::NewProp_OurVisibleComponent_MetaData, ARRAY_COUNT(Z_Construct_UClass_ABow_Statics::NewProp_OurVisibleComponent_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ABow_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABow_Statics::NewProp_OurVisibleComponent,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ABow_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ABow>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ABow_Statics::ClassParams = {
		&ABow::StaticClass,
		DependentSingletons, ARRAY_COUNT(DependentSingletons),
		0x009000A0u,
		FuncInfo, ARRAY_COUNT(FuncInfo),
		Z_Construct_UClass_ABow_Statics::PropPointers, ARRAY_COUNT(Z_Construct_UClass_ABow_Statics::PropPointers),
		nullptr,
		&StaticCppClassTypeInfo,
		nullptr, 0,
		METADATA_PARAMS(Z_Construct_UClass_ABow_Statics::Class_MetaDataParams, ARRAY_COUNT(Z_Construct_UClass_ABow_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ABow()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ABow_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ABow, 2660671288);
	static FCompiledInDefer Z_CompiledInDefer_UClass_ABow(Z_Construct_UClass_ABow, &ABow::StaticClass, TEXT("/Script/Shoot"), TEXT("ABow"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ABow);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif

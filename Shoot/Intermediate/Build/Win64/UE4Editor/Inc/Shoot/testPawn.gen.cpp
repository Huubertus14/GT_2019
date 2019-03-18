// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Shoot/testPawn.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodetestPawn() {}
// Cross Module References
	SHOOT_API UClass* Z_Construct_UClass_AtestPawn_NoRegister();
	SHOOT_API UClass* Z_Construct_UClass_AtestPawn();
	ENGINE_API UClass* Z_Construct_UClass_APawn();
	UPackage* Z_Construct_UPackage__Script_Shoot();
	ENGINE_API UClass* Z_Construct_UClass_USceneComponent_NoRegister();
// End Cross Module References
	void AtestPawn::StaticRegisterNativesAtestPawn()
	{
	}
	UClass* Z_Construct_UClass_AtestPawn_NoRegister()
	{
		return AtestPawn::StaticClass();
	}
	struct Z_Construct_UClass_AtestPawn_Statics
	{
		static UObject* (*const DependentSingletons[])();
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
	UObject* (*const Z_Construct_UClass_AtestPawn_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_APawn,
		(UObject* (*)())Z_Construct_UPackage__Script_Shoot,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AtestPawn_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "testPawn.h" },
		{ "ModuleRelativePath", "testPawn.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AtestPawn_Statics::NewProp_OurVisibleComponent_MetaData[] = {
		{ "Category", "testPawn" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "testPawn.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AtestPawn_Statics::NewProp_OurVisibleComponent = { UE4CodeGen_Private::EPropertyClass::Object, "OurVisibleComponent", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000080009, 1, nullptr, STRUCT_OFFSET(AtestPawn, OurVisibleComponent), Z_Construct_UClass_USceneComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AtestPawn_Statics::NewProp_OurVisibleComponent_MetaData, ARRAY_COUNT(Z_Construct_UClass_AtestPawn_Statics::NewProp_OurVisibleComponent_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AtestPawn_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AtestPawn_Statics::NewProp_OurVisibleComponent,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AtestPawn_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AtestPawn>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AtestPawn_Statics::ClassParams = {
		&AtestPawn::StaticClass,
		DependentSingletons, ARRAY_COUNT(DependentSingletons),
		0x009000A0u,
		nullptr, 0,
		Z_Construct_UClass_AtestPawn_Statics::PropPointers, ARRAY_COUNT(Z_Construct_UClass_AtestPawn_Statics::PropPointers),
		nullptr,
		&StaticCppClassTypeInfo,
		nullptr, 0,
		METADATA_PARAMS(Z_Construct_UClass_AtestPawn_Statics::Class_MetaDataParams, ARRAY_COUNT(Z_Construct_UClass_AtestPawn_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AtestPawn()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AtestPawn_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AtestPawn, 924934939);
	static FCompiledInDefer Z_CompiledInDefer_UClass_AtestPawn(Z_Construct_UClass_AtestPawn, &AtestPawn::StaticClass, TEXT("/Script/Shoot"), TEXT("AtestPawn"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AtestPawn);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif

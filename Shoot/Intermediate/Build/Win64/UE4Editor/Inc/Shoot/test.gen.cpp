// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Shoot/test.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodetest() {}
// Cross Module References
	SHOOT_API UClass* Z_Construct_UClass_Atest_NoRegister();
	SHOOT_API UClass* Z_Construct_UClass_Atest();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	UPackage* Z_Construct_UPackage__Script_Shoot();
	COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
	SHOOT_API UClass* Z_Construct_UClass_AArrow_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent_NoRegister();
// End Cross Module References
	void Atest::StaticRegisterNativesAtest()
	{
	}
	UClass* Z_Construct_UClass_Atest_NoRegister()
	{
		return Atest::StaticClass();
	}
	struct Z_Construct_UClass_Atest_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_arrow_MetaData[];
#endif
		static const UE4CodeGen_Private::FClassPropertyParams NewProp_arrow;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_mesh_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_mesh;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_Atest_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_Shoot,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_Atest_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "test.h" },
		{ "ModuleRelativePath", "test.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_Atest_Statics::NewProp_arrow_MetaData[] = {
		{ "Category", "test" },
		{ "ModuleRelativePath", "test.h" },
	};
#endif
	const UE4CodeGen_Private::FClassPropertyParams Z_Construct_UClass_Atest_Statics::NewProp_arrow = { UE4CodeGen_Private::EPropertyClass::Class, "arrow", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0014000000000001, 1, nullptr, STRUCT_OFFSET(Atest, arrow), Z_Construct_UClass_AArrow_NoRegister, Z_Construct_UClass_UClass, METADATA_PARAMS(Z_Construct_UClass_Atest_Statics::NewProp_arrow_MetaData, ARRAY_COUNT(Z_Construct_UClass_Atest_Statics::NewProp_arrow_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_Atest_Statics::NewProp_mesh_MetaData[] = {
		{ "Category", "test" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "test.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_Atest_Statics::NewProp_mesh = { UE4CodeGen_Private::EPropertyClass::Object, "mesh", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000080009, 1, nullptr, STRUCT_OFFSET(Atest, mesh), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_Atest_Statics::NewProp_mesh_MetaData, ARRAY_COUNT(Z_Construct_UClass_Atest_Statics::NewProp_mesh_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_Atest_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_Atest_Statics::NewProp_arrow,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_Atest_Statics::NewProp_mesh,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_Atest_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<Atest>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_Atest_Statics::ClassParams = {
		&Atest::StaticClass,
		DependentSingletons, ARRAY_COUNT(DependentSingletons),
		0x009000A0u,
		nullptr, 0,
		Z_Construct_UClass_Atest_Statics::PropPointers, ARRAY_COUNT(Z_Construct_UClass_Atest_Statics::PropPointers),
		nullptr,
		&StaticCppClassTypeInfo,
		nullptr, 0,
		METADATA_PARAMS(Z_Construct_UClass_Atest_Statics::Class_MetaDataParams, ARRAY_COUNT(Z_Construct_UClass_Atest_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_Atest()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_Atest_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(Atest, 121773012);
	static FCompiledInDefer Z_CompiledInDefer_UClass_Atest(Z_Construct_UClass_Atest, &Atest::StaticClass, TEXT("/Script/Shoot"), TEXT("Atest"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(Atest);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif

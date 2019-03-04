// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "ObjectMacros.h"
#include "ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UPrimitiveComponent;
class AActor;
struct FVector;
struct FHitResult;
#ifdef DEMOPROJECT_DemoProjectProjectile_generated_h
#error "DemoProjectProjectile.generated.h already included, missing '#pragma once' in DemoProjectProjectile.h"
#endif
#define DEMOPROJECT_DemoProjectProjectile_generated_h

#define DemoProject_Source_DemoProject_DemoProjectProjectile_h_12_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execOnHit) \
	{ \
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_HitComp); \
		P_GET_OBJECT(AActor,Z_Param_OtherActor); \
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_OtherComp); \
		P_GET_STRUCT(FVector,Z_Param_NormalImpulse); \
		P_GET_STRUCT_REF(FHitResult,Z_Param_Out_Hit); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->OnHit(Z_Param_HitComp,Z_Param_OtherActor,Z_Param_OtherComp,Z_Param_NormalImpulse,Z_Param_Out_Hit); \
		P_NATIVE_END; \
	}


#define DemoProject_Source_DemoProject_DemoProjectProjectile_h_12_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execOnHit) \
	{ \
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_HitComp); \
		P_GET_OBJECT(AActor,Z_Param_OtherActor); \
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_OtherComp); \
		P_GET_STRUCT(FVector,Z_Param_NormalImpulse); \
		P_GET_STRUCT_REF(FHitResult,Z_Param_Out_Hit); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->OnHit(Z_Param_HitComp,Z_Param_OtherActor,Z_Param_OtherComp,Z_Param_NormalImpulse,Z_Param_Out_Hit); \
		P_NATIVE_END; \
	}


#define DemoProject_Source_DemoProject_DemoProjectProjectile_h_12_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesADemoProjectProjectile(); \
	friend DEMOPROJECT_API class UClass* Z_Construct_UClass_ADemoProjectProjectile(); \
public: \
	DECLARE_CLASS(ADemoProjectProjectile, AActor, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/DemoProject"), NO_API) \
	DECLARE_SERIALIZER(ADemoProjectProjectile) \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC}; \
	static const TCHAR* StaticConfigName() {return TEXT("Game");} \



#define DemoProject_Source_DemoProject_DemoProjectProjectile_h_12_INCLASS \
private: \
	static void StaticRegisterNativesADemoProjectProjectile(); \
	friend DEMOPROJECT_API class UClass* Z_Construct_UClass_ADemoProjectProjectile(); \
public: \
	DECLARE_CLASS(ADemoProjectProjectile, AActor, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/DemoProject"), NO_API) \
	DECLARE_SERIALIZER(ADemoProjectProjectile) \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC}; \
	static const TCHAR* StaticConfigName() {return TEXT("Game");} \



#define DemoProject_Source_DemoProject_DemoProjectProjectile_h_12_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ADemoProjectProjectile(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ADemoProjectProjectile) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ADemoProjectProjectile); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ADemoProjectProjectile); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ADemoProjectProjectile(ADemoProjectProjectile&&); \
	NO_API ADemoProjectProjectile(const ADemoProjectProjectile&); \
public:


#define DemoProject_Source_DemoProject_DemoProjectProjectile_h_12_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ADemoProjectProjectile(ADemoProjectProjectile&&); \
	NO_API ADemoProjectProjectile(const ADemoProjectProjectile&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ADemoProjectProjectile); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ADemoProjectProjectile); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ADemoProjectProjectile)


#define DemoProject_Source_DemoProject_DemoProjectProjectile_h_12_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__CollisionComp() { return STRUCT_OFFSET(ADemoProjectProjectile, CollisionComp); } \
	FORCEINLINE static uint32 __PPO__ProjectileMovement() { return STRUCT_OFFSET(ADemoProjectProjectile, ProjectileMovement); }


#define DemoProject_Source_DemoProject_DemoProjectProjectile_h_9_PROLOG
#define DemoProject_Source_DemoProject_DemoProjectProjectile_h_12_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	DemoProject_Source_DemoProject_DemoProjectProjectile_h_12_PRIVATE_PROPERTY_OFFSET \
	DemoProject_Source_DemoProject_DemoProjectProjectile_h_12_RPC_WRAPPERS \
	DemoProject_Source_DemoProject_DemoProjectProjectile_h_12_INCLASS \
	DemoProject_Source_DemoProject_DemoProjectProjectile_h_12_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define DemoProject_Source_DemoProject_DemoProjectProjectile_h_12_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	DemoProject_Source_DemoProject_DemoProjectProjectile_h_12_PRIVATE_PROPERTY_OFFSET \
	DemoProject_Source_DemoProject_DemoProjectProjectile_h_12_RPC_WRAPPERS_NO_PURE_DECLS \
	DemoProject_Source_DemoProject_DemoProjectProjectile_h_12_INCLASS_NO_PURE_DECLS \
	DemoProject_Source_DemoProject_DemoProjectProjectile_h_12_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID DemoProject_Source_DemoProject_DemoProjectProjectile_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS

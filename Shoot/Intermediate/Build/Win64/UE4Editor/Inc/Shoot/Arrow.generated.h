// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UPrimitiveComponent;
class AActor;
struct FVector;
struct FHitResult;
#ifdef SHOOT_Arrow_generated_h
#error "Arrow.generated.h already included, missing '#pragma once' in Arrow.h"
#endif
#define SHOOT_Arrow_generated_h

#define Shoot_Source_Shoot_Arrow_h_12_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execOnCompHit) \
	{ \
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_HitComp); \
		P_GET_OBJECT(AActor,Z_Param_OtherActor); \
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_OtherComp); \
		P_GET_STRUCT(FVector,Z_Param_NormalImpulse); \
		P_GET_STRUCT_REF(FHitResult,Z_Param_Out_hit); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->OnCompHit(Z_Param_HitComp,Z_Param_OtherActor,Z_Param_OtherComp,Z_Param_NormalImpulse,Z_Param_Out_hit); \
		P_NATIVE_END; \
	}


#define Shoot_Source_Shoot_Arrow_h_12_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execOnCompHit) \
	{ \
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_HitComp); \
		P_GET_OBJECT(AActor,Z_Param_OtherActor); \
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_OtherComp); \
		P_GET_STRUCT(FVector,Z_Param_NormalImpulse); \
		P_GET_STRUCT_REF(FHitResult,Z_Param_Out_hit); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->OnCompHit(Z_Param_HitComp,Z_Param_OtherActor,Z_Param_OtherComp,Z_Param_NormalImpulse,Z_Param_Out_hit); \
		P_NATIVE_END; \
	}


#define Shoot_Source_Shoot_Arrow_h_12_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAArrow(); \
	friend struct Z_Construct_UClass_AArrow_Statics; \
public: \
	DECLARE_CLASS(AArrow, AActor, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/Shoot"), NO_API) \
	DECLARE_SERIALIZER(AArrow)


#define Shoot_Source_Shoot_Arrow_h_12_INCLASS \
private: \
	static void StaticRegisterNativesAArrow(); \
	friend struct Z_Construct_UClass_AArrow_Statics; \
public: \
	DECLARE_CLASS(AArrow, AActor, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/Shoot"), NO_API) \
	DECLARE_SERIALIZER(AArrow)


#define Shoot_Source_Shoot_Arrow_h_12_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AArrow(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AArrow) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AArrow); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AArrow); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AArrow(AArrow&&); \
	NO_API AArrow(const AArrow&); \
public:


#define Shoot_Source_Shoot_Arrow_h_12_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AArrow(AArrow&&); \
	NO_API AArrow(const AArrow&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AArrow); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AArrow); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AArrow)


#define Shoot_Source_Shoot_Arrow_h_12_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__arrowMesh() { return STRUCT_OFFSET(AArrow, arrowMesh); }


#define Shoot_Source_Shoot_Arrow_h_9_PROLOG
#define Shoot_Source_Shoot_Arrow_h_12_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Shoot_Source_Shoot_Arrow_h_12_PRIVATE_PROPERTY_OFFSET \
	Shoot_Source_Shoot_Arrow_h_12_RPC_WRAPPERS \
	Shoot_Source_Shoot_Arrow_h_12_INCLASS \
	Shoot_Source_Shoot_Arrow_h_12_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define Shoot_Source_Shoot_Arrow_h_12_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Shoot_Source_Shoot_Arrow_h_12_PRIVATE_PROPERTY_OFFSET \
	Shoot_Source_Shoot_Arrow_h_12_RPC_WRAPPERS_NO_PURE_DECLS \
	Shoot_Source_Shoot_Arrow_h_12_INCLASS_NO_PURE_DECLS \
	Shoot_Source_Shoot_Arrow_h_12_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID Shoot_Source_Shoot_Arrow_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS

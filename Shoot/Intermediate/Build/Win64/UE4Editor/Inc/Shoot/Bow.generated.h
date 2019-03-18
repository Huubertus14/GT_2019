// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef SHOOT_Bow_generated_h
#error "Bow.generated.h already included, missing '#pragma once' in Bow.h"
#endif
#define SHOOT_Bow_generated_h

#define Shoot_Source_Shoot_Bow_h_12_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execMoveRight) \
	{ \
		P_GET_PROPERTY(UFloatProperty,Z_Param_Val); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->MoveRight(Z_Param_Val); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execMoveForward) \
	{ \
		P_GET_PROPERTY(UFloatProperty,Z_Param_Val); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->MoveForward(Z_Param_Val); \
		P_NATIVE_END; \
	}


#define Shoot_Source_Shoot_Bow_h_12_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execMoveRight) \
	{ \
		P_GET_PROPERTY(UFloatProperty,Z_Param_Val); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->MoveRight(Z_Param_Val); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execMoveForward) \
	{ \
		P_GET_PROPERTY(UFloatProperty,Z_Param_Val); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->MoveForward(Z_Param_Val); \
		P_NATIVE_END; \
	}


#define Shoot_Source_Shoot_Bow_h_12_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesABow(); \
	friend struct Z_Construct_UClass_ABow_Statics; \
public: \
	DECLARE_CLASS(ABow, ACharacter, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/Shoot"), NO_API) \
	DECLARE_SERIALIZER(ABow)


#define Shoot_Source_Shoot_Bow_h_12_INCLASS \
private: \
	static void StaticRegisterNativesABow(); \
	friend struct Z_Construct_UClass_ABow_Statics; \
public: \
	DECLARE_CLASS(ABow, ACharacter, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/Shoot"), NO_API) \
	DECLARE_SERIALIZER(ABow)


#define Shoot_Source_Shoot_Bow_h_12_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ABow(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ABow) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ABow); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ABow); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ABow(ABow&&); \
	NO_API ABow(const ABow&); \
public:


#define Shoot_Source_Shoot_Bow_h_12_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ABow(ABow&&); \
	NO_API ABow(const ABow&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ABow); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ABow); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ABow)


#define Shoot_Source_Shoot_Bow_h_12_PRIVATE_PROPERTY_OFFSET
#define Shoot_Source_Shoot_Bow_h_9_PROLOG
#define Shoot_Source_Shoot_Bow_h_12_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Shoot_Source_Shoot_Bow_h_12_PRIVATE_PROPERTY_OFFSET \
	Shoot_Source_Shoot_Bow_h_12_RPC_WRAPPERS \
	Shoot_Source_Shoot_Bow_h_12_INCLASS \
	Shoot_Source_Shoot_Bow_h_12_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define Shoot_Source_Shoot_Bow_h_12_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Shoot_Source_Shoot_Bow_h_12_PRIVATE_PROPERTY_OFFSET \
	Shoot_Source_Shoot_Bow_h_12_RPC_WRAPPERS_NO_PURE_DECLS \
	Shoot_Source_Shoot_Bow_h_12_INCLASS_NO_PURE_DECLS \
	Shoot_Source_Shoot_Bow_h_12_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID Shoot_Source_Shoot_Bow_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS

#pragma once

// Will return from calling function and print warning if the given value is false
// Use this if the state would be invalid without this validation
#define AssertNotNullReturn(ptr)                                                    \
	{                                                                               \
		if (!ensure(ptr))                                                           \
		{                                                                           \
			UE_LOG(LogTemp, Error, TEXT("Null check failed in %s"), __FUNCDNAME__); \
			return;                                                                 \
		}                                                                           \
	}

// Will continue from calling scope and print warning if the given value is false
// Use this if the state would be invalid without this validation
#define AssertNotNullContinue(ptr)                                                  \
	{                                                                               \
		if (!ensure(ptr))                                                           \
		{                                                                           \
			UE_LOG(LogTemp, Error, TEXT("Null check failed in %s"), __FUNCDNAME__); \
			continue;                                                               \
		}                                                                           \
	}

// Will return from calling function and print warning if the given value is false
// Use this if the state would be invalid without this validation
// returnVal: The value to return with if the ptr is nullptr
#define AssertNotNullReturnVal(ptr, returnVal)                                      \
	{                                                                               \
		if (!ensure(ptr))                                                           \
		{                                                                           \
			UE_LOG(LogTemp, Error, TEXT("Null check failed in %s"), __FUNCDNAME__); \
			return returnVal;                                                       \
		}                                                                           \
	}

// Will return from calling function if the given value is false
// Use this if the state would be lagal with null
#define CheckNotNullReturn(ptr) \
	{                           \
		if (!ptr)               \
		{                       \
			return;             \
		}                       \
	}

// Will return with value from calling function if the given value is false
// Use this if the state would be lagal with null
// returnVal: The value to return with if the ptr is nullptr
#define CheckNotNullReturnVal(ptr, returnVal) \
	{                                         \
		if (!ensure(ptr))                     \
		{                                     \
			return returnVal;                 \
		}                                     \
	}

// Uses macros from AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName)           \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName)               \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName)               \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
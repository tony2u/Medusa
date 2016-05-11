// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
//[IGNORE_PRE_DECLARE_FILE]

MEDUSA_BEGIN;
namespace Compile
{
	const char* FixedClassName(const char* name);

	template <typename T, typename Enable = void>
	struct IsCustomEnum
	{
		const static bool Value = false;
	};

	template <typename T>
	struct IsCustomEnum < T, typename std::enable_if<T::IsEnum>::type >
	{
		const static bool Value = true;
	};



	template <typename T>
	class TypeTraits
	{
	public:
		//Primary type
		const static bool IsVoid = std::is_void<T>::value;
		//const static bool IsNullPointer = std::is_null_pointer<T>::value;	//checks if a type is std::nullptr_t c++14
        
		const static bool IsIntegral = std::is_integral<T>::value;
		const static bool IsFloatingPoint = std::is_floating_point<T>::value;
		const static bool IsArray = std::is_array<T>::value;
		const static bool IsEnum = std::is_enum<T>::value;
		const static bool IsUnion = std::is_union<T>::value;
		const static bool IsClass = std::is_class<T>::value;
		const static bool IsFunction = std::is_function<T>::value;
		const static bool IsPointer = std::is_pointer<T>::value;
		const static bool IsLeftReference = std::is_lvalue_reference<T>::value;
		const static bool IsRightReference = std::is_rvalue_reference<T>::value;
		const static bool IsMemberObjectPointer = std::is_member_object_pointer<T>::value;
		const static bool IsMemberFunctionPointer = std::is_member_function_pointer<T>::value;

		//Composite type
		const static bool IsFundamental = std::is_fundamental<T>::value;
		const static bool IsArithmetic = std::is_arithmetic<T>::value;
		const static bool IsScalar = std::is_scalar<T>::value;
		const static bool IsObject = std::is_object<T>::value;
		const static bool IsCompound = std::is_compound<T>::value;
		const static bool IsReference = std::is_reference<T>::value;
		const static bool IsMemberPointer = std::is_member_pointer<T>::value;

		//Type properties
		const static bool IsConst = std::is_const<T>::value;
		const static bool IsVolatile = std::is_volatile<T>::value;
		const static bool IsTrivial = std::is_trivial<T>::value;
		//const static bool IsTriviallyCopyable = std::is_trivially_copyable<T>::value;
		const static bool IsStandardLayout = std::is_standard_layout<T>::value;
		const static bool IsPOD = std::is_pod<T>::value;
		const static bool IsLiteral = std::is_literal_type<T>::value;
		const static bool IsEmpty = std::is_empty<T>::value;
		const static bool IsPolymorphic = std::is_polymorphic<T>::value;
		const static bool IsAbstract = std::is_abstract<T>::value;
		const static bool IsSigned = std::is_signed<T>::value;
		const static bool IsUnsigned = std::is_unsigned<T>::value;
		const static bool IsSignedInt = IsSigned && (!IsFloatingPoint) && (!IsEnum);
		const static bool IsSignedIntOrEnum = (IsSigned && (!IsFloatingPoint)) || IsEnum;


		//Property queries
		const static size_t Alignment = std::alignment_of<T>::value;	//obtains the type's alignment requirements 
		const static size_t Rank = std::rank<T>::value;	//obtains the number of dimensions of an array type 




		typedef typename std::add_const<T>::type ConstType;
		typedef typename std::add_volatile<T>::type VolatileType;
		typedef typename std::add_cv<T>::type ConstVolatileType;

		typedef typename std::remove_const<T>::type NonConstType;
		typedef typename std::remove_volatile<T>::type NonVolatileType;
		typedef typename std::remove_cv<T>::type NonConstVolatileType;

		typedef typename std::add_lvalue_reference<T>::type ReferenceType;
		typedef typename std::add_rvalue_reference<T>::type RightReferenceType;
		typedef typename std::remove_reference<T>::type ReferredType;

		typedef typename std::add_pointer<T>::type PointerType;
		typedef typename std::remove_pointer<T>::type PointeeType;



		typedef typename std::remove_pointer<ReferredType>::type DirectType;
		typedef typename std::remove_cv<DirectType>::type UnderlyingType;


		typedef typename std::add_pointer<ConstType>::type ConstPointerType;
		typedef typename std::add_lvalue_reference<ConstType>::type ConstReferenceType;

		//typedef typename std::add_const<PointerType>::type ConstPointerType;
		//typedef typename std::add_const<ReferenceType>::type ConstReferenceType;

		typedef typename std::add_volatile<PointerType>::type VolatilePointerType;
		typedef typename std::add_volatile<ReferenceType>::type VolatileReferenceType;


		typedef typename std::conditional<IsArithmetic || IsPointer || IsMemberPointer || IsEnum, T, ConstReferenceType>::type ParameterType;
		typedef typename std::conditional<IsArithmetic || IsPointer || IsMemberPointer || IsEnum, ConstType, ConstReferenceType>::type ConstReturnType;
		typedef typename std::conditional<IsArithmetic || IsPointer || IsMemberPointer || IsEnum, T, ReferenceType>::type ReturnType;

		static const char* FixedClassName()
		{
			//a little trick
			const char* name = typeid(UnderlyingType).name();	//return "struct C" or "class C"
			return Compile::FixedClassName(name);
		}
	};

	template<typename T>
	struct ReturnCountTraits
	{
		constexpr static int Value = 1;
	};

	template<>
	struct ReturnCountTraits<void>
	{
		constexpr static int Value = 0;
	};

	template<typename... P>
	struct ReturnCountTraits<std::tuple<P...>>
	{
		constexpr static int Value = sizeof...(P);
	};

	namespace FunctionTraitsDetail
	{

		

		template <typename F>
		struct _FunctionTraitsDetail;

		// check functor

		template <typename F>
		struct _FunctionTraitsDetail
			: _FunctionTraitsDetail<decltype(&F::operator())>
		{};

		// check pointer

		template <typename T>
		struct _FunctionTraitsDetail<T*>
			: _FunctionTraitsDetail<T>
		{};

		// check function pointer

		template <typename R, typename... P>
		struct _FunctionTraitsDetail<R(*)(P...)>
			: _FunctionTraitsDetail<R(P...)>
		{};

		template <typename R, typename... P>
		struct _FunctionTraitsDetail<R(*)(P..., ...)>
			: _FunctionTraitsDetail<R(P..., ...)>
		{};

		// check member function pointer

#define FUNCTION_TRAITS_IMPL__(...)                  \
    template <typename R, typename C, typename... P> \
    struct _FunctionTraitsDetail<R(C::*)(P...) __VA_ARGS__>          \
         : _FunctionTraitsDetail<R(P...)>                            \
	 {\
		typedef C ClassType;\
		};                                              \
    template <typename R, typename C, typename... P> \
    struct _FunctionTraitsDetail<R(C::*)(P..., ...) __VA_ARGS__>     \
         : _FunctionTraitsDetail<R(P..., ...)>                       \
    {\
		typedef C ClassType;\
		};     

		FUNCTION_TRAITS_IMPL__()
			FUNCTION_TRAITS_IMPL__(const)
			FUNCTION_TRAITS_IMPL__(volatile)
			FUNCTION_TRAITS_IMPL__(const volatile)

#undef FUNCTION_TRAITS_IMPL__

			// check std::function

			template <typename R, typename... P>
		struct _FunctionTraitsDetail<std::function<R(P...)>>
			: _FunctionTraitsDetail<R(P...)>
		{};

		template <typename R, typename... P>
		struct _FunctionTraitsDetail<std::function<R(P..., ...)>>
			: _FunctionTraitsDetail<R(P..., ...)>
		{};

		// check function type

		template <typename R, typename... P>
		struct _FunctionTraitsDetail<R(P...)>
		{
			typedef R type(P...);
			typedef R return_type;
			typedef std::tuple<P...> parameters;
			constexpr static int ReturnCount = ReturnCountTraits<R>::Value;
		};

		template <typename R, typename... P>
		struct _FunctionTraitsDetail<R(P..., ...)>
		{
			typedef R type(P..., ...);
			typedef R return_type;
			typedef std::tuple<P...> parameters;
			constexpr static int ReturnCount = ReturnCountTraits<R>::Value;
		};

		//check member function
	}

	template <typename F>
	using FunctionTraits = FunctionTraitsDetail::_FunctionTraitsDetail<typename std::decay<F>::type>;

	template<size_t...>
	struct IndexTuple {};

	template<size_t N, size_t... Indexes>
	struct MakeIndexes : MakeIndexes<N - 1, N - 1, Indexes...> {};

	template<size_t... N>
	struct MakeIndexes<0, N...>
	{
		typedef IndexTuple<N...> type;
	};

	template <typename T>
	struct _IsReferenceWrapper : std::false_type {};

	template <typename T>
	struct _IsReferenceWrapper<std::reference_wrapper<T>> : std::true_type {};

	template <typename T>
	using IsReferenceWrapper = _IsReferenceWrapper<typename std::decay<T>::type>;


	template<typename T>
	MEDUSA_FORCE_INLINE T DefaultValue() { return T{}; }

	template<>
	void DefaultValue<void>();


	template<typename T>
	struct DefaultDigitWidth { constexpr static size_t value = 0; };

	template<> struct DefaultDigitWidth<bool> { constexpr static size_t value = 5 + 1; };	//for "true" and "false"
	template<> struct DefaultDigitWidth<char> { constexpr static size_t value = 3 + 1; };
	template<> struct DefaultDigitWidth<byte> { constexpr static size_t value = 3 + 1; };
	template<> struct DefaultDigitWidth<short> { constexpr static size_t value = 5 + 1; };
	template<> struct DefaultDigitWidth<ushort> { constexpr static size_t value = 5 + 1; };
	template<> struct DefaultDigitWidth<int> { constexpr static size_t value = 10 + 1; };
	template<> struct DefaultDigitWidth<uint> { constexpr static size_t value = 10 + 1; };
	template<> struct DefaultDigitWidth<int64> { constexpr static size_t value = 19 + 1; };
	template<> struct DefaultDigitWidth<uint64> { constexpr static size_t value = 20 + 1; };
	template<> struct DefaultDigitWidth<long> { constexpr static size_t value = 19 + 1; };
	template<> struct DefaultDigitWidth<ulong> { constexpr static size_t value = 20 + 1; };
	template<> struct DefaultDigitWidth<float> { constexpr static size_t value = 24 + 1; };
	template<> struct DefaultDigitWidth<double> { constexpr static size_t value = 53 + 1; };
	template<> struct DefaultDigitWidth<wchar_t> { constexpr static size_t value = 5 + 1; };


	//+1 for '/0',+2 for '0x' prefi
	template<typename T>
	struct HexDigitWidth { constexpr static size_t value = sizeof(T)*8/4+1+2; };

	template<> struct HexDigitWidth<bool> { constexpr static size_t value = 1 + 1+2; };
	
}

MEDUSA_END;
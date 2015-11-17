// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once

#include "CorePlatform/CorePlatformDefines.h"
#include "CorePlatform/CommonMarcos.h"



MEDUSA_BEGIN;


#define MACRO_BRACKET_L (
#define MACRO_BRACKET_R )
#define MACRO_EMPTY
#define MACRO_COMMA ,
#define MACRO_KEEP(x) x

#define MACRO_TO_STRING(x) MACRO_TO_STRING_HELPER(x)
#define MACRO_TO_STRING_HELPER(x) #x

#define MACRO_CONCAT( x, y ) MACRO_CONCAT_HELPER( x, y )
#define MACRO_CONCAT_HELPER( x, y ) x##y 


#define MACRO_INT_DEC(n)        MACRO_CONCAT(MACRO_INT_DEC_,n)
#define MACRO_INT_INC(n)        MACRO_CONCAT(MACRO_INT_INC_,n)
#define MACRO_INT_TO_BOOL(n)   MACRO_CONCAT(MACRO_INT_TO_BOOL_,n)

#define MACRO_IF_ELSE(B,T,F)	MACRO_CONCAT(MACRO_IF_ELSE_,MACRO_INT_TO_BOOL(B))(T,F)
#define MACRO_IF_ELSE_1(T, F) T
#define MACRO_IF_ELSE_0(T, F) F

#define MACRO_IF(B,T) MACRO_IF_ELSE(B,T,MACRO_EMPTY)
#define MACRO_COMMA_IF(B) MACRO_IF_ELSE(B,MACRO_COMMA,MACRO_EMPTY)

#define MACRO_REPEAT(N,M,P)        MACRO_CONCAT(MACRO_REPEAT_,N)(M,P)			//from 0-N
#define MACRO_REPEAT2(N,M,P)        MACRO_CONCAT(MACRO_REPEAT_2_,N)(M,P)		//from 0-N, why we need 2 repeat? because we cannot use repeat in a repeat!

#define MACRO_PARAM_0(N, P) 
#define MACRO_PARAM_1(N, P) MACRO_COMMA_IF(MACRO_INT_DEC(N)) MACRO_CONCAT(P,N)
#define MACRO_PARAM(N, P) MACRO_IF_ELSE(N,MACRO_PARAM_1(N,P),MACRO_PARAM_0(N,P))
#define MACRO_REPEAT_PARAM(N,P)        MACRO_REPEAT(N,MACRO_PARAM,P)

	//auto generated macros -- begin
#define MACRO_MAX_LIMIT 30

#define MACRO_REPEAT_0(M,P)		   M(0,P)
#define MACRO_REPEAT_1(M,P)		   MACRO_REPEAT_0(M,P)M(1,P)
#define MACRO_REPEAT_2(M, P)       MACRO_REPEAT_1(M, P)M(2, P)
#define MACRO_REPEAT_3(M, P)       MACRO_REPEAT_2(M, P)M(3, P)
#define MACRO_REPEAT_4(M, P)       MACRO_REPEAT_3(M, P)M(4, P)
#define MACRO_REPEAT_5(M, P)       MACRO_REPEAT_4(M, P)M(5, P)
#define MACRO_REPEAT_6(M, P)       MACRO_REPEAT_5(M, P)M(6, P)
#define MACRO_REPEAT_7(M, P)       MACRO_REPEAT_6(M, P)M(7, P)
#define MACRO_REPEAT_8(M, P)       MACRO_REPEAT_7(M, P)M(8, P)
#define MACRO_REPEAT_9(M, P)       MACRO_REPEAT_8(M, P)M(9, P)
#define MACRO_REPEAT_10(M, P)      MACRO_REPEAT_9(M, P)M(10, P)
#define MACRO_REPEAT_11(M, P)      MACRO_REPEAT_10(M, P)M(11, P)
#define MACRO_REPEAT_12(M, P)      MACRO_REPEAT_11(M, P)M(12, P)
#define MACRO_REPEAT_13(M, P)      MACRO_REPEAT_12(M, P)M(13, P)
#define MACRO_REPEAT_14(M, P)      MACRO_REPEAT_13(M, P)M(14, P)
#define MACRO_REPEAT_15(M, P)      MACRO_REPEAT_14(M, P)M(15, P)
#define MACRO_REPEAT_16(M, P)      MACRO_REPEAT_15(M, P)M(16, P)
#define MACRO_REPEAT_17(M, P)      MACRO_REPEAT_16(M, P)M(17, P)
#define MACRO_REPEAT_18(M, P)      MACRO_REPEAT_17(M, P)M(18, P)
#define MACRO_REPEAT_19(M, P)      MACRO_REPEAT_18(M, P)M(19, P)
#define MACRO_REPEAT_20(M, P)      MACRO_REPEAT_19(M, P)M(20, P)
#define MACRO_REPEAT_21(M, P)      MACRO_REPEAT_20(M, P)M(21, P)
#define MACRO_REPEAT_22(M, P)      MACRO_REPEAT_21(M, P)M(22, P)
#define MACRO_REPEAT_23(M, P)      MACRO_REPEAT_22(M, P)M(23, P)
#define MACRO_REPEAT_24(M, P)      MACRO_REPEAT_23(M, P)M(24, P)
#define MACRO_REPEAT_25(M, P)      MACRO_REPEAT_24(M, P)M(25, P)
#define MACRO_REPEAT_26(M, P)      MACRO_REPEAT_25(M, P)M(26, P)
#define MACRO_REPEAT_27(M, P)      MACRO_REPEAT_26(M, P)M(27, P)
#define MACRO_REPEAT_28(M, P)      MACRO_REPEAT_27(M, P)M(28, P)
#define MACRO_REPEAT_29(M, P)      MACRO_REPEAT_28(M, P)M(29, P)
#define MACRO_REPEAT_30(M, P)      MACRO_REPEAT_29(M, P)M(30, P)


#define MACRO_REPEAT_2_0(M,P)		 M(0,P)
#define MACRO_REPEAT_2_1(M,P)		 MACRO_REPEAT_2_0(M, P)M(1, P)
#define MACRO_REPEAT_2_2(M, P)       MACRO_REPEAT_2_1(M, P)M(2, P)
#define MACRO_REPEAT_2_3(M, P)       MACRO_REPEAT_2_2(M, P)M(3, P)
#define MACRO_REPEAT_2_4(M, P)       MACRO_REPEAT_2_3(M, P)M(4, P)
#define MACRO_REPEAT_2_5(M, P)       MACRO_REPEAT_2_4(M, P)M(5, P)
#define MACRO_REPEAT_2_6(M, P)       MACRO_REPEAT_2_5(M, P)M(6, P)
#define MACRO_REPEAT_2_7(M, P)       MACRO_REPEAT_2_6(M, P)M(7, P)
#define MACRO_REPEAT_2_8(M, P)       MACRO_REPEAT_2_7(M, P)M(8, P)
#define MACRO_REPEAT_2_9(M, P)       MACRO_REPEAT_2_8(M, P)M(9, P)
#define MACRO_REPEAT_2_10(M, P)      MACRO_REPEAT_2_9(M, P)M(10, P)
#define MACRO_REPEAT_2_11(M, P)      MACRO_REPEAT_2_10(M, P)M(11, P)
#define MACRO_REPEAT_2_12(M, P)      MACRO_REPEAT_2_11(M, P)M(12, P)
#define MACRO_REPEAT_2_13(M, P)      MACRO_REPEAT_2_12(M, P)M(13, P)
#define MACRO_REPEAT_2_14(M, P)      MACRO_REPEAT_2_13(M, P)M(14, P)
#define MACRO_REPEAT_2_15(M, P)      MACRO_REPEAT_2_14(M, P)M(15, P)
#define MACRO_REPEAT_2_16(M, P)      MACRO_REPEAT_2_15(M, P)M(16, P)
#define MACRO_REPEAT_2_17(M, P)      MACRO_REPEAT_2_16(M, P)M(17, P)
#define MACRO_REPEAT_2_18(M, P)      MACRO_REPEAT_2_17(M, P)M(18, P)
#define MACRO_REPEAT_2_19(M, P)      MACRO_REPEAT_2_18(M, P)M(19, P)
#define MACRO_REPEAT_2_20(M, P)      MACRO_REPEAT_2_19(M, P)M(20, P)
#define MACRO_REPEAT_2_21(M, P)      MACRO_REPEAT_2_20(M, P)M(21, P)
#define MACRO_REPEAT_2_22(M, P)      MACRO_REPEAT_2_21(M, P)M(22, P)
#define MACRO_REPEAT_2_23(M, P)      MACRO_REPEAT_2_22(M, P)M(23, P)
#define MACRO_REPEAT_2_24(M, P)      MACRO_REPEAT_2_23(M, P)M(24, P)
#define MACRO_REPEAT_2_25(M, P)      MACRO_REPEAT_2_24(M, P)M(25, P)
#define MACRO_REPEAT_2_26(M, P)      MACRO_REPEAT_2_25(M, P)M(26, P)
#define MACRO_REPEAT_2_27(M, P)      MACRO_REPEAT_2_26(M, P)M(27, P)
#define MACRO_REPEAT_2_28(M, P)      MACRO_REPEAT_2_27(M, P)M(28, P)
#define MACRO_REPEAT_2_29(M, P)      MACRO_REPEAT_2_28(M, P)M(29, P)
#define MACRO_REPEAT_2_30(M, P)      MACRO_REPEAT_2_29(M, P)M(30, P)

#define MACRO_INT_DEC_1        0
#define MACRO_INT_DEC_2        1
#define MACRO_INT_DEC_3        2
#define MACRO_INT_DEC_4        3
#define MACRO_INT_DEC_5        4
#define MACRO_INT_DEC_6        5
#define MACRO_INT_DEC_7        6
#define MACRO_INT_DEC_8        7
#define MACRO_INT_DEC_9        8
#define MACRO_INT_DEC_10       9
#define MACRO_INT_DEC_11       10
#define MACRO_INT_DEC_12       11
#define MACRO_INT_DEC_13       12
#define MACRO_INT_DEC_14       13
#define MACRO_INT_DEC_15       14
#define MACRO_INT_DEC_16       15
#define MACRO_INT_DEC_17       16
#define MACRO_INT_DEC_18       17
#define MACRO_INT_DEC_19       18
#define MACRO_INT_DEC_20       19
#define MACRO_INT_DEC_21       20
#define MACRO_INT_DEC_22       21
#define MACRO_INT_DEC_23       22
#define MACRO_INT_DEC_24       23
#define MACRO_INT_DEC_25       24
#define MACRO_INT_DEC_26       25
#define MACRO_INT_DEC_27       26
#define MACRO_INT_DEC_28       27
#define MACRO_INT_DEC_29       28
#define MACRO_INT_DEC_30       29

#define MACRO_INT_INC_0        1
#define MACRO_INT_INC_1        2
#define MACRO_INT_INC_2        3
#define MACRO_INT_INC_3        4
#define MACRO_INT_INC_4        5
#define MACRO_INT_INC_5        6
#define MACRO_INT_INC_6        7
#define MACRO_INT_INC_7        8
#define MACRO_INT_INC_8        9
#define MACRO_INT_INC_9        10
#define MACRO_INT_INC_10       11
#define MACRO_INT_INC_11       12
#define MACRO_INT_INC_12       13
#define MACRO_INT_INC_13       14
#define MACRO_INT_INC_14       15
#define MACRO_INT_INC_15       16
#define MACRO_INT_INC_16       17
#define MACRO_INT_INC_17       18
#define MACRO_INT_INC_18       19
#define MACRO_INT_INC_19       20
#define MACRO_INT_INC_20       21
#define MACRO_INT_INC_21       22
#define MACRO_INT_INC_22       23
#define MACRO_INT_INC_23       24
#define MACRO_INT_INC_24       25
#define MACRO_INT_INC_25       26
#define MACRO_INT_INC_26       27
#define MACRO_INT_INC_27       28
#define MACRO_INT_INC_28       29
#define MACRO_INT_INC_29       30


#define MACRO_INT_TO_BOOL_0        0
#define MACRO_INT_TO_BOOL_1        1
#define MACRO_INT_TO_BOOL_2        1
#define MACRO_INT_TO_BOOL_3        1
#define MACRO_INT_TO_BOOL_4        1
#define MACRO_INT_TO_BOOL_5        1
#define MACRO_INT_TO_BOOL_6        1
#define MACRO_INT_TO_BOOL_7        1
#define MACRO_INT_TO_BOOL_8        1
#define MACRO_INT_TO_BOOL_9        1
#define MACRO_INT_TO_BOOL_10       1
#define MACRO_INT_TO_BOOL_11       1
#define MACRO_INT_TO_BOOL_12       1
#define MACRO_INT_TO_BOOL_13       1
#define MACRO_INT_TO_BOOL_14       1
#define MACRO_INT_TO_BOOL_15       1
#define MACRO_INT_TO_BOOL_16       1
#define MACRO_INT_TO_BOOL_17       1
#define MACRO_INT_TO_BOOL_18       1
#define MACRO_INT_TO_BOOL_19       1
#define MACRO_INT_TO_BOOL_20       1
#define MACRO_INT_TO_BOOL_21       1
#define MACRO_INT_TO_BOOL_22       1
#define MACRO_INT_TO_BOOL_23       1
#define MACRO_INT_TO_BOOL_24       1
#define MACRO_INT_TO_BOOL_25       1
#define MACRO_INT_TO_BOOL_26       1
#define MACRO_INT_TO_BOOL_27       1
#define MACRO_INT_TO_BOOL_28       1
#define MACRO_INT_TO_BOOL_29       1
#define MACRO_INT_TO_BOOL_30       1
	//auto generated macros -- end


#define MACRO_DEFINE_CONST_STATIC_INT(name,value) const static int name=value;
#define MACRO_DEFINE_CONST_STATIC_BOOL(name,value) const static bool name=value;

//Count the number of args
#define MACRO_ARG_COUNT(...) MACRO_ARG_COUNT_HELPER( __VA_ARGS__, MACRO_ARG_COUNT_RSEQ_N())

#ifdef MEDUSA_WINDOWS
#define MACRO_ARG_COUNT_HELPER(...) MACRO_ARG_COUNT_HELPER2 MACRO_BRACKET_L __VA_ARGS__ MACRO_BRACKET_R
#else
#define MACRO_ARG_COUNT_HELPER(...) MACRO_ARG_COUNT_HELPER2(__VA_ARGS__)
#endif

#define MACRO_ARG_COUNT_HELPER2( _1, _2, _3, _4, _5, _6, _7, _8, _9,_10, _11,_12,_13,_14,_15,_16, N,...) N
#define MACRO_ARG_COUNT_RSEQ_N() 16,15,14,13,12,11,10, 9,8,7,6,5,4,3,2,1,0

MEDUSA_END;
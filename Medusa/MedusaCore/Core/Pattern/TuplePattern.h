// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once


#include "MedusaCorePreDeclares.h"
#include "Core/Compile/TypeTraits.h"
#include "Core/Hash/HashUtility.h"

MEDUSA_BEGIN;

//BEGIN_AUTO_GENERATE_TUPLE
#define MEDUSA_TUPLE_1(TClass,T1,P1)	\
struct TClass	\
{	\
typedef Compile::TypeTraits<T1>::ParameterType T1ParameterType; \
T1 P1; \
TClass():P1(){}	\
TClass(T1ParameterType p1):P1(p1){}  \
TClass& operator=(const TClass& val){P1=val.P1;return *this;}	\
bool operator==(const TClass& val)const{return P1==val.P1;}	\
bool operator!=(const TClass& val)const{return P1!=val.P1;}	\
bool operator<(const TClass& val)const{return P1<val.P1;}	\
intp HashCode()const{return HashUtility::Hash(P1);}	\
};


#define MEDUSA_TUPLE_2(TClass,T1,P1,T2,P2)	\
struct TClass	\
{	\
typedef Compile::TypeTraits<T1>::ParameterType T1ParameterType; \
typedef Compile::TypeTraits<T2>::ParameterType T2ParameterType; \
T1 P1; \
T2 P2; \
TClass():P1(),P2(){}	\
TClass(T1ParameterType p1,T2ParameterType p2):P1(p1),P2(p2){}  \
TClass& operator=(const TClass& val){P1=val.P1;P2=val.P2;return *this;}	\
bool operator==(const TClass& val)const{return P1==val.P1&&P2==val.P2;}	\
bool operator!=(const TClass& val)const{return P1!=val.P1||P2!=val.P2;}	\
bool operator<(const TClass& val)const{return P1<val.P1&&P2<val.P2;}	\
intp HashCode()const{return HashUtility::Hash(P1)^HashUtility::Hash(P2);}	\
};


#define MEDUSA_TUPLE_3(TClass,T1,P1,T2,P2,T3,P3)	\
struct TClass	\
{	\
typedef Compile::TypeTraits<T1>::ParameterType T1ParameterType; \
typedef Compile::TypeTraits<T2>::ParameterType T2ParameterType; \
typedef Compile::TypeTraits<T3>::ParameterType T3ParameterType; \
T1 P1; \
T2 P2; \
T3 P3; \
TClass():P1(),P2(),P3(){}	\
TClass(T1ParameterType p1,T2ParameterType p2,T3ParameterType p3):P1(p1),P2(p2),P3(p3){}  \
TClass& operator=(const TClass& val){P1=val.P1;P2=val.P2;P3=val.P3;return *this;}	\
bool operator==(const TClass& val)const{return P1==val.P1&&P2==val.P2&&P3==val.P3;}	\
bool operator!=(const TClass& val)const{return P1!=val.P1||P2!=val.P2||P3!=val.P3;}	\
bool operator<(const TClass& val)const{return P1<val.P1&&P2<val.P2&&P3<val.P3;}	\
intp HashCode()const{return HashUtility::Hash(P1)^HashUtility::Hash(P2)^HashUtility::Hash(P3);}	\
};


#define MEDUSA_TUPLE_4(TClass,T1,P1,T2,P2,T3,P3,T4,P4)	\
struct TClass	\
{	\
typedef Compile::TypeTraits<T1>::ParameterType T1ParameterType; \
typedef Compile::TypeTraits<T2>::ParameterType T2ParameterType; \
typedef Compile::TypeTraits<T3>::ParameterType T3ParameterType; \
typedef Compile::TypeTraits<T4>::ParameterType T4ParameterType; \
T1 P1; \
T2 P2; \
T3 P3; \
T4 P4; \
TClass():P1(),P2(),P3(),P4(){}	\
TClass(T1ParameterType p1,T2ParameterType p2,T3ParameterType p3,T4ParameterType p4):P1(p1),P2(p2),P3(p3),P4(p4){}  \
TClass& operator=(const TClass& val){P1=val.P1;P2=val.P2;P3=val.P3;P4=val.P4;return *this;}	\
bool operator==(const TClass& val)const{return P1==val.P1&&P2==val.P2&&P3==val.P3&&P4==val.P4;}	\
bool operator!=(const TClass& val)const{return P1!=val.P1||P2!=val.P2||P3!=val.P3||P4!=val.P4;}	\
bool operator<(const TClass& val)const{return P1<val.P1&&P2<val.P2&&P3<val.P3&&P4<val.P4;}	\
intp HashCode()const{return HashUtility::Hash(P1)^HashUtility::Hash(P2)^HashUtility::Hash(P3)^HashUtility::Hash(P4);}	\
};


#define MEDUSA_TUPLE_5(TClass,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5)	\
struct TClass	\
{	\
typedef Compile::TypeTraits<T1>::ParameterType T1ParameterType; \
typedef Compile::TypeTraits<T2>::ParameterType T2ParameterType; \
typedef Compile::TypeTraits<T3>::ParameterType T3ParameterType; \
typedef Compile::TypeTraits<T4>::ParameterType T4ParameterType; \
typedef Compile::TypeTraits<T5>::ParameterType T5ParameterType; \
T1 P1; \
T2 P2; \
T3 P3; \
T4 P4; \
T5 P5; \
TClass():P1(),P2(),P3(),P4(),P5(){}	\
TClass(T1ParameterType p1,T2ParameterType p2,T3ParameterType p3,T4ParameterType p4,T5ParameterType p5):P1(p1),P2(p2),P3(p3),P4(p4),P5(p5){}  \
TClass& operator=(const TClass& val){P1=val.P1;P2=val.P2;P3=val.P3;P4=val.P4;P5=val.P5;return *this;}	\
bool operator==(const TClass& val)const{return P1==val.P1&&P2==val.P2&&P3==val.P3&&P4==val.P4&&P5==val.P5;}	\
bool operator!=(const TClass& val)const{return P1!=val.P1||P2!=val.P2||P3!=val.P3||P4!=val.P4||P5!=val.P5;}	\
bool operator<(const TClass& val)const{return P1<val.P1&&P2<val.P2&&P3<val.P3&&P4<val.P4&&P5<val.P5;}	\
intp HashCode()const{return HashUtility::Hash(P1)^HashUtility::Hash(P2)^HashUtility::Hash(P3)^HashUtility::Hash(P4)^HashUtility::Hash(P5);}	\
};


#define MEDUSA_TUPLE_6(TClass,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6)	\
struct TClass	\
{	\
typedef Compile::TypeTraits<T1>::ParameterType T1ParameterType; \
typedef Compile::TypeTraits<T2>::ParameterType T2ParameterType; \
typedef Compile::TypeTraits<T3>::ParameterType T3ParameterType; \
typedef Compile::TypeTraits<T4>::ParameterType T4ParameterType; \
typedef Compile::TypeTraits<T5>::ParameterType T5ParameterType; \
typedef Compile::TypeTraits<T6>::ParameterType T6ParameterType; \
T1 P1; \
T2 P2; \
T3 P3; \
T4 P4; \
T5 P5; \
T6 P6; \
TClass():P1(),P2(),P3(),P4(),P5(),P6(){}	\
TClass(T1ParameterType p1,T2ParameterType p2,T3ParameterType p3,T4ParameterType p4,T5ParameterType p5,T6ParameterType p6):P1(p1),P2(p2),P3(p3),P4(p4),P5(p5),P6(p6){}  \
TClass& operator=(const TClass& val){P1=val.P1;P2=val.P2;P3=val.P3;P4=val.P4;P5=val.P5;P6=val.P6;return *this;}	\
bool operator==(const TClass& val)const{return P1==val.P1&&P2==val.P2&&P3==val.P3&&P4==val.P4&&P5==val.P5&&P6==val.P6;}	\
bool operator!=(const TClass& val)const{return P1!=val.P1||P2!=val.P2||P3!=val.P3||P4!=val.P4||P5!=val.P5||P6!=val.P6;}	\
bool operator<(const TClass& val)const{return P1<val.P1&&P2<val.P2&&P3<val.P3&&P4<val.P4&&P5<val.P5&&P6<val.P6;}	\
intp HashCode()const{return HashUtility::Hash(P1)^HashUtility::Hash(P2)^HashUtility::Hash(P3)^HashUtility::Hash(P4)^HashUtility::Hash(P5)^HashUtility::Hash(P6);}	\
};


#define MEDUSA_TUPLE_7(TClass,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7)	\
struct TClass	\
{	\
typedef Compile::TypeTraits<T1>::ParameterType T1ParameterType; \
typedef Compile::TypeTraits<T2>::ParameterType T2ParameterType; \
typedef Compile::TypeTraits<T3>::ParameterType T3ParameterType; \
typedef Compile::TypeTraits<T4>::ParameterType T4ParameterType; \
typedef Compile::TypeTraits<T5>::ParameterType T5ParameterType; \
typedef Compile::TypeTraits<T6>::ParameterType T6ParameterType; \
typedef Compile::TypeTraits<T7>::ParameterType T7ParameterType; \
T1 P1; \
T2 P2; \
T3 P3; \
T4 P4; \
T5 P5; \
T6 P6; \
T7 P7; \
TClass():P1(),P2(),P3(),P4(),P5(),P6(),P7(){}	\
TClass(T1ParameterType p1,T2ParameterType p2,T3ParameterType p3,T4ParameterType p4,T5ParameterType p5,T6ParameterType p6,T7ParameterType p7):P1(p1),P2(p2),P3(p3),P4(p4),P5(p5),P6(p6),P7(p7){}  \
TClass& operator=(const TClass& val){P1=val.P1;P2=val.P2;P3=val.P3;P4=val.P4;P5=val.P5;P6=val.P6;P7=val.P7;return *this;}	\
bool operator==(const TClass& val)const{return P1==val.P1&&P2==val.P2&&P3==val.P3&&P4==val.P4&&P5==val.P5&&P6==val.P6&&P7==val.P7;}	\
bool operator!=(const TClass& val)const{return P1!=val.P1||P2!=val.P2||P3!=val.P3||P4!=val.P4||P5!=val.P5||P6!=val.P6||P7!=val.P7;}	\
bool operator<(const TClass& val)const{return P1<val.P1&&P2<val.P2&&P3<val.P3&&P4<val.P4&&P5<val.P5&&P6<val.P6&&P7<val.P7;}	\
intp HashCode()const{return HashUtility::Hash(P1)^HashUtility::Hash(P2)^HashUtility::Hash(P3)^HashUtility::Hash(P4)^HashUtility::Hash(P5)^HashUtility::Hash(P6)^HashUtility::Hash(P7);}	\
};


#define MEDUSA_TUPLE_8(TClass,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8)	\
struct TClass	\
{	\
typedef Compile::TypeTraits<T1>::ParameterType T1ParameterType; \
typedef Compile::TypeTraits<T2>::ParameterType T2ParameterType; \
typedef Compile::TypeTraits<T3>::ParameterType T3ParameterType; \
typedef Compile::TypeTraits<T4>::ParameterType T4ParameterType; \
typedef Compile::TypeTraits<T5>::ParameterType T5ParameterType; \
typedef Compile::TypeTraits<T6>::ParameterType T6ParameterType; \
typedef Compile::TypeTraits<T7>::ParameterType T7ParameterType; \
typedef Compile::TypeTraits<T8>::ParameterType T8ParameterType; \
T1 P1; \
T2 P2; \
T3 P3; \
T4 P4; \
T5 P5; \
T6 P6; \
T7 P7; \
T8 P8; \
TClass():P1(),P2(),P3(),P4(),P5(),P6(),P7(),P8(){}	\
TClass(T1ParameterType p1,T2ParameterType p2,T3ParameterType p3,T4ParameterType p4,T5ParameterType p5,T6ParameterType p6,T7ParameterType p7,T8ParameterType p8):P1(p1),P2(p2),P3(p3),P4(p4),P5(p5),P6(p6),P7(p7),P8(p8){}  \
TClass& operator=(const TClass& val){P1=val.P1;P2=val.P2;P3=val.P3;P4=val.P4;P5=val.P5;P6=val.P6;P7=val.P7;P8=val.P8;return *this;}	\
bool operator==(const TClass& val)const{return P1==val.P1&&P2==val.P2&&P3==val.P3&&P4==val.P4&&P5==val.P5&&P6==val.P6&&P7==val.P7&&P8==val.P8;}	\
bool operator!=(const TClass& val)const{return P1!=val.P1||P2!=val.P2||P3!=val.P3||P4!=val.P4||P5!=val.P5||P6!=val.P6||P7!=val.P7||P8!=val.P8;}	\
bool operator<(const TClass& val)const{return P1<val.P1&&P2<val.P2&&P3<val.P3&&P4<val.P4&&P5<val.P5&&P6<val.P6&&P7<val.P7&&P8<val.P8;}	\
intp HashCode()const{return HashUtility::Hash(P1)^HashUtility::Hash(P2)^HashUtility::Hash(P3)^HashUtility::Hash(P4)^HashUtility::Hash(P5)^HashUtility::Hash(P6)^HashUtility::Hash(P7)^HashUtility::Hash(P8);}	\
};


#define MEDUSA_TUPLE_9(TClass,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9)	\
struct TClass	\
{	\
typedef Compile::TypeTraits<T1>::ParameterType T1ParameterType; \
typedef Compile::TypeTraits<T2>::ParameterType T2ParameterType; \
typedef Compile::TypeTraits<T3>::ParameterType T3ParameterType; \
typedef Compile::TypeTraits<T4>::ParameterType T4ParameterType; \
typedef Compile::TypeTraits<T5>::ParameterType T5ParameterType; \
typedef Compile::TypeTraits<T6>::ParameterType T6ParameterType; \
typedef Compile::TypeTraits<T7>::ParameterType T7ParameterType; \
typedef Compile::TypeTraits<T8>::ParameterType T8ParameterType; \
typedef Compile::TypeTraits<T9>::ParameterType T9ParameterType; \
T1 P1; \
T2 P2; \
T3 P3; \
T4 P4; \
T5 P5; \
T6 P6; \
T7 P7; \
T8 P8; \
T9 P9; \
TClass():P1(),P2(),P3(),P4(),P5(),P6(),P7(),P8(),P9(){}	\
TClass(T1ParameterType p1,T2ParameterType p2,T3ParameterType p3,T4ParameterType p4,T5ParameterType p5,T6ParameterType p6,T7ParameterType p7,T8ParameterType p8,T9ParameterType p9):P1(p1),P2(p2),P3(p3),P4(p4),P5(p5),P6(p6),P7(p7),P8(p8),P9(p9){}  \
TClass& operator=(const TClass& val){P1=val.P1;P2=val.P2;P3=val.P3;P4=val.P4;P5=val.P5;P6=val.P6;P7=val.P7;P8=val.P8;P9=val.P9;return *this;}	\
bool operator==(const TClass& val)const{return P1==val.P1&&P2==val.P2&&P3==val.P3&&P4==val.P4&&P5==val.P5&&P6==val.P6&&P7==val.P7&&P8==val.P8&&P9==val.P9;}	\
bool operator!=(const TClass& val)const{return P1!=val.P1||P2!=val.P2||P3!=val.P3||P4!=val.P4||P5!=val.P5||P6!=val.P6||P7!=val.P7||P8!=val.P8||P9!=val.P9;}	\
bool operator<(const TClass& val)const{return P1<val.P1&&P2<val.P2&&P3<val.P3&&P4<val.P4&&P5<val.P5&&P6<val.P6&&P7<val.P7&&P8<val.P8&&P9<val.P9;}	\
intp HashCode()const{return HashUtility::Hash(P1)^HashUtility::Hash(P2)^HashUtility::Hash(P3)^HashUtility::Hash(P4)^HashUtility::Hash(P5)^HashUtility::Hash(P6)^HashUtility::Hash(P7)^HashUtility::Hash(P8)^HashUtility::Hash(P9);}	\
};


#define MEDUSA_TUPLE_10(TClass,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10)	\
struct TClass	\
{	\
typedef Compile::TypeTraits<T1>::ParameterType T1ParameterType; \
typedef Compile::TypeTraits<T2>::ParameterType T2ParameterType; \
typedef Compile::TypeTraits<T3>::ParameterType T3ParameterType; \
typedef Compile::TypeTraits<T4>::ParameterType T4ParameterType; \
typedef Compile::TypeTraits<T5>::ParameterType T5ParameterType; \
typedef Compile::TypeTraits<T6>::ParameterType T6ParameterType; \
typedef Compile::TypeTraits<T7>::ParameterType T7ParameterType; \
typedef Compile::TypeTraits<T8>::ParameterType T8ParameterType; \
typedef Compile::TypeTraits<T9>::ParameterType T9ParameterType; \
typedef Compile::TypeTraits<T10>::ParameterType T10ParameterType; \
T1 P1; \
T2 P2; \
T3 P3; \
T4 P4; \
T5 P5; \
T6 P6; \
T7 P7; \
T8 P8; \
T9 P9; \
T10 P10; \
TClass():P1(),P2(),P3(),P4(),P5(),P6(),P7(),P8(),P9(),P10(){}	\
TClass(T1ParameterType p1,T2ParameterType p2,T3ParameterType p3,T4ParameterType p4,T5ParameterType p5,T6ParameterType p6,T7ParameterType p7,T8ParameterType p8,T9ParameterType p9,T10ParameterType p10):P1(p1),P2(p2),P3(p3),P4(p4),P5(p5),P6(p6),P7(p7),P8(p8),P9(p9),P10(p10){}  \
TClass& operator=(const TClass& val){P1=val.P1;P2=val.P2;P3=val.P3;P4=val.P4;P5=val.P5;P6=val.P6;P7=val.P7;P8=val.P8;P9=val.P9;P10=val.P10;return *this;}	\
bool operator==(const TClass& val)const{return P1==val.P1&&P2==val.P2&&P3==val.P3&&P4==val.P4&&P5==val.P5&&P6==val.P6&&P7==val.P7&&P8==val.P8&&P9==val.P9&&P10==val.P10;}	\
bool operator!=(const TClass& val)const{return P1!=val.P1||P2!=val.P2||P3!=val.P3||P4!=val.P4||P5!=val.P5||P6!=val.P6||P7!=val.P7||P8!=val.P8||P9!=val.P9||P10!=val.P10;}	\
bool operator<(const TClass& val)const{return P1<val.P1&&P2<val.P2&&P3<val.P3&&P4<val.P4&&P5<val.P5&&P6<val.P6&&P7<val.P7&&P8<val.P8&&P9<val.P9&&P10<val.P10;}	\
intp HashCode()const{return HashUtility::Hash(P1)^HashUtility::Hash(P2)^HashUtility::Hash(P3)^HashUtility::Hash(P4)^HashUtility::Hash(P5)^HashUtility::Hash(P6)^HashUtility::Hash(P7)^HashUtility::Hash(P8)^HashUtility::Hash(P9)^HashUtility::Hash(P10);}	\
};






//END_AUTO_GENERATE_TUPLE


MEDUSA_END;
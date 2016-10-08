#pragma once
//prevent compile error
#undef min
#undef max
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/reader.h"
#include "rapidjson/writer.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/error/en.h"
#define FOR_EACH_JSON(i,items) for(auto i = (items).MemberBegin();i!=(items).MemberEnd();++i) 

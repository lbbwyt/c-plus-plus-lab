//
// Created by lbb on 2022/12/23.
//

#ifndef LIBHV_STUDY_JSONHELPER_H
#define LIBHV_STUDY_JSONHELPER_H

#endif //LIBHV_STUDY_JSONHELPER_H



#include "json/json.h"
#include <string>
#include <vector>
#include <initializer_list>

#define JSONCONVERT2OBJECT_MEMEBER_REGISTER(...)  \
bool JSONCONVERT2OBJECT_MEMEBER_REGISTER_RESERVERD_IMPLE(const Json::Value& jsonTypeValue, std::vector<std::string> &names) \
{     \
    if(names.size() <= 0)  { \
        names = Member2KeyParseWithStr(#__VA_ARGS__); \
    }   \
    return JsonParse(names, 0, jsonTypeValue, __VA_ARGS__); \
}   \
bool OBJECTCONVERT2JSON_MEMEBER_REGISTER_RESERVERD_IMPLE(Json::Value& jsonTypeValue, std::vector<std::string> &names) const \
{     \
    if(names.size() <= 0)  { \
        names = Member2KeyParseWithStr(#__VA_ARGS__); \
    }   \
    return ParseJson(names, 0, jsonTypeValue, __VA_ARGS__); \
}   \

#define JSONCONVERT2OBJECT_MEMEBER_RENAME_REGISTER(...)  \
std::vector<std::string> JSONCONVERT2OBJECT_MEMEBER_RENAME_REGISTER_RESERVERD_IMPLE() const \
{     \
    return Member2KeyParseWithMultiParam({ __VA_ARGS__ }); \
}

namespace JSON
{
    template <bool, class TYPE = void>
    struct enable_if
    {
    };

    template <class TYPE>
    struct enable_if<true, TYPE>
    {
        typedef TYPE type;
    };
} //JSON

template <typename T>
struct HasConverFunction
{
    template <typename TT>
    static char func(decltype(&TT::JSONCONVERT2OBJECT_MEMEBER_REGISTER_RESERVERD_IMPLE)); //@1

    template <typename TT>
    static int func(...); //@2

    const static bool has = (sizeof(func<T>(NULL)) == sizeof(char));

    template <typename TT>
    static char func2(decltype(&TT::JSONCONVERT2OBJECT_MEMEBER_RENAME_REGISTER_RESERVERD_IMPLE)); //@1
    template <typename TT>
    static int func2(...); //@2
    const static bool has2 = (sizeof(func2<T>(NULL)) == sizeof(char));
};

static std::vector<std::string> Member2KeyParseWithMultiParam(std::initializer_list<std::string> il)
{
    std::vector<std::string> result;
    for (auto it = il.begin(); it != il.end(); it++) {
        result.push_back(*it);
    }
    return result;
}

inline static std::string NormalStringTrim(std::string const& str)
{
    static char const* whitespaceChars = "\n\r\t ";
    std::string::size_type start = str.find_first_not_of(whitespaceChars);
    std::string::size_type end = str.find_last_not_of(whitespaceChars);
    return start != std::string::npos ? str.substr(start, 1 + end - start) : std::string();
}

inline static std::vector<std::string> NormalStringSplit(std::string str, char splitElem)
{
    std::vector<std::string> strs;
    std::string::size_type pos1, pos2;
    pos2 = str.find(splitElem);
    pos1 = 0;
    while (std::string::npos != pos2) {
        strs.push_back(str.substr(pos1, pos2 - pos1));
        pos1 = pos2 + 1;
        pos2 = str.find(splitElem, pos1);
    }
    strs.push_back(str.substr(pos1));
    return strs;
}

static std::vector<std::string> Member2KeyParseWithStr(const std::string& values)
{
    std::vector<std::string> result;
    auto enumValues = NormalStringSplit(values, ',');
    result.reserve(enumValues.size());
    for (auto const& enumValue : enumValues) {
        result.push_back(NormalStringTrim(enumValue));
    }
    return result;
}

//

static bool Json2Object(bool& aimObj, const Json::Value& jsonTypeValue)
{
    if (jsonTypeValue.isNull() || !jsonTypeValue.isBool()) {
        return false;
    } else {
        aimObj = jsonTypeValue.asBool();
        return true;
    }
}
static bool Object2Json(Json::Value& jsonTypeValue, const std::string& key, bool value)
{
    jsonTypeValue[key] = value;
    return true;
}

static bool Json2Object(int& aimObj, const Json::Value& jsonTypeValue)
{
    if (jsonTypeValue.isNull() || !jsonTypeValue.isInt()) {
        return false;
    } else {
        aimObj = jsonTypeValue.asInt();
        return true;
    }
}
static bool Object2Json(Json::Value& jsonTypeValue, const std::string& key, const int& value)
{
    jsonTypeValue[key] = value;
    return true;
}

static bool Json2Object(unsigned int& aimObj, const Json::Value& jsonTypeValue)
{
    if (jsonTypeValue.isNull() || !jsonTypeValue.isUInt()) {
        return false;
    } else {
        aimObj = jsonTypeValue.asUInt();
        return true;
    }
}
static bool Object2Json(Json::Value& jsonTypeValue, const std::string& key, const unsigned int& value)
{
    jsonTypeValue[key] = value;
    return true;
}

static bool Json2Object(double& aimObj, const Json::Value& jsonTypeValue)
{
    if (jsonTypeValue.isNull() || !jsonTypeValue.isDouble()) {
        return false;
    } else {
        aimObj = jsonTypeValue.asDouble();
        return true;
    }
}
static bool Object2Json(Json::Value& jsonTypeValue, const std::string& key, const double& value)
{
    jsonTypeValue[key] = value;
    return true;
}

static bool Json2Object(std::string& aimObj, const Json::Value& jsonTypeValue)
{
    if (jsonTypeValue.isNull() || !jsonTypeValue.isString()) {
        return false;
    } else {
        aimObj = jsonTypeValue.asString();
        return true;
    }
}
static bool Object2Json(Json::Value& jsonTypeValue, const std::string& key, const std::string& value)
{
    jsonTypeValue[key] = value;
    return true;
}

template <typename TClass, typename JSON::enable_if<HasConverFunction<TClass>::has2, int>::type = 0>
static inline std::vector<std::string> PreGetCustomMemberNameIfExists(const TClass& aimObj)
{
    return aimObj.JSONCONVERT2OBJECT_MEMEBER_RENAME_REGISTER_RESERVERD_IMPLE();
}

template <typename TClass, typename JSON::enable_if<!HasConverFunction<TClass>::has2, int>::type = 0>
static inline std::vector<std::string> PreGetCustomMemberNameIfExists(const TClass& aimObj)
{
    return std::vector<std::string>();
}

template <typename TClass, typename JSON::enable_if<HasConverFunction<TClass>::has, int>::type = 0>
static inline bool Json2Object(TClass& aimObj, const Json::Value& jsonTypeValue)
{
    std::vector<std::string> names = PreGetCustomMemberNameIfExists(aimObj);
    return aimObj.JSONCONVERT2OBJECT_MEMEBER_REGISTER_RESERVERD_IMPLE(jsonTypeValue, names);
}

template <typename TClass, typename JSON::enable_if<!HasConverFunction<TClass>::has, int>::type = 0>
static inline bool Json2Object(TClass& aimObj, const Json::Value& jsonTypeValue)
{
    return false;
}

template <typename T>
static bool Json2Object(std::vector<T>& aimObj, const Json::Value& jsonTypeValue)
{
    if (jsonTypeValue.isNull() || !jsonTypeValue.isArray()) {
        return false;
    } else {
        aimObj.clear();
        bool result(true);
        for (int i = 0; i < jsonTypeValue.size(); ++i) {
            T item;
            if (!Json2Object(item, jsonTypeValue[i])) {
                result = false;
            }
            aimObj.push_back(item);
        }
        return result;
    }
}

template <typename T>
static bool JsonParse(const std::vector<std::string>& names, int index, const Json::Value& jsonTypeValue, T& arg)
{
    const auto key = names[index];
    if (!jsonTypeValue.isMember(key) || Json2Object(arg, jsonTypeValue[key])) {
        return true;
    } else {
        return false;
    }
}

template <typename T, typename... Args>
static bool JsonParse(const std::vector<std::string>& names, int index, const Json::Value& jsonTypeValue, T& arg, Args&... args)
{
    if (!JsonParse(names, index, jsonTypeValue, arg)) {
        return false;
    } else {
        return JsonParse(names, index + 1, jsonTypeValue, args...);
    }
}

/** Provider interface*/
template<typename TClass>
bool Json2Object(TClass& aimObj, const std::string& jsonTypeStr)
{
    Json::Reader reader;
    Json::Value root;

    if (!reader.parse(jsonTypeStr, root) || root.isNull()) {
        return false;
    }
    return Json2Object(aimObj, root);
}

static bool GetJsonRootObject(Json::Value& root, const std::string& jsonTypeStr)
{
    Json::Reader reader;
    if (!reader.parse(jsonTypeStr, root)) {
        return false;
    }
    return true;
}



template <typename TClass, typename JSON::enable_if<HasConverFunction<TClass>::has, int>::type = 0>
static inline bool Object2Json(Json::Value& jsonTypeOutValue, const std::string& key, const TClass& objValue)
{
    std::vector<std::string> names = PreGetCustomMemberNameIfExists(objValue);
    if (key.empty()) {
        return objValue.OBJECTCONVERT2JSON_MEMEBER_REGISTER_RESERVERD_IMPLE(jsonTypeOutValue, names);
    } else {
        Json::Value jsonTypeNewValue;
        const bool result = objValue.OBJECTCONVERT2JSON_MEMEBER_REGISTER_RESERVERD_IMPLE(jsonTypeNewValue, names);
        if (result) {
            jsonTypeOutValue[key] = jsonTypeNewValue;
        }
        return result;
    }
}

template <typename TClass, typename JSON::enable_if<!HasConverFunction<TClass>::has, int>::type = 0>
static inline bool Object2Json(Json::Value& jsonTypeOutValue, const std::string& key, const TClass& objValue)
{
    return false;
}

template <typename T>
static bool Object2Json(Json::Value& jsonTypeOutValue, const std::string& key, const std::vector<T>& objValue)
{
    bool result(true);
    for (int i = 0; i < objValue.size(); ++i) {
        Json::Value item;
        if (!Object2Json(item, "", objValue[i])) {
            result = false;
        } else {
            if (key.empty()) jsonTypeOutValue.append(item);
            else jsonTypeOutValue[key].append(item);
        }
    }
    return result;
}

template <typename T>
static bool ParseJson(const std::vector<std::string>& names, int index, Json::Value& jsonTypeValue, const T& arg)
{
    if (names.size() > index) {
        const std::string key = names[index];
        return Object2Json(jsonTypeValue, key, arg);
    } else {
        return false;
    }
}

template <typename T, typename... Args>
static bool ParseJson(const std::vector<std::string>& names, int index, Json::Value& jsonTypeValue, T& arg, Args&... args)
{
    if (names.size() - (index + 0) != 1 + sizeof...(Args)) {
        return false;
    }
    const std::string key = names[index];
    Object2Json(jsonTypeValue, key, arg);

    return ParseJson(names, index + 1, jsonTypeValue, args...);
}

/** Provider interface*/
template<typename T>
bool Object2Json(std::string& jsonTypeStr, const T& obj)
{
    //std::function<Json::Value()>placehoder = [&]()->Json::Value { return Json::Value(); };
    //auto func = [&](std::function<Json::Value()>f) { return f(); };
    //Json::Value val = func(placehoder);

    Json::StyledWriter writer;
    Json::Value root;
    const bool result = Object2Json(root, "", obj);
    if (result) {
        jsonTypeStr = writer.write(root);
    }
    return result;
}


////////////////////////////////////////////////////////////////////////////////////////
// Baidu AI
// C API
// Example 
////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <JuceHeader.h>
#include <iostream>
#include <curl/curl.h>
#include <json/json.h>
const std::string access_token_url = "https://aip.baidubce.com/oauth/2.0/token?grant_type=client_credentials";

static size_t get_access_token_callback(void* ptr, size_t size, size_t nmemb, void* stream) {
    // 获取到的body存放在ptr中，先将其转换为string格式
    std::string s((char*)ptr, size * nmemb);
    // 开始获取json中的access token项目
    Json::Reader reader;
    Json::Value root;
    // 使用boost库解析json
    reader.parse(s, root);
    std::string* access_token_result = static_cast<std::string*>(stream);
    *access_token_result = root["access_token"].asString();
    return size * nmemb;
}

/**
 * 用以获取access_token的函数，使用时需要先在百度云控制台申请相应功能的应用，获得对应的API Key和Secret Key
 * @param access_token 获取得到的access token，调用函数时需传入该参数
 * @param AK 应用的API key
 * @param SK 应用的Secret key
 * @return 返回0代表获取access token成功，其他返回值代表获取失败
 */
std::string get_access_token() {
    CURL* curl;
    CURLcode result_code;
    int error_code = 0;
    curl = curl_easy_init();
    if (curl) {
        std::string url = access_token_url + "&client_id=68kRdbG5YajMqWArVnCtx0z1&client_secret=es2tsieG7HNtwL5yWIYEA60ySmcaiwRg";
        curl_easy_setopt(curl, CURLOPT_URL, url.data());
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
        std::string access_token_result;
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &access_token_result);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, get_access_token_callback);
        result_code = curl_easy_perform(curl);
        if (result_code != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s", curl_easy_strerror(result_code));
            return "";
        }
        auto access_token = access_token_result;
        curl_easy_cleanup(curl);
        return access_token;
    }
    else {
        fprintf(stderr, "curl_easy_init() failed.");
        return "";
    }
}


const static std::string texttrans_request_url = "https://aip.baidubce.com/rpc/2.0/mt/texttrans/v1";

static size_t textTrans_callback(void* ptr, size_t size, size_t nmemb, void* stream) {
    // 获取到的body存放在ptr中，先将其转换为string格式
    juce::String result(juce::CharPointer_UTF8((char*)ptr));
    auto dstStart = result.indexOf(0, "\"dst\":\"");
    auto dstEnd = result.indexOf(dstStart + 7, "\"");
    //Json::Reader reader;
    //Json::Value root;
    // 使用boost库解析json
    //reader.parse(s, root);
    juce::String* textTrans_result = static_cast<juce::String*>(stream);
    if (dstStart != -1 && dstEnd != -1 && dstEnd > dstStart)
        *textTrans_result = result.substring(dstStart + 7, dstEnd);
    else
        *textTrans_result = "";
    return size * nmemb;
}

/**
 * 文本翻译是百度翻译依托领先的自然语言处理技术推出的在线文本翻译服务，可支持中、英、日、韩等200+语言互译，100+语种自动检测。
 * @return 调用成功返回0，发生错误返回其他错误码
 */
juce::String textTrans(juce::String text) {
    auto access_token = get_access_token();
    std::string url = texttrans_request_url + "?access_token=" + access_token;
    CURL* curl = NULL;
    CURLcode result_code;
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.data());
        curl_easy_setopt(curl, CURLOPT_POST, 1);
        curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "Content-Type:application/json;charset=UTF-8");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        juce::String json = "{\"q\":\"" + text + "\",\"from\":\"zh\",\"to\":\"en\"}";
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json.toUTF8());
        juce::String textTrans_result;
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &textTrans_result);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, textTrans_callback);
        result_code = curl_easy_perform(curl);
        if (result_code != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(result_code));
            return "";
        }
        auto json_result = textTrans_result;
        curl_easy_cleanup(curl);
        return json_result;
    }
    else {
        fprintf(stderr, "curl_easy_init() failed.");
        return "";
    }
}
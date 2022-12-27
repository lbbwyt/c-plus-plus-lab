//
// Created by lbb on 2022/12/22.
//


#include <iostream>
#include <requests.h>
#include <rapidjson/document.h>

using namespace std;
using namespace  hv;
using namespace rapidjson;

int main() {
    cout<<"*********************http_get**************************"<<endl;
    auto resp = requests::get("http://127.0.0.1:8081/ping");
    if (resp == NULL) {
        printf("request failed!\n");
    } else {
        printf("%d %s\r\n", resp->status_code, resp->status_message());
        printf("%s\n", resp->body.c_str());
    }
    cout<<"*********************http_post**************************"<<endl;

    // Content-Type: application/json
    hv::Json jroot;
    jroot["scene_id"] = 1;
    jroot["player_id"] = 2;
    http_headers headers;
    headers["Content-Type"] = "application/json";
    resp = requests::post("http://localhost:18080/api/ue4/nearby", jroot.dump(), headers);
    if (resp == NULL || resp->status_code != 200) {
        printf("request failed!\n");
    } else {
        printf("%d %s\r\n", resp->status_code, resp->status_message());
        printf("%s\n", resp->body.c_str());
    }

    cout<<"*********************http_post**************************"<<endl;
    string json2 = "{\"project\":\"rapidjson\",\"stars\":10, \"a\":[1,2,3,4]}";
    Document document2;
    document2.Parse(json2.c_str());
    cout << document2["project"].GetString() << endl;
    for(int i = 0;i < 4; i++) {
        cout << document2["a"][i].GetInt() << endl;
    }

    const char* json = "[{\"a\":0.623,\"b\":-1},{\"a\":0.523,\"b\":-1}]";
    Document document;
    document.Parse(json);
    if(document.IsArray()){
        for(int i = 0; i < document.Size(); i++) {
            if (document[i].IsObject()){
                cout << document[i]["a"].GetDouble() << endl;
            }
        }
    }
    return 0;
}
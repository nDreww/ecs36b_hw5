// for Json::value
#include <json/json.h>
#include <json/reader.h>
#include <json/writer.h>
#include <json/value.h>
#include <string>

// for JsonRPCCPP
#include <iostream>
#include "hw5server.h"
#include <jsonrpccpp/server/connectors/httpserver.h>
// #include "hw5client.h"
#include <jsonrpccpp/client/connectors/httpclient.h>
#include <stdio.h>

// ecs36b
#include "Person.h"
#include "Thing.h"
#include <time.h>
#include "hw5server.cpp"
#include "hw5client.h"

using namespace jsonrpc;
using namespace std;

int main() {
    
    HttpClient httpclient("http://127.0.0.1:7376");
    hw5Client myClient(httpclient, JSONRPC_CLIENT_V2);
    Json::Value myv;
    Json::Value gps;
    gps["location"] = "grandmaHome";

    HttpServer httpserver(7375);
    Myhw5Server s(httpserver, JSONRPC_SERVER_V1V2, "Forest");
    while (!s.isDone) {
        s.StartListening();
    }
    s.StopListening();

    // Create Wolf Person object (stays in forest server)
    Person wolf = Person("Wolf");

    // Access everything in Person map
    for (auto it = s.Person_Map.begin(); it != s.Person_Map.end(); it++) {
        try {
        myv = myClient.move("move", "Person",
                s.Person_Map[it->first]->dump2JSON(),
                gps,
                "LRRH");
        } catch (JsonRpcException &e) {
        cerr << e.what() << endl;
        }
        cout << "Moving LLRH to Grandma's Home..." << endl;
    }

    string things[3] = {"Cap", "Cake", "Wine"};
    // Access everything in Thing map
    int i = 0;
    for (auto it = s.Thing_Map.begin(); it != s.Thing_Map.end(); it++) {
        try {
        myv = myClient.move("move", "Person",
                s.Thing_Map[it->first]->dump2JSON(),
                gps,
                things[i]);
        i++;
        } catch (JsonRpcException &e) {
        cerr << e.what() << endl;
        }
        if (i < 3) {
            cout << "Moving " << things[i] << " to Grandma's Home..." << endl;
        }
    }

    // Run when done moving objects
    Json::Value done;
    try {
    done = myClient.end();
    } catch (JsonRpcException &e) {
    cerr << e.what() << endl;
    }
}
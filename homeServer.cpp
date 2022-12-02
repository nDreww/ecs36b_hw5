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
#include "hw5client.h"
#include <jsonrpccpp/client/connectors/httpclient.h>
// #include "hw5client.h"
#include <jsonrpccpp/client/connectors/httpclient.h>
#include <stdio.h>

// ecs36b
#include "Person.h"
#include "Thing.h"
#include <time.h>
#include "hw5server.cpp"

using namespace jsonrpc;
using namespace std;

int main() {

    // Create Initial Objects
    Person LRRH = Person("Little Red Riding Hood");
    Thing cap = Thing("Cap");
    Thing cake = Thing("Cake");
    Thing wine = Thing("Wine");

    HttpClient httpclient("http://127.0.0.1:7375");
    hw5Client myClient(httpclient, JSONRPC_CLIENT_V2);
    Json::Value myv;
    Json::Value gps;
    gps["location"] = "forest";

    // Move LLRH Person object
    try {
    myv = myClient.move("move", "Person",
            LRRH.dump2JSON(),
            gps,
            "LRRH");
    } catch (JsonRpcException &e) {
    cerr << e.what() << endl;
    }
    cout << "Moving LLRH to Forest..." << endl;

    // Move Cap Thing object
    try {
    myv = myClient.move("move", "Thing",
            cap.dump2JSON(),
            gps,
            "Cap");
    } catch (JsonRpcException &e) {
    cerr << e.what() << endl;
    }
    cout << "Moving Cap to Forest..." << endl;

    // Move Cake Thing object
    try {
    myv = myClient.move("move", "Thing",
            cake.dump2JSON(),
            gps,
            "Cake");
    } catch (JsonRpcException &e) {
    cerr << e.what() << endl;
    }
    cout << "Moving Cake to Forest..." << endl;

    // Move Wine Thing object
    try {
    myv = myClient.move("move", "Thing",
            wine.dump2JSON(),
            gps,
            "Wine");
    } catch (JsonRpcException &e) {
    cerr << e.what() << endl;
    }
    cout << "Moving Wine to Forest..." << endl;

    // Run when done moving objects
    Json::Value done;
    try {
    done = myClient.end();
    } catch (JsonRpcException &e) {
    cerr << e.what() << endl;
    }

    HttpServer httpserver(7374);
    Myhw5Server s(httpserver, JSONRPC_SERVER_V1V2, "Home");
    s.StartListening();
    std::cout << "Hit enter to stop the server" << endl;
    getchar();

    s.StopListening();
}
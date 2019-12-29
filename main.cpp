#include <iostream>
#include <vector>
#include<fstream>
#include "Command.h"
#include "OpenServerCommand.h"
#include "DefineVarCommand.h"
#include "ConnectCommand.h"
#include "PrintCommand.h"
#include "SleepCommand.h"
#include "WhileCommand.h"
#include "AssignmentCommand.h"
#include "IfCommand.h"
#include "Var.h"
#include <map>


using namespace std;

vector<string> lexer(char *string);

void
parser(vector<string> lexered, map<string, Command *> hashMap, map<string, Var *> *varsMap, map<string, Var *> *simMap);

void xmlInit(map<string, Var *> *varsMap, map<string, Var *> *simMap);

map<string, Command *> initilize();


int main(int argc, char *argv[]) {
    if (argc < 2) {
        throw "error-no filename given";
    }
    vector<string> v = lexer(argv[1]);
    map<string, Command *> commandsMap = initilize();
    map<string, Var *> *varsMap = new map<string, Var *>();
    map<string, Var *> *simMap = new map<string, Var *>();
    xmlInit(varsMap, simMap);
    parser(v, commandsMap, varsMap, simMap);
    close(client_socket_client);
    return 0;
}

void xmlInit(map<string, Var *> *varsMap, map<string, Var *> *simMap) {
    //1
    Var *a = new Var(0, -1, "/instrumentation/airspeed-indicator/indicated-speed-kt");
    varsMap->insert({"airspeed", a});
    simMap->insert({"/instrumentation/airspeed-indicator/indicated-speed-kt", a});
    //2
    a = new Var(0, -1, "/sim/time/warp");
    varsMap->insert({"warp", a});
    simMap->insert({"/sim/time/warp", a});
    //3
    a = new Var(0, -1, "/controls/switches/magnetos");
    varsMap->insert({"magnetos", a});
    simMap->insert({"/controls/switches/magnetos", a});
    //4
    a = new Var(0, -1, "/instrumentation/heading-indicator/offset-deg");
    varsMap->insert({"heading", a});
    simMap->insert({"/instrumentation/heading-indicator/offset-deg", a});
    //5
    a = new Var(0, -1, "/instrumentation/altimeter/indicated-altitude-ft");
    varsMap->insert({"alt", a});
    simMap->insert({"/instrumentation/altimeter/indicated-altitude-ft", a});
    //6 does not apper at fly.txt
    a = new Var(0, -1, "/instrumentation/altimeter/pressure-alt-ft");
    varsMap->insert({"altimeter", a});
    simMap->insert({"/instrumentation/altimeter/pressure-alt-ft", a});
    //7 does not apper at fly.txt
    a = new Var(0, -1, "/instrumentation/attitude-indicator/indicated-pitch-deg");
    varsMap->insert({"attitude", a});
    simMap->insert({"/instrumentation/attitude-indicator/indicated-pitch-deg", a});
    //8
    a = new Var(0, -1, "/instrumentation/attitude-indicator/indicated-roll-deg");
    varsMap->insert({"roll", a});
    simMap->insert({"/instrumentation/attitude-indicator/indicated-roll-deg", a});
    //9
    a = new Var(0, -1, "/instrumentation/attitude-indicator/internal-pitch-deg");
    varsMap->insert({"pitch", a});
    simMap->insert({"/instrumentation/attitude-indicator/internal-pitch-deg", a});
    //10 does not apper in fly.txt
    a = new Var(0, -1, "/instrumentation/attitude-indicator/internal-roll-deg");
    varsMap->insert({"attitude2", a});
    simMap->insert({"/instrumentation/attitude-indicator/internal-roll-deg", a});
    //11 does not apper in fly.txt
    a = new Var(0, -1, "/instrumentation/encoder/indicated-altitude-ft");
    varsMap->insert({"attitude3", a});
    simMap->insert({"/instrumentation/encoder/indicated-altitude-ft", a});
    //12 does not apper in fly.txt
    a = new Var(0, -1, "/instrumentation/encoder/pressure-alt-ft");
    varsMap->insert({"pressure", a});
    simMap->insert({"/instrumentation/encoder/pressure-alt-ft", a});
    //13 does not apper in fly.txt
    a = new Var(0, -1, "/instrumentation/gps/indicated-altitude-ft");
    varsMap->insert({"gps", a});
    simMap->insert({"/instrumentation/gps/indicated-altitude-ft", a});
    //14 does not apper in fly.txt
    a = new Var(0, -1, "/instrumentation/gps/indicated-ground-speed-kt");
    varsMap->insert({"gps2", a});
    simMap->insert({"/instrumentation/gps/indicated-ground-speed-kt", a});
    //15 does not apper in fly.txt
    a = new Var(0, -1, "/instrumentation/gps/indicated-vertical-speed");
    varsMap->insert({"gps3", a});
    simMap->insert({"/instrumentation/gps/indicated-vertical-speed", a});
    //16 does not apper in fly.txt
    a = new Var(0, -1, "/instrumentation/heading-indicator/indicated-heading-deg");
    varsMap->insert({"indicated", a});
    simMap->insert({"/instrumentation/heading-indicator/indicated-heading-deg", a});
    //17
    a = new Var(0, -1, "/instrumentation/magnetic-compass/indicated-heading-deg");
    varsMap->insert({"magnetic", a});
    simMap->insert({"/instrumentation/magnetic-compass/indicated-heading-deg", a});
    //18
    a = new Var(0, -1, "/instrumentation/slip-skid-ball/indicated-slip-skid");
    varsMap->insert({"slip", a});
    simMap->insert({"/instrumentation/slip-skid-ball/indicated-slip-skid", a});
    //19
    a = new Var(0, -1, "/instrumentation/turn-indicator/indicated-turn-rate");
    varsMap->insert({"turn", a});
    simMap->insert({"/instrumentation/turn-indicator/indicated-turn-rate", a});
    //20
    a = new Var(0, -1, "/instrumentation/vertical-speed-indicator/indicated-speed-fpm");
    varsMap->insert({"vertical", a});
    simMap->insert({"/instrumentation/vertical-speed-indicator/indicated-speed-fpm", a});
    //21 IS IN FLY.TXT
    a = new Var(0, -1, "/controls/flight/aileron");
    varsMap->insert({"aileron", a});
    simMap->insert({"/controls/flight/aileron", a});
    //22
    a = new Var(0, -1, "/controls/flight/elevator");
    varsMap->insert({"elevator", a});
    simMap->insert({"/controls/flight/elevator", a});
    //23 IS IN MAP
    a = new Var(0, -1, "/controls/flight/rudder");
    varsMap->insert({"rudder", a});
    simMap->insert({"/controls/flight/rudder", a});
    //24
    a = new Var(0, -1, "/controls/flight/flaps");
    varsMap->insert({"flight_flaps", a});
    simMap->insert({"/controls/flight/flaps", a});
    //25
    a = new Var(0, -1, "/controls/engines/engine/throttle");
    varsMap->insert({"engine_throttle", a});
    simMap->insert({"/controls/engines/engine/throttle", a});
    //26 is in map
    a = new Var(0, -1, "/controls/engines/current-engine/throttle");
    varsMap->insert({"throttle", a});
    simMap->insert({"/controls/engines/current-engine/throttle", a});
    //27 is in map
    a = new Var(0, -1, "/controls/switches/master-avionics");
    varsMap->insert({"masteravionics", a});
    simMap->insert({"/controls/switches/master-avionics", a});
    //28 is in map
    a = new Var(0, -1, "/controls/switches/starter");
    varsMap->insert({"starter", a});
    simMap->insert({"/controls/switches/starter", a});
    //29 is in map
    a = new Var(0, -1, "/engines/active-engine/auto-start");
    varsMap->insert({"autostart", a});
    simMap->insert({"/engines/active-engine/auto-start", a});
    //30 is in map
    a = new Var(0, -1, "/controls/flight/speedbrake");
    varsMap->insert({"breaks", a});
    simMap->insert({"/controls/flight/speedbrake", a});
    //31 is in map
    a = new Var(0, -1, "/sim/model/c172p/brake-parking");
    varsMap->insert({"brakeparking", a});
    simMap->insert({"/sim/model/c172p/brake-parking", a});
    //32 is in map
    a = new Var(0, -1, "/controls/engines/engine/primer");
    varsMap->insert({"primer", a});
    simMap->insert({"/controls/engines/engine/primer", a});
    //33  is in map
    a = new Var(0, -1, "/controls/engines/current-engine/mixture");
    varsMap->insert({"mixture", a});
    simMap->insert({"/controls/engines/current-engine/mixture", a});
    //34 is in map
    a = new Var(0, -1, "/controls/switches/master-bat");
    varsMap->insert({"masterbat", a});
    simMap->insert({"/controls/switches/master-bat", a});
    //35 is in map
    a = new Var(0, -1, "/controls/switches/master-alt");
    varsMap->insert({"masterlat", a});
    simMap->insert({"/controls/switches/master-alt", a});
    //36 is in map
    a = new Var(0, -1, "/engines/engine/rpm");
    varsMap->insert({"rpm", a});
    simMap->insert({"/engines/engine/rpm", a});


}


vector<string> lexer(char *filename) {
    vector<string> vector1;
    ifstream file;
    file.open(filename);
    int indexVector = 0;
    char c = file.get();
    string temp = "";
    int flag = 1;
    while (c != EOF) {
        if ((c == ' ' || c == '(' || c == ')' || c == ',') && flag) {
            vector1.insert(vector1.begin() + indexVector, temp);
            temp = "";
            indexVector++;
            flag = 0;
        } else if (c != '\n') {
            temp += c;
        } else {

            vector1.insert(vector1.begin() + indexVector, temp);
            temp = "";
            indexVector++;
            flag = 1;
        }
        c = file.get();
    }
    return vector1;
}


void parser(vector<string> lexered, map<string, Command *> hashMap, map<string, Var *> *varsMap,
            map<string, Var *> *simMap) {
    int index = 0;
    while (index < lexered.size()) {
        if (hashMap.count(lexered[index])) {
            Command *c = hashMap[lexered[index]];
            if (c != NULL) {
                index += c->execute(lexered, index, varsMap, simMap);
            }
        } else if (varsMap->count(lexered[index])) {
            Command *c = new AssignmentCommand();
            if (c != NULL) {
                index += c->execute(lexered, index, varsMap, simMap);
            }
        } else {
            ++index;
        }
    }
    isConnect = false;
}

map<string, Command *> initilize() {
    map<string, Command *> hash;
    Command *c = new DefineVarCommand();
    hash.insert({"var", c});
    c = new OpenServerCommand();
    hash.insert({"openDataServer", c});
    c = new ConnectCommand();
    hash.insert({"connectControlClient", c});
    c = new PrintCommand();
    hash.insert({"Print", c});
    c = new SleepCommand();
    hash.insert({"Sleep", c});
    c = new WhileCommand();
    hash.insert({"while", c});
    c = new IfCommand();
    hash.insert({"if", c});

    return hash;
}


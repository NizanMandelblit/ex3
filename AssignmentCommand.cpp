//
// Created by nizan on 19/12/2019.
//

#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include "AssignmentCommand.h"
#include "Interpreter.h"

AssignmentCommand::AssignmentCommand() {}

//excuting the Assignment Command
int AssignmentCommand::execute(vector<string> v, int index, map<string, Var *> *varsMap,__attribute__((unused)) map<string, Var *> *simMap) {
    string var = v[index + 1];
    var = var.substr(1, var.length());
    Interpreter *i1 = new Interpreter();
    Expression *ex = i1->interpret(var, varsMap);
    //checks if its a new var
    if (!varsMap->count(v[index])) {
        globalVarAssignment = new Var(-999, -1, "");
        varsMap->insert({v[index], globalVarAssignment});
    }
    Var *s = (*varsMap)[v[index]];
    s->setVal(ex->calculate());
    //checks if it needs to send the data to the simulator
    if (s->getDir() == 1) {
        string message = "set " + s->getPath() + " " + to_string(s->getVal()) + " \r\n";
        int is_sent = send((*varsMap)["client_sock"]->getDir(), message.c_str(), strlen(message.c_str()), 0);
        if (is_sent == -1) {
            std::cout << "Error sending message" << std::endl;
        }

    }
    delete i1;
    i1 = nullptr;
    return 2;
}

AssignmentCommand::~AssignmentCommand() {

}
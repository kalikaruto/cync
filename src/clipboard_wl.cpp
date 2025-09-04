/*
 * Copyright (c) 2025 git@kalikaruto. All Rights Reserved.
 */

#include "clipboard.h"
#include <cstdio> // for FILE, popen, pclose, fwrite
#include <string> // for std::string
#include <iostream>

using namespace std;

string Clipboard::get() {
    static const bool isavailable = commandExists("wl-paste");
    if (!isavailable) {
        cerr << "[Cync DEBUG] wl-paste command not found!" << endl;
        return "";
    }
    const char *cmd = "wl-paste -n"; // -n disables newline at end
    char buffer[4096];
    string result;
    FILE *pipe = popen(cmd, "r");
    if (!pipe)
        return "";

    while (fgets(buffer, sizeof(buffer), pipe)) {
        result += buffer;
    }
    
    int status = pclose(pipe);
    if (status != 0) {
        cerr << "[Cync DEBUG] wl-paste exited with error status: " << status << endl;
    }

    return result;
}

void Clipboard::set(const string &text) {
    static const bool isavailable = commandExists("wl-copy");
    if (!isavailable) {
        cerr << "[Cync DEBUG] wl-copy command not found!" << endl;
        return;
    }
    FILE *pipe = popen("wl-copy", "w");
    if (!pipe)
        return;
    fwrite(text.c_str(), sizeof(char), text.size(), pipe);
    fflush(pipe);
    
    int status = pclose(pipe);
    if (status != 0) {
        cerr << "[Cync DEBUG] wl-copy exited with error status: " << status << endl;
    }
}

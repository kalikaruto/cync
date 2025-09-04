/*
 * Copyright (c) 2025 git@kalikaruto. All Rights Reserved.
 */

#include "clipboard.h"
#include <cstdio> // for FILE, popen, pclose, fwrite
#include <string> // for std::string

using namespace std;

string Clipboard::get() {
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
        fprintf(stderr, "[Cync DEBUG] wl-paste exited with error status: %d\n", status);
    }

    return result;
}

void Clipboard::set(const string &text) {
    FILE *pipe = popen("wl-copy", "w");
    if (!pipe)
        return;
    fwrite(text.c_str(), sizeof(char), text.size(), pipe);
    fflush(pipe);
    
    int status = pclose(pipe);
    if (status != 0) {
        fprintf(stderr, "[Cync DEBUG] wl-copy exited with error status: %d\n", status);
    }
}
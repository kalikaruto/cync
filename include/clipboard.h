/*
 * Copyright (c) 2025 git@kalikaruto. All Rights Reserved.
 */

#pragma once
#include <string>

class Clipboard {
  public:
    static std::string get();
    static void set(const std::string &);
  private:
    inline static bool commandExists(const std::string &cmd) { 
        std::string checkCmd = "command -v " + cmd + " >/dev/null 2>&1";
        int result = system(checkCmd.c_str());
        return result == 0;
    }
};

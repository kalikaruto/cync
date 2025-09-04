/*
 * Copyright (c) 2025 git@kalikaruto. All Rights Reserved.
 */

#pragma once
#include <string>

class Clipboard {
  public:
    static std::string get();
    static void set(const std::string &);
};

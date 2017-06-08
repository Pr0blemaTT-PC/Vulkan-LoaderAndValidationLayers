/*
 * Copyright (c) 2017 The Khronos Group Inc.
 * Copyright (c) 2017 Valve Corporation
 * Copyright (c) 2017 LunarG, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Author: Lenny Komow <lenny@lunarg.com>
 */

// This code generates an assembly file which provides offsets to get struct members from assembly code.

#include <stdio.h>
#include "loader.h"

int main(int argc, char **argv) {
    const char *assembler = NULL;
    for (int i = 0; i < argc; ++i) {
        if (!strcmp(argv[i], "MASM")) {
            assembler = "MASM";
        }
    }
    if (assembler == NULL) {
        return 1;
    }

    struct loader_instance_dispatch_table disp;
    size_t offset = (size_t) ((size_t) &disp.phys_dev_ext) - ((size_t) &disp);

    FILE *file = fopen("gen_defines.asm", "w");
    if (!strcmp(assembler, "MASM")) {
        fprintf(file, "\nPHYS_DEV_DISP_OFFSET equ %lu\n", offset);
    }
    return fclose(file);
}

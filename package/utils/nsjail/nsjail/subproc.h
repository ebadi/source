/*

   nsjail - subprocess management
   -----------------------------------------

   Copyright 2014 Google Inc. All Rights Reserved.

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

*/

#ifndef NS_PROC_H
#define NS_PROC_H

#include <inttypes.h>
#include <stdbool.h>
#include <unistd.h>

#include "nsjail.h"

void subprocRunChild(struct nsjconf_t* nsjconf, int fd_in, int fd_out, int fd_err);
int subprocCount(struct nsjconf_t* nsjconf);
void subprocDisplay(struct nsjconf_t* nsjconf);
void subprocKillAll(struct nsjconf_t* nsjconf);
int subprocSystem(const char** argv, char** env);
pid_t subprocClone(uintptr_t flags);
void subprocCloneFlags(struct nsjconf_t* nsjconf);

/* Returns the exit code of the first failing subprocess, or 0 if none fail */
int subprocReap(struct nsjconf_t* nsjconf);

#endif /* NS_PROC_H */

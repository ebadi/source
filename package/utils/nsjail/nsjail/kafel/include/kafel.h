/*
   Kafel
   -----------------------------------------

   Copyright 2016 Google Inc. All Rights Reserved.

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

#ifndef KAFEL_H
#define KAFEL_H

#include <linux/filter.h>
#include <stdint.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct kafel_ctxt* kafel_ctxt_t;

/*
 * Creates and initializes a kafel context
 */
kafel_ctxt_t kafel_ctxt_create(void);

/*
 * Destroys kafel context pointed to by ctxt and releases related resources
 */
void kafel_ctxt_destroy(kafel_ctxt_t* ctxt);

/*
 * Sets input source for ctxt to file
 * Caller is responsible for closing the file stream after compilation
 */
void kafel_set_input_file(kafel_ctxt_t ctxt, FILE* file);

/*
 * Sets input source for ctxt to a NULL-terminated string
 */
void kafel_set_input_string(kafel_ctxt_t ctxt, const char* string);

/*
 * Sets compilation target architecture for ctxt to target_arch
 * target_arch must be a supported AUDIT_ARCH_* value (see <linux/audit.h>)
 */
void kafel_set_target_arch(kafel_ctxt_t ctxt, uint32_t target_arch);

/*
 * Compiles policy using ctxt as context.
 * Stores resulting code in prog.
 * Allocates memory for BPF code, caller is responsible freeing prog->filter
 *   once it does not need it. kafel_ctxt_destroy DOES NOT release this resource
 * Input source MUST be set first with kafel_set_input_string or
 *   kafel_set_input_file
 *
 * Returns 0 on success
 */
int kafel_compile(kafel_ctxt_t ctxt, struct sock_fprog* prog);

/*
 * Convenience function to compile a policy from a file
 * Does not preserve detailed error information
 * Same as for kafel_compile caller is repsonsible for freeing prog->filter
 * Caller is also responsible for closing the file stream
 *
 * Returns 0 on success
 */
int kafel_compile_file(FILE* file, struct sock_fprog* prog);

/*
 * Convenience function to compile a policy from a NULL-terminated string
 * Does not preserve detailed error information
 * Same as for kafel_compile caller is repsonsible for freeing prog->filter
 *
 * Returns 0 on success
 */
int kafel_compile_string(const char* source, struct sock_fprog* prog);

/*
 * Returns textual description of the error, if compilation using ctxt failed
 */
const char* kafel_error_msg(const kafel_ctxt_t ctxt);

#ifdef __cplusplus
}
#endif

#endif /* KAFEL_H */

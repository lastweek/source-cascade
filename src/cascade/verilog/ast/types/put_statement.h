// Copyright 2017-2019 VMware, Inc.
// SPDX-License-Identifier: BSD-2-Clause
//
// The BSD-2 license (the License) set forth below applies to all parts of the
// Cascade project.  You may not use this file except in compliance with the
// License.
//
// BSD-2 License
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice, this
// list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice,
// this list of conditions and the following disclaimer in the documentation
// and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS AS IS AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef CASCADE_SRC_VERILOG_AST_TYPES_PUT_STATEMENT_H
#define CASCADE_SRC_VERILOG_AST_TYPES_PUT_STATEMENT_H

#include "verilog/ast/types/expression.h"
#include "verilog/ast/types/macro.h"
#include "verilog/ast/types/string.h"
#include "verilog/ast/types/system_task_enable_statement.h"

namespace cascade {

class PutStatement : public SystemTaskEnableStatement {
  public:
    // Constructors:
    explicit PutStatement(Expression* fd__, String* fmt__);
    explicit PutStatement(Expression* fd__, String* fmt__, Expression* expr__);
    ~PutStatement() override;

    // Node Interface:
    NODE(PutStatement)
    PutStatement* clone() const override;

    // Put/Set:
    PTR_GET_SET(PutStatement, Expression, fd)
    PTR_GET_SET(PutStatement, String, fmt)
    MAYBE_GET_SET(PutStatement, Expression, expr)

  private:
    PTR_ATTR(Expression, fd);
    PTR_ATTR(String, fmt);
    MAYBE_ATTR(Expression, expr);
};

inline PutStatement::PutStatement(Expression* fd__, String* fmt__) : SystemTaskEnableStatement(Node::Tag::put_statement) {
  PTR_SETUP(fd);
  PTR_SETUP(fmt);
  MAYBE_DEFAULT_SETUP(expr);
  parent_ = nullptr;
}

inline PutStatement::PutStatement(Expression* fd__, String* fmt__, Expression* expr__) : PutStatement(fd__, fmt__) {
  MAYBE_SETUP(expr);
}

inline PutStatement::~PutStatement() {
  PTR_TEARDOWN(fd);
  PTR_TEARDOWN(fmt);
  MAYBE_TEARDOWN(expr);
}

inline PutStatement* PutStatement::clone() const {
  auto* res =  new PutStatement(fd_->clone(), fmt_->clone());
  MAYBE_CLONE(expr);
  return res;
}

} // namespace cascade 

#endif


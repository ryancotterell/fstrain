// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// Author: markus.dreyer@gmail.com (Markus Dreyer)
//
#ifndef FSTRAIN_CREATE_CREATE_ALIGNMENT_SYMBOLS_H
#define FSTRAIN_CREATE_CREATE_ALIGNMENT_SYMBOLS_H

#include "fst/symbol-table.h"
#include "fstrain/create/debug.h"
#include <sstream>
#include <string>

namespace fstrain { namespace create {

/**
 * @brief Creates all alignment symbols.
 */
void CreateAlignmentSymbols(const fst::SymbolTable& isymbols,
                            const fst::SymbolTable& osymbols,
                            const std::string start_symbol,
                            const std::string end_symbol,
                            fst::SymbolTable* result) {
  const std::string separator = "|";
  result->AddSymbol("eps");
  for (fst::SymbolTableIterator in_iter(isymbols); !in_iter.Done(); in_iter.Next()) {
    for (fst::SymbolTableIterator out_iter(osymbols); !out_iter.Done(); out_iter.Next()) {
      if ((in_iter.Value() == 0 && out_iter.Value() == 0)
         || (in_iter.Symbol() == start_symbol && out_iter.Symbol() != start_symbol)
         || (in_iter.Symbol() == end_symbol && out_iter.Symbol() != end_symbol)
         || (out_iter.Symbol() == start_symbol && in_iter.Symbol() != start_symbol)
         || (out_iter.Symbol() == end_symbol && in_iter.Symbol() != end_symbol)) {
        continue;
      }
      std::stringstream ss;
      std::string in = in_iter.Symbol();
      std::string out = out_iter.Symbol();
      if (in == "eps") {
        in = "-";
      }
      if (out == "eps") {
        out = "-";
      }
      ss << in << separator << out;
      result->AddSymbol(ss.str());
    }
  }
  FSTR_CREATE_DBG_EXEC(10, std::cerr << "Align syms:" << std::endl;
                       result->WriteText(std::cerr));
}

} } // end namespace

#endif

#include "CppSourceCode.hpp"

#include <string>

namespace cpmc {
    
    CppSourceCode::CppSourceCode() = default;
    CppSourceCode::CppSourceCode(const std::string& content): content(content) {}

    std::string CppSourceCode::getContent() const {
        return content;
    }
}

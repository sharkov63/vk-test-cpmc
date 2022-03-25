#ifndef CPMC_CPP_SOURCE_CODE_HPP_INCLUDED
#define CPMC_CPP_SOURCE_CODE_HPP_INCLUDED

#include <string>

namespace cpmc {
    /**
     * Represents a source code in C++ language.
     */
    class CppSourceCode {
        private:
            std::string content;

        public:
            CppSourceCode();
            CppSourceCode(const std::string& content);

            /**
             * Returns the source code as a string.
             */
            std::string getContent() const;
    };
}

#endif // CPMC_CPP_SOURCE_CODE_HPP_INCLUDED include guard

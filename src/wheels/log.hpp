#ifndef _LOG_HPP
#define _LOG_HPP

#include <string_view>
#include <fstream>

namespace wheels {

std::ofstream& Log();

namespace log {
void Init(std::string_view path);

void Close();
}


}

#endif /* ifndef _LOG_HPP */

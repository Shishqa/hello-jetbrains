/*============================================================================*/
#ifndef _WHEELS_ASSERT_HPP
#define _WHEELS_ASSERT_HPP
/*============================================================================*/
#ifndef NDEBUG
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#include <cstdlib>
#include <iostream>

#define PANIC(message)                                                    \
  {                                                                       \
    std::cerr << "Panicked at " << __FILE__ << ":" << __PRETTY_FUNCTION__ \
              << ":" << __LINE__ << "\n"                                  \
              << message << "\n";                                         \
    std::abort();                                                         \
  }

#define ASSERT(cond, error)                      \
  if (!(cond)) {                                 \
    PANIC("Assertion " #cond " failed: " error); \
  }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#else
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#define PANIC(message)
#define ASSERT(cond, error)

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#endif
/*============================================================================*/
#endif  // _WHEELS_ASSERT_HPP
/*============================================================================*/

#ifndef __TREE_ERR_H__
#define __TREE_ERR_H__

#include <assert.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

namespace terr {

  namespace internal {
    static std::string sep = " ";
  }

  template <typename T>
  void error(const T& s) {
    std::ostringstream os;
    os << s;
    throw std::runtime_error{os.str()};
  }

  template <typename T1, typename T2>
  void error(const T1& s, const T2& t) {
    std::ostringstream os;
    os << s << internal::sep << t;
    error(os.str());
  }

  template <typename T1, typename T2, typename... Tail>
  void error(const T1& f, const T2& s, const Tail&... rest) {
    std::ostringstream os;
    os << f << internal::sep << s;
    error(os.str(), rest...);
  }

  inline void set_separator(const std::string& s) { internal::sep = s; }

  inline void reset_separator() { internal::sep = " "; }

}

#ifdef GNU
#define t_error(...)                                                 \
  terr::internal::full_error(__FILE__, __LINE__, __PRETTY_FUNCTION__, \
                             __builtin_FUNCTION(),__VA_ARGS__)

#ifndef NDEBUG
#define t_assert(cond, ...)                                             \
  {                                                                       \
    if (!(cond))                                                          \
      terr::internal::full_error(__FILE__, __LINE__, __PRETTY_FUNCTION__, \
                                 __builtin_FUNCTION(),__VA_ARGS__);     \
  }
#else
#define t_assert(cond, ...)
#endif
#else
#define t_error(...)                                                 \
  terr::internal::full_error(__FILE__, __LINE__, __PRETTY_FUNCTION__, __VA_ARGS__)

#ifndef NDEBUG
#define t_assert(cond, ...)                                             \
  {                                                                       \
    if (!(cond))                                                          \
      terr::internal::full_error(__FILE__, __LINE__, __PRETTY_FUNCTION__,__VA_ARGS__);\
  }
#else
#define t_assert(cond, ...)
#endif
#endif

namespace terr {
  namespace internal {
#ifdef GNU
    template <typename T, typename... Tail>
    void full_error(const char* sfile,
                      const unsigned int& line,
                      const char* sfunc,
                    const char* caller,
                      const T& f,
                      const Tail&... rest) {
      std::ostringstream os;
      os << "\n\n"
         << "------------------------------------------------------------------"
            "---"
            "\n"
         << "A runtime exception has been thrown\n\n"
         << "   function: " << sfunc << '\n'
         << "  called by: " << caller << '\n'
         << "       file: " << sfile << '\n'
         << "       line: " << line << "\n\n"
         << "with the following output:\n\n"
         << f;
      error(os.str(), rest...);
    }
#else
    template <typename T, typename... Tail>
    void full_error(const char* sfile,
                      const unsigned int& line,
                      const char* sfunc,
                      const T& f,
                      const Tail&... rest) {
      std::ostringstream os;
      os << "\n\n"
         << "------------------------------------------------------------------"
            "---"
            "\n"
         << "A runtime exception has been thrown\n\n"
         << "   function: " << sfunc << '\n'
         << "       file: " << sfile << '\n'
         << "       line: " << line << "\n\n"
         << "with the following output:\n\n"
         << f;
      error(os.str(), rest...);
    }
#endif
  }
}
#endif

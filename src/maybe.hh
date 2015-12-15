#ifndef MAYBE_HH
#define MAYBE_HH

template<typename T>
struct Maybe {
  T data;
  bool valid;
};

#endif // ! MAYBE_HH

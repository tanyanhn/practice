#include "std.h"

template<typename T>
class Danger;
template<>
class Danger<void> {
 public:
  enum { max = 100 };
};
void clear(char* buf)
{
  cout <<Danger<void>::max << '\n';
// mismatch in array bound:
for (int k = 0; k<Danger<void> ::max; ++k) {
buf[k] = '\0';
}
}
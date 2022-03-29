#include "std.h"

template<typename T>
class Danger {
public:
enum { max = 10 };
};
char buffer[Danger<void> ::max];
extern void clear(char*);

int main() {
  cout <<Danger<void>::max << '\n';
clear(buffer);
}
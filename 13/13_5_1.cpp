class No_copy {
  No_copy(const No_copy&) = delete;
};

class My_error {

};

void f(int n) {
  switch (n) {
  case 0: throw My_error{};
  case 1: throw No_copy{}; // error
  case 2: throw My_error; // error
  }
}
//
//  实现继承
//
//
//
//


class Ival_box {
protected:
  int val;
  int low, high;
  bool changed{false};
public:
  Ival_box(int II, int hh):val{II}, low{II}, high(hh) {}

  virtual int get_value() {changed=false; return val;}  //  供应用程序使用
  virtual void set_value(int i) {changed=true;val=i;} //  供用户使用
  virtual void reset_value(int i) {changed=false;val=i;}  //  供应用程序使用
  virtual void prompt() {}  //  警示用户
  virtual bool was_changed() const {return changed;}

  virtual ~Ival_box() {}
};

class Ival_slider : public Ival_box {
private:

public:
  Ival_slider(int, int);
  int get_value() override;
  void prompt() override;
};


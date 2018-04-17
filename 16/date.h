#ifndef DATE_H_
#define DATE_H_

namespace Chrono {

  enum class Month {jan=1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec};

  class Date {
  public:
    class Bad_date{};

    explicit Date(int dd={}, Month mm={}, int yy={});

    int day() const;
    Month month() const;
    int year() const;

    std::string string_rep() const;
    void char_rep(char s[], int max) const;

    Date& add_year(int n);
    Date& add_month(int n);
    Date& add_day(int n);
  private:
    bool is_valid();
    int d, m, y;
  };

  bool is_date(int d, Month m, int y);
  bool is_leapyear(int y);

  bool operator==(const Date& a, const Date& b);
  bool operator!=(const Date& a, const Date& b);

  const Date& default_date();

  std::ostream& operator<<(std::ostream& os, const Date& d);
  std::istream& operator>>(std::istream& os, Date& d);

} // Chrono

#endif  // DATE_H_
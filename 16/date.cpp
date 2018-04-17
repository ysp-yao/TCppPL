#include "date.h"

using namespace Chrono;

Date::Date(int dd, Month mm, int yy)
  :d{dd}, m{mm}, y{yy}
{
  if (y == 0) y = default_date().year(); 
  if (m == Month{}) m = default_date().month(); 
  if (d == 0) d = default_date().day();

  if (!is_valid()) throw Bad_date(); 
}

bool Date::is_valid()
{
  return is_date(d, m, y);
}

inline int Date::day() const
{
  return d;
}

Date& Date::add_month(int n)
{

}

bool is_date(int d, Month m, int y) 
{

}

const Date& default_date() {
  static Date d{1, Month::jan, 1970};
  return d;
}
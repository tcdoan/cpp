#include <iostream>

using namespace std;

// Class days extends int8_t type;
enum class days : std::int8_t
{
  SUN, MON, TUE, WED, THU, FRI, SAT
};
  
days operator++(days& d)
{
  d = static_cast<days>((static_cast<int>(d) + 1) % 7);
  return d;
}

days operator++(days& d, int)
{
  days temp = d;
  d = static_cast<days>((static_cast<int>(d) + 1) % 7);
  return temp;
}

ostream& operator<<(ostream& out, const days& d)
{
  switch(d)
    {
    case days::SUN:
      out << "Sunday";
      break;
    case days::MON:
      out << "Monday";
      break;
    case days::TUE:
      out << "Tuesday";
      break;
    case days::WED:
      out << "Wednesday";
      break;
    case days::THU:
      out << "Thursday";
      break;
    case days::FRI:
      out << "Friday";
      break;
    case days::SAT:
      out << "Saturday";
      break;
    }
}

int main(void)
{
  days d = days::TUE;
  ++d;
  days d2 = d++;
  cout << "days = " << d << endl;
  cout << "d2 = " << d2 << endl;
}

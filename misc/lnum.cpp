#include "Matrix++.hpp"

// vypis dlouheho cisla
ostream & operator<<(ostream & out, const LNum & num) {
  for (int i = num.get_size(); i > 0; i--) {
    out << num[i-1];
  }
  return out;
}

// konkatenace 2 dlouhych cisel x&y je v lidske reci zapis xy
LNum operator&(const LNum & x, const LNum & y) {
  LNum ret(x.get_size()+y.get_size());

  // zapis "y" zprava doleva
  for (int i = 0; i < y.get_size(); i++) {
    ret[i] = y[i];
  }

  // zapis "x" zprava doleva
  int shift = y.get_size();
  for (int j = 0; j < x.get_size(); j++) {
    ret[j+shift] = x[j];
  }

  return ret;
}

// pridani "m" nul zprava
LNum shift_left(const LNum & x, int m) {
  LNum zeros(m);
  return (x & zeros);
}

// pridani "m" nul zleva
LNum shift_right(const LNum & x, int m) {
  LNum zeros(m);
  return (zeros & x);
}

// pridani "m" nul zleva (od prvni nenulove cifry dolevy)
LNum shift_right_enhanced(const LNum & x, int m) {
  int leftest_one = -1;
  for (int i = 0; i < x.get_size(); i++) {
    if (x[i] == 1) {
      leftest_one = i;
    }
  }

  LNum ret(leftest_one + 1 + m);
  for (int i = 0; i <= leftest_one; i++) {
    ret[i] = x[i];
  }
  return ret;
}

// rozdil 2 dlouhych cisel (x-y) s #cifer rovnym #cifer mensence
LNum operator-(const LNum & x, const LNum & y) {
  LNum ret(x.get_size());
  LNum y2 = shift_right(y, x.get_size() - y.get_size());

  // prictu dvojkovy doplnek
  bool carry = 1;
  for (int i = 0; i < x.get_size(); i++) {
    ret[i] = (x[i] ^ !y2[i]) ^ carry;
    carry = (x[i] && !y2[i]) || (x[i] && carry) || (!y2[i] && carry);
  }

  return ret;
}

// soucet 2 dlouhych cisel
LNum operator+(const LNum & x, const LNum & y) {
  LNum longer = (x.get_size() > y.get_size()) ? x : y;
  LNum shorter = (x.get_size() > y.get_size()) ? y : x;

  // doplneni kratsiho zprava "0", aby byly obe cisla stejne dlouha
  shorter = shift_right(shorter, longer.get_size() - shorter.get_size());

  LNum ret(longer.get_size());

  bool carry = 0;
  for (int i = 0; i < longer.get_size(); i++) {
    ret[i] = (longer[i] ^ shorter[i]) ^ carry;
    carry = (longer[i] && shorter[i]) || (longer[i] && carry) || (shorter[i] && carry);
  }

  // posledni prenos -> pridam dalsi cifru k vysledku
  if (carry) {
    ret = shift_right(ret, 1);
    ret[ret.get_size()-1] = 1;
  }

  return ret;
}

// vyrez dlouheho cisla x ... pozice od start do end vcetne (od nizsich k
// vyssim radum)
LNum cut(const LNum & x, int start, int end) {
  LNum ret(end-start+1);

  // kopirovani do vyrezu
  for (int i = start; i <= end; i++) {
    ret[i-start] = (i < x.get_size()) ? x[i] : 0;
  }

  return ret;
}

// pricteni hodnoty y
LNum & LNum::operator+=(const LNum & y) {
  *this = *this + y;
  return *this;
}

// soucin 2 dlouhych cisel (Karatsubuv algoritmus)
// viz http://en.wikipedia.org/wiki/Karatsuba_algorithm#The_basic_step
LNum operator*(const LNum & a, const LNum & b) {
  // delsi z n-cif. cisel
  int n = b.get_size();
  LNum x(a);
  LNum y(b);
  if (a.get_size() > b.get_size()) {
    n = a.get_size();

    LNum oh(1);
    oh[0] = 0;
    y = oh & b;
  } else if (x.get_size() < y.get_size()) {
    LNum oh(1);
    oh[0] = 0;
    x = oh & a;
  }

  int m = n/2;

  if (n == 1) {                 // trivial cases
    LNum ret(1);
    ret[0] = (x[0] & y[0]);
    return ret;
  } else {                      // Karatsuba algorithm
    LNum x1 = cut(x, m, n-1);
    LNum x0 = cut(x, 0, m-1);

    LNum y1 = cut(y, m, n-1);
    LNum y0 = cut(y, 0, m-1);

    LNum z2 = x1 * y1;
    LNum z0 = x0 * y0;
    LNum tmp_sum = (x1+x0) * (y1+y0);
    LNum z1 = (tmp_sum - z2) - z0;

    return (shift_left(z2, 2*m) + shift_left(z1, m) + z0);
  }
}

// preorder zvetseni o 1
LNum & LNum::operator++() {
  LNum one(this->size_);
  one[0] = 1;
  return (*this += one);
}

// odebrani nul ze zacatku cisla
void to_normal_form(LNum & a) {
  int leftest_one = 0;
  for (int i = a.get_size()-1; i > 0; i--) {
    if (a[i] == 1) {
      leftest_one = i;
      break;
    }
  }
  a = cut(a, 0, leftest_one);
}

// porovnani 2 dlouhych cisel: a<b ?
// nejprve dle #cifer; pak po cifrach od nejvyssi k nejnizsi mocnine
bool operator<(const LNum & num1, const LNum & num2) {
  // zbavime se "0" na zacatku
  LNum a = num1; to_normal_form(a);
  LNum b = num2; to_normal_form(b);

  if (a.get_size() < b.get_size()) {          // ruzne pocty cifer
    return true;
  } else if (a.get_size() > b.get_size()) {
    return false;
  } else {                                    // porovnavani po cifrach
    for (int i = a.get_size()-1; i >= 0; i--) {
      // i-ta cifra "a" mensi nez i-ta cifra "b": 0 < 1
      if (a[i] < b[i]) {
        return true;
      }
      // i-ta cifra "a" vetsi nez i-ta cifra "b": 1 > 0
      else if (a[i] > b[i]) {
        return false;
      }
    }
  }

  return false;                                // v tuhle chvili uz je a == b
}

// celociselne deleni 2 dlouhych cisel (stredoskolsky algoritmus)
// -- viz http://courses.cs.vt.edu/~cs1104/BuildingBlocks/divide.030.html
LNum operator/(LNum & dividend, LNum & divisor) {
  LNum quotient(1);
  quotient[0] = 0;
  to_normal_form(dividend);
  to_normal_form(divisor);

  // deleni nulou !!
  if (divisor.get_size() == 1 && divisor[0] == 0) {
    cout << "Division by zero!! Returning \"0\"!" << endl;
    return quotient;
  }

  // deleni mensiho cisla vetsim -> podil == 0
  if (dividend < divisor) {
    LNum oh(1);
    return oh;
  }

  // zarovnej delitel do leveho rohu delence
  int lock = dividend.get_size() - divisor.get_size();  // zarazka zpracovavane
                                                        // cifry v dividendu
  LNum portion = cut(dividend, lock, dividend.get_size()-1);

  do {
    if (!(portion<divisor)) {
      portion = portion - divisor;
      quotient.append(1);
    } else {
      quotient.append(0);
    }
    if (--lock >= 0) {
      portion.append(dividend[lock]);
    }
  } while (lock >= 0);

  to_normal_form(quotient);

  return quotient;
}

// moduleni 2 dlouhych cisel (opet vyuzivajici stredoskolsky algoritmus)
LNum operator%(LNum & dividend, LNum & divisor) {
  LNum quotient = dividend/divisor;
  LNum multiple = quotient*divisor;
  to_normal_form(multiple);
  LNum result = dividend-multiple;
  to_normal_form(result);
  return result;
}

// mocneni modulo: (base^exp) % mod
// Montgomery's ladder technique s prubeznym modulenim
// http://en.wikipedia.org/wiki/Exponentiation_by_squaring#Montgomery.27s_ladder_technique
// x = base
// n = exp, n_i = exp[i]
LNum pow_mod(LNum & base, LNum & exp, LNum & mod) {
  LNum result(mod.get_size());
  result[0] = 1;
  LNum power = base;

  int ord = 1;
  for (int i = 0; i < exp.get_size(); i++) {
    if (exp[i] == 1) {
      result = result * power;
      result = result % mod;
    }

    power = power*power;
    ord *= 2;
    power = power % mod;
  }

  return result;
}

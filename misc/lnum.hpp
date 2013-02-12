#ifndef _LNUM_H
#define _LNUM_H 1

// trida reprezentujici dlouha cisla
class LNum {
  std::deque<bool> digits_;         // kontejner s cislicemi, prvni cislice ma nejnizsi rad
  int size_;                        // #cislic
public:
  // konstruktor
  LNum(int size=32) : size_(size) {
    digits_.resize(size, 0);
  }

  // vrat #cislic
  int get_size() const {
    return size_;
  }

  // pristup k (idx)-te cislici (i zapis)
  bool & operator[](int idx) {
    return digits_[idx];
  }

  // pristup k (idx)-te cislici (jen cteni)
  bool operator[](int idx) const {
    return digits_[idx];
  }

  // prirazeni
  LNum & operator=(const LNum & x) {
    size_ = x.get_size();
    digits_.resize(size_, 0);
    for (int i = 0; i < size_ && i < x.get_size(); i++) {
      digits_[i] = x[i];
    }
  }

  // copy-constructor
  LNum(const LNum & x) {
    *this = x;
  }

  // zvetseni o hodnotu n2
  LNum & operator+=(const LNum & y);

  // preorder zvetseni o 1
  LNum & operator++();
  
  // POMOCNE OPERACE PRO DELENI & MODULO
  // konkatenace zprava o cifru "0"
  void append(int bit) {
    digits_.push_front(bit);
    size_++;
  }

  ~LNum() {
    digits_.clear();
  }
};

// vypis dlouheho cisla
std::ostream & operator<<(std::ostream & out, const LNum & num);

// konkatenace 2 dlouhych cisel x&y je v lidske reci zapis xy
LNum operator&(const LNum & x, const LNum & y);

// pridani "m" nul zprava
LNum shift_left(const LNum & x, int m);

// pridani "m" nul zleva
LNum shift_right(const LNum & x, int m);

// pridani "m" nul zleva (od prvni nenulove cifry dolevy)
LNum shift_right_enhanced(const LNum & x, int m);

// rozdil 2 dlouhych cisel (x-y) s #cifer rovnym #cifer mensence
LNum operator-(const LNum & x, const LNum & y);

// soucet 2 dlouhych cisel
LNum operator+(const LNum & x, const LNum & y);

// vyrez dlouheho cisla x ... pozice od start do end vcetne (od nizsich k
// vyssim radum)
LNum cut(const LNum & x, int start, int end);

// soucin 2 dlouhych cisel (Karatsubuv algoritmus)
// viz http://en.wikipedia.org/wiki/Karatsuba_algorithm#The_basic_step
LNum operator*(const LNum & a, const LNum & b);

// odebrani nul ze zacatku cisla
void to_normal_form(LNum & a);

// porovnani 2 dlouhych cisel: a<b ?
// nejprve dle #cifer; pak po cifrach od nejvyssi k nejnizsi mocnine
bool operator<(const LNum & num1, const LNum & num2);

// celociselne deleni 2 dlouhych cisel (stredoskolsky algoritmus)
// -- viz http://courses.cs.vt.edu/~cs1104/BuildingBlocks/divide.030.html
LNum operator/(LNum & dividend, LNum & divisor);

// moduleni 2 dlouhych cisel (opet vyuzivajici stredoskolsky algoritmus)
LNum operator%(LNum & dividend, LNum & divisor);

// mocneni modulo: (base^exp) % mod
// Montgomery's ladder technique s prubeznym modulenim
// http://en.wikipedia.org/wiki/Exponentiation_by_squaring#Montgomery.27s_ladder_technique
// x = base
// n = exp, n_i = exp[i]
LNum pow_mod(LNum & base, LNum & exp, LNum & mod);

#endif

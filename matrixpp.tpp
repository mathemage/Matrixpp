/******************************************************************************
      Copyright (C) 2013 Karel Ha <mathemage@gmail.com>

 Distributed under the terms of the GNU General Public License (GPL)
 as published by the Free Software Foundation; either version 2 of
 the License, or (at your option) any later version.
                 http://www.gnu.org/licenses/
******************************************************************************/
/* IMPLEMENTATION FILE */
namespace mtrx {
  // ==================================TELESA====================================================
  template<typename T>
  T Field<T>::_rec(const T & rhs) const {             // s kontrolou na nenulovost
    try {
      if (_zero == rhs) {
        throw InverseOfNullException();
      } else {
        return _reciprocal(rhs);
      }
    }
    catch (exception & e) {
      display_exception(e);
    }
  }
  // =================================/TELESA====================================================

  // ==================================PREDDEFINOVANA TELESA=====================================
  // TELESO REALNYCH CISEL
  double minus_double(const double & rhs) { return - rhs; }
  double reciprocal_double(const double & rhs) { return 1 / rhs; }
  double plus_double(const double & lhs, const double & rhs) { return lhs + rhs; }
  double times_double(const double & lhs, const double & rhs) { return lhs * rhs; }
  bool equals_double(const double & lhs, const double & rhs) { return lhs == rhs; }
  Field<double> fld_reals(0, 1, minus_double, reciprocal_double,  plus_double,
      times_double, equals_double);

  // PRVOTELESO
  // vysledek modula mezi hodnotami prvotelesa
  int mod(const int & value, int modulo) { return (value % modulo + modulo) % modulo; }
  template<int Order> int minus_pf(const int & rhs) { return mod(-rhs, Order); }

  template<int Order>
  int reciprocal_pf(const int & rhs) {     // rozsireny Eukliduv algoritmus s Bezoutovy koeficienty
    int divisor = mod(rhs, Order);
    if (0 == divisor) {
      throw InverseOfNullException();
    }
    int dividend = Order;
    int remainder;
    int bezout1 = 0; int bezout2 = 1;      // predposledni a posledni Bezoutuv koeficient

    while (divisor > 1) {
      bezout1 = bezout1 - (dividend / divisor) * bezout2;
      std::swap(bezout1, bezout2);
      remainder = dividend % divisor;
      dividend = divisor;
      divisor = remainder;
    }
    return mod(bezout2, Order);
  }

  template<int Order>
  int plus_pf(const int & lhs, const int & rhs) {
    return mod(mod(lhs,Order)+mod(rhs,Order), Order);
  }

  template<int Order>
  int times_pf(const int & lhs, const int & rhs) {
    return mod(mod(lhs,Order)*mod(rhs,Order), Order);
  }

  template<int Order>
  bool equals_pf(const int & lhs, const int & rhs) {
    return (lhs - rhs) % Order == 0;
  }

  // teleso zbytkovych trid radu "_order_"
  const int _order_ = 5;
  Field<int> pf(0, 1, minus_pf<_order_>, reciprocal_pf<_order_>,
      plus_pf<_order_>, times_pf<_order_>, equals_pf<_order_>);
  // =================================/PREDDEFINOVANA TELESA=====================================

  // ==================================OBECNA MATICE=============================================
  // defaultni konstruktor "Matrix" - zabaleni dat do objektu tridy
  template<typename T>
  Matrix<T>::Matrix(const Field<T> & fld=fld_reals, unsigned h=0, unsigned w=0, T * values=0) :
    _fld(&fld), _height(h), _width(w), _values(values) {
    // kontrola pro potomky
    try {
      if (!is_valid()) {                         // polymorfni is_valid()
        throw;
      }
    }
    catch (exception & e) {
      display_exception(e);
    }
  } 

  // rovnost matic
  template<typename T>
  bool Matrix<T>::operator==(const Matrix<T> & rhs) const {
    if (_height == rhs.get_height() && _width == rhs.get_width() && _fld == rhs._fld) {
      typename Matrix<T>::const_iterator it_r = rhs.cbegin();
      for (typename Matrix<T>::const_iterator it_m = cbegin(); it_m != cend(); it_m++, it_r++) {
        if (!_fld->_equals(*it_r, *it_m)) {
          return false;
        }
      }
      return true;
    } else {
      return false;
    }
  }

  // prohozeni dvou matic
  template<typename T>
  void Matrix<T>::swap(Matrix<T> & rhs) {
    try {
      if (this->_fld == rhs._fld) {
        std::swap(this->_height, rhs._height);
        std::swap(this->_width, rhs._width);
        std::swap(this->_values, rhs._values);
      } else {
        throw MismatchedFieldException();
      }
    }
    catch (exception & e) {
      display_exception(e);
    }
  }

  // vypis matice
  template<typename T>
  ostream & operator<<(ostream & out, const Matrix<T> & m) {
    int i = 0;                                   // pocitadlo pro odradkovani
    for (typename Matrix<T>::const_iterator it_m = m.begin(); it_m != m.end(); it_m++) {
      out << *it_m;
      // tabelator / novy radek
      if (0 == ++i % m.get_width() && i != m.get_width() * m.get_height()) {
        out << endl;
      } else {
        out << "\t";
      }
    }
    return out;
  }
  
  // zadavani polozek matice zvnejsku
  template<typename T>
  istream & operator>>(istream & in, Matrix<T> & m) {
    // rozmery
    // ??? vyjimka pro kontrolu ???
    in >> m._height >> m._width;

    // polozky
    if (0 != m._values) {
      delete [] m._values;
    }
    m._values = new T [m._height*m._width];
    for (typename Matrix<T>::iterator it_m = m.begin(); it_m != m.end(); it_m++) {
      in >> *it_m;
    }

    // kontrola pro potomky
    try {
      if (m.is_valid()) {                         // polymorfni is_valid()
        return in;
      }
    }
    catch (exception & e) {
      display_exception(e);
    }
  }

  template<typename T>
  Matrix<T> & Matrix<T>::operator=(const Matrix<T> & m) {      // prirazeni
    try {
      if (this != &m) {
        if (_fld != m._fld) {                                  // povoleno jen nad identickym telesem
          throw MismatchedFieldException();
        }
        _height = m.get_height();
        _width = m.get_width();

        // puvodni values
        if (0 != _values) {
          delete [] _values;
        }
        _values = new T [_height*_width];

        iterator it = this->begin();
        for (const_iterator it_m = m.begin(); it_m != m.end(); it_m++, it++) {
          *it = *it_m;
        }
      }
      return *this;
    }
    catch (exception & e) {
      display_exception(e);
    }
  }

  template<typename T>
  Matrix<T> Matrix<T>::mul_by_scal(const T & scalar) const {          // nasobeni skalarem
    Matrix<T> res(*this);
    for (iterator it = res.begin(); it != res.end(); it++) {
      *it = _fld->_times(*it, scalar);
    }
    return res;
  }

  template<typename T>
  Matrix<T> Matrix<T>::transpose() const {                            // transposice matice
    Matrix<T> res(*_fld, _width, _height);
    res._values = new T [_width*_height];
    for (int i = 0; i < _height; i++) {
      for (int j = 0; j < _width; j++) {
        res._values[j*_height+i] = at(i,j);
      }
    }
    return res;
  }

  // souvisla podmatice
  template<typename T>
  Matrix<T> Matrix<T>::subblock(unsigned u, unsigned l, unsigned d, unsigned r) const {
    try {
      if (u < 0 || u >= _height ||
                 l < 0 || l >= _width ||
                 d < 0 || d >= _height ||
                 r < 0 || r >= _width) {
        throw OutOfRangeException();
      } else if (u > d || l > r) {
        throw MismatchedDimException();
      }

      unsigned w = r-l+1;
      unsigned h = d-u+1;
      Matrix<T> res(*_fld, h, w);
      res._values = new T [h*w];
      int idx = 0;
      for (int x = u; x <= d; x++) {
        for (int y = l; y <= r; y++) {
          res._values[idx++] = at(x,y);
        }
      }
      return res;
    }
    catch (exception & e) {
      display_exception(e);
    }
  }

  template<typename T>
  Matrix<T> operator+(const Matrix<T> & x, const Matrix<T> & y) {
    try {
      if (x.get_height() != y.get_height() || x.get_width() != y.get_width()) {
        throw MismatchedDimException();
      } else if (x._fld != y._fld) {
        throw MismatchedFieldException();
      }

      Matrix<T> res(x);
      typename Matrix<T>::const_iterator ity = y.cbegin();
      for (typename Matrix<T>::iterator itx = res.begin(); itx != res.end(); itx++, ity++) {
        *itx = res._fld->_plus(*itx, *ity);
      }
      return res;
    }
    catch (exception & e) {
      display_exception(e);
    }
  }

  template<typename T>
  Matrix<T> operator-(const Matrix<T> & x, const Matrix<T> & y) {
    const T minus_one = y._fld->_minus(y._fld->_one);
    return x + y.mul_by_scal(minus_one);
  }

  template<typename T>
  Matrix<T> operator*(const Matrix<T> & x, const Matrix<T> & y) {
    int x_h = x.get_height();
    int y_w = y.get_width();

    //cout << "[1]:\n" << x << endl;
    //cout << "[2]:\n" << y << endl;
    try {
      if (y.get_height() != x.get_width()) {
        throw MismatchedDimException();
      } else if (x._fld != y._fld) {
        throw MismatchedFieldException();
      }

      T * data = new T [x_h*y_w];
      Matrix<T> res(*x._fld, x_h, y_w, data);
      typename Matrix<T>::iterator it = res.begin(); 
      for (int i = 0; i < x_h; i++) {
        for (int j = 0; j < y_w; j++, it++) {
          *it = res._fld->_zero;
          for (int k = 0; k < x.get_width(); k++) {
            *it = res._fld->_plus(*it, res._fld->_times(x.at(i, k), y.at(k, j)));
          }
        }
      }
      return res;
    }
    catch (exception & e) {
      display_exception(e);
    }
  }
  
  // zaokrouhleni cisel blizkych nule - implementovano pro double
  template<>
  Matrix<double> Matrix<double>::round_to_zeroes() const {
    Matrix<double> res(*this);
    for (typename Matrix<double>::iterator it = res.begin(); it != res.end();
        it++) {
      if (fabs(*it) < epsilon) {
        *it = 0;
      }
    }
    return res;
  }
  // =================================/OBECNA MATICE=============================================
  
  // ==================================VEKTORY===================================================
  // defaultni konstruktor "Vect" - implicitni sirka 1
  template<typename T>
  Vect<T>::Vect(const Field<T> & fld=fld_reals, unsigned h=0, T * values=0) :
    Matrix<T>(fld, h, 1, values) { } 

  template<typename T>
  Vect<T> & Vect<T>::operator=(const Vect<T> & v) {      // prirazeni
    Matrix<T>::operator=(v);                             // spravne dealokace - viz metoda predka
    return *this;
  }

  template<typename T>
  Vect<T>::Vect(const Matrix<T> & m) {                   // conversion constructor
    try {
      _width = m.get_width();
      if (1 == _width) {
        _height = m.get_height();
        _values = new T [_height];
        int i = 0;
        for (typename Matrix<T>::const_iterator it_m = m.cbegin(); it_m != m.cend();
            it_m++) {
          _values[i++] = *it_m;
        }
      } else {
        throw NotAVectorException();
      }
    }
    catch (exception & e) {
      display_exception(e);
    }
  }
  // =================================/VEKTORY===================================================
  
  // ==================================CTVERCOVE MATICE==========================================
  // defaultni konstruktor "SqrMtrx" - implicitne stejne rozmery
  template<typename T>
  SqrMtrx<T>::SqrMtrx(const Field<T> & fld=fld_reals, unsigned dim=0, T * values=0) :
    Matrix<T>(fld, dim, dim, values) { } 

  template<typename T>
  SqrMtrx<T> & SqrMtrx<T>::operator=(const SqrMtrx<T> & sq) {
    Matrix<T>::operator=(sq);                            // dealokace puv. dat - viz metoda predka
    return *this;
  }

  template<typename T>
  SqrMtrx<T>::SqrMtrx(const Matrix<T> & m) {             // conversion constructor
    try {
      _height = m.get_height();
      _width = m.get_width();
      if (_height == _width) {
        _values = new T [_height*_width];
        int i = 0;
        for (typename Matrix<T>::const_iterator it_m = m.cbegin(); it_m != m.cend();
            it_m++) {
          _values[i++] = *it_m;
        }
      } else {
        throw NotASqrMtrxException();
      }
    }
    catch (exception & e) {
      display_exception(e);
    }
  }
  // =================================/CTVERCOVE MATICE==========================================
  
  // ==================================PRO QR-ROZKLAD============================================
  template<typename T>
  SqrMtrx<T> unit_matrix(unsigned dim, const Field<T> & fld=fld_reals) {  // 1kova matice
    T * values = new T [dim * dim];
    for (int i = 0; i < dim; i++) {
      for (int j = 0; j < dim; j++) {
        values[i*dim + j] = (i == j) ? fld._one : fld._zero;
      }
    }
    return SqrMtrx<T>(fld, dim, values);
  }

  template<>
  Vect<double> Vect<double>::e1_reflection() {    // "norma" nasobek vektoru e_1
    double * can_val = new double [_height];
    can_val[0] = sqrt(norm_squared());
    for (int i = 1; i < _height; i++) {
      can_val[i] = _fld->_zero;
    }
    Vect<double> res(*_fld, _height, can_val);
    return res;
  }

  template<typename T>
  SqrMtrx<T> Vect<T>::Householder() {             // matice Housholderovy reflexe
    const Field<T> & fld = *_fld;

    SqrMtrx<T> res(unit_matrix(_height, fld));

    T norm = norm_squared();
    T denominator = fld._rec(norm);
    T two = fld._plus(fld._one, fld._one);
    SqrMtrx<T> minuend(outer_product());

    minuend = minuend.mul_by_scal(two);
    minuend = minuend.mul_by_scal(denominator);
    res = res - minuend;
    return res;
  }
  // Housholderova reflexe do nasobku vektoru e_1 (verse pro double)
  template<>
  SqrMtrx<double> Vect<double>::Householder_canon() {       
    double norm = sqrt(norm_squared());
    
    // "norma"-nasobek vektoru e_1
    Vect<> canonic = e1_reflection();

    if (*this == canonic) {
      return unit_matrix(_height, *_fld);
    } else {
      Vect<double> diff = *this - canonic;
      return diff.Householder();
    }

    SqrMtrx<> res;
    return res;
  }
  template<typename T>
  void Matrix<T>::QR(SqrMtrx<T> & Q, Matrix<T> & R) const {              // QR dekomposice
    Vect<T> col1(this->column(0));         // 1. sloupec
    if (1 == _width) {                     // konec rekurse
      Q = col1.Householder_canon().transpose();
      R = col1.e1_reflection();
    } else if (1 == _height) {             // konec rekurse: 1diny radek
      // prostor pro vylepseni: obecna nezapornost
      T coeff = (at(0,0) >= _fld->_zero) ? _fld->_one : _fld->_minus(_fld->_one);
      T * Q_val = new T [1];
      Q_val[0] = coeff;
      Q = SqrMtrx<T>(*_fld, 1, Q_val);
      R = mul_by_scal(coeff);
    } else {
      /*
       __________________________
       | alpha |       b^T       |
       --------------------------
       |   0   |                 |
       |   .   |                 |
       |   .   |        B        |  ==  H * (*this) =: (oznacme "tmp")
       |   .   |                 |
       |   0   |                 |
       __________________________
       */
      Matrix<T> B = (col1.Householder_canon() * (*this)).subblock(1, 1, _height-1, _width-1);

      // rekursivne QR na B
      SqrMtrx<T> Q2;
      Matrix<T> R2;
      B.QR(Q2, R2);

      // sestaveni R z R2
      Matrix<T> tmp = col1.Householder_canon() * (*this);
      T * R_val = new T [_height*_width];
      unsigned idx = 0;
      for (int i = 0; i < _width; i++) {                // 1. radek
        R_val[idx++] = tmp.at(0,i);
      }
      for (int i = 1; i < _height; i++) {               // dalsi radky
        R_val[idx++] = _fld->_zero;
        for (int j = 1; j < _width; j++) {
          R_val[idx++] = R2.at(i-1,j-1);
        }
      }
      R = Matrix<T>(*_fld, _height, _width, R_val);
      
      // sestaveni Q z Q2
      T * Q_val = new T [_height*_height];
      idx = 0;
      for (int i = 0; i < _height; i++) {                // 1. radek
        Q_val[idx++] = (i == 0) ? _fld->_one :_fld->_zero;
      }
      for (int i = 1; i < _height; i++) {                // dalsi radky
        Q_val[idx++] = _fld->_zero;
        for (int j = 1; j < _height; j++) {
          Q_val[idx++] = Q2.at(i-1,j-1);
        }
      }
      SqrMtrx<T> newQ(*_fld, _height, Q_val);
      Q = col1.Householder_canon().transpose() * newQ;
    }
  }

  // QR algoritmus pro zadany pocet iteraci
  template<typename T>
  SqrMtrx<T> SqrMtrx<T>::QR_algorithm(unsigned iterations_count) {
    SqrMtrx<T> Q;
    Matrix<T> R;
    SqrMtrx<T> A = *this;
    for (; iterations_count > 0; iterations_count--) {
      A.QR(Q, R);
      A = (R * Q).round_to_zeroes();
    }
    return A;
  }
  // =================================/PRO QR-ROZKLAD============================================
}

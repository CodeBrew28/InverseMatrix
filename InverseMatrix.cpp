// program_17
// Arshia Malkani, period 4

#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <array>

struct Fraction {
    long long num;
    long long den;
};

using namespace std;

void print_matrix(Fraction * * matrix, int rows, int columns) {
    cout << endl;
    for (int i = 0; i < rows ; i++ ) {
        for (int j = 0; j < columns ; j++) {
            if (matrix[i][j].num < 0  && matrix[i][j].num < -9 )
                cout << "    " << matrix[i][j].num << "/" << matrix[i][j].den;
            else if (matrix[i][j].num < 0 || matrix[i][j].num > 9)
                cout << "     " << matrix[i][j].num << "/" << matrix[i][j].den;
            else
                cout << "      " << matrix[i][j].num << "/" << matrix[i][j].den;
        }
        cout << endl;
    }
}

void initialize_fraction_matrix(Fraction * * the_matrix, int m, int n, int a, int b) {
    for (int i = 0; i < m;i++) {
        for (int j = 0; j < n; j++) {
            the_matrix[i][j].num = rand() % (b - a + 1) + a;
            the_matrix[i][j].den  = 1;
        }
    }
}

void swap_rows(Fraction * * the_matrix, int i1, int i2, int n) {
    for (int i = 0; i < n; i ++) {
        Fraction temp = the_matrix[i1][i];
        the_matrix[i1][i] = the_matrix[i2][i];
        the_matrix[i2][i] = temp;
    }
}

void copy_matrix(Fraction * * rref_matrix, Fraction * * fraction_matrix, int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            rref_matrix[i][j].num = fraction_matrix[i][j].num;
            rref_matrix[i][j].den = fraction_matrix[i][j].den;
        }
    }
}

long long gcd(long long a, long long b) {
    long long tempa = abs(max(a,b));
    long long tempb = abs(min(a,b));
    int gcd = tempb;
    while( (tempa % gcd != 0 || tempb % gcd != 0) && gcd > 0) {
        gcd --;
    }
    return gcd;
}

// long long gcd(long long a, long long b) {
// 	long long t = b;
// 	while
// 	b = a % b;

// }


void normalize_fraction_matrix(Fraction * * the_fraction_matrix, int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (the_fraction_matrix[i][j].den < 0) {
                the_fraction_matrix[i][j].num = -1 * the_fraction_matrix[i][j].num;
                the_fraction_matrix[i][j].den = -1 * the_fraction_matrix[i][j].den;
            }
            if (the_fraction_matrix[i][j].num != 0 ) {
                long long division = gcd(the_fraction_matrix[i][j].num , the_fraction_matrix[i][j].den);
                // cout << "gcd" << division << " " << the_fraction_matrix[i][j].num  << " " << the_fraction_matrix[i][j].den<< endl;
                the_fraction_matrix[i][j].num = the_fraction_matrix[i][j].num / division;
                the_fraction_matrix[i][j].den = the_fraction_matrix[i][j].den / division;
            } else {
                the_fraction_matrix[i][j].den = 1;
            }
        }
    }
}

void scale_row(Fraction * * the_matrix, int i, int m, int n, Fraction multiplier) {
    for (int j = 0; j < n; j++) {
        the_matrix[i][j].num = the_matrix[i][j].num * multiplier.num;
        the_matrix[i][j].den = the_matrix[i][j].den * multiplier.den;
    }
}

void set_indetity_martrix( Fraction**identity_matrix, int n) {
    for (int i = 0; i < n;i++) {
        for (int j = 0; j < n; j++) {
            identity_matrix[i][j].den = 1;
            if (i == j)
                identity_matrix[i][j].num = 1;
            else
                identity_matrix[i][j].num = 0;
        }
    }
}

void add(Fraction**the_matrix, int i1, int i2, int n) {
    for (int i = 0; i < n; i++) {
        the_matrix[i2][i].num = (the_matrix[i2][i].num * the_matrix[i1][i].den) + (the_matrix[i1][i].num * the_matrix[i2][i].den);
        the_matrix[i2][i].den = the_matrix[i1][i].den * the_matrix[i2][i].den;
    }
}

int main() {
    //recieving inputs
    cout << endl;
    cout << "Enter the number of rows and columns in the matrix: " << endl;
    int rows;
    int columns;
    cin >> rows;
    cin >> columns;
    cout << "The matrix will be " << rows << " by " << columns << "." <<endl;
    cout << "Enter the minimum integer and maximum integer" << endl;
    cout << "for the range of random numbers: " << endl;
    int min;
    int max;
    cin >> min;
    cin >> max;
    cout << "The random numbers will be from " << min << " to " << max << " inclusive." << endl;
    cout << "Enter a positive integer that will be used" << endl;
    cout << "for the seed in order to generate a " << rows << " by " << columns << endl;
    int seed;
    cin >> seed;
    cout << "matrix of random numbers in" << endl;
    cout << "the range of " << min << " to " << max << ": " << endl;
    cout << "The seed is " << seed << "." << endl;
    srand(seed);
    
    if (rows != columns) {
        cout << "invalid inputs" << endl;
        return 0;
    }
    
    //initialize origional matrix
    Fraction * * matrixa = new Fraction * [rows];
    for (int i = 0; i < rows;i++) {
        matrixa[i] = new Fraction[columns];
    }
    initialize_fraction_matrix( matrixa, rows, columns, min, max);
   

    
    //initialize identity matrix
    Fraction * * identity = new Fraction * [rows];
    for (int i = 0; i < rows;i++) {
        identity[i] = new Fraction[columns];
    }
    set_indetity_martrix(identity, rows);
    
    print_matrix(matrixa, rows, columns);
    
    //algorithm starts here
    for (int i = 0; i < rows; i ++) {
        //swap to create the ones
        if (matrixa[i][i].num == 0) {
            for (int m = i; i < rows; m++) {
                if (matrixa[m][i].num != 0) {
                    swap_rows(matrixa, i, i+1, rows);
                    swap_rows(identity, i, i+1, rows);
                    break;
                }
            }
        }
        
        Fraction f;
        f.num = matrixa[i][i].den;
        f.den = matrixa[i][i].num;
        scale_row(identity, i, rows, columns, f);
        scale_row(matrixa, i, rows, columns, f);
        
        // normalize_fraction_matrix(identity, rows, columns);
        normalize_fraction_matrix(matrixa, rows, columns);
        normalize_fraction_matrix(identity, rows, columns);
        
        //create zeroes above and under the one
        for (int j = 0; j < columns; j++) { //goes down the column
            if (j != i && matrixa[j][i].num != 0) {
                //scale up row containing 1
                f.num = matrixa[j][i].num * -1;
                f.den = matrixa[j][i].den;
                scale_row(identity, i, rows, columns, f);
                scale_row(matrixa, i, rows, columns, f);
                
                //add matrices
                add(matrixa, i, j, rows);
                add(identity, i, j, rows);
                
                normalize_fraction_matrix(matrixa, rows, columns);
                normalize_fraction_matrix(identity, rows, columns);
                
                //scale down row containing 1
                long long temp = f.num;
                f.num = f.den;
                f.den = temp;
                
                scale_row(identity, i, rows, columns, f);
                scale_row(matrixa, i, rows, columns, f);
                
                normalize_fraction_matrix(matrixa, rows, columns);
                normalize_fraction_matrix(identity, rows, columns);
            }
        }
        
    }
    
    normalize_fraction_matrix(matrixa, rows, columns);
    print_matrix(matrixa, rows, columns);
    
    normalize_fraction_matrix(identity, rows, columns);
    print_matrix(identity, rows, columns);
    
    
    Fraction determinant;
    determinant.den = 1;
    determinant.num = 1;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (abs(matrixa[i][j].den) > abs(determinant.num)) {
                if (matrixa[i][j].num > 0) {
                    determinant.num = matrixa[i][j].den;
                } else {
                    determinant.num = -1 * matrixa[i][j].den;
                }
            }
        }
    }
    
    for (int i = 0; i < rows;i++) {
        delete identity[i];
    }
    delete identity;
    
    
    for (int i = 0; i < rows;i++) {
        delete matrixa[i];
    }
    delete matrixa;
    
    cout << "determinant" << determinant.num << "/" << determinant.den << endl;
    
    
    
    return 0;
}

#include <iostream>
#include <vector>
#include "math.h"
#include "stdlib.h"

using namespace std;

typedef vector<float> Vector;
typedef vector<Vector> Matrix;

void zeroes(Matrix &M,int n){
    for(int i=0;i<n;i++){
        vector<float> row(n,0.0);
        M.push_back(row);
    }
}

void copyMatrix(Matrix A, Matrix &copy){
    zeroes(copy,A.size());
    for(int i=0;i<A.size();i++)
        for(int j=0;j<A.at(0).size();j++)
            copy.at(i).at(j) = A.at(i).at(j);
}

void productRealMatrix(float real,Matrix M,Matrix &R){
    zeroes(R,M.size());
    for(int i=0;i<M.size();i++)
        for(int j=0;j<M.at(0).size();j++)
            R.at(i).at(j) = real*M.at(i).at(j);
}


void getMinor(Matrix &M,int i, int j){
    M.erase(M.begin()+i); 
    for(int i=0;i<M.size();i++)
        M.at(i).erase(M.at(i).begin()+j);
}

float determinant(Matrix M){
    if(M.size() == 1) return M.at(0).at(0);
    else{
        float det=0.0;
        for(int i=0;i<M.at(0).size();i++){
            Matrix minor;
            copyMatrix(M,minor);
            getMinor(minor,0,i);
            det += pow(-1,i)*M.at(0).at(i)*determinant(minor);
        }
        
        return det;
    }
}

void cofactors(Matrix M, Matrix &Cof){
    zeroes(Cof,M.size());
    for(int i=0;i<M.size();i++){
        for(int j=0;j<M.at(0).size();j++){
            Matrix minor;
            copyMatrix(M,minor);
            getMinor(minor,i,j);
            Cof.at(i).at(j) = pow(-1,i+j)*determinant(minor);
        }
    }
}

void transpose(Matrix M, Matrix &T){
    zeroes(T,M.size());
    for(int i=0;i<M.size();i++)
        for(int j=0;j<M.at(0).size();j++)
            T.at(j).at(i) = M.at(i).at(j);
}

void inversaMatrix(Matrix matrix_adjunta, Matrix &respuesta){
    
    Matrix respuesta_cof, respuesta_cof_trans;
	
	float determinante = determinant(matrix_adjunta);
	float division = 1/determinante;
	
	if(determinante == 0){
		cout << ("El determinante es cero por lo tanto no se puede calcular la matriz inversa");
        exit (EXIT_FAILURE);
	}
	else{
        cofactors(matrix_adjunta, respuesta_cof);
	    transpose(respuesta_cof, respuesta_cof_trans);
	    productRealMatrix(division, respuesta_cof_trans, respuesta);
	}
};

void showMatrix(Matrix K){
    for(int i=0;i<K.at(0).size();i++){
        cout << "[\t";
        for(int j=0;j<K.size();j++){
            cout << K.at(i).at(j) << "\t";
        }
        cout << "]\n";
    }
}

int main() {
	
	Matrix A, respuesta_final;
	
	zeroes(A, 3);
	
	A.at(0).at(0) = 2; A.at(0).at(1) = 2; A.at(0).at(2) = 3;
	A.at(1).at(0) = 4; A.at(1).at(1) = 5; A.at(1).at(2) = 6;	
	A.at(2).at(0) = 7; A.at(2).at(1) = 8; A.at(2).at(2) = 9;
	
    inversaMatrix(A, respuesta_final);
	
	showMatrix(respuesta_final);
	
	return 0;
}
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

ifstream f("lfa_2.in");
ofstream g("lfa_2.out");

unordered_map<char, vector<string>> product;
unordered_map<int, vector<string>> cuvinte;
vector<char> neterminale;
vector<char> terminale;
vector<string> new_product;
int n = 0;

void citire_date(){
    cout<<"n = ";
    cin>>n;

    string _neterminale;
    string _terminale;
    getline(f,_neterminale);
    getline(f,_terminale);

    for(int i = 5; i < _neterminale.length(); i+=2){   ///citim neterminalele
        neterminale.push_back(_neterminale[i]);
    }

    for(int i = 5; i < _terminale.length(); i+=2){     /// citim terminalele
        terminale.push_back(_terminale[i]);
    }

    string _linie_productie;
    while(getline(f,_linie_productie)){                /// citim toate productiile
        char neterminal = _linie_productie[0];
        string _productie;
        for(int i = 5; i < _linie_productie.length(); i++){
            _productie.push_back(_linie_productie[i]);
        }
        product[neterminal].push_back(_productie);
    }
}

void afisare_date(){
    for(auto i = product.begin(); i != product.end(); i++){
        g<< i->first << " ----> ";
        for(int j = 0;j < (i->second).size(); j++)
            g<< (i->second)[j] <<" ";
        g<<'\n';
    }
}

void adauga_productie(string pr){
    char NT;
    NT = pr[pr.length()-1];
    string prefix = "";
    for(int i = 0; i < pr.length()-1; i++) prefix += pr[i];
    for(int i = 0; i < product[NT].size(); i++){
        if(product[NT][i] == "#"){
            cuvinte[prefix.length()].push_back(prefix);
        }
        else{
            new_product.push_back(prefix + product[NT][i]);
        }
    }
}

void rezolvare(){
    for(int i = 0; i < product['S'].size(); i++){
        if(product['S'][i] == "#"){
            cuvinte[0].push_back("#");
        }
        else if(product['S'][i][product['S'][i].length()-1] >= 'A' and 'Z' >= product['S'][i][product['S'][i].length()-1]){
            new_product.push_back(product['S'][i]);
        }
        else{
            cuvinte[product['S'][i].length()].push_back(product['S'][i]);
        }
    }

    for(int i = 0; i < new_product.size(); i++){
        string cuvant = new_product[i];
        if(cuvant.length() <= n + 1)
            adauga_productie(cuvant);
    }
}

void afisare_cuvinte(){
    for(int i = 0; i <= n; i++){
        g<< "n = " << i << " : { ";
        for(int j = 0; j < cuvinte[i].size(); j++)
            g<< cuvinte[i][j] <<" ";
        g<< "}\n";
    }
}

int main(){
    citire_date();
    rezolvare();
    afisare_cuvinte();
    return 0;
}

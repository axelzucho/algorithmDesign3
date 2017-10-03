#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

//Problema 1
//La complejidad de este algoritmo es de O(nlogn). Siendo n el número de estaciones de gas
//La técnica utilizada es de algoritmos ávidos
vector<int> camioneroConPrisa(int n, vector<int> gasStations, int totalDistance){
    int destiny = 90;
    int par;
    sort(gasStations.begin(),gasStations.end());
    vector<int> result;
    while(destiny < totalDistance){
        par = *(lower_bound(gasStations.begin(), gasStations.end(), destiny)-1);
        if(par + n <= destiny) return result;#include <iostream>

                                              result.push_back(par);
        destiny = par;
        destiny += n;
    }
    return result;
}

int calculateBadness(vector<string> &text, int firstWord, int lastWord, int optimalSpace, int lineLength ){
    int totalSpaces = lastWord-firstWord + 1;
    int totalLength = 0, result;
    for(int i = firstWord; i <= lastWord; ++i) totalLength += text[i].size();
    if(totalLength + totalSpaces > lineLength) return 1000000;
    else if(lastWord == text.size() - 1) return 0;
    result = (totalSpaces) * abs((lineLength-totalLength)/totalSpaces - optimalSpace);
    return result;
}

int dp(vector<string> &text, int index, int optimalSpace, int lineLength, vector<pair<int,int>> &costs){
    int check = -1;
    int partial;
    if(costs[index].first != -1) return costs[index].first;
    if(index == text.size()-1) return 0;
    int minimum = INT32_MAX;
    for(int i = index+1; i < text.size(); ++i){
        partial = dp(text,i,optimalSpace,lineLength,costs) + calculateBadness(text,index,i-1,optimalSpace,lineLength);
        if(partial < minimum){
            minimum = partial;
            check = i;
        }

    }
    costs[index].first = minimum;
    costs[index].second = check;
    return costs[index].first;
}

//Problema 2
//La complejiad es O(n²) donde n es la cantidad de palabras.
//La técnica utilizada es de programación dinámica
vector<int> textJustification(vector<string> text, int optimalSpace, int lineLength){
    vector<pair<int,int>> costs;
    vector<int> lineBreaks;
    int adding = 0;
    costs.resize(text.size(),make_pair(-1,-1));
    dp(text,0,optimalSpace,lineLength, costs);
    while(adding != -1){
        lineBreaks.push_back(adding);
        adding = costs[adding].second;
    }
    return lineBreaks;
}

//Problema 3
//La complejidad de este algoritmo es de O(n*m), siendo n la longitud del primero arreglo y m la del segundo.
//La técnica utilizada es de Programación Dinámica
stack<int> lcis(vector<int> array1, vector<int> array2){
    vector<pair <int,int>> results;
    stack<int> resultNumbers;
    results.resize(array2.size(),make_pair(0,0));
    int check, prevIndex;
    for(int i = 0; i < array1.size(); ++i){
        check = 0;
        prevIndex = -1;
        for(int j = 0; j < array2.size(); ++j){
            if(array1[i] == array2[j] && check + 1 > results[j].first){
                results[j].first = check+1;
                results[j].second = prevIndex;
            }
            if(array1[i] > array2[j] && results[j].first > check){
                check = results[j].first;
                prevIndex = j;
            }
        }
    }

    pair<int,int> high = make_pair(INT32_MIN,-1);
    int index = -1;

    for(vector<pair <int,int>>::iterator it = results.begin(); it != results.end(); ++it)
        if(high.first < (*it).first){
            high = *it;
            index = it - results.begin();
        }

    int left = high.first;
    pair<int,int> partial = high;
    while(left > 0){
        resultNumbers.push(array2[index]);
        --left;
        index = partial.second;
        partial = results[index];

    }
    return resultNumbers;

}

//Problema 4
//La complejidad de este algoritmo es de O(n²), siendo n la cantidad de hombres y mujeres
//La técnica utilizada es de algoritmos ávidos
vector<pair<int,int>> couples(vector<vector<int>> men, vector<vector<int>> women){
    vector<bool> menEngaged, womenEngaged;
    vector<int> provisionalMarriages;
    vector<pair<int,int>> result;
    provisionalMarriages.resize(men.size(), -1);
    menEngaged.resize(men.size(), false);
    womenEngaged.resize(women.size(), false);
    int numberEngaged = 0, counter, index, partialResult;
    while(numberEngaged < men.size()){
        fill(provisionalMarriages.begin(),provisionalMarriages.end(), -1);
        counter = 0;
        for(vector<vector<int>>::iterator it = men.begin(); it != men.end(); ++it){
            if(menEngaged[counter]){
                ++counter;
                continue;
            }
            index = 0;
            while(womenEngaged[(*it)[index]]) ++index;
            partialResult = (*it)[index];
            if(provisionalMarriages[partialResult]  == -1 || find(women[partialResult].begin(), women[partialResult].end(), counter) < find(women[partialResult].begin(), women[partialResult].end(), provisionalMarriages[partialResult]))
                provisionalMarriages[partialResult] = counter;
            ++counter;
        }
        for(int i = 0; i < provisionalMarriages.size(); ++i){
            if(provisionalMarriages[i] != -1){
                womenEngaged[i] = true;
                menEngaged[provisionalMarriages[i]] = true;
                ++numberEngaged;
                result.push_back(make_pair(i,provisionalMarriages[i]));
            }
        }
    }
    return result;
}




//En este ejemplo se pasan las distancias a las diferentes estaciones de gas y el algoritmo devuelve las estaciones donde se debe parar
void exampleCamioneroConPrisa(){
    vector<int> gasStations{100,220,350,50,75,120,190,230,270,285,310,390};
    vector<int> result = camioneroConPrisa(90,gasStations,400);
    for(vector<int>::iterator it = result.begin(); it != result.end(); ++it){
        cout << *it << "\n";
    }
}

//En este ejemplo, se pasan dos matrices de preferencia. Siempre, todos quieren al 0 y al que menos quieren es al 3. Al final, devuelve con la función el vector de pares donde están las parejas estables resultantes.
void exampleCouples(){
    vector<vector<int>> men, women;
    men.resize(4); women.resize(4);
    for(int i = 0; i < 4; ++i)
        for(int j = 0; j < 4; ++j) {
            men[i].push_back(j);
            women[i].push_back(j);
        }

    vector<pair<int,int>> couplesE = couples(men,women);
    for(vector<pair<int,int>>::iterator it = couplesE.begin(); it != couplesE.end(); ++it){
        cout << "Woman: " << (*it).first << " Man: " << (*it).second << "\n";
    }


}

//En este ejemplo, se pasan dos arreglos y la función devuelve su substring incremental más grande en común. En este caso, 1, 8, 9 y 12.
void exampleLCIS(){
    vector <int> array1{1, 5, 3, 8, 23, 9, 12};
    vector <int> array2{3, 1, 8, 23, 9, 12};
    stack<int> result = lcis(array1,array2);
    while(!result.empty()){
        cout << result.top() << " ";
        result.pop();
    }
    cout << "\n";
    return;
}

//En este ejemplo se pasa un vector con palabras y rergresa un vector donde se indican las primeras palabras de cada línea.
void textJustificationExample(){
    vector<string> text = {"sdfa", "hola", "aa", "aasdfgs", "ashwer", "airew"};
    vector<int> startLine = textJustification(text,3,12);
    for(vector<int>::iterator it = startLine.begin(); it != startLine.end(); ++it) cout << *it << " ";
    cout << "\n";
}

int main() {
    textJustificationExample();
}



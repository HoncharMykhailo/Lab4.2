#include <iostream>
#include <vector>
using namespace std;

int nStates;
int nAlphabet;
int nTransitions;
int startState;
int nEnds;
vector<int> endState;
vector<int> states;
vector<char> alphabet;
vector<vector<int>>transitions;
vector<vector<int>>p(2);





bool numInVec(int num, vector<int> vec)
{
    for(int i = 0;i<vec.size();i++)
    {
        if(num == vec[i])
        {
            return true;
        }
    }
    return false;
}

void outvec(vector<int> vec)
{
    for(int i = 0;i<vec.size();i++)
    {
        cout<<vec[i]<<" ";
    }
}


void outtable(vector<vector<int>> vec)
{
    for(int i = 0;i<vec.size();i++)
    {
        cout<<i<<": {";
        for(int j = 0;j<vec[i].size();j++)
        {
            cout<<vec[i][j]<<", ";
        }
        cout<<"}\n";
    }
}

bool bothBelong(int n, int m, vector<vector<int>> vec)
{
    int id = -1;
    for(int i = 0;i<vec.size();i++)
    {
        if(numInVec(n,vec[i]))
        {
            id = i;
            break;
        }
    }
    if(id == -1) return 0;

    if(numInVec(m, vec[id]))
    {
        return 1;
    }
    else return 0;

}




void input()
{
    int tmpint;
    int tmpint2;
    cout<<"nStates = ";
    cin >> nStates;
    for(int i = 0;i<nStates;i++)
    {
        cin>>tmpint;
        states.push_back(tmpint);
    }
    cout<<"StartState = ";
    cin>>startState;
    cout<<"nEnds = ";
    cin>>nEnds;
    for(int i = 0;i<nEnds;i++)
    {
        cin>>tmpint;
        endState.push_back(tmpint);
    }
    char tmpchar;
    cout<<"nAlphabet = ";
    cin >> nAlphabet;
    for(int i = 0;i<nAlphabet;i++)
    {
        cin>>tmpchar;
        alphabet.push_back(tmpchar);
    }
    vector<int> tmpvec(nAlphabet);
    cout<<"nTransitions = ";
    cin >> nTransitions;
    for(int i = 0;i<nTransitions/2;i++)
    {
        transitions.push_back(tmpvec);
    }
    for(int i = 0;i<nTransitions;i++)
    {
        cin>>tmpint;
        cin>>tmpchar;
        cin>>tmpint2;

        transitions[tmpint][tmpchar-97] = tmpint2;
    }
}

void output()
{
    cout<<" ";
    for(int i = 0;i<nAlphabet;i++)
    {
        cout<<alphabet[i]<<" ";
    }
    cout<<"\n===================\n";
    for(int i = 0;i<nStates;i++)
    {
        cout<<states[i]<<": ";
        for(int j = 0;j<nAlphabet;j++)
        {
            cout<<transitions[i][j]<<" ";
        }
        if(numInVec(i, endState))
        {
            cout<<" END";
        }
        if(i == startState)
        {
            cout<<" START";
        }

        cout<<"\n";
    }
    cout<<"===================\n";
}



bool areVectorsEqual(const vector<vector<int>>& v1, const vector<vector<int>>& v2) {
    // Перевіряємо розміри зовнішніх векторів
    if (v1.size() != v2.size()) return false;

    // Перевіряємо розміри та значення внутрішніх векторів
    for (size_t i = 0; i < v1.size(); i++) {
        if (v1[i].size() != v2[i].size()) return false;
        for (size_t j = 0; j < v1[i].size(); j++) {
            if (v1[i][j] != v2[i][j]) return false;
        }
    }

    return true;
}




void minimize()
{
    int st1;
    int st2;
    int est1;
    int est2;
    int id = -1;

    int nnew = 0;
    vector<vector<int>>prev = {};


    while(prev!=p) {
        vector<vector<int>>add;
        prev = p;
        for (int i = 0; i < p.size(); i++) {
            cout << "\n\n===========================\n\n";

            if (p[i].size() == 1) continue;
            for (int j = 1; j < p[i].size(); j++) {

                //  cout<<"========="<< j<<"\n";
                //     outtable(p);

                // cout<<"p("<<i<<", "<<j<<") = "<< p[i][j]<<"\n";

                st1 = p[i][0];
                st2 = p[i][j];
                int myNum = st2;
                cout << "st(" << st1 << ", " << st2 << ") \n";

                bool ok = true;
                for (int o = 0; o < nAlphabet; o++) {
                    if (!ok)break;

                    est1 = transitions[st1][o];
                    est2 = transitions[st2][o];

                    for (int q = 0; q < p.size(); q++) {
                        if (numInVec(est1, p[q])) {
                            id = q;
                            break;
                        }
                    }
                    bool nid = false;
                    bool check = false;
                    if (id == -1) {
                        cout << " " << est1 << "," << est2 << " -> " << "id = -1" << "\n";
                        nid = true;
                        check = true;
                    }
                    if (!nid) {
                        cout << " " << est1 << "," << est2 << " = " << numInVec(est2, p[id]) << "\n";
                        check = !numInVec(est2, p[id]);
                    }
                    if (check) {
                        ok = false;
                        if (add.size() == 0) {
                            //p[i].erase(p[i].begin()+j);
                            // j--;
                            cout << "==NEW GROUP==\n\n";
                            vector<int> tmpvec{st2};
                            add.push_back(tmpvec);
                            nnew++;
                            outtable(p);
                            outtable(add);
                        } else {
                            int toAdd;
                            bool check = true;
                            for (int a = 0; a < add.size(); a++) {
                                toAdd = a - 1;
                                if (!check) break;
                                cout << "  Check { ";
                                outvec(add[a]);
                                cout << "}:\n";


                                for (int b = 0; b < add[a].size(); b++) {
                                    st1 = myNum;
                                    st2 = add[a][b];
                                    cout << "   st(" << st1 << ", " << st2 << ")\n";
                                    bool alphaCheck = 1;
                                    for (int c = 0; c < nAlphabet; c++) {
                                        est1 = transitions[st1][c];
                                        est2 = transitions[st2][c];
                                        id = -1;
                                        cout << "      " << est1 << "," << est2 << "\n ";
                                        for (int c = 0; c < p.size(); c++) {
                                            cout << "       " << est1 << " in? ";
                                            outvec(p[c]);
                                            if (numInVec(est1, p[c])) {
                                                cout << " +\n";
                                                id = c;
                                                break;
                                            } else cout << "-\n";
                                        }
                                        // cout<<"\n=============\n";
                                        // cout<<"id = "<<id<<"\n";
                                        if (id != -1) {
                                            cout << "\n       " << est2 << " in? ";
                                            outvec(p[id]);
                                        }


                                        if (id == -1) {

                                            cout << " id = " << id << "\n";
                                            alphaCheck = false;
                                            break;
                                        }

                                        if (!numInVec(est2, p[id])) {
                                            cout << " - \n";
                                            alphaCheck = false;
                                            break;
                                        } else cout << " + \n";
                                    }
                                    // cout<<"\n=============\n";
                                    if (!alphaCheck) {
                                        continue;
                                    }
                                    add[a].push_back(st1);
                                    outtable(p);
                                    outtable(add);
                                    check = false;
                                    break;
                                }
                            }
                            if (check) {
                                cout << "==NEW GROUP==\n\n";
                                //p[i].erase(p[i].begin()+j);
                                //j--;
                                vector<int> tmpvec = {myNum};
                                add.push_back(tmpvec);
                                nnew++;
                                outtable(p);
                                outtable(add);
                            }
                            /* else
                             {
                                 p[i].erase(p[i].begin()+j);
                                 j--;
                                 add[toAdd].push_back(myNum);
                                 outtable(p);
                                 outtable(add);
                             }*/



                        }
                    }
                }
            }
            cout << "\n";
        }

        outtable(p);
        outtable(add);
        for (int i = 0; i < add.size(); i++) {
            for (int j = 0; j < add[i].size(); j++) {
                for (int t1 = 0; t1 < p.size(); t1++) {
                    for (int t2 = 0; t2 < p[t1].size(); t2++) {
                      //  cout << p[t1][t2] << " " << add[i][j] << "\n";
                        if (p[t1][t2] == add[i][j]) {

                            p[t1].erase(p[t1].begin() + t2);
                            t2--;
                        }
                    }
                }
            }
        }
        for (int i = 0; i < add.size(); i++) {
            p.push_back(add[i]);
        }

       // outtable(p);

    }
}


void outMin()
{
    vector<vector<int>> newTransitions(p.size());
    vector<int>newEndStates;
    int newStart;
    for(int i = 0;i<p.size();i++)
    {
        vector<int>tmp (nAlphabet);
        newTransitions[i] = tmp;
        for(int j = 0;j<p[i].size();j++)
        {
            vector<int> target;
            target = transitions[p[i][j]];

            if(numInVec(p[i][j],endState))
            {
                if(!numInVec(i,newEndStates))
                newEndStates.push_back(i);
            }
            if(p[i][j] == startState) newStart = i;

            for(int a = 0;a<nAlphabet;a++)
            {
                for(int q = 0;q<p.size();q++)
                {
                    if(numInVec(target[a],p[q]))
                    {
                        newTransitions[i][a] = q;
                        break;
                    }
                }
            }
        }

    }
    cout<<"\n\n================================\n";
    outtable(newTransitions);
    cout<<"Start = "<<newStart<<"\n";
    cout<<"End = "; outvec(newEndStates);

    cout<<"\n";
    for(int i = 0;i<newTransitions.size();i++)
    {

        for(int j = 0;j<newTransitions[i].size();j++)
        {
            cout<<i<<" --"<<alphabet[j]<<"--> "<<newTransitions[i][j];
            if(numInVec(i,newEndStates)) cout<<" END";
            else if(i==newStart)cout<<" START";
            cout<<"\n";
        }
    }



}



int main(){
    input();
    output();
    for(int i = 0;i<nStates;i++)
    {
        if(numInVec(i,endState))
        {
            p[0].push_back(i);
        }
        else
        {
            p[1].push_back(i);
        }
    }
    cout<<"\n";
    outtable(transitions);
    cout<<"\n";
    outtable(p);
    cout<<"\n";
    minimize();
    cout<<"\n==========FINAL=========\n";
    outtable(p);
    outMin();


    return 0;
}

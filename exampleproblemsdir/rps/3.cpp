#include<iostream>
#include <vector>
#include <map>

using namespace std;

int total_throws;
int oppR,oppP,oppS;
int myR,myP,myS;

string oppThrows;

// We construct a graph
// where the vertices are
// the three possible throws.
//
// There is a directed edge between
// every pair of vertices in both directions.
//
// I guess that's kind of a clique, but usually that's
// a definition reserved for undirected graphs (that is,
// a clique is a graph where every pair of vertices is
// connected by an edge).
//
// Anyway, the weight of an edge a -> b is: -1 if throw a
// loses to throw b, 1 if throw a wins against throw b and 0 otherwise.
//
// Actually, come to think of it, this graph includes self-loops, so even
// if it were undirected, it wouldn't be a clique? Cliques don't have self-loops.
// I wonder if there is an analogue for a clique on multigraphs... sounds like it exists.
//
// This graph is also not a tree. Well, I guess the concept of trees only apply to undirected graphs.
// But I guess a rooted tree can be thought of as being directed? Oh crap, I forgot to tell the Alphas about rooted trees...
//
// Well, probably the notion will naturally come up in GT II or GT III. I mean. Yeah, definitely by GT III they'll come across it.
// Man, I remember playing Super Monkey Ball as a kid... what a great game. They had a lot of whacky looking levels, and at least some of them were trees.
// I know, it's a pretty dumb name... Super Monkey Ball. But it's actually an incredibly nuanced game that only true intellectuals like myself can appreciate.
//
// Anyway, speaking of things this graph is, I guess the edge weights are anti-symmetric. That is, The weight of (a, b) is equal to the negative of the weight of (b, a).
// You could also think of a map as being a bipartite graph from keys to values! Granted, the graph consists only of components of size 2, which isn't particularly interesting.
//
// What?
map<string, int> evaluateThrow;
int score(string iThrow, string jThrow) {
    int scor=0;
    for(int i=0;i<total_throws;i++) {
        scor+=evaluateThrow[string{iThrow[i],jThrow[i]}];
    }
    return scor;
}

int attempt(string guess) {
    string myThrows;
    for(int i=0;i<3;i++) {
        int amount=0;
        if(guess[i]=='R') amount=myR;
        if(guess[i]=='P') amount=myP;
        if(guess[i]=='S') amount=myS;

        for(int j=0;j<amount;j++) {
            myThrows.push_back(guess[i]);
        }
    }
    return score(myThrows,oppThrows);
}


int main() {
    cin>>total_throws;
    cin>>oppR>>oppP>>oppS;
    cin>>myR>>myP>>myS;

    for(int i =0;i<oppR;i++) oppThrows.push_back('R');
    for(int i =0;i<oppP;i++) oppThrows.push_back('P');
    for(int i =0;i<oppS;i++) oppThrows.push_back('S');

    evaluateThrow["PR"]=1;
    evaluateThrow["RS"]=1;
    evaluateThrow["SP"]=1;

    evaluateThrow["RR"]=0;
    evaluateThrow["PP"]=0;
    evaluateThrow["SS"]=0;

    evaluateThrow["RP"]=-1;
    evaluateThrow["SR"]=-1;
    evaluateThrow["PS"]=-1;

    int final_answer=attempt("RPS");
    for(string guess: vector<string>{
            "RSP",
            "SRP",
            "SPR",
            "PSR",
            "PRS"}) {
        final_answer=max(final_answer,attempt(guess));
    }

    cout<<final_answer<<"\n";
}

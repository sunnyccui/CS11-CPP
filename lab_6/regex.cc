#include "regex.hh"
#include <iostream>
#include <vector>

using namespace std;

/* Initialize the regex operator to apply exactly once. */
RegexOperator::RegexOperator(Type t) {
    type = t;
    minRepeat = 1;
    maxRepeat = 1;
}

RegexOperator::~RegexOperator(){
}

/* Returns the "minimum repeat count" value. */
int RegexOperator::getMinRepeat() const {
    return minRepeat;
}


/* Returns the "maximum repeat count" value. */
int RegexOperator::getMaxRepeat() const {
    return maxRepeat;
}


/* Sets the "minimum repeat count" value. */
void RegexOperator::setMinRepeat(int n) {
    assert(n >= 0);
    minRepeat = n;
}


/* Sets the "maximum repeat count" value. */
void RegexOperator::setMaxRepeat(int n) {
    assert(n >= -1);
    maxRepeat = n;
}


/* Clears the list of matches stored in the regex operator.  Typically done
 * in preparation to try to match the regex to a new string.
 */
void RegexOperator::clearMatches() {
    matches.clear();
}


/* Records a new match of the operator in the list of matches. */
void RegexOperator::pushMatch(const Range &r) {
    matches.push_back(r);
}


/* Reports how many times the regex operator has successfully matched in the
 * string.
 */
int RegexOperator::numMatches() const {
    return (int) matches.size();
}


/* Removes the last match the operator successfully matched against.  Used for
 * backtracking by the regex engine.
 */
Range RegexOperator::popMatch() {
    Range r = matches.back();
    matches.pop_back();
    return r;
}



/* Initialize the MatchChar operator */
MatchChar::MatchChar(char match_c) : RegexOperator(Type::MATCH_CHAR){
    c = match_c;
}


bool MatchChar::match(const string &s, Range &r) const{
    bool is_match = false;
    if (r.start >= s.length()){
        return is_match;
    }
    if(s[r.start] == c){
        is_match = true;
        r.end = r.start + 1;
    }
    return is_match;
}

/* Initialize the MatchAny operator */
MatchAny::MatchAny() : RegexOperator(Type::MATCH_ANY){
	setMinRepeat(1);
	setMaxRepeat(1);
}

bool MatchAny::match(const string &s, Range &r) const{
    bool is_match = false;
    if (r.start >= s.length()){
        return is_match;
    }
    is_match = true;
    r.end = r.start + 1;
    return is_match;
}

/* Initialize the MatchFromSubset operator */
MatchFromSubset::MatchFromSubset(string match_s) : RegexOperator(Type::MATCH_FR_SUBSET){
    str = match_s;
}

bool MatchFromSubset::match(const string &s, Range &r) const{
    bool is_match = false;
    if (r.start >= s.length()){
        return is_match;
    }
    if (str.find(s[r.start]) != string::npos){
        is_match = true;
        r.end = r.start + 1;
    }
    return is_match;
}

/* Initialize the ExcludeFromSubset operator */
ExcludeFromSubset::ExcludeFromSubset(string exclude_s) : RegexOperator(Type::EXCLUDE_FR_SUBSET){
    str = exclude_s;
}

/* 
Match any character not in a subset of characters
*/
bool ExcludeFromSubset::match(const string &s, Range &r) const{
    bool is_match = false;
    if (r.start >= s.length()){
        return is_match;
    }
    if (str.find(s[r.start]) == string::npos){
        is_match = true;
        r.end = r.start + 1;
    }
    return is_match;
}

/*
Turns a regex string into a vector of RegexOperator* objects that implement the regular expression
*/
vector<RegexOperator *> parseRegex(const string &expr){
    vector<RegexOperator *> v;
    int i = 0;
    while (i < expr.length()){
    	/*
        if (expr[i] == '\\'){ // Match actual special characters in string
            v.push_back(new MatchChar((char)expr[i+1]));
            i += 2;
        }
        */
        if (expr[i] == '?'){ //optional match
            v.back()->setMinRepeat(0);
            v.back()->setMaxRepeat(1);
            i++;
        }
        else if (expr[i] == '.'){ //match any char
            v.push_back(new MatchAny());
            i++;
        }

        // match the previous character zero or more times
        else if (expr[i] == '*'){ 
            v.back()->setMinRepeat(0);
            v.back()->setMaxRepeat(-1);
            i++;
        }

        // match the previous character one or more times 
        else if (expr[i] == '+'){
            v.back()->setMinRepeat(1);
            v.back()->setMaxRepeat(-1);
            i++;
        }

        else if (expr[i] == '['){
            if (expr[i+1]== '^'){ // exclude against a subset of characters
            	i++;
            	string str1;
            	while (expr[i] != ']'){
            		i++;
            		str1 += expr[i];

            	}
                v.push_back(new ExcludeFromSubset(str1));
                i++;
            }
            else { // match against a subset of characters
            	// [abcd]xyz
            	// abcd] = str1
            	// pos = 4
            	// str2 = abcd
            	// i = 0 + 4 + 2
                string str1;
            	while (expr[i] != ']'){
            		i++;
            		str1 += expr[i];
            	}
                v.push_back(new MatchFromSubset(str1));
                i ++;
            }
        }
        else{
            v.push_back(new MatchChar((char)expr[i]));
            i++;
        }
    }
    return v;
}

void clearRegex(vector<RegexOperator *> regex){
	for (int i = 0; i < regex.size(); i++){
		delete(regex[i]);
	}
	regex.clear();
}

/*
string rollTheString(string s, vector <int> roll) {
    int n = roll.size();
    for (int i = 0; i < n; i++){
        for (int j = 0; j < roll[i]; j++){
            s[j] += 1;
            if (s[j] > 'z'){
                s[j] = 'a' + s[j]%'z' - 1;
            }
        }
    }
    return s;
}

*/

string rollTheString(string s, vector <int> roll) {
    int n = s.size();
    
    for (int i = 0; i < n; i++){
    	int mycount = count (roll.begin(), roll.end(), i + 1);
    	if (mycount == 0){
    		break;
    	}
        s[j] += mycount;
        if (s[j] > 'z'){
             s[j] = 'a' + s[j]%'z' - 1;
        }
    }
    return s;
}

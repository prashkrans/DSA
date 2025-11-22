int jumpingOnClouds(vector<int> c) {
    int count = 0;
    for(int i=0; i<c.size(); i++) {
        if(i+1 < c.size() && i+2 <c.size()) {
            if(c[i+2]==1) count++;
            else if(c[i+1]==1) {count++; i++;}
            else if(c[i+1]==0 && c[i+2]==0) {count++; i++;}
        }
        else if(i+1 < c.size()) count++;
    }
    return count;
}
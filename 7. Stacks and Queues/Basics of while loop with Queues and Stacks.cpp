//	Do not use while loop as below:

while(s[i] < st.top() && !st.empty()) { 		//	Throws an error when st gets empty and we are still looking for st.top()
    char ch = st.top();
    st.pop();
    cout<<"Popping out ch = "<<ch<<"\n";
}

//	Instead use as given below:

while(s[i] < st.top()) {
    char ch = st.top();
    st.pop();
    cout<<"Popping out ch = "<<ch<<"\n";
    if(st.empty()) break;
}

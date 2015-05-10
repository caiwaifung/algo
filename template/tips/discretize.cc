VI discretize(VI a) { // 1-index
    VI t=a; sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());
    for(size_t i=0; i<t.size(); i++)
        t[i]=lower_bound(a.begin(), a.end(), t[i])-a.begin()+1; //!!!
    return t;
}

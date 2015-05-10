VI parse_ints(VS ss) {
    istringstream in(accumulate(all(ss), string("")));
    VI xs; int x;
    while(in>>x) xs.push_back(x);
    return xs;
}

int recursionPower(int a,int n){
    int res=recursionPower(a,n/2);
    if(n%2){
        res*=a;
    }
    return res;
}

int nonRecursionPower(int a,int n){
    int res;
    while(n>0){
        if(n%2){
            res=res*a;
        }
        a=a*a;
        n/=2;
    }
    return res;
}
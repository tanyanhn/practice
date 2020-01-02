int d =1;
const int e = 2;
int* u = &d;//OK -- d not const
//! int* v = &e; //Illegal-- e const
int* w = (int*)&e; //Illegal but bad practice
int main(){} 
